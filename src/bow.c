//
// Created by eu on 27/04/17.
//

#include <stdlib.h>
#include <printf.h>
#include "../header/morphology.h"
#include "../header/histogram.h"
#include "../header/myMath.h"
#include "../header/alg.h"
#include "../header/stringManipulation.h"
#include <stdio.h>
#include <dirent.h>
#include <memory.h>
#include <stdbool.h>
#include "../header/bow.h"
#include "../header/filter.h"

FeatureVector * getBowFeatures(Image *imgPile, int numImg, FeatureVector *Dict , int numWords){
    FeatureVector *fvout = malloc(numImg*sizeof(FeatureVector));
    Image *cropImg;
    int pileSize;
    int bins[3]={2,2,2};
    float begin=1, end=3, step=1;

    for (int i = 0; i < numImg; ++i) {
        //cropImg = cropImage(&imgPile[i],1,64,64,&pileSize);

        //hist
        Histogram histPile[pileSize];
        for (int j = 0; j < pileSize; ++j) {
        //    getRGBHistogram(&cropImg[j],&histPile[j], &bins);
        }

        //granulo
        FeatureVector fv[pileSize];
        int numFeatures = (int)((end-begin)/step)+1;
        for (int j = 0; j < pileSize; ++j) {
            float *granulometryFeatures = getGranulometry(&cropImg[j], begin, end,step);
            vecMerge (histPile[j].normBin, granulometryFeatures, histPile[j].numBins, numFeatures, &fv[j]);
        }

        // closest word
        int idx;
        setFeatureVector(&fvout[i],numWords);
        for (int j = 0; j < pileSize; ++j) {
            fvout[i].features[j] = 0;
        }

        for (int j = 0; j < pileSize; ++j) {
             idx = closestVec(&fv[j], Dict, numWords);
             fvout[i].features[idx] += 1;
        }

        //norm hist word

        for (int j = 0; j < pileSize; ++j) {
            fvout[i].features[j] = fvout[i].features[j]/(float)pileSize;
            if(fvout[i].features[j]>1){
                printf("aqui %d\n",i);
            }
            if(fvout[i].features[j]<0){
                printf("aqui2 %d\n", i);
            }
        }

    }

    return fvout;
}

int findVisualWords(FeatureVector *aword, FeatureVector *matWords, int numWords){
    return closestVec(aword,matWords,numWords);
}

float classifier(char *trainDir, char *testDir, FeatureVector *dic, int dictonarySize,
                  FeatureVector *kel, int kSize, Image* pileImg, int pileSize){
    DIR *dir;
    struct dirent *ent;
    int rClass, cClass,cont=0, right=0;
    Image img;


    dir = opendir(testDir);
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if( !((strcmp(ent->d_name,".")==0) || (strcmp(ent->d_name,"..")==0)) ){

                char *imgFullPath = strAppend(testDir,ent->d_name);
                rClass = getNumber(ent->d_name);
                //readImage(imgFullPath, &img);

                FeatureVector *hwImg = getBowFeatures(&img, 1, dic , dictonarySize);
                int idxK = findVisualWords(hwImg,kel,kSize);
                int idxC = findVisualWords(&kel[idxK],pileImg, pileSize);
                char *imgName = getImgeAfter(trainDir, idxC);
                cClass = getNumber(imgName);

                if(rClass == cClass){
                    right++;
                }
                cont++;
                //printf("%d\n", cont);
            }

        }
        closedir (dir);
    }
    else{
        perror ("");
        return EXIT_FAILURE;
    }
    printf("%d, %d\n",right, cont);
    return ((float)right/(float)cont);
}

char * getImgeAfter(char *srcDir, int aft){
    DIR *dir;
    struct dirent *ent;
    dir = opendir(srcDir);
    int cont=0;

    if (dir != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (!((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))) {
                if(cont==aft){
                    char *str = ent->d_name;
                    return str;
                }
                else{
                    cont++;
                }
            }
        }
    }
    return "";
}

void saveColorDescriptorFeatures(char * sourceFile, char * tarFile, int numBins){

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp = fopen(sourceFile,"r");
    FILE *fout = fopen(tarFile,"w");
    int cont =1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%d\n", cont);
        if(cont>0) {
            line[strlen(line) - 1] = 0;
            Image *img = readPPMImage(line);
            Histogram *histogram = getRGBHistogram(img,numBins);
            for (int i = 0; i < histogram->numBins; ++i) {
                fprintf(fout,"%f ",histogram->normBin[i]);
            }
            fprintf(fout,"\n");
            destroyImage(img);
            destroyHistogram(histogram);
        }
        cont++;

    }
    fclose(fp);

    if (line)
        free(line);
}

int * findKeypoints(Image* spImg, Image* gradImg, float th){
    float maxValue = maxImg(gradImg);
    float thValue = maxValue * th;
    int X[3]= {-1,0,0,0,1};
    int Y[3]= {0,-1,0,1,0};
    AdjRelation *adjRelation = createAdjRelation(X,Y,3);

    //printf("%f, %f\n",maxValue, maxValue*0.7);
    int cont = 0;
    for (int i = 0; i < spImg->numPixels; ++i) {
        if ( (i%spImg->numCols>0) &&
             ( i%spImg->numCols<spImg->numCols-1) &&
             ( i/spImg->numCols>0) &&
             ( i/spImg->numCols<spImg->numRows-1) ){
            if(isIntersection(spImg, adjRelation,i/spImg->numCols, i%spImg->numCols, 1)){
                if(gradImg->ch[0].vecIntensity[i] >= thValue){
                    //printf("%d, %d, %.0f\n", i/spImg->numCols, i%spImg->numCols, gradImg->ch[0].vecIntensity[i]);
                    cont++;
                }
            }
        }
    }
    //printf("%d\n",cont);
    int *p = (int*)malloc((cont*2+1)*sizeof(int));
    p[0] = cont*2;
    int k=1;
    for (int i = 0; i < spImg->numPixels; ++i) {
        if ( (i%spImg->numCols>0) &&
             ( i%spImg->numCols<spImg->numCols-1) &&
             ( i/spImg->numCols>0) &&
             ( i/spImg->numCols<spImg->numRows-1) ){
            if(isIntersection(spImg, adjRelation,i/spImg->numCols, i%spImg->numCols, 1)){
                if(gradImg->ch[0].vecIntensity[i] >= thValue){
                    p[k] = i/spImg->numCols;
                    p[k+1] =  i%spImg->numCols;
                    k +=2;
                }
            }
        }
    }
    return p;
}

bool isIntersection(Image *img, AdjRelation *adjRelation, int row, int col, int diffnum){
    int x,y,cont=0;
    float val = img->ch[0].matIntensity[row][col];
    for (int i = 0; i < adjRelation->numAdj; ++i) {
        x = (row + adjRelation->dx[i])*img->numCols ;
        y = col+adjRelation->dy[i];
        if (img->ch[0].vecIntensity[x+y]!=val){
            cont++;
        }
        if(cont >= diffnum){
            return true;
        }

    }
    return false;
}

void printKeyPoints(int *p){
    printf("number of key points: %d\n", p[0]/2);
    printf("x,y:\n");
    for (int i = 1; i < p[0]; i+=2) {
        printf("%d, %d\n",p[i], p[i+1]);
    }

}

Image* matchKeyPoints(int *p,Image *img) {
    Image *image = (Image*)malloc(sizeof(Image));
    duplicateImg(img, image);

    for (int i = 1; i < p[0]; i += 2) {
        setVal(image, 255, p[i], p[i + 1], 0);
        setVal(image, 0, p[i], p[i + 1], 1);
        setVal(image,0,p[i],p[i+1],2);
    }
    return image;
}

int *adjustKeypoints(int *p, int diffy){
    int cont=1,k=1;
    int new_y, old_y = p[2];
    for (int i = 3; i < p[0]; i += 2) {
        new_y = p[i+1];
        if (abs(new_y - old_y)>diffy){
            cont++;
            old_y = new_y;
        }

    }
    int *np = (int*)malloc((cont*2+1)*sizeof(int));
    np[0]= cont*2;
    np[1]= p[1];
    np[2]= p[2];
    k+=2;
    old_y = p[2];
    for (int i = 3; i < p[0]; i += 2) {
        new_y = p[i+1];
        if (abs(new_y - old_y)>diffy){
            np[k] = p[i];
            np[k+1] = p[i+1];
            k += 2;
            old_y = new_y;
        }
    }
    return np;
}