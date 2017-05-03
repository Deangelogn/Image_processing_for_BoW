//
// Created by eu on 18/04/17.
//

#ifndef CLION_MATH_H
#define CLION_MATH_H

#include "../header/morphology.h"

double round(double num);
double clip(double num, double maxLimit, double minLimit);
double powD(double num, int p);
double maxD(double *vec, int vecSize);
double minD(double *vec, int vecSize);
double maxF(float *vec, int vecSize);
double minF(float *vec, int vecSize);
double sqroot(double square);
double euclidianDistD(double *vec,int vecSize);
double euclidianDistF(float *vec,int vecSize);
float *points2Vec(float *p1, float *p2, int size);
float twoPointsDist(float *p1, float *p2, int size);
void sumVec(float* vecA,float* vecB, int begin, int end);
void printVec(float *vec, int size);
void printVecI(int* vec, int size);
double absf(double num);
double myFloor(double num);
double myCeil(double num);
void *vecMerge(float *vec1, float *vec2, int size1,int size2, FeatureVector *mergeVec);
void fv2array(FeatureVector *fv,float *vecOut, int vecSize);
#endif //CLION_MATH_H
