/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'bcc'                                        []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            UserAgent.h                                               []
[] Date:            31.03.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Разборщик USER_AGENT                                      []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                
#ifndef UserAgent_H
#define UserAgent_H

//______________________________________________________________________________
//                                                                            []
//` Разборщик USER_AGENT                                                      []
//                                                                            []
#define USER_AGENT_MAX_LEN 1024


class USER_AGENT
{

private:

	char m_Browser					[USER_AGENT_MAX_LEN];
	char m_Browser_ver			[USER_AGENT_MAX_LEN];
	char m_OperatingSystem		[USER_AGENT_MAX_LEN];
	char m_OperatingSystem_ver	[USER_AGENT_MAX_LEN];

	void Init ();

public:
	USER_AGENT ();

	USER_AGENT (const char * sUSER_AGENT);

	USER_AGENT (const string& sUSER_AGENT);

	void CopyFrom (const USER_AGENT& from);

	USER_AGENT (const USER_AGENT& from);

	USER_AGENT& operator = (const USER_AGENT& from);

	void DebugPrint ();

	void UserAgent (string& str);

	void OperatingSystem (string& str);

	void OperatingSystemVer (string& str);

	void Browser (string& str);

	void BrowserVer (string& str);

	void Parse (const char * _sUSER_AGENT);	
};
//____________________________________________________________________________[]



#endif   // end of UserAgent_H
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/