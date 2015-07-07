/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'BX'                                         []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            URL.h                                                     []
[] Date:            31.03.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                         
#ifndef URL_H
#define URL_H

//______________________________________________________________________________
//                                                                            []
// Разборщик адресов протокола http															[]
//                                                                            []
class HTTP_URL
{

private:

	char m_login		[MAX_URL_SIZE];
	char m_password	[MAX_URL_SIZE];
	char m_domain		[MAX_URL_SIZE];
	char m_port			[MAX_URL_SIZE];
	char m_path			[MAX_URL_SIZE];
	char m_file			[MAX_URL_SIZE];
	char m_ext			[MAX_URL_SIZE];
	char m_args			[MAX_URL_SIZE];
	//----------------------------------------------------------------------------[] 

	void Init ();

public:

	HTTP_URL ();

	HTTP_URL (const char * sURL);

	void CopyFrom (const HTTP_URL& from);

	HTTP_URL (const HTTP_URL& from);

	HTTP_URL& operator = (const HTTP_URL& from);

	bool operator == (const HTTP_URL& to);

	bool IsChildFor (const HTTP_URL& Parent);

	void Domain (string& str);

	void Path (string& str);

	void Args (string& str);

	void DomainPath (string& str);

	void DomainPathFile (string& str);

	void DomainPathFileExt (string& str);

	void DomainPathFileExtArgs (string& str);

// Собирает полный адрес
	void URL (string& str);

	void DebugPrint ();

//  http://login:password @ domain /path/file.ext?args
	void Parse (const char * _sURL);

};
//____________________________________________________________________________[]



#endif   // end of URL_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/