/*
 * Copyright 2016 - 2018 Marcin Matula
 *
 * This file is part of Oap.
 *
 * Oap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Oap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Oap.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "oapNetwork.h"
#include "oapMatrixCudaCommon.h"

using LC_t = size_t;

Network::Network()
{}

Network::~Network()
{
  destroyLayers();
}

Layer* Network::createLayer (size_t neurons, const Activation& activation)
{
  Layer* layer = new Layer(activation);

  layer->allocateNeurons (neurons);
  createLevel (layer);

  return layer;
}

void Network::createLevel (Layer* layer)
{
  Layer* previous = nullptr;

  if (m_layers.size() > 0)
  {
    previous = m_layers.back();
  }

  addLayer (layer);

  if (previous != nullptr)
  {
    previous->allocateWeights (layer);
  }
}

void Network::addLayer (Layer* layer)
{
  m_layers.push_back (layer);
}

oap::HostMatrixUPtr Network::run (math::Matrix* inputs, Type argsType, oap::ErrorType errorType)
{
  Layer* layer = m_layers.front();

  if (argsType == Network::HOST)
  {
    layer->setHostInputs (inputs);
  }
  else if (argsType == Network::DEVICE)
  {
    oap::cuda::CopyDeviceMatrixToDeviceMatrix (layer->m_inputs, inputs);
  }

  forwardPropagation ();

  auto llayer = m_layers.back();

  math::Matrix* output = oap::host::NewMatrix (1, llayer->m_neuronsCount);
  oap::cuda::CopyDeviceMatrixToHostMatrix (output, llayer->m_inputs);

  return oap::HostMatrixUPtr (output);
}

void Network::setInputs (math::Matrix* inputs, Type argsType)
{
  Layer* layer = m_layers.front();

  if (argsType == Network::HOST)
  {
    layer->setHostInputs (inputs);
  }
  else if (argsType == Network::DEVICE)
  {
    layer->setDeviceInputs (inputs);
  }
}

void Network::setExpected (math::Matrix* expected, Type argsType)
{
  Layer* layer = m_layers.front();

  if (argsType == Network::HOST)
  {
    if (!m_expectedDeviceOutputs)
    {
      m_expectedDeviceOutputs = oap::cuda::NewDeviceMatrixHostRef (expected);
    }
    oap::cuda::CopyHostMatrixToDeviceMatrix (m_expectedDeviceOutputs, expected);
  }
  else if (argsType == Network::DEVICE)
  {
    m_expectedDeviceOutputs.reset (expected, false);
  }
  else if (argsType == Network::DEVICE_COPY)
  {
    if (!m_expectedDeviceOutputs)
    {
      m_expectedDeviceOutputs = oap::cuda::NewDeviceMatrixDeviceRef (expected);
    }
    oap::cuda::CopyDeviceMatrixToDeviceMatrix (m_expectedDeviceOutputs, expected);
  }
}

math::Matrix* Network::getOutputs (math::Matrix* outputs, Type argsType) const
{
  Layer* llayer = m_layers.back();
  if (argsType == Type::HOST)
  {
    oap::cuda::CopyDeviceMatrixToHostMatrix (outputs, llayer->m_inputs);
    return outputs;
  }
  else if (argsType == Type::DEVICE_COPY)
  {
    math::Matrix* cmatrix = oap::cuda::NewDeviceMatrixDeviceRef (llayer->m_inputs);
    oap::cuda::CopyDeviceMatrixToDeviceMatrix (cmatrix, llayer->m_inputs);
    return cmatrix;
  }
  else if (argsType == Type::DEVICE)
  {
    return llayer->m_inputs;
  }
  return nullptr;
}

math::Matrix* Network::getHostOutputs () const
{
  Layer* llayer = m_layers.back();
  auto minfo = oap::cuda::GetMatrixInfo (llayer->m_inputs);

  math::Matrix* matrix = oap::host::NewMatrix (minfo);
  return getOutputs (matrix, Type::HOST);
}

void Network::forwardPropagation ()
{
  if (m_layers.size() < 2)
  {
    throw std::runtime_error ("m_layers.size() is lower than 2");
  }

  Layer* previous = nullptr;
  Layer* current = m_layers[0];

  for (size_t idx = 1; idx < m_layers.size(); ++idx)
  {
    previous = current;
    current = m_layers[idx];
    m_cuApi.dotProduct (current->m_sums, previous->m_weights, previous->m_inputs);
    activateFunc (current->m_inputs, current->m_sums, current->getActivation ());
  }
}

void Network::calculateErrors (oap::ErrorType errorType)
{
  debugAssert (m_expectedDeviceOutputs != nullptr);

  size_t idx = m_layers.size () - 1;
  Layer* next = nullptr;
  Layer* current = m_layers[idx];

  if (errorType == oap::ErrorType::CROSS_ENTROPY)
  {
    m_cuApi.crossEntropy (current->m_errors, m_expectedDeviceOutputs, current->m_inputs);
  }
  else
  {
    m_cuApi.substract (current->m_errors, m_expectedDeviceOutputs, current->m_inputs);
    //m_cuApi.hadamardProduct (current->m_errors, current->m_errors, current->m_errors);
    //m_cuApi.multiplyReConstant (current->m_errors, current->m_errors, 0.5);
  }
}

math::Matrix* Network::getErrors (Type type) const
{
  Layer* last = m_layers.back();

  if (type == Network::DEVICE)
  {
    return last->m_errors;
  }
  else if (type == Network::HOST)
  {
    math::Matrix* matrix = oap::host::NewReMatrix (1, last->getNeuronsCount());
    oap::cuda::CopyDeviceMatrixToHostMatrix (matrix, last->m_errors);
    return matrix;
  }
  else if (type == Network::DEVICE_COPY)
  {
    math::Matrix* matrix = oap::cuda::NewDeviceReMatrix (1, last->getNeuronsCount());
    oap::cuda::CopyDeviceMatrixToDeviceMatrix (matrix, last->m_errors);
    return matrix;
  }

  return nullptr;
}

floatt Network::calculateMSE ()
{
  floatt eValue = 0;
  m_cuApi.magnitude2 (eValue, m_layers.back()->m_errors);
  eValue = eValue / m_layers.back()->getNeuronsCount ();
  return eValue;
}

floatt Network::calculateRMSE ()
{
  return sqrt (calculateMSE());
}

floatt Network::calculateSum ()
{
  floatt eValue = 0;
  m_cuApi.sum (eValue, m_layers.back()->m_errors);
  return eValue;
}

floatt Network::calculateSumMean ()
{
  return calculateSum() / m_layers.back()->getNeuronsCount ();
}

floatt Network::calculateCrossEntropy ()
{       
  return (- calculateSum()) / m_layers.back()->getNeuronsCount ();
}

floatt Network::calculateError (oap::ErrorType errorType)
{
  std::map<oap::ErrorType, std::function<floatt()>> errorsFunctions =
  {
    {oap::ErrorType::MEAN_SQUARE_ERROR, std::bind (&Network::calculateMSE, this)},
    {oap::ErrorType::ROOT_MEAN_SQUARE_ERROR, std::bind (&Network::calculateRMSE, this)},
    {oap::ErrorType::SUM, std::bind (&Network::calculateSum, this)},
    {oap::ErrorType::MEAN_OF_SUM, std::bind (&Network::calculateSumMean, this)},
    {oap::ErrorType::CROSS_ENTROPY, std::bind (&Network::calculateCrossEntropy, this)}
  };

  return errorsFunctions [errorType]();
}

void Network::backwardPropagation ()
{
  size_t idx = m_layers.size () - 1;
  Layer* next = nullptr;
  Layer* current = m_layers[idx];

  do
  {
    next = current;
    --idx;
    current = m_layers[idx];

    m_cuApi.transpose (current->m_tweights, current->m_weights);
    m_cuApi.dotProduct (current->m_errors, current->m_tweights, next->m_errors);
  }
  while (idx > 0);
  updateWeights();
}

bool Network::train (math::Matrix* inputs, math::Matrix* expectedOutputs, Type argsType, oap::ErrorType errorType)
{
  Layer* layer = m_layers.front();

  setExpected (expectedOutputs, argsType);
  setInputs (inputs, argsType);

  forwardPropagation ();
  calculateErrors (errorType);
  if(!shouldContinue (errorType))
  {
    return false;
  }

  backwardPropagation ();

  ++m_step;
  return true;
}

void Network::setController(Network::IController* icontroller)
{
  m_icontroller = icontroller;
}

void Network::setHostWeights (math::Matrix* weights, size_t layerIndex)
{
  Layer* layer = m_layers[layerIndex];
  layer->setHostWeights (weights);
}

void Network::getHostWeights (math::Matrix* weights, size_t layerIndex)
{
  Layer* layer = getLayer (layerIndex);
  oap::cuda::CopyDeviceMatrixToHostMatrix (weights, layer->m_weights);
}

void Network::setDeviceWeights (math::Matrix* weights, size_t layerIndex)
{
  Layer* layer = m_layers[layerIndex];
  layer->setDeviceWeights (weights);
}

void Network::setLearningRate (floatt lr)
{
  m_learningRate = lr;
}

floatt Network::getLearningRate () const
{
  return m_learningRate;
}

void Network::save (utils::ByteBuffer& buffer) const
{
  buffer.push_back (m_learningRate);
  buffer.push_back (m_step);

  LC_t layersCount = m_layers.size ();
  buffer.push_back (layersCount);

  for (const auto& layer : m_layers)
  {
    layer->save (buffer);
  }
}

Network* Network::load (const utils::ByteBuffer& buffer)
{
  Network* network = new Network ();

  decltype(Network::m_learningRate) learningRate = buffer.template read<decltype(Network::m_learningRate)> ();
  decltype(Network::m_step) step = buffer.template read<decltype(Network::m_step)> ();

  network->setLearningRate (learningRate);
  network->m_step = step;

  LC_t layersCount = buffer.template read<LC_t> ();

  for (LC_t idx = 0; idx < layersCount; ++idx)
  {
    Layer* layer = Layer::load (buffer);
    network->addLayer (layer);
  }

  return network;
}

Layer* Network::getLayer(size_t layerIndex) const
{
  if (layerIndex >= m_layers.size())
  {
    throw std::runtime_error ("Layer index out of scope.");
  }

  return m_layers[layerIndex];
}

void Network::destroyLayers()
{
  for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
  {
    delete *it;
  }
  m_layers.clear();
}

void Network::updateWeights()
{
  debugFunc();
  Layer* current = nullptr;
  Layer* next = m_layers[0];

  for (size_t idx = 1; idx < m_layers.size(); ++idx)
  {
    current = next;
    next = m_layers[idx];

    transpose (current->m_tinputs, current->m_inputs);
    tensorProduct (current->m_weights1, current->m_tinputs, next->m_errors);
    multiplyReConstant (current->m_weights1, current->m_weights1, m_learningRate);
    derivativeFunc (next->m_sums, next->m_sums, next->getActivation ());
    hadamardProductVec (current->m_weights2, current->m_weights1, next->m_sums);
    add (current->m_weights, current->m_weights, current->m_weights2);
    logInfo ("m_weights %p %s", current, oap::cuda::to_string(current->m_weights).c_str());
  }
}

void Network::setHostInputs (math::Matrix* inputs, size_t layerIndex)
{
  Layer* layer = getLayer(layerIndex);
  oap::cuda::CopyHostMatrixToDeviceMatrix (layer->m_inputs, inputs);
}

bool Network::shouldContinue (oap::ErrorType errorType)
{
  if (m_icontroller != nullptr && m_icontroller->shouldCalculateError(m_step))
  {
    Layer* llayer = m_layers.back();
    floatt eValue = calculateError (errorType);;

    m_icontroller->setError (eValue, errorType);

    if(!m_icontroller->shouldContinue())
    {
      return false;
    }
  }

  return true;
}

bool Network::operator== (const Network& network) const
{
  if (&network == this)
  {
    return true;
  }

  if (getLayersCount () != network.getLayersCount ())
  {
    return false;
  }

  for (size_t idx = 0; idx < getLayersCount (); ++idx)
  {
    Layer* layer = getLayer (idx);
    Layer* layer1 = network.getLayer (idx);
    if ((*layer) != (*layer1))
    {
      return false;
    }
  }

  return true;
}

void Network::printLayersWeights ()
{
  for (size_t idx = 0; idx < getLayersCount(); ++idx)
  {
    getLayer(idx)->printHostWeights (true);
  }
}

bool Network::operator!= (const Network& network) const
{
  return !(*this == network);
}
