/*
_____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'ZOOB/Intertek'									[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  problem_ini.cpp														[]
[] Date: 			  28.06.2000															[]
[] Author:			  Roman V. Koshelev													[]
[] Description:	  ���������������� ������ ������� 								[]
[]_________________________________________________________________________[]
*/

#define USES_MOD_User
#define USES_MOD_UserGroup
#define USES_MOD_InfoSource

#include "include.h"


//______________________________________________________________________________
//                                                                            []
//` ������ ���� �������������                                                 []                         
//                                                                            []
GROUP_INI GROUP_INI_ARR[] = 
{
// ���������
	{"��������",
	 "intertek.ru/analyst",
	 "�������� � ���������� ������������� � �������� ����������",
	 "Concept.Feod.Data.Type.������									[LRCW]"
	 "Concept.Feod.Data.Topic											[LRCW]"
	 "Concept.Feod.Data.Service.Tasks								[LRD]"
	 "Concept.Feod.Data.Service.Drafts								[LRCW]"
	 "Concept.Feod.Data.Mark.Regular									[LRCW]"
	 "Concept.Feod.Aux													[LR]"
	},

// ����������
	{"��������� ���� ���������� ������ '���'",
	 "intertek.ru/newsmaker",
	 "���������� ��������� ���������� ��� ���� ���������� ������ '���'",
	 "Concept.Feod.Data.Type.News										[LRC]"
	 "Concept.Feod.Data.Topic.���										[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },																		
																				
	{"��������� ������� '������ ���'",
	 "intertek.ru/newsmaker",											
	 "���������� ������� ���",											
	 "Concept.Feod.Data.Type.������ ���								[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },

	{"��������� ������� '������� ��������'",
	 "intertek.ru/newsmaker",
	 "���������� �������� �� ���������",
	 "Concept.Feod.Data.Type.������� ��������						[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },																		
																				
	{"��������� ������� '������� �����'",
	 "intertek.ru/newsmaker",											
	 "���������� �������� �� ���������",							
	 "Concept.Feod.Data.Type.������� �����							[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 },

// �������������
	{"�������� ���� ���������� ������ '���'",
	 "intertek.ru/subeditor",
	 "��������, �������������� � ���������� ��� ���������� �������������� ��������� ���������� ���� ���������� ������ '���'.",
	 "Concept.Feod.Data.Type.News										[LRW]"
	 "Concept.Feod.Data.Topic.���										[LRW]"
	 "Concept.Feod.Data.Service.Drafts								[LRCWD]"
	 "Concept.Feod.Data.Service.Public								[LRCWD]"
	 "Concept.Feod.Data.Service.Forbidden							[LRCWD]"
	 "Concept.Feod.Aux													[LR]"
	 "Concept.Feod.Data.Mark.Regular									[LRCW]"
	},

// ���������
	{"�������� ������ '���'",
	 "intertek.ru/editor",
	 "������ �������������� ����������, �������� �� � ������ ��������� ������ '���', ���������� ���������.",
	 "Concept.Feod.Data.Type.News										[LRCWD]"
	 "Concept.Feod.Data.Topic.���										[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"�������� ������� '������ ���'",
	 "intertek.ru/editor",
	 "��������������, ���������� � ���������� ������� ���.",
	 "Concept.Feod.Data.Type.������ ���								[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"�������� ������� '������� ��������'",
	 "intertek.ru/editor",
	 "��������������, ���������� � ���������� �������� ��������.",
	 "Concept.Feod.Data.Type.������� ��������						[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"�������� ������� '������� �����'",
	 "intertek.ru/editor",
	 "��������������, ���������� � ���������� �������� ��������.",
	 "Concept.Feod.Data.Type.������� �����							[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"�������� ������� '������'",
	 "intertek.ru/editor",
	 "��������������, ���������� � ���������� ����������, ��������� ����������� (������).",
	 "Concept.Feod.Data.Type.������									[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},	

// ������������� ��������
	{"������������� ��������",
	 "intertek.ru/chiefeditor",
	 "����������� �������� �������, ������ ����������, �������� ������, ������������ ������� �� ���������, ��������� ��������� ��������.",
	 "Concept.Feod.Data.Type		[LRCWDM]"
	 "Concept.Feod.Data.Topic		[LRCWDM]"
	 "Concept.Feod.Data.Service	[LRCWD]"
	 "Concept.Feod.Data.Mark		[LRCWDM]"
	 "Concept.Feod.Aux				[LRCWD]"
	}
};
int GROUP_INI_NUM = 0; //sizeof (GROUP_INI_ARR)/sizeof (GROUP_INI_ARR[0]);
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` ������������                                                              []            
//                                                                            []
USER_INI USER_INI_ARR[]=
{
// ���������
	{"analyst",				"123",		"������ ���������",		"horosho@beznalo.gov",		"��������"														},

// ����������
	{"newsmaker_prom",	"123",		"���� ��������",			"Maria@sisek.net",			"��������� ���� ���������� ������ '���'"				},
	{"newsmaker_smi",		"123",		"���� �������",			"one@inbox.com",				"��������� ������� '������ ���'"							},
	{"newsmaker_com",		"123",		"ϸ�� �������",			"two@inbox.com",				"��������� ������� '������� ��������'"					},
	{"newsmaker_site",	"123",		"������� �������",		"three@inbox.com",			"��������� ������� '������� �����'"						},

// ������������
	{"subeditor_prom",	"123",		"���� ������",				"keller@dantes.fr",			"�������� ���� ���������� ������ '���'"				},

// ���������
	{"editor_prom",		"123",		"������� �����������",	"Head@golova.gov",			"�������� ������ '���'"										},		
	{"editor_smi",			"123",		"����� ���������",		"mike@dubrovsky.il",			"�������� ������� '������ ���'"							},
	{"editor_com",			"123",		"����� ������",			"Taras@halyava.ru",			"�������� ������� '������� ��������'"					},
	{"editor_site",		"123",		"����� �����-������",	"hueva_zalupa@mail.ru",		"�������� ������� '������� �����'"						},
	{"editor_st",			"123",		"����� �����-������",	"hueva_zalupa@mail.ru",		"�������� ������� '������'"								},

// ������������� ��������
	{"chief",				"123",		"������ ��������� �����","serg@want.mamba.too",		"������������� ��������"									},

// ��������
	{"designer",			"123",		"���� ������",				"Vasya@pupkin.ru",			"�������� �����"												},

// ����������� web-�������
	{"websmith",			"123",		"������� ��������",		"AV@4me.ru",					"����������� web-�������"									},

// �������������
	{"admin",				"123",		"�������� ����������� �����-��������","death@smerti.net",	"�������������"}
};
int USER_INI_NUM = 0; // sizeof (USER_INI_ARR)/sizeof (USER_INI_ARR[0]);
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` ��������� �����������																		[]
//                                                                            []
INFOSOURCE_INI INFOSOURCE_INI_ARR[] = 
{
	{"�������� ������� '������'",									"��������",		"URL",	1,		"Concept.Feod.Data.Content.������"							},

	{"�������� ������� '���'",										"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���"						},
	{"�������� ������� '���.������'",							"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.������"				},
	{"�������� ������� '���.�����'",								"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.�����"				},
	{"�������� ������� '���.���'",								"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.���"					},
	{"�������� ������� '���.�����'",								"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.�����"				},
	{"�������� ������� '���.����������'",						"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.����������"			},
	{"�������� ������� '���.������� � ����'",					"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.���.������� � ����"	},
	{"�������� ������� '��������'",								"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.��������"					},
	{"�������� ������� '��������.��������'",					"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.��������.��������"		},
	{"�������� ������� '��������.���������'",					"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.��������.���������"	},
	{"�������� ������� '��������.�����'",						"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.��������.�����"			},
	{"�������� ������� '��������.�� �������'",				"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.��������.�� �������"	},

	{"�������� ������� '������ ���'",							"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.������ ���"				},
	{"�������� ������� '������� ��������'",					"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.������� ��������"		},
	{"�������� ������� '������� �����'",						"��������",		"URL",	1,		"Concept.Feod.Data.Content.News.������� �����"			}
};
int INFOSOURCE_INI_NUM = 0; //sizeof (INFOSOURCE_INI_ARR)/sizeof (INFOSOURCE_INI_ARR[0]);
//____________________________________________________________________________[]







/*______________________________________________________________________________
[] 																									[]
[] 																									[]
[] END OF FILE 																					[]
[] 																									[]
[]____________________________________________________________________________[]
*/

