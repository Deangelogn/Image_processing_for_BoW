//
// Created by eu on 17/04/17.
//

#include "../header/image.h"
#include "../header/adjRelation.h"
#include <stdlib.h>
#include <stdio.h>


unsigned char * getAdjRelationValues(Image *img, AdjRelation *adjR, int x, int y){
    unsigned char * v = malloc(adjR->numAdj*img->nChannels*sizeof(unsigned char));
    int row, col;
    for (int i = 0; i < adjR->numAdj; ++i) {
        for (int j = 0; j < img->nChannels; ++j) {
            row = x*img->numCols + adjR->dx[i];
            col = y + adjR->dy[i];
            if( (row<0) || (row>=img->numRows) || (col<0) || (col>=img->numCols) ){
                v[i*img->nChannels + j] = 0;
            }
            else{
                v[i*img->nChannels + j] = img->ch[j].vecIntensity[row+col];
            }
        }
    }
    return  v;
}

void createCircularAdjacency(AdjRelation *adjR, float r){
    adjR->numAdj=0;
    adjR->dx = malloc(adjR->numAdj*sizeof(int));
    adjR->dy = malloc(adjR->numAdj*sizeof(int));

    for (int i = -r; i <= r; ++i) {
        for (int j = -r; j <= r; ++j) {
            if( (float)((i*i)+(j*j))<=(r*r) ){
                adjR->numAdj++;
                adjR->dx = realloc(adjR->dx, adjR->numAdj*sizeof(int));
                adjR->dy = realloc(adjR->dy, adjR->numAdj*sizeof(int));
                adjR->dx[adjR->numAdj-1] = i;
                adjR->dy[adjR->numAdj-1] = j;
            }
        }
    }
}

void createLosangeAdjacency(AdjRelation *adjR, int s){
    adjR->numAdj=0;
    adjR->dx = malloc(adjR->numAdj*sizeof(int));
    adjR->dy = malloc(adjR->numAdj*sizeof(int));

    for (int i = -s; i <= s; ++i) {
        for (int j = -s; j <= s; ++j) {
            if( abs(i)+ abs(j)<=s ){
                adjR->numAdj++;
                adjR->dx = realloc(adjR->dx, adjR->numAdj*sizeof(int));
                adjR->dy = realloc(adjR->dy, adjR->numAdj*sizeof(int));
                adjR->dx[adjR->numAdj-1] = i;
                adjR->dy[adjR->numAdj-1] = j;
            }
        }
    }
}

void createCrossAdjacency(AdjRelation *adjR, int s){
    adjR->numAdj=0;
    adjR->dx = malloc(adjR->numAdj*sizeof(int));
    adjR->dy = malloc(adjR->numAdj*sizeof(int));

    for (int i = -s; i <= s; ++i) {
        for (int j = -s; j <= s; ++j) {
            if((i==0)||(j==0)){
                adjR->numAdj++;
                adjR->dx = realloc(adjR->dx, adjR->numAdj*sizeof(int));
                adjR->dy = realloc(adjR->dy, adjR->numAdj*sizeof(int));
                adjR->dx[adjR->numAdj-1] = i;
                adjR->dy[adjR->numAdj-1] = j;
            }
        }
    }
}

void setAdjRelation(AdjRelation *adjR, int numberOfAdjacencies, int *xVec, int *yVec){
    adjR->numAdj=numberOfAdjacencies;
    adjR->dx = malloc(adjR->numAdj*sizeof(int));
    adjR->dy = malloc(adjR->numAdj*sizeof(int));
    for (int i = 0; i < numberOfAdjacencies; ++i) {
        adjR->dx[i] = xVec[i];
        adjR->dy[i] = yVec[i];
    }
}
void destroyAdjRelation(AdjRelation *adjR){
    free(adjR->dx);
    free(adjR->dy);
}