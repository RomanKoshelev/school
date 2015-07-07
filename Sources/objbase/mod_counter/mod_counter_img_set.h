/******************************************************************************
* File name:   image_set.h
*
* Version:     1.1
*
* Author:      Dima Polyakov <dima_twin@mtu-net.ru>
*
* Purpose:     GIF->RGB, GRB->GIF routines
*
*
* Created:     13 March, 2000
*
* Last update: 16 March, 2000 by Dima Polyakov
*******************************************************************************/

#ifndef __GIF_RGB_IMAGE_ROUTINES__
#define __GIF_RGB_IMAGE_ROUTINES__

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

#include "mod_counter_dp_img.h"

#ifdef SIGNED_COMPARE_SLOW
	typedef unsigned long int count_int;
	typedef unsigned short int count_short;
#else /*SIGNED_COMPARE_SLOW*/
	typedef long int          count_int;
#endif /*SIGNED_COMPARE_SLOW*/

#define GIF_STAMP					"GIFVER"	 /* First chars in file - GIF stamp. */
#define GIF_STAMP_LEN			sizeof(GIF_STAMP) - 1
#define GIF_VERSION_POS			3		/* Version first character in stamp. */

#define LZ_MAX_CODE	4095		/* Biggest code possible in 12 bits. */
#define LZ_BITS		12

#define NO_SUCH_CODE		4098    /* Impossible code, to signal empty. */

#define	GIF_ERROR	0
#define	GIF_OK		1

typedef struct GifColorType
{
	unsigned char Red, Green, Blue;
} GifColorType;

typedef struct GifFileType
{
	short SWidth, SHeight,                     /* Screen dimensions. */
		SColorResolution, SBitsPerPixel,        /* How many colors can we generate? */
		SBackGroundColor,                       /* I hope you understand this one... */
		ILeft, ITop, IWidth, IHeight,           /* Current image dimensions. */
		IInterlace,                             /* Sequential/Interlaced lines. */
		IBitsPerPixel;                          /* How many colors this image has? */
		GifColorType *SColorMap, *IColorMap;    /* NULL if not exists. */
		void *Private;                          /* The regular user should not mess with this one! */
} GifFileType;

typedef enum
{
	UNDEFINED_RECORD_TYPE,
	SCREEN_DESC_RECORD_TYPE,
	IMAGE_DESC_RECORD_TYPE,				   /* Begin with ',' */
	EXTENSION_RECORD_TYPE,				   /* Begin with '!' */
	TERMINATE_RECORD_TYPE				   /* Begin with ';' */
} GifRecordType;

#define	GIF2RGB_ERR_OPEN_FAILED			101		/* And GIF2RGB_ possible errors. */
#define	GIF2RGB_ERR_READ_FAILED			102
#define	GIF2RGB_ERR_NOT_GIF_FILE		103
#define	GIF2RGB_ERR_NO_SCRN_DSCR		104
#define	GIF2RGB_ERR_NO_IMAG_DSCR		105
#define	GIF2RGB_ERR_NO_COLOR_MAP		106
#define	GIF2RGB_ERR_WRONG_RECORD		107
#define	GIF2RGB_ERR_DATA_TOO_BIG		108
#define	GIF2RGB_ERR_NOT_ENOUGH_MEM		109
#define	GIF2RGB_ERR_CLOSE_FAILED		110
#define	GIF2RGB_ERR_NOT_READABLE		111
#define	GIF2RGB_ERR_IMAGE_DEFECT		112
#define	GIF2RGB_ERR_EOF_TOO_SOON		113

typedef struct GifFilePrivateType
{
	short FileState,
		BitsPerPixel,                  /* Bits per pixel (Codes uses at list this + 1). */
		ClearCode,                     /* The CLEAR LZ code. */
		EOFCode,                       /* The EOF LZ code. */
		RunningCode,                   /* The next code algorithm can generate. */
		RunningBits,                   /* The number of bits required to represent RunningCode. */
		MaxCode1,                      /* 1 bigger than max. possible code, in RunningBits bits. */
		LastCode,                      /* The code before the current code. */
		CrntCode,                      /* Current algorithm code. */
		StackPtr,                      /* For character stack (see below). */
		CrntShiftState;                /* Number of bits in CrntShiftDWord. */
	unsigned long CrntShiftDWord,     /* For bytes decomposition into codes. */
		PixelCount;		                /* Number of pixels in image. */
	char *File;                       /* File as stream. */
	long cpos;
	long flength;
	unsigned char Buf[256];	          /* Compressed input is buffered here. */
	unsigned char Stack[LZ_MAX_CODE];   /* Decoded pixels are stacked here. */
	unsigned char Suffix[LZ_MAX_CODE+1];/* So we can trace the codes. */
	unsigned short Prefix[LZ_MAX_CODE+1];
} GifFilePrivateType;

#define tab_prefixof(i) CodeTabOf(i)
#define tab_suffixof(i)        ((char_type*)(htab))[i]
#define de_stack	       ((char_type*)&tab_suffixof((code_int)1<<BITS))

#ifdef COMPATIBLE		// But wrong!
# define MAXCODE(n_bits)	((int) 1 << (n_bits) - 1)
#else
# define MAXCODE(n_bits)	(((int) 1 << (n_bits)) - 1)
#endif

#define HashTabOf(i)	   htab[i]
#define CodeTabOf(i)	codetab[i]

#define BITS	12
#define HSIZE  5003	       // 80% occupancy

#ifdef NO_UCHAR
 typedef char	char_type;
#else
 typedef	unsigned char	char_type;
#endif

typedef struct
{
	long m_width;
	long m_height;

	unsigned char * data;
}RGBIMAGE;

typedef struct
{
	long data_len;
	unsigned char * data;
}GIFIMAGE;

#define TRANSPARENT_SET		0x01
#define REPLACE_COLOR_SET	0x02

typedef struct
{
	char mask;

	// прозрачные цвета в источнике
	unsigned char transp_r;
	unsigned char transp_g;
	unsigned char transp_b;

	// какие цвета заменить в источнике
	unsigned char replace_r;
	unsigned char replace_g;
	unsigned char replace_b;

	// на какие цвета заменить в источнике
	unsigned char replace_by_r;
	unsigned char replace_by_g;
	unsigned char replace_by_b;
}MERGE_COLOR;

//-------------------------------------------------------------------------[]
// FUNCTIONS:
//-------------------------------------------------------------------------[]

// load gif
int GIF2RGB_LoadGifFile(RGBIMAGE *img, char *file_name);
int GIF2RGB_LoadGifFromMemory(RGBIMAGE *img, unsigned char *file, int file_size);

// Create gif
int RGB2GIF(RGBIMAGE *rgb, GIFIMAGE *gif);

// convert gif file to RGB
int GIF2RGB();

short GIF2RGB_PrepareGif(int);

int Merge(RGBIMAGE *img, RGBIMAGE *img_src, int x, int y);
int MergeEx(RGBIMAGE *img, RGBIMAGE *img_src, int x_dest, int y_dest, int src_x, int src_y, int src_w, int src_h, MERGE_COLOR *mc);

//--------------------------------------------------------------------------------[]
// GIF2RGB FUNCTIONS
//--------------------------------------------------------------------------------[]
void  GIF2RGB_SetPoint (RGBIMAGE *img, int , int , int );
short GIF2RGB_GetScreenDesc(GifFileType *);
short GIF2RGB_GetRecordType(GifRecordType *);
short GIF2RGB_GetImageDesc(GifFileType *);
short GIF2RGB_GetLine(GifFileType *, unsigned char *, short );
short GIF2RGB_GetPixel(GifFileType *, unsigned char);
short GIF2RGB_GetExtension(GifFileType *, short *, unsigned char **);
short GIF2RGB_GetExtensionNext(GifFileType *, unsigned char **);
short GIF2RGB_CloseFile(GifFileType *);
short GIF2RGB_GetWord(char *, short *);
short GIF2RGB_GetCode(GifFileType *, short *, unsigned char **);
short GIF2RGB_GetCodeNext(GifFileType *, unsigned char **);
short GIF2RGB_SetupDecompress(GifFileType *);
short GIF2RGB_DecompressLine(GifFileType *, unsigned char *,short);
short GIF2RGB_GetPrefixChar(unsigned short *, short, short );
short GIF2RGB_GetLZCodes(GifFileType *, short *);
short GIF2RGB_DecompressInput(GifFilePrivateType *, short *);
short GIF2RGB_BufferedInput(char * , unsigned char *, unsigned char *);
long GIF2RGB_ffread(unsigned char *,int,int,char *);

//--------------------------------------------------------------------------------[]
// RGB2GIF FUNCTIONS
//--------------------------------------------------------------------------------[]
int RGB2GIF_AddToPalette(unsigned char r, unsigned char g, unsigned char b);
int RGB2GIF_Write2ImageEx(void *data, int len);
int RGB2GIF_Write2Image(unsigned char data);
void RGB2GIF_GIFEncode(int GInterlace, unsigned char Background, int Transparent);

// Set up the 'byte output' routine
void RGB2GIF_char_init();

// Add a character to the end of the current packet, and if it is 254
// characters, flush the packet to disk.
void RGB2GIF_char_out( int c );

// Flush the packet to disk, and reset the accumulator
void RGB2GIF_flush_char();

void RGB2GIF_compress(int init_bits );
void RGB2GIF_output( int code );
void RGB2GIF_cl_block ();		/* table clear for block compress */
void RGB2GIF_cl_hash(register count_int hsize);		/* reset code table */
void RGB2GIF_Putword(int w );
int RGB2GIF_GIFNextPixel();

// Bump the 'curx' and 'cury' to point to the next pixel
void RGB2GIF_BumpPixel();

void *malloc_ex(long size);
void free_ex(void *t);
int get_memory_allocation_counter();

//--------------------------------------------------------------------------------[]
// STRUCT INTERFACE FUNCTIONS
//--------------------------------------------------------------------------------[]

// free RGBIMAGE struct
void FreeImage_RGB(RGBIMAGE *rgb_img);

// free GIFIMAGE struct
void FreeImage_GIF(GIFIMAGE *gif_img);

// make RGB from GIF
int MakeImage_RGB(GIFIMAGE *gif_img, RGBIMAGE *rgb_img);

// make GIF from RGB
int MakeImage_GIF(RGBIMAGE *rgb_img, GIFIMAGE *gif_img);

/***********************************************************************************
*
*                        INTERFACE EXTENDED
*
* RGB_EX:
*  long screen_width
*  long screen_height
*  unsigned char r
*  unsigned char g
*  unsigned char b
*  ...
*  full size = screen_width * screen_height * 3
************************************************************************************/

// make RGB_EX from GIF
int MakeImage_RGB_EX(char *gif_file_data,             // <- образ GIF файла
							int gif_file_data_len,           // <- размер GIF образа
							unsigned char **rgb_data_ex,     // -> образ RGB_EX изображения
							int *rgb_data_ex_len					// -> длина RGB_EX изображения
							);

// free rgb_data_ex
void FreeImage_RGB_EX(unsigned char **rgb_data_ex);

// make GIF from RGB_EX
int MakeImage_GIF_EX(char *rgb_data_ex,					// <- образ RGB_EX изображения
							unsigned char **gif_data,			// -> указатель на полученный GIF образ
							int *gif_len);							// -> размер GIF образа

// free gif_data
void FreeImage_GIF_EX(unsigned char **gif_data);

// dublicate RGB image
int DublicateRGBImage(RGBIMAGE *rgb, RGBIMAGE *new_rgb);

// replace RGB color for a new RGB color
int ReplaceRGBColor(RGBIMAGE *rgb, unsigned char r0, unsigned char g0, unsigned char b0, unsigned char r, unsigned char g, unsigned char b);

#endif //__GIF_RGB_IMAGE_ROUTINES__
