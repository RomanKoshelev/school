/******************************************************************************
* File name:   mod_counter_image_set.c
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
* Last update: 17 March, 2000 by Dima Polyakov
*******************************************************************************/

#include "mod_counter_img_set.h"
#include "mod_counter_dp_img.h"

/**************************************************************************
                            GLOBAL VARIABLES
**************************************************************************/

//-------------------------------------------------------------------------[]
// GIF to RGB
//-------------------------------------------------------------------------[]

// error description
static short _GifError;

// gif header
static GifFileType *GifFile;

// file in memory
static char * GifImageMap = 0;

//-------------------------------------------------------------------------[]
// RGB to GIF
//-------------------------------------------------------------------------[]

// 8 bit (index color dim)
static unsigned char *data_ind = 0;

// data for file writing (virtual file)
static unsigned char *data_file = 0;

// used colors in pallete table, MAX = 256
static int used_colors = 0;

// in virtual gif-file current position
static long mem_file_pos = 0;

// Color table
static unsigned char color_table[256*3];

// Number of characters so far in this 'packet'
static int a_count;

// Define the storage for the packet accumulator
static char accum[256];

static int image_real_width = 0;
static int image_real_height = 0;

static int curx, cury;
static long CountDown;
static int Pass = 0;
static int Interlace;

static int n_bits;			  // number of bits/code
static int maxbits = BITS;		  // user settable max # bits/code
static int maxcode;		  // maximum code, given n_bits
static int maxmaxcode = (int) 1 << BITS; // should NEVER generate this code

static count_int htab [HSIZE];
static unsigned short codetab [HSIZE];

static int hsize = HSIZE; //for dynamic table sizing

static int free_ent = 0; // first unused entry

// block compression parameters -- after all codes are used up,
// and compression rate changes, start over.
static int clear_flg = 0;

static int offset;
static long int in_count = 1;		 // length of input
static long int out_count = 0;	 // # of codes output (for debugging)

//compress

static int g_init_bits;

static int ClearCode;
static int EOFCode;

static unsigned long cur_accum = 0;
static int cur_bits = 0;

static unsigned long masks[] = {
	0x0000, 0x0001, 0x0003, 0x0007, 0x000F,
	0x001F, 0x003F, 0x007F, 0x00FF,
	0x01FF, 0x03FF, 0x07FF, 0x0FFF,
	0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

//----------------------------------------------------------------------------[]
// FUNCTIONS
//----------------------------------------------------------------------------[]

int GIF2RGB_LoadGifFile(RGBIMAGE *img, char *fName)
{
	FILE *f;
	int gif_file_len = 0;
	int return_value = 0;

	if(!img) return 0;

	f=fopen(fName,"rb");
	if(!f)
	{
		_GifError=GIF2RGB_ERR_OPEN_FAILED;
		goto EXIT;
	}
	fseek(f,0,SEEK_END);
	gif_file_len = ftell(f);

	fseek(f,0,SEEK_SET);
	GifImageMap = (char *)malloc_ex(gif_file_len);
	if(!GifImageMap)
	{
		_GifError=GIF2RGB_ERR_NOT_ENOUGH_MEM;
		goto EXIT;
	}
	if(fread(GifImageMap, 1, gif_file_len, f) != (unsigned int)gif_file_len)
	{
		_GifError=GIF2RGB_ERR_READ_FAILED;
		goto EXIT;
	}
	fclose(f);

	if(GIF2RGB_PrepareGif(gif_file_len) == GIF_OK)
	{
		img->m_width = GifFile->SWidth;
		img->m_height = GifFile->SHeight;
		img->data = 0;

		if(img->m_width <= 0 || img->m_height <= 0)
		goto EXIT;

		_GifError=0;

		if(GIF2RGB(img))
		{
			if(GifImageMap)
				GIF2RGB_CloseFile(GifFile);
			GifImageMap = 0;
			return_value = 1;
		}
	}

EXIT:
	if(GifImageMap)
		GIF2RGB_CloseFile(GifFile);
	GifFile = 0;

	return return_value;
}

// Load GIF from memory
int GIF2RGB_LoadGifFromMemory(RGBIMAGE *img, unsigned char *file, int file_size)
{
	int return_value = 0;

	if(!img || !file || file_size<=0) return 0;

	GifImageMap = (char *) malloc_ex(file_size);

	if(!GifImageMap) return 0;

	memcpy(GifImageMap, file, file_size);

	if(GIF2RGB_PrepareGif(file_size) == GIF_OK)
	{
		img->m_width = GifFile->SWidth;
		img->m_height = GifFile->SHeight;
		img->data = 0;

		if(img->m_width <= 0 || img->m_height <= 0)
			goto EXIT;

		_GifError=0;

		if(GIF2RGB(img))
		{
			if(GifImageMap)
				GIF2RGB_CloseFile(GifFile);
			GifImageMap = 0;
			return_value = 1;
		}
	}

EXIT:
	if(GifImageMap)
		GIF2RGB_CloseFile(GifFile);
	GifFile = 0;

	return return_value;
}

void GIF2RGB_SetPoint(RGBIMAGE *img, int row, int col, int colorindex)
{
	int offset;
	unsigned char *buffer;
	GifColorType *ColorMap;

	offset = (img->m_width * row + col) * 3;
	buffer = img->data;
	ColorMap = (GifFile->IColorMap ? GifFile->IColorMap : GifFile->SColorMap);

	buffer += offset;
	buffer[0] = ColorMap[colorindex].Red;
	buffer[1] = ColorMap[colorindex].Green;
	buffer[2] = ColorMap[colorindex].Blue;
}

// return 0 if error else return 1
int GIF2RGB(RGBIMAGE *img)
{
	int    row,col;
	short  i, j, Row, Col, Width, Height, ExtCode, Count;
	GifRecordType RecordType;
	unsigned char *Extension;
	short InterlacedOffset[] = { 0, 4, 2, 1 }, // The way Interlaced image should.
	InterlacedJumps[]  = { 8, 8, 4, 2 }; // be read - offsets and jumps...
	unsigned char OnePictureLine[1024*10];// maximum width of the one line in pixels
	long m_image_size;

	if(!img) return 0;

	m_image_size = img->m_width * img->m_height * 3;

	if(!m_image_size) return 0;

	_GifError=0;

	if(img->data) free_ex(img->data);

	img->data = (unsigned char *)malloc_ex(m_image_size);
	if(!img->data)
	{
		_GifError=GIF2RGB_ERR_NOT_ENOUGH_MEM;
		return 0;
	}

	for(row=0; row < img->m_height; row++)
		for(col=0; col < img->m_width; col++)
			GIF2RGB_SetPoint(img, row, col, GifFile->SBackGroundColor);
//	memset(data, 0, m_image_size);

	do
	{
		if(GIF2RGB_GetRecordType(&RecordType) == GIF_ERROR)
		{
			if(img)
			{
				free_ex(img->data);
				img->data = 0;
			}
			return 0;
		}
		switch (RecordType)
		{
		case IMAGE_DESC_RECORD_TYPE:
			if(GIF2RGB_GetImageDesc(GifFile) == GIF_ERROR)
			{
				free_ex(img->data);
				img->data = 0;
				return 0;
			}
			Row = GifFile->ITop; // Image Position relative to Screen.
			Col = GifFile->ILeft;
			Width = GifFile->IWidth;
			Height = GifFile->IHeight;
			if(GifFile->ILeft + GifFile->IWidth > GifFile->SWidth || GifFile->ITop + GifFile->IHeight > GifFile->SHeight)
			{
				free_ex(img->data);
				img->data = 0;
				return 0;
			}
			if(GifFile->IInterlace)
			{
				// Need to perform 4 passes on the images:
				for(Count=i=0; i<4; i++)
					for(j=Row+InterlacedOffset[i]; j<Row+Height; j+=InterlacedJumps[i])
					{
						if(GIF2RGB_GetLine(GifFile,OnePictureLine,Width)==GIF_ERROR)
						{
							free_ex(img->data);
							img->data = 0;
							return 0;
						}
						for (col=Col;col<(Col+Width);col++)
							GIF2RGB_SetPoint(img, j, col, OnePictureLine[col-Col]);
					}
			}
			else
			{
				for(i=0; i<Height; i++)
				{
					if(GIF2RGB_GetLine(GifFile,OnePictureLine,Width)==GIF_ERROR)
					{
						free_ex(img->data);
						img->data = 0;
						return 0;
					}
					for(col=Col; col<(Col+Width); col++)
						GIF2RGB_SetPoint(img, Row, col, OnePictureLine[col-Col]);
					Row++;
				}
			}
			break;
		case EXTENSION_RECORD_TYPE:
			// Skip any extension blocks in file:
			if(GIF2RGB_GetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR)
			{
				free_ex(img->data);
				img->data = 0;
				return 0;
			}
			while (Extension != NULL)
			{
				if(GIF2RGB_GetExtensionNext(GifFile, &Extension) == GIF_ERROR)
				{
					free_ex(img->data);
					img->data = 0;
					return 0;
				}
			}
			break;
		case TERMINATE_RECORD_TYPE:
			break;
		default:                // Should be traps by GIF2RGB_GetRecordType.
			break;
		}
	} while (RecordType != TERMINATE_RECORD_TYPE);

	return 1;
}

long GIF2RGB_ffread(unsigned char *buff, int isize, int icnt, char *from)
{
	int     toread;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	toread=isize*icnt;
	if((Private->cpos+toread) > Private->flength)
		toread=Private->flength-Private->cpos;
	memcpy(buff,Private->File+Private->cpos,toread);
	Private->cpos+=toread;
	return(toread);
}

short GIF2RGB_PrepareGif(int len)
{
	char Buf[GIF_STAMP_LEN+1];
	GifFilePrivateType *Private;

	if(GifFile)
	{
		if(GifFile->Private)
			free_ex(GifFile->Private);
		free_ex(GifFile);
	}

	if((GifFile=(GifFileType *)malloc_ex(sizeof(GifFileType))) == NULL)
	{
		_GifError = GIF2RGB_ERR_NOT_ENOUGH_MEM;
		return GIF_ERROR;
	}

	if((Private=(GifFilePrivateType *)malloc_ex(sizeof(GifFilePrivateType))) == NULL)
	{
		_GifError = GIF2RGB_ERR_NOT_ENOUGH_MEM;
		free_ex((char *)GifFile);
		return 0;
	}
	GifFile->Private = (void *) Private;
	GifFile->SColorMap = GifFile->IColorMap = NULL;
	Private->File = GifImageMap;
	Private->cpos = 0;
	Private->flength = len;
	Private->FileState = 0;   /* Make sure bit 0 = 0 (File open for read). */
	/* Lets see if this is GIF file: */
	if(GIF2RGB_ffread((unsigned char *)Buf, 1, GIF_STAMP_LEN, Private->File) != GIF_STAMP_LEN)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		free_ex((char *) Private);
		free_ex((char *) GifFile);
		Private = 0;
		GifFile = 0;
		return 0;
	}

	/* The GIF Version number is ignored at this time. Maybe we should do    */
	/* something more useful with it.					     */
	Buf[GIF_STAMP_LEN] = 0;
	if(strncmp(GIF_STAMP, Buf, GIF_VERSION_POS) != 0)
	{
		_GifError = GIF2RGB_ERR_NOT_GIF_FILE;
		free_ex((char *) Private);
		free_ex((char *) GifFile);
		Private = 0;
		GifFile = 0;
		return 0;
	}

	if(GIF2RGB_GetScreenDesc(GifFile) == GIF_ERROR)
	{
		free_ex((char *) Private);
		free_ex((char *) GifFile);
		Private = 0;
		GifFile = 0;
		return 0;
	}
	_GifError = 0;
	return (GIF_OK);
}

/******************************************************************************
*   This routine should be called before any other GIF2RGB_ calls. Note that      *
* this routine is called automatically from GIF2RGB_ file open routines.	      *
******************************************************************************/
short GIF2RGB_GetScreenDesc(GifFileType *GifFile)
{
	short Size, i;
	unsigned char Buf[3];
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	/* Put the screen descriptor into the file: */
	if(GIF2RGB_GetWord(Private->File, &GifFile->SWidth) == GIF_ERROR || GIF2RGB_GetWord(Private->File, &GifFile->SHeight) == GIF_ERROR)
		return GIF_ERROR;

	if(GIF2RGB_ffread(&Buf[0], 1, 3, Private->File) != 3)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}

	GifFile->SColorResolution = (((Buf[0] & 0x70) + 1) >> 4) + 1;
	GifFile->SBitsPerPixel = (Buf[0] & 0x07) + 1;
	GifFile->SBackGroundColor = Buf[1];

	if(Buf[0] & 0x80)                       /* Do we have global color map? */
	{
		Size = (1 << GifFile->SBitsPerPixel);
		GifFile->SColorMap = (GifColorType *) malloc_ex(sizeof(GifColorType) * Size);
		for (i = 0; i < Size; i++)              /* Get the global color map: */
		{
			if(GIF2RGB_ffread(Buf, 1, 3, Private->File) != 3)
			{
				_GifError = GIF2RGB_ERR_READ_FAILED;
				return GIF_ERROR;
			}
			GifFile->SColorMap[i].Red = Buf[0];
			GifFile->SColorMap[i].Green = Buf[1];
			GifFile->SColorMap[i].Blue = Buf[2];
		}
	}

	return GIF_OK;
}

short GIF2RGB_GetRecordType(GifRecordType *Type)
{
	unsigned char Buf;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(GIF2RGB_ffread(&Buf, 1, 1, Private->File) != 1)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}

	switch (Buf)
	{
	case ',':
		*Type = IMAGE_DESC_RECORD_TYPE;
		break;
	case '!':
		*Type = EXTENSION_RECORD_TYPE;
		break;
	case ';':
		*Type = TERMINATE_RECORD_TYPE;
		break;
	default:
		*Type = UNDEFINED_RECORD_TYPE;
		_GifError = GIF2RGB_ERR_WRONG_RECORD;
		return GIF_ERROR;
	}
	return GIF_OK;
}

short GIF2RGB_GetImageDesc(GifFileType *GifFile)
{
	short Size, i;
	unsigned char Buf[3];
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(	GIF2RGB_GetWord(Private->File, &GifFile->ILeft) == GIF_ERROR ||
			GIF2RGB_GetWord(Private->File, &GifFile->ITop) == GIF_ERROR ||
			GIF2RGB_GetWord(Private->File, &GifFile->IWidth) == GIF_ERROR ||
			GIF2RGB_GetWord(Private->File, &GifFile->IHeight) == GIF_ERROR)
		return GIF_ERROR;

	if(GIF2RGB_ffread(Buf, 1, 1, Private->File) != 1)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}

	GifFile->IBitsPerPixel = (Buf[0] & 0x07) + 1;
	GifFile->IInterlace = (Buf[0] & 0x40);

	if(Buf[0] & 0x80)              /* Does this image have local color map? */
	{
		Size = (1 << GifFile->IBitsPerPixel);
		if(GifFile->IColorMap) free_ex((char *) GifFile->IColorMap);
		GifFile->IColorMap = (GifColorType *) malloc_ex(sizeof(GifColorType) * Size);
		for(i = 0; i<Size; i++)        /* Get the image local color map: */
		{
			if(GIF2RGB_ffread(Buf, 1, 3, Private->File) != 3)
			{
				_GifError = GIF2RGB_ERR_READ_FAILED;
				return GIF_ERROR;
			}
			GifFile->IColorMap[i].Red = Buf[0];
			GifFile->IColorMap[i].Green = Buf[1];
			GifFile->IColorMap[i].Blue = Buf[2];
		}
	}

	Private->PixelCount = (long) GifFile->IWidth * (long) GifFile->IHeight;
	GIF2RGB_SetupDecompress(GifFile);  /* Reset decompress algorithm parameters. */
	return GIF_OK;
}

/******************************************************************************
*  Get one full scanned line (Line) of length LineLen from GIF file.	      *
******************************************************************************/
short GIF2RGB_GetLine(GifFileType *GifFile, unsigned char *Line, short LineLen)
{
	unsigned char *Dummy;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(!LineLen) LineLen = GifFile->IWidth;

	if((Private->PixelCount -= LineLen) > 0xffff0000)
	{
		_GifError = GIF2RGB_ERR_DATA_TOO_BIG;
		return GIF_ERROR;
	}

	if(GIF2RGB_DecompressLine(GifFile, Line, LineLen) == GIF_OK)
	{
		if(Private->PixelCount == 0)
		{
			/* We probably would not be called any more, so lets clean 	     */
			/* everything before we return: need to flush out all rest of    */
			/* image until empty block (size 0) detected. We use GetCodeNext.*/
			do
			{
				if(GIF2RGB_GetCodeNext(GifFile, &Dummy) == GIF_ERROR) return GIF_ERROR;
			}while (Dummy != NULL);
		}
		return GIF_OK;
	}
	else return GIF_ERROR;
}

/******************************************************************************
* Put one pixel (Pixel) into GIF file.					      *
******************************************************************************/
short GIF2RGB_GetPixel(GifFileType *GifFile, unsigned char Pixel)
{
	unsigned char *Dummy;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(--Private->PixelCount > 0xffff0000)
	{
		_GifError = GIF2RGB_ERR_DATA_TOO_BIG;
		return GIF_ERROR;
	}

	if(GIF2RGB_DecompressLine(GifFile, &Pixel, 1) == GIF_OK)
	{
		if(Private->PixelCount == 0)
		{
			/* We probably would not be called any more, so lets clean 	     */
			/* everything before we return: need to flush out all rest of    */
			/* image until empty block (size 0) detected. We use GetCodeNext.*/
			do
			{
				if(GIF2RGB_GetCodeNext(GifFile, &Dummy) == GIF_ERROR) return GIF_ERROR;
			} while (Dummy != NULL);
		}
		return GIF_OK;
	}
	else return GIF_ERROR;
}

/******************************************************************************
*   Get an extension block (see GIF manual) from gif file. This routine only  *
* returns the first data block, and GIF2RGB_GetExtensionNext shouldbe called      *
* after this one until NULL extension is returned.			      *
*   The Extension should NOT be freed by the user (not dynamically allocated).*
*   Note it is assumed the Extension desc. header ('!') has been read.	      *
******************************************************************************/
short GIF2RGB_GetExtension(GifFileType *GifFile, short *ExtCode, unsigned char **Extension)
{
	unsigned char Buf;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(GIF2RGB_ffread(&Buf, 1, 1, Private->File) != 1)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}
	*ExtCode = Buf;

	return GIF2RGB_GetExtensionNext(GifFile, Extension);
}

/******************************************************************************
*   Get a following extension block (see GIF manual) from gif file. This      *
* routine sould be called until NULL Extension is returned.		      *
*   The Extension should NOT be freed by the user (not dynamically allocated).*
******************************************************************************/
short GIF2RGB_GetExtensionNext(GifFileType *GifFile, unsigned char **Extension)
{
	unsigned char Buf;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(GIF2RGB_ffread(&Buf, 1, 1, Private->File) != 1)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}
	if(Buf > 0)
	{
		*Extension = Private->Buf;           /* Use private unused buffer. */
		(*Extension)[0] = Buf;  /* Pascal strings notation (pos. 0 is len.). */
		if(GIF2RGB_ffread(&((*Extension)[1]), 1, Buf, Private->File) != Buf)
		{
			_GifError = GIF2RGB_ERR_READ_FAILED;
			return GIF_ERROR;
		}
	}
	else *Extension = NULL;
	return GIF_OK;
}

/******************************************************************************
*   This routine should be called last, to close GIF file.		      *
******************************************************************************/
short GIF2RGB_CloseFile(GifFileType *GifFile)
{
	GifFilePrivateType *Private;
	char * File;

	if(GifFile == NULL) return GIF_ERROR;

	Private = (GifFilePrivateType *) GifFile->Private;

	if(GifFile->IColorMap) free_ex((char *) GifFile->IColorMap);
	if(GifFile->SColorMap) free_ex((char *) GifFile->SColorMap);
	File=Private->File;
	if(Private) free_ex((char *) Private);
	free_ex(GifFile);

	free_ex(File);

	return GIF_OK;
}

/******************************************************************************
*   Get 2 bytes (word) from the given file:				      *
******************************************************************************/
short GIF2RGB_GetWord(char * File, short *Word)
{
	unsigned char c[2];

	if(GIF2RGB_ffread(c, 1, 2, File) != 2)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}

	*Word = (((unsigned short) c[1]) << 8) + c[0];
	return GIF_OK;
}

/******************************************************************************
*   Get the image code in compressed form. his routine can be called if the   *
* information needed to be piped out as is. Obviously this is much faster     *
* than decoding and encoding again. This routine should be followed by calls  *
* to GIF2RGB_GetCodeNext, until NULL block is returned.			      *
*   The block should NOT be freed by the user (not dynamically allocated).    *
******************************************************************************/
short GIF2RGB_GetCode(GifFileType *GifFile, short *CodeSize, unsigned char **CodeBlock)
{
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	*CodeSize = Private->BitsPerPixel;
	return GIF2RGB_GetCodeNext(GifFile, CodeBlock);
}

/******************************************************************************
*   Continue to get the image code in compressed form. This routine should be *
* called until NULL block is returned.					      *
*   The block should NOT be freed by the user (not dynamically allocated).    *
******************************************************************************/
short GIF2RGB_GetCodeNext(GifFileType *GifFile, unsigned char **CodeBlock)
{
	unsigned char Buf;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(GIF2RGB_ffread(&Buf, 1, 1, Private->File) != 1)
	{
		_GifError = GIF2RGB_ERR_READ_FAILED;
		return GIF_ERROR;
	}

	if(Buf > 0)
	{
		*CodeBlock = Private->Buf;	       /* Use private unused buffer. */
		(*CodeBlock)[0] = Buf;  /* Pascal strings notation (pos. 0 is len.). */
		if(GIF2RGB_ffread(&((*CodeBlock)[1]), 1, Buf, Private->File) != Buf)
		{
			_GifError = GIF2RGB_ERR_READ_FAILED;
			return GIF_ERROR;
		}
	}
	else
	{
		*CodeBlock = NULL;
		Private->Buf[0] = 0;		   /* Make sure the buffer is empty! */
		Private->PixelCount = 0;   /* And local info. indicate image read. */
	}

	return GIF_OK;
}

/******************************************************************************
*   Setup the LZ decompression for this image:				      *
******************************************************************************/
short GIF2RGB_SetupDecompress(GifFileType *GifFile)
{
	short i, BitsPerPixel;
	unsigned char CodeSize;
	unsigned short *Prefix;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	GIF2RGB_ffread(&CodeSize, 1, 1, Private->File);    /* Read Code size from file. */
	BitsPerPixel = CodeSize;

	Private->Buf[0] = 0;			      /* Input Buffer empty. */
	Private->BitsPerPixel = BitsPerPixel;
	Private->ClearCode = (1 << BitsPerPixel);
	Private->EOFCode = Private->ClearCode + 1;
	Private->RunningCode = Private->EOFCode + 1;
	Private->RunningBits = BitsPerPixel + 1;	 /* Number of bits per code. */
	Private->MaxCode1 = 1 << Private->RunningBits;     /* Max. code + 1. */
	Private->StackPtr = 0;		    /* No pixels on the pixel stack. */
	Private->LastCode = NO_SUCH_CODE;
	Private->CrntShiftState = 0;	/* No information in CrntShiftDWord. */
	Private->CrntShiftDWord = 0;

	Prefix = Private->Prefix;

	for(i=0; i <= LZ_MAX_CODE; i++) Prefix[i] = NO_SUCH_CODE;

	return GIF_OK;
}

/******************************************************************************
*   The LZ decompression routine:					      *
*   This version decompress the given gif file into Line of length LineLen.   *
*   This routine can be called few times (one per scan line, for example), in *
* order the complete the whole image.					      *
******************************************************************************/
short GIF2RGB_DecompressLine(GifFileType *GifFile, unsigned char *Line, short LineLen)
{
	short i = 0, j, CrntCode, EOFCode, ClearCode, CrntPrefix, LastCode, StackPtr;
	unsigned char *Stack, *Suffix;
	unsigned short *Prefix;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	StackPtr = Private->StackPtr;
	Prefix = Private->Prefix;
	Suffix = Private->Suffix;
	Stack = Private->Stack;
	EOFCode = Private->EOFCode;
	ClearCode = Private->ClearCode;
	LastCode = Private->LastCode;

	if(StackPtr != 0)
	{
		/* Let pop the stack off before continueing to read the gif file: */
		while (StackPtr != 0 && i < LineLen) Line[i++] = Stack[--StackPtr];
	}

	while (i < LineLen)                             /* Decode LineLen items. */
	{
		if(GIF2RGB_DecompressInput(Private, &CrntCode) == GIF_ERROR)
			return GIF_ERROR;

		if(CrntCode == EOFCode)
		{
			/* Note however that usually we will not be here as we will stop */
			/* decoding as soon as we got all the pixel, or EOF code will    */
			/* not be read at all, and GIF2RGB_GetLine/Pixel clean everything.   */
			if(i != LineLen - 1 || Private->PixelCount != 0)
			{
				_GifError = GIF2RGB_ERR_EOF_TOO_SOON;
				return GIF_ERROR;
			}
			i++;
		}
		else if(CrntCode == ClearCode)
		{
			/* We need to start over again: */
			for(j=0; j<=LZ_MAX_CODE; j++) Prefix[j] = NO_SUCH_CODE;
			Private->RunningCode = Private->EOFCode + 1;
			Private->RunningBits = Private->BitsPerPixel + 1;
			Private->MaxCode1 = 1 << Private->RunningBits;
			LastCode = Private->LastCode = NO_SUCH_CODE;
		}
		else
		{
			/* Its regular code - if in pixel range simply add it to output  */
			/* stream, otherwise trace to codes linked list until the prefix */
			/* is in pixel range:                                            */
			if(CrntCode < ClearCode)
			{
				/* This is simple - its pixel scalar, so add it to output:   */
				Line[i++] = (unsigned char)CrntCode;
			}
			else
			{
				/* Its a code to needed to be traced: trace the linked list  */
				/* until the prefix is a pixel, while pushing the suffix     */
				/* pixels on our stack. If we done, pop the stack in reverse */
				/* (thats what stack is good for!) order to output.          */
				if(Prefix[CrntCode] == NO_SUCH_CODE)
				{
					/* Only allowed if CrntCode is exactly the running code: */
					/* In that case CrntCode = XXXCode, CrntCode or the      */
					/* prefix code is last code and the suffix char is       */
					/* exactly the prefix of last code!                      */
					if(CrntCode == Private->RunningCode - 2)
					{
						CrntPrefix = LastCode;
						Suffix[Private->RunningCode - 2] =
						Stack[StackPtr++] = (unsigned char)GIF2RGB_GetPrefixChar(Prefix, LastCode, ClearCode);
					}
					else
					{
						_GifError = GIF2RGB_ERR_IMAGE_DEFECT;
						return GIF_ERROR;
					}
				} else CrntPrefix = CrntCode;

				/* Now (if image is O.K.) we should not get an NO_SUCH_CODE  */
				/* During the trace. As we might loop forever, in case of    */
				/* defective image, we count the number of loops we trace    */
				/* and stop if we got LZ_MAX_CODE. obviously we can not      */
				/* loop more than that.                                      */
				j = 0;
				while (j++ <= LZ_MAX_CODE && CrntPrefix > ClearCode && CrntPrefix <= LZ_MAX_CODE)
				{
					Stack[StackPtr++] = Suffix[CrntPrefix];
					CrntPrefix = Prefix[CrntPrefix];
				}
				if(j >= LZ_MAX_CODE || CrntPrefix > LZ_MAX_CODE)
				{
					_GifError = GIF2RGB_ERR_IMAGE_DEFECT;
					return GIF_ERROR;
				}
				/* Push the last character on stack: */
				Stack[StackPtr++] = (unsigned char)CrntPrefix;

				/* Now lets pop all the stack into output: */
				while (StackPtr != 0 && i < LineLen)
					Line[i++] = Stack[--StackPtr];
			}
			if(LastCode != NO_SUCH_CODE)
			{
				Prefix[Private->RunningCode - 2] = LastCode;

				if(CrntCode == Private->RunningCode - 2)
				{
					/* Only allowed if CrntCode is exactly the running code: */
					/* In that case CrntCode = XXXCode, CrntCode or the      */
					/* prefix code is last code and the suffix char is       */
					/* exactly the prefix of last code!                      */
					Suffix[Private->RunningCode - 2] = (unsigned char)GIF2RGB_GetPrefixChar(Prefix, LastCode, ClearCode);
				}
				else
				{
					Suffix[Private->RunningCode - 2] = (unsigned char)GIF2RGB_GetPrefixChar(Prefix, CrntCode, ClearCode);
				}
			}
			LastCode = CrntCode;
		}
	}

	Private->LastCode = LastCode;
	Private->StackPtr = StackPtr;

	return GIF_OK;
}

/******************************************************************************
* Routine to trace the Prefixes linked list until we get a prefix which is    *
* not code, but a pixel value (less than ClearCode). Returns that pixel value.*
* If image is defective, we might loop here forever, so we limit the loops to *
* the maximum possible if image O.k. - LZ_MAX_CODE times.		      *
******************************************************************************/
short GIF2RGB_GetPrefixChar(unsigned short *Prefix, short Code, short ClearCode)
{
	short i = 0;

	while (Code > ClearCode && i++ <= LZ_MAX_CODE) Code = Prefix[Code];
	return Code;
}

/******************************************************************************
*   Interface for accessing the LZ codes directly. Set Code to the real code  *
* (12bits), or to -1 if EOF code is returned.				      *
******************************************************************************/
short GIF2RGB_GetLZCodes(GifFileType *GifFile, short *Code)
{
	unsigned char *CodeBlock;
	GifFilePrivateType *Private = (GifFilePrivateType *) GifFile->Private;

	if(GIF2RGB_DecompressInput(Private, Code) == GIF_ERROR)
		return GIF_ERROR;

	if(*Code == Private->EOFCode)
	{
		/* Skip rest of codes (hopefully only NULL terminating block): */
		do
		{
			if(GIF2RGB_GetCodeNext(GifFile, &CodeBlock) == GIF_ERROR)
				return GIF_ERROR;
		}while (CodeBlock != NULL);

		*Code = -1;
	}
	else if(*Code == Private->ClearCode)
	{
		/* We need to start over again: */
		Private->RunningCode = Private->EOFCode + 1;
		Private->RunningBits = Private->BitsPerPixel + 1;
		Private->MaxCode1 = 1 << Private->RunningBits;
	}

	return GIF_OK;
}

/******************************************************************************
*   The LZ decompression input routine:					      *
*   This routine is responsable for the decompression of the bit stream from  *
* 8 bits (bytes) packets, into the real codes.				      *
*   Returns GIF_OK if read succesfully.					      *
******************************************************************************/
short GIF2RGB_DecompressInput(GifFilePrivateType *Private, short *Code)
{
	unsigned char NextByte;
	static unsigned short CodeMasks[] =
	{
		0x0000, 0x0001, 0x0003, 0x0007,
		0x000f, 0x001f, 0x003f, 0x007f,
		0x00ff, 0x01ff, 0x03ff, 0x07ff,
		0x0fff
	};

	while (Private->CrntShiftState < Private->RunningBits)
	{
		/* Needs to get more bytes from input stream for next code: */
		if(GIF2RGB_BufferedInput(Private->File, Private->Buf, &NextByte) == GIF_ERROR)
		{
			return GIF_ERROR;
		}
		Private->CrntShiftDWord |= ((unsigned long) NextByte) << Private->CrntShiftState;
		Private->CrntShiftState += 8;
	}

	*Code = (short)(Private->CrntShiftDWord & CodeMasks[Private->RunningBits]);

	Private->CrntShiftDWord >>= Private->RunningBits;
	Private->CrntShiftState -= Private->RunningBits;

	/* If code cannt fit into RunningBits bits, must raise its size. Note */
	/* however that codes above 4095 are used for special signaling.      */
	if(++Private->RunningCode > Private->MaxCode1 && Private->RunningBits < LZ_BITS)
	{
		Private->MaxCode1 <<= 1;
		Private->RunningBits++;
	}
	return GIF_OK;
}

/******************************************************************************
*   This routines read one gif data block at a time and buffers it internally *
* so that the decompression routine could access it.			      *
*   The routine returns the next byte from its internal buffer (or read next  *
* block in if buffer empty) and returns GIF_OK if succesful.		      *
******************************************************************************/
short GIF2RGB_BufferedInput(char * File, unsigned char *Buf, unsigned char *NextByte)
{
	if(Buf[0] == 0)
	{
		/* Needs to read the next buffer - this one is empty: */
		if(GIF2RGB_ffread(Buf, 1, 1, File) != 1)
		{
			_GifError = GIF2RGB_ERR_READ_FAILED;
			return GIF_ERROR;
		}
		if(GIF2RGB_ffread(&Buf[1], 1, Buf[0], File) != Buf[0])
		{
			_GifError = GIF2RGB_ERR_READ_FAILED;
			return GIF_ERROR;
		}
		*NextByte = Buf[1];
		Buf[1] = 2;	   /* We use now the second place as last char read! */
		Buf[0]--;
	}
	else
	{
		*NextByte = Buf[Buf[1]++];
		Buf[0]--;
	}
	return GIF_OK;
}

/**************************************************************************
*
*  
*   MAKE GIF ROUTINES
*		
*		  
**************************************************************************/

// return 0 if error else 1
int RGB2GIF(RGBIMAGE *rgb, GIFIMAGE *gif)
{
	int i, j, index;
	unsigned char r, g, b;
	unsigned char *rgb_data;
	unsigned char *rgb_data_ind;

	if(!rgb) return 0;
	if(!gif) return 0;

	if(!rgb->data) return 0;
	if(rgb->m_width<=0 || rgb->m_height<=0) return 0;

	image_real_width = rgb->m_width;
	image_real_height = rgb->m_height;

	gif->data = 0;
	gif->data_len = 0;

	memset(color_table, 0, 256*3);

	used_colors = 0;

	if(data_ind) free_ex(data_ind);

	data_ind = (unsigned char *)malloc_ex(image_real_width * image_real_height);
	if(!data_ind) return 0;

	if(data_file) free_ex(data_file);
	data_file = (unsigned char *)malloc_ex(image_real_width * image_real_height + 1024);
	if(!data_file)
	{
		free_ex(data_ind);
		return 0;
	}

	mem_file_pos = 0;
	used_colors = 0;

	rgb_data = rgb->data;

	rgb_data_ind = data_ind;

	// make palette mode
	for(j=0; j<image_real_height; j++)
	{
		for(i=0; i<image_real_width; i++)
		{
			r = *(rgb_data++);
			g = *(rgb_data++);
			b = *(rgb_data++);

			index = RGB2GIF_AddToPalette(r, g, b);
			*(rgb_data_ind) = index;
			rgb_data_ind++;			
		}
	}

// clear some variables
	a_count = 0;
	curx, cury = 0;
	CountDown = 0;
	Pass = 0;
	Interlace = 0;
	n_bits = 0;			  // number of bits/code
	maxbits = BITS;		  // user settable max # bits/code
	maxcode = 0;		  // maximum code, given n_bits
	maxmaxcode = (int) 1 << BITS; // should NEVER generate this code
	hsize = HSIZE; //for dynamic table sizing
	free_ent = 0; // first unused entry
	clear_flg = 0;
	offset = 0;
	in_count = 1;		 // length of input
	out_count = 0;	 // # of codes output (for debugging)
	g_init_bits = 0;
	ClearCode = 0;
	EOFCode = 0;
	cur_accum = 0;
	cur_bits = 0;

	RGB2GIF_GIFEncode(0, 0, -1);

	free_ex(data_ind);
	data_ind = 0;

	gif->data = data_file;
	data_file = 0;
	gif->data_len = mem_file_pos;

	return 1;
}

// возвращает номер в паллитре
int RGB2GIF_AddToPalette(unsigned char r, unsigned char g, unsigned char b)
{
	int index = 0, found_color = 0, i;
	unsigned char *c_tbl;
	int dl, dl_t, di;

	c_tbl = color_table;
	for(i=0; i<used_colors; i++)
	{
		if((c_tbl[0] == r) && (c_tbl[1] == g) && (c_tbl[2] == b))
		{
			found_color = 1;
			index = i;
			break;
		}
		c_tbl += 3;
	}

	if(!found_color)
	{
		if(used_colors == 256)
		{
			// try to find nearest color: color quantization
			c_tbl = color_table;
			di = 0;
			dl = abs(r-c_tbl[0]) + abs(g-c_tbl[1]) + abs(b-c_tbl[2]);
			c_tbl += 3;

			for(i=1; i<256; i++)
			{
				dl_t = abs(r-c_tbl[0]) + abs(g-c_tbl[1]) + abs(b-c_tbl[2]);
				if(dl > dl_t)
				{
					dl = dl_t;
					di = i;
				}
				c_tbl += 3;
			}
			index = di;
		}
		else
		{
			index = used_colors;
			c_tbl = color_table + index * 3;
			c_tbl[0] = r;
			c_tbl[1] = g;
			c_tbl[2] = b;
			used_colors++;
		}
	}

	return index;
}

// Bump the 'curx' and 'cury' to point to the next pixel
void RGB2GIF_BumpPixel()
{
	// Bump the current X position
	++curx;

	// If we are at the end of a scan line, set curx back to the beginning
	// If we are interlaced, bump the cury to the appropriate spot,
	// otherwise, just increment it.
	if( curx == image_real_width )
	{
		curx = 0;
		if( !Interlace )
			++cury;
		else
		{
			switch( Pass )
			{
			case 0:
				cury += 8;
				if( cury >= image_real_height )
				{
					++Pass;
					cury = 4;
				}break;
			case 1:
				cury += 8;
				if( cury >= image_real_height )
				{
					++Pass;
					cury = 2;
				} break;
			case 2:
				cury += 4;
				if( cury >= image_real_height )
				{
					++Pass;
					cury = 1;
				} break;
			case 3:
				cury += 2;
				break;
			}
		}
	}
}


// Return the next pixel from the image
int RGB2GIF_GIFNextPixel()
{
	int r;

	if( CountDown == 0 )
		return EOF;
	--CountDown;

	r = data_ind[ cury * image_real_width + curx ];
	RGB2GIF_BumpPixel();
	return r;
}

// public
void RGB2GIF_GIFEncode(int GInterlace, unsigned char Background, int Transparent)
{
	unsigned char B;
	int Color_Resolution;
	int ColorMapSize;
	unsigned char InitCodeSize;
	int i;
	char *c_tbl;
	int BitsPerPixel = -1;

	for(BitsPerPixel= 0; (1 << BitsPerPixel)<used_colors; BitsPerPixel++);

	Interlace = GInterlace;

	// Calculate number of bits we are expecting
	CountDown = (long)image_real_width * (long)image_real_height;

	// Indicate which pass we are on (if interlace)
	Pass = 0;

	// The initial code size
	if( BitsPerPixel <= 1 )
		InitCodeSize = 2;
	else
		InitCodeSize = BitsPerPixel;

	// Set up the current x and y position
	curx = cury = 0;

	// Write the Magic header
	RGB2GIF_Write2ImageEx("GIF87a", 6);

	// Write out the screen width and height
	RGB2GIF_Putword( image_real_width );
	RGB2GIF_Putword( image_real_height );

	// Indicate that there is a global colour map
	B = 0x80; // Yes, there is a color map

	// OR in the resolution
	Color_Resolution = BitsPerPixel - 1;
	B |= (Color_Resolution) << 4;

	// OR in the Bits per Pixel
	B |= (BitsPerPixel - 1);

	// Write it out
	RGB2GIF_Write2Image(B);

	// Write out the Background colour
	RGB2GIF_Write2Image(Background);

	// Byte of 0's (future expansion)
	RGB2GIF_Write2Image(0);

	ColorMapSize = 1 << BitsPerPixel;

	// Write out the Global Colour Map
	c_tbl = color_table;
	for(i=0; i<ColorMapSize; i++)
	{
		RGB2GIF_Write2Image(*c_tbl++);// Red   
		RGB2GIF_Write2Image(*c_tbl++);	// Green 
		RGB2GIF_Write2Image(*c_tbl++);	// Blue  
	}

	// Write an Image separator
	RGB2GIF_Write2Image(0x2C);

	// Write the Image header
	RGB2GIF_Putword( 0 );
	RGB2GIF_Putword( 0 );
	RGB2GIF_Putword( image_real_width );
	RGB2GIF_Putword( image_real_height );

	// Write out whether or not the image is interlaced
	RGB2GIF_Write2Image(0x00);

	// Write out the initial code size
	RGB2GIF_Write2Image(InitCodeSize);

	// Go and actually compress the data
	RGB2GIF_compress( InitCodeSize+1 );

	// Write out a Zero-length packet (to end the series)
	RGB2GIF_Write2Image(0);

	// Write the GIF file terminator
	RGB2GIF_Write2Image(';');
}

// Write out a word to the GIF file
void RGB2GIF_Putword(int w)
{
	RGB2GIF_Write2Image( (unsigned char)(w & 0xff) );
	RGB2GIF_Write2Image( (unsigned char)((w / 256) & 0xff) );
}

void RGB2GIF_compress(int init_bits )
{
	register long fcode;
	register int i;
	register int c;
	register int ent;
	register int disp;
	register int hsize_reg;
	register int hshift;

	// Set up the globals:  g_init_bits - initial number of bits
	g_init_bits = init_bits;

	// Set up the necessary values
	offset = 0;
	out_count = 0;
	clear_flg = 0;
	in_count = 1;
	maxcode = MAXCODE(n_bits = g_init_bits);

	ClearCode = (1 << (init_bits - 1));
	EOFCode = ClearCode + 1;
	free_ent = ClearCode + 2;

	RGB2GIF_char_init();

	ent = RGB2GIF_GIFNextPixel( );

	hshift = 0;

	for(fcode=(long)hsize; fcode<65536L; fcode*=2L)
		++hshift;

	hshift = 8 - hshift;		// set hash code range bound

	hsize_reg = hsize;
	RGB2GIF_cl_hash( (count_int) hsize_reg); // clear hash table

	RGB2GIF_output( (int)ClearCode );

#ifdef SIGNED_COMPARE_SLOW
	while ( (c = RGB2GIF_GIFNextPixel( )) != (unsigned) EOF ) {
#else
	while ( (c = RGB2GIF_GIFNextPixel( )) != EOF ) {
#endif
		++in_count;

		fcode = (long) (((long) c << maxbits) + ent);
		i = (((int)c << hshift) ^ ent); // xor hashing

		if( HashTabOf (i) == fcode )
		{
			ent = CodeTabOf (i);
			continue;
		}
		else
			if ( (long)HashTabOf (i) < 0 ) // empty slot
				goto nomatch;

		disp = hsize_reg - i; // secondary hash (after G. Knott)
		if ( i == 0 )
			disp = 1;
probe:
		if ((i -= disp) < 0 )
			i += hsize_reg;

		if ( HashTabOf (i) == fcode )
		{
			ent = CodeTabOf (i);
			continue;
		}
		if ( (long)HashTabOf (i) > 0 )
			goto probe;

		nomatch:
		RGB2GIF_output ( (int) ent );
		++out_count;
		ent = c;
#ifdef SIGNED_COMPARE_SLOW
		if ( (unsigned) free_ent < (unsigned) maxmaxcode) {
#else
		if ( free_ent < maxmaxcode ) {
#endif
			CodeTabOf (i) = free_ent++; // code -> hashtable
			HashTabOf (i) = fcode;
		}
		else
			RGB2GIF_cl_block();
	}
	// Put out the final code.
	RGB2GIF_output( (int)ent );
	++out_count;
	RGB2GIF_output( (int) EOFCode );
}

void RGB2GIF_output( int code )
{
	cur_accum &= masks[ cur_bits ];

	if( cur_bits > 0 )
		cur_accum |= ((long)code << cur_bits);
	else
		cur_accum = code;

	cur_bits += n_bits;

	while( cur_bits >= 8 )
	{
		RGB2GIF_char_out( (unsigned int)(cur_accum & 0xff) );
		cur_accum >>= 8;
		cur_bits -= 8;
	}

	// If the next entry is going to be too big for the code size,
	// then increase it, if possible.
	if ( free_ent > maxcode || clear_flg )
	{
		if( clear_flg )
		{
			maxcode = MAXCODE (n_bits = g_init_bits);
			clear_flg = 0;
		}
		else
		{
			++n_bits;
			if ( n_bits == maxbits )
				maxcode = maxmaxcode;
			else
				maxcode = MAXCODE(n_bits);
		}
	}

	if( code == EOFCode )
	{
		// At EOF, write the rest of the buffer.
		while( cur_bits > 0 )
		{
			RGB2GIF_char_out( (unsigned int)(cur_accum & 0xff) );
			cur_accum >>= 8;
			cur_bits -= 8;
		}
		RGB2GIF_flush_char();
	}
}

// Clear out the hash table
void RGB2GIF_cl_block ()		// table clear for block compress
{
	RGB2GIF_cl_hash ( (count_int) hsize );
	free_ent = ClearCode + 2;
	clear_flg = 1;

	RGB2GIF_output( (int)ClearCode );
}

void RGB2GIF_cl_hash(register count_int hsize) // reset code table
{
	register count_int *htab_p = htab+hsize;

	register long i;
	register long m1 = -1;

	i = hsize - 16;
	do {				// might use Sys V memset(3) here
		*(htab_p-16) = m1;
		*(htab_p-15) = m1;
		*(htab_p-14) = m1;
		*(htab_p-13) = m1;
		*(htab_p-12) = m1;
		*(htab_p-11) = m1;
		*(htab_p-10) = m1;
		*(htab_p-9) = m1;
		*(htab_p-8) = m1;
		*(htab_p-7) = m1;
		*(htab_p-6) = m1;
		*(htab_p-5) = m1;
		*(htab_p-4) = m1;
		*(htab_p-3) = m1;
		*(htab_p-2) = m1;
		*(htab_p-1) = m1;
		htab_p -= 16;
	} while ((i -= 16) >= 0);

	for ( i += 16; i > 0; --i )
		*--htab_p = m1;
}

// Set up the 'byte output' routine
void RGB2GIF_char_init()
{
	a_count = 0;
}

// Add a character to the end of the current packet, and if it is 254
// characters, flush the packet to disk.
void RGB2GIF_char_out( int c )
{
	accum[ a_count++ ] = c;
	if( a_count >= 254 )
		RGB2GIF_flush_char();
}

// Flush the packet to disk, and reset the accumulator
void RGB2GIF_flush_char()
{
	if( a_count > 0 )
	{
		RGB2GIF_Write2Image((unsigned char)a_count);

		RGB2GIF_Write2ImageEx(accum, a_count);

		a_count = 0;
	}
}

// return current position
int RGB2GIF_Write2ImageEx(void *data, int len)
{
	if(!data) return -1;
	memcpy(data_file+mem_file_pos, data, len);
	mem_file_pos+=len;
	return mem_file_pos;
}

// return current position
int RGB2GIF_Write2Image(unsigned char data)
{
	data_file[mem_file_pos] = data;
	mem_file_pos+=1;
	return mem_file_pos;
}


/***********************************************************************************
                      Merge two images
************************************************************************************/

int Merge(RGBIMAGE *img, RGBIMAGE *img_src, int x, int y)
{
	MERGE_COLOR mc;

	if(!img_src) return 0;
	if(!img) return 0;

	memset(&mc, 0, sizeof(MERGE_COLOR));

	return MergeEx(img, img_src, 0, 0, 0, 0, img_src->m_width, img_src->m_height, &mc);
}

int MergeEx(RGBIMAGE *img, RGBIMAGE *img_src, int x_dest, int y_dest, int src_x, int src_y, int src_w, int src_h, MERGE_COLOR *mc)
{
	unsigned char *data = 0, *src_data = 0;
	int x, y, x1, y1, ind1, ind2;
	unsigned char r_src, g_src, b_src;
	int use_transp = 0;
	unsigned char transp_r = 0, transp_g = 0, transp_b = 0;
	int use_replace = 0;
	unsigned char replace_r = 0, replace_g = 0, replace_b = 0;
	unsigned char replace_by_r = 0, replace_by_g = 0, replace_by_b = 0;

	if(mc->mask & TRANSPARENT_SET)
	{
		use_transp = 1;
		transp_r = mc->transp_r;
		transp_g = mc->transp_g;
		transp_b = mc->transp_b;
	}

	if(mc->mask & REPLACE_COLOR_SET)
	{
		use_replace = 1;

		replace_r = mc->replace_r;
		replace_g = mc->replace_g;
		replace_b = mc->replace_b;

		replace_by_r = mc->replace_by_r;
		replace_by_g = mc->replace_by_g;
		replace_by_b = mc->replace_by_b;
	}

	if(!img) return 0;
	if(!img->data) return 0;
	if(!img_src) return 0;
	if(!img_src->data) return 0;

	if(img_src->m_width<=0 || img_src->m_height<=0)
		return 0;

	if(img->m_width<=0 || img->m_height<=0)
		return 0;

	if(src_h<=0 || src_w<=0 || src_x<0 || src_y<0)
		return 0;

	if(src_x + src_w > img_src->m_width) return 0;
	if(src_y + src_h > img_src->m_height) return 0;

	if(x_dest >= img->m_width || y_dest >= img->m_height)
		return 1;

	if(x_dest < 0) x_dest = 0;
	if(y_dest < 0) y_dest = 0;

	if(x_dest+src_w > img->m_width) src_w = img->m_width - x_dest;
	if(y_dest+src_h > img->m_height) src_h = img->m_height - y_dest;

	src_data = img_src->data;
	data = img->data;

	if(use_transp)
	{
		for(y=y_dest, y1=src_y; y1<(src_y+src_h) && y<img->m_height; y++, y1++)
		{
			for(x=x_dest, x1=src_x; x1<(src_x+src_w) && x<img->m_width; x++, x1++)
			{
				ind1 = (y*img->m_width+x)*3;
				ind2 = (y1*img_src->m_width+x1)*3;

				r_src = src_data[ind2++];
				g_src = src_data[ind2++];
				b_src = src_data[ind2];

				if(use_replace)
				{
					if(r_src == replace_r && g_src == replace_g && b_src == replace_b)
					{
						r_src = replace_by_r;
						g_src = replace_by_g;
						b_src = replace_by_b;
					}
				}

				if(r_src == transp_r && g_src == transp_g && b_src == transp_b)
					continue;
				data[ind1++] = r_src;
				data[ind1++] = g_src;
				data[ind1] = b_src;
			}
		}
	}
	else
	{
		for(y=y_dest, y1=src_y; y1<src_h && y<img->m_height; y++, y1++)
		{
			ind1 = (y*img->m_width+x_dest)*3;
			ind2 = (y1*img_src->m_width+src_x)*3;

			memcpy(&data[ind1], &src_data[ind2], src_w*3);
		}
	}

	return 1;
}

/************************************************************************************

INTERFACE FUNCTIONS

*************************************************************************************/

void FreeImage_RGB(RGBIMAGE *rgb_img)
{
	if(rgb_img)
	{
		if(rgb_img->data) free_ex(rgb_img->data);
		rgb_img->data =0;
		rgb_img->m_height = 0;
		rgb_img->m_width = 0;
	}
}

void FreeImage_GIF(GIFIMAGE *gif_img)
{
	if(gif_img)
	{
		if(gif_img->data) free_ex (gif_img->data);
		gif_img->data =0;
		gif_img->data_len = 0;
	}
}

// make RGB from GIF
int MakeImage_RGB(GIFIMAGE *gif_img, RGBIMAGE *rgb_img)
{
	if(!gif_img || !rgb_img) return 0;

	if(!GIF2RGB_LoadGifFromMemory(rgb_img, gif_img->data, gif_img->data_len))
		return 0;

	return 1;
}

// make GIF from RGB
int MakeImage_GIF(RGBIMAGE *rgb_img, GIFIMAGE *gif_img)
{
	return RGB2GIF(rgb_img, gif_img);
}

// make RGB data from GIF
int MakeImage_RGB_EX(char *gif_file_data, int gif_file_data_len, unsigned char **rgb_data_ex, int *rgb_data_ex_len)
{
	GIFIMAGE gif;
	RGBIMAGE rgb;

	long *l_data;

	if(!gif_file_data || gif_file_data_len<=0) return 0;

	gif.data = gif_file_data;
	gif.data_len = gif_file_data_len;
	
	if(!MakeImage_RGB(&gif, &rgb))
		return 0;

	*rgb_data_ex_len = sizeof(long) + sizeof(long) + rgb.m_width * rgb.m_height * 3;

	*rgb_data_ex = (unsigned char *)malloc_ex(*rgb_data_ex_len);

	if(!*rgb_data_ex) return 0;

	l_data = (long *)*rgb_data_ex;

	// copy width
	l_data[0] = rgb.m_width;

	// copy height
	l_data[1] = rgb.m_height;

	// copy data
	memcpy((void *)(*rgb_data_ex+sizeof(long)+sizeof(long)), rgb.data, rgb.m_width * rgb.m_height * 3);

	free_ex(rgb.data);

	return 1;
}

void FreeImage_RGB_EX(unsigned char **rgb_data_ex)
{
	if(*rgb_data_ex)
		free_ex(*rgb_data_ex);
	*rgb_data_ex = 0;
}

// make GIF from RGB_EX data
int MakeImage_GIF_EX(char *rgb_data_ex, unsigned char **gif_data, int *gif_len)
{
	GIFIMAGE gif;
	RGBIMAGE rgb;
	long rgb_size_w;
	long rgb_size_h;

	if(!rgb_data_ex) return 0;

	rgb_size_w = (long)(*(rgb_data_ex));
	rgb_size_h = (long)(*(rgb_data_ex + sizeof(long)));

	if(rgb_size_w<=0 || rgb_size_h<=0) return 0;

	rgb.data = rgb_data_ex + sizeof(long) + sizeof(long);
	rgb.m_width = rgb_size_w;
	rgb.m_height = rgb_size_h;
	
	if(!MakeImage_GIF(&rgb, &gif))
		return 0;

	*gif_data = gif.data;
	*gif_len = gif.data_len;

	return 1;
}

void FreeImage_GIF_EX(unsigned char **gif_img)
{
	if(*gif_img)
		free_ex(*gif_img);
	*gif_img = 0;
}

int DublicateRGBImage(RGBIMAGE *rgb, RGBIMAGE *new_rgb)
{
	int len;
	
	if(!rgb || !new_rgb) return 0;

	if(!rgb->data) return 0;

	if(rgb->m_width<=0 || rgb->m_height<=0) return 0;

	len = rgb->m_width * rgb->m_height * 3;

	new_rgb->data = (unsigned char *) malloc_ex(len);
	if(!new_rgb->data) return 0;

	memcpy(new_rgb->data, rgb->data, len);

	new_rgb->m_width = rgb->m_width;
	new_rgb->m_height = rgb->m_height;

	return 1;
}

int ReplaceRGBColor(RGBIMAGE *rgb, unsigned char r0, unsigned char g0, unsigned char b0, unsigned char r, unsigned char g, unsigned char b)
{
	int w, h, x, y;
	unsigned char *data;

	if(!rgb) return 0;
	if(!rgb->data) return 0;
	if(rgb->m_width<=0 || rgb->m_height<=0) return 0;
	w = rgb->m_width;
	h = rgb->m_height;

	data = rgb->data;

	for(y=0; y<h; y++)
	{
		for(x=0; x<w; x++)
		{
			if(data[0] == r0 && data[1] == g0 && data[2] == b0)
			{
				data[0] = r;
				data[1] = g;
				data[2] = b;
			}
			data += 3;
		}
	}
	return 1;
}

static int memory_allocation_counter = 0;

void *malloc_ex(long size)
{
	void *t;
	t = malloc(size);

	if(t)
		memory_allocation_counter++;
	return t;
}

void free_ex(void *t)
{
	memory_allocation_counter--;
	free(t);
}

int get_memory_allocation_counter()
{
	return memory_allocation_counter;
}

/***********************************************************************************
*
*                        SPECIAL FOR MODULE INTERFACE
*
************************************************************************************/

// Create RGB from GIF, alloc memory
int DP_Create_RGB_from_GIF(const void * gif_file_data, int gif_file_data_len, void ** rgb_data, int * rgb_data_len)
{
	* rgb_data = 0;
	* rgb_data_len = 0;
	return MakeImage_RGB_EX((char *)gif_file_data, gif_file_data_len, (unsigned char **)rgb_data, rgb_data_len);
}

// Destroy RGB, free memory
void DP_Destroy_RGB (const void *rgb_data)
{
	FreeImage_RGB_EX((unsigned char **)&rgb_data);
}
 
// Create GIF from RGB, alloc memory
int DP_Create_GIF_from_RGB(const void * rgb_file_data, int rgb_file_data_len, void ** gif_data, int * gif_data_len)
{
	* gif_data = 0;
	* gif_data_len = 0;
	return MakeImage_GIF_EX((char *)rgb_file_data, (unsigned char **)gif_data, gif_data_len);
}

// Destroy GIF, free memory
void DP_Destroy_GIF (const void *gif_data)
{
	FreeImage_GIF_EX((unsigned char **)&gif_data);
}

int DP_Create_GIF_from_template  (void *  pRGBTemplate,       // <- Образ файла-шаблона
                                  int     nRGBTemplateSize,   // <- Размер образа шаблона 
                                  int     nStrArrSize,        // <- Размер массива строк, которые надо вписать в гиф
                                  char ** strArr,             // <- Массив строк. Строки заканчиваются нулём.
                                  int   * strPosX,            // <- Х-координата соответствующей строки
                                  int   * strPosY,            // <- Y-координата соответствующей строки 
                                  int *pR, int *pG, int *pB,  // <- Цвета соответствующей строки
                                  void  * pRGBFont,           // <- Образ файла-шрифта (шрифт моноширинный)
                                  int     nRGBFontSize,       // <- Размер образа шрифта
                                  void ** pGifRes,            // -> Образ полученного гиф-изображения
                                  int   * nGifResSize         // -> Размер полученного гиф-изображения
                                 )
{
	RGBIMAGE rgb_tmpl;
	RGBIMAGE rgb_font;
	unsigned char * uc_pRGBTemplate = (unsigned char *) pRGBTemplate;
	unsigned char * uc_pRGBFont = (unsigned char *) pRGBFont;
	unsigned char * str;
	int i, j, x_src, y_src, x_dest, y_dest, str_len, index;
	long * l_data;
	int nRGBFontLiterWidth; // Длина одной литеры в шрифте
	int nRGBFontLiterHeight;// Ширина одной литеры в шрифте
	MERGE_COLOR mc;

	// check input parametrs
	if(!pRGBTemplate || nRGBTemplateSize<=0 || nStrArrSize<0 || !strArr || !strPosX || !strPosY || !pRGBFont || !pR || !pG || !pB)
		return 0;

	* pGifRes = 0;
	* nGifResSize = 0;

	// extract RGBTemplate paramerts
	l_data = (long *)uc_pRGBTemplate;
	rgb_tmpl.m_width = l_data[0];
	rgb_tmpl.m_height = l_data[1];
	rgb_tmpl.data = uc_pRGBTemplate + sizeof(long) + sizeof(long);
	if(rgb_tmpl.m_width * rgb_tmpl.m_height * 3  + (int)sizeof(long) + (int)sizeof(long) != nRGBTemplateSize)
		return 0;

	// extract RGBFont paramerts
	l_data = (long *)uc_pRGBFont;
	rgb_font.m_width = l_data[0];
	rgb_font.m_height = l_data[1];
	rgb_font.data = uc_pRGBFont + sizeof(long) + sizeof(long);
	if(rgb_font.m_width * rgb_font.m_height * 3 + (int)sizeof(long) + (int)sizeof(long) != nRGBFontSize)
		return 0;

	if(rgb_font.m_width % 256) return 0;
	
	nRGBFontLiterWidth = rgb_font.m_width / 256;
	nRGBFontLiterHeight = rgb_font.m_height;

	// check font liter size: must be 256 liters
	if(nRGBFontLiterWidth*256 > rgb_font.m_width || nRGBFontLiterHeight > rgb_font.m_height)
		return 0;

	// set MERGE_COLOR struct
	memset(&mc, 0, sizeof(MERGE_COLOR));

	mc.mask |= TRANSPARENT_SET;
	mc.transp_r = 255;
	mc.transp_g = 255;
	mc.transp_b = 255;

	mc.mask |= REPLACE_COLOR_SET;
	// какие цвета заменить
	mc.replace_r = 0;
	mc.replace_r = 0;
	mc.replace_r = 0;

	for(i=0; i<nStrArrSize; i++)
	{
		str = (unsigned char *)strArr[i];
		if(!str) return 0;

		str_len = strlen(str);
		if(!str_len) return 0;

		x_dest = strPosX[i];// куда накладывать изображение, x
		y_dest = strPosY[i];// куда накладывать изображение, y

		x_src = 0;// откуда начинаются литеры в файле шрифте, x
		y_src = 0;// откуда начинаются литеры в файле шрифте, y

		// на какие цвета заменить
		mc.replace_by_r = (unsigned char) pR[i];
		mc.replace_by_g = (unsigned char) pG[i];
		mc.replace_by_b = (unsigned char) pB[i];

		for(j=0; j<str_len; j++)
		{
			index = str[j];

			x_src = index * nRGBFontLiterWidth;

			if(!MergeEx(&rgb_tmpl, &rgb_font, x_dest, y_dest, x_src, y_src, nRGBFontLiterWidth, nRGBFontLiterHeight, &mc))
				return 0;

			x_dest += nRGBFontLiterWidth;
		}
	}	

	// convert rgb_tmpl to GIF
	if(!MakeImage_GIF_EX((char *)uc_pRGBTemplate, (unsigned char**) pGifRes, nGifResSize))
		return 0;

	return 1;
}

// load GIF file to memory
int DP_Load_GIF(char *file_name, void **gif, int *size)
{
	FILE *f;
	long read;
	int ret = 0;

	*gif = 0;
	*size = 0;

	if(!file_name) return 0;

	// загружем файл в память
	f = fopen(file_name, "rb");
	if(!f) return 0;
	fseek(f,0,SEEK_END);

	*size = ftell(f);

	if(!*size) goto EXIT;

	fseek(f, 0, SEEK_SET);
	*gif = (void *)malloc_ex(*size);

	if(!*gif)
	{
		*size = 0;
		goto EXIT;
	}

	read = fread(*gif, *size, 1, f);

	if(read != 1)
	{
		if(*gif)
			free_ex(*gif);
		*gif = 0;
		*size = 0;
		goto EXIT;
	}
	ret = 1;

EXIT:
	fclose(f);
	return ret;
}

// load RGB file to memory
int DP_Load_RGB(char *file_name, void **rgb, int *size)
{
	FILE *f;
	long read;
	int ret = 0;

	*rgb = 0;
	*size = 0;

	if(!file_name) return 0;

	// загружем файл в память
	f = fopen(file_name, "rb");
	if(!f) return 0;
	fseek(f,0,SEEK_END);

	*size = ftell(f);

	if(!*size) goto EXIT;

	fseek(f, 0, SEEK_SET);
	*rgb = (void *)malloc_ex(*size);

	if(!*rgb)
	{
		*size = 0;
		goto EXIT;
	}

	read = fread(*rgb, *size, 1, f);

	if(read != 1)
	{
		if(*rgb)
			free_ex(*rgb);
		*rgb = 0;
		*size = 0;
		goto EXIT;
	}
	ret = 1;

EXIT:
	fclose(f);
	return ret;
}

// save gif image to disk
int DP_Save_GIF(char *file_name, void *gif, int size)
{
	FILE *f;
	int ret = 1;

	if(!file_name) return 0;
	if(!gif) return 0;
	if(size<=0) return 0;

	f = fopen(file_name, "wb");
	if(!f) return 0;

	if(fwrite(gif, (long)size, 1, f) != 1)
		ret = 0;

	fclose(f);
	return ret;
}

// save rgb image to disk
int DP_Save_RGB(char *file_name, void *rgb, int size)
{
	FILE *f;
	int ret = 1;

	if(!file_name) return 0;
	if(!rgb) return 0;
	if(size<=0) return 0;

	f = fopen(file_name, "wb");
	if(!f) return 0;

	if(fwrite(rgb, (long)size, 1, f) != 1)
		ret = 0;

	fclose(f);
	return ret;
}

int DP_ConvertGIF2RGB_File(char *gif_file_name, char *rgb_file_name)
{
	void *gif = 0;
	int size;
	void *rgb = 0;
	int rgb_len;
	int ret = 0;
	
	if(!gif_file_name || !rgb_file_name)
		goto EXIT;

	if(!DP_Load_GIF(gif_file_name, &gif, &size))
		goto EXIT;

	if(!DP_Create_RGB_from_GIF(gif, size, &rgb, &rgb_len))
		goto EXIT;
	
	if(!DP_Save_RGB(rgb_file_name, rgb, rgb_len))
		goto EXIT;

	ret = 1;

EXIT:
	if(gif) DP_Destroy_GIF(gif);
	if(rgb) DP_Destroy_RGB(rgb);

	return ret;
}

int DP_ConvertRGB2GIF_File(char *rgb_file_name, char *gif_file_name)
{
	void *gif = 0;
	int size = 0;
	void *rgb = 0;
	int gif_len = 0;
	int ret = 0;
	
	if(!gif_file_name || !rgb_file_name)
		goto EXIT;

	if(!DP_Load_RGB(rgb_file_name, &rgb, &size))
		goto EXIT;

	if(!DP_Create_GIF_from_RGB(rgb, size, &gif, &gif_len))
		goto EXIT;
	
	if(!DP_Save_GIF(gif_file_name, gif, gif_len))
		goto EXIT;

	ret = 1;

EXIT:
	if(gif) DP_Destroy_GIF(gif);
	if(rgb) DP_Destroy_RGB(rgb);

	return ret;
}
