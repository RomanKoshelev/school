/*
_____________________________________________________________________________
[] 																								[]
[] This is a part of the PROJECT: 'ZOOB/Intertek'									[]
[] ________________________________________________________________________[]
[]																									[]
[] Name: 			  problem_ini.cpp														[]
[] Date: 			  28.06.2000															[]
[] Author:			  Roman V. Koshelev													[]
[] Description:	  Инициализирующие данные проекта 								[]
[]_________________________________________________________________________[]
*/

#define USES_MOD_User
#define USES_MOD_UserGroup
#define USES_MOD_InfoSource

#include "include.h"


//______________________________________________________________________________
//                                                                            []
//` ГРУППЫ ПРАВ ПОЛЬЗОВАТЕЛЕЙ                                                 []                         
//                                                                            []
GROUP_INI GROUP_INI_ARR[] = 
{
// Аналитики
	{"Аналитик",
	 "intertek.ru/analyst",
	 "Создание и публикация аналитических и обзорных материалов",
	 "Concept.Feod.Data.Type.Статьи									[LRCW]"
	 "Concept.Feod.Data.Topic											[LRCW]"
	 "Concept.Feod.Data.Service.Tasks								[LRD]"
	 "Concept.Feod.Data.Service.Drafts								[LRCW]"
	 "Concept.Feod.Data.Mark.Regular									[LRCW]"
	 "Concept.Feod.Aux													[LR]"
	},

// Сотрудники
	{"Сотрудник всех подканалов канала 'ТЭК'",
	 "intertek.ru/newsmaker",
	 "Подготовка новостных материалов для всех подканалов канала 'ТЭК'",
	 "Concept.Feod.Data.Type.News										[LRC]"
	 "Concept.Feod.Data.Topic.ТЭК										[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },																		
																				
	{"Сотрудник раздела 'Анонсы СМИ'",
	 "intertek.ru/newsmaker",											
	 "Подготовка анонсов СМИ",											
	 "Concept.Feod.Data.Type.Анонсы СМИ								[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },

	{"Сотрудник раздела 'Новости компаний'",
	 "intertek.ru/newsmaker",
	 "Подготовка новостей по компаниям",
	 "Concept.Feod.Data.Type.Новости компаний						[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 },																		
																				
	{"Сотрудник раздела 'Новости сайта'",
	 "intertek.ru/newsmaker",											
	 "Подготовка новостей по компаниям",							
	 "Concept.Feod.Data.Type.Новости сайта							[LRC]"
	 "Concept.Feod.Data.Topic											[LRC]"
	 "Concept.Feod.Data.Service.Drafts								[LRC]"
	 "Concept.Feod.Aux													[LR]"
	 "Concept.Feod.Data.Mark.Regular									[LRC]"
	 },

// Подредакторры
	{"Редактор всех подканалов канала 'ТЭК'",
	 "intertek.ru/subeditor",
	 "Просмотр, редактирование и публикация или запрещение подготовленных новостных материалов всех подканалов канала 'ТЭК'.",
	 "Concept.Feod.Data.Type.News										[LRW]"
	 "Concept.Feod.Data.Topic.ТЭК										[LRW]"
	 "Concept.Feod.Data.Service.Drafts								[LRCWD]"
	 "Concept.Feod.Data.Service.Public								[LRCWD]"
	 "Concept.Feod.Data.Service.Forbidden							[LRCWD]"
	 "Concept.Feod.Aux													[LR]"
	 "Concept.Feod.Data.Mark.Regular									[LRCW]"
	},

// Редакторы
	{"Редактор канала 'ТЭК'",
	 "intertek.ru/editor",
	 "Анализ опубликованных материалов, переброс их в другие подканалы канала 'ТЭК', назначение признаков.",
	 "Concept.Feod.Data.Type.News										[LRCWD]"
	 "Concept.Feod.Data.Topic.ТЭК										[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"Редактор раздела 'Анонсы СМИ'",
	 "intertek.ru/editor",
	 "Редактирование, публикация и запрещение анонсов СМИ.",
	 "Concept.Feod.Data.Type.Анонсы СМИ								[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"Редактор раздела 'Новости компаний'",
	 "intertek.ru/editor",
	 "Редактирование, публикация и запрещение новостей компаний.",
	 "Concept.Feod.Data.Type.Новости компаний						[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"Редактор раздела 'Новости сайта'",
	 "intertek.ru/editor",
	 "Редактирование, публикация и запрещение новостей компаний.",
	 "Concept.Feod.Data.Type.Новости сайта							[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},

	{"Редактор раздела 'Статьи'",
	 "intertek.ru/editor",
	 "Редактирование, публикация и запрещение материалов, созданных аналитиками (статей).",
	 "Concept.Feod.Data.Type.Статьи									[LRCWD]"
	 "Concept.Feod.Data.Topic											[LRCWD]"
	 "Concept.Feod.Data.Service										[LRCWD]"
	 "Concept.Feod.Data.Mark											[LRCWD]"
	 "Concept.Feod.Aux													[LRCW]"
	},	

// Ответственный редактор
	{"Ответственный редактор",
	 "intertek.ru/chiefeditor",
	 "Определение политики издания, анализ статистики, контроль работы, формирование заданий на материалы, изменение структуры разделов.",
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
//` ПОЛЬЗОВАТЕЛИ                                                              []            
//                                                                            []
USER_INI USER_INI_ARR[]=
{
// Аналитики
	{"analyst",				"123",		"Витька Охламонов",		"horosho@beznalo.gov",		"Аналитик"														},

// Сотрудники
	{"newsmaker_prom",	"123",		"Маша Сиськина",			"Maria@sisek.net",			"Сотрудник всех подканалов канала 'ТЭК'"				},
	{"newsmaker_smi",		"123",		"Иван Ларьцов",			"one@inbox.com",				"Сотрудник раздела 'Анонсы СМИ'"							},
	{"newsmaker_com",		"123",		"Пётр Ларьцов",			"two@inbox.com",				"Сотрудник раздела 'Новости компаний'"					},
	{"newsmaker_site",	"123",		"Василий Ларьцов",		"three@inbox.com",			"Сотрудник раздела 'Новости сайта'"						},

// Подредакторы
	{"subeditor_prom",	"123",		"Саша Пушкин",				"keller@dantes.fr",			"Редактор всех подканалов канала 'ТЭК'"				},

// Редакторы
	{"editor_prom",		"123",		"Николай Безбашенный",	"Head@golova.gov",			"Редактор канала 'ТЭК'"										},		
	{"editor_smi",			"123",		"Мойша Гейлекман",		"mike@dubrovsky.il",			"Редактор раздела 'Анонсы СМИ'"							},
	{"editor_com",			"123",		"Тарас Халява",			"Taras@halyava.ru",			"Редактор раздела 'Новости компаний'"					},
	{"editor_site",		"123",		"Ольга Зуева-Халупа",	"hueva_zalupa@mail.ru",		"Редактор раздела 'Новости сайта'"						},
	{"editor_st",			"123",		"Ольга Зуева-Халупа",	"hueva_zalupa@mail.ru",		"Редактор раздела 'Статьи'"								},

// Ответственный редактор
	{"chief",				"123",		"Сергей Сергеевич Мамба","serg@want.mamba.too",		"Ответственный редактор"									},

// Дизайнер
	{"designer",			"123",		"Вася Пупкин",				"Vasya@pupkin.ru",			"Дизайнер сайта"												},

// Программист web-страниц
	{"websmith",			"123",		"Алексей Вершинин",		"AV@4me.ru",					"Программист web-страниц"									},

// Администратор
	{"admin",				"123",		"Товладор Евлампиевич Тобой-Убиенный","death@smerti.net",	"Администратор"}
};
int USER_INI_NUM = 0; // sizeof (USER_INI_ARR)/sizeof (USER_INI_ARR[0]);
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` ИСТОЧНИКИ ИНФОРМАЦИИИ																		[]
//                                                                            []
INFOSOURCE_INI INFOSOURCE_INI_ARR[] = 
{
	{"Источник раздела 'Статьи'",									"Описание",		"URL",	1,		"Concept.Feod.Data.Content.Статьи"							},

	{"Источник раздела 'ТЭК'",										"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК"						},
	{"Источник раздела 'ТЭК.Власть'",							"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Власть"				},
	{"Источник раздела 'ТЭК.Нефть'",								"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Нефть"				},
	{"Источник раздела 'ТЭК.Газ'",								"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Газ"					},
	{"Источник раздела 'ТЭК.Уголь'",								"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Уголь"				},
	{"Источник раздела 'ТЭК.Энергетика'",						"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Энергетика"			},
	{"Источник раздела 'ТЭК.Сегодня в мире'",					"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.ТЭК.Сегодня в мире"	},
	{"Источник раздела 'Общество'",								"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Общество"					},
	{"Источник раздела 'Общество.Политика'",					"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Общество.Политика"		},
	{"Источник раздела 'Общество.Экономика'",					"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Общество.Экономика"	},
	{"Источник раздела 'Общество.Жизнь'",						"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Общество.Жизнь"			},
	{"Источник раздела 'Общество.За рубежом'",				"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Общество.За рубежом"	},

	{"Источник раздела 'Анонсы СМИ'",							"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Анонсы СМИ"				},
	{"Источник раздела 'Новости компаний'",					"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Новости компаний"		},
	{"Источник раздела 'Новости сайта'",						"Описание",		"URL",	1,		"Concept.Feod.Data.Content.News.Новости сайта"			}
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

