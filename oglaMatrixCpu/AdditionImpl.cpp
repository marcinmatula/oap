#include "MathOperationsCpu.h"        
#include "ThreadData.h"        

namespace math {

    void AdditionOperationCpu::execute() {
        uintt threadsCount = utils::mapper::createThreadsMap(getBMap(),
                this->m_threadsCount,
                m_output->columns,
                m_output->rows);
        ThreadData<AdditionOperationCpu>* threads = m_threadData;
        utils::mapper::ThreadsMap<uintt> map;
        for (uintt fa = 0; fa < threadsCount; fa++) {
            threads[fa].outputs[0] = this->m_output;
            threads[fa].params[0] = this->m_matrix1;
            threads[fa].params[1] = this->m_matrix2;
            threads[fa].thiz = this;
            utils::mapper::getThreadsMap(map, getBMap(), fa);
            threads[fa].calculateRanges(map);
            threads[fa].thread.setFunction(AdditionOperationCpu::Execute, &threads[fa]);
            threads[fa].thread.run((this->m_threadsCount == 1));
        }
        for (uint fa = 0; fa < threadsCount; fa++) {
            threads[fa].thread.yield();
        }
    }

    void AdditionOperationCpu::Execute(void* ptr) {
        ThreadData<AdditionOperationCpu>* threadData =
                (ThreadData<AdditionOperationCpu>*) ptr;
        intt begin = threadData->begins[0];
        intt end = threadData->ends[0];
        intt begin1 = threadData->begins[1];
        intt end1 = threadData->ends[1];
        intt offset = threadData->offset;
        if (threadData->thiz->m_executionPathRe == EXECUTION_NORMAL &&
                threadData->thiz->m_executionPathIm == EXECUTION_NORMAL) {
            for (intt fa = begin; fa < end; fa++) {
                for (intt fb = begin1; fb < end1; fb++) {
                    intt index = fa + offset * fb;
                    threadData->outputs[0]->reValues[index] =
                            threadData->params[0]->reValues[index] +
                            threadData->params[1]->reValues[index];
                    threadData->outputs[0]->imValues[index] =
                            threadData->params[0]->imValues[index] +
                            threadData->params[1]->imValues[index];
                }
            }
        } else if (threadData->thiz->m_executionPathRe == EXECUTION_NORMAL) {
            for (intt fa = begin; fa < end; fa++) {
                for (intt fb = begin1; fb < end1; fb++) {
                    intt index = fa + offset * fb;
                    threadData->outputs[0]->reValues[index] =
                            threadData->params[0]->reValues[index] +
                            threadData->params[1]->reValues[index];
                }
            }
        } else if (threadData->thiz->m_executionPathIm == EXECUTION_NORMAL) {
            for (intt fa = begin; fa < end; fa++) {
                for (intt fb = begin1; fb < end1; fb++) {
                    intt index = fa + offset * fb;
                    threadData->outputs[0]->imValues[index] =
                            threadData->params[0]->imValues[index] +
                            threadData->params[1]->imValues[index];
                }
            }
        }
        if (threadData->thiz->m_executionPathRe == EXECUTION_OUTPUT_TO_ZEROS) {
            for (intt fa = begin; fa < end; fa++) {
                for (intt fb = begin1; fb < end1; fb++) {
                    intt index = fa + offset * fb;
                    threadData->outputs[0]->reValues[index] = 0;
                }
            }
        }
        if (threadData->thiz->m_executionPathIm == EXECUTION_OUTPUT_TO_ZEROS) {
            for (intt fa = begin; fa < end; fa++) {
                for (intt fb = begin1; fb < end1; fb++) {
                    intt index = fa + offset * fb;
                    threadData->outputs[0]->imValues[index] = 0;
                }
            }
        }
    }
}