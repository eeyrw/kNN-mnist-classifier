#include <stdio.h>
#include "MnistLoader.h"
#include "kNN.h"

int main(void)
{
    MNIST_CHAR_LIST mnistTrainList;
    MNIST_CHAR_LIST mnistTestList;
    mnistTrainList=MnistLoad("./dataSet/train-images.idx3-ubyte","./dataSet/train-labels.idx1-ubyte");
    mnistTestList=MnistLoad("./dataSet/t10k-images.idx3-ubyte","./dataSet/t10k-labels.idx1-ubyte");


    uint32_t errorCount=0;
    for(uint32_t i=0;i<mnistTestList.len;i+=1)
    {
        uint8_t result=KnnFit(&mnistTrainList,&mnistTestList.chars[i],7);
        if(result!=mnistTestList.chars[i].label)
            errorCount++;

        if((i+1)%100==0)
        {
            printf("Tested: %d Accuracy:%f\n",i+1,1-(double)errorCount/(i+1));
        }
    }
    printf("Test finished. Final accuracy: %f",1-(double)errorCount/mnistTestList.len);
    getchar();

    return 0;
}
