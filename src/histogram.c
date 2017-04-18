//
// Created by eu on 13/04/17.
//

#include "../header/histogram.h"
#include <stdlib.h>
#include <stdio.h>

//Start bins 0 values and create the bin windows.
void initBins(Histogram *hist, int *binsPerChannel, int numChannels){

    hist->numBins = 1;
    hist->binWindow = malloc(numChannels*sizeof(float));

    for (int i = 0; i < numChannels; ++i) {
        hist->numBins *= binsPerChannel[i];
        hist->binWindow[i] = (float)256/binsPerChannel[i];
    }

    hist->bins = malloc(hist->numBins*sizeof(int));
    hist->normBins = malloc(hist->numBins*sizeof(float));

    // set to 0 the values of all bins
    for (int i = 0; i <hist->numBins ; ++i) {
        hist->bins[i] = 0;
        hist->normBins[i] = 0.0;
    }
}

void getGrayHistogram(Image *img,Histogram *hist, int numBins){
    initBins(hist, &numBins, img->nChannels);
    for (int i = 0; i < img->numPixels; ++i) {
        hist->bins[img->ch[0].vecIntensity[i]]++;
    }
    for (int j = 0; j < hist->numBins; ++j) {
        hist->normBins[j] = (float)hist->bins[j]/img->numPixels;
    }
}

void getRGBHistogram(Image *img, Histogram *hist,int *binsPerChannel){
    initBins(hist, binsPerChannel, img->nChannels);
    int R,G,B;
    for (int i = 0; i < img->numPixels; ++i) {
        R = img->ch[0].vecIntensity[i]/hist->binWindow[0];
        G = img->ch[1].vecIntensity[i]/hist->binWindow[1];
        B = img->ch[2].vecIntensity[i]/hist->binWindow[2];

        hist->bins[R+(G*binsPerChannel[0])+(B*binsPerChannel[0]*binsPerChannel[1])]++;
    }
}

void destroyHistogram(Histogram *hist){
    free(hist->bins);
    free(hist->normBins);
    free(hist->binWindow);
}