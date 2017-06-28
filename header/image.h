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
Image * zeroImage(int row, int col, int c);
void printImage(Image *img);
void printImageFromTo(Image *img,int x_begin,int x_end, int y_begin, int y_end, int c_begin, int c_end);
Image * getChannel(Image *img, int c);

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

Image * rgb2ycbcr(Image *rgbImg);
void ycbcr2rgb(Image *ycbcrImg, Image *rgbImg);
void rgb2hsv(Image *rgbImg, Image *hsvImg);

void duplicateImg(Image *img1, Image *img2);
Image * getSubImage (Image *img, int rowB, int rowE, int colB, int colE);
void setVal(Image *img, float val, int x, int y, int c);
float maxImg(Image*img);

Image * roundImage(Image *img);

#endif //CLION_IMAGE_H
