#include "MathOperationsCpu.h"
#include "ThreadData.h"
#include <math.h>
namespace math {

    void MagnitudeOperationCpu::Execute(void* ptr) {
        ThreadData<MagnitudeOperationCpu>* threadData = (ThreadData<MagnitudeOperationCpu>*) ptr;
        floatt output = 0;
        if (threadData->thiz->m_executionPathRe == EXECUTION_NORMAL &&
                threadData->thiz->m_executionPathIm == EXECUTION_NORMAL) {
            for (intt fa = threadData->begins[0]; fa < threadData->ends[0]; fa++) {
                floatt v1 = threadData->params[0]->reValues[fa] *
                        threadData->params[0]->reValues[fa];
                floatt v2 = threadData->params[0]->imValues[fa] *
                        threadData->params[0]->imValues[fa];
                output += v1 + v2;
            }
        } else if (threadData->thiz->m_executionPathRe == EXECUTION_NORMAL) {
            for (intt fa = threadData->begins[0]; fa < threadData->ends[0]; fa++) {
                output += threadData->params[0]->reValues[fa] *
                        threadData->params[0]->reValues[fa];
            }
        } else if (threadData->thiz->m_executionPathIm == EXECUTION_NORMAL) {
            for (intt fa = threadData->begins[0]; fa < threadData->ends[0]; fa++) {
                output += threadData->params[0]->imValues[fa] *
                        threadData->params[0]->imValues[fa];
            }
        }
        threadData->values[0] = output;
    }

    void MagnitudeOperationCpu::execute() {
        uintt* bmap = utils::mapper::allocMap(this->m_threadsCount);
        uintt length = m_matrix->columns * m_matrix->rows;
        uintt threadsCount = utils::mapper::createThreadsMap(bmap, this->m_threadsCount, length);
        ThreadData<MagnitudeOperationCpu>* threads = new ThreadData<MagnitudeOperationCpu>[threadsCount];
        for (intt fa = 0; fa < threadsCount; fa++) {
            threads[fa].params[0] = m_matrix;
            threads[fa].calculateRanges(m_subcolumns, m_subrows, bmap, fa);
            threads[fa].thiz = this;
            threads[fa].thread.setFunction(MagnitudeOperationCpu::Execute, &threads[fa]);
            threads[fa].thread.run((this->m_threadsCount == 1));
        }
        for (uint fa = 0; fa < threadsCount; fa++) {
            threads[fa].thread.yield();
        }
        floatt output = 0.;
        for (uint fa = 0; fa < threadsCount; fa++) {
            output += threads[fa].values[0];
        }
        (*this->m_output1) = sqrt(output);
        utils::mapper::freeMap(bmap);
        delete[] threads;
    }
}

