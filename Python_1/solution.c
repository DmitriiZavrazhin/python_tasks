#include<stdio.h>
#include<stdlib.h>
#define BPP 8
#define CTS 4

#pragma pack(push, 1)                                                                                         
typedef struct{                                                                                               
        unsigned short signature;                                                                                     
        unsigned int   fileSize;                                                                              
        unsigned short reserved1;                                                                             
        unsigned short reserved2;                                                                             
        unsigned int   offset;                                                                                
} FileHeader;                                                                                                 
                                                                                  
typedef struct{                                                                   
        unsigned int   size;                                                      
        unsigned int   width;                                                     
        unsigned int   height;                                                    
        unsigned short planeNumber;                                               
        unsigned short bitsPerPixel;                                              
        unsigned int   compression;                                               
        unsigned int   imgSize;                                                   
        unsigned int   xPixelPerMeter;                                            
        unsigned int   yPixelPerMeter;                                            
        unsigned int   ctColourCount;                                             
        unsigned int   importantColourCount;                                      
} DataHeader;                                                                    
                                                                                                                                                                        
typedef struct{
        unsigned char  blue;
        unsigned char  green;
        unsigned char  red;
        unsigned char  reserved;
} ctentry_t;
#pragma pack(pop)                                                                

typedef struct{
        FileHeader     fheader;
        DataHeader     dheader;
        ctentry_t      colours[4];
        unsigned char**bitmap;
        int            padding;
} bmp_t;


void allocBMP(bmp_t* bmp)
{
        bmp->bitmap = calloc(bmp->dheader.height,sizeof(unsigned char*));
        for(int i = 0; i < bmp->dheader.height; i++)
                bmp->bitmap[i] = calloc(bmp->dheader.width, sizeof(unsigned char));
}

void freeBMP(bmp_t* bmp)
{
        for(int i = 0; i < bmp->dheader.height; i++)
                free(bmp->bitmap[i]);
        free(bmp->bitmap);
        free(bmp);
}

bmp_t* createBMP(int width, int height)
{
	ctentry_t black = {0, 0, 0, 0x00};
	ctentry_t red = {0, 0, 255, 0x00};
	ctentry_t green = {0, 255, 0, 0x00};
	ctentry_t yellow = {0, 255, 255, 0x00};
    bmp_t* bmp = calloc(1, sizeof(bmp_t));
	FileHeader fheader = {0x4d42, 0, 0,  0, sizeof(FileHeader) + sizeof(DataHeader) + CTS * sizeof(ctentry_t)};
	bmp->fheader = fheader;
	DataHeader dheader = {sizeof(DataHeader), width, height, 1, 8, 0, width * height, 0x0ec4, 0x0ec4, 4, 4}; //7873
	bmp->dheader = dheader;
	bmp->colours[0] = black;
	bmp->colours[1] = red;
	bmp->colours[2] = green;
	bmp->colours[3] = yellow;
	allocBMP(bmp);
    int pitch = bmp->dheader.width;
    if(pitch %4 != 0)
        pitch += 4 - pitch % 4;
    bmp->padding = pitch - bmp->dheader.width;
    /*if(bmp->padding)
        bmp->padding = 4 - bmp->padding;*/
	int h = bmp->dheader.height / 5;
	int w = bmp->dheader.width / 5;
        for(int i = 0; i < bmp->dheader.height; i++)
        {
            for(int j = 0; j < bmp->dheader.width; j++)
                    if(i     > h && i     < 2 * h &&
                       j     > w && j     < 4 * w)
                        bmp->bitmap[i][j] += 2;
                    else if(i     > 3 * h && i < 4 * h &&
                            j     > w     && j < 2 * w)
                        bmp->bitmap[i][j] += 1;
                    else if(i     > 3 * h && i < 4 * h && 
                            j     > 3 * w && j < 4 * w)
                        bmp->bitmap[i][j] += 3;
                /*else
                    bmp->bitmap[i][j/4] += 0 << j % 4;*/
        }
	return bmp;
}

void writeBMP(char* filename, bmp_t* bmp)
{
        FILE* out = fopen(filename, "w");
        int zero = 0;
        fwrite(&bmp->fheader, sizeof(bmp->fheader), 1,   out);
        fwrite(&bmp->dheader, sizeof(bmp->dheader), 1,   out);
        fwrite(&bmp->colours, sizeof(ctentry_t),    CTS, out);
        for(int i = 0; i < bmp->dheader.height; i++)
        {
                for(int j = 0; j < bmp->dheader.width; j ++)
                        fwrite(&bmp->bitmap[i][j], sizeof(unsigned char), 1, out);
                fwrite(&zero, bmp->padding, 1, out);
        }
        fclose(out);
}

int main()
{
        bmp_t* bmp = createBMP(50, 50);
        writeBMP("output.bmp", bmp);
        freeBMP(bmp);
        return 0;
}
