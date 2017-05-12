#include <stdio.h>
#include <stdlib.h>
#include "header/image.h"
#include "header/histogram.h"
#include "header/alg.h"
#include "header/myMath.h"
#include "header/adjRelation.h"
#include "header/morphology.h"
#include "header/direct.h"
#include "header/imagePile.h"
#include "header/bow.h"
#include "header/label.h"
#include "header/features.h"

#include <dirent.h>
int main(int   argc, char *argv[])
{
    // ----- part 1 -------
    int numWords = 50, it = 1000, run=2;
    ImagePile *imgPile, *cropImgPile;
    int height = 64, width=64;
    int binsPerChannel=4; //histogram bins
    float begin=1, end=3, step=1; //Granulometry parameters
    int numClasses=5;

    //create random training and test datasets from coil database
    //uncomment this part if you wish to generate a dataset

    int *pInt = randInt(100,numClasses), ID = 5;
    float per = 0.84;

    /*char *srcDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/classes/";
    char *tarDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/";
    createDatasetFrom(pInt,numClasses, srcDir, tarDir, ID, per);
    saveDatasetInfo(pInt,numClasses,72,ID,per,"/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/");
    */

    // Create a pile of images
    char *datasetDir = "/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/test_set5/";
    imgPile = getImagesFrom(datasetDir);

    //sub-sampling images
    cropImgPile = cropPile(imgPile,height,width);

    //get image histogram
    Histogram *histPile = createRGBHistogramFromPile(cropImgPile,binsPerChannel);

    //get granulometry features
    FeatureMatrix *granulometryPile = getGranulometryFromPile(imgPile,begin,end,step);

    //Merge features
    FeatureMatrix *fm = MergeFMWithHistogram(granulometryPile,histPile);

    saveFM("/home/eu/Desktop/C_C++/Image_processing_for_BoW/Data/fm.txt",fm);

    return 0;
}
