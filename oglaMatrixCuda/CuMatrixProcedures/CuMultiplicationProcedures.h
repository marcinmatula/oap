/* 
 * File:   CuMultiplicationProcedures.h
 * Author: mmatula
 *
 * Created on January 8, 2015, 9:16 PM
 */

#ifndef CUMULTIPLICATIONPROCEDURES_H
#define	CUMULTIPLICATIONPROCEDURES_H

extern "C" __device__ __forceinline__ void CUDA_multiplyConstantReMatrix(
    math::Matrix* output,
    math::Matrix* params0, floatt re,
    uintt threadIndexX, uintt threadIndexY) {
    uintt index = threadIndexX + threadIndexY * output->columns;
    output->reValues[index] =
        params0->reValues[index] * re;
    __syncthreads();
}

extern "C" __device__ __forceinline__ void CUDA_multiplyConstantImMatrix(
    math::Matrix* output,
    math::Matrix* params0, floatt im,
    uintt threadIndexX, uintt threadIndexY) {
    uintt index = threadIndexX + threadIndexY * output->columns;
    output->imValues[index] =
        params0->imValues[index] * im;
    __syncthreads();
}

extern "C" __device__ __forceinline__ void CUDA_multiplyConstantRealMatrix(
    math::Matrix* output,
    math::Matrix* params0,
    floatt re, floatt im,
    uintt threadIndexX, uintt threadIndexY) {
    uintt index = threadIndexX + threadIndexY * output->columns;
    output->reValues[index] =
        params0->reValues[index] * re;
    output->imValues[index] =
        params0->imValues[index] * im;
    __syncthreads();
}

extern "C" __device__ __forceinline__ void CUDA_multiplyConstantMatrix(
    math::Matrix* output, math::Matrix* params0,
    floatt re, floatt im,
    uintt threadIndexX, uintt threadIndexY) {
    bool isre = output->reValues != NULL;
    bool isim = output->imValues != NULL;
    if (isre && isim) {
        CUDA_multiplyConstantRealMatrix(output, params0, re, im, threadIndexX, threadIndexY);
    } else if (isre) {
        CUDA_multiplyConstantReMatrix(output, params0, re, threadIndexX, threadIndexY);
    } else if (isim) {
        CUDA_multiplyConstantImMatrix(output, params0, im, threadIndexX, threadIndexY);
    }
}


#endif	/* CUMULTIPLICATIONPROCEDURES_H */

