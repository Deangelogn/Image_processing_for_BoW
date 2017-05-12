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
    int numIt = (int)((end-start)/step);
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

FeatureMatrix *getGranulometryFromPile(ImagePile *imgPile, float begin, float end, float step){
    int FVsize = (int)round(end - begin)/step;
    float currentIt = begin;
    FeatureMatrix *fm = createFeaturematrix(FVsize,imgPile->pileSize);
    float *granulometryFeatures;
    for (int i = 0; i < imgPile->pileSize; ++i) {
        granulometryFeatures = getGranulometry(&imgPile->img[i], begin,end,step);
        setFVinFM(&fm->fv[i],granulometryFeatures);
    }
    return fm;
}
