//
// Created by eu on 12/05/17.
//

#ifndef MO815_BOW_FEATURES_H
#define MO815_BOW_FEATURES_H

#include "histogram.h"

typedef struct FeatureVector{
    float *features;
    int numFeatures;
}FeatureVector;

typedef struct FeatureMatrix{
    FeatureVector *fv;
    int numFV;
}FeatureMatrix;

void destroyFeatureVector(FeatureVector *fv);
void setFeatureVector(FeatureVector *fv, int numElem);
void copyFV(FeatureVector *fv1, FeatureVector *fv2);
double distFV(FeatureVector *fv1, FeatureVector *fv2);
void sumFV(FeatureVector *fv1, FeatureVector *fv2);
void printFV(FeatureVector * fv);
float maxValueFV(FeatureVector *fv);
void saveFV(char *filename, FeatureVector *fv, int numFV);
FeatureVector *importDictonary(char *path, int *numFV);
FeatureMatrix *createFeaturematrix(int FVSize,int numFV);
void setFVinFM(FeatureVector *fv, float *features);
void printFM(FeatureMatrix *fm);
FeatureMatrix* MergeFMWithHistogram(FeatureMatrix *fm,Histogram *hist);
void saveFM (char *filename, FeatureMatrix *fm);

#endif //MO815_BOW_FEATURES_H
