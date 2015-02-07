/**-------------------------/// bmp \\\---------------------------
 *
 * <b>bmp pics head</b>
 * @version : 1.0
 * @since : 2015  2月 07
 *
 * @description :
 *     To produce bmp pictures.
 * @usage :
 *
 * @author : 'Jiahui Yu' | yjh199511 ^_^ gmail.com
 * @copyright 
 * @TODO :
 *
 *--------------------------\\\ bmp ///---------------------------*/

#include "bmp.h"

TBMP::TBMP(const char *filename, int w, int h, int mode){
#ifdef BMP_TEST
	char bufferc[4];
	/* char ch = 255; */
	unsigned long  buffer4;
	unsigned short buffer2;
	
	fp = fopen(filename, "wb");
	if (fp == NULL) printf("!!");
	W = w;
	H = h;
	MODE = mode%2;
	if (W%4!=0) W=(W/4+1)*4;
	
	int i, j;
	bitmap = (char **)malloc(H * sizeof(char *));
	if (bitmap == NULL) printf("00");
	for(i=0; i<H; i++){
         bitmap[i] = (char *)malloc(W * sizeof(char));
         assert(bitmap[i]!=NULL);
	}
	for (j=0; j<H; j++)
	for (i=0; i<W; i++){
	    bitmap[j][i] = 255;
	}

	//bitmap-file header (14 Bytes)
	fwrite("BM", 1, 2, fp);     //0000h 2 bfType
	buffer4 = W*H + 1078;
	fwrite(&buffer4, 4, 1, fp);	//0002h 4 bfSize
	buffer4 = 0;
	fwrite(&buffer4, 1, 4, fp);  //0006h 4 bfReserved
	buffer4 = 1078;
	fwrite(&buffer4, 4, 1, fp);	//000Ah 4 bfOffbits

	//bitmap-information header (40 Bytes)
	buffer4 = 0x28;
	fwrite(&buffer4, 4, 1, fp); //000Eh 4 biSize
	buffer4 = W;
	fwrite(&buffer4, 4, 1, fp); //0012h 4 biWidth
	buffer4 = H;
	fwrite(&buffer4, 4, 1, fp); //0016h 4 biHeight
	buffer2 = 1;
	fwrite(&buffer2, 2, 1, fp); //001Ah 2 biPlanes
	buffer2 = 8;
	fwrite(&buffer2, 2, 1, fp); //001Ch 2 biBitCount (8bit 256色)
	buffer4 = 0;
	fwrite(&buffer4, 4, 1, fp); //001Eh 4 biCompression
	buffer4 = 0;
	fwrite(&buffer4, 4, 1, fp); //0022h 4 biSizeImage
	buffer4 = 0;
	fwrite(&buffer4, 4, 1, fp); //0026h 4 biXPelsPerMeter
	buffer4 = 0;
	fwrite(&buffer4, 4, 1, fp); //002Ah 4 biYPelsPerMeter
	buffer4 = 256;
	fwrite(&buffer4, 4, 1, fp); //002Eh 4 biClrUsed (256色调色板)
	buffer4 = 256;
	fwrite(&buffer4, 4, 1, fp); //0032h 4 biClrImportant (256个重要颜色索引)
	
	//color table (1024 Bytes)
	bufferc[3] = 0;
	for (i=0; i<256; i++){
		bufferc[0] = i;
		bufferc[1] = i;
		bufferc[2] = i;
		fwrite(bufferc, 1, 4, fp);
	}
#endif
}

TBMP::~TBMP(){
#ifdef BMP_TEST
	//data (W*H Bytes)
	for (int j=H-1; j>=0; j--)
		fwrite(bitmap[j], 1, W, fp);
	fclose(fp);
	//realease resources
#endif
}

int TBMP::setcolor(int grey){
#ifdef BMP_TEST
	if (grey<0 || grey>255)
		return 1;

	Grey = grey;
	return 0;
#endif
}

int TBMP::drawpoint(int x, int y){
#ifdef BMP_TEST
	if (!checkborder(x,y))
		return 1;
		
	if (MODE)
		bitmap[H-1-y][x] = Grey;
	else
		bitmap[y][x] = Grey;
	return 0;
#endif
}

int TBMP::drawline(int x0, int y0, int x1, int y1){
#ifdef BMP_TEST
	if (!checkborder(x0, y0) || !checkborder(x1, y1))
		return 1;
	if (x0==x1 && y0==y1)
	    return drawpoint(x0, y0);
	
	int xs, ys, xe, ye;
	int i, j;
	double t;
	if (abs(x0-x1) >= abs(y0-y1)){
		if (x0 < x1){
			xs = x0;
			ys = y0;
			xe = x1;
			ye = y1;
		}
		else{
			xs = x1;
			ys = y1;
			xe = x0;
			ye = y0;
		}
		t = (double)(ye - ys) / (double)(xe - xs);
		for (i=xs; i<=xe; i++){
			j = (int)((i - xs) * t + ys);
			drawpoint(i,j);
			//bitmap[j][i] = Grey;
		}
	}
	else{
		if (y0 < y1){
			xs = x0;
			ys = y0;
			xe = x1;
			ye = y1;
		}
		else{
			xs = x1;
			ys = y1;
			xe = x0;
			ye = y0;
		}
		t = (double)(xe - xs) / (double)(ye - ys);
		for (j=ys; j<=ye; j++){
			i = (int)((j-ys) * t + xs);
			drawpoint(i,j);
			//bitmap[j][i] =Grey;
		}
	}
	return 0;
#endif
}

int TBMP::drawrect(int x0, int y0, int x1, int y1){
#ifdef BMP_TEST
	return drawline(x0, y0, x0, y1) || drawline(x0, y0, x1, y0) \
	|| drawline(x1, y0, x1, y1) || drawline(x0, y1, x1, y1);
#endif
}
