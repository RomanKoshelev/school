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
                                 );

// Create RGB from GIF, alloc memory
int DP_Create_RGB_from_GIF(
       const void * gif_file_data,              // <- образ GIF файла
       int          gif_file_data_len,          // <- размер GIF образа
       void      ** rgb_data,                   // -> образ RGB изображения
       int        * rgb_data_len                // -> длина  RGB изображения
       );

// Destroy RGB, free memory
void DP_Destroy_RGB (const void *rgb_data);
 
 
// Create GIF from RGB, alloc memory
int DP_Create_GIF_from_RGB(
       const void * rgb_file_data,               // <- образ  RGB файла
       int          rgb_file_data_len,           // <- размер RGB образа
       void      ** gif_data,                    // -> образ  GIF изображения
       int        * gif_data_len                 // -> длина  GIF изображения
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
