//
// Created by eu on 12/05/17.

#include <stdio.h>
#include <stdlib.h>
#include "../header/myMath.h"
#include "../header/features.h"

void destroyFeatureVector(FeatureVector *fv){
    free(fv->features);
}

void setFeatureVector(FeatureVector *fv, int numElem){
    fv->features = malloc(numElem*sizeof(float));
    fv->numFeatures = numElem;
}

void copyFV(FeatureVector *fv1, FeatureVector *fv2){

    for (int i = 0; i < fv1->numFeatures; ++i) {
        fv2->features[i] = fv1->features[i];
    }

}

double distFV(FeatureVector *fv1, FeatureVector *fv2){
    double result =0;
    for (int i = 0; i < fv1->numFeatures; ++i) {
        result += powD((fv1->features[i] - fv2->features[i]),2);
    }
    return  sqroot(result);
}

void sumFV(FeatureVector * fv1, FeatureVector *fv2){
    for (int i = 0; i < fv1->numFeatures; ++i) {
        fv1->features[i] += fv2->features[i];
        //    printf("v1: %f, v2: %f\n",fv1->features[i], fv2->features[i]);
    }
}

void printFV(FeatureVector * fv){
    for (int i = 0; i < fv->numFeatures; ++i) {
        printf("%f, ",fv->features[i]);
    }
    printf("\n");
}

float maxValueFV(FeatureVector *fv){
    float max = fv->features[0];
    for (int i = 1; i < fv->numFeatures; ++i) {
        if(fv->features[i]>max){
            max = fv->features[i];
        }
    }
    return max;
}

void saveFV(char *filename, FeatureVector *fv, int numFV){

    FILE *f = fopen(filename,"w");
    fprintf(f,"%d %d\n", numFV,fv[0].numFeatures);
    for (int i = 0; i < numFV; ++i) {
        for (int j = 0; j < fv[i].numFeatures; ++j) {
            fprintf(f,"%f ", fv[i].features[j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

FeatureVector *importDictonary(char *path, int *numFV){

    FILE *f = fopen(path,"r");
    int vecSize, nfv;
    fscanf(f,"%d %d\n", &nfv,&vecSize);
    *numFV = nfv;

    FeatureVector *fv = malloc(nfv*sizeof(FeatureVector));
    for (int i = 0; i < nfv; ++i) {
        setFeatureVector(&fv[i],vecSize);
        for (int j = 0; j < fv[i].numFeatures; ++j) {
            fscanf(f,"%f ", &fv[i].features[j]);
        }
    }
    fclose(f);
    return fv;
}

FeatureMatrix *createFeaturematrix(int FVSize,int numFV){
    FeatureMatrix *fm = malloc(sizeof(FeatureMatrix));
    fm->fv = malloc(numFV*sizeof(FeatureVector));
    fm->numFV = numFV;
    for (int i = 0; i < numFV; ++i) {
        fm->fv[i].numFeatures = FVSize;
        fm->fv[i].features = malloc(FVSize*sizeof(float));
    }
    return fm;
}

void setFVinFM(FeatureVector *fv, float *features){
    for (int i = 0; i < fv->numFeatures; ++i) {
        fv->features[i] = features[i];
    }
}

void printFM(FeatureMatrix *fm){
    for (int i = 0; i < fm->numFV; ++i) {
        for (int j = 0; j < fm->fv[i].numFeatures; ++j) {
            printf("%f ",fm->fv[i].features[j]);
        }
        printf("\n");
    }
}
