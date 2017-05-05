//
// Created by eu on 17/04/17.
//

#include <stdlib.h>
#include <printf.h>
#include "../header/image.h"
#include "../header/adjRelation.h"
#include "../header/myMath.h"
#include "../header/morphology.h"
#include <stdio.h>

void imDilate(Image *img, Image* dImg, int ch, AdjRelation *adjRel){
    float *adjValues, max;
    setImage(dImg,1,img->numRows,img->numCols, img->numRows);

    for (int i = 0; i < img->numRows; ++i) {
        for (int j = 0; j < img->numCols; ++j) {
            adjValues = getAdjRelationValues(img,adjRel, i,j,ch);
            max = maxF(adjValues,adjRel->numAdj);
            dImg->ch[ch].vecIntensity[i*img->numCols+j]=max;
            dImg->ch[ch].matIntensity[i][j] = max;
        }
    }
}
void imErode(Image *img, Image *eImg, int ch, AdjRelation *adjRel){
    float *adjValues, min;
    setImage(eImg,1,img->numRows,img->numCols, img->numRows);

    for (int i = 0; i < img->numRows; ++i) {
        for (int j = 0; j < img->numCols; ++j) {
            adjValues = getAdjRelationValues(img,adjRel, i,j,ch);
            min = minF(adjValues,adjRel->numAdj);
            eImg->ch[ch].vecIntensity[i*img->numCols+j]=min;
            eImg->ch[ch].matIntensity[i][j] = min;
        }
    }
}
void imOpen(Image *img, Image *opImg, int ch, AdjRelation *adjRel){
    Image eImg;

    setImage(&eImg,1,img->numRows,img->numCols, img->numRows);
    imErode(img,&eImg,ch, adjRel);

    setImage(opImg,1,img->numRows,img->numCols, img->numRows);
    imDilate(&eImg,opImg,ch, adjRel);

}
void imClose(Image *img, Image *clImg, int ch, AdjRelation *adjRel){
    Image dImg;
    setImage(&dImg,1,img->numRows,img->numCols, img->numRows);
    imDilate(img,&dImg,ch, adjRel);

    setImage(clImg,1,img->numRows,img->numCols, img->numRows);
    imDilate(&dImg,clImg,ch, adjRel);
}

float * getGranulometry(Image *img, float start, float end, float step){
    int numIt = (int)((end-start)/step)+1;
    float currentStep = start;
    float *features = malloc(numIt*sizeof(float));
    AdjRelation adjRel;
    Image ycbcrImg, granImg;
    rgb2ycbcr(img, &ycbcrImg);

    for (int i = 0; i < numIt; ++i) {
        createLosangeAdjacency(&adjRel, (int)currentStep);
        imOpen(&ycbcrImg, &granImg, 0, &adjRel);
        features[i] = 1-(sumIntensities(&granImg,0)/sumIntensities(&ycbcrImg,0));
        currentStep += step;
    }
    return features;

}

double sumIntensities(Image *img, int ch){
    double sum=0;
    for (int i = 0; i < img->numPixels; ++i) {
        sum += img->ch[ch].vecIntensity[i];
    }
    return sum;
}

void destroyFeatureVector(FeatureVector *fv){
    free(fv->features);
}

void setFeatureVector(FeatureVector *fv, int numElem){
    fv->features = malloc(numElem*sizeof(float));
    fv->size = numElem;
}

void copyFV(FeatureVector *fv1, FeatureVector *fv2){

    for (int i = 0; i < fv1->size; ++i) {
        fv2->features[i] = fv1->features[i];
    }

}

double distFV(FeatureVector *fv1, FeatureVector *fv2){
    double result =0;
    for (int i = 0; i < fv1->size; ++i) {
        result += powD((fv1->features[i] - fv2->features[i]),2);
    }
    return  sqroot(result);
}

void sumFV(FeatureVector * fv1, FeatureVector *fv2){
    for (int i = 0; i < fv1->size; ++i) {
        fv1->features[i] += fv2->features[i];
    //    printf("v1: %f, v2: %f\n",fv1->features[i], fv2->features[i]);
    }
}

void printFV(FeatureVector * fv){
    for (int i = 0; i < fv->size; ++i) {
        printf("%f, ",fv->features[i]);
    }
    printf("\n");
}

float maxValueFV(FeatureVector *fv){
    float max = fv->features[0];
    for (int i = 1; i < fv->size; ++i) {
        if(fv->features[i]>max){
            max = fv->features[i];
        }
    }
    return max;
}

void saveFV(char *filename, FeatureVector *fv, int numFV){

    FILE *f = fopen(filename,"w");
    fprintf(f,"%d %d\n", numFV,fv[0].size);
    for (int i = 0; i < numFV; ++i) {
        for (int j = 0; j < fv[i].size; ++j) {
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
        for (int j = 0; j < fv[i].size; ++j) {
            fscanf(f,"%f ", &fv[i].features[j]);
        }
    }
    fclose(f);
    return fv;
}