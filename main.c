//
// Created by eu on 19/06/17.
//

#include "header/direct.h"
#include "header/stringManipulation.h"
#include "header/adjRelation.h"
#include "header/filter.h"
#include "header/myMath.h"
#include "header/bow.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


int main(int   argc, char *argv[])
{
    //step 1
    /*char * fileDir = "/home/eu/Desktop/Image_processing_for_BoW/data/Coil_100";
    char * datasetDir = "/home/eu/Desktop/Data/Coil_100/";
    createDatasetFileFromData(datasetDir,fileDir,0.75, 0);*/

    //AdjRelation *adjRelation = createSquareAdjRelation(3);
    //printAdjRelation(adjRelation);


    //saveP2Image(roundImage(gradImg),"/home/eu/Desktop/out2.pgm");

    // destroyKernel(&kernel);

    //destroyAdjRelation(adjRelation);

    //step 2
    /*char * fileIn = "/home/eu/Desktop/Image_processing_for_BoW/data/MNIST_traning.txt";
    char * tarDir = "~/Desktop/Data/sp_MNIST/";

    char *numSP = " 50 ";
    char *alpha = "0.12 ";
    char *beta = "12 ";
    char *it = "10 ";
    char *p = "0 ";

    char *aux = "~/Desktop/isf_demo/bin/iftISF_MIX_MEAN ";

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen(fileIn,"r");
    int cont =1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%d\n", cont);
        line[strlen(line)-1] = 0;
        char *command = strAppend(aux,line);
        command = strAppend(command, numSP);
        command = strAppend(command,alpha);
        command = strAppend(command,beta);
        command = strAppend(command,it);
        command = strAppend(command,p);
        command = strAppend(command,strAppend(tarDir,num2str(cont,4)));
        system(command);
        cont++;
    }
    */
     //step 3
    /*char * fileIn = "/home/eu/Desktop/Image_processing_for_BoW/data/101_ObjectCategories_test.txt";
    char * tarDir = "/home/eu/Desktop/Data/101_ObjectCategories_test_grad/";

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen(fileIn,"r");
    int cont =1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%d\n", cont);
        if(cont>1393) {
            line[strlen(line) - 1] = 0;
            Image *img = readPPMImage(line);
            Image *ycbcr = rgb2ycbcr(img);
            Image *yimg = getChannel(ycbcr, 0);
            char *out = strAppend(tarDir, num2str(cont, 4));
            out = strAppend(out, ".pgm");
            saveP2Image(sobelFilter(yimg), out);
            destroyImage(img);
            destroyImage(ycbcr);
            destroyImage(yimg);
        }
        cont++;
    }




    fclose(fp);

    if (line)
        free(line);*/

    //

    //step 4 - find key points


    //step 5
    //char * fileIn = "/home/eu/Desktop/Image_processing_for_BoW/data/Coil_100_traning.txt";
    //char * tarDir = "/home/eu/Desktop/Image_processing_for_BoW/data/HistColor_Features/Coil_100_train.txt";
    //int binsPerChannel = 4;
    //saveColorDescriptorFeatures(fileIn,tarDir,binsPerChannel);

    Image *image = readPPMImage("/home/eu/Desktop/Data/Coil_100/060/obj60__175.ppm");
    Image *imagrad = readPGMImage("/home/eu/Desktop/Data/Coil_100_train_grad/0001.pgm");
    Image *imasp = readPGMImage("/home/eu/Desktop/Data/Coil_100_train_sp/0001.pgm");

    int *p = findKeypoints(imasp, imagrad, 0.45);
    int *np = adjustKeypoints(p,8);
    printKeyPoints(np);


    Image *kimg= matchKeyPoints(np,image);
    int xb,yb,xe,ye,maxR, maxC;
    //maxR = kimg.

    for (int i = 1; i < np[0]; i+=2) {
        xb = np[i] - 8;
        xe = np[i] + 7;
        yb = np[i+1] -8;
        ye = np[i+1] +7;
       // if ()
        //Image *img = getSubImage(image, p[i]);


        //destroyImage(img);
    }

    //saveP3Image(kimg,"/home/eu/Desktop/Kimg.ppm");

    destroyImage(imagrad);
    destroyImage(imasp);
    destroyImage(image);
    //destroyImage(kimg);
    free(p);
    return 0;
}