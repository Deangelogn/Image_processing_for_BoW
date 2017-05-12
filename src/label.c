//
// Created by eu on 11/05/17.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "../header/label.h"

VecLabel *createVecLabel(int numLabels){
    VecLabel *vl;
    vl->labelId = malloc(numLabels*sizeof(int));
    vl->labelName = malloc(numLabels*sizeof(Label));
    vl->numLabels = numLabels;
    for (int i = 0; i < numLabels; ++i) {
        vl->labelId[i] = i;
    }
    return vl;
}

void destroyVecLabel(VecLabel *vl){
    free(vl->labelId);
    for (int i = 0; i < vl->numLabels; ++i) {
        free(vl->labelName[i].name);
    }
}

void setLabelNameById(VecLabel *vl, char *name, int Id){
    vl->labelName[Id].name = (char*)malloc(strlen(name)*sizeof(char));
    vl->labelName[Id].name = name;
}

void printLabels(VecLabel *vl){
    for (int i = 0; i < vl->numLabels; ++i) {
        printf("%d: %s\n", vl->labelId[i],vl->labelName[i].name);
    }
}
