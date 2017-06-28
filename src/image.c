//
// Created by eu on 12/04/17.
//

#include "../header/image.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/myMath.h"

//_____________________________useful functions____________________
char * getExtention(char filename[]){
    char *ext;
    ext = strrchr(filename, '.');
    return ext;
}

void destroyImage(Image *img){
    for (int i = 0; i < img->nChannels; i++) {
        for (int j = 0; j < img->numRows; ++j) {
            (img->ch[i].matIntensity[j]);
        }
        free(img->ch[i].matIntensity);
        free(img->ch[i].vecIntensity);
    }

}

void setImage(Image *img, int numChannels, int numRows, int numCols, int maxIntensity){
    img->numRows = numRows;
    img->numCols = numCols;
    img->numPixels = numCols * numRows;
    img->nChannels = numChannels;
    img->maxIntensity = maxIntensity;
    img->ch = malloc(numChannels*sizeof(intensityMap));
    for (int i = 0; i < numChannels; ++i) {
        img->ch[i].vecIntensity = malloc((numRows*numCols)*sizeof(float));
        img->ch[i].matIntensity = malloc(numRows * sizeof(float*));
        for (int j = 0; j < numRows; j++) {
            img->ch[i].matIntensity[j] = malloc(numCols * sizeof(float));
        }
    }
}

void printImage(Image *img){
    for (int i = 0; i < img->nChannels; ++i) {
        printf("channel %d:\n", i);
        for (int j = 0; j < img->numPixels; ++j) {
            printf("%d, ", (int)img->ch[i].vecIntensity[j]);
            if((j+1)%img->numCols==0){
                printf(";\n");
            }
        }
        printf("\n");
    }
}

void printImageFromTo(Image *img,int x_begin,int x_end, int y_begin, int y_end, int c_begin, int c_end){
    for (int i = c_begin; i < c_end+1; ++i) {
        for (int j = x_begin; j < x_end; ++j) {
            for (int k = y_begin; k < y_end; ++k) {
                printf("%.2f ", img->ch[i].matIntensity[j][k]);
            }
            printf("\n");
        }
    }
}

Image * zeroImage(int row, int col, int c){
    Image * image = (Image*)malloc(sizeof(Image));
    setImage(image,c,row,col,255);
    //printf("%d,%d,%d,%d\n", image->numRows,image->numCols,image->nChannels,image->maxIntensity);
    for (int i = 0; i < c; ++i) {
        for (int j = 0; j < row; ++j) {
            for (int k = 0; k < col; ++k) {
                setVal(image,0,j,k,i);
            }
        }
    }
    return image;
}

//____________________________end___________________________________


// _____________________reading functions_______________________

Image* readImage(char imgPath[]){

    char* ext = getExtention(imgPath);
    if( strcmp(ext, ".pgm") == 0){
        return readPGMImage(imgPath);
    }
    if( strcmp(ext, ".ppm") == 0){
        return readPPMImage(imgPath);
    }
    else{
        printf("extension %s not supported\n",ext);
    }

}
//PGM------------
Image* readPGMImage(char imgPath[]){
    FILE *f;
    Image *img = malloc(sizeof(Image));
    f = fopen(imgPath, "rb");
    char magicNum[3];
    int cols, rows;
    int maxIntensity;

    if (f == NULL){
        fprintf(stderr,"Cannot open %s\n",imgPath);
        exit(-1);
    }

    //Get magic number
    fscanf(f,"%s\n",magicNum);

    //Skipping comments
    char strC[2]="\0";
    strC[0] = getc(f);
    while( strcmp(strC,"#")==0 ){
        while (getc(f) != '\n');
        strC[0] = getc(f);
    }
    ungetc(strC[0], f);

    //Get image dimentions and max intensity
    fscanf(f,"%d %d %d",&cols, &rows, &maxIntensity);
    setImage(img, 1, rows, cols, maxIntensity);

    //Set intensities for P2 images
    if( strcmp(magicNum,"P2")==0 ){
        int r,c;
        for(int i=0; i< img->numPixels; i++){
            fscanf(f,"%f",&img->ch[0].vecIntensity[i]);
            //Fill Matrix
            r = i/img->numCols;
            c = i%img->numCols;
            img->ch[0].matIntensity[r][c] = img->ch[0].vecIntensity[i];
        }
    }

        //Set intensities for P5 images
    else if( strcmp(magicNum,"P5")==0 ){
        fgetc(f);
        fread(img->ch[0].vecIntensity,sizeof(float),img->numPixels,f);

        //Fill Matrix
        int r,c;
        for(int i=0; i< img->numPixels; i++){
            r = i/img->numCols;
            c = i%img->numCols;
            printf("%f\n",img->ch[0].vecIntensity[i]);
            img->ch[0].matIntensity[r][c] = img->ch[0].vecIntensity[i];
        }
    }

        //Magic number not found
   else{
       fprintf(stderr,"Unknown magic number.\n");
       exit(-1);
   }
    fclose(f);
    return img;
}

//PPM------------
Image* readPPMImage(char imgPath[]){

    FILE *f;
    Image *img = malloc(sizeof(Image));
    f = fopen(imgPath, "rb");
    char magicNum[3];
    int cols, rows;
    int maxIntensity;

    if (f == NULL){
        fprintf(stderr,"Cannot open %s\n",imgPath);
        exit(-1);
    }

    //Get magic number
    fscanf(f,"%s\n",magicNum);


    //Skipping comments
    char strC[2]="\0";
    strC[0] = getc(f);
    while( strcmp(strC,"#")==0 ){
        while (getc(f) != '\n');
        strC[0] = getc(f);
    }
    ungetc(strC[0], f);

    //set parameters
    fscanf(f,"%d %d %d\n",&cols, &rows, &maxIntensity);
    //Skipping comments
    strC[0] = getc(f);
    while( strcmp(strC,"#")==0 ){
        while (getc(f) != '\n');
        strC[0] = getc(f);
    }
    ungetc(strC[0], f);

    setImage(img, 3, rows, cols, maxIntensity);

    if (strcmp(magicNum,"P3")==0){
        int r,c;
        for (int i = 0; i < img->numPixels; ++i) {
            for (int j = 0; j < img->nChannels; ++j) {
                fscanf(f,"%f",&img->ch[j].vecIntensity[i]);
                r = i/img->numCols;
                c = i%img->numCols;
                img->ch[j].matIntensity[r][c] = img->ch[j].vecIntensity[i];
            }
        }
    }
    else if(strcmp(magicNum,"P6")==0){

        //Fill Matrix
        int r,c;
        for(int i=0; i< img->numPixels; i++){
            for (int j = 0; j < img->nChannels ; ++j) {
                r = i/img->numCols;
                c = i%img->numCols;
                img->ch[j].vecIntensity[i] = fgetc(f);
                img->ch[j].matIntensity[r][c] = img->ch[j].vecIntensity[i];
            }
        }
    }
    else{
        fprintf(stderr,"Unknown magic number %s.\n", magicNum);
        exit(-1);
    }

    fclose(f);
    return img;
}
// ___________________________________end______________________________


//_______________________________save functions_________________________
void savePXMImage( Image *img, char magicNumber[], char filename[]){

    if (strcmp(magicNumber,"P2")==0){
        saveP2Image(img,filename);
    }
    else if (strcmp(magicNumber,"P3")==0){
        saveP3Image(img,filename);
    }
    else if(strcmp(magicNumber,"P5")==0){
        saveP5Image(img,filename);
    }
    else if(strcmp(magicNumber,"P6")==0) {
        saveP6Image(img, filename);
    }
    else{
        printf("Unknown magic number");
    }
}

//P2------
void saveP2Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "w");
    fprintf(f, "P2\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);

    for (int i = 0; i < img->numRows; i++){
        for (int j = 0; j < img->numCols; j++){
            fprintf(f,"%.0f ",img->ch[0].matIntensity[i][j]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

//P3-------
void saveP3Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "w");
    fprintf(f, "P3\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);

    for (int i = 0; i < img->numPixels; i++){
        for (int j = 0; j < img->nChannels; j++){
            fprintf(f,"%d ",(int)img->ch[j].vecIntensity[i]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

//P5--------
void saveP5Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P5\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);
    fwrite(img->ch[0].vecIntensity, sizeof(float), img->numPixels, f);
    fclose(f);
}

//P6--------
void saveP6Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);
    unsigned char color[3];
    for (int i = 0; i < img->numPixels; i++){
        for (int j = 0; j < img->nChannels; j++){
            color[j] = (unsigned char)img->ch[j].vecIntensity[i];
        }
        fwrite(color, sizeof(unsigned char), 3, f);
    }
    fclose(f);
}

void copyImg(char *from, char *to){
    Image *img;
    img = readImage(from);
    saveP6Image(img,to);
}

//____________________________________end__________________________________

//_____________________________Conversions________________________________
Image * rgb2ycbcr(Image *rgbImg){
    Image *ycbcrImg = zeroImage(0,0,0);
    setImage(ycbcrImg, rgbImg->nChannels, rgbImg->numRows, rgbImg->numCols, 240);

    float Kr = 0.257, Kg = 0.504, Kb = 0.098;
    float Cbr = -0.148, Cbg = -0.291, Cbb = 0.439;
    float Crr = 0.439, Crg = -0.368, Crb = -0.071;
    int R,G,B;
    float valY,valCb, valCr;

    for (int i = 0; i < rgbImg->numPixels; ++i) {
        R = rgbImg->ch[0].vecIntensity[i];
        G = rgbImg->ch[1].vecIntensity[i];
        B = rgbImg->ch[2].vecIntensity[i];
        valY = (float)clip(round(Kr*R + Kg*G + Kb*B + 16), 16, ycbcrImg->maxIntensity);
        valCb = (float)clip(round(Cbr*R + Cbg*G + Cbb*B + 128),16, ycbcrImg->maxIntensity);
        valCr = (float)clip(round(Crr*R + Crg*G + Crb*B + 128),16, ycbcrImg->maxIntensity);
        setVal(ycbcrImg,valY,i/rgbImg->numCols, i%rgbImg->numCols, 0);
        setVal(ycbcrImg,valCb,i/rgbImg->numCols, i%rgbImg->numCols, 1);
        setVal(ycbcrImg,valCr,i/rgbImg->numCols, i%rgbImg->numCols, 2);
    }
    return ycbcrImg;
}

void ycbcr2rgb(Image *ycbcrImg, Image *rgbImg){

    setImage(rgbImg, ycbcrImg->nChannels, ycbcrImg->numRows, ycbcrImg->numCols, 255);

    float RGBy = 1.164;
    float Rcr = 1.596;
    float Gcr = -0.813, Gcb = -0.392;
    float Bcb = 2.071;
    int Y,Cb,Cr;

    for (int i = 0; i < rgbImg->numPixels; ++i) {
        Y = ycbcrImg->ch[0].vecIntensity[i];
        Cb = ycbcrImg->ch[1].vecIntensity[i];
        Cr = ycbcrImg->ch[2].vecIntensity[i];
        rgbImg->ch[0].vecIntensity[i] = (float)clip(round(RGBy * (Y-16) + Rcr*(Cr-128)), 0, rgbImg->maxIntensity);
        rgbImg->ch[1].vecIntensity[i] = (float)clip(round(RGBy * (Y-16) + Gcr*(Cr - 128) + Gcb*(Cb - 128)), 0, rgbImg->maxIntensity);
        rgbImg->ch[2].vecIntensity[i] = (float)clip(round(RGBy * (Y-16) + Bcb*(Cb - 128)),  0, rgbImg->maxIntensity);
    }
}

void rgb2hsv(Image *rgbImg, Image *hsvImg){

}

Image* rgb2gray(Image *rgbImg){
    Image *image = NULL;

    return image;
}
//____________________________________end_________________________________

void duplicateImg(Image *img1, Image *img2){
    setImage(img2, img1->nChannels,img1->numRows,img1->numCols,img1->maxIntensity);
    int r,c;
    for (int i = 0; i < img1->nChannels; ++i) {
        for (int j = 0; j < img1->numPixels; ++j) {
            img2->ch[i].vecIntensity[j] = img1->ch[i].vecIntensity[j];
            r = j/img2->numCols;
            c = j%img2->numCols;
            img2->ch[i].matIntensity[r][c] = img2->ch[i].vecIntensity[j];
        }
    }
}


Image * getSubImage (Image *img, int rowB, int rowE, int colB, int colE){
    Image *subImg = malloc(sizeof(Image));
    setImage(subImg, 3, rowE-rowB, colE-colB, 255);
    int k=0, index;
    for (int i = rowB; i < rowE; ++i) {
        for (int j = colB; j < colE; ++j) {
            index = i*img->numCols+j;
            subImg->ch[0].vecIntensity[k]= img->ch[0].vecIntensity[i*img->numCols+j];
            subImg->ch[1].vecIntensity[k]= img->ch[1].vecIntensity[i*img->numCols+j];
            subImg->ch[2].vecIntensity[k]= img->ch[2].vecIntensity[i*img->numCols+j];
            subImg->ch[0].matIntensity[k/subImg->numCols][k%subImg->numCols] = subImg->ch[0].vecIntensity[k];
            subImg->ch[1].matIntensity[k/subImg->numCols][k%subImg->numCols] = subImg->ch[1].vecIntensity[k];
            subImg->ch[2].matIntensity[k/subImg->numCols][k%subImg->numCols] = subImg->ch[2].vecIntensity[k];
            k++;
        }
    }
    return subImg;
}

void setVal(Image *img, float val, int x, int y, int c){
    img->ch[c].matIntensity[x][y] = val;
    img->ch[c].vecIntensity[x*img->numCols + y] = val;
}

Image * roundImage(Image *img){
    Image *image = zeroImage(img->numRows,img->numCols,img->nChannels);
    for (int i = 0; i < img->nChannels; ++i) {
        for (int j = 0; j < img->numRows; ++j) {
            for (int k = 0; k < img->numCols; ++k) {
                setVal(image,round(img->ch[i].matIntensity[j][k]),j,k,i);
            }
        }
    }
    return image;
}

Image * getChannel(Image *img, int c){
    Image *image = zeroImage(img->numRows,img->numCols,1);
    for (int i = 0; i < img->numRows; ++i) {
        for (int j = 0; j < img->numCols; ++j) {
            setVal(image,img->ch[c].matIntensity[i][j],i,j,0);
        }
    }

    return image;
}

float maxImg(Image*img){
    float max=0;
    for (int i = 0; i < img->numPixels; ++i) {
        if(img->ch[0].vecIntensity[i]>max){
            max = img->ch[0].vecIntensity[i];
        }
    }
    return max;
}