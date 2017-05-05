//
// Created by eu on 28/04/17.
//
#include "../header/direct.h"
#include "../header/myMath.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>
#include "../header/myMath.h"
#include "../header/stringManipulation.h"

void createDir(char path[]){

    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }

}

int numFiles(char path[]){
    int cont = 0;
    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            cont++;
        }
        closedir (dir);
    }
    else{
        perror ("");
        return EXIT_FAILURE;
    }
    return  cont-2;
}

void createDataSet(char sourceDir[], char targetDir[], int ID, float percentTrainSample){
    int cont = 0;
    DIR *dir;
    struct dirent *ent;
    int totalSample = numFiles(sourceDir);

    //get percentege of samples
    int trainSample = round(totalSample*percentTrainSample);
    int testSample = totalSample - trainSample;


    //adjusting directory names
    char str1[20];
    char str2[15];
    sprintf(str1, "training_set%d", ID);
    sprintf(str2, "test_set%d", ID);

    char *dir1 = strAppend(targetDir,str1);
    char *dir2 = strAppend(targetDir,str2);

    //creating training and test datasets
    createDir(dir1);
    createDir(dir2);

    dir = opendir(sourceDir);
    srand( time(NULL) );
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){
                if(testSample==0){
                    char *srcFile = strAppend(sourceDir, "/");
                    char *tarFile = strAppend(dir1,"/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    tarFile = strAppend(tarFile,ent->d_name);
                    copyImg(srcFile,tarFile);
                    continue;
                } else if(trainSample==0){
                    char *srcFile = strAppend(sourceDir, "/");
                    char *tarFile = strAppend(dir2,"/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    tarFile = strAppend(tarFile,ent->d_name);
                    copyImg(srcFile,tarFile);
                    continue;
                } else if((float)rand()/(float)(RAND_MAX)>=0.5) {
                    char *srcFile = strAppend(sourceDir, "/");
                    char *tarFile = strAppend(dir1, "/");
                    srcFile = strAppend(srcFile, ent->d_name);
                    tarFile = strAppend(tarFile, ent->d_name);
                    copyImg(srcFile, tarFile);
                    trainSample -= 1;
                    continue;
                } else{
                    char *srcFile = strAppend(sourceDir, "/");
                    char *tarFile = strAppend(dir2,"/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    tarFile = strAppend(tarFile,ent->d_name);
                    copyImg(srcFile,tarFile);
                    testSample -= 1;
                    }
                }
            }
        closedir (dir);
        }
    else{
        perror ("ERROR");
    }

}

void createDatasetFrom(int *pInt, int numClasses, char *srcDir, char *tarDir,int ID, float percentTrainSample){
    char *folderName;
    char *fullPath;
    for (int i = 0; i < numClasses; ++i) {
        folderName = strAppend("obj",num2str(pInt[i],3));
        fullPath = strAppend(srcDir,folderName);
        createDataSet(fullPath, tarDir, ID, percentTrainSample);
    }
}

void saveDatasetInfo(int *pInt,int nClasses, int spc, int ID, float percentTrainSample, char *pathDir){
    char strAux[25], *str;
    sprintf(strAux,"datasetInfo_ID%d.txt", ID);
    str = strAppend(pathDir,strAux);
    FILE *f = fopen(str,"w");

    fprintf(f, "Dataset ID: %d\n",ID);
    fprintf(f, "total samples: %d\n",(int)round(nClasses*spc));
    fprintf(f, "num train samples: %d\n",(int)(nClasses*round(spc*percentTrainSample)));
    fprintf(f, "num test samples: %d\n",(int)(nClasses*round(spc*(1-percentTrainSample))));
    fprintf(f, "Classes: ");
    for (int i = 0; i < nClasses-1; ++i) {
        fprintf(f, "%d, ",pInt[i]);
    }
    fprintf(f, "%d.", pInt[nClasses-1]);
    fclose(f);
}

Image *getImagesFrom(char *path, int *numImg){
    char *imgFullPath;
    *numImg = numFiles(path);
    int nI = *numImg;
    Image img[*numImg], *pileImg;
    pileImg = malloc(nI*sizeof(Image));
    int k=0;

    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){
                imgFullPath = strAppend(path,ent->d_name);
                //printf("%d: %s\n",k, imgFullPath);
                readImage(imgFullPath, &pileImg[k]);
                saveP6Image(&pileImg[k],"/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/teste1.ppm");
                k++;
            }
        }
        closedir (dir);
    }
    else{
        perror ("");
        return EXIT_FAILURE;
    }
    return pileImg;
}
