#include <stdio.h>
#include <stdlib.h>
#include "header/image.h"
#include "header/histogram.h"
#include "header/alg.h"
#include "header/myMath.h"
#include "header/adjRelation.h"
#include "header/morphology.h"
#include "header/stringManipulation.h"
#include "header/direct.h"

#include <dirent.h>
int main(int   argc, char *argv[])
{
    int numWords = 3, it = 10000, run=1;
    int numImg=0;
    char filename[100];
    char path[]="/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/classes";
    Image rgbImg, *imgPile;


    //create random training and test datasets from coil database
    //uncomment this part if you wish to generate a dataset
    /*int *pInt = randInt(10,5), ID = 1;
    float per = 0.84;
    char *srcDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/classes/";
    char *tarDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/";
    createDatasetFrom(pInt,5, srcDir, tarDir, ID, per);
    saveDatasetInfo(pInt,5,72,ID,per,"/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/");*/

    /*int pileSize=0;
    AdjRelation adjRelation;
    readImage("/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/obj6__0.ppm", &rgbImg[0]);
    readImage("/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/obj7__0.ppm", &rgbImg[1]);
    readImage("/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/obj8__0.ppm", &rgbImg[2]);
    imgPile = cropImage(&rgbImg, 3, 64,64, &pileSize);

    Histogram histPile[pileSize];
    FeatureVector fv[pileSize];
    int bins[3]={2,2,2};
    for (int i = 0; i < pileSize; ++i) {
        getRGBHistogram(&imgPile[i],&histPile[i], &bins);
    }

    float begin=0, end=2, step=1;
    int numFeatures = (int)((end-begin)/step)+1;
    for (int i = 0; i < pileSize; ++i) {
        float *granulometryFeatures = getGranulometry(&imgPile[i], begin, end,step);
        vecMerge (histPile[i].normBins, granulometryFeatures, histPile[i].numBins, numFeatures, &fv[i]);
    }

    float featMat[pileSize*fv->size];
    fv2array(&fv, &featMat, pileSize);

    char dir[100];
    sprintf(dir, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/dic_%d.txt", run);

    //kmeans(featMat, pileSize, numWords, fv->size, it, dir);

    FeatureVector fv2[numWords];
    getDictonary(dir, &fv2);
    float wordMat[numWords*fv2->size];
    fv2array(&fv2, &wordMat, numWords);

    //fv, pileSize, vecSize, 3, hist

    for (int i = 0; i < pileSize; ++i) {
        destroyImage(&imgPile[i]);
        destroyHistogram(&histPile[i]);
        destroyFeatureVector(&fv[i]);
    }

    for (int j = 0; j < numWords; ++j) {
        destroyFeatureVector(&fv2[j]);
    }*/
    return 0;
}
