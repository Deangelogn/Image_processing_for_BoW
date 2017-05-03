//
// Created by eu on 20/04/17.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../header/myMath.h"
#include "../header/alg.h"


void kmeans(float *featMat,int numObjs , int numKernels,int vecSize,int it,char outputFile[]){
    int kernelElements = numKernels*vecSize;
    float* kernels = malloc(kernelElements*sizeof(float));
    float* totalSum = malloc(kernelElements*sizeof(float));
    float* errorVec = malloc(kernelElements*sizeof(float));
    double erGoal = 0.0000000000000001;
    int numElements = numObjs*vecSize;
    int count=0, idx, kernelCont[numKernels];

    srand( time(NULL) );
    for (int i = 0; i < kernelElements; ++i) {
        kernels[i] = (float)rand()/(float)(RAND_MAX);
    }

    float *p, kernelVariation;
    while(count<=it){
        zeroStart(&kernelCont, numKernels);
        zeroStartF(totalSum, kernelElements);

        for (int i = 0; i < numElements; i+=vecSize){
            p = getSubVec(featMat,vecSize,i);
            int idx = closestVec(p,kernels,vecSize,numKernels);
            kernelCont[idx]++;
            sumVec(totalSum, p, idx*vecSize, idx*vecSize+vecSize);
        }

        for (int j = 0; j < kernelElements; ++j) {
            kernelVariation = (totalSum[j]+kernels[j])/(float)(kernelCont[j/vecSize]+1);
            errorVec[j] = absf(kernels[j] - kernelVariation);
            kernels[j] = kernelVariation;
        }

        if(maxF(errorVec, kernelElements)<=erGoal){
            break;
        }
        count++;
        //printf("maxE: %f\n", maxF(errorVec, kernelElements));
    }

    printf("it: %d", count);

    if(count>=it){
        printf("Nucleos não convergiram");
    }

    FILE *fp = fopen(outputFile, "wb");
    fprintf(fp,"%d %d\n", numKernels, vecSize);
    for (int k = 0; k <kernelElements ; ++k) {
        fprintf(fp,"%f ", kernels[k]);
        if((k+1)%vecSize==0){
            fprintf(fp,"\n");
        }
    }

    fclose(fp);
}

float * getSubVec(float *vec, int size, int begin){
    float *p = malloc(size*sizeof(float));
    for (int i = 0; i < size; ++i) {
        p[i] = vec[i+begin];
    }
    return p;
}

int closestVec(float *vec, float *matVec, int vecSize, int numVec){

    int k=vecSize, idx=0;
    float *subVec, dist;
    subVec = getSubVec(matVec,vecSize,0);
    float minDist = twoPointsDist(vec, subVec, vecSize);

    for (int i = 1; i < numVec; ++i){
        subVec = getSubVec(matVec,vecSize,k);
        dist = twoPointsDist(vec, subVec, vecSize);
        if (dist < minDist){
            minDist = dist;
            idx = i;
        }
        k += vecSize;
    }
    return idx;
}

void zeroStart(int *p, int vecSize){
    for (int i = 0; i < vecSize; ++i) {
        p[i] = 0;
    }
}

void zeroStartF(float *p, int vecSize){
    for (int i = 0; i < vecSize; ++i) {
        p[i] = 0.0;
    }
}

void getDictonary(char filename[], FeatureVector* fv){
    //featMat = malloc()
    FILE *f = fopen(filename, "rb");
    int numWords, vecSize;
    fscanf(f,"%d %d\n",&numWords, &vecSize);
    float var;
    for (int i = 0; i < numWords; ++i) {
        fv[i].features = malloc(vecSize*sizeof(float));
        for (int j = 0; j < vecSize; ++j) {
            fscanf(f,"%f",&fv[i].features[j]);
        }
    }
}

