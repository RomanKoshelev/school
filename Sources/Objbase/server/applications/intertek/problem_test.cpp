/*
_____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'bcc'												[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  problem_test.cpp													[]
[] Date: 			  28.06.2000															[]
[] Author:			  Roman V. Koshelev													[]
[] Description:	  Тесты проекта 														[]
[]_________________________________________________________________________[]
*/

#ifdef WIN32
#define USES_OC_ALL
#define USES_MOD_User
#define USES_MOD_InfoDiv
#define USES_MOD_InfoSource
#define USES_MOD_InfoObject
#define USES_MOD_WebFolder
#define USES_MOD_MetaObject



#include "include.h"



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` RunTest                                                                   []
[]                                                                            []
[]____________________________________________________________________________*/
void RunTest (void)
{
	DEBUG_STACK_NAME (RunTest);
	srand(time(0));
	clock_t ini_clock;
	ini_clock = clock();
	puts  ("\n----------------------------------------------------------\n");
//----------------------------------------------------------------------------[] 






#if 0
//______________________________________________________________________________
//                                                                            []
//` Перечисление пользователей                                                []                          
//                                                                            []
	MOD_User_Args arg;
	arg.Login		= "root";
	arg.Password	= "letmein";
	arg.objFirstNo	=	0;
	arg.objLastNo	=	100;

	OBJ_User_Enumerate (arg);
	if (arg.ExitCode==ERR_OK)
	{
		puts ("\nUsers:");
		FOR_EACH_ITEM_EVAL (arg.objIDs,
			{
				printf ("[%d] %s\n", arg.objIDs[i], arg.objNames[i].c_str());
			}
		);
	}
//____________________________________________________________________________[]
#endif
	

	







#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение данных пользователя                                             []                             
//                                                                            []
	arg.Login		= "root";
	arg.Password	= "letmein";
	arg.objID		= FindUserByLogin ("admin");

	OBJ_User_GetData (arg);
	if (arg.ExitCode==ERR_OK)
	{
		string sUser;
		sUser.Format 
		(	
			"User[%d].Data\n"
			"~~~~~~~~~~~~~~~~~~~\n"
			"ReadOnly:          %s\n"
			"Login:             %s\n"
			"FullName:          %s\n"
			"Email:             %s\n"
			"PasswordInBrowser: %s\n",
			 arg.objID, (arg.ReadOnly? "YES": "NO"), arg.Login.c_str(), arg.FullName.c_str(), arg.Email.c_str(), (arg.PasswordInBrowser? "YES": "NO")
		);
		sUser.win_2_dos();
		sUser.Print ();
	}
//____________________________________________________________________________[]
#endif








#if 0
//______________________________________________________________________________
//                                                                            []
//` Изменение данных пользователя                                             []                             
//                                                                            []
	MOD_User_Args arg;
	char *sUser					= "admin";

	arg.Login					= "root";
	arg.Password				= "letmein";
	arg.objID					= FindUserByLogin (sUser);
									
	arg.NewPassword			= "1234";
	arg.NewPasswordConfirm	= "1234";
	arg.FullName				= "Вася Пупкин";
	arg.Email					= "vasja@pupkin.ru";
	arg.PasswordInBrowser	= false;

	OBJ_User_PutData (arg);
	if (arg.ExitCode==ERR_OK)
	{
		arg.Login					= "root";
		arg.Password				= "letmein";
		arg.objID					= FindUserByLogin (sUser);

		OBJ_User_GetData (arg);
		if (arg.ExitCode==ERR_OK)
		{
			string sUser;
			sUser.Format 
			(	
				"User[%d].Data\n"
				"~~~~~~~~~~~~~~~~~~~\n"
				"Login:             %s\n"
				"FullName:          %s\n"
				"Email:             %s\n"
				"PasswordInBrowser: %s\n",
				arg.objID, arg.Login.c_str(), arg.FullName.c_str(), arg.Email.c_str(), (arg.PasswordInBrowser? "YES": "NO")
			);
			sUser.win_2_dos();
			sUser.Print ();
		}
	}
//____________________________________________________________________________[]
#endif
	

	




	
#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение групп прав пользователя                                         []                                 
//                                                                            []
	MOD_User_Args arg;
	arg.Login			= "newsmaker";
	arg.Password		= "123";
	arg.objID			= FindUserByLogin ("newsmaker");
	arg.ExpandGroups	= true;
	arg.ExpandRights	= true;

	printf ("%s >> ", arg.Login);
	MOD_User_GetRights (arg);
	if (arg.ExitCode==ERR_OK)
	{
		string sUser;
		sUser.Format 
		(	
			"User[%d].Groups\n"
			"~~~~~~~~~~~~~~~~~~~\n"
			"Login:             %s\n"
			"ReadOnly:          %s\n"
			"AccessLevel:       %d\n"
			"Groups:\n",
			arg.objID, arg.Login.c_str(), (arg.ReadOnly? "YES": "NO"), arg.ObjAccessLevel
		);
	// Напечатать список групп
		for (int g=0; g<arg.LoginGroupIDs.Size(); g++)
		{
			string sGroup;

			int i = arg.ObjGroupIDs.Find (arg.LoginGroupIDs[g]);
			sGroup.Format 
			(
				"  [%d]  %c %-38s %s\n", 
				arg.LoginGroupIDs[g], 
				(i!=-1?'*':' '), 
				arg.LoginGroupNames[g].c_str(), 
				arg.LoginGroupRights[g].c_str()
			);
			sUser += sGroup;
		}

		sUser.win_2_dos();
		sUser.Print ();
	}
//____________________________________________________________________________[]
#endif
	
	




	

#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение списка доступных разделов                                       []                                   
//                                                                            []
	int N=100;
	MOD_InfoDiv_Args arg;
for (int i=0; i<N; i++)
{
	PRINT_PERCENT (i, N);
	arg.Login				= "user";
	arg.Password			= "123";
	arg.ParentName			= "Concept.Feod.Data.Topic";
	arg.FeodAttributes	= "L";

	MOD_InfoDiv_Enumerate (arg);

	if (arg.ExitCode==ERR_OK)
	{
#if 0
	// Напечатать список разделов
		string sResult="";
		for (int d=0; d<arg.objIDs.Size(); d++)
		{
			string sDiv;

			sDiv.Format 
			(
				"  [%d]  %s\n", 
				arg.objIDs[d],
				arg.objNames[d].c_str()
			);
			sResult += sDiv;
		}

		sResult.win_2_dos();
		sResult.Print ();
#endif
	}
	else
	{
		arg.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg.ExitCodeComment.Print ();
	}
}
//____________________________________________________________________________[]
#endif
	
	
	

#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение списка всех подразделов                                         []                                 
//                                                                            []
	identifier     divID  = GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность");
	identifier_arr subDivIDs;
	InfoDivGetAllSubDivIDs (divID, subDivIDs);
	for (int d=0; d<subDivIDs.Size(); d++)
	{
		if (CHECK_INFODIV_ID(subDivIDs[d]))
		{
			printf ("%d\n", subDivIDs[d]);
		}
		else
		{
			printf ("ERROR!\n");
		}
	}
//____________________________________________________________________________[]
#endif









#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение списка информационных источников                                []                                          
//                                                                            []
	MOD_InfoSource_Args arg;
	arg.Login				= "analyst";
	arg.Password			= "123";
	arg.ShowAll				= true;
	arg.divName				= "Concept.Feod.Data";

	MOD_InfoSource_Enumerate (arg);

	if (arg.ExitCode==ERR_OK)
	{
	// Напечатать список источников
		string sResult="";
		for (int d=0; d<arg.objIDs.Size(); d++)
		{
			string sSrc;

			sSrc.Format 
			(
				"  [%d]  %s\n", 
				arg.objIDs[d],
				arg.objNames[d].c_str()
			);
			sResult += sSrc;
		}

		sResult.win_2_dos();
		sResult.Print ();
	}
	else
	{
		arg.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg.ExitCodeComment.Print ();
	}
//____________________________________________________________________________[]
#endif
	








#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение списка разделов                                                 []                         
//                                                                            []
	MOD_InfoDiv_Args arg;
	arg.Login				= "editor_st";
	arg.Password			= "123";
//	arg.ParentName			=	"Concept.Feod.Data.Mark";
//	arg.ParentName			=	"Concept.Feod.Data.Service";
	arg.ParentName			=	"Concept.Feod.Data";
	arg.FeodAttributes	=	"LRW";

	MOD_InfoDiv_Enumerate (arg);

	if (arg.ExitCode==ERR_OK)
	{
	// Напечатать список разделов
		string sResult="";
		for (int d=0; d<arg.objIDs.Size(); d++)
		{
			string sTmp;

			sTmp.Format 
			(
				"  [%d]  %s\n", 
				arg.objIDs[d],
				arg.objNames[d].c_str()
			);
			sResult += sTmp;
		}

		sResult.win_2_dos();
		sResult.Print ();
	}
	else
	{
		arg.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg.ExitCodeComment.Print ();
	}
//____________________________________________________________________________[]
#endif
	








#if 0
//______________________________________________________________________________
//                                                                            []
//` Получение списка всех подразделов                                         []                                 
//                                                                            []
	identifier     divID  = GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность");
	identifier_arr subDivIDs;
	InfoDivGetAllSubDivIDs (divID, subDivIDs);
	for (int d=0; d<subDivIDs.Size(); d++)
	{
		if (CHECK_INFODIV_ID(subDivIDs[d]))
		{
			printf ("%d\n", subDivIDs[d]);
		}
		else
		{
			printf ("ERROR!\n");
		}
	}
//____________________________________________________________________________[]
#endif









#if 0
//______________________________________________________________________________
//                                                                            []
//` Создание информационного объекта и получение списка                       []                                                   
//                                                                            []
int i=0,NN=30;
#if 0  //{ RomanVK
for (i=0; i<NN; i++)
{
	PRINT_PERCENT (i, NN);
	MOD_InfoObject_Args	arg1;

	arg1.Login				= "root";
	arg1.Password			= "123";
	arg1.Name.Format		("Информационный объект #%d", i+1);
	arg1.InfoTime			=	time(0);//-(rand()*rand())%80000*30*12;
	if (i%10==0)
	{
		arg1.divIDs			+= GetInfoDivIDByType ("Concept.Feod.Data.Mark.Hot");
	}
	else
	{
		arg1.divIDs			+= GetInfoDivIDByType ("Concept.Feod.Data.Mark.Regular");
	}
	arg1.divIDs				+= GetInfoDivIDByType ("Concept.Feod.Data.Service.Public");
	arg1.divIDs				+= GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность.Власть");
	//arg1.divIDs				+= GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность.Нефть");
	//arg1.divIDs				+= GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность.Газ");
	//arg1.divIDs				+= GetInfoDivIDByType ("Concept.Feod.Data.Type.News.Промышленность.Уголь");

	MOD_InfoObject_New	(arg1);
	if (arg1.ExitCode==ERR_OK)
	{
		// ...
	}
	else
	{
		arg1.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg1.ExitCodeComment.Print ();
	}
}

puts ("");
#endif //}

NN = 1;
for (i=0; i<NN; i++)
{
	if (NN>1) PRINT_PERCENT (i, NN);
	MOD_InfoObject_Args	arg2;
	arg2.Login				= "anonymous";
	arg2.Password			= "anonymous";
//	arg2.Time0				= time(0)+80000*30;
//	arg2.Time1				= time(0)-80000*30;
	arg2.objFirstNo		= 1;
	arg2.objLastNo			= 1;
	arg2.divNames			+= "Concept.Feod.Data.Mark.Hot";
	arg2.divNames			+= "Concept.Feod.Data.Service.Public";
//	arg2.divAttributes	= "LR";
	arg2.UpdateStatistics=	true;
	arg2.divLookInSub		=	true;
	MOD_InfoObject_Enumerate (arg2);

	if (arg2.ExitCode==ERR_OK)
	{
	// Напечатать список информационных объектов
		if (NN==1)
		{
			string sResult="";
			sResult.Format ("TotalStoredNum = %d\n", arg2.TotalStoredNum);
			for (int d=0; d<arg2.objIDs.Size(); d++)
			{
				string sInfo;

				sInfo.Format 
				(
					"%3d  [%5d]  '%s'  Time=%d\n", 
					d+1,
					arg2.objIDs[d],
					arg2.objNames[d].c_str(),
					arg2.objInfoTimes[d]
				);
				sResult += sInfo;
			}

			sResult.win_2_dos();
			sResult.Print ();
		}
	}
	else
	{
		arg2.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg2.ExitCodeComment.Print ();
	}
}
//____________________________________________________________________________[]
#endif









#if 0
//______________________________________________________________________________
//                                                                            []
//` Создание папки																				[]
//                                                                            []
int i=0,NN=100;
for (i=0; i<NN; i++)
{
	PRINT_PERCENT (i, NN);
	MOD_WebFolder_Args	arg;

	arg.Login				= "root";
	arg.Password			= "123";
	arg.Name					= "Тестовая папка";
	arg.ParentName			= "Concept.Feod.Files.Site.Public.Archive.Upload";
	MOD_WebFolder_New	(arg);

	arg.ParentID			= NA;
	arg.Login				= "root";
	arg.Password			= "123";
	arg.Name					= "Тестовая папка";
	arg.ParentName			= "Concept.Feod.Files.Site.Public.Archive.Upload.Тестовая папка";
	MOD_WebFolder_New	(arg);

	if (arg.ExitCode==ERR_OK)
	{
		MOD_WebFolder_Args	arg;

		arg.Login				= "admin";
		arg.Password			= "123";
//		arg.Login				= "anonymous";
//		arg.Password			= "anonymous";
		arg.ParentName			= "Concept.Feod.Files.Site.Public";
		arg.IncludeParent		= true;
		arg.AllDescendants	= false;
		arg.FeodAttributes	= "C";
		arg.FullNameLevel		= 30;

		MOD_WebFolder_Enumerate	(arg);

		if (arg.ExitCode==ERR_OK)
		{
#if 0  //{ RomanVK
			string sResult;
			for (int f=0; f<arg.objIDs.Size(); f++)
			{
				string sTmp;
				for (int i=0; i<arg.objLevels[f]; i++) sTmp+="   ";
				sResult += sTmp;
			//	sTmp.Format ("%s    {%s}\n", arg.objNames[f].c_str(), arg.objTypes[f].c_str());
				sTmp.Format ("%s\n", arg.objNames[f].c_str());
				sResult += sTmp;
			}
			sResult.win_2_dos();
			sResult.Print();
#endif //}
		}
		else
		{
			arg.ExitCodeComment.win_2_dos ();
			printf ("ERROR: ");
			arg.ExitCodeComment.Print ();
		}
	}
	else
	{
		arg.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg.ExitCodeComment.Print ();
	}
}
//____________________________________________________________________________[]
#endif









#if 0
//______________________________________________________________________________
//                                                                            []
//` Создание раздела																				[]
//                                                                            []
int i=0,NN=1;
for (i=0; i<NN; i++)
{
	PRINT_PERCENT (i, NN);
	MOD_InfoDiv_Args arg;

	arg.Login						= "root";
	arg.Password					= "123";
	arg.Name							=	"Каталог ресурсов";
	arg.Description				=	"ляляля";
	arg.ParentID					=	GetInfoDivIDByType ("Concept.Feod.Data.Topic");
	arg.AccessLevelThreshold	= 100000;

	MOD_InfoDiv_New	(arg);

	if (arg.ExitCode==ERR_OK)
	{
		printf ("objID = %u", arg.objID);
	}
	else
	{
		arg.ExitCodeComment.win_2_dos ();
		printf ("ERROR: ");
		arg.ExitCodeComment.Print ();
	}
}
//____________________________________________________________________________[]
#endif



#if 1
//______________________________________________________________________________
//                                                                            []
//` Получение списка	метаобъектов															[]
//                                                                            []

//----------------------------------------------------------------------------[] 
#if 0  //{ RomanVK
// Создаём метаобъекты
{
	MOD_MetaObject_Args arg;
	arg.Login	= "root";
	arg.Password= "yucr";
	arg.Type		= "Ref_Пол";
	arg.Name		= "Женский";
	arg.SysName	= "Nachaljnik";
	MOD_MetaObject_New (arg);
}
#endif //}
//----------------------------------------------------------------------------[] 
// Перечисляем метаобъекты
{
	MOD_MetaObject_Args arg;
	arg.Login		= "root";
	arg.Password	= "yucr";
	arg.TypePrefix	= "Ref_";
	arg.objFirstNo	= 0;
	arg.objLastNo	= 49;

	MOD_MetaObject_Enumerate (arg);
	printf ("\narg.objIDs.Size = %d\n", arg.objIDs.Size());
}
//____________________________________________________________________________[]
#endif





	puts  ("\n\n\n----------------------------------------------------------\n");
	printf("\n  **************************\n    Total time: %.2f sec.\n  **************************\n\n", double(clock() - ini_clock) / CLOCKS_PER_SEC);
}
//____________________________________________________________________________[]






#endif // ifdef WIN32
/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/

