//
// Created by eu on 13/04/17.
//

#include "../header/histogram.h"
#include "../header/alg.h"
#include "../header/myMath.h"
#include "../header/imagePile.h"
#include <stdlib.h>
#include <stdio.h>

Histogram* getGrayHistogram(Image *img, int numBins){

    Histogram *hist = createHistogram(numBins);
    for (int i = 0; i < img->numPixels; ++i) {
        hist->bins[(int)img->ch[0].vecIntensity[i]]++;
    }
    for (int j = 0; j < hist->numBins; ++j) {
        hist->normBin[j] = (float)hist->bins[j]/img->numPixels;
    }
    return hist;
}

Histogram *getRGBHistogram(Image *img,int binsPerChannel){

    Histogram *hist = createHistogram(powD(binsPerChannel,3));
    float Rwindow = 256/binsPerChannel;
    float Gwindow = 256/binsPerChannel;
    float Bwindow = 256/binsPerChannel;
    int idx;

    int R,G,B;
    for (int i = 0; i < img->numPixels; ++i) {
        R = (int)(img->ch[0].vecIntensity[i]/Rwindow);
        G = (int)(img->ch[1].vecIntensity[i]/Gwindow);
        B = (int)(img->ch[2].vecIntensity[i]/Bwindow);
        hist->bins[R+(G*binsPerChannel)+(B*binsPerChannel*binsPerChannel)]++;
    }

    for (int j = 0; j < hist->numBins; ++j) {
        hist->normBin[j] = (float)hist->bins[j]/img->numPixels;
    }
    return hist;
}

void printHistogram(Histogram *hist){
    printf("%f\n", hist->numBins);

    for (int i = 0; i < hist->numBins; ++i) {
        printf("%d: %f\n", i, hist->normBin[i]);
    }
}

Histogram *createRGBHistogramFromPile(ImagePile *imgPile, int binsPerChannel){
    Histogram * hist = malloc(imgPile->pileSize * sizeof(Histogram));
    Histogram *auxHist;
    int numBins = powD(binsPerChannel,3);

    for (int i = 0; i < imgPile->pileSize; ++i) {
        createHistogramByPointer(numBins,&hist[i]);
        auxHist = getRGBHistogram(&imgPile->img[i],binsPerChannel);
        copyHistogram(auxHist, &hist[i]);
    }
    return hist;
}

Histogram * createHistogram(int numBins){
    Histogram *hist = malloc(sizeof(Histogram));
    hist->bins = malloc(numBins*sizeof(int));
    hist->normBin = malloc(numBins*sizeof(float));
    hist->numBins = numBins;
    for (int i = 0; i < numBins; ++i) {
        hist->bins[i]=0;
        hist->normBin[i]=0;
    }
    return hist;
}

void destroyHistogram(Histogram *hist){
    free(hist->bins);
    free(hist->normBin);
}

void createHistogramByPointer(int numBins, Histogram *hist){
    hist->bins = malloc(numBins*sizeof(int));
    hist->normBin = malloc(numBins*sizeof(float));
    hist->numBins = numBins;
    for (int i = 0; i < numBins; ++i) {
        hist->bins[i]=0;
        hist->normBin[i]=0;
    }
}

void copyHistogram(Histogram *hist1, Histogram *hist2){

    hist2->numBins = hist1->numBins;
    for (int i = 0; i < hist1->numBins; ++i) {
        hist2->bins[i] = hist1->bins[i];
        hist2->normBin[i] = hist1->normBin[i];
    }

}