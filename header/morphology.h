//
// Created by eu on 17/04/17.
//

#ifndef CLION_MORPHOLOGY_H
#define CLION_MORPHOLOGY_H

#include "image.h"
#include "adjRelation.h"

typedef struct FeatureVector{
    float *features;
    int size;
}FeatureVector;

void imDilate(Image *img, Image* dImg, int ch, AdjRelation *adjRel);
void imErode(Image *img, Image *eImg, int ch, AdjRelation *adjRel);
void imOpen(Image *img, Image *opImg, int ch, AdjRelation *adjRel);
void imClose(Image *img, Image *clImg, int ch, AdjRelation *adjRel);
double sumIntensities(Image *img, int ch);
float * getGranulometry(Image *img, float start, float end, float step);
void destroyFeatureVector(FeatureVector *fv);

#endif //CLION_MORPHOLOGY_H
