//
// Created by eu on 20/04/17.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../header/myMath.h"
#include "../header/alg.h"

float *getSubVec(float *vec, int size, int begin){
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
    for (int i = 0; i < fv->numFeatures; ++i) {
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
        kernel[i].features = malloc(featMat[0].numFeatures*sizeof(float));
        kernel[i].numFeatures = featMat[0].numFeatures;
        setFeatureVector(&kernelNew[i],featMat[0].numFeatures);
        for (int j = 0; j < kernel[i].numFeatures; ++j) {
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
            for (int i = 0; i < kernelNew[j].numFeatures; ++i) {
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

/*float knn (FeatureMatrix *kernels, int* labels, FeatureVector *input ){

    return 0;
}*/