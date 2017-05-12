//
// Created by eu on 11/05/17.
//

#ifndef MO815_BOW_LABEL_H
#define MO815_BOW_LABEL_H

typedef struct Label{
    char *name;
}Label;


typedef struct VecLabel{
    int * labelId;
    int numLabels;
    Label *labelName;
}VecLabel;


VecLabel *createVecLabel(int numLabels);
void destroyVecLabel(VecLabel *vl);
void setLabelNameById(VecLabel *vl, char *name, int Id);
void printLabels(VecLabel *vl);

#endif //MO815_BOW_LABEL_H
