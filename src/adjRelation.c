//
// Created by eu on 17/04/17.
//

#include "../header/image.h"
#include "../header/adjRelation.h"
#include "../header/myMath.h"
#include <stdlib.h>
#include <stdio.h>


float * getAdjRelationValues(Image *img, AdjRelation *adjR, int x, int y, int ch){
    float *v = malloc(adjR->numAdj*sizeof(float));
    int row, col;
    for (int i = 0; i < adjR->numAdj; ++i) {
        //row = (x+ adjR->dx[i])*img->numCols ;
        //col = y + adjR->dy[i];
        row = x+adjR->dx[i];
        col = y+adjR->dy[i];

        if( (row<0) || (row>=img->numRows) || (col<0) || (col>=img->numCols) ){
            v[i] = 0.0;
        }
        else{
            v[i] = img->ch[ch].vecIntensity[row*img->numCols+col];
        }
    }
    return v;
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

AdjRelation * createAdjRelation(int *coordX, int* coordY, int numElements){
    AdjRelation *adjRelation = malloc(sizeof(AdjRelation));
    adjRelation->dx = malloc(numElements*sizeof(int));
    adjRelation->dy = malloc(numElements*sizeof(int));
    adjRelation->numAdj = numElements;
    for (int j = 0; j < numElements; ++j) {
        adjRelation->dx[j] = coordX[j];
        adjRelation->dy[j] = coordY[j];
    }
    return adjRelation;
}

AdjRelation * createSquareAdjRelation(int size){
    AdjRelation *adjRelation = malloc(sizeof(AdjRelation));
    int numElements = size*size;
    adjRelation->numAdj=numElements;
    adjRelation->dx = malloc(numElements*sizeof(int));
    adjRelation->dy = malloc(numElements*sizeof(int));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            adjRelation->dx[i*size + j] = i - (size/2);
            adjRelation->dy[i*size + j] = j - (size/2);
        }
    }
    return adjRelation;
}

void printAdjRelation(AdjRelation *adjRelation){
    for (int i = 0; i < adjRelation->numAdj; ++i) {
        printf("%d, %d\n", adjRelation->dx[i], adjRelation->dy[i]);
    }
}

Kernel * createKernel(int size, float * w){
    struct Kernel *kernel =  (struct Kernel *)malloc(sizeof(struct Kernel));
    kernel->adjRelation = (struct AdjRelation *)malloc(sizeof(struct AdjRelation));
    kernel->adjRelation = createSquareAdjRelation(size);
    kernel->w = (float *)malloc(kernel->adjRelation->numAdj*sizeof(float));
    for (int i = 0; i < kernel->adjRelation->numAdj; ++i) {
        kernel->w[i] = w[i];
    }
    return kernel;
}

void printKernel(Kernel *kernel){
    for (int i = 0; i < kernel->adjRelation->numAdj; ++i) {
        printf("%f ", kernel->w[i]);
    }
}

void destroyAdjRelation(AdjRelation *adjR){
    free(adjR->dx);
    free(adjR->dy);
}

void destroyKernel(Kernel *kernel){
    free(kernel->adjRelation->dx);
    free(kernel->adjRelation->dy);
}

