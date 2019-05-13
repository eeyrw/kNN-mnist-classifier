#include <stdio.h>
#include <stdint.h>
#include "MnistLoader.h"


uint32_t BgEndToLtlEnd_U32(uint32_t num)
{
    uint32_t swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
      ((num<<8)&0xff0000) | // move byte 1 to byte 2
      ((num>>8)&0xff00) | // move byte 2 to byte 1
      ((num<<24)&0xff000000); // byte 0 to byte 3
    return swapped;
}


MNIST_CHAR* MnistLoad(char* dataSetPath,char* dataLabelPath)
{
    FILE *imageFile;
    FILE *labelFile;
    MNIST_CHAR* charImages;

	imageFile=fopen(dataSetPath,"rb");
    labelFile=fopen(dataLabelPath,"rb");

	if (!imageFile || !labelFile)
	{
		printf("Unable to open file!");
		return -1;
	}

    // TRAINING SET LABEL FILE (train-labels-idx1-ubyte):
    // [offset] [type]          [value]          [description]
    // 0000     32 bit integer  0x00000801(2049) magic number (MSB first)
    // 0004     32 bit integer  60000            number of items
    // 0008     unsigned byte   ??               label
    // 0009     unsigned byte   ??               label
    // ........
    // xxxx     unsigned byte   ??               label
    // The labels values are 0 to 9.

    // TRAINING SET IMAGE FILE (train-images-idx3-ubyte):
    // [offset] [type]          [value]          [description]
    // 0000     32 bit integer  0x00000803(2051) magic number
    // 0004     32 bit integer  60000            number of images
    // 0008     32 bit integer  28               number of rows
    // 0012     32 bit integer  28               number of columns
    // 0016     unsigned byte   ??               pixel
    // 0017     unsigned byte   ??               pixel
    // ........
    // xxxx     unsigned byte   ??               pixel
    // Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

    uint8_t magicNumber[4];

    fread(magicNumber,1,sizeof(magicNumber),imageFile);
    if( magicNumber[0]!=0x00 ||
        magicNumber[1]!=0x00 ||
        magicNumber[2]!=0x08 ||
        magicNumber[3]!=0x03 )
    {
		printf("Invalid data set!");
		return NULL;
    }

    fread(magicNumber,1,sizeof(magicNumber),labelFile);
    if( magicNumber[0]!=0x00 ||
        magicNumber[1]!=0x00 ||
        magicNumber[2]!=0x08 ||
        magicNumber[3]!=0x01 )
    {
		printf("Invalid label set!");
		return NULL;
    }

    uint32_t imageNum,labelNum;

    fread(&imageNum,1,sizeof(uint32_t),imageFile);
    fread(&labelNum,1,sizeof(uint32_t),labelFile);
    imageNum=BgEndToLtlEnd_U32(imageNum);
    labelNum=BgEndToLtlEnd_U32(labelNum);

    if(imageNum!=labelNum)
    {
 		printf("Number of image don't fit the number of label!");
		return NULL;
    }

    uint32_t imageWidth,imageHeight;
    fread(&imageHeight,1,sizeof(uint32_t),imageFile);
    fread(&imageWidth,1,sizeof(uint32_t),imageFile);
    imageWidth=BgEndToLtlEnd_U32(imageWidth);
    imageHeight=BgEndToLtlEnd_U32(imageHeight);

    if(imageHeight!=CHAR_H || imageWidth!=CHAR_W)
    {
 		printf("Wrong size images!");
		return NULL;
    }

    charImages=malloc(sizeof(MNIST_CHAR)*imageNum);

    for(int32_t i=0;i<imageNum;i++)
    {
        fread(&charImages[i].label,1,sizeof(uint8_t),labelFile);
        fread(&charImages[i].pixels,1,CHAR_H*CHAR_W,imageFile);
    }

	fclose(imageFile);
    fclose(labelFile);
	return charImages;
}

int MnistFree(MNIST_CHAR* charImages)
{
    free(charImages);
}
