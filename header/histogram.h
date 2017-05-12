//
// Created by eu on 13/04/17.
//

#include "image.h"
#include "imagePile.h"

#ifndef CLION_HISTOGRAM_H
#define CLION_HISTOGRAM_H

typedef struct Histogram{
    int numBins;
    int *bins;
    float *normBin;
}Histogram;

Histogram* getGrayHistogram(Image *img, int numBins);
Histogram *getRGBHistogram(Image *img,int binsPerChannel);
Histogram * createHistogram(int numBins);
void destroyHistogram(Histogram *hist);
void printHistogram(Histogram *hist);
void setRGBHistogramFromImage(Histogram *hist, Image *img, int numBinsPerChannel);
Histogram *createRGBHistogramFromPile(ImagePile *imgPile, int binsPerChannel);
void createHistogramByPointer(int numBins, Histogram *hist);
void copyHistogram(Histogram *hist1, Histogram *hist2);

#endif //CLION_HISTOGRAM_H