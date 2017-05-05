//
// Created by eu on 20/04/17.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../header/myMath.h"
#include "../header/alg.h"


/*FeatureVector* kmeans(FeatureVector *featMat,int numObjs , int numKernels,int it){
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
}*/

float * getSubVec(float *vec, int size, int begin){
    float *p = malloc(size*sizeof(float));
    for (int i = 0; i < size; ++i) {
        p[i] = vec[i+begin];
    }
    return p;
}

int closestVec(FeatureVector *vecFV, FeatureVector *matFV, int matElem){

    int idx=0;
    float *subVec, dist;
    float minDist = (float)distFV(vecFV, &matFV[0]);//twoPointsDist(vec, subVec, vecSize);


    for (int i = 1; i <matElem ; ++i){
        dist = (float)distFV(vecFV, &matFV[i]);

        if (dist < minDist){
            minDist = dist;
            idx = i;
        }
    }
    return idx;
}

void zeroStart(int *p, int vecSize){
    for (int i = 0; i < vecSize; ++i) {
        p[i] = 0;
    }
}

void zeroFV(FeatureVector *fv){
    for (int i = 0; i < fv->size; ++i) {
        fv->features[i] = 0;
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

FeatureVector* kmeans(FeatureVector *featMat,int numObjs, int numKernels,int it){

    FeatureVector *kernel = malloc(numKernels * sizeof(FeatureVector));
    FeatureVector kernelCont, kernelError, kernelNew[numKernels];


    double erGoal = 0.00000000000001;
    int count=0, idx;

    setFeatureVector(&kernelError,numKernels);
    setFeatureVector(&kernelCont,numKernels);

    srand( time(NULL) );
    for (int i = 0; i < numKernels; ++i) {
        kernel[i].features = malloc(featMat[0].size*sizeof(float));
        kernel[i].size = featMat[0].size;
        setFeatureVector(&kernelNew[i],featMat[0].size);
        for (int j = 0; j < kernel[i].size; ++j) {
            kernel[i].features[j] = (float)rand()/(float)(RAND_MAX);
        }
    }


    while(count<=it){
        zeroFV(&kernelCont);
        zeroFV(&kernelError);



        for (int j = 0; j < numKernels; ++j) {
            zeroFV(&kernelNew[j]);
        }

        for (int i = 0; i < numObjs; ++i) {
            int idx = closestVec(&featMat[i], kernel, numKernels);
            kernelCont.features[idx] += 1;
            sumFV(&kernelNew[idx], &featMat[i]);
        }

        for (int j = 0; j < numKernels; ++j) {
            for (int i = 0; i < kernelNew[j].size; ++i) {
                kernelNew[j].features[i] += (kernel[j].features[i]);
                kernelNew[j].features[i] /= (kernelCont.features[j]+1);
            }
            kernelError.features[j] = distFV(&kernel[j], &kernelNew[j]);
        }

        if(maxValueFV(&kernelError)<=erGoal){
            break;
        }

        for (int i = 0; i < numKernels; ++i) {
                copyFV(&kernelNew[i], &kernel[i]) ;
        }

        count++;

    }

    return kernel;
}

