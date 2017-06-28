//
// Created by eu on 21/06/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "../header/image.h"
#include "../header/myMath.h"
#include "../header/adjRelation.h"

Image * filter(Image *img, Kernel *kernel){
    if(img->nChannels > 1){
        perror ("ERROR - A imagem deve possuir apenas um canal");
    }

    Image *fimage = zeroImage(img->numRows,img->numCols,img->nChannels);

    for (int i = 0; i < img->numRows; ++i) {
        for (int j = 0; j < img->numCols; ++j) {
            float val=0;
            for (int k = 0; k < kernel->adjRelation->numAdj; ++k) {
                if( (i+kernel->adjRelation->dx[k]>=0) && (i+kernel->adjRelation->dx[k]<=img->numRows-1) && (j+kernel->adjRelation->dy[k]>=0) && (j+kernel->adjRelation->dy[k]<=img->numCols-1)){
                    val += kernel->w[k]*img->ch[0].matIntensity[i+kernel->adjRelation->dx[k]][j+kernel->adjRelation->dy[k]];
                }
            }
            setVal(fimage,val,i,j,0);
        }
    }
    return fimage;
}

Image * sobelFilter(Image *img){

    float wx[9] = {-1,0,1,-2,0,2,-1,0,1};
    float wy[9] = {1,2,1,0,0,0,-1,-2,-1};
    Kernel *kernelx = createKernel(3, &wx);
    Kernel *kernely = createKernel(3, &wy);

    Image *imgx = filter(img, kernelx);
    Image *imgy = filter(img, kernely);

    destroyKernel(kernelx);
    destroyKernel(kernely);

    Image *gradImg = dotEuclidianDist(imgx,imgy);

    return gradImg;
}