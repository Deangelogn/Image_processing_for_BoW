//
// Created by eu on 28/04/17.
//

#ifndef MO815_BOW_DIRECT_H
#define MO815_BOW_DIRECT_H

#include "image.h"
#include "imagePile.h"

void createDir(char dir[]);
int numFiles(char dir[]);
void createDataSet(char sourceDir[], char targetDir[], int ID, float percentTrainSample);
void createDatasetFrom(int *pInt, int numClasses, char *srcDir, char *tarDir,int ID, float percentTrainSample);
void saveDatasetInfo(int *pInt, int nClasses, int spc, int ID, float percentTrainSample, char *pathDir);
ImagePile *getImagesFrom(char *path);
void createFileDataset(char *srcDir, char *tarDir, int ID, float percentTrainSample);
void createDatasetFileFromData(char sourceDir[], char targetDir[], float percentTrainSample, int ID);

#endif //MO815_BOW_DIRECT_H
