#include "CuMatrixProcedures.h"
#include "CuMatrixUtils.h"

extern "C" __global__ void CUDAKernel_AddDotProductRe(math::Matrix* output,
                                                   math::Matrix* params0,
                                                   math::Matrix* params1) {
  CUDA_addDotProductRe(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddDotProductIm(math::Matrix* output,
                                                   math::Matrix* params0,
                                                   math::Matrix* params1) {
  CUDA_addDotProductIm(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddDotProduct(math::Matrix* output,
                                                 math::Matrix* params0,
                                                 math::Matrix* params1) {
  CUDA_addDotProduct(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_DotProductRe(math::Matrix* output,
                                                   math::Matrix* params0,
                                                   math::Matrix* params1) {
  CUDA_specific_dotProductRe (output, params0, params1);
}

extern "C" __global__ void CUDAKernel_DotProductIm(math::Matrix* output,
                                                   math::Matrix* params0,
                                                   math::Matrix* params1) {
  CUDA_specific_dotProductIm(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_DotProduct(math::Matrix* output,
                                                 math::Matrix* params0,
                                                 math::Matrix* params1) {
  CUDA_specific_dotProduct (output, params0, params1);
}

extern "C" __global__ void CUDAKernel_DotProductShared (math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDAKernel_dotProductShared (output, params0, params1);
}

extern "C" __global__ void
CUDAKernel_DotProductPeriodic (math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_dotProductPeriodic (output, params0, params1);
}

extern "C" __global__ void
CUDAKernel_DotProductDimPeriodic (math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt* ex)
{
  CUDA_dotProductDimPeriodic (output, params0, params1, ex);
}

extern "C" __global__
void CUDAKernel_DotProductDim(
     math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt* ex)
{
  CUDA_dotProductDim (output, params0, params1, ex);
}

extern "C" __global__ void CUDAKernel_AddRe(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addReMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddIm(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addImMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_Add(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addMatrix(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_SubstractRe(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_substractReMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_SubstractIm(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_substractImMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_SubstractReal(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_substractRealMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddSubstractRe(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addSubstractReMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddSubstractIm(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addSubstractImMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddSubstractReal(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addSubstractRealMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_Substract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_substractMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_AddSubstract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_addSubstractMatrices(output, params0, params1);
}

extern "C" __global__ void CUDAKernel_MultiplyConstantRe(math::Matrix* output,
                                                         math::Matrix* params0,
                                                         floatt re) {
  CUDA_multiplyConstantReMatrix(output, params0, re);
}

extern "C" __global__ void CUDAKernel_MultiplyConstantIm(math::Matrix* output,
                                                         math::Matrix* params0,
                                                         floatt im) {
  CUDA_multiplyConstantImMatrix(output, params0, im);
}

extern "C" __global__ void CUDAKernel_MultiplyConstant(math::Matrix* output,
                                                       math::Matrix* params0,
                                                       floatt re, floatt im) {
  CUDA_multiplyConstantMatrix(output, params0, re, im);
}

extern "C" __global__ void CUDAKernel_MultiplyConstantReal(
    math::Matrix* output, math::Matrix* params0, floatt re, floatt im) {
  CUDA_multiplyConstantRealMatrix(output, params0, re, im);
}

extern "C" __global__ void CUDAKernel_TransposeRe(math::Matrix* output,
                                                  math::Matrix* params0) {
  CUDA_transposeReMatrix(output, params0);
}

extern "C" __global__ void CUDAKernel_TransposeIm(math::Matrix* output,
                                                  math::Matrix* params0) {
  CUDA_transposeImMatrix(output, params0);
}

extern "C" __global__ void CUDAKernel_Transpose(math::Matrix* output,
                                                math::Matrix* params0) {
  CUDA_transposeMatrix(output, params0);
}

extern "C" __global__ void CUDAKernel_TransposeEx(math::Matrix* output,
                                                  math::Matrix* params0,
                                                  MatrixEx* matrixEx) {
  CUDA_transposeMatrixEx(output, params0, *matrixEx);
}

extern "C" __global__ void CUDAKernel_ConjugateTranspose(math::Matrix* output,
                                                math::Matrix* params0) {
  CUDA_conjugateTransposeMatrix(output, params0);
}

extern "C" __global__ void CUDAKernel_Magnitude(floatt* value,
                                                math::Matrix* params0,
                                                floatt* buffer) {
  CUDA_magnitudeOpt(value, params0, buffer);
}

extern "C" __global__ void CUDAKernel_QRGR(
    math::Matrix* output0, math::Matrix* output1, math::Matrix* params0,
    math::Matrix* aux0, math::Matrix* aux1, math::Matrix* aux2,
    math::Matrix* aux3) {
  CUDA_QRGR(output0, output1, params0, aux0, aux1, aux2, aux3);
}

extern "C" __global__ void CUDAKernel_QRHT (math::Matrix* Q, math::Matrix* R, math::Matrix* A, math::Matrix* V, math::Matrix* VT, math::Matrix* P, math::Matrix* VVT)
{
  CudaKernel_QRHT (Q, R, A, V, VT, P, VVT);
}

extern "C" __global__ void CUDAKernel_SetVector (math::Matrix* output, uintt index, math::Matrix* params0, uintt length)
{
  CUDAKernel_setVector(output, index, params0, length);
}

extern "C" __global__ void CUDAKernel_GetVector (math::Matrix* output, uintt length, math::Matrix* params0, uintt index)
{
  CUDAKernel_getVector (output, length, params0, index);
}

extern "C" __global__ void CUDAKernel_SetIdentity(math::Matrix* matrix) {
  CUDA_setIdentityMatrix(matrix);
}

extern "C" __global__ void CUDAKernel_SetDiagonal(math::Matrix* matrix,
                                                  floatt re, floatt im) {
  CUDA_setDiagonalMatrix(matrix, re, im);
}

extern "C" __global__ void CUDAKernel_Invert(math::Matrix* output,
                                             math::Matrix* matrix,
                                             math::Matrix* aux1,
                                             math::Matrix* aux2,
                                             math::Matrix* aux3) {
  CUDA_invertMatrix(output, matrix, aux1, aux2, aux3);
}

extern "C" __global__ void CUDAKernel_CompareRe(floatt* sums,
                                                math::Matrix* matrix1,
                                                math::Matrix* matrix2,
                                                floatt* buffer,
                                                uint bufferLength)
{
  CUDA_compareReMatrix(sums, matrix1, matrix2, buffer);
}

extern "C" __global__ void CUDAKernel_Compare(floatt* sums,
                                              math::Matrix* matrix1,
                                              math::Matrix* matrix2,
                                              floatt* buffer,
                                              uint bufferLength)
{
  CUDA_compare(sums, matrix1, matrix2, buffer);
}

extern "C" __global__ void CUDAKernel_CompareOpt(floatt* sums,
                                                 math::Matrix* matrix1,
                                                 math::Matrix* matrix2)
{
  extern __shared__ floatt sharedBufferFloatt[];
  CUDA_compareOpt(sums, matrix1, matrix2, sharedBufferFloatt);
}

extern "C" __global__ void CUDAKernel_CompareOptVer2(floatt* sums,
                                                     math::Matrix* matrix1,
                                                     math::Matrix* matrix2)
{
  extern __shared__ floatt sharedBufferFloatt[];
  CUDA_compareOptVer2(sums, matrix1, matrix2, sharedBufferFloatt);
}

extern "C" __global__ void CUDAKernel_MagnitudeOpt(floatt* sums,
                                                   math::Matrix* matrix)
{
  extern __shared__ floatt bufferFloat[];
  CUDA_magnitudeOpt(sums, matrix, bufferFloat);
}

extern "C" __global__ void CUDAKernel_MagnitudeOptVer2(floatt* sums,
                                                       math::Matrix* matrix) {
  extern __shared__ floatt bufferFloat[];
  CUDA_magnitudeOptVer2(sums, matrix, bufferFloat);
}

extern "C" __global__ void CUDAKernel_IsUpperTriangular(int* outcome,
                                                        math::Matrix* matrix) {
  int is = CUDA_isUpperTriangular(matrix);
  (*outcome) = is;
}

extern "C" __global__ void CUDAKernel_Sigmoid(math::Matrix* omatrix, math::Matrix* imatrix) {
  CUDA_sigmoid (omatrix, imatrix);
}

extern "C" __global__ void CUDAKernel_DSigmoid (math::Matrix* matrix) {
  CUDA_dsigmoid (matrix, matrix);
}

extern "C" __global__ void CUDAKernel_MultiplyDSigmoid (math::Matrix* omatrix, math::Matrix* matrix) {
  CUDA_multiplyDSigmoid (omatrix, matrix);
}

extern "C" __global__ void CUDAKernel_SigmoidDim (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_sigmoidDim (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_DSigmoidDim (math::Matrix* matrix, uintt* ex) {
  CUDA_dsigmoidDim (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_MultiplyDSigmoidDim (math::Matrix* omatrix, math::Matrix* matrix, uintt* ex) {
  CUDA_multiplyDSigmoidDim (omatrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_SigmoidDimPeriodic (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_sigmoidDimPeriodic (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_DSigmoidDimPeriodic (math::Matrix* matrix, uintt* ex) {
  CUDA_dsigmoidDimPeriodic (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_MultiplyDSigmoidDimPeriodic (math::Matrix* omatrix, math::Matrix* matrix, uintt* ex) {
  CUDA_multiplyDSigmoidDimPeriodic (omatrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_Tanh(math::Matrix* omatrix, math::Matrix* imatrix) {
  CUDA_tanh (omatrix, imatrix);
}

extern "C" __global__ void CUDAKernel_DTanh (math::Matrix* matrix) {
  CUDA_dtanh (matrix, matrix);
}

extern "C" __global__ void CUDAKernel_TanhDim (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_tanhDim (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_DTanhDim (math::Matrix* matrix, uintt* ex) {
  CUDA_dtanhDim (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_TanhDimPeriodic (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_tanhDimPeriodic (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_DTanhDimPeriodic (math::Matrix* matrix, uintt* ex) {
  CUDA_dtanhDimPeriodic (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_Sin(math::Matrix* omatrix, math::Matrix* imatrix) {
  CUDA_sin (omatrix, imatrix);
}

extern "C" __global__ void CUDAKernel_MultiplyDSin (math::Matrix* matrix) {
  CUDA_multiplyDSin (matrix, matrix);
}

extern "C" __global__ void CUDAKernel_DSin (math::Matrix* matrix) {
  CUDA_dsin (matrix, matrix);
}

extern "C" __global__ void CUDAKernel_SinDim (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_sinDim (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_MultiplyDSinDim (math::Matrix* matrix, uintt* ex) {
  CUDA_multiplyDSinDim (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_DSinDim (math::Matrix* matrix, uintt* ex) {
  CUDA_dsinDim (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_SinDimPeriodic (math::Matrix* omatrix, math::Matrix* imatrix, uintt* ex) {
  CUDA_sinDimPeriodic (omatrix, imatrix, ex);
}

extern "C" __global__ void CUDAKernel_MultiplyDSinDimPeriodic (math::Matrix* matrix, uintt* ex) {
  CUDA_multiplyDSinDimPeriodic (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_DSinDimPeriodic (math::Matrix* matrix, uintt* ex) {
  CUDA_dsinDimPeriodic (matrix, matrix, ex);
}

extern "C" __global__ void CUDAKernel_CrossEntropy (math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_crossEntropy (output, params0, params1);
}

extern "C" __global__ void CUDAKernel_CrossEntropyRe (math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_crossEntropyRe (output, params0, params1);
}

extern "C" __global__ void CUDAKernel_SumShared (floatt* rebuffer, floatt* imbuffer, math::Matrix* params0)
{
  CUDA_sumShared (rebuffer, imbuffer, params0);
}

extern "C" __global__ void CUDAKernel_CalculateTriangularH(
    math::Matrix* H, math::Matrix* Q, math::Matrix* R,
    math::Matrix* aux1, math::Matrix* aux2, math::Matrix* aux3,
    math::Matrix* aux4, math::Matrix* aux5, math::Matrix* aux6)
{
  CUDA_calcUTMatrix_GR (H, Q, R, aux1, aux2, aux3, aux4, aux5, aux6);
}

extern "C" __global__ void CUDAKernel_CalculateTriangularHStep(
    math::Matrix* H, math::Matrix* Q, math::Matrix* R,
    math::Matrix* aux1, math::Matrix* aux2, math::Matrix* aux3,
    math::Matrix* aux4, math::Matrix* aux5, math::Matrix* aux6)
{
  CUDA_calcUTMatrixStep_GR (H, Q, R, aux1, aux2, aux3, aux4, aux5, aux6);
}

extern "C" __global__ void
CUDAKernel_TensorProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_tensorProduct (output, params0, params1);
}

extern "C" __global__ void
CUDAKernel_TensorProductDim (math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt* ex)
{
  CUDA_tensorProductDim (output, params0, params1, ex);
}

extern "C" __global__ void
CUDAKernel_HadamardProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_hadamardProduct (output, params0, params1);
}

extern "C" __global__ void
CUDAKernel_PHadamardProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  CUDA_phadamardProduct (output, params0, params1);
}

