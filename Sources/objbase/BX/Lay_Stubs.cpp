/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_Stubs.cpp                                             []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Мощные затычки для тупых компиляторов                     []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/
#ifndef Lay_Stubs_H
#define Lay_Stubs_H

#define USES_OC_ALL
#include "./../bcc/main.h"
#include "./../bcc/OBD.h"
#include "Lay_ObjData.h"




//------------------------------------------------------------------------------[]
//
// Конструктор
//
void * new_OD (identifier classID, bool bInit)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return new OD_Viewer (bInit);
      case OBJ_CLASS_ID_ViewerGroup: return new OD_ViewerGroup (bInit);
      case OBJ_CLASS_ID_User: return new OD_User (bInit);
      case OBJ_CLASS_ID_TradeStats: return new OD_TradeStats (bInit);
      case OBJ_CLASS_ID_Banner: return new OD_Banner (bInit);
      case OBJ_CLASS_ID_BannerProfile: return new OD_BannerProfile (bInit);
      case OBJ_CLASS_ID_Page: return new OD_Page (bInit);
      case OBJ_CLASS_ID_Site: return new OD_Site (bInit);
      case OBJ_CLASS_ID_SiteProfile: return new OD_SiteProfile (bInit);
      case OBJ_CLASS_ID_ShowEvent: return new OD_ShowEvent (bInit);
      case OBJ_CLASS_ID_Registry: return new OD_Registry (bInit);
      case OBJ_CLASS_ID_VBN: return new OD_VBN (bInit);
      case OBJ_CLASS_ID_Language: return new OD_Language (bInit);
      case OBJ_CLASS_ID_Concept: return new OD_Concept (bInit);
      case OBJ_CLASS_ID_SiteList: return new OD_SiteList (bInit);
      case OBJ_CLASS_ID_Keyword: return new OD_Keyword (bInit);
      case OBJ_CLASS_ID_ModeratorComment: return new OD_ModeratorComment (bInit);
      case OBJ_CLASS_ID_TimeStats: return new OD_TimeStats (bInit);
      case OBJ_CLASS_ID_YearStats: return new OD_YearStats (bInit);
      case OBJ_CLASS_ID_DayStats: return new OD_DayStats (bInit);
      case OBJ_CLASS_ID_Referrer: return new OD_Referrer (bInit);
      case OBJ_CLASS_ID_DailyReferrerStats: return new OD_DailyReferrerStats (bInit);
      case OBJ_CLASS_ID_SearchWordsInfo: return new OD_SearchWordsInfo (bInit);
      case OBJ_CLASS_ID_SuspiciousInfo: return new OD_SuspiciousInfo (bInit);
      case OBJ_CLASS_ID_RatingPlaceInfo: return new OD_RatingPlaceInfo (bInit);
      case OBJ_CLASS_ID_IPRecord: return new OD_IPRecord (bInit);
      case OBJ_CLASS_ID_ViewerReference: return new OD_ViewerReference (bInit);
      case OBJ_CLASS_ID_AbstractObject: return new OD_AbstractObject (bInit);
      case -1: (void)classID; (void)bInit;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Деструктор
//
void delete_pData (identifier classID, void * pData)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: delete ((OD_Viewer*)pData); return;
      case OBJ_CLASS_ID_ViewerGroup: delete ((OD_ViewerGroup*)pData); return;
      case OBJ_CLASS_ID_User: delete ((OD_User*)pData); return;
      case OBJ_CLASS_ID_TradeStats: delete ((OD_TradeStats*)pData); return;
      case OBJ_CLASS_ID_Banner: delete ((OD_Banner*)pData); return;
      case OBJ_CLASS_ID_BannerProfile: delete ((OD_BannerProfile*)pData); return;
      case OBJ_CLASS_ID_Page: delete ((OD_Page*)pData); return;
      case OBJ_CLASS_ID_Site: delete ((OD_Site*)pData); return;
      case OBJ_CLASS_ID_SiteProfile: delete ((OD_SiteProfile*)pData); return;
      case OBJ_CLASS_ID_ShowEvent: delete ((OD_ShowEvent*)pData); return;
      case OBJ_CLASS_ID_Registry: delete ((OD_Registry*)pData); return;
      case OBJ_CLASS_ID_VBN: delete ((OD_VBN*)pData); return;
      case OBJ_CLASS_ID_Language: delete ((OD_Language*)pData); return;
      case OBJ_CLASS_ID_Concept: delete ((OD_Concept*)pData); return;
      case OBJ_CLASS_ID_SiteList: delete ((OD_SiteList*)pData); return;
      case OBJ_CLASS_ID_Keyword: delete ((OD_Keyword*)pData); return;
      case OBJ_CLASS_ID_ModeratorComment: delete ((OD_ModeratorComment*)pData); return;
      case OBJ_CLASS_ID_TimeStats: delete ((OD_TimeStats*)pData); return;
      case OBJ_CLASS_ID_YearStats: delete ((OD_YearStats*)pData); return;
      case OBJ_CLASS_ID_DayStats: delete ((OD_DayStats*)pData); return;
      case OBJ_CLASS_ID_Referrer: delete ((OD_Referrer*)pData); return;
      case OBJ_CLASS_ID_DailyReferrerStats: delete ((OD_DailyReferrerStats*)pData); return;
      case OBJ_CLASS_ID_SearchWordsInfo: delete ((OD_SearchWordsInfo*)pData); return;
      case OBJ_CLASS_ID_SuspiciousInfo: delete ((OD_SuspiciousInfo*)pData); return;
      case OBJ_CLASS_ID_RatingPlaceInfo: delete ((OD_RatingPlaceInfo*)pData); return;
      case OBJ_CLASS_ID_IPRecord: delete ((OD_IPRecord*)pData); return;
      case OBJ_CLASS_ID_ViewerReference: delete ((OD_ViewerReference*)pData); return;
      case OBJ_CLASS_ID_AbstractObject: delete ((OD_AbstractObject*)pData); return;
      case -1: (void)classID; (void)pData;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Печать
//
bool pData_DebugPrint (identifier classID, void * pData, string& dbg, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_ViewerGroup: return ((OD_ViewerGroup*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_TradeStats: return ((OD_TradeStats*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Banner: return ((OD_Banner*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_BannerProfile: return ((OD_BannerProfile*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Page: return ((OD_Page*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Site: return ((OD_Site*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_SiteProfile: return ((OD_SiteProfile*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_ShowEvent: return ((OD_ShowEvent*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_VBN: return ((OD_VBN*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Language: return ((OD_Language*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_SiteList: return ((OD_SiteList*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Keyword: return ((OD_Keyword*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_ModeratorComment: return ((OD_ModeratorComment*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_TimeStats: return ((OD_TimeStats*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_YearStats: return ((OD_YearStats*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_DayStats: return ((OD_DayStats*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_Referrer: return ((OD_Referrer*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_DailyReferrerStats: return ((OD_DailyReferrerStats*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_SearchWordsInfo: return ((OD_SearchWordsInfo*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_SuspiciousInfo: return ((OD_SuspiciousInfo*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_RatingPlaceInfo: return ((OD_RatingPlaceInfo*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_IPRecord: return ((OD_IPRecord*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_ViewerReference: return ((OD_ViewerReference*)pData)->DebugPrint(dbg, objID);
      case OBJ_CLASS_ID_AbstractObject: return ((OD_AbstractObject*)pData)->DebugPrint(dbg, objID);
      case -1: (void)classID; (void)pData; (void)objID; (void)dbg;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return false;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Сохранение
//
bool pData_WriteToFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_ViewerGroup: return ((OD_ViewerGroup*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_TradeStats: return ((OD_TradeStats*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Banner: return ((OD_Banner*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_BannerProfile: return ((OD_BannerProfile*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Page: return ((OD_Page*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Site: return ((OD_Site*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_SiteProfile: return ((OD_SiteProfile*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_ShowEvent: return ((OD_ShowEvent*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_VBN: return ((OD_VBN*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Language: return ((OD_Language*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_SiteList: return ((OD_SiteList*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Keyword: return ((OD_Keyword*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_ModeratorComment: return ((OD_ModeratorComment*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_TimeStats: return ((OD_TimeStats*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_YearStats: return ((OD_YearStats*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_DayStats: return ((OD_DayStats*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_Referrer: return ((OD_Referrer*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_DailyReferrerStats: return ((OD_DailyReferrerStats*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_SearchWordsInfo: return ((OD_SearchWordsInfo*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_SuspiciousInfo: return ((OD_SuspiciousInfo*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_RatingPlaceInfo: return ((OD_RatingPlaceInfo*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_IPRecord: return ((OD_IPRecord*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_ViewerReference: return ((OD_ViewerReference*)pData)->WriteToFile (objID);
      case OBJ_CLASS_ID_AbstractObject: return ((OD_AbstractObject*)pData)->WriteToFile (objID);
      case -1: (void)classID; (void)pData; (void)objID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return false;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Загрузка
//
size_t pData_LoadFromFile (identifier classID, void * pData, identifier objID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_ViewerGroup: return ((OD_ViewerGroup*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_TradeStats: return ((OD_TradeStats*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Banner: return ((OD_Banner*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_BannerProfile: return ((OD_BannerProfile*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Page: return ((OD_Page*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Site: return ((OD_Site*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_SiteProfile: return ((OD_SiteProfile*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_ShowEvent: return ((OD_ShowEvent*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_VBN: return ((OD_VBN*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Language: return ((OD_Language*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_SiteList: return ((OD_SiteList*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Keyword: return ((OD_Keyword*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_ModeratorComment: return ((OD_ModeratorComment*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_TimeStats: return ((OD_TimeStats*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_YearStats: return ((OD_YearStats*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_DayStats: return ((OD_DayStats*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_Referrer: return ((OD_Referrer*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_DailyReferrerStats: return ((OD_DailyReferrerStats*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_SearchWordsInfo: return ((OD_SearchWordsInfo*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_SuspiciousInfo: return ((OD_SuspiciousInfo*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_RatingPlaceInfo: return ((OD_RatingPlaceInfo*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_IPRecord: return ((OD_IPRecord*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_ViewerReference: return ((OD_ViewerReference*)pData)->LoadFromFile (objID);
      case OBJ_CLASS_ID_AbstractObject: return ((OD_AbstractObject*)pData)->LoadFromFile (objID);
      case -1: (void)classID; (void)pData; (void)objID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return 0;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Установка указателя в индексе
//
void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: ((OD_Viewer*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_ViewerGroup: ((OD_ViewerGroup*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_User: ((OD_User*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_TradeStats: ((OD_TradeStats*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Banner: ((OD_Banner*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_BannerProfile: ((OD_BannerProfile*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Page: ((OD_Page*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Site: ((OD_Site*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_SiteProfile: ((OD_SiteProfile*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_ShowEvent: ((OD_ShowEvent*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Registry: ((OD_Registry*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_VBN: ((OD_VBN*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Language: ((OD_Language*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Concept: ((OD_Concept*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_SiteList: ((OD_SiteList*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Keyword: ((OD_Keyword*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_ModeratorComment: ((OD_ModeratorComment*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_TimeStats: ((OD_TimeStats*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_YearStats: ((OD_YearStats*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_DayStats: ((OD_DayStats*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_Referrer: ((OD_Referrer*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_DailyReferrerStats: ((OD_DailyReferrerStats*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_SearchWordsInfo: ((OD_SearchWordsInfo*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_SuspiciousInfo: ((OD_SuspiciousInfo*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_RatingPlaceInfo: ((OD_RatingPlaceInfo*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_IPRecord: ((OD_IPRecord*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_ViewerReference: ((OD_ViewerReference*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case OBJ_CLASS_ID_AbstractObject: ((OD_AbstractObject*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;
      case -1: (void)classID; (void)pData; (void)indexID; (void)coIndexPtr;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Получение указателя в индексе
//
OBD_pointer pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_ViewerGroup: return ((OD_ViewerGroup*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_TradeStats: return ((OD_TradeStats*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Banner: return ((OD_Banner*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_BannerProfile: return ((OD_BannerProfile*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Page: return ((OD_Page*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Site: return ((OD_Site*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_SiteProfile: return ((OD_SiteProfile*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_ShowEvent: return ((OD_ShowEvent*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_VBN: return ((OD_VBN*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Language: return ((OD_Language*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_SiteList: return ((OD_SiteList*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Keyword: return ((OD_Keyword*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_ModeratorComment: return ((OD_ModeratorComment*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_TimeStats: return ((OD_TimeStats*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_YearStats: return ((OD_YearStats*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_DayStats: return ((OD_DayStats*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_Referrer: return ((OD_Referrer*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_DailyReferrerStats: return ((OD_DailyReferrerStats*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_SearchWordsInfo: return ((OD_SearchWordsInfo*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_SuspiciousInfo: return ((OD_SuspiciousInfo*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_RatingPlaceInfo: return ((OD_RatingPlaceInfo*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_IPRecord: return ((OD_IPRecord*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_ViewerReference: return ((OD_ViewerReference*)pData)->m_CoIndexPtr[indexID];
      case OBJ_CLASS_ID_AbstractObject: return ((OD_AbstractObject*)pData)->m_CoIndexPtr[indexID];
      case -1: (void)classID; (void)pData; (void)indexID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NULL;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Идентификатор класса
//
identifier pData_classID (identifier classID, void * pData)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: return ((OD_Viewer*)pData)->classID;
      case OBJ_CLASS_ID_ViewerGroup: return ((OD_ViewerGroup*)pData)->classID;
      case OBJ_CLASS_ID_User: return ((OD_User*)pData)->classID;
      case OBJ_CLASS_ID_TradeStats: return ((OD_TradeStats*)pData)->classID;
      case OBJ_CLASS_ID_Banner: return ((OD_Banner*)pData)->classID;
      case OBJ_CLASS_ID_BannerProfile: return ((OD_BannerProfile*)pData)->classID;
      case OBJ_CLASS_ID_Page: return ((OD_Page*)pData)->classID;
      case OBJ_CLASS_ID_Site: return ((OD_Site*)pData)->classID;
      case OBJ_CLASS_ID_SiteProfile: return ((OD_SiteProfile*)pData)->classID;
      case OBJ_CLASS_ID_ShowEvent: return ((OD_ShowEvent*)pData)->classID;
      case OBJ_CLASS_ID_Registry: return ((OD_Registry*)pData)->classID;
      case OBJ_CLASS_ID_VBN: return ((OD_VBN*)pData)->classID;
      case OBJ_CLASS_ID_Language: return ((OD_Language*)pData)->classID;
      case OBJ_CLASS_ID_Concept: return ((OD_Concept*)pData)->classID;
      case OBJ_CLASS_ID_SiteList: return ((OD_SiteList*)pData)->classID;
      case OBJ_CLASS_ID_Keyword: return ((OD_Keyword*)pData)->classID;
      case OBJ_CLASS_ID_ModeratorComment: return ((OD_ModeratorComment*)pData)->classID;
      case OBJ_CLASS_ID_TimeStats: return ((OD_TimeStats*)pData)->classID;
      case OBJ_CLASS_ID_YearStats: return ((OD_YearStats*)pData)->classID;
      case OBJ_CLASS_ID_DayStats: return ((OD_DayStats*)pData)->classID;
      case OBJ_CLASS_ID_Referrer: return ((OD_Referrer*)pData)->classID;
      case OBJ_CLASS_ID_DailyReferrerStats: return ((OD_DailyReferrerStats*)pData)->classID;
      case OBJ_CLASS_ID_SearchWordsInfo: return ((OD_SearchWordsInfo*)pData)->classID;
      case OBJ_CLASS_ID_SuspiciousInfo: return ((OD_SuspiciousInfo*)pData)->classID;
      case OBJ_CLASS_ID_RatingPlaceInfo: return ((OD_RatingPlaceInfo*)pData)->classID;
      case OBJ_CLASS_ID_IPRecord: return ((OD_IPRecord*)pData)->classID;
      case OBJ_CLASS_ID_ViewerReference: return ((OD_ViewerReference*)pData)->classID;
      case OBJ_CLASS_ID_AbstractObject: return ((OD_AbstractObject*)pData)->classID;
      case -1: (void)classID; (void)pData;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
   return NA;
}
//------------------------------------------------------------------------------[]




//------------------------------------------------------------------------------[]
//
// Добавление ключей
//
void pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID)
{
   switch (classID)
   {
      case OBJ_CLASS_ID_Viewer: ((OD_Viewer*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_ViewerGroup: ((OD_ViewerGroup*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_User: ((OD_User*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_TradeStats: ((OD_TradeStats*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Banner: ((OD_Banner*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_BannerProfile: ((OD_BannerProfile*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Page: ((OD_Page*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Site: ((OD_Site*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_SiteProfile: ((OD_SiteProfile*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_ShowEvent: ((OD_ShowEvent*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Registry: ((OD_Registry*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_VBN: ((OD_VBN*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Language: ((OD_Language*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Concept: ((OD_Concept*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_SiteList: ((OD_SiteList*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Keyword: ((OD_Keyword*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_ModeratorComment: ((OD_ModeratorComment*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_TimeStats: ((OD_TimeStats*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_YearStats: ((OD_YearStats*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_DayStats: ((OD_DayStats*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_Referrer: ((OD_Referrer*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_DailyReferrerStats: ((OD_DailyReferrerStats*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_SearchWordsInfo: ((OD_SearchWordsInfo*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_SuspiciousInfo: ((OD_SuspiciousInfo*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_RatingPlaceInfo: ((OD_RatingPlaceInfo*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_IPRecord: ((OD_IPRecord*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_ViewerReference: ((OD_ViewerReference*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case OBJ_CLASS_ID_AbstractObject: ((OD_AbstractObject*)pData)->AddKeyVarForField (ka, fieldID ); return;
      case -1: (void)classID; (void)pData; (void)ka; (void)fieldID;
   }
   SERVER_DEBUG_ERROR_1 ("Неизвестный класс %d", classID);
}
//------------------------------------------------------------------------------[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
