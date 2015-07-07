/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            OBServer_Interface.cpp                                    []
[] Date:            01.04.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Интерфейс с внешними модулями                             []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                      
#define	USES_OBServer_Interface_h
#include "main.h"

// Буфер для текстового представления значения выходного аргумента:
static	char argValueStrBuffer	[MAX_ARG_VALUE_LENGTH];

// Буфер выходного потока:
			char OutStreamBuffer		[OUT_STREAM_BUFFER_SIZE];


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Функции распаковки аргументов                                             []                             
[]                                                                            []
[]____________________________________________________________________________[]
*/

//______________________________________________________________________________
//                                                                            []
//` bool                                                                      []    
//                                                                            []
bool GetArg(const char * inStr, bool& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.

	if (isdigit(*pName) == 0)				// Ошибка: значение - не цифра.
		return false;

// Берём значение аргумента:
	argValue = ((*pName) != '0');

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` byte                                                                      []    
//                                                                            []
bool GetArg(const char * inStr, byte& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.
/*
	if (isdigit(*pName) == 0)
		return false;
*/
// Берём значение аргумента:
	int nTmpVal=0;
	if (sscanf (pName, "%d", &nTmpVal) != 1)
		return false;
	argValue = (byte)nTmpVal;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` int                                                                       []   
//                                                                            []
bool GetArg(const char * inStr, int& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.
/*
	if ((*pName != '-') && (isdigit(*pName) == 0))
		return false;
*/
// Берём значение аргумента:
	int nTmpVal=0;
	if (sscanf (pName, "%d", &nTmpVal) != 1)
		return false;
	argValue = nTmpVal;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` time_t                                                                    []      
//                                                                            []
bool GetArg(const char * inStr, time_t& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.
/*
	if ((*pName != '-') && (isdigit(*pName) == 0))
		return false;
*/
// Берём значение аргумента:
	time_t nTmpVal=0L;
	if (sscanf (pName, "%li", &nTmpVal) != 1)
		return false;
	argValue = nTmpVal;

	return true;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` identifier                                                                []          
//                                                                            []
bool GetArg(const char * inStr, identifier& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.
/*
	if (isdigit(*pName) == 0)
		return false;
*/
// Берём значение аргумента:
	if (sscanf(pName, "%lu", &argValue) != 1)
		return false;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` float                                                                     []     
//                                                                            []
bool GetArg(const char * inStr, float& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.
/*
	if ((isdigit(*pName) == 0) && ((*pName)!= '.'))	
		return false;
*/
// Берём значение аргумента:
	float fTmpVal=0.0;
	if (sscanf (pName, "%f", &fTmpVal) != 1)
		return false;
	argValue = fTmpVal;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` string                                                                    []      
//                                                                            []
bool GetArg(const char * inStr, string& argValue, const char* argName)
{
	GET_ARG_START;

	if (*pName != FIELD_HEADER_CHAR)		// Ошибка: нет маркера начала значения.
		return false;
	pName++;										// На начало значения.

	size_t end_index = strcspn(pName, ARG_NAME_HEADER_STR FIELD_HEADER_STR);
	if (pName[end_index] == FIELD_HEADER_CHAR)
		return false;			// Ошибка - встретился разделитель полей для скалярного параметра.

	argValue.Copy(pName, end_index);		// Скопировать всё до маркера или до конца строки.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` bool_arr                                                                  []        
//                                                                            []
bool GetArg(const char * inStr, bool_arr& argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	bool_arr	tempArr;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.

		if ((*pName != '0') && (*pName != '1'))	// Ошибка - это не булевское значение.	
			return false;
		
		tempArr.Add((*pName) != '0');					// Добавим во временный массив.

		pName++;												// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;																// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` byte_arr                                                                  []        
//                                                                            []
bool GetArg(const char * inStr, byte_arr& argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	byte_arr	tempArr;
	size_t	end_index;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.
/*
		if (isdigit(*pName) == 0)						// Ошибка - это не цифра.	
			return false;
*/		
	// Берём значение аргумента:
		int nTmpVal=0;
		if (sscanf (pName, "%d", &nTmpVal) != 1)
			return false;
		tempArr.Add(byte(nTmpVal));				// Добавим во временный массив.
		
		end_index = strcspn(pName, FIELD_HEADER_STR ARG_NAME_HEADER_STR);	// Поиск маркера.
		
		pName += end_index;								// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;																// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` int_arr                                                                   []       
//                                                                            []
bool GetArg(const char * inStr, int_arr& argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	int_arr	tempArr;
	size_t	end_index;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.
/*
		if (isdigit(*pName) == 0)						// Ошибка - это не цифра.	
			return false;
*/		
	// Берём значение аргумента:
		int nTmpVal=0;
		if (sscanf (pName, "%d", &nTmpVal) != 1)
			return false;
		tempArr.Add(nTmpVal);						// Добавим во временный массив.
		
		end_index = strcspn(pName, FIELD_HEADER_STR ARG_NAME_HEADER_STR);	// Поиск маркера.
		
		pName += end_index;								// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;									// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` identifier_arr                                                            []              
//                                                                            []
bool GetArg(const char * inStr, identifier_arr&	argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	identifier_arr	tempArr;
	identifier		tempID;

	size_t			end_index;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.
/*
		if (isdigit(*pName) == 0)						// Ошибка - это не цифра.	
			return false;
*/			
		if (sscanf(pName, "%lu", &tempID) != 1)	// Ошибка сканирования.
			return false;

		tempArr.Add(tempID);								// Добавим во временный массив.
		
		end_index = strcspn(pName, FIELD_HEADER_STR ARG_NAME_HEADER_STR);	// Поиск маркера.
		
		pName += end_index;								// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;									// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` float_arr                                                                 []         
//                                                                            []
bool GetArg(const char * inStr, float_arr& argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	float_arr	tempArr;
	size_t		end_index;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.
		
	// Берём значение аргумента:
		float fTmpVal=0.0;
		if (sscanf (pName, "%f", &fTmpVal) != 1)
			return false;
		tempArr.Add(fTmpVal);							// Добавим во временный массив.

		end_index = strcspn(pName, FIELD_HEADER_STR ARG_NAME_HEADER_STR);	// Поиск маркера.
		
		pName += end_index;								// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;									// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` string_arr                                                                []          
//                                                                            []
bool GetArg(const char * inStr, string_arr& argValue, const char* argName)
{
	GET_ARG_START;

	if ((*pName == ARG_NAME_HEADER_CHAR) || (*pName == 0))
	{	// Пустой массив
		argValue.Delete();
		return true;
	}

	string_arr	tempArr;
	string		tempStr;
	size_t		end_index;

	do
	{
		if (*pName != FIELD_HEADER_CHAR)				// Ошибка: нет маркера начала значения.
			return false;
		pName++;												// На начало значения.

		end_index = strcspn(pName, FIELD_HEADER_STR ARG_NAME_HEADER_STR);	// Поиск маркера.

		tempStr.Copy(pName, end_index);
		tempArr.Add(tempStr);
		
		
		pName += end_index;								// Устанавливаем указатель на маркер.

	} while (((*pName) != ARG_NAME_HEADER_CHAR) && ((*pName) != 0));	// Пока не дойдём до конца массива или конца строки.

	argValue = tempArr;																// Скопируем в исходный массив.

	return true;
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Функции упаковки аргументов                                               []                           
[]                                                                            []
[]____________________________________________________________________________[]
*/



//______________________________________________________________________________
//                                                                            []
//` bool                                                                      []    
//                                                                            []
bool PackArg(const char * outStr, bool& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(&argValueStrBuffer[0],"%c%s%c%c", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue ? '1':'0');

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` byte                                                                      []    
//                                                                            []
bool PackArg(const char * outStr, byte& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%u", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, (unsigned int)argValue);

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` int                                                                       []   
//                                                                            []
bool PackArg(const char * outStr, int& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%d", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue);

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` time_t                                                                    []      
//                                                                            []
bool PackArg(const char * outStr, time_t& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%li", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue);

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` identifier                                                                []          
//                                                                            []
bool PackArg(const char * outStr, identifier& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%lu", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue);

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` float                                                                     []     
//                                                                            []
bool PackArg(const char * outStr, float& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%.3f", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue);

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` string                                                                    []      
//                                                                            []
bool PackArg(const char * outStr, string& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;
	
	if (argValue.len() > (MAX_ARG_VALUE_LENGTH-MAX_ARG_NAME_LENGTH))
	{
		char SSS[128];
		memcpy (SSS, argValue.c_str(), 100);
		SSS[100] = 0;
		SERVER_DEBUG_ERROR_2 ("PackArg: Размер возвращаемой строки больше чем MAX_ARG_NAME_LENGTH (%d), '%s'. Строка обрезана.", MAX_ARG_VALUE_LENGTH, SSS);
		argValue[MAX_ARG_VALUE_LENGTH - MAX_ARG_NAME_LENGTH] = 0;
	}
		 
// Переводим значение аргумента в текстовый вид:
	sprintf(argValueStrBuffer,"%c%s%c%s", ARG_NAME_HEADER_CHAR, argName, FIELD_HEADER_CHAR, argValue.c_str());

// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` bool_arr                                                                  []        
//                                                                            []
bool PackArg(const char * outStr, bool_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		sprintf(argValueStrBuffer,"%c%c", FIELD_HEADER_CHAR, (argValue[i]==true) ? '1' : '0');
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` byte_arr                                                                  []        
//                                                                            []
bool PackArg(const char * outStr, byte_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		sprintf(argValueStrBuffer,"%c%u", FIELD_HEADER_CHAR, (unsigned int)argValue[i]);
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` int_arr                                                                   []       
//                                                                            []
bool PackArg(const char * outStr, int_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		sprintf(argValueStrBuffer,"%c%d", FIELD_HEADER_CHAR, argValue[i]);
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` identifier_arr                                                            []              
//                                                                            []
bool PackArg(const char * outStr, identifier_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		sprintf(argValueStrBuffer,"%c%lu", FIELD_HEADER_CHAR, argValue[i]);
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` float_arr                                                                 []         
//                                                                            []
bool PackArg(const char * outStr, float_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		sprintf(argValueStrBuffer,"%c%.3f", FIELD_HEADER_CHAR, argValue[i]);
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` string_arr                                                                []          
//                                                                            []
bool PackArg(const char * outStr, string_arr& argValue, const char* argName, int& BufferPos)
{
	PACK_ARG_START;

// Записываем имя аргумента :
	sprintf(argValueStrBuffer,"%c%s", ARG_NAME_HEADER_CHAR, argName);
// Кладём в выходной буфер:	
	PUT_TO_STREAM_BUFFER;
// Записываем каждый элемент массива:
	for (int i = 0; i < argValue.Size(); i++)
	{
		if (argValue[i].len() > (MAX_ARG_VALUE_LENGTH-MAX_ARG_NAME_LENGTH))
		{
			char SSS[128];
			memcpy (SSS, argValue[i].c_str(), 100);
			SSS[100] = 0;
			SERVER_DEBUG_ERROR_2 ("PackArg: Размер возвращаемой строки больше чем MAX_ARG_NAME_LENGTH (%d), '%s'. Строка обрезана.", MAX_ARG_VALUE_LENGTH, SSS);
			argValue[i][MAX_ARG_VALUE_LENGTH - MAX_ARG_NAME_LENGTH] = 0;
		}
		sprintf(argValueStrBuffer,"%c%s", FIELD_HEADER_CHAR, (string(argValue[i])).c_str());
	// Кладём в выходной буфер:	
		PUT_TO_STREAM_BUFFER;
	}

	return true;
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` OBServer_PackErrorDescription                                             []
//                                                                            []
bool OBServer_PackErrorDescription(int result, int& BufferPos)
{
	for (int i = 0; i < theOBServer_ERROR_DESCRIPTION_ARR.GetSize(); i++)
	{
		if (theOBServer_ERROR_DESCRIPTION_ARR[i].nEnum == result){
			sprintf(argValueStrBuffer, "%s", theOBServer_ERROR_DESCRIPTION_ARR[i].sDesc.c_str());
			int BlockLength = strlen(argValueStrBuffer);
			memcpy(&OutStreamBuffer[BufferPos], argValueStrBuffer, BlockLength + 1);
			BufferPos += BlockLength;
			return true;
		}
	}

	SERVER_DEBUG_ERROR_1 ("OBServer_PackErrorDescription: Unrecognized error %d", result);

	sprintf(argValueStrBuffer, "Unrecognized error.");
	int BlockLength = strlen(argValueStrBuffer);
	memcpy(&OutStreamBuffer[BufferPos], argValueStrBuffer, BlockLength + 1);
	BufferPos += BlockLength;
	
	return false;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` OBServer_Interface_Free                                                   []                 
//                                                                            []
void OBServer_Interface_Free(void ** ppData)
{
	if (*ppData != NULL)
	{
		delete [] ((pbyte)(*ppData));
		* ppData = NULL;
	}
	return;
}
//____________________________________________________________________________[]


#ifndef	HELPER_DISABLED
//______________________________________________________________________________
//                                                                            []
//` OBServer_Help                                                             []
//                                                                            []
void OBServer_Help (void ** ppData, 
					string_arr& FnNames, 
					string_arr& FnDesc, 
					CPtr<FUNCTION_ARGS>& REGISTERED_FUNCTIONS_ARGS, 
					const char * InputArgs)
{
	int OBServer_result = OBServer_OK;

	OBServer_WRAPPER_START;

	string	OutArgs;

	OutArgs.Format(
		"%ca1%ca2%ca3%ca4%ca5%ca6%ca7%ca8",
		ARG_NAME_HEADER_CHAR, ARG_NAME_HEADER_CHAR,
		ARG_NAME_HEADER_CHAR, ARG_NAME_HEADER_CHAR,
		ARG_NAME_HEADER_CHAR, ARG_NAME_HEADER_CHAR, 
		ARG_NAME_HEADER_CHAR, ARG_NAME_HEADER_CHAR);


// Список функций с описаниями
	int FuncNum = -1;
	if (!GetArg(InputArgs, FuncNum, "a1"))
	{
	// Запись имён функций в выходной буфер:
		PackArg(OutArgs.c_str(), FnNames,	"a1",	BufferPos);
		PackArg(OutArgs.c_str(), FnDesc,		"a2",	BufferPos);
	}
	else
// Описание аргументов функции
	{
		if ((FuncNum >= 0) && (FuncNum < REGISTERED_FUNCTIONS_ARGS.Size()))
		{
		// Функция
			PackArg(OutArgs.c_str(), FnNames[FuncNum],	"a1",	BufferPos);
			PackArg(OutArgs.c_str(), FnDesc[FuncNum],		"a2",	BufferPos);

		// Входные аргументы
			PackArg(	OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].InArgs_Type,
						"a3",
						BufferPos);
			PackArg(	OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].InArgs_Name,
						"a4",
						BufferPos);
			PackArg( OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].InArgs_Description,
						"a5",
						BufferPos);

		// Выходные аргументы
			PackArg(	OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].OutArgs_Type,
						"a6",
						BufferPos);
			PackArg(	OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].OutArgs_Name,
						"a7",
						BufferPos);
			PackArg(	OutArgs.c_str(), 
						REGISTERED_FUNCTIONS_ARGS[FuncNum].OutArgs_Description,
						"a8",
						BufferPos);
		}
		else
		{
			OBServer_result = OBServer_SYSTEM_ERROR;
		}

	}

	if (OBServer_result	== OBServer_OK)
	{
	}

	OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Осмысленные имена типов для php3
//                                                                            []
const char * CONVERT_ARG_TYPE_NAME(const char * raw_name)
{
	string RawName = raw_name;

	if (RawName == "identifier")		return "id";
	if (RawName == "int")				return "int";
	if (RawName == "byte")				return "byte";
	if (RawName == "bool")				return "bool";
	if (RawName == "float")				return "float";
	if (RawName == "string")			return "string";
	if (RawName == "time_t")			return "time";

	if (RawName == "identifier_arr") return "id[]";
	if (RawName == "int_arr")			return "int[]";
	if (RawName == "byte_arr")			return "byte[]";
	if (RawName == "bool_arr")			return "bool[]";
	if (RawName == "float_arr")		return "float[]";
	if (RawName == "string_arr")		return "string[]";
	if (RawName == "time_t_arr")		return "time[]";

	return "Wrong type!";
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` Функции определения типов аргументов проблемных функций
//                                                                            []
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (identifier);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (int);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (byte);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (bool);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (float);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (string);
MAKE_IMPLEMENTATION__GET_FUNCTION_ARG_TYPE (time_t);
//____________________________________________________________________________[]


#endif


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
