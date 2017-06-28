//
// Created by eu on 18/04/17.
//
#define MINDIFF 2.25e-308

#include <stdlib.h>
#include <printf.h>
#include "../header/myMath.h"
#include "../header/morphology.h"
#include <stdio.h>
#include <time.h>

double round(double num){
    int integer =  (int)num;
    if(num-integer>0.5){
        return (int)(num+1);
    }
    else{
        return integer;
    }
}

double clip(double num, double minLimit, double maxLimit){
    if(num>maxLimit){
        return maxLimit;
    }
    if(num<minLimit){
        return minLimit;
    }
    return num;
}

double powD(double num, int p){
    if(p==0){
        return 1;
    }
    double result=num;
    for (int i = 0; i < p-1; ++i) {
        result *= num;
    }
    return result;
}

double sqroot(double square) {
    double root=square/3, last, diff=1;
    if (square <= 0) return 0;
    do {
        last = root;
        root = (root + square / root) / 2;
        diff = root - last;
    } while (diff > MINDIFF || diff < -MINDIFF);
    return root;
}

double euclidianDistD(double *vec,int vecSize){
    double dist=0;
    for (int i = 0; i < vecSize; ++i) {
        dist = powD(vec[i],2);
    }
    return sqroot(dist);
}

double euclidianDistF(float *vec,int vecSize){
    double dist=0;
    for (int i = 0; i < vecSize; ++i) {
        dist += powD(vec[i],2);
    }
    return sqroot(dist);
}

double maxD(double *vec, int vecSize){
    double max = vec[0];
    for (int i = 1; i < vecSize; ++i) {
        if(vec[i]>max){
            max = vec[i];
        }
    }
    return max;
}

double minD(double *vec, int vecSize){
    double min = vec[0];
    for (int i = 1; i < vecSize; ++i) {
        if(vec[i]<min){
            min = vec[i];
        }
    }
    return min;
}

double maxF(float *vec, int vecSize){
    double max = vec[0];
    for (int i = 1; i < vecSize; ++i) {
        if(vec[i]>max){
            max = vec[i];
        }
    }
    return max;
}

double minF(float *vec, int vecSize){
    double min = vec[0];
    for (int i = 1; i < vecSize; ++i) {
        if(vec[i]<min){
            min = vec[i];
        }
    }
    return min;
}

float * points2Vec(float *p1, float *p2, int size){
    float *p = malloc(size* sizeof(float));
    for (int i = 0; i < size; ++i) {
        p[i] = p2[i] - p1[i];
    }
    return p;
}

float twoPointsDist(float *p1, float *p2, int size){
    float *p = points2Vec(p1, p2, size);
    return euclidianDistF(p, size);
}

void sumVec(float* vecA,float* vecB, int begin, int end){
    int vecSize = end - begin;
    for (int i = 0; i < vecSize; ++i) {
        vecA[begin+i] += vecB[i];
    }
}

void printVec(float* vec, int size){
    for (int i = 0; i < size; ++i) {
        printf("%f, ", vec[i]);
    }
    printf("\n");
}

void printVecI(int* vec, int size){
    for (int i = 0; i < size; ++i) {
        printf("%d, ", vec[i]);
    }
    printf("\n");
}

double absf(double num){
    if (num>=0){
        return num;
    }
    else{
        return num*(-1);
    }
}

double myFloor(double num){
    return (int)num;
}

double myCeil(double num){
    if((num - (int)num) >0.0){
        return (int)(num+1);
    }
    else{
        return num;
    }
}

void *vecMerge(float *vec1, float *vec2, int size1,int size2, FeatureVector *mergeVec){
    mergeVec->features = malloc((size1+size2)*sizeof(float));
    mergeVec->numFeatures = size1 + size2;
    for (int i = 0; i < size1; ++i) {
        mergeVec->features[i] = vec1[i];
    }
    for (int j = 0; j < size2; ++j) {
        mergeVec->features[size1+j] = vec2[j];
    }

}

void fv2array(FeatureVector *fv,float *vecOut, int vecSize){
    //vecOut = malloc(vecSize*fv->size*sizeof(float));
    for (int i = 0; i < vecSize; ++i) {
        for (int j = 0; j <fv->numFeatures ; ++j) {
            vecOut[i*fv->numFeatures+j] = fv[i].features[j];
        }
    }
}

int *randInt(int maxValue, int numElements){
    int *pInt = malloc(maxValue*sizeof(int));
    int *pOut = malloc(numElements*sizeof(int));
    for (int i = 0; i < maxValue; ++i) {
        pInt[i]=i+1;
    }

    int aux;
    srand( time(NULL) );
    for (int i = 0; i < maxValue; i++) {    // shuffle array
        aux = pInt[i];
        int randIdx = rand() % numElements;
        pInt[i]  = pInt[randIdx];
        pInt[randIdx] = aux;
    }

    for (int i = 0; i < numElements; ++i) {
        pOut[i] = pInt[i];
    }

    return pOut;
}

Image *dotEuclidianDist(Image* img1, Image* img2){

    Image *image = zeroImage(img1->numRows,img1->numCols,img1->nChannels);
    float v1,v2;
    for (int i = 0; i < img1->nChannels; ++i) {
        for (int j = 0; j < img1->numRows; ++j) {
            for (int k = 0; k < img1->numCols; ++k) {
                v1 = img1->ch[i].matIntensity[j][k];
                v2 = img2->ch[i].matIntensity[j][k];
                setVal(image,sqroot(powD(v1,2) + powD(v2,2)),j,k,i);
            }
        }
    }
    return image;
}