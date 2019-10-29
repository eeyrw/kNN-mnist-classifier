#include <stdio.h>
#include "MnistLoader.h"
#include "kNN.h"
#include "bitmap_image.hpp"
#include "jpeg_decoder.h"


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

int recognize(MNIST_CHAR_LIST mnistTrainList,MNIST_CHAR &mnistChar)
{

        uint8_t result=KnnFit(&mnistTrainList,&mnistChar,3);
        return static_cast<int>(result);

}


int readImageToMnistChar(char* path,MNIST_CHAR &mnistChar)
{
    size_t size;
    unsigned char *buf;
    FILE *f;

    f = fopen(path, "rb");
    if (!f) {
        printf("Error opening the input file.\n");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    buf = (unsigned char*)malloc(size);
    fseek(f, 0, SEEK_SET);
    size_t read = fread(buf, 1, size, f);
    fclose(f);

    Jpeg::Decoder decoder(buf, size);
    if (decoder.GetResult() != Jpeg::Decoder::OK)
    {
        printf("Error decoding the input file\n");
        return 1;
    }

    printf("IsColor:%d W:%d H:%d\n", decoder.IsColor() ? 1 : 0, decoder.GetWidth(), decoder.GetHeight());
    //fwrite(decoder.GetImage(), 1, decoder.GetImageSize(), f);
    if(decoder.IsColor())
    {
        unsigned char* image=decoder.GetImage();
        int j=0;
        for(int i=0;i<decoder.GetImageSize();i+=3)
        {

            mnistChar.pixels[j]=image[i];
            j++;
        }
    }
    else
        memcpy(mnistChar.pixels,decoder.GetImage(),28*28);
    fclose(f);

}
int main(void)
{
    MNIST_CHAR_LIST mnistTrainList;
    MNIST_CHAR_LIST mnistTestList;
    mnistTrainList=MnistLoad("./dataSet/train-images.idx3-ubyte","./dataSet/train-labels.idx1-ubyte");
    mnistTestList=MnistLoad("./dataSet/t10k-images.idx3-ubyte","./dataSet/t10k-labels.idx1-ubyte");


//    double acc_k1=Evaluate(mnistTrainList,mnistTestList,1);
//    double acc_k3=Evaluate(mnistTrainList,mnistTestList,3);
//    double acc_k5=Evaluate(mnistTrainList,mnistTestList,5);
//    double acc_k9=Evaluate(mnistTrainList,mnistTestList,9);
//
//    printf("Acc K=1: %f, Acc K=3: %f, Acc K=5: %f, Acc K=9: %f\n",acc_k1,acc_k3,acc_k5,acc_k9);



    MNIST_CHAR mnistChar;
    char path[1024];
    while(true)
    {
        printf("Please input your handwriting image path:\n");
        gets(path);
      readImageToMnistChar(path,mnistChar);
    auto result = recognize(mnistTrainList,mnistChar);
    printf("Your number is: %d\n",result);

    }


    getchar();

    return 0;
}
