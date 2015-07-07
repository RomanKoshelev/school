/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:				MOD_UserGroup.pvt.cpp													[]
[] Date:          01.07.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с группами прав пользователей								[]
[]						Внутренние функции.														[]
[]____________________________________________________________________________[]
*/
#include "MOD_UserGroup.inc.h"



//______________________________________________________________________________
//                                                                            []
//` Добавить всех рутов в указанную группу                                    []                                      
//                                                                            []
void AddRootsToGroup (identifier groupID, identifier loginID)
{
	DEBUG_STACK_NAME (AddRootsToGroup);

	identifier rootGroupID = GetGroupIDByType ("root");
	if (rootGroupID!=NA)
	{
		OC_UserGroup oc_root_group (rootGroupID);
		for (int r=0; r<oc_root_group.m_UserID.Size(); r++)
		{
			identifier rootID = oc_root_group.m_UserID[r];
			if (!OC_Exist (OBJ_CLASS_ID_User, rootID))
			{
				SERVER_DEBUG_ERROR_1 ("Невалидный рутовый пользователь [%d]. Исправлено.", rootID);
				oc_root_group.m_UserID.Del (r);
				r--;
				continue;
			}
		// Каждого пользователя рутовой группы причисляем к созданной группе
		// с тем уровнем доступа, который он имеет в рутовой группе, если только 
		// он не тот самый пользователь, что создал группу.
			if (loginID!=rootID) AddUserToGroup (rootID, groupID);
		}
	}
	else if (!IGNORE_AUTHORIZATION)
	{
		SERVER_DEBUG_ERROR ("Не удалось обнаружить системную группу с типом 'root'");
	}
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор группы прав по её имени                            []                                              
//                                                                            []
identifier GetGroupID (const char * Name, bool JustCheck)
{
	DEBUG_STACK_NAME (GetGroupID);

	OC_UserGroup oc_group;
	oc_group.SetIndex_Name ();
	if (oc_group.Find (Name))
	{
		identifier groupID = oc_group.GetObjectID ();
		if (oc_group.GoNextSame ())
		{
			SERVER_DEBUG_ERROR_1 ("Обнаружено неуникальное имя группы %s", Name);			
		}
		return groupID;
	}

	if (!JustCheck)
	{
		SERVER_DEBUG_ERROR_1 ("Группа с именем [%s] не найдена", Name);
	}
	
	return NA;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Получить идентификатор системной группы по её типу								[]
//                                                                            []
identifier GetGroupIDByType (const char * Type)
{
	DEBUG_STACK_NAME (GetGroupIDByType);

	string strType (Type);

	OC_UserGroup oc_group;
	oc_group.SetIndex_Type ();
	if (!oc_group.Find (Type))
	{
		if (!IGNORE_AUTHORIZATION)
		{
			SERVER_DEBUG_ERROR_1 ("Не удалось найти группу с типом %s.", Type);
		}
		return NA;
	}
	if (oc_group.m_AccessLevelThreshold!=0)
	{
		SERVER_DEBUG_ERROR_3 ("Порог доступа группы %s типа %s должен быть равен SYSTEM_ACCESS_LEVEL (0), а не %d", string(oc_group.m_Name).c_str(), Type, int (oc_group.m_AccessLevelThreshold));
	}


	return oc_group.GetObjectID();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Получить описание прав группы                                             []                             
//                                                                            []
const char* GetGroupRights (identifier groupID, bool bExpand)
{
	DEBUG_STACK_NAME (GetGroupRights);

	// Формат: 
	// feodID|атрибуты|feodName\nfeodID|атрибуты|feodName\n...feodID|атрибуты|feodName

	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("Не найдена группа [%d]", groupID);
		return "";
	}
	OC_UserGroup oc_group (groupID);


	static string Result;
	Result = ""; // Инициировать надо, так как "static"

//	Проходимся по всем феодам группы
	for (int f=0; f<oc_group.m_Rights_Feod.Size(); f++)
	{
		string strFeodID;
		string strFeodName;

		identifier feodID = oc_group.m_Rights_Feod[f];
		if (!CHECK_FEOD_ID(feodID))
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный ID зоны доступа (%d) в группе %s. Исправлено.", feodID, ((string)oc_group.m_Name).c_str());
			oc_group.m_Rights_Feod.Del (f);
			oc_group.m_Rights_Attr.Del (f);
			f--;
			continue;
		}

	// Если требуется раскрывать все дочернии зоны доступа, то делаем это
		identifier_arr allFeods;
		if (bExpand)
		{
			GetAllFeodChilds	(feodID, allFeods);
			allFeods.Insert	(0, feodID);
		}
		else
		{
			allFeods += feodID;
		}

	// Формируем результат
		for (int i=0; i<allFeods.Size(); i++)
		{
			if (GetFeodFullName (allFeods[i], strFeodName, 1, "::"))
			{
				string strFeodType;
				GetFeodType (allFeods[i], strFeodType);
				strFeodID.Format ("%d", allFeods[i]);
				Result += "\n";
				Result += strFeodID;
				Result += "|";
				Result += oc_group.m_Rights_Attr[f];
				Result += "|";
				Result += strFeodName;
				Result += "|";
				Result += strFeodType;
			}
			else
			{
				SERVER_DEBUG_ERROR ("Обнаружен невалидный феод, пытаемся выправить ситуацию вызовом функции FIX_FEODS.");
				FIX_FEODS ();
			}
		}
	}

	return Result.c_str();
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` CreateUserGroup                                                           []               
//                                                                            []
ERR_RESULT CreateUserGroup (const char* Name, const char* Type, const char* Description, int AccessLevelThreshold, const char* sFeodAttr)
{
	DEBUG_STACK_NAME (CreateUserGroup);

// Имя группы должно быть уникальным
	if (GetGroupID (Name, true)!=NA)
	{
		return ERR_NameAlreadyExists;
	}

// Разбираем входные строки на массивы -- зоны доступа и уровни доступа
	string		FeodAttrStr (sFeodAttr);
	string_arr	FeodAttrArr;

	FeodAttrStr.explode	(FeodAttrArr, "]");
	FOR_EACH_ITEM			(FeodAttrArr, trim);


// Создаём группу и добавляем в неё отпарсенные права (зоны доступа и уровни доступа)
	OC_UserGroup oc_group;
	identifier groupID = oc_group.New ();

	oc_group.m_Name						=	Name;
	oc_group.m_Description				=	Description;
	oc_group.m_AccessLevelThreshold	=	AccessLevelThreshold;
	oc_group.m_CreationTime				=	time(0);
	oc_group.m_Type						=  Type;

	FOR_EACH_ITEM_EVAL (FeodAttrArr, 
	{
		if (FeodAttrArr[i].IsEmpty()) continue;
		string_arr FA;
		FeodAttrArr[i].explode	(FA, "[");
		FOR_EACH_ITEM				(FA, trim);
		string sFeod=FA[0];
		string sAttr=FA[1];
		identifier feodID = GetFeodIDByType (sFeod);
		if (feodID!=NA)
		{
		// Проверяем корректность атрибутов
			if (!CHECK_ATTRIBUTES (sAttr))
			{
				continue;
			}
			oc_group.m_Rights_Feod.Add (feodID);
			oc_group.m_Rights_Attr.Add (sAttr);
		}
		else
		{
			SERVER_DEBUG_ERROR_1 ("Нет такой зоны доступа: %s", sFeod.c_str());
		}
	});

// Добавляем всех рутов в созданную группу
	AddRootsToGroup (groupID, NA);


	return ERR_OK;
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Упростить набор прав группы                                               []
//                                                                            []
void UserGroupSimplifyRightsSet	(identifier groupID)
{
	DEBUG_STACK_NAME (UserGroupSimplifyRightsSet);

	if (!OC_Exist (OBJ_CLASS_ID_UserGroup, groupID))
	{
		SERVER_DEBUG_ERROR_1 ("Не найдена группа [%d]", groupID);
		return;
	}
	OC_UserGroup oc_group (groupID);

	identifier_arr FeodArr	= oc_group.m_Rights_Feod;
	string_arr		AttrArr	= oc_group.m_Rights_Attr;

// Проверка на соответствие параллельных массивов
	SERVER_DEBUG_ASSERT (FeodArr.Size() == AttrArr.Size(), "Разные размеры массивов имён прав и их атрибутов");

// Объявляем переменные статическими чтобы избежать глупой ошибки "INTERNAL COMPILER ERROR" в VC++ 6.0
	static int f,r;

// Проверка феодов на корректность
	for (f=0; f<FeodArr.Size(); f++)
	{
		if (!CHECK_FEOD_ID(FeodArr[f]))
		{
			SERVER_DEBUG_ERROR_2 ("Невалидный ID зоны доступа (%d) в группе %s. Исправлено.", FeodArr[f], ((string)oc_group.m_Name).c_str());
			FeodArr.Del (f);
			AttrArr.Del (f);
			f--;
			continue;
		}
	}

//	Исключение дублирования и слияние атрибутов для одинаковых зон
	for (f=0; f<FeodArr.Size(); f++)
	{
		for (r=f+1; r<FeodArr.Size(); r++) if (FeodArr[f]==FeodArr[r])
		{
		// Нашлись два одинаковых феода -- права можно объединить
			for (int a=0; a<(int)AttrArr[r].Len(); a++)
			{
			// Во втором праве есть атрибут, не присутствующий в первом, его надо перенести в первое право
				if (AttrArr[f].Find(AttrArr[r][a])==-1)
				{
					AttrArr[f]+=AttrArr[r][a];
				}
			}
		// Удаляем дублирующееся право
			FeodArr.Del(r);
			AttrArr.Del(r);
			r--;
		}
	}

//	Исключение выводимых прав.
	for (f=0; f<FeodArr.Size(); f++)
	{
		for (r=f+1; r<FeodArr.Size(); r++) if (FeodHasChild (FeodArr[f], FeodArr[r]))
		{
		// Второй феод выводится из первого, если он не имеет таких атрибутов, каких нет у первого, его следует выкинуть
			bool bHasUniqueAttr = false;
			for (int a=0; a<(int)AttrArr[r].Len(); a++)
			{
			// Во втором, более частном, праве есть атрибут, не присутствующий в первом, более общем. Частное право надо сохранить.
				if (AttrArr[f].Find(AttrArr[r][a])==-1)
				{
					bHasUniqueAttr = true;
					break;
				}
			}
			if (!bHasUniqueAttr)
			{
			// Удаляем полностью выводимое право
				FeodArr.Del(r);
				AttrArr.Del(r);
				r--;
			}
		}
	}

// Прописываем в группу упрощённый набор прав
	oc_group.m_Rights_Feod	=	FeodArr;
	oc_group.m_Rights_Attr	=	AttrArr;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/