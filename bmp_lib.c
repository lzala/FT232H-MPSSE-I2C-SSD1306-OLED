#include "bmp_lib.h"

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    
    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL) {
      printf("Couldn't open file %s\n", filename);
      return NULL;
    }
  
    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42) {
      printf("Expected 0x4d42, found: %x\n", bitmapFileHeader.bfType);
      printf("File is not a bmp\n");
      fclose(filePtr);
      return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage) {
      printf("Error 2\n");
      free(bitmapImage);
      fclose(filePtr);
      return NULL;
    }
  
    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);
  
    //make sure bitmap image data was read
    if (bitmapImage == NULL) {
      printf("Error 3\n");
      fclose(filePtr);
      return NULL;
    }
  
  // for(imageIdx=0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=3){
  //   //tft_writeColor(bitmapImage[imageIdx+2], bitmapImage[imageIdx+1], bitmapImage[imageIdx]);
  // }

  //this is the image in bytes
  for(imageIdx=0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx+=1){
    //printf("%u ", bitmapImage[imageIdx]);
  }

  //printf("\n size %u \n", bitmapInfoHeader->biSizeImage);
  //printf("Bit Count %u \n", bitmapInfoHeader->biBitCount);

  //close file and return bitmap iamge data
  fclose(filePtr);
  return bitmapImage;
}