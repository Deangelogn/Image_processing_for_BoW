//
// Created by eu on 19/06/17.
//

#include "../header/direct.h"
#include <stdio.h>
#include <stdlib.h>

int step1(int   argc, char *argv[])
{
    char * fileDir = "/home/eu/Desktop/Image_processing_for_BoW/data/Emotions";
    char * datasetDir = "/home/eu/Desktop/Data/Emotions/";

    createDatasetFileFromData(datasetDir,fileDir,0.75, 0);

    return 0;
}