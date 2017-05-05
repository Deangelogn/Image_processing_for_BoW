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
#include "header/bow.h"

#include <dirent.h>
int main(int   argc, char *argv[])
{
    // ----- part 1 -------
    int numWords = 3, it = 10000, run=1;
    int numImg=0, numCropImg=0;
    Image *imgPile, *cropImgPile;
    int bins[3]={2,2,2}; //histogram bins
    float begin=1, end=3, step=1; //Granulometry parameters


    //create random training and test datasets from coil database
    //uncomment this part if you wish to generate a dataset
    /*int numClasses=2;
    int *pInt = randInt(10,numClasses), ID = 3;
    float per = 0.84;
    char *srcDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/classes/";
    char *tarDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/";
    createDatasetFrom(pInt,numClasses, srcDir, tarDir, ID, per);
    saveDatasetInfo(pInt,numClasses,72,ID,per,"/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/");
    */

    // Create a pile of images
    char *datasetDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/training_set3/";
    imgPile = getImagesFrom(datasetDir,&numImg);
    cropImgPile = cropImage(imgPile, numImg, 64,64, &numCropImg);

    //histogram features
    /*Histogram histPile[numCropImg];
    for (int i = 0; i < numCropImg; ++i) {
        getRGBHistogram(&cropImgPile[i],&histPile[i], &bins);
    }

    //Granulometry features
    FeatureVector fv[numCropImg];
    int numFeatures = (int)((end-begin)/step)+1;
    for (int i = 0; i < numCropImg; ++i) {
        float *granulometryFeatures = getGranulometry(&cropImgPile[i], begin, end,step);
        vecMerge (histPile[i].normBins, granulometryFeatures, histPile[i].numBins, numFeatures, &fv[i]);
    }

    //Create dictonary
    FeatureVector *vw;
    vw = kmeans(&fv, numCropImg, numWords, it);

    char filename[100];
    sprintf(filename, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/dic_%d.txt", run);

    saveFV(filename,vw,numWords);*/

    // ----- part 2 -------
    int dictonarySize;
    char filename[100];
    sprintf(filename, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/dic_%d.txt", run);

    FeatureVector *dic = importDictonary(filename, &dictonarySize);

    getBowFeatures(imgPile, numImg, dic , dictonarySize);


    for (int j = 0; j < numImg; ++j) {
        destroyImage(&imgPile[j]);
    }
    for (int j = 0; j < numCropImg; ++j) {
        destroyImage(&cropImgPile[j]);
    }


    /*
    for (int j = 0; j < numCropImg; ++j) {
        destroyHistogram(&histPile[j]);
        destroyFeatureVector(&fv[j]);
    }*/


    return 0;
}
