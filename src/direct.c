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
#include "../header/imagePile.h"

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

void createFileDataset(char *srcDir, char *tarDir, int ID, float percentTrainSample){

    char *fname1 = strAppend(tarDir,"/traning_set.txt");
    char *fname2 = strAppend(tarDir,"/test_set.txt");

    FILE* f1 = fopen(tarDir,"w");
    FILE* f2 = fopen(tarDir,"w");

    int cont = 0;
    DIR *dir;
    struct dirent *ent;
    int totalSample = numFiles(srcDir);
    int trainSample = round(totalSample*percentTrainSample);
    int testSample = totalSample - trainSample;
    dir = opendir(srcDir);

    srand( time(NULL) );
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){
                if(testSample==0){
                    char *srcFile = strAppend(srcDir, "/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    fprintf(f1,"%s",srcFile);
                    continue;
                } else if(trainSample==0){
                    char *srcFile = strAppend(srcDir, "/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    fprintf(f2,"%s",srcFile);
                    continue;
                } else if((float)rand()/(float)(RAND_MAX)>=0.5) {
                    char *srcFile = strAppend(srcDir, "/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    fprintf(f1,"%s",srcFile);
                    trainSample -= 1;
                    continue;
                } else{
                    char *srcFile = strAppend(srcDir, "/");
                    srcFile = strAppend(srcFile,ent->d_name);
                    fprintf(f2,"%s",srcFile);
                    testSample -= 1;
                    continue;
                }
            }
        }
        closedir (dir);
    }
    else{
        perror ("ERROR");
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

ImagePile *getImagesFrom(char *path){

    ImagePile *imgPile = createImagePile(numFiles(path));
    Image *img;

    char *imgFullPath;
    int k=0;

    DIR *dir;
    struct dirent *ent;

    dir = opendir(path);

    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){
                imgFullPath = strAppend(path,ent->d_name);
                img = readImage(imgFullPath);
                duplicateImg(img,&imgPile->img[k]);
                //saveP6Image(&imgPile->img[k],"/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/teste1.ppm");
                k++;
            }
        }
        closedir (dir);
    }
    else{
        perror ("");
        return EXIT_FAILURE;
    }
    return imgPile;
}

void createDatasetFileFromData(char sourceDir[], char targetDir[], float percentTrainSample, int ID){
    FILE *ftrain = fopen(strAppend(targetDir,"_traning.txt"),"w");
    FILE *ftest = fopen(strAppend(targetDir,"_test.txt"),"w");
    FILE *ftrainLabels = fopen(strAppend(targetDir,"_traningLabels.txt"),"w");
    FILE *ftestLabels = fopen(strAppend(targetDir,"_testLabels.txt"),"w");
    DIR *dir;
    struct dirent *ent;
    dir = opendir(sourceDir);
    srand( time(ID) );
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){
                char *partDir = strAppend(sourceDir, ent->d_name);
                char *fullDir = strAppend(partDir,"/");
                DIR *fileDir;
                struct dirent *files;
                fileDir = opendir(fullDir);

                int totalSample = numFiles(fullDir);
                int trainSample = round(totalSample*percentTrainSample);
                int testSample = totalSample - trainSample;

                if (fileDir != NULL) {
                    while ((files = readdir (fileDir)) != NULL) {
                        if( !((strcmp(files->d_name,".")==0) || (strcmp(files->d_name,"..")==0)) ) {
                            if(testSample==0){
                                char *fullDirFile = strAppend(fullDir, files->d_name);
                                fprintf(ftrain,"%s\n",fullDirFile);
                                fprintf(ftrainLabels,"%s\n",ent->d_name);
                                continue;
                            } else if(trainSample==0){
                                char *fullDirFile = strAppend(fullDir, files->d_name);
                                fprintf(ftest,"%s\n",fullDirFile);
                                fprintf(ftestLabels,"%s\n",ent->d_name);
                                continue;
                            } else if((float)rand()/(float)(RAND_MAX)>=0.5) {
                                char *fullDirFile = strAppend(fullDir, files->d_name);
                                fprintf(ftrain,"%s\n",fullDirFile);
                                fprintf(ftrainLabels,"%s\n",ent->d_name);
                                trainSample -= 1;
                                continue;
                            } else{
                                char *fullDirFile = strAppend(fullDir, files->d_name);
                                fprintf(ftest,"%s\n",fullDirFile);
                                fprintf(ftestLabels,"%s\n",ent->d_name);
                                testSample -= 1;
                            }
                        }
                    }
                }
                else{
                    perror ("ERROR");
                }
            }
        }
    }
    else{
        perror ("ERROR");
    }

}

