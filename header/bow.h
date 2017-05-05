//
// Created by eu on 27/04/17.
//

#include "morphology.h"

#ifndef MO815_BOW_BOW_H
#define MO815_BOW_BOW_H

FeatureVector * getBowFeatures(Image *imgPile, int numImg, FeatureVector *Dict , int numWords);
int findVisualWords(FeatureVector *aword, FeatureVector *matWords, int numWords);
float classifier(char *trainDir, char *testDir, FeatureVector *dic, int dictonarySize,
           FeatureVector *kel, int kSize, Image* pileImg, int pileSize);
char * getImgeAfter(char *srcDir, int aft);

#endif //MO815_BOW_BOW_H
