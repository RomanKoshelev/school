/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Admin.cpp                                              []
[] Date:            24.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Интерфейсные функции для администратора                   []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                 
#define USES_BX_SingleObject
#define USES_BX_Errors
#define USES_BX_Macros
#define USES_BX_Admin
#define USES_BX_Concept
#define USES_BX_User
#define USES_BX_Site


#define USES_MemoryManager_h

#define USES_OC_Viewer
#define USES_OC_Site
#define USES_OC_Concept


// for BX_Admin_GetObjectNum():
#define USES_OC_ViewerReference
#define USES_OC_IPRecord
#define USES_OC_Referrer
#define USES_OC_ModeratorComment
#define USES_OC_Keyword
#define USES_OC_Concept
#define USES_OC_VBN
#define USES_OC_ShowEvent
#define USES_OC_Site
#define USES_OC_BannerProfile
#define USES_OC_Banner
#define USES_OC_User

#include "BX.h"


//______________________________________________________________________________
//                                                                            []
//` BX_Admin_MemoryManagerReport                                              []                            
//                                                                            []
BX_RESULT
BX_Admin_MemoryManagerReport(BX_Admin_Args& arg)
{
//	if (!CheckAdminPassword(arg.Password))	return BXE_BadAdminPassword;

	arg.MemoryManagerReport = string(MEMORY_MANAGER_REPORT(true));
	
	return BX_OK;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_ConceptRate_Reg_InetAudience                                           []                               
//                                                                            []
BX_RESULT
BX_ConceptRate_Reg_InetAudience(BX_ConceptRate_Args& arg)
{
	return BX_Concept_PrepareForPrinting(
				oc_reg.m_CRN_InetAudience.GetCPtr(),
				arg.TypeNums,
				arg.objLanguageNo,
				arg.CRN_Name,
				arg.CRN_Value,
				arg.CRN_Level
				);
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_ConceptRate_Site_Visitor                                               []                           
//                                                                            []
BX_RESULT 
BX_ConceptRate_Site_Visitor(BX_ConceptRate_Args& arg)
{
	OC_Site	oc_site;
	BX_CHECK_AND_OPEN(oc_site, arg.objID, OBJ_CLASS_ID_Site);

	return BX_Concept_PrepareForPrinting(
				oc_site.m_CRN_Visitor.GetCPtr(),
				arg.TypeNums,
				arg.objLanguageNo,
				arg.CRN_Name,
				arg.CRN_Value,
				arg.CRN_Level);
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_ConceptRate_Viewer_Site                                                []                          
//                                                                            []
BX_RESULT	
BX_ConceptRate_Viewer_Site(BX_ConceptRate_Args& arg)
{
	OC_Viewer	oc_viewer;
	BX_CHECK_AND_OPEN(oc_viewer, arg.objID, OBJ_CLASS_ID_Viewer);

	return BX_Concept_PrepareForPrinting(
				oc_viewer.m_CRN_Site.GetCPtr(),
				arg.TypeNums,
				arg.objLanguageNo,
				arg.CRN_Name,
				arg.CRN_Value,
				arg.CRN_Level);
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` BX_ConceptRate_Viewer_Inquiry                                             []                             
//                                                                            []
BX_RESULT
BX_ConceptRate_Viewer_Inquiry(BX_ConceptRate_Args& arg)
{
	OC_Viewer	oc_viewer;
	BX_CHECK_AND_OPEN(oc_viewer, arg.objID, OBJ_CLASS_ID_Viewer);

	return BX_Concept_PrepareForPrinting(
				oc_viewer.m_CRN_Inquiry.GetCPtr(),
				arg.TypeNums,
				arg.objLanguageNo,
				arg.CRN_Name,
				arg.CRN_Value,
				arg.CRN_Level);
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` RCR                                                                       []   
//                                                                            []
// Циклический сдвиг вправо:
void RCR(unsigned int &x, int HowMany = 0)
{
	if (HowMany < 0 || HowMany > 31) return;

	bool Carry;	// флаг переноса
	
	for (int i = 0; i < HowMany; i++)
	{
		if (x&1) {
			Carry = true;
		}
		else	{
			Carry = false;
		}

		x >>= 1;

		if (Carry) {
			x |= (1 << 31); // 0x80000000
		}
	}

	return;
}

//______________________________________________________________________________
//                                                                            []
//` CheckPassword                                                             []             
//                                                                            []
bool
CheckAdminPassword(const string& Password)
{
	tm*				TS			= NULL;
	unsigned int	Pass		= 0;
	unsigned int	PassTry	= 0;
	time_t			GMTime	= time (NULL);

	sscanf(Password.c_str(), "%x", &PassTry);
		
	TS = localtime(&GMTime);

	Pass |= int(TS->tm_mday);
	Pass |= (((int)TS->tm_mon+1) << 8);
	RCR(Pass, TS->tm_hour);

	if (Pass == PassTry)	{
		return true;
	}

	return false;
}
//____________________________________________________________________________[]

//______________________________________________________________________________
//                                                                            []
//` GetAdminPassword                                                          []                
//                                                                            []
void
GetAdminPassword(string& Password)
{
	tm*				TS			= NULL;
	unsigned int	Pass		= 0;
	time_t			GMTime	= time (NULL);

	TS = localtime(&GMTime);

	Pass |= int(TS->tm_mday);
	Pass |= (((int)TS->tm_mon+1) << 8);
	RCR(Pass, TS->tm_hour);

	Password.Format("%x", Pass);

	return;
}
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` SaveField                                                                 []         
[]                                                                            []
[]____________________________________________________________________________*/
void SaveField(string &OutputString, const bool			&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%s", FieldName, Field ? "1":"0");	return;
}
void SaveField(string &OutputString, const byte			&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%d", FieldName, (int)Field);			return;
}
void SaveField(string &OutputString, const int			&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%d", FieldName, Field);				return;
}
void SaveField(string &OutputString, const time_t		&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%li", FieldName, Field);				return;
}
void SaveField(string &OutputString, const float		&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%f", FieldName, Field);				return;
}
void SaveField(string &OutputString, const identifier	&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%lu", FieldName, Field);				return;
}
void SaveField(string &OutputString, const string		&Field, const char *FieldName) {
	OutputString.Format("\x03\n%s=\x04%s", FieldName, Field.c_str());		return;
}
//----------------------------------------------------------------------------[]
void SaveField(string &OutputString, const bool_arr	&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%s", Field[i] ? "1":"0");		OutputString += StrTmp;
	}	return;
}
void SaveField(string &OutputString, const byte_arr	&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%d", (int)Field[i]);		OutputString += StrTmp;
	}	return;
}
void SaveField(string &OutputString, const int_arr		&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%d", Field[i]);		OutputString += StrTmp;
	}	return;
}
void SaveField(string &OutputString, const float_arr	&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%f", Field[i]);		OutputString += StrTmp;
	}	return;
}
void SaveField(string &OutputString, const identifier_arr&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%lu", Field[i]);		OutputString += StrTmp;
	}	return;
}
void SaveField(string &OutputString, const string_arr	&Field, const char *FieldName) {
	string StrTmp;	OutputString.Format("\x03\n%s=", FieldName);
	for (int i = 0; i < Field.Size(); i++)	{
		StrTmp.Format("\x04%s", Field[i].c_str());		OutputString += StrTmp;
	}	return;
}
//----------------------------------------------------------------------------[]

#define OBJECT_DELIMITER		"\n\n\x01"
#define FUNCTION_DELIMITER		"\n\x02"
#define BACKUP_FILENAME			"backup.txt"
//______________________________________________________________________________
//                                                                            []
//` BX_Admin_SaveBXObjects                                                    []                      
//                                                                            []
BX_RESULT 
BX_Admin_SaveBXObjects(BX_Admin_Args& arg)
{
	OC_VBN			oc_vbn;
	OC_User			oc_user;
	OC_Site			oc_site;
	key_arr			ka;

	BX_User_Args	user_args;
	BX_Site_Args	site_args;

	string			sFile;
	string			sTemp;

	if (!CheckAdminPassword(arg.Password))
		return BXE_BadAdminPassword;

//----------------------------------------------------------------------------[]
// Сохранение пользователей:
	for (oc_user.GoFirst(); oc_user.IsValid(); oc_user.GoNext())
	{
		sFile += OBJECT_DELIMITER;

	// Найти VBN юзера с целью узнать её ID:
		ka.Init();
		ka += (byte)oc_user.m_VBN;
		oc_vbn.SetIndex_No();
		SERVER_DEBUG_ASSERT_RETURN(oc_vbn.Find(ka), "BX_Admin_SaveBXObjects(): Invalid User::VBN.", BX_SYSTEM_ERROR);

	// Получить данные о пользователе:
		user_args.objID		= oc_user.GetObjectID();
		user_args.Login		= oc_user.m_Login;
		user_args.Password	= oc_user.m_Password;
		user_args.VBN			= oc_vbn.GetObjectID();
		BX_ASSERT_RETURN(BX_User_GetData(user_args));

	// Сохранить данные, необходимые для BX_User_New:
		sTemp.Format("User_New:%lu\n", oc_user.GetObjectID());					sFile += sTemp;
																									
		SaveField(sTemp,  user_args.Login,		"Login");							sFile += sTemp;
		SaveField(sTemp,  user_args.Password,	"Password");						sFile += sTemp;
		SaveField(sTemp,  user_args.Password,	"PasswordConfirm");				sFile += sTemp;
		SaveField(sTemp,  user_args.FullName,	"FullName");						sFile += sTemp;
		SaveField(sTemp,  user_args.Email,		"Email");							sFile += sTemp;

	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
		sFile += FUNCTION_DELIMITER;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Сохранить данные, необходимые для BX_User_PutData:
		sTemp.Format("User_PutData:%lu\n", oc_user.GetObjectID());				sFile += sTemp;

		SaveField(sTemp,  user_args.Password,				"Password");			sFile += sTemp;
		SaveField(sTemp,  user_args.FullName,				"FullName");			sFile += sTemp;
		SaveField(sTemp,  user_args.InterfaceLanguage,	"InterfaceLanguage");sFile += sTemp;
		SaveField(sTemp,  user_args.InterfaceType,		"InterfaceType");		sFile += sTemp;
		SaveField(sTemp,  user_args.Email,					"Email");				sFile += sTemp;
		SaveField(sTemp,  user_args.Phone,					"Phone");				sFile += sTemp;
		SaveField(sTemp,  user_args.Fax,						"Fax");					sFile += sTemp;
		SaveField(sTemp,  user_args.Address,				"Address");				sFile += sTemp;
		SaveField(sTemp,  user_args.URL,						"URL");					sFile += sTemp;
		SaveField(sTemp,  user_args.Comment,				"Comment");				sFile += sTemp;
		SaveField(sTemp,  user_args.TZOffset,				"TZOffset");			sFile += sTemp;
		SaveField(sTemp,  user_args.NotifyFreq,			"NotifyFreq");			sFile += sTemp;
		SaveField(sTemp,  user_args.NotifyHTML,			"NotifyHTML");			sFile += sTemp;
		SaveField(sTemp,  user_args.NotifyDepth,			"NotifyDepth");		sFile += sTemp;
	}

//----------------------------------------------------------------------------[]
// Сохранение сайтов:
	for (oc_site.GoFirst(); oc_site.IsValid(); oc_site.GoNext())
	{
		sFile += OBJECT_DELIMITER;

	// Открыть владельца сайта с целью узнать его пароль:
		BX_CHECK_AND_OPEN(oc_user, oc_site.m_OwnerID, OBJ_CLASS_ID_User);

	// Получить данные о сайте:
		site_args.objID		= oc_site.GetObjectID();
		site_args.objPassword= oc_user.m_Password;
		BX_ASSERT_RETURN(BX_Site_GetData(site_args));

	// Сохранить данные, необходимые для BX_Site_New:
		sTemp.Format("Site_New:%lu\n", oc_site.GetObjectID());					sFile += sTemp;
		SaveField(sTemp,  site_args.OwnerID,			"OwnerID");					sFile += sTemp;		
		SaveField(sTemp,  NA,								"Profile");					sFile += sTemp;		
		SaveField(sTemp,  site_args.Name,				"Name");						sFile += sTemp;		
		SaveField(sTemp,  site_args.objPassword,		"objPassword");			sFile += sTemp;		
		SaveField(sTemp,  site_args.URL,					"URL");						sFile += sTemp;		
		SaveField(sTemp,  NA,								"objFromID");				sFile += sTemp;		
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
		sFile += FUNCTION_DELIMITER;
	//- - - - - - - - - - - - - - - - - - - - - - - - - - -]
	// Сохранить данные, необходимые для BX_Site_PutData:
		sTemp.Format("Site_PutData:%lu\n", oc_site.GetObjectID());				sFile += sTemp;

		SaveField(sTemp,  site_args.objID,						"objID");			sFile += sTemp;
		SaveField(sTemp,  site_args.objPassword,				"objPassword");	sFile += sTemp;
		SaveField(sTemp,  site_args.MirrorInclude,			"MirrorInclude");	sFile += sTemp;
		SaveField(sTemp,  site_args.MirrorExclude,			"MirrorExclude");	sFile += sTemp;
		SaveField(sTemp,  site_args.MirrorSubstr,				"MirrorSubstr");	sFile += sTemp;
		SaveField(sTemp,  site_args.IgnoredIP,					"IgnoredIP");		sFile += sTemp;
		SaveField(sTemp,  site_args.Alias,						"Alias");			sFile += sTemp;
		SaveField(sTemp,  site_args.Name,						"Name");				sFile += sTemp;
		SaveField(sTemp,  site_args.Description,				"Description");	sFile += sTemp;
		SaveField(sTemp,  site_args.URL,							"URL");				sFile += sTemp;
		SaveField(sTemp,  site_args.CounterType,				"CounterType");	sFile += sTemp;
		SaveField(sTemp,  site_args.RateMySite,				"RateMySite");		sFile += sTemp;
		SaveField(sTemp,  site_args.RateStatsViewPassword,	"RateStatsViewPassword");sFile += sTemp;
		SaveField(sTemp,  site_args.ShowAudience,				"ShowAudience");	sFile += sTemp;
		SaveField(sTemp,  NA,										"Profile");			sFile += sTemp;
		SaveField(sTemp,  site_args.Keyword,					"Keyword");			sFile += sTemp;
		SaveField(sTemp,  site_args.Concept,					"Concept");			sFile += sTemp;
		SaveField(sTemp,  site_args.PageName,					"PageName");		sFile += sTemp;
	}

	sFile.WriteFile(BACKUP_FILENAME);

	return BX_OK;
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` BX_Admin_RestoreBXObjects                                                 []                         
//                                                                            []
BX_RESULT BX_Admin_RestoreBXObjects(BX_Admin_Args& /*arg*/)
{
	return BX_OK;
}
//____________________________________________________________________________[]

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` BX_Admin_GetObjectNum                                                     []                     
[]                                                                            []
[]____________________________________________________________________________*/
BX_RESULT
BX_Admin_GetObjectNum(BX_Admin_Args& arg)
{
	arg.Result.Delete();
	string		Str;

	OC_User		oc_user;
	Str.Format("User,%d,", oc_user.GetTotalNum());
	arg.Result += Str;

	OC_Banner		oc_banner;
	Str.Format("Banner,%d,", oc_banner.GetTotalNum());
	arg.Result += Str;

	OC_BannerProfile		oc_bannerprofile;
	Str.Format("BannerProfile,%d,", oc_bannerprofile.GetTotalNum());
	arg.Result += Str;

	OC_Site		oc_site;
	Str.Format("Site,%d,", oc_site.GetTotalNum());
	arg.Result += Str;
	
	OC_ShowEvent		oc_showevent;
	Str.Format("ShowEvent,%d,", oc_showevent.GetTotalNum());
	arg.Result += Str;

//	OC_Viewer		oc_viewer;
	Str.Format("Viewer,%d,", oc_reg.m_Viewers.Size());
	arg.Result += Str;
	
	OC_VBN		oc_vbn;
	Str.Format("VBN,%d,", oc_vbn.GetTotalNum());
	arg.Result += Str;

	OC_Concept		oc_concept;
	Str.Format("Concept,%d,", oc_concept.GetTotalNum());
	arg.Result += Str;

	OC_Keyword		oc_keyword;
	Str.Format("Keyword,%d,", oc_keyword.GetTotalNum());
	arg.Result += Str;

	OC_ModeratorComment		oc_moderatorcomment;
	Str.Format("ModeratorComment,%d,", oc_moderatorcomment.GetTotalNum());
	arg.Result += Str;

	OC_Referrer		oc_referrer;
	Str.Format("Referrer,%d,", oc_referrer.GetTotalNum());
	arg.Result += Str;

	OC_IPRecord		oc_iprecord;
	Str.Format("IPRecord,%d,", oc_iprecord.GetTotalNum());
	arg.Result += Str;

	OC_ViewerReference		oc_viewerreference;
	Str.Format("ViewerReference,%d", oc_viewerreference.GetTotalNum());
	arg.Result += Str;

	return BX_OK;
}
//____________________________________________________________________________[]




/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
