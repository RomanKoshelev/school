/******************************************************************************
* File name:   mod_counter_dp_img.h
*
* Version:     1.1
*
* Author:      Dima Polyakov <dima_twin@mtu-net.ru>
*
* Purpose:     Module functions
*
*
* Created:     16 March, 2000
*
* Last update: 16 March, 2000 by Dima Polyakov
*******************************************************************************/

#ifndef __DP_GIF_RGB_IMAGE_ROUTINES__
#define __DP_GIF_RGB_IMAGE_ROUTINES__

/***********************************************************************************
*
*                        SPECIAL MODULE INTERFACE
*
************************************************************************************/

int DP_Create_GIF_from_template  (void *  pRGBTemplate,       // <- ����� �����-�������
                                  int     nRGBTemplateSize,   // <- ������ ������ ������� 
                                  int     nStrArrSize,        // <- ������ ������� �����, ������� ���� ������� � ���
                                  char ** strArr,             // <- ������ �����. ������ ������������� ����.
                                  int   * strPosX,            // <- �-���������� ��������������� ������
                                  int   * strPosY,            // <- Y-���������� ��������������� ������ 
                                  int *pR, int *pG, int *pB,  // <- ����� ��������������� ������
                                  void  * pRGBFont,           // <- ����� �����-������ (����� ������������)
                                  int     nRGBFontSize,       // <- ������ ������ ������
                                  void ** pGifRes,            // -> ����� ����������� ���-�����������
                                  int   * nGifResSize         // -> ������ ����������� ���-�����������
                                 );

// Create RGB from GIF, alloc memory
int DP_Create_RGB_from_GIF(
       const void * gif_file_data,              // <- ����� GIF �����
       int          gif_file_data_len,          // <- ������ GIF ������
       void      ** rgb_data,                   // -> ����� RGB �����������
       int        * rgb_data_len                // -> �����  RGB �����������
       );

// Destroy RGB, free memory
void DP_Destroy_RGB (const void *rgb_data);
 
 
// Create GIF from RGB, alloc memory
int DP_Create_GIF_from_RGB(
       const void * rgb_file_data,               // <- �����  RGB �����
       int          rgb_file_data_len,           // <- ������ RGB ������
       void      ** gif_data,                    // -> �����  GIF �����������
       int        * gif_data_len                 // -> �����  GIF �����������
       );

// Destroy GIF, free memory
void DP_Destroy_GIF (const void *gif_data);

int DP_Load_GIF(char *file_name, void **gif, int *size);
int DP_Load_RGB(char *file_name, void **rgb, int *size);
int DP_Save_GIF(char *file_name, void *gif, int size);
int DP_Save_RGB(char *file_name, void *rgb, int size);

int DP_ConvertGIF2RGB_File(char * gif_name, char * rgb_name);
int DP_ConvertRGB2GIF_File(char * rgb_name, char * gif_name);

#endif //__DP_GIF_RGB_IMAGE_ROUTINES__
