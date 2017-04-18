#include <stdio.h>
#include "header/image.h"
#include "header/histogram.h"
#include "header/adjRelation.h"

int main(int   argc, char *argv[])
{
    Image rgbImg, ycbcrImg, testImg;
    readImage("/home/eu/Desktop/C_C++/MO815_BoW/Data/teste4.ppm", &rgbImg);
    rgb2ycbcr(&rgbImg, &ycbcrImg);
    ycbcr2rgb(&ycbcrImg,&testImg);

    destroyImage(&rgbImg);
    destroyImage(&ycbcrImg);
    destroyImage(&testImg);
    return 0;
}
