//
// Created by eu on 12/04/17.
//

#include "../header/image.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../header/math.h"

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
        img->ch[i].vecIntensity = malloc((numRows*numCols)*sizeof(unsigned char));
        img->ch[i].matIntensity = malloc(numRows * sizeof(unsigned char*));
        for (int j = 0; j < numRows; j++) {
            img->ch[i].matIntensity[j] = malloc(numCols * sizeof(unsigned char));
        }
    }
}

void readImage(char imgPath[], Image *img){

    char* ext = getExtention(imgPath);

    if( strcmp(ext, ".pgm") == 0){
        readPGMImage(imgPath, img);
        return;
    }
    if( strcmp(ext, ".ppm") == 0){
        readPPMImage(imgPath, img);
        return;
    }
    else{
        printf("extension %s not supported\n",ext);
    }

}

// _____________________reading functions_______________________

//PGM------------
void readPGMImage(char imgPath[], Image *img){
    FILE *f;
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
            fscanf(f,"%hhu",&img->ch[0].vecIntensity[i]);
            //Fill Matrix
            r = i/img->numCols;
            c = i%img->numCols;
            img->ch[0].matIntensity[r][c] = img->ch[0].vecIntensity[i];
        }
    }

        //Set intensities for P5 images
    else if( strcmp(magicNum,"P5")==0 ){
        fgetc(f);
        fread(img->ch[0].vecIntensity,sizeof(unsigned char),img->numPixels,f);

        //Fill Matrix
        int r,c;
        for(int i=0; i< img->numPixels; i++){
            r = i/img->numCols;
            c = i%img->numCols;
            img->ch[0].matIntensity[r][c] = img->ch[0].vecIntensity[i];
        }
    }

        //Magic number not found
   else{
       fprintf(stderr,"Unknown magic number.\n");
       exit(-1);
   }
    fclose(f);
}

//PPM------------
void readPPMImage(char imgPath[], Image *img){

    FILE *f;
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
        unsigned char val;
        for (int i = 0; i < img->numPixels; ++i) {
            for (int j = 0; j < img->nChannels; ++j) {
                fscanf(f,"%hhu",&img->ch[j].vecIntensity[i]);
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
        fprintf(stderr,"Unknown magic number.\n");
        exit(-1);
    }

    fclose(f);
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
            fprintf(f,"%u ",img->ch[0].matIntensity[i][j]);
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
            fprintf(f,"%u ",img->ch[j].vecIntensity[i]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

//P5--------
void saveP5Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P5\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);
    fwrite(img->ch[0].vecIntensity, sizeof(unsigned char), img->numPixels, f);
    fclose(f);
}

//P6--------
void saveP6Image(Image *img, char filename[]){
    FILE *f = fopen(filename, "wb");
    fprintf(f, "P6\n%d %d\n%d\n", img->numCols,img->numRows, img->maxIntensity);
    unsigned char color[3];
    for (int i = 0; i < img->numPixels; i++){
        for (int j = 0; j < img->nChannels; j++){
            color[j] = img->ch[j].vecIntensity[i];
        }
        fwrite(color, sizeof(unsigned char), 3, f);
    }
    fclose(f);
}
//____________________________________end__________________________________

//_____________________________Conversions________________________________
void rgb2ycbcr(Image *rgbImg, Image *ycbcrImg){

    setImage(ycbcrImg, rgbImg->nChannels, rgbImg->numRows, rgbImg->numCols, 240);

    float Kr = 0.257, Kg = 0.504, Kb = 0.098;
    float Cbr = -0.148, Cbg = -0.291, Cbb = 0.439;
    float Crr = 0.439, Crg = -0.368, Crb = -0.071;
    int R,G,B;

    for (int i = 0; i < rgbImg->numPixels; ++i) {
        R = rgbImg->ch[0].vecIntensity[i];
        G = rgbImg->ch[1].vecIntensity[i];
        B = rgbImg->ch[2].vecIntensity[i];
        ycbcrImg->ch[0].vecIntensity[i] = (unsigned char)clip(round(Kr*R + Kg*G + Kb*B + 16), 16, ycbcrImg->maxIntensity);
        ycbcrImg->ch[1].vecIntensity[i] = (unsigned char)clip(round(Cbr*R + Cbg*G + Cbb*B + 128),16, ycbcrImg->maxIntensity);
        ycbcrImg->ch[2].vecIntensity[i] = (unsigned char)clip(round(Crr*R + Crg*G + Crb*B + 128),16, ycbcrImg->maxIntensity);
    }
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
        rgbImg->ch[0].vecIntensity[i] = (unsigned char)clip(round(RGBy * (Y-16) + Rcr*(Cr-128)), 0, rgbImg->maxIntensity);
        rgbImg->ch[1].vecIntensity[i] = (unsigned char)clip(round(RGBy * (Y-16) + Gcr*(Cr - 128) + Gcb*(Cb - 128)), 0, rgbImg->maxIntensity);
        rgbImg->ch[2].vecIntensity[i] = (unsigned char)clip(round(RGBy * (Y-16) + Bcb*(Cb - 128)),  0, rgbImg->maxIntensity);
    }
}

void rgb2hsv(Image *rgbImg, Image *hsvImg){

}

//____________________________________end_________________________________
