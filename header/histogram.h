//
// Created by eu on 13/04/17.
//

#include "image.h"

#ifndef CLION_HISTOGRAM_H
#define CLION_HISTOGRAM_H

typedef struct Histogram{
    int numBins;
    int *bins;
    float *normBins;
    float *binWindow;


}Histogram;

void getGrayHistogram(Image *img,Histogram *hist, int numBins);
void getRGBHistogram(Image *img, Histogram *hist,int *binsPerChannel);
void initBins(Histogram *hist, int *binsPerChannel, int numChannels);
void destroyHistogram(Histogram *hist);

#endif //CLION_HISTOGRAM_H