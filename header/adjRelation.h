//
// Created by eu on 17/04/17.
//

#include "../header/image.h"

#ifndef CLION_ADJRELATION_H
#define CLION_ADJRELATION_H

typedef struct AdjRelation{
    int *dx;
    int *dy;
    int numAdj;
}AdjRelation;

void getAdjRelation(Image *img, AdjRelation *adjR);
void createCircularAdjacency(AdjRelation *adjR, float r);
void destroyAdjRelation(AdjRelation *adjR);
void setAdjRelation(AdjRelation *adjR, int numberOfAdjacencies, int *xVec, int *yVec);
void createLosangeAdjacency(AdjRelation *adjR, int s);
void createCrossAdjacency(AdjRelation *adjR, int s);
float * getAdjRelationValues(Image *img, AdjRelation *adjR, int x, int y, int ch);


#endif //CLION_ADJRELATION_H
