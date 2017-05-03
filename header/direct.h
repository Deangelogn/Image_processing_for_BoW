//
// Created by eu on 28/04/17.
//

#ifndef MO815_BOW_DIRECT_H
#define MO815_BOW_DIRECT_H

void createDir(char dir[]);
int numFiles(char dir[]);
void createDataSet(char sourceDir[], char targetDir[], int ID, float percentTrainSample);

#endif //MO815_BOW_DIRECT_H
