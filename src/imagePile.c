//
// Created by eu on 11/05/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "../header/imagePile.h"
#include "../header/myMath.h"

ImagePile * createImagePile(int numImages){
    ImagePile* imgPile = malloc(sizeof(ImagePile));
    imgPile->pileSize = numImages;
    imgPile->img = malloc(numImages*sizeof(Image));
    return imgPile;
}

ImagePile *cropPile(ImagePile *imgPile, int height, int width){
    int numCropImg =0, it=0, rEnd, cEnd;
    Image *auxImg;
    for (int i = 0; i < imgPile->pileSize; ++i) {
        numCropImg += myCeil(imgPile->img[i].numRows/height) + myCeil(imgPile->img[i].numCols/width);
    }

    ImagePile *cropImgPile = createImagePile(numCropImg);

    for (int i = 0; i < imgPile->pileSize; ++i) {
        for (int j = 0; j < imgPile->img[i].numRows; j+=height) {
            for (int k = 0; k < imgPile->img[i].numCols; k+=width) {

                if(j+height>imgPile->img[i].numRows){
                    rEnd = j + (imgPile->img[i].numRows-j);
                }
                else{
                    rEnd = j + height;
                }

                if(k+width>imgPile->img[i].numCols){
                    cEnd = k + (imgPile->img[i].numCols-k);
                }
                else{
                    cEnd = k + width;
                }
                auxImg = getSubImage(&imgPile->img[i],j, rEnd, k, cEnd);
                duplicateImg(auxImg,&cropImgPile->img[it]);

                it++;
            }
        }

    }


    return  cropImgPile;
}
