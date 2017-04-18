//
// Created by eu on 18/04/17.
//

double round(double num){
    int integer =  (int)num;
    if(num-integer>0.5){
        return (int)(num+1);
    }
    else{
        return integer;
    }
}

double clip(double num, double minLimit, double maxLimit){
    if(num>maxLimit){
        return maxLimit;
    }
    if(num<minLimit){
        return minLimit;
    }
    return num;
}

double pow(double num, int p){
    if(p==0){
        return 1;
    }
    double result=num;
    for (int i = 0; i < p-1; ++i) {
        result *= num;
    }
    return result;
}
