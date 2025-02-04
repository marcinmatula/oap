#ifndef MAIN_AP_EXECUTOR_H
#define MAIN_AP_EXECUTOR_H

#include "ArnoldiUtils.h"
#include "IEigenCalculator.h"
#include "DeviceDataLoader.h"

#include "oapDeviceMatrixPtr.h"

#include "Outcome.h"

#include <functional>
#include <vector>

namespace oap
{

class MainAPExecutor final
{
  public:
    MainAPExecutor();
    ~MainAPExecutor();

    void destroy();

    std::shared_ptr<Outcome> run(ArnUtils::Type type = ArnUtils::HOST);

    IEigenCalculator* operator->() const;

  private:
    class EigenCalculator;
    MainAPExecutor(CuHArnoldiCallback* cuhArnolldi, bool deallocateArnoldi);

    static void multiplyMatrixCallback(math::Matrix* m_w, math::Matrix* m_v, oap::CuProceduresApi& cuProceduresApi, void* userData, oap::VecMultiplicationType mt);
    static void multiplySubMatrixCallback(math::Matrix* m_w, math::Matrix* m_v, oap::CuProceduresApi& cuProceduresApi, void* userData, oap::VecMultiplicationType mt);
    static void multiplyVecsCallback(math::Matrix* m_w, math::Matrix* m_v, oap::CuProceduresApi& cuProceduresApi, void* userData, oap::VecMultiplicationType mt);

    static bool sizeCondition (const math::MatrixInfo& info)
    {
      auto size = info.getSize ();
      debugInfo ("info = %s", info.toString().c_str());
      return (size.first <= 800 && size.second <= math::MatrixInfo::Units::MB);
    }

    EigenCalculator* m_eigenCalc;
    CuHArnoldiCallback* m_cuhArnoldi;
    bool m_bDeallocateArnoldi;

  private:
    class EigenCalculator : public IEigenCalculator
    {
      public:
        EigenCalculator (CuHArnoldiCallback* cuhArnoldi) : IEigenCalculator(cuhArnoldi) {}

        ~EigenCalculator() {}

        void setEigenvaluesOutput(floatt* eigenvalues)
        {
          IEigenCalculator::setEigenvaluesOutput (eigenvalues);
        }

        void setEigenvectorsOutput(math::Matrix** eigenvecs, ArnUtils::Type type)
        {
          IEigenCalculator::setEigenvectorsOutput (eigenvecs, type);
        }

        oap::DeviceDataLoader* getDataLoader() const
        {
          return IEigenCalculator::getDataLoader ();
        }
    };
};

}

#endif
