#include <stdio.h>
#include "dp_img.h"

static double perfomance;

#ifdef _WIN32
	#include "windows.h"
	static LARGE_INTEGER tBefore, tAfter, i64PerfFrequency;
	static __int64 dif;

	#define TIMER_START()												\
		QueryPerformanceFrequency( &i64PerfFrequency );			\
		Sleep( 0 );															\
		QueryPerformanceCounter( &tBefore )

	#define TIMER_END()													\
		QueryPerformanceCounter( &tAfter );							\
		dif = tAfter.QuadPart - tBefore.QuadPart;					\
		perfomance = (double)dif / i64PerfFrequency.QuadPart
#else
	#define TIMER_START()
	#define TIMER_END()
#endif

#define CHECK(x, txt)	\
	if(x)						\
	{							\
		puts(txt);			\
		return -1;			\
	}							\

// Additional function
int SAVE_DATA(char *file_name, void *data, long length);
int LOAD_DATA(char *file_name, void **data, long *length);
void FREE_DATA(void **data);

int test2();

int main()
{
	test2();
	return 0;
}

#define NUM_STR	6
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//` test2                                                                     []     
//                                                                            []
int test2()
{
	char * gif_template;	long gif_template_len;
	char * rgb_template;	long rgb_template_len;
	char * gif_font;		long gif_font_len;
	char * rgb_font;		long rgb_font_len;
	char * gif_output;	long gif_output_len;

	char *str_arr	[]	=	{"1234", "456", "789", "654", "973", "873"};
	int	pos_x		[]	=	{  44,     44,    44,    44,    44,    44};
	int	pos_y		[]	=	{  45,     55,    65,    76,    86,    96};
	int	clr_R		[]	=	{ 196,      0,     0,     0,     0,     0};
	int	clr_G		[]	=	{   0,    196,     0,     0,     0,     0};
	int	clr_B		[]	=	{   0,      0,   196,     0,     0,     0};

	DP_Load_GIF					("template.gif", &gif_template, &gif_template_len);
	DP_Create_RGB_from_GIF	(gif_template, gif_template_len, &rgb_template, &rgb_template_len);
	DP_Destroy_GIF				(gif_template);

	DP_Load_GIF					("font_0.gif", &gif_font, &gif_font_len);
	DP_Create_RGB_from_GIF	(gif_font, gif_font_len, &rgb_font, &rgb_font_len);
	DP_Destroy_GIF				(gif_font);


	DP_Create_GIF_from_template(	rgb_template, 			// <- Образ файла-шаблона                              
											rgb_template_len,		// <- Размер образа шаблона                            
											6, 						// <- Размер массива строк, которые надо вписать в гиф 
											str_arr,					// <- Массив строк. Строки заканчиваются нулём.        
											pos_x, 					// <- Х-координата соответствующей строки              
											pos_y, 					// <- Y-координата соответствующей строки              
											clr_R, clr_G, clr_B,	// <- Цвета соответствующей строки                     
											rgb_font, 				// <- Образ файла-шрифта (шрифт моноширинный)          
											rgb_font_len,			// <- Размер образа шрифта                             
											&gif_output, 			// -> Образ полученного гиф-изображения                
											&gif_output_len);		// -> Размер полученного гиф-изображения               

	DP_Save_GIF		("output.gif", gif_output, gif_output_len);

	DP_Destroy_RGB (rgb_template);
	DP_Destroy_RGB (rgb_font);
	DP_Destroy_GIF (gif_output);

	return 1;
}
//____________________________________________________________________________[]













