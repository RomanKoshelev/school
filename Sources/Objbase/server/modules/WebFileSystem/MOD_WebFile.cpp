/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'IT'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:          MOD_WebFile.cpp															[]
[] Date:          4.08.2000																	[]
[] Author:        Roman V. Koshelev															[]
[] Description:   Работа с файлами.															[]
[]						Интерфейсные функции.													[]
[]____________________________________________________________________________[]
*/
#include "MOD_WebFile.inc.h"








//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` СОЗДАНИЕ НОВОГО ФАЙЛА																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_New (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_New);
/*............................................................................[]
		<Login                  Логин пользователя, запрашивающего операцию. Пользователь должен обладать правами создания файлов во всех указанных папках.
		<Password               Пароль пользователя, запрашивающего операцию.

		<Name                   Имя создаваемого файла.
		<Description            Описание создаваемого файла.
		<Name_Upload				Имя, под которым файл загружался.
		<OS_Path						Полный путь к тому месту, где скрипты будут хранить копию файла.
		<OS_Ext						Расширение файла. Полное имя OS-копии файла получится = <OS_Path><objID>.<OS_ext>
		<MIMEType					MIME-тип, например: "image/jpeg", "object-link/InfoObject"
		<IconType					Интерпретируемое скриптами значение, для отображения иконки.
		<PlainTextData				Образ текстового содержания файла, если возможно.
		<BinaryData					Бинарное содержимое файла.
		<folderIDs					К каким папкам будет относиться объект.

		>objID                  Идентификатор созданного объекта.
		>ExitCode               Код возврата.
		>ExitCodeComment        Текстовый комментарий к коду возврата.
*///..........................................................................[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Папки должны существовать
	int f;
	for (f=0; f<arg.folderIDs.Size(); f++) if (!CHECK_WEBFOLDER_ID (arg.folderIDs[f]))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указана некорректная папка ID=%d", arg.folderIDs[f]);
	}

// Проверяем логин и пароль
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь права создавать объекты в указанных папках
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		OC_WebFolder oc_folder (arg.folderIDs[f]);
		res=USER_CHECK_ACCESS (loginID, guid(oc_folder.m_MOD_Base_GUID).id, "C");
		if (res!=ERR_OK)
		{
			string folderName;
			GetWebFolderFullName (arg.folderIDs[f], folderName);
			ERR_RETURN_COMMENT_3 (res, "Пользователь %s не имеет права создавать объекты в папке '%s'[%d]", arg.Login.c_str(), folderName.c_str(), arg.folderIDs[f]);
		}
	}
//----------------------------------------------------------------------------[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Загружаемое имя файла не должно быть пустым
	if (arg.Name_Upload.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Загружаемое имя файла не должно быть пустым");
	}
// Если имя пустое -- исgользуем Name_Upload
	if (arg.Name.IsEmpty())
	{
		arg.Name = arg.Name_Upload;
	}
// Должна быть указана хотя-бы одна папка
	if (arg.folderIDs.Size()==0)
	{
		ERR_RETURN_COMMENT (ERR_BadArgument, "Должна быть указана хотя-бы одна папка");
	}
//----------------------------------------------------------------------------[] 



//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Создаём файл и записываем его в папку
	OC_WebFile oc_file;
	identifier fileID = oc_file.New ();
	guid	fileGUID		= oc_file.GetObjectGUID();
	string OSName;
	OSName.Format ("%s%u.%s", arg.OS_Path.c_str(), fileID, arg.OS_Ext.c_str());
	time_t CurTime	= time (0);


	FULL_INDEX_BEGIN (oc_file);
	{
		oc_file.m_Name						=	arg.Name;
		oc_file.m_Description			=	arg.Description;
		oc_file.m_Name_Upload			=	arg.Name_Upload;
		oc_file.m_Name_OSFile			=	OSName;
		oc_file.m_MIMEType				=	arg.MIMEType;
		oc_file.m_IconType				=	arg.IconType;

		oc_file.m_Text						=	arg.PlainTextData;
		oc_file.m_BinaryData				=	arg.BinaryData;

		oc_file.m_CreationTime			=	CurTime;
		oc_file.m_ModificationTime		=	CurTime;
		oc_file.m_LastAccessTime		=	CurTime;
		oc_file.m_OwnerGUID				=	GetUserGUID (loginID);
	}
	FULL_INDEX_END (oc_file);

// Добавляем файл в папки
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		OC_WebFolder oc_folder (arg.folderIDs[f]);
		oc_folder.m_WebFileSortedID.InsertSorted (fileID);
	}

	arg.objID = fileID;
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПЕРЕЧИСЛЕНИЕ ФАЙОВ																			[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_Enumerate (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_Enumerate);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право получения списка.
		<Password					Пароль пользователя, запрашивающего операцию.
		<objFirstNo					Номер объекта, с которого их перечислять.
		<objLastNo					Номер последнего запрашиваемого объекта.
		<folderID					К какой папке должен принадлежать файл. Если не указано -- работать по folderName.
		<folderName					К папке с каким именем должен принадлежать файл, если не указан folderID. Полное имя вида "Concept.Feod.Files.Site".
		<UpdateStatistics			Надо ли изменять статистику показов/кликов/CTR запрашиваемых файлов.

		>objIDs						Массив идентификаторов объектов.
		>objNames					Массив названий объектов.
		>objOSNames					Имена, под которыми файлы дублируется на сервере, например, files/435662.jpg
		>objIconTypes				Интерпретируемые скриптами значения, для отображения иконок.
		>objDescriptions			Массив описаний объектов (анонсы).
		>objCreationTimes			Времена создания файлов.
		>objStatShows				Сколько раз файл был показан
		>objStatClicks				Сколько раз файл был востребован для просмотра
		>objStatCTRs				objStatClicks*100/objStatShows
		>TotalStoredNum			Сколько всего файлов может быть перечислено.
		>MaxNumInQuery				Максимально допустимое число запрашиваемых за один раз файлов.
		>ExitCode					Код возврата.
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]

	

//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[]
// Если не указан ID папки, берём по имени.
	if (arg.folderID==NA)
	{
		arg.folderID = GetWebFolderIDByType (arg.folderName);
	}
// Папка должна существовать
	if (!CHECK_WEBFOLDER_ID (arg.folderID)) 
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Указана несуществующая папка ID=%d", arg.folderID);
	}

// Чтобы не запросили слишком много объектов
	arg.objFirstNo = max (arg.objFirstNo, 0);
	if (arg.objLastNo==INT_MAX) arg.objLastNo=arg.objFirstNo+MAX_WEBFILE_ENUMERATE_NUM;
	if ((arg.objLastNo - arg.objFirstNo) > MAX_WEBFILE_ENUMERATE_NUM)
	{
		ERR_RETURN (ERR_TooManyEnumerate);
	}
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь право получения списка файлов в указанной папке.
	res = USER_CHECK_ACCESS (loginID, guid(OC_WebFolder(arg.folderID).m_MOD_Base_GUID).id, "L");
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT_2 (ERR_AccessDeny, "Пользователь %s не иммеет права полуения списка в указанной папке %u", arg.Login.c_str(), arg.folderID);
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Эту переменную пишу здесь как статическую, так как иначе глупый VC++6.0 
//	выдаёт INTERNAL COMPILER ERROR
	static int i=0;

// Находим все идентификаторы файлов, отсортированные по имени
	OC_WebFile oc_file;
	oc_file.SetIndex_Name ();
	identifier_arr fileIDs;
	oc_file.GetClassIdList (fileIDs);


// Оставляем только те файлы, которые находятся в указанной папке
	identifier_arr oc_folder_m_WebFileSortedID;
	WebFolderGetWebFileSortedIDs (arg.folderID, oc_folder_m_WebFileSortedID);
// Ищем файлы в запрашиваемой папках
	for (i=0; i<fileIDs.Size(); i++)	if (oc_folder_m_WebFileSortedID.Find (fileIDs[i], true)==-1)
	{
	// файл не найден -- выкидываем его
		fileIDs.Del (i);
		i--;
	}

// fileIDs -- все файлы запрашиваемой папки 
// Оставляем необходимое количество.
	for (i=arg.objFirstNo; i<=arg.objLastNo && i<fileIDs.Size(); i++)
	{
		if (!OC_Exist (OBJ_CLASS_ID_WebFile, fileIDs[i]))
		{
			SERVER_DEBUG_ERROR_1 ("Некорректный идентификатор файла %d", fileIDs[i]);
			continue;
		}
		OC_WebFile oc_file (fileIDs[i]);
		
		arg.objIDs				+= fileIDs[i];
		arg.objNames			+=	oc_file.m_Name;
		arg.objDescriptions	+=	oc_file.m_Description;
		arg.objCreationTimes	+=	oc_file.m_CreationTime;
		arg.objOSNames			+=	oc_file.m_Name_OSFile;
		arg.objIconTypes		+=	oc_file.m_IconType;

		arg.objStatShows		+= oc_file.m_ShowCount;
		arg.objStatClicks		+=	oc_file.m_ClickCount;
		arg.objStatCTRs		+=	oc_file.m_CTR;

	// Если необходимо, изменяем статистику.
		if (arg.UpdateStatistics)
		{
			oc_file.m_ShowCount	+= 1;
			if (oc_file.m_ShowCount!=0)
			{
				oc_file.m_CTR = (oc_file.m_ClickCount*100)/float(int(oc_file.m_ShowCount));
			}
		// !!! Изменить статистику у папки
		}
	}

	arg.TotalStoredNum = fileIDs.Size();
//----------------------------------------------------------------------------[] 


	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]











//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ПОЛУЧЕНИЕ ДАННЫХ ФАЙЛА																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_GetData (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_GetData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право чтения "R" хотя бы в одной папке, содержащей файл.
		<Password					Пароль пользователя, запрашивающего операцию.
		<objID						Идентификатор запрашиваемого информационного объекта.
		<UpdateStatistics			Надо ли изменять статистику показов/кликов/CTR.
		<NeedBinaryData			Нужно ли возвращать бинарное содержимое.
		<NeedPlainTextData		Нужно ли возвращать текстовый образ.

		>Name							Название файла.
		>Name_Upload				Имя, под которым файл загружался.
		>Name_OS						Имя, под которым файл дублируется на сервере, например, files/435662.jpg
		>Description				Описание файла.

		>CreationTime				Время создание файла.
		>Version						Число модификаций файла.
		>MIMEType					MIME-тип, например: "image/jpeg", "object-link/InfoObject"
		>IconType					Интерпретируемое скриптами значение, для отображения иконки.

		>BinaryData					Бинарное содержимое файла, если необходимо.
		>PlainTextData				Образ текстового содержания файла, если необходимо.

		>OwnerID						Создатель файла. [User]
		>folderIDs					К каким папкам относится файл. (Перечисляются только те, к которым есть доступ [L])
		>folderNames				Имена папок.

		>StatShow					Сколько раз объект был показан
		>StatClick					Сколько раз объект был востребован для просмотра
		>StatCTR						objStatView*100/objStatShow

		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]



//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Запрашиваемый Файл должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_WebFile, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый Файл %d не существует", arg.objID);
	}
	OC_WebFile oc_file (arg.objID);
//----------------------------------------------------------------------------[] 




//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}

// Пользователь должен иметь право чтение файла хотя бы в одной из папок, в которых тот лежит
	bool bAccess=false;
	int f;
	for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (oc_file.m_WebFolderID[f]), "R");
		if (res==ERR_OK)
		{
			bAccess = true;
			break;
		}
	}
	if (!bAccess)
	{
		ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "Пользователь %s не иммеет права читать указанный файл", arg.Login.c_str());
	}
//----------------------------------------------------------------------------[]





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Если необходимо, изменяем статистику.
	if (arg.UpdateStatistics)
	{
		oc_file.m_ClickCount	+= 1;
		if (oc_file.m_ShowCount!=0)
		{
			oc_file.m_CTR = (oc_file.m_ClickCount*100)/float(int(oc_file.m_ShowCount));
		}
	// !!! Изменить статистику у папок
	}
	oc_file.m_LastAccessTime = time(0);

// Заполняем выходные аргументы
	arg.Name					=	oc_file.m_Name;
	arg.Description		=	oc_file.m_Description;

	arg.Name_Upload		=	oc_file.m_Name_Upload;
	arg.Name_OS				=	oc_file.m_Name_OSFile;

	arg.CreationTime		=	oc_file.m_CreationTime;
	arg.Version				=	oc_file.m_Version;
	arg.MIMEType			=	oc_file.m_MIMEType;
	arg.IconType			=	oc_file.m_IconType;

	arg.StatShow			=	oc_file.m_ShowCount;
	arg.StatClick			=	oc_file.m_ClickCount;
	arg.StatCTR				=	oc_file.m_CTR;

	if (arg.NeedBinaryData)					arg.BinaryData			= oc_file.m_BinaryData;
	if (arg.NeedPlainTextData)				arg.PlainTextData		= oc_file.m_Text;

	if (OC_Exist(oc_file.m_OwnerGUID))	arg.OwnerID				=	guid(oc_file.m_OwnerGUID).id;
	else											oc_file.m_OwnerGUID	=	guid ((char)0);


// Перечисляем те разделы, в которых пользователь может увидеть файл
	for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		identifier folderID = oc_file.m_WebFolderID[f];
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (folderID), "L");
		if (res==ERR_OK)
		{
			string folderFullName;
			if (GetWebFolderFullName (folderID, folderFullName))
			{
				arg.folderIDs	+=	folderID;
				arg.folderNames+=	folderFullName;
			}
			else
			{
				SERVER_DEBUG_ERROR_2 ("Некорректный идентификатор папки %d у файла %d", identifier (folderID), arg.objID);
			}
		}
	}
//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]














//______________________________________________________________________________
//                                                                            []
//                                                                            []
//` ИЗМЕНЕНИЕ ДАННЫХ ФАЙЛА																		[]
//                                                                            []
//____________________________________________________________________________[]
//
//
//
ERR_RESULT MOD_WebFile_PutData (MOD_WebFile_Args& arg)
{
	DEBUG_STACK_NAME (MOD_WebFile_PutData);
/*............................................................................[]
		<Login						Логин пользователя, запрашивающего операцию. Для выполнения операции пользователь должен иметь право записи "W" хотя бы в одной папке, содержащей файл или быть владельцем файла.
		<Password					Пароль пользователя, запрашивающего операцию.

		<objID						Идентификатор запрашиваемого информационного файла.
		<Name							Новое имя файла.
		<Description				Описание файла.
		<MIMEType					MIME-тип, например: "image/jpeg", "object-link/InfoObject"
		<IconType					Интерпретируемое скриптами значение, для отображения иконки. Строка.

		<ContentChanged			Если true, значит изменяется содержимое и учитываются поля Name_Upload, OS_Path, OS_Ext, BinaryData и PlainTextData.
		<Name_Upload				Имя, под которым загружается файл.
		<OS_Path						Полный путь к тому месту, где скрипты будут хранить копию файла.
		<OS_Ext						Расширение файла. Полное имя OS-копии файла получится = <OS_Path><objID>.<OS_ext>
		<PlainTextData				Образ текстового содержания файла, учитывается если ContentChanged==true.
		<BinaryData					Бинарное содержимое файла, учитывается если ContentChanged==true.

		<folderIDs					К каким папкам, по меннию логина, должен отностится файл. Логин не может выкинуть файл из папки без доступа [D] и добавить в папку без доступа [C]. Файл обязан лежать хотя-бы в одной папке.

		>ExitCode					Код возврата (OK BadLogin BadPassword AccessDeny).
		>ExitCodeComment			Текстовый комментарий к коду возврата.
*///..........................................................................[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка доступа																				[]                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Объявляем переменные статическими чтобы избежать глупой ошибки "INTERNAL COMPILER ERROR" в VC++ 6.0
	static int f;

// Запрашиваемый файл должен существовать
	if (!OC_Exist (OBJ_CLASS_ID_WebFile, arg.objID))
	{
		ERR_RETURN_COMMENT_1 (ERR_BadID, "Запрашиваемый файл %d не существует", arg.objID);
	}
	OC_WebFile oc_file (arg.objID);

// Проверка пароля
	identifier loginID=NA;
	ERR_RESULT res = USER_CHECK_LOGIN_PASSWORD (arg.Login, arg.Password, loginID);
	if (res!=ERR_OK)
	{
		ERR_RETURN_COMMENT (res, "Некорректный пароль или логин");
	}
	guid loginGUID = GetUserGUID (loginID);

// Пользователь должен иметь право редактирования файла хотя бы в одной папке или быть владельцем файла
	bool	 bAccess = (guid(oc_file.m_OwnerGUID) == loginGUID);
	if (!bAccess) for (f=0; f<oc_file.m_WebFolderID.Size(); f++)
	{
		res = USER_CHECK_ACCESS (loginID, GetFeodIDByWebFolderID (oc_file.m_WebFolderID[f]), "W");
		if (res==ERR_OK)
		{
			bAccess = true;
			break;
		}
	}
	if (!bAccess)
	{
		ERR_RETURN_COMMENT_1 (ERR_AccessDeny, "Пользователь %s не иммеет изменять указанный файл", arg.Login.c_str());
	}
//----------------------------------------------------------------------------[]






//----------------------------------------------------------------------------[] 
//                                                                            []
// Проверка аргументов	                                                      []                    
//                                                                            []
//----------------------------------------------------------------------------[] 
// Имя объекта не должно быть пустым
	if (arg.Name.IsEmpty())
	{
		ERR_RETURN_COMMENT (ERR_BadName, "Имя файла не может быть пустым");
	}
//----------------------------------------------------------------------------[] 





//----------------------------------------------------------------------------[] 
//                                                                            []
// Выполнение запроса																			[]
//                                                                            []
//----------------------------------------------------------------------------[] 
// Перемещаем объект по разделам:
// arg.folderIDs -- к каким папкам, по меннию логина, должен принадлежать файл.
// Логин не может выкинуть файл из папки без доступа [D] и добавить в папку без доступа [C].
	identifier_arr new_folder_arr = oc_file.m_WebFolderID;

// Проходимся по папкам объекта и смотрим, какие из них не указаны пользователем, т.е. он решил их выкинуть
	for (f=0; f<new_folder_arr.Size(); f++)
	{
		identifier folderID = new_folder_arr[f];
		if (arg.folderIDs.Find(folderID)==-1)
		{
		// Пользователь решил, что файл не должен находиться в папке folderID
			if (USER_CHECK_ACCESS_TO_WEBFOLDER (loginID, folderID, "D")==ERR_OK)
			{
			// Пользователь имеет право выкинуть файл из папки
				new_folder_arr.Del (f);
				f--;
			// Выкидываем файл из папки
				OC_WebFolder oc_folder (folderID);
				int nIndex = oc_folder.m_WebFileSortedID.Find (arg.objID, true);
				if (nIndex!=-1)
				{
					oc_folder.m_WebFileSortedID.Del (nIndex);
				}
			}
		}
	}

// Проходимся по папкам, указанным пользоваетелем и смотрим, каких из них нет у файла, т.е. он решил их добавить
	for (f=0; f<arg.folderIDs.Size(); f++)
	{
		identifier folderID = arg.folderIDs[f];
		if (new_folder_arr.Find(folderID)==-1)
		{
		// Пользователь решил, что файл должен находиться в папке folderID
			if (USER_CHECK_ACCESS_TO_WEBFOLDER (loginID, folderID, "C")==ERR_OK)
			{
			// Пользователь имеет право добавить файл в папку
				new_folder_arr.Add (folderID);
				OC_WebFolder (folderID).m_WebFileSortedID.InsertSorted (arg.objID);
			}
		}
	}

// Изменяем принадлежность объекта папкам
	if (new_folder_arr.Size()!=0)	oc_file.m_WebFolderID = new_folder_arr;
	else									ERR_RETURN_COMMENT (ERR_BadArgument, "Файл должен находиться хотя-бы одной папке");


// Изменяем простые поля файла
	FULL_INDEX_BEGIN (oc_file);
	{
		oc_file.m_Name						=	arg.Name;
		oc_file.m_Description			=	arg.Description;
		oc_file.m_MIMEType				=	arg.MIMEType;
		oc_file.m_IconType				=	arg.IconType;
		oc_file.m_ModificationTime		=	time(0);
	}
	FULL_INDEX_END (oc_file);

	if (arg.ContentChanged)
	{
		string OSName;
		OSName.Format ("%s%u.%s", arg.OS_Path.c_str(), arg.objID, arg.OS_Ext.c_str());
		oc_file.m_Text					=	arg.PlainTextData;
		oc_file.m_BinaryData			=	arg.BinaryData;
		oc_file.m_Name_OSFile		=	OSName;
		oc_file.m_Name_Upload		=	arg.Name_Upload;
		oc_file.m_Version				+=	1;
	}

//----------------------------------------------------------------------------[] 

	ERR_RETURN (ERR_OK);
}
//____________________________________________________________________________[]







// !! При удалении объекта выкидывать его из индекса!







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/