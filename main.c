#include <stdio.h>
#include "MnistLoader.h"
#include "kNN.h"


double Evaluate(MNIST_CHAR_LIST mnistTrainList,MNIST_CHAR_LIST mnistTestList,int kNb)
{
    uint32_t errorCount=0;
    printf("Start evaluating kNN with k=%d.\n",kNb);
    for(uint32_t i=0;i<mnistTestList.len;i+=1)
    {
        uint8_t result=KnnFit(&mnistTrainList,&mnistTestList.chars[i],kNb);
        if(result!=mnistTestList.chars[i].label)
            errorCount++;

        if((i+1)%1000==0)
        {
            printf("Tested: %d Accuracy:%f\n",i+1,1-(double)errorCount/(i+1));
        }
    }
    printf("Test finished. Final accuracy: %f",1-(double)errorCount/mnistTestList.len);
    return (1-(double)errorCount/mnistTestList.len);
}

int main(void)
{
    MNIST_CHAR_LIST mnistTrainList;
    MNIST_CHAR_LIST mnistTestList;
    mnistTrainList=MnistLoad("./dataSet/train-images.idx3-ubyte","./dataSet/train-labels.idx1-ubyte");
    mnistTestList=MnistLoad("./dataSet/t10k-images.idx3-ubyte","./dataSet/t10k-labels.idx1-ubyte");


    double acc_k1=Evaluate(mnistTrainList,mnistTestList,1);
    double acc_k3=Evaluate(mnistTrainList,mnistTestList,3);
    double acc_k5=Evaluate(mnistTrainList,mnistTestList,5);
    double acc_k9=Evaluate(mnistTrainList,mnistTestList,9);

    printf("Acc K=1: %f, Acc K=3: %f, Acc K=5: %f, Acc K=9: %f\n",acc_k1,acc_k3,acc_k5,acc_k9);

    getchar();

    return 0;
}
