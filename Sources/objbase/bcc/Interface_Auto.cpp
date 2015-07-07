/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Auto.cpp                                        []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Интерфейсные функции для работы с базой данных.           []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________[]
*/
#include "BX_Interface.h"



//______________________________________________________________________________
//                                                                            []
// Диспетчер вызовов прикладных фунций                                        []
//                                                                            []
void CGI_Interface (const char* CGI_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)
{
// Поиск зарегистрированной функции
   FNC_BEGIN;
   {
   // EnumObject
      FNC        (BX_EnumObject_New, "Создание или изменение параметров перечислителей типа ObjType.");
			FNC_IN  (BX_EnumObject, ObjType, "Строка с названием типа объекта: {Country, City, Domain,ISP}.");
			FNC_IN  (BX_EnumObject, Name, "Массив названий (на всех языках системы) перечислителя типа ObjType.");
			FNC_IN  (BX_EnumObject, objID, "Если не указан, то создаётся новый объект");
			FNC_OUT (BX_EnumObject, objID, "В случае создания объекта = ID созданного объекта.");
      FNC        (BX_EnumObject_GetData, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, Name, "");
			FNC_IN  (BX_EnumObject, objID, "");
      FNC        (BX_EnumObject_GetNamesAndIDs, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, objID, "");
			FNC_OUT (BX_EnumObject, objIDs, "");
			FNC_OUT (BX_EnumObject, Name, "");
      FNC        (BX_EnumObject_Delete, "");
			FNC_IN  (BX_EnumObject, ObjType, "");
			FNC_IN  (BX_EnumObject, objID, "");
			FNC_OUT (BX_EnumObject, objID, "");

   // Language
      FNC        (BX_Language_New, "Добавление языка. В objID возвращается идентификатор созданного объекта.");
			FNC_IN  (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_IN  (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках.");
			FNC_IN  (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_OUT (BX_Language, objID, "Идентификатор объекта.");
      FNC        (BX_Language_PutData, "Изменение параметров существующего языка.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");
			FNC_IN  (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_IN  (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках.");
			FNC_IN  (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
      FNC        (BX_Language_GetNamesAndIDs, "Получение названий всех языков, зарегистрированных в системе на языке #1. Названия возвращаются в поле Name[] входной структуры. Соответствующие идентификаторы возвращаются в поле objIDs[] входной структуры.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");
			FNC_OUT (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках.");
			FNC_OUT (BX_Language, objIDs, "Идентификаторы объектов.");
      FNC        (BX_Language_GetData, "Получение информации о языке с указанным ID.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");
			FNC_OUT (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_OUT (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках.");
			FNC_OUT (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_OUT (BX_Language, No, "Порядковый номер языка");
      FNC        (BX_Language_Delete, "Удаление языка.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");

   // QQQQQ
      FNC        (BX_QQQQQ_GetData, "Получение информации о языке с указанным ID.");
   }
// Вызов обнаруженной функции или сообщение об ошибке.
   FNC_END;
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
// Создание или изменение параметров перечислителей типа ObjType.
//                                                                            []
void CGI_BX_EnumObject_New (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (ObjType);
   GET_ARG (Name);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_EnumObject_New (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_GetData ()
//                                                                            []
void CGI_BX_EnumObject_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (ObjType);
   GET_ARG (Name);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_EnumObject_GetData (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
   // Выходных аргументов нет.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_GetNamesAndIDs ()
//                                                                            []
void CGI_BX_EnumObject_GetNamesAndIDs (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (ObjType);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_EnumObject_GetNamesAndIDs (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (Name);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// BX_EnumObject_Delete ()
//                                                                            []
void CGI_BX_EnumObject_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_EnumObject_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (ObjType);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_EnumObject_Delete (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Добавление языка. В objID возвращается идентификатор созданного объекта.
//                                                                            []
void CGI_BX_Language_New (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// Вызвать проблемную функцию:
   cgi_result = BX_Language_New (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (objID);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение параметров существующего языка.
//                                                                            []
void CGI_BX_Language_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (objID);
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// Вызвать проблемную функцию:
   cgi_result = BX_Language_PutData (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
   // Выходных аргументов нет.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение названий всех языков, зарегистрированных в системе на языке #1. Названия возвращаются в поле Name[] входной структуры. Соответствующие идентификаторы возвращаются в поле objIDs[] входной структуры.
//                                                                            []
void CGI_BX_Language_GetNamesAndIDs (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_Language_GetNamesAndIDs (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (objIDs);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение информации о языке с указанным ID.
//                                                                            []
void CGI_BX_Language_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_Language_GetData (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
      PACK_ARG (OwnName);
      PACK_ARG (Name);
      PACK_ARG (Language);
      PACK_ARG (No);
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление языка.
//                                                                            []
void CGI_BX_Language_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        cgi_args;
   int                  cgi_result;

// Записать нужные аргументы из строки inStr в структуру cgi_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   cgi_result = BX_Language_Delete (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
   // Выходных аргументов нет.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение информации о языке с указанным ID.
//                                                                            []
void CGI_BX_QQQQQ_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   CGI_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_QQQQQ_Args        cgi_args;
   int                  cgi_result;

// Входных аргументов нет.

// Вызвать проблемную функцию:
   cgi_result = BX_QQQQQ_GetData (cgi_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (cgi_result == CGI_OK)
   {
   // Выходных аргументов нет.
   }
   CGI_WRAPPER_END;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
