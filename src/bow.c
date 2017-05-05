//
// Created by eu on 27/04/17.
//

#include <stdlib.h>
#include <printf.h>
#include "../header/morphology.h"
#include "../header/histogram.h"
#include "../header/myMath.h"
#include "../header/alg.h"
#include "../header/stringManipulation.h"
#include <stdio.h>
#include <dirent.h>
#include <memory.h>
#include "../header/bow.h"

FeatureVector * getBowFeatures(Image *imgPile, int numImg, FeatureVector *Dict , int numWords){
    FeatureVector *fvout = malloc(numImg*sizeof(FeatureVector));
    Image *cropImg;
    int pileSize;
    int bins[3]={2,2,2};
    float begin=1, end=3, step=1;

    for (int i = 0; i < numImg; ++i) {
        cropImg = cropImage(&imgPile[i],1,64,64,&pileSize);

        //hist
        Histogram histPile[pileSize];
        for (int j = 0; j < pileSize; ++j) {
            getRGBHistogram(&cropImg[j],&histPile[j], &bins);
        }

        //granulo
        FeatureVector fv[pileSize];
        int numFeatures = (int)((end-begin)/step)+1;
        for (int j = 0; j < pileSize; ++j) {
            float *granulometryFeatures = getGranulometry(&cropImg[j], begin, end,step);
            vecMerge (histPile[j].normBins, granulometryFeatures, histPile[j].numBins, numFeatures, &fv[j]);
        }

        // closest word
        int idx;
        setFeatureVector(&fvout[i],numWords);
        for (int j = 0; j < pileSize; ++j) {
            fvout[i].features[j] = 0;
        }

        for (int j = 0; j < pileSize; ++j) {
             idx = closestVec(&fv[j], Dict, numWords);
             fvout[i].features[idx] += 1;
        }

        //norm hist word

        for (int j = 0; j < pileSize; ++j) {
            fvout[i].features[j] = fvout[i].features[j]/(float)pileSize;
            if(fvout[i].features[j]>1){
                printf("aqui %d\n",i);
            }
            if(fvout[i].features[j]<0){
                printf("aqui2 %d\n", i);
            }
        }

    }

    return fvout;
}

int findVisualWords(FeatureVector *aword, FeatureVector *matWords, int numWords){
    return closestVec(aword,matWords,numWords);
}

float classifier(char *trainDir, char *testDir, FeatureVector *dic, int dictonarySize,
                  FeatureVector *kel, int kSize, Image* pileImg, int pileSize){
    DIR *dir;
    struct dirent *ent;
    int rClass, cClass,cont=0, right=0;
    Image img;


    dir = opendir(testDir);
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){

                char *imgFullPath = strAppend(testDir,ent->d_name);
                rClass = getNumber(ent->d_name);
                readImage(imgFullPath, &img);

                FeatureVector *hwImg = getBowFeatures(&img, 1, dic , dictonarySize);
                int idxK = findVisualWords(hwImg,kel,kSize);
                int idxC = findVisualWords(&kel[idxK],pileImg, pileSize);
                char *imgName = getImgeAfter(trainDir, idxC);
                cClass = getNumber(imgName);

                if(rClass == cClass){
                    right++;
                }
                cont++;
                //printf("%d\n", cont);
            }

        }
        closedir (dir);
    }
    else{
        perror ("");
        return EXIT_FAILURE;
    }
    printf("%d, %d\n",right, cont);
    return ((float)right/(float)cont);
}

char * getImgeAfter(char *srcDir, int aft){
    DIR *dir;
    struct dirent *ent;
    dir = opendir(srcDir);
    int cont=0;

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (!((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))) {
                if(cont==aft){
                    char *str = ent->d_name;
                    return str;
                }
                else{
                    cont++;
                }
            }
        }
    }
    return "";
}