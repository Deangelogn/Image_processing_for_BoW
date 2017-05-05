//
// Created by eu on 28/04/17.
//

#ifndef MO815_BOW_DIRECT_H
#define MO815_BOW_DIRECT_H

#include "image.h"

void createDir(char dir[]);
int numFiles(char dir[]);
void createDataSet(char sourceDir[], char targetDir[], int ID, float percentTrainSample);
void createDatasetFrom(int *pInt, int numClasses, char *srcDir, char *tarDir,int ID, float percentTrainSample);
void saveDatasetInfo(int *pInt, int nClasses, int spc, int ID, float percentTrainSample, char *pathDir);
Image *getImagesFrom(char *path, int *numImg);

#endif //MO815_BOW_DIRECT_H
