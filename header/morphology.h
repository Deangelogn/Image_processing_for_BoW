//
// Created by eu on 17/04/17.
//

#ifndef CLION_MORPHOLOGY_H
#define CLION_MORPHOLOGY_H

#include "image.h"
#include "adjRelation.h"

void imDilate(intensityMap *img, intensityMap *out, AdjRelation adjRel);
void imErode(Image *img, Image *out, AdjRelation adjRel);
void imOpen(Image *img, Image *out, AdjRelation adjRel);
void imClose(Image *img, Image *out, AdjRelation adjRel);

#endif //CLION_MORPHOLOGY_H
