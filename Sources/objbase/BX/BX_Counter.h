/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 1999 TSMC Networks.                                          []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_Counter.h                                              []
[] Date:            17.11.1999                                                []
[] Author:          Alex Vershinin                                            []
[] Description:     Работа со счётчиком                                       []
[] Last Modified:                                                             []
[]____________________________________________________________________________[]
*/                                                                 
#ifndef BX_Counter_H
#define BX_Counter_H

//______________________________________________________________________________
//                                                                            []
//` Counter                                                                   []       
//                                                                            []

struct BX_Counter_Args : public BX_Event_Args 
{
	BX_Counter_Args() {
		JustGetData							= false;
		CounterType							= 0;
		Visits								= 0;
		LastVisitTime						= 0L;
		OnlineVisitors						= 0;
												
		Total_Loads							= 0;
		Total_Visitors						= 0;
		Total_VisitorReturns				= 0;
		Total_AnonymousVisitors			= 0;
		Total_AnonymousVisitors_Prc	= 0;
		Total_VisitorExperience			= 0;
		Ave_VisitorExperience			= 0;
													
		Total_Hosts							= 0;
													
		Total_Hits							= 0;
		OnlineVisitors						= 0;
		Total_AnonymousHits				= 0;
		Total_AnonymousHits_Prc			= 0;
		Total_SuspiciousHits_Prc		= 0;
		Total_SessionTime					= 0;
													
		Total_Shows							= 0;
		Total_Clicks						= 0;
		Total_MouseOver					= 0;
		Total_CTR_Prc						= 0;
													
		Total_Votes							= 0;
		Total_Votes_Sum					= 0;
		Total_Votes_Ave					= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LM_Loads								= 0;
		LM_Visitors							= 0;
   	LM_VisitorReturns					= 0;
   	LM_VisitorReturns_Prc			= 0;
													
   	LM_Hosts								= 0;
													
   	LM_Hits								= 0;
		LM_AnonymousHits					= 0;
		LM_AnonymousHits_Prc				= 0;
		LM_SuspiciousHits_Prc			= 0;
		LM_SessionTime						= 0;
													
		LM_Shows								= 0;
   	LM_Clicks							= 0;
		LM_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LW_Loads								= 0;
		LW_Visitors							= 0;
   	LW_VisitorReturns					= 0;
   	LW_VisitorReturns_Prc			= 0;
													
   	LW_Hosts								= 0;
													
   	LW_Hits								= 0;
		LW_AnonymousHits					= 0;
		LW_AnonymousHits_Prc				= 0;
		LW_SuspiciousHits_Prc			= 0;
		LW_SessionTime						= 0;
													
		LW_Shows								= 0;
   	LW_Clicks							= 0;
		LW_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LD_Loads								= 0;
		LD_Visitors							= 0;
   	LD_VisitorReturns					= 0;
   	LD_VisitorReturns_Prc			= 0;
													
   	LD_Hosts								= 0;
													
		LD_Hits								= 0;
		LD_AnonymousHits					= 0;
		LD_AnonymousHits_Prc				= 0;
		LD_SuspiciousHits_Prc			= 0;
		LD_SessionTime						= 0;
													
		LD_Shows								= 0;
   	LD_Clicks							= 0;
		LD_CTR_Prc							= 0;
//- - - - - - - - - - - - - - - - - - - - - - 
		LH_Loads								= 0;
		LH_Visitors							= 0;
   	LH_VisitorReturns					= 0;
   	LH_VisitorReturns_Prc			= 0;
													
   	LH_Hosts								= 0;
													
		LH_Hits								= 0;
		LH_AnonymousHits					= 0;
		LH_AnonymousHits_Prc				= 0;
		LH_SuspiciousHits_Prc			= 0;
		LH_SessionTime						= 0;
													
		LH_Shows								= 0;
   	LH_Clicks							= 0;
		LH_CTR_Prc							= 0;
//----------------------------------------------------------------------------[] 
	
	}
	bool		JustGetData						;	// Получить значение полей счетчика сайтов без их модификации. На вход нужен только ID сайта.
	int		CounterType						;	// Тип счётчика (по умолчанию - тот, что установлен у сайта).
	int		Visits							;	// Количество хитов, сделанных зрителем на этом сайте.
	time_t	LastVisitTime					;	// Время последнего посещёния данным зрителем этого сайте.
	int		OnlineVisitors					;	// Число уникальных посетителей за последние 3 минуты.
		
	int		Total_Loads							;	//*  Всего загрузок сайта.
	int		Total_Visitors						;	//*  Всего новых посетителей сайта.
	int		Total_VisitorReturns				;	//*  Всего возвратов на сайт.
	int		Total_AnonymousVisitors			;	//   Всего анонимных посетителей сайта.
	int		Total_AnonymousVisitors_Prc	;	//+  Процент анонимных посетителей сайта от общего числа новых посетителей сайта.
	int		Total_VisitorExperience			;	//   Общее количество посещённых сайтов всеми хостами данного сайта.
	int		Ave_VisitorExperience			;	//+  Среднее количество посещённых сайтов для хоста на данном сайте.
														
	int		Total_Hosts							;	//   Всего зрителей сайта за время, меньшее суток.
														
	int		Total_Hits							;	//*  Всего (не подозрительных) хитов сайта.
	int		Total_AnonymousHits				;	//   Всего анонимных посетителей сайта.
	int		Total_AnonymousHits_Prc			;	//*+ Процент анонимных посетителей сайта от общего числа новых посетителей сайта.
	int		Total_SuspiciousHits_Prc		;	//+  Процент подозрительных хитов сайта от общего общего числа хитов на сайте (включая подозрительные).
	int		Total_SessionTime					;	//	  Суммарная продолжительность сессии на сайте.
														
	int		Total_Shows							;	//   Всего показов баннеров на сайте.
	int		Total_Clicks						;	//	  Всего нажатий баннеров на сайте.
	int		Total_MouseOver					;	//   Подведений курсора к баннерам на этом сайте за всё время.
	int		Total_CTR_Prc						;	//*+ CTR баннеров на этом сайте за всё время.
														
	int		Total_Votes							;	//   Всего проголосовавших за сайт.
	int		Total_Votes_Sum					;	//   Суммарная оценка голосования за сайт.
	int		Total_Votes_Ave					;	//+  Средняя оценка голосования за сайт.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LM_Loads								;	//	  Всего загрузок сайта за последний месяц. 
	int		LM_Visitors							;  //   Новых посетителей сайта за последний месяц. 
   int		LM_VisitorReturns					;	//   Возвратов на сайт в течение месяца.
   int		LM_VisitorReturns_Prc			;	//+  Процент возвратившихся в течение месяца посетителей сайта от общего числа посетителей сайта в течение месяца.
														
   int		LM_Hosts								;  //   Хостов на сайте за последний месяц.
														
   int		LM_Hits								;	//   Хитов (не подозрительных) на сайте за последний месяц.  
	int		LM_AnonymousHits					;	//   Анонимных хитов сайта за последний месяц.
	int		LM_AnonymousHits_Prc				;	//+  Процент анонимных хитов сайта за последний месяц от общего числа (не подозрительных) хитов за последний месяц.
	int		LM_SuspiciousHits_Prc			;	//+  Процент подозрительных хитов сайта за последний месяц от общего числа хитов за последний месяц (включая подозрительные).
	int		LM_SessionTime						;	//	  Суммарная продолжительность сессии на сайте за последний месяц.

	int		LM_Shows								;	//	  Показов баннеров на сайте за последний месяц.
   int		LM_Clicks							;  //   Нажатий баннеров на сайте за последний месяц.  
	int		LM_CTR_Prc							;	//+  CTR за последний месяц.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LW_Loads								;	//	  Всего загрузок сайта за последнюю неделю.
	int		LW_Visitors							;	//   Новых посетителей сайта за последнюю неделю.
   int		LW_VisitorReturns					;	//   Возвратов на сайт в течение недели.
   int		LW_VisitorReturns_Prc			;	//+  Процент возвратившихся в течение недели посетителей сайта от общего числа посетителей сайта в течение недели.
														
   int		LW_Hosts								;	//   Хостов на сайте за последнюю неделю.
														
   int		LW_Hits								;	//   Хитов (не подозрительных) на сайте за последнюю неделю.  
	int		LW_AnonymousHits					;	//   Анонимных хитов сайта за последнюю неделю.  
	int		LW_AnonymousHits_Prc				;	//+  Процент анонимных хитов сайта за последнюю неделю от общего числа (не подозрительных) хитов за последнюю неделю.
	int		LW_SuspiciousHits_Prc			;	//+  Процент подозрительных хитов сайта за последнюю неделю от общего числа хитов за последнюю неделю (включая подозрительные).  
	int		LW_SessionTime						;	//	  Суммарная продолжительность сессии на сайте за последнюю неделю.
														
	int		LW_Shows								;	//	  Показов баннеров на сайте за последнюю неделю.
   int		LW_Clicks							;  //   Нажатий баннеров на сайте за последнюю неделю.
	int		LW_CTR_Prc							;	//+  CTR за последнюю неделю.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LD_Loads								;	//	  Всего загрузок сайта за последние сутки.
	int		LD_Visitors							;	//   Новых посетителей сайта за последние сутки.
   int		LD_VisitorReturns					;	//+  Возвратов на сайт в течение суток.  
   int		LD_VisitorReturns_Prc			;	//+  Процент возвратившихся в течение суток посетителей сайта от общего числа посетителей сайта в течение суток.
														
   int		LD_Hosts								;	//   Хостов на сайте за последние сутки.
														
	int		LD_Hits								;	//   Хитов (не подозрительных) на сайте за последние сутки.
	int		LD_AnonymousHits					;	//   Анонимных хитов сайта за последние сутки.
	int		LD_AnonymousHits_Prc				;	//+  Процент анонимных хитов сайта за последние сутки от общего числа (не подозрительных) хитов за последние сутки.
	int		LD_SuspiciousHits_Prc			;	//+  Процент подозрительных хитов сайта за последние сутки от общего числа хитов за последние сутки (включая подозрительные).
	int		LD_SessionTime						;	//	  Суммарная продолжительность сессии на сайте за последний день.
														
	int		LD_Shows								;	//	  Показов баннеров на сайте за последние сутки.
   int		LD_Clicks							;	//   Нажатий баннеров на сайте за последние сутки.
	int		LD_CTR_Prc							;	//+  CTR за последние сутки.
//- - - - - - - - - - - - - - - - - - - - - - 
	int		LH_Loads								;	//	  Всего загрузок сайта за последний час. 
	int		LH_Visitors							;	//   Новых посетителей сайта за последний час. 
   int		LH_VisitorReturns					;  //   Возвратов на сайт в течение часа.  
   int		LH_VisitorReturns_Prc			;	//+  Процент возвратившихся в течение часа посетителей сайта от общего числа посетителей сайта в течение часа.
														
   int		LH_Hosts								;	//   Хостов на сайте за последний час.
														
	int		LH_Hits								;  //   Хитов (не подозрительных) на сайте за последний час.
	int		LH_AnonymousHits					;	//   Анонимных хитов сайта за последний час.
	int		LH_AnonymousHits_Prc				;	//+  Процент анонимных хитов сайта за последний час от общего числа (не подозрительных) хитов за последний час.
	int		LH_SuspiciousHits_Prc			;	// + Процент подозрительных хитов сайта за последний час от общего числа хитов за последний час (включая подозрительные).
	int		LH_SessionTime						;	//	  Суммарная продолжительность сессии на сайте за последний час.
														
	int		LH_Shows								;	//	  Показов баннеров на сайте за последние сутки.
   int		LH_Clicks							;  //   Нажатий баннеров на сайте за последний час.
	int		LH_CTR_Prc							;	//	+ CTR за последние сутки.
//----------------------------------------------------------------------------[] 
	


};
//----------------------------------------------------------------------------[] 

// Возвращает статистическую информацию для показа счётчика.
BX_RESULT BX_Counter_GetData(BX_Counter_Args& arg);
//____________________________________________________________________________[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/