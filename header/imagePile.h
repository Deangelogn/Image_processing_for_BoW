//
// Created by eu on 11/05/17.
//

#ifndef MO815_BOW_IMAGEPILE_H
#define MO815_BOW_IMAGEPILE_H

#include "image.h"

typedef struct ImagePile{
    Image *img;
    int pileSize;
}ImagePile;

ImagePile * createImagePile(int numImages);
ImagePile *cropPile(ImagePile *imgPile, int height, int width);

#endif //MO815_BOW_IMAGEPILE_H
