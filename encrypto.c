#include <stdio.h>
#include <stdlib.h>

/* Struc Definitions */
/**********************************************************************/
#pragma pack(push, 1)
typedef struct Pix
{
  unsigned char R;
  unsigned char G;
  unsigned char B;
}Pix_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct fileHeader
{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short int bfReserved1, bfReserved2;
    unsigned int bOffBits;
}fileHeader_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct Bitmap
{
    unsigned int Size;
    int Width;
    int Height;
    unsigned short int Planes;
    unsigned short int BitCount;
    unsigned int Compression;
    unsigned int SizeImage;
    int XPixelsPreMeter;
    int YPixelsPreMeter;
    unsigned int ColorsUsed;
    unsigned int ColorsImportant;
    struct Pix *pixels;
}Bitmap_t;
#pragma pack(pop)
/**********************************************************************/
/* Function Declarations */







/**********************************************************************/
int main(int argc, char *argv[])
{
  
    struct Bitmap source_info;
    struct fileHeader fileHeader_t;
    struct Pix source_pix;

    readFile();
    

int readFile()
{
    FILE *fp = fopen("inn.bmp","rb");
    FILE *Ofp = fopen("out.bmp","wb");

    if (fp==NULL)
    {
        printf("Error opening file.");
        return 1;
    }

    fread(&fileHeader_t, sizeof(fileHeader_t),1,fp);
    fread(&source_info, sizeof(Bitmap_t),1,fp);
}

int encodeFile()
{
    unsigned long int i=0;
    unsigned long int S=0;

    S=source_info.Width*source_info.Height;
    source_info.pixels = (struct Pix *) malloc(sizeof(struct Pix)*S);
}
/**********************************************************************/
    

    /*if(!(fp=fopen("inn.bmp","rb")))
    {
    printf("Error opening file.");
    exit(1);
    }

    Ofp=fopen("out.bmp","wb");*/

    /*fread(&fileHeader_t, sizeof(fileHeader_t),1,fp);
    fread(&source_info, sizeof(Bitmap_t),1,fp);*/

    S=source_info.Width*source_info.Height;
    source_info.pixels = (struct Pix *) malloc(sizeof(struct Pix)*S);

    for(i=1;i<=S;i++)
    {
        fread(&source_pix,sizeof(struct Pix),1,fp);
        if(i%2==0){
        source_pix.R = (source_pix.R  ^(254));
        source_pix.G = (source_pix.G  ^(254));
        source_pix.B = (source_pix.B  ^(254));
        }
        source_info.pixels[(i-1)^100] = source_pix;
    }

    fwrite(&fileHeader_t, sizeof(fileHeader_t),1,Ofp);
    fwrite(&source_info, sizeof(source_info),1,Ofp);

    for(i=1;i<=S;i++)
    {
        fwrite(&source_info.pixels[i-1],sizeof(struct Pix),1,Ofp);
    }
    fclose(fp);
    fclose(Ofp);
    printf("Encryption Complete.\n");
    return 0;
}

