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
    int numClasses=2;

    //create random training and test datasets from coil database
    //uncomment this part if you wish to generate a dataset
    /*
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

    for (int k = 0; k < numCropImg; ++k) {
        printf("%d: ", k);
        for (int i = 0; i < fv[k].size; ++i) {
            printf(" %f, ", fv[k].features[i]);
        }
        printf("\n");
    }

    //Create dictonary
    FeatureVector *vw;
    vw = kmeans(&fv, numCropImg, numWords, it);

    char filename[100];
    sprintf(filename, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/dic_%d.txt", run);

    saveFV(filename,vw,numWords);*/

    // ----- part 2 -------
    int dictonarySize;
    char fileRead[100];
    sprintf(fileRead, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/dic_%d.txt", run);

    FeatureVector *dic = importDictonary(fileRead, &dictonarySize);

    FeatureVector *histWord = getBowFeatures(imgPile, numImg, dic , dictonarySize);
    /*FeatureVector fv2[numImg];
    for (int i = 0; i < numImg; ++i) {
       setFeatureVector(&fv2[i],histWord[i].size);
        for (int j = 0; j < histWord[i].size; ++j) {
            fv2[i].features[j] = histWord[i].features[j];
        }
    }

    FeatureVector *cl = kmeans(&fv2, numImg, numClasses, it);

    char fileSave2[100];
    sprintf(fileSave2, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/clk_%d.txt", run);
    saveFV(fileSave2,cl,numClasses);*/



    /*for (int i = 0; i < kSize; ++i) {
        int idx = findVisualWords(&kel[i],histWord,numImg);
        printf("%d\n", idx);
    }*/

    // ----- part 3 -------

    int kSize;
    char fileRead2[100];
    sprintf(fileRead2, "/home/eu/Desktop/C_C++/Image_processing_for_BoW/dictonary/clk_%d.txt", run);
    FeatureVector *kel = importDictonary(fileRead2, &kSize);

    char *testDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/test_set3/";

    float acc = classifier(datasetDir, testDir, dic, dictonarySize, kel, kSize, histWord, numImg);
    printf("acc: %f", acc);


    for (int j = 0; j < numImg; ++j){
        destroyImage(&imgPile[j]);
    }
    for (int j = 0; j < numCropImg; ++j){
        destroyImage(&cropImgPile[j]);
    }

    return 0;
}
