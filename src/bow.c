//
// Created by eu on 27/04/17.
//

#include <stdlib.h>
#include <printf.h>
#include "../header/morphology.h"
#include "../header/histogram.h"
#include "../header/myMath.h"
#include <stdio.h>

FeatureVector * getBowFeatures(Image *imgPile, int numImg, FeatureVector *Dict , int numWords){
    FeatureVector *fvout = malloc(numImg*sizeof(FeatureVector));
    Image *cropImg;
    int pileSize;
    int bins[3]={2,2,2};
    float begin=1, end=3, step=1;

    for (int i = 0; i < numImg; ++i) {
        setFeatureVector(&fvout[i],numWords);
    }
    for (int i = 0; i < numImg; ++i) {
        cropImg = cropImage(&imgPile[i],1,64,64,&pileSize);
        Histogram histPile[pileSize];
        for (int j = 0; j < pileSize; ++j) {
            getRGBHistogram(&cropImg[j],&histPile[j], &bins);
        }
        FeatureVector fv[pileSize];
        int numFeatures = (int)((end-begin)/step)+1;
        for (int j = 0; j < pileSize; ++j) {
            float *granulometryFeatures = getGranulometry(&cropImg[j], begin, end,step);
            vecMerge (histPile[i].normBins, granulometryFeatures, histPile[i].numBins, numFeatures, &fv[i]);
        }

        for (int k = 0; k < pileSize; ++k) {
            for (int j = 0; j < fv[k].size ; ++j) {
                printf("%f, ", fv[k].features[j]);
            }
            printf("\n");
        }
        break;
    }

}