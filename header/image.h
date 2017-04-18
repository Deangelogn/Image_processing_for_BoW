//
// Created by eu on 12/04/17.
//

#ifndef CLION_IMAGE_H
#define CLION_IMAGE_H

#define getPixelValue(img,x,y) img.ch[0].vecIntensity[x*img.numCols+y]

typedef struct intensityMap{
    unsigned char **matIntensity;
    unsigned char *vecIntensity;
} intensityMap;

typedef struct Image{
    int nChannels, numRows, numCols, maxIntensity, numPixels ;
    intensityMap *ch;
} Image;

char * getExtention(char filename[]);

void readImage(char imgPath[], Image *img);
void setImage(Image *img, int numChannels, int numRows, int numCols, int maxIntensity);
void readPGMImage(char imgPath[], Image *img);
void readPPMImage(char imgPath[], Image *img);

void destroyImage(Image *img);

void savePXMImage( Image *img, char magicNumber[], char filename[]);
void saveP2Image(Image *img, char filename[]);
void saveP5Image(Image *img, char filename[]);
void saveP3Image(Image *img, char filename[]);
void saveP6Image(Image *img, char filename[]);

void rgb2ycbcr(Image *rgbImg, Image *ycbcrImg);
void ycbcr2rgb(Image *ycbcrImg, Image *rgbImg);
void rgb2hsv(Image *rgbImg, Image *hsvImg);

#endif //CLION_IMAGE_H
