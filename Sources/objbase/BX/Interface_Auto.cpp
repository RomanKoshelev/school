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
// Возвращает статистическую информацию для показа счётчика.
//                                                                            []
void OBServer_BX_Counter_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Counter_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (JustGetData);
   GET_ARG (SiteID);
   GET_ARG (Alias);
   GET_ARG (CounterType);
   GET_ARG (PageNo);
   GET_ARG (CookieSupported);
   GET_ARG (ViewerID);
   GET_ARG (LocalTime);
   GET_ARG (ViewerIP);
   GET_ARG (SiteURL);
   GET_ARG (Referrer);
   GET_ARG (ViewerHostName);
   GET_ARG (UserAgent);
   GET_ARG (ScreenResolution);
   GET_ARG (ColorDepth);
   GET_ARG (JavaEnabled);
   GET_ARG (JavaScriptVersion);
   GET_ARG (Charset);
   GET_ARG (Language);

// Вызвать проблемную функцию:
   OBServer_result = BX_Counter_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ViewerID);
      PACK_ARG (ExitCode);
      PACK_ARG (Visits);
      PACK_ARG (LastVisitTime);
      PACK_ARG (OnlineVisitors);
      PACK_ARG (Total_Loads);
      PACK_ARG (Total_Visitors);
      PACK_ARG (Total_VisitorReturns);
      PACK_ARG (Total_AnonymousVisitors);
      PACK_ARG (Total_AnonymousVisitors_Prc);
      PACK_ARG (Total_VisitorExperience);
      PACK_ARG (Ave_VisitorExperience);
      PACK_ARG (Total_Hosts);
      PACK_ARG (Total_Hits);
      PACK_ARG (Total_AnonymousHits);
      PACK_ARG (Total_AnonymousHits_Prc);
      PACK_ARG (Total_SuspiciousHits_Prc);
      PACK_ARG (Total_SessionTime);
      PACK_ARG (Total_Shows);
      PACK_ARG (Total_Clicks);
      PACK_ARG (Total_CTR_Prc);
      PACK_ARG (Total_Votes);
      PACK_ARG (Total_Votes_Sum);
      PACK_ARG (Total_Votes_Ave);
      PACK_ARG (LM_Loads);
      PACK_ARG (LM_Visitors);
      PACK_ARG (LM_VisitorReturns);
      PACK_ARG (LM_VisitorReturns_Prc);
      PACK_ARG (LM_Hosts);
      PACK_ARG (LM_Hits);
      PACK_ARG (LM_AnonymousHits);
      PACK_ARG (LM_AnonymousHits_Prc);
      PACK_ARG (LM_SuspiciousHits_Prc);
      PACK_ARG (LM_SessionTime);
      PACK_ARG (LM_Shows);
      PACK_ARG (LM_Clicks);
      PACK_ARG (LM_CTR_Prc);
      PACK_ARG (LW_Loads);
      PACK_ARG (LW_Visitors);
      PACK_ARG (LW_VisitorReturns);
      PACK_ARG (LW_VisitorReturns_Prc);
      PACK_ARG (LW_Hosts);
      PACK_ARG (LW_Hits);
      PACK_ARG (LW_AnonymousHits);
      PACK_ARG (LW_AnonymousHits_Prc);
      PACK_ARG (LW_SuspiciousHits_Prc);
      PACK_ARG (LW_SessionTime);
      PACK_ARG (LW_Shows);
      PACK_ARG (LW_Clicks);
      PACK_ARG (LW_CTR_Prc);
      PACK_ARG (LD_Loads);
      PACK_ARG (LD_Visitors);
      PACK_ARG (LD_VisitorReturns);
      PACK_ARG (LD_VisitorReturns_Prc);
      PACK_ARG (LD_Hosts);
      PACK_ARG (LD_Hits);
      PACK_ARG (LD_AnonymousHits);
      PACK_ARG (LD_AnonymousHits_Prc);
      PACK_ARG (LD_SuspiciousHits_Prc);
      PACK_ARG (LD_SessionTime);
      PACK_ARG (LD_Shows);
      PACK_ARG (LD_Clicks);
      PACK_ARG (LD_CTR_Prc);
      PACK_ARG (LH_Loads);
      PACK_ARG (LH_Visitors);
      PACK_ARG (LH_VisitorReturns);
      PACK_ARG (LH_VisitorReturns_Prc);
      PACK_ARG (LH_Hosts);
      PACK_ARG (LH_Hits);
      PACK_ARG (LH_AnonymousHits);
      PACK_ARG (LH_AnonymousHits_Prc);
      PACK_ARG (LH_SuspiciousHits_Prc);
      PACK_ARG (LH_SessionTime);
      PACK_ARG (LH_Shows);
      PACK_ARG (LH_Clicks);
      PACK_ARG (LH_CTR_Prc);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение координат для вывода графика счётчика сайта за последние 24 часа.
//                                                                            []
void OBServer_BX_TimeStats_GetStatInfo (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_TimeStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (Site);
   GET_ARG (StatsName);

// Вызвать проблемную функцию:
   OBServer_result = BX_TimeStats_GetStatInfo (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (XLabel);
      PACK_ARG (YValue);
      PACK_ARG (YMax);
      PACK_ARG (YMin);
      PACK_ARG (VisitorsOnline);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить кол-во экземпляров объектов в базе данных.
//                                                                            []
void OBServer_BX_Admin_GetObjectNum (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Admin_Args        OBServer_args;
   int                  OBServer_result;

// Входных аргументов нет.

// Вызвать проблемную функцию:
   OBServer_result = BX_Admin_GetObjectNum (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Result);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Установить фильтрующиеся типы концептов для зрителя.
//                                                                            []
void OBServer_BX_Concept_SetFilter (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (ConceptType);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_SetFilter (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ConceptType);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить фильтрующиеся типы концептов для зрителя.
//                                                                            []
void OBServer_BX_Concept_GetFilter (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Входных аргументов нет.

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_GetFilter (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ConceptType);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает информацию о реферерах.
//                                                                            []
void OBServer_BX_SiteStats_Referrer (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (OwnerPassword);
   GET_ARG (StatsPassword);
   GET_ARG (Mode);
   GET_ARG (SortOrder);
   GET_ARG (StartDate);
   GET_ARG (EndDate);
   GET_ARG (FirstPos);
   GET_ARG (LastPos);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteStats_Referrer (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (CreationTime);
      PACK_ARG (URL);
      PACK_ARG (RawTable);
      PACK_ARG (TotalObjects);
      PACK_ARG (StartDate);
      PACK_ARG (EndDate);
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить синоним сайта по ID.
//                                                                            []
void OBServer_BX_Site_GetAliasByID (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetAliasByID (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Alias);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить ID по синониму сайта.
//                                                                            []
void OBServer_BX_Site_GetIDByAlias (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (Alias);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetIDByAlias (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Сохранение основных объектов BX.
//                                                                            []
void OBServer_BX_Admin_SaveBXObjects (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Admin_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (Password);

// Вызвать проблемную функцию:
   OBServer_result = BX_Admin_SaveBXObjects (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Result);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Краткая информация по сайту.
//                                                                            []
void OBServer_BX_Site_GetBriefInfo (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetBriefInfo (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (URL);
      PACK_ARG (CreationTime);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение данных из полновременного счетчика сайта.
//                                                                            []
void OBServer_BX_TimeStats_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_TimeStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (OwnerPassword);
   GET_ARG (StatsPassword);
   GET_ARG (Object);
   GET_ARG (Counter);
   GET_ARG (Date_Start);
   GET_ARG (Date_End);
   GET_ARG (TZOffset);
   GET_ARG (TimeDescrete);
   GET_ARG (TimeAggregate);
   GET_ARG (WeekdayLong);
   GET_ARG (MonthLong);

// Вызвать проблемную функцию:
   OBServer_result = BX_TimeStats_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Data);
      PACK_ARG (Labels);
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает информацию о последних событиях и зрителях.
//                                                                            []
void OBServer_BX_SiteStats_WhatsNew (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (OwnerPassword);
   GET_ARG (StatsPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteStats_WhatsNew (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (CreationTime);
      PACK_ARG (URL);
      PACK_ARG (RawVector);
      PACK_ARG (RawTable);
      PACK_ARG (TotalObjects);
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить пароль на доступ к статистике сайта.
//                                                                            []
void OBServer_BX_Site_GetStatsPassword (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetStatsPassword (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (RateStatsViewPassword);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Проверка пароля на доступ к статистике сайта.
//                                                                            []
void OBServer_BX_Site_CheckStatsPassword (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (OwnerPassword);
   GET_ARG (StatsPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_CheckStatsPassword (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение ID VBN по ID сайта.
//                                                                            []
void OBServer_BX_Site_GetVBN (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetVBN (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (VBN);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает информацию, касающуюся пересечения аудиторий сайта.
//                                                                            []
void OBServer_BX_SiteStats_AudienceIntersect (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (OwnerPassword);
   GET_ARG (StatsPassword);
   GET_ARG (SortOrder);
   GET_ARG (FirstPos);
   GET_ARG (LastPos);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteStats_AudienceIntersect (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (CreationTime);
      PACK_ARG (URL);
      PACK_ARG (RawTable);
      PACK_ARG (TotalObjects);
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создать новый диапазон адресов.
//                                                                            []
void OBServer_BX_IPRecord_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_IPRecord_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (First);
   GET_ARG (Last);
   GET_ARG (Checked);
   GET_ARG (ConceptID);

// Вызвать проблемную функцию:
   OBServer_result = BX_IPRecord_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить параметры диапазона адресов.
//                                                                            []
void OBServer_BX_IPRecord_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_IPRecord_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_IPRecord_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Count);
      PACK_ARG (Mask);
      PACK_ARG (First);
      PACK_ARG (Last);
      PACK_ARG (Checked);
      PACK_ARG (ConceptID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Установить границы диапазона адресов и соответствующие ему концепты. Отличается от New тем, что не создает нового объекта, а устанавливает (помимо прочего) флаг checked у существующего. Если массив концептов пуст, то существующие у объекта концепты не меняются.
//                                                                            []
void OBServer_BX_IPRecord_Check (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_IPRecord_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);
   GET_ARG (First);
   GET_ARG (Last);
   GET_ARG (ConceptID);

// Вызвать проблемную функцию:
   OBServer_result = BX_IPRecord_Check (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Вывод зарегистрированных в системе IP-диапазонов.
//                                                                            []
void OBServer_BX_IPRecord_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_IPRecord_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (Checked);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_IPRecord_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает номера типов концептов и их названия.
//                                                                            []
void OBServer_BX_Concept_TypeEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Входных аргументов нет.

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_TypeEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objNums);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает ID языка интерфейса пользователя. Пароль не требуется.
//                                                                            []
void OBServer_BX_User_GetLanguage (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_GetLanguage (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (InterfaceLanguage);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить пересечение аудиторий для данного сайта.
//                                                                            []
void OBServer_BX_Site_GetAudienceIntersect (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetAudienceIntersect (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Audience_SiteID);
      PACK_ARG (Audience_SiteName);
      PACK_ARG (Audience_Viewers);
      PACK_ARG (Audience_Hosts);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить распределение концептов для аудитории интернета.
//                                                                            []
void OBServer_BX_ConceptRate_Reg_InetAudience (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_ConceptRate_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (TypeNums);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_ConceptRate_Reg_InetAudience (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (CRN_Name);
      PACK_ARG (CRN_Value);
      PACK_ARG (CRN_Level);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить распределение концептов посетителей сайта.
//                                                                            []
void OBServer_BX_ConceptRate_Site_Visitor (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_ConceptRate_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (TypeNums);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_ConceptRate_Site_Visitor (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (CRN_Name);
      PACK_ARG (CRN_Value);
      PACK_ARG (CRN_Level);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить распределение концептов зрителя.
//                                                                            []
void OBServer_BX_ConceptRate_Viewer_Site (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_ConceptRate_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (TypeNums);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_ConceptRate_Viewer_Site (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (CRN_Name);
      PACK_ARG (CRN_Value);
      PACK_ARG (CRN_Level);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить распределение анкетных концептов зрителя.
//                                                                            []
void OBServer_BX_ConceptRate_Viewer_Inquiry (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_ConceptRate_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (TypeNums);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_ConceptRate_Viewer_Inquiry (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (CRN_Name);
      PACK_ARG (CRN_Value);
      PACK_ARG (CRN_Level);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение отчета диспетчера памяти. Требуется пароль администратора.
//                                                                            []
void OBServer_BX_Admin_MemoryManagerReport (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Admin_Args        OBServer_args;
   int                  OBServer_result;

// Входных аргументов нет.

// Вызвать проблемную функцию:
   OBServer_result = BX_Admin_MemoryManagerReport (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (MemoryManagerReport);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечислить зрителей.
//                                                                            []
void OBServer_BX_Viewer_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Viewer_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Viewer_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить информацию по зрителю.
//                                                                            []
void OBServer_BX_Viewer_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Viewer_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (IPAddress);

// Вызвать проблемную функцию:
   OBServer_result = BX_Viewer_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Anonymous);
      PACK_ARG (TotalShows);
      PACK_ARG (TotalClicks);
      PACK_ARG (IPAddress);
      PACK_ARG (Referrer);
      PACK_ARG (CreationTime);
      PACK_ARG (sCreationTime);
      PACK_ARG (LastVisitTime);
      PACK_ARG (sLastVisitTime);
      PACK_ARG (TZOffset);
      PACK_ARG (Site);
      PACK_ARG (sSite);
      PACK_ARG (sSite_LastVisited);
      PACK_ARG (Site_Visits);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить рейтинговую информацию по сайтам.
//                                                                            []
void OBServer_BX_RateStats_Site (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_RateStats_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (VBN);
   GET_ARG (Concept);
   GET_ARG (FirstPos);
   GET_ARG (LastPos);
   GET_ARG (Ascending);
   GET_ARG (WithDescription);
   GET_ARG (CreatedAfter);
   GET_ARG (CreatedBefore);
   GET_ARG (Indices);
   GET_ARG (KeyIndex);

// Вызвать проблемную функцию:
   OBServer_result = BX_RateStats_Site (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (RawTable);
      PACK_ARG (ObjectsNum);
      PACK_ARG (Total);
      PACK_ARG (SubTotal);
      PACK_ARG (VBNTotalObjects);
      PACK_ARG (ReqTotal);
      PACK_ARG (VBNTotalObjectsAct);
      PACK_ARG (ReqTotalObjects);
      PACK_ARG (ReqTotalObjectsAct);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Авторизация пользователей, администраторов системы и VBN.
//                                                                            []
void OBServer_BX_Security_Authorize (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Security_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (VBN);
   GET_ARG (Level);
   GET_ARG (Login);
   GET_ARG (Password);

// Вызвать проблемную функцию:
   OBServer_result = BX_Security_Authorize (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Result);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечисления всех пользователей независимо от VBN.
//                                                                            []
void OBServer_BX_User_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечисления всех профилей сайта независимо от VBN.
//                                                                            []
void OBServer_BX_SiteProfile_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечисления всех сайтов независимо от VBN.
//                                                                            []
void OBServer_BX_Site_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечисления всех профилей баннеров независимо от VBN.
//                                                                            []
void OBServer_BX_BannerProfile_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Перечисления всех баннеров независимо от VBN.
//                                                                            []
void OBServer_BX_Banner_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Banner_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Banner_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание нового языка. В случае создания в objID возвращается идентификатор созданного объекта.
//                                                                            []
void OBServer_BX_Language_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (ShortName);
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// Вызвать проблемную функцию:
   OBServer_result = BX_Language_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение параметров существующего языка с идентификатором objID.
//                                                                            []
void OBServer_BX_Language_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);
   GET_ARG (ShortName);
   GET_ARG (OwnName);
   GET_ARG (Name);
   GET_ARG (Language);

// Вызвать проблемную функцию:
   OBServer_result = BX_Language_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение названий всех языков, зарегистрированных в системе. Названия возвращаются в поле objNames[] входной структуры. Соответствующие идентификаторы возвращаются в поле objIDs[] входной структуры.
//                                                                            []
void OBServer_BX_Language_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Language_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение информации о языке с указанным ID.
//                                                                            []
void OBServer_BX_Language_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Language_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ShortName);
      PACK_ARG (OwnName);
      PACK_ARG (Name);
      PACK_ARG (Language);
      PACK_ARG (No);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление языка.
//                                                                            []
void OBServer_BX_Language_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Language_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Language_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание концепта. В случае создания идентификатор созданного концепта возвращается в objID.
//                                                                            []
void OBServer_BX_Concept_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (Parent);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (ShortName);
   GET_ARG (Type);
   GET_ARG (TypeNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Модификация параметров существующего концепта с идентификатором objID.
//                                                                            []
void OBServer_BX_Concept_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (ShortName);
   GET_ARG (Type);
   GET_ARG (TypeNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение идентификаторов всех концептов на языке # objLanguageNo методом 'в ширину', т.е. в порядке возрастания уровня.
//                                                                            []
void OBServer_BX_Concept_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить список идентификаторов и названий концептов заданного уровня на заданном языке с возможными отступами в соответствии с уровнем. Концепты выводятся 'в глубину', т.е. в порядке следования родителей. Если указан Level, то выводятся концепты с уровнем до Level включительно, иначе - все концепты.
//                                                                            []
void OBServer_BX_Concept_ExtendedEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (SiteCount);
   GET_ARG (Indent);
   GET_ARG (VBN);
   GET_ARG (Level);
   GET_ARG (ConceptType);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_ExtendedEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение информации о концепте с указанным идентификатором objID.
//                                                                            []
void OBServer_BX_Concept_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Parent);
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (ShortName);
      PACK_ARG (Type);
      PACK_ARG (TypeNo);
      PACK_ARG (Level);
      PACK_ARG (No);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление концепта с указанным идентификатором objID. Все потомки концепта также удаляются.
//                                                                            []
void OBServer_BX_Concept_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Concept_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Concept_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание виртуальной баннерной сети. На входе нужен пароль владельца сети Password, который будет требоваться  для доступа ко всем функциям с данной VBN, а также пароль администратора AdminPassword. В случае создания в objID возвращается идентификатор созданного объекта.
//                                                                            []
void OBServer_BX_VBN_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (IsModerated);
   GET_ARG (DefaultLanguage);
   GET_ARG (DefaultTZOffset);
   GET_ARG (ConceptMask);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение параметров виртуальной баннерной сети с идентификатором objID. На входе нужен пароль владельца сети Password.
//                                                                            []
void OBServer_BX_VBN_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (IsModerated);
   GET_ARG (DefaultLanguage);
   GET_ARG (DefaultTZOffset);
   GET_ARG (ConceptMask);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение идентификаторов (в objIDs) и названий (objNames) всех виртуальных банерных сетей, зарегистрированных в системе.
//                                                                            []
void OBServer_BX_VBN_Enumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_Enumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение параметров виртуальной баннерной сети с указанным objID. Пароль владельца сети передавать не нужно.
//                                                                            []
void OBServer_BX_VBN_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (IsModerated);
      PACK_ARG (DefaultLanguage);
      PACK_ARG (DefaultTZOffset);
      PACK_ARG (ConceptMask);
      PACK_ARG (No);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение идентификаторов (в objIDs) и названий (objNames) всех концептов виртуальной банерной сети с идентификатором objID.
//                                                                            []
void OBServer_BX_VBN_ConceptEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objLanguageNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ConceptEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение идентификатора владельца сети. На входе нужен пароль владельца сети Password.
//                                                                            []
void OBServer_BX_VBN_GetOwnerID (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_GetOwnerID (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Owner);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление виртуальной баннерной сети с указанным идентификатором objID. Необходимо передать правильный пароль администратора AdminPassword.
//                                                                            []
void OBServer_BX_VBN_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (AdminPassword);
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена разрешённых пользователей из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UserEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UserEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена разрешённых сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_SiteEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_SiteEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена разрешённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_SiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_SiteProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена разрешённых баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_BannerEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_BannerEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена разрешённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_BannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_BannerProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена неразрешённых пользователей из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UnallowedUserEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UnallowedUserEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена  неразрешённых сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UnallowedSiteEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UnallowedSiteEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена  неразрешённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UnallowedSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UnallowedSiteProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена неразрешённых баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UnallowedBannerEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UnallowedBannerEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена неразрешённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_UnallowedBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_UnallowedBannerProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена новых пользователей из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_NewUserEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_NewUserEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена новых сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_NewSiteEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_NewSiteEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена новых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_NewSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_NewSiteProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена новых баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_NewBannerEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_NewBannerEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена новых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_NewBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_NewBannerProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена изменённых пользователей из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_ChangedUserEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ChangedUserEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена изменённых сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_ChangedSiteEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ChangedSiteEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена изменённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_ChangedSiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ChangedSiteProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена изменённых баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_ChangedBannerEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ChangedBannerEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает в objIDs и objNames идентификаторы и имена изменённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.
//                                                                            []
void OBServer_BX_VBN_ChangedBannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_VBN_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_VBN_ChangedBannerProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Возвращает флаг перезагрузки пароля.
//                                                                            []
void OBServer_BX_User_GetForgetPassword (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (VBN);
   GET_ARG (Login);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_GetForgetPassword (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (ForgetPassword);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Устанавливает флаг перезагрузки пароля.
//                                                                            []
void OBServer_BX_User_SetForgetPassword (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (VBN);
   GET_ARG (Login);
   GET_ARG (ForgetPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_SetForgetPassword (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание пользователя. Также создаются профили баннера и сайта по умолчанию.
//                                                                            []
void OBServer_BX_User_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (PasswordConfirm);
   GET_ARG (FullName);
   GET_ARG (Email);
   GET_ARG (VBN);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (ExitCode);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение установок пользователя. Если не указан objID, то пользователь ищется по полям Login, Password и VBN, а идентификатор найденного пользователя возвращается в objID. В этом случае возможен возврат ошибок BXE_User_GetData_LoginNotFound или BXE_User_GetData_PasswordIncorrect. Пароль пользователя Password необходимо указать в любом случае.
//                                                                            []
void OBServer_BX_User_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Login);
   GET_ARG (Password);
   GET_ARG (VBN);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (Login);
      PACK_ARG (FullName);
      PACK_ARG (InterfaceLanguage);
      PACK_ARG (InterfaceType);
      PACK_ARG (CreationTime);
      PACK_ARG (sCreationTime);
      PACK_ARG (VBN);
      PACK_ARG (Email);
      PACK_ARG (Phone);
      PACK_ARG (Fax);
      PACK_ARG (Address);
      PACK_ARG (URL);
      PACK_ARG (Comment);
      PACK_ARG (TZOffset);
      PACK_ARG (NotifyFreq);
      PACK_ARG (NotifyHTML);
      PACK_ARG (NotifyDepth);
      PACK_ARG (ShowsLeft);
      PACK_ARG (ClicksLeft);
      PACK_ARG (TradeStats);
      PACK_ARG (Allowed);
      PACK_ARG (ObjectState);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение адреса эл. почты пользователя по его логину и VBN.
//                                                                            []
void OBServer_BX_User_GetEmail (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (VBN);
   GET_ARG (Login);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_GetEmail (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Email);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение установок пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (FullName);
   GET_ARG (InterfaceLanguage);
   GET_ARG (InterfaceType);
   GET_ARG (Email);
   GET_ARG (Phone);
   GET_ARG (Fax);
   GET_ARG (Address);
   GET_ARG (URL);
   GET_ARG (Comment);
   GET_ARG (TZOffset);
   GET_ARG (NotifyFreq);
   GET_ARG (NotifyHTML);
   GET_ARG (NotifyDepth);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление пользователя с идентификатором objID. Удаляются все сайты, профили и баннеры пользователя. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение списка идентификаторов (в objIDs) и названий (в objNames) сайтов пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_SiteEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_SiteEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение списка идентификаторов (в objIDs) и названий (в objNames) баннеров пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_BannerEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_BannerEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей сайтов пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_SiteProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_SiteProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей баннеров пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.
//                                                                            []
void OBServer_BX_User_BannerProfileEnumerate (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);
   GET_ARG (objFirstNo);
   GET_ARG (objLastNo);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_BannerProfileEnumerate (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objIDs);
      PACK_ARG (objNames);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Регистрация пользователя как системного (баннеры которого показываются в исключительных ситуациях). Необходимо указать Password для доступа к VBN пользователя.
//                                                                            []
void OBServer_BX_User_RegisterAsSystem (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_User_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (Password);

// Вызвать проблемную функцию:
   OBServer_result = BX_User_RegisterAsSystem (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создаёт профиль сайта для пользователя с идентификатором OwnerID. Если указан objFromID , то в созданный профиль копируются параметры из профиля с идентификатором objFromID. В objID возвращается id созданного профиля. В Name возвращается название созданного профиля. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_SiteProfile_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (OwnerID);
   GET_ARG (objPassword);
   GET_ARG (Name);
   GET_ARG (objFromID);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (Name);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Копирование установок профиля сайта из профиля objFromID в профиль objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_SiteProfile_CopyData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (objFromID);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_CopyData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение установок профиля сайта с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_SiteProfile_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (Site);
      PACK_ARG (sSite);
      PACK_ARG (VBN);
      PACK_ARG (LastModified);
      PACK_ARG (sLastModified);
      PACK_ARG (OwnerID);
      PACK_ARG (BannerInclude);
      PACK_ARG (BannerExclude);
      PACK_ARG (SiteInclude);
      PACK_ARG (SiteExclude);
      PACK_ARG (MaxFileSize);
      PACK_ARG (UseKeywords);
      PACK_ARG (BannerConceptInclude);
      PACK_ARG (BannerConceptExclude);
      PACK_ARG (Allowed);
      PACK_ARG (ObjectState);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение установок профиля сайта с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_SiteProfile_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (Name);
   GET_ARG (BannerInclude);
   GET_ARG (BannerExclude);
   GET_ARG (SiteInclude);
   GET_ARG (SiteExclude);
   GET_ARG (MaxFileSize);
   GET_ARG (UseKeywords);
   GET_ARG (BannerConceptInclude);
   GET_ARG (BannerConceptExclude);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление установок профиля сайта с указанным ID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_SiteProfile_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteProfile_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание сайта. Требуется идентификатор владельца OwnerID и URL сайта. Идентификатор созданного сайта возвращается в поле objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Site_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (OwnerID);
   GET_ARG (Profile);
   GET_ARG (Name);
   GET_ARG (objPassword);
   GET_ARG (URL);
   GET_ARG (objFromID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение параметров сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Site_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (OwnerID);
      PACK_ARG (VBN);
      PACK_ARG (CreationTime);
      PACK_ARG (sCreationTime);
      PACK_ARG (MirrorInclude);
      PACK_ARG (MirrorExclude);
      PACK_ARG (MirrorSubstr);
      PACK_ARG (IgnoredIP);
      PACK_ARG (IgnoredViewerID);
      PACK_ARG (Alias);
      PACK_ARG (Name);
      PACK_ARG (Description);
      PACK_ARG (URL);
      PACK_ARG (CounterType);
      PACK_ARG (RateMySite);
      PACK_ARG (RateStatsViewPassword);
      PACK_ARG (ShowAudience);
      PACK_ARG (ShowAudienceOffTime);
      PACK_ARG (Profile);
      PACK_ARG (Keyword);
      PACK_ARG (Concept);
      PACK_ARG (PageName);
      PACK_ARG (PageNo);
      PACK_ARG (AdBannerProfile);
      PACK_ARG (SuspiciousInfo);
      PACK_ARG (Allowed);
      PACK_ARG (ObjectState);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение параметров сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Site_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (MirrorInclude);
   GET_ARG (MirrorExclude);
   GET_ARG (MirrorSubstr);
   GET_ARG (IgnoredIP);
   GET_ARG (IgnoredViewerID);
   GET_ARG (Alias);
   GET_ARG (Name);
   GET_ARG (Description);
   GET_ARG (URL);
   GET_ARG (CounterType);
   GET_ARG (RateMySite);
   GET_ARG (RateStatsViewPassword);
   GET_ARG (ShowAudience);
   GET_ARG (Profile);
   GET_ARG (Keyword);
   GET_ARG (Concept);
   GET_ARG (PageName);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Site_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить тип счетчика для сайта.
//                                                                            []
void OBServer_BX_Site_GetCounterType (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Site_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);

// Вызвать проблемную функцию:
   OBServer_result = BX_Site_GetCounterType (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (CounterType);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получить информацию о подозрительных событиях, произошедших на сайте.
//                                                                            []
void OBServer_BX_SiteSuspiciousInfo_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_SiteSuspiciousInfo_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_SiteSuspiciousInfo_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (sEventType);
      PACK_ARG (sTime);
      PACK_ARG (Viewer);
      PACK_ARG (IP);
      PACK_ARG (Referrer);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создаёт профиль баннера для пользователя OwnerID. Если указан objFromID , то в созданный профиль копируются параметры из профиля objFromID. В objID возвращается id созданного профиля. В Name  возвращается название созданного профиля. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_BannerProfile_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (OwnerID);
   GET_ARG (objPassword);
   GET_ARG (Name);
   GET_ARG (HREF);
   GET_ARG (objFromID);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
      PACK_ARG (Name);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Копирование установок профиля баннера из профиля objFromID в профиль objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_BannerProfile_CopyData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (objFromID);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_CopyData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_BannerProfile_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (Name);
      PACK_ARG (VBN);
      PACK_ARG (LastModified);
      PACK_ARG (sLastModified);
      PACK_ARG (OwnerID);
      PACK_ARG (HREF);
      PACK_ARG (Commercial);
      PACK_ARG (Banner);
      PACK_ARG (sBanner);
      PACK_ARG (Concept);
      PACK_ARG (State);
      PACK_ARG (AltText);
      PACK_ARG (SiteConceptInclude);
      PACK_ARG (SiteConceptExclude);
      PACK_ARG (SiteInclude);
      PACK_ARG (sSiteInclude);
      PACK_ARG (SiteExclude);
      PACK_ARG (sSiteExclude);
      PACK_ARG (ViewerIPEnable);
      PACK_ARG (ViewerIPDisable);
      PACK_ARG (ViewerConceptInclude);
      PACK_ARG (ViewerConceptExclude);
      PACK_ARG (UseLocalTime);
      PACK_ARG (ScheduleTZOffset);
      PACK_ARG (ShowIfLocalUnknown);
      PACK_ARG (Schedule);
      PACK_ARG (AutoOn);
      PACK_ARG (AutoOff);
      PACK_ARG (RepeatCount);
      PACK_ARG (RepeatTime);
      PACK_ARG (CountTypeByShows);
      PACK_ARG (MaxDailyClicks);
      PACK_ARG (MaxDailyShows);
      PACK_ARG (TotalShows);
      PACK_ARG (TotalClicks);
      PACK_ARG (Allowed);
      PACK_ARG (ObjectState);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_BannerProfile_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (Name);
   GET_ARG (HREF);
   GET_ARG (Commercial);
   GET_ARG (Banner);
   GET_ARG (sBanner);
   GET_ARG (Concept);
   GET_ARG (State);
   GET_ARG (AltText);
   GET_ARG (SiteConceptInclude);
   GET_ARG (SiteConceptExclude);
   GET_ARG (SiteInclude);
   GET_ARG (sSiteInclude);
   GET_ARG (SiteExclude);
   GET_ARG (sSiteExclude);
   GET_ARG (ViewerIPEnable);
   GET_ARG (ViewerIPDisable);
   GET_ARG (ViewerConceptInclude);
   GET_ARG (ViewerConceptExclude);
   GET_ARG (UseLocalTime);
   GET_ARG (ScheduleTZOffset);
   GET_ARG (ShowIfLocalUnknown);
   GET_ARG (Schedule);
   GET_ARG (AutoOn);
   GET_ARG (AutoOff);
   GET_ARG (RepeatCount);
   GET_ARG (RepeatTime);
   GET_ARG (CountTypeByShows);
   GET_ARG (MaxDailyClicks);
   GET_ARG (MaxDailyShows);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_BannerProfile_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_BannerProfile_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_BannerProfile_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Создание баннера. Требуется OwnerID владельца, FileName баннера. Идентификатор созданного баннера возвращается в objID.  Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Banner_New (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Banner_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (OwnerID);
   GET_ARG (objPassword);
   GET_ARG (FileName);
   GET_ARG (FileSize);
   GET_ARG (Concept);
   GET_ARG (Profile);

// Вызвать проблемную функцию:
   OBServer_result = BX_Banner_New (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (objID);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Получение параметров баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Banner_GetData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Banner_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_Banner_GetData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
      PACK_ARG (OwnerID);
      PACK_ARG (FileName);
      PACK_ARG (FileSize);
      PACK_ARG (UploadNo);
      PACK_ARG (CreationTime);
      PACK_ARG (sCreationTime);
      PACK_ARG (VBN);
      PACK_ARG (State);
      PACK_ARG (Profile);
      PACK_ARG (Concept);
      PACK_ARG (TotalShows);
      PACK_ARG (TotalClicks);
      PACK_ARG (Allowed);
      PACK_ARG (ObjectState);
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Изменение параметров баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Banner_PutData (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Banner_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);
   GET_ARG (FileName);
   GET_ARG (FileSize);
   GET_ARG (UploadNo);
   GET_ARG (State);
   GET_ARG (Profile);
   GET_ARG (Concept);

// Вызвать проблемную функцию:
   OBServer_result = BX_Banner_PutData (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
// Удаление баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.
//                                                                            []
void OBServer_BX_Banner_Delete (const char * inStr, const char * outStr, void ** ppData)
{
   OBServer_WRAPPER_START;
   AVOID_WARNING_ON_ARGS;

// Переменные, необходимые для вызова проблемной функции:
   BX_Banner_Args        OBServer_args;
   int                  OBServer_result;

// Записать нужные аргументы из строки inStr в структуру OBServer_args:
   GET_ARG (objID);
   GET_ARG (objPassword);

// Вызвать проблемную функцию:
   OBServer_result = BX_Banner_Delete (OBServer_args);

// Если функция отработала успешно, то упакуем требуемые выходные аргументы:
   if (OBServer_result == OBServer_OK)
   {
   // Выходных аргументов нет.
   }
   OBServer_WRAPPER_END;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
