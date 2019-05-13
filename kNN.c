#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "kNN.h"
#include "MnistLoader.h"

int compare(const void * a, const void * b)
{
    return ( (*(RESULT_PAIR*)a).distance - (*(RESULT_PAIR*)b).distance );
}

float CalcL2(uint8_t* vect1,uint8_t* vect2,int vectLen)
{
    float L2=0;
    for(int i=0;i<vectLen;i+=1)
    {
        L2+=(vect1[i]-vect2[i])*(vect1[i]-vect2[i]);
    }
    return L2;
}

uint8_t KnnVote(RESULT_PAIR* resultPair,int kNb)
{

}

uint8_t KnnFit(MNIST_CHAR_LIST* trainDataList,MNIST_CHAR* testChar,int kNb)
{
    uint32_t len=trainDataList->len;
    RESULT_PAIR* resultPairList=malloc(len*sizeof(RESULT_PAIR));

    for(int i=0;i<len;i++)
    {
        resultPairList[i].distance=CalcL2(trainDataList->chars[i].pixels,testChar->pixels,CHAR_H*CHAR_W);
        resultPairList[i].index=i;
    }
    qsort(resultPairList, len, sizeof(RESULT_PAIR), compare);
    uint8_t finalResult=trainDataList->chars[resultPairList[0].index].label;
    free(resultPairList);
    return finalResult;
}

