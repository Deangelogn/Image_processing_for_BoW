//
// Created by eu on 12/04/17.
//

#ifndef CLION_IMAGE_H
#define CLION_IMAGE_H

#define getPixelValue(img,x,y) img.ch[0].vecIntensity[x*img.numCols+y]

typedef struct intensityMap{
    float **matIntensity;
    float *vecIntensity;
} intensityMap;

typedef struct Image{
    int nChannels, numRows, numCols, maxIntensity, numPixels ;
    intensityMap *ch;
} Image;

char * getExtention(char filename[]);
void setImage(Image *img, int numChannels, int numRows, int numCols, int maxIntensity);
void printImage(Image *img);

Image* readImage(char imgPath[]);
Image* readPGMImage(char imgPath[]);
Image* readPPMImage(char imgPath[]);

void destroyImage(Image *img);

void savePXMImage( Image *img, char magicNumber[], char filename[]);
void saveP2Image(Image *img, char filename[]);
void saveP5Image(Image *img, char filename[]);
void saveP3Image(Image *img, char filename[]);
void saveP6Image(Image *img, char filename[]);
void copyImg(char *from, char *to);

void rgb2ycbcr(Image *rgbImg, Image *ycbcrImg);
void ycbcr2rgb(Image *ycbcrImg, Image *rgbImg);
void rgb2hsv(Image *rgbImg, Image *hsvImg);

void duplicateImg(Image *img1, Image *img2);
Image * getSubImage (Image *img, int rowB, int rowE, int colB, int colE);

#endif //CLION_IMAGE_H
