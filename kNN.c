#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "kNN.h"
#include "MnistLoader.h"
#include "hashtable.h"

int compare(const void * a, const void * b)
{
    return ( (*(RESULT_PAIR*)a).distance - (*(RESULT_PAIR*)b).distance );
}

uint32_t CalcL2(uint8_t* vect1,uint8_t* vect2,int vectLen)
{
    uint32_t L2=0;
    for(int i=0;i<vectLen;i+=1)
    {
        int32_t a=vect1[i]-vect2[i];
        L2+=a*a;
    }
    return L2;
}

uint32_t KnnVote(RESULT_PAIR* resultPairList,int kNb)
{
    hash_table ht;
    ht_init(&ht, HT_KEY_CONST | HT_VALUE_CONST, 0.05);

    for(int i=0;i<kNb;i++)
    {
        if(!ht_contains(&ht,&resultPairList[i].label,sizeof(uint32_t)))
        {
            ht_insert(&ht,&resultPairList[i].label,sizeof(uint32_t),&resultPairList[i].occurTimes,sizeof(uint32_t));
        }
        else
        {
            size_t valueSize;
            uint32_t* occurTimes=ht_get(&ht,&resultPairList[i].label,sizeof(uint32_t),&valueSize);
            (*occurTimes)++;
        }
    }

    size_t keyNum;

    void** keys=ht_keys(&ht,&keyNum);


}

uint8_t KnnFit(MNIST_CHAR_LIST* trainDataList,MNIST_CHAR* testChar,int kNb)
{
    uint32_t len=trainDataList->len;
    RESULT_PAIR* resultPairList=malloc(len*sizeof(RESULT_PAIR));

    for(int i=0;i<len;i++)
    {
        resultPairList[i].distance=CalcL2(trainDataList->chars[i].pixels,testChar->pixels,CHAR_H*CHAR_W);
        resultPairList[i].index=i;
        resultPairList[i].label=trainDataList->chars[i].label;
    }
    qsort(resultPairList, len, sizeof(RESULT_PAIR), compare);
    uint32_t result=KnnVote(resultPairList,kNb);
    free(resultPairList);
    return result;
}

