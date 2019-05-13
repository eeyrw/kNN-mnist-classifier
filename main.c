#include <stdio.h>
#include "MnistLoader.h"

int main(void)
{
    MNIST_CHAR_LIST mnistTrainList;
    MNIST_CHAR_LIST mnistTestList;
    mnistTrainList=MnistLoad("./dataSet/train-images.idx3-ubyte","./dataSet/train-labels.idx1-ubyte");
    mnistTestList=MnistLoad("./dataSet/t10k-images.idx3-ubyte","./dataSet/t10k-labels.idx1-ubyte");

    return 0;
}
