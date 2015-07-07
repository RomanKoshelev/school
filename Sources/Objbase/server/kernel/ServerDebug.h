/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ServerDebug.h															[]
[] Date:            01/22/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Writing debug info to HTML page									[]
[]____________________________________________________________________________[]
*/
#ifndef ServerDebug_H
#define ServerDebug_H


#define SD_ERROR_SIZE	10240
extern char SD_ERROR[];
bool SD_ASSERT(const char * sFILE, int line, const char * sCONDITION, const char * sCOMMENT);
int	PRINT_PERCENT	(int i, int N);
bool	RANDOM_PERCENT	(int Threshold, int nBASE=100);


//----------------------------------------------------------------------------[] 
#ifdef WIN32  // WINDOWS
	#ifdef _DEBUG
		#define DBG_STOP_ASK																		\
		{																								\
			if (::MessageBox (NULL," Останавливаться для отладки?","STOP",			\
				MB_YESNO|MB_DEFBUTTON1|MB_ICONSTOP)==IDYES)								\
			{																							\
			__asm { int 3 };																		\
			}																							\
		}
		#define DBG_STOP {__asm { int 3 }}
	#else
		#define DBG_STOP {}
		#define DBG_STOP_ASK {}
	#endif
#else			// UNIX
	#define DBG_STOP {}
	#define DBG_STOP_ASK {}
#endif
//----------------------------------------------------------------------------[] 


//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]
extern char * STR_OSHIBKA;
extern char * STR_NE_VYPOLNJAETTSJA_USLOVIE;
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]


//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]
void SERVER_DEBUG_ERROR_VA(const char *strTemplate, ...);
void SERVER_DEBUG_TEXT_VA(const char *strTemplate, ...);
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-[]


//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR(strTemplate)													\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate);									\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_1(strTemplate, a1)											\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1);								\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_2(strTemplate, a1,a2)										\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2);							\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_3(strTemplate, a1,a2,a3)									\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2,a3);						\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_4(strTemplate, a1,a2,a3,a4)								\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2,a3,a4);					\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_5(strTemplate, a1,a2,a3,a4,a5)							\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2,a3,a4,a5);				\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_6(strTemplate, a1,a2,a3,a4,a5,a6)						\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2,a3,a4,a5,a6);			\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_7(strTemplate, a1,a2,a3,a4,a5,a6,a7)					\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, strTemplate, a1,a2,a3,a4,a5,a6,a7);		\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ERROR_8(strTemplate, a1,a2,a3,a4,a5,a6,a7,a8)				\
	{snprintf (SD_ERROR, SD_ERROR_SIZE, SD_ERROR_SIZE, strTemplate, a1,a2,a3,a4,a5,a6,a7,a8);\
	theServerDebug.Error(__FILE__, __LINE__, SD_ERROR);								\
	if (SD_ASSERT (__FILE__, __LINE__, STR_OSHIBKA, SD_ERROR))						\
		DBG_STOP_ASK}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ASSERT(Condition, Comment)											\
if (!(Condition))																					\
{																										\
	snprintf (SD_ERROR, SD_ERROR_SIZE, STR_NE_VYPOLNJAETTSJA_USLOVIE, #Condition);\
	theServerDebug.Assert(__FILE__, __LINE__, SD_ERROR, Comment);					\
	if (SD_ASSERT (__FILE__, __LINE__, SD_ERROR, Comment))							\
	{																									\
		DBG_STOP_ASK																				\
		return;																						\
	}																									\
}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_ASSERT_RETURN(Condition, Comment, RetVal)						\
if (!(Condition))																					\
{																										\
	snprintf (SD_ERROR, SD_ERROR_SIZE, STR_NE_VYPOLNJAETTSJA_USLOVIE, #Condition);\
	theServerDebug.Assert(__FILE__, __LINE__, SD_ERROR, Comment);					\
	if (SD_ASSERT (__FILE__, __LINE__, SD_ERROR, Comment))							\
	{																									\
		DBG_STOP_ASK																				\
		return RetVal;																				\
	}																									\
}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_VALUE(val)																\
{																										\
	theServerDebug.Value(__FILE__, __LINE__, #val, val);								\
}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_TEXT(str)																\
{																										\
	theServerDebug.Text(__FILE__, __LINE__, str);										\
}
//----------------------------------------------------------------------------[] 
#define SERVER_DEBUG_PLACE																		\
{																										\
	theServerDebug.Place(__FILE__, __LINE__);												\
}
//----------------------------------------------------------------------------[] 


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CServerDebug
[]                                                                            []
[]____________________________________________________________________________[]
*/
class CServerDebug
{
public:
	FILE *		m_LogFile;
	static bool	m_bCreated;
	static char m_Template[10240];
	static char m_Entrance[10240];

public:
	CServerDebug (const char * sPrefix);
	~CServerDebug();

	void Write (const char	* sFILE, int line, const char * s4="", const char * s5="", const char * s6="",const char * s7="",const char * s8="",const char * s9="",const char * s10="");
	void Error (const char  * sFILE, int line, const char * sCOMMENT);
	void Assert(const char	* sFILE, int line, const char * sCONDITION, const char * sCOMMENT);
	void Value (const char	* sFILE, int line, const char * sVALUE_NAME, int nValue);
	void Value (const char	* sFILE, int line, const char * sVALUE_NAME, const char  * sValue);
	void Value (const char	* sFILE, int line, const char * sVALUE_NAME, const void  * pValue);
	void Text  (const char	* sFILE, int line, const char * pText);
	void Place (const char	* sFILE, int line);

	const char * GetStack ();
};
extern CServerDebug theServerDebug;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Очистка директории c файловой системой												[]
//                                                                            []
#ifdef WIN32 // WINDOWS
#include "windows.h"
#include <conio.h>
#include <io.h>
class CClearFof
{
// В своём конструкторе класс удаляет всю встроенную файловую систему
// Объект этого класса должен создаваться самым первым во всей программе.
protected:	void About_class_CClearFof(){};

public: CClearFof(bool bClearBeforeRun)
	{
		if (bClearBeforeRun)
		{
			bool bNT = GetVersion() < 0x80000000;
			if (bNT) // Windows NT
			{
				system ("cmd /c if exist .\\files\\*.* echo Y | del .\\files\\*.* >NUL");
			}
			else		// Windows 95/98
			{
			struct _finddata_t fi;
			long hFile;
			char fname[256];
			if( (hFile = _findfirst( ".\\files\\*.*", &fi )) != -1L )
				do
				{	
					strcpy (fname, ".\\files\\");
					strcat (fname, fi.name);
					/*
					if( _unlink( fname ) == -1 )
						perror("Could not delete\n\r");
					else
						printf( "Deleted '%s'\n\r", fi.name);
					*/
					_unlink (fname);
				}
				while (!_findnext (hFile, &fi));
				_findclose (hFile);
			}
		}
	}
};
#else // UNIX
#include <stdlib.h>
class CClearFof
{
public: CClearFof(bool bClearBeforeRun)
	{
		if (bClearBeforeRun)
			system ("rm files/*");
	}
};
#endif
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` DEBUG_STACK_RECORD                                                        []                  
//                                                                            []
struct DEBUG_STACK_RECORD
{
	const	char *	m_Name;
	const	char *	m_FileName;
	int				m_Line;
};
//----------------------------------------------------------------------------[] 
#define	DEBUG_STACK_MAX_SIZE 10240
extern	DEBUG_STACK_RECORD	DEBUG_STACK_RECORD_ARR [];
extern	int						DEBUG_STACK_RECORD_NUM;
//----------------------------------------------------------------------------[] 
struct DEBUG_STACK_CONTROL_ITEM
{
	int m_DEBUG_STACK_RECORD_NUM;
	DEBUG_STACK_CONTROL_ITEM (const char * a_Name, const char * a_FileName, int a_Line)
	{
		m_DEBUG_STACK_RECORD_NUM = DEBUG_STACK_RECORD_NUM;
		DEBUG_STACK_RECORD_NUM ++;
		DEBUG_STACK_RECORD_ARR[DEBUG_STACK_RECORD_NUM].m_Name			= a_Name;
		DEBUG_STACK_RECORD_ARR[DEBUG_STACK_RECORD_NUM].m_FileName	= a_FileName;
		DEBUG_STACK_RECORD_ARR[DEBUG_STACK_RECORD_NUM].m_Line			= a_Line;
	}

	~DEBUG_STACK_CONTROL_ITEM ()
	{
		DEBUG_STACK_RECORD_NUM = m_DEBUG_STACK_RECORD_NUM;
	}
};
//----------------------------------------------------------------------------[] 
#define	DEBUG_STACK 																			\
	DEBUG_STACK_CONTROL_ITEM	_dbg_stack			("..",__FILE__,__LINE__)
//----------------------------------------------------------------------------[] 
#define	DEBUG_STACK_NAME(name) 																\
	DEBUG_STACK_CONTROL_ITEM	_dbg_stack_##name	(#name,__FILE__,__LINE__)
//____________________________________________________________________________[]





#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

