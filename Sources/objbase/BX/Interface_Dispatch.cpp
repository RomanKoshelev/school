/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Interface_Dispatch.cpp                                    []
[] Date:            NA                                                        []
[] Author:          Alex Vershinin, Roman V. Koshelev                         []
[] Description:     Диспетчер для вызова оболочек прикладных функций.         []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Interface.h-file   []
[]____________________________________________________________________________*/

#define	USES_OBServer_Interface_h
#define	USES_BX_Interface
#include	"BX.h"


//______________________________________________________________________________
//                                                                            []
// Диспетчер вызовов прикладных фунций                                        []
//                                                                            []
void OBServer_Interface (const char* OBServer_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)
{
// Поиск зарегистрированной функции
   FNC_BEGIN;
   {
   // Counter
      FNC        (BX_Counter_GetData, "Возвращает статистическую информацию для показа счётчика.");
			FNC_IN  (BX_Counter, JustGetData, "Получить значение полей счетчика сайтов без их модификации. На вход нужен только ID сайта.");
			FNC_IN  (BX_Counter, SiteID, "{class:Site}ID сайта.");
			FNC_IN  (BX_Counter, Alias, "Синоним ID сайта.");
			FNC_IN  (BX_Counter, CounterType, "Тип счётчика (по умолчанию - тот, что установлен у сайта).");
			FNC_IN  (BX_Counter, PageNo, "Номер страницы сайта.");
			FNC_IN  (BX_Counter, CookieSupported, "Поддерживается ли Cookie.");
			FNC_IN  (BX_Counter, ViewerID, "{class:Viewer}Cookie (ID) зрителя, если Cookie поддерживается и установлен, или NA в противном случае.");
			FNC_IN  (BX_Counter, LocalTime, "Местное время посетителя.");
			FNC_IN  (BX_Counter, ViewerIP, "IP зрителя.");
			FNC_IN  (BX_Counter, SiteURL, "URL сайта, на котором произошло событие (HTTP_REFERER).");
			FNC_IN  (BX_Counter, Referrer, "Предыдущий URL (doсument.referrer на Javascript'е.");
			FNC_IN  (BX_Counter, ViewerHostName, "Хост посетителя.");
			FNC_IN  (BX_Counter, UserAgent, "UserAgent посетителя.");
			FNC_IN  (BX_Counter, ScreenResolution, "Разрешение экрана.");
			FNC_IN  (BX_Counter, ColorDepth, "Глубина цвета.");
			FNC_IN  (BX_Counter, JavaEnabled, "Включена ли Ява-машина.");
			FNC_IN  (BX_Counter, JavaScriptVersion, "Версия ЯваСкрипта.");
			FNC_IN  (BX_Counter, Charset, "CHARSET");
			FNC_IN  (BX_Counter, Language, "HTTP_ACCEPT_LANGUAGE");
			FNC_OUT (BX_Counter, ViewerID, "Cookie (ID) зрителя, который нужно установить.");
			FNC_OUT (BX_Counter, ExitCode, "Код возврата: -1 - неопределён, 0 - хит легальный, 1 - накрутка (<5 сек), 2 - несовпадение с зеркалом, 3 - ignored IP, 4 - сайт запрещён модератором, 5 - хит легальный, но передан несуществующий Cookie.");
			FNC_OUT (BX_Counter, Visits, "Количество хитов, сделанных зрителем на этом сайте.");
			FNC_OUT (BX_Counter, LastVisitTime, "Время последнего посещёния данным зрителем этого сайте.");
			FNC_OUT (BX_Counter, OnlineVisitors, "Число уникальных посетителей за последние 3 минуты.");
			FNC_OUT (BX_Counter, Total_Loads, "Всего загрузок сайта.");
			FNC_OUT (BX_Counter, Total_Visitors, "Всего новых посетителей сайта.");
			FNC_OUT (BX_Counter, Total_VisitorReturns, "Всего возвратов на сайт.");
			FNC_OUT (BX_Counter, Total_AnonymousVisitors, "Всего анонимных посетителей сайта.");
			FNC_OUT (BX_Counter, Total_AnonymousVisitors_Prc, "Процент анонимных посетителей сайта от общего числа новых посетителей сайта.");
			FNC_OUT (BX_Counter, Total_VisitorExperience, "Общее количество посещённых сайтов всеми хостами данного сайта.");
			FNC_OUT (BX_Counter, Ave_VisitorExperience, "Среднее количество посещённых сайтов для хоста на данном сайте.");
			FNC_OUT (BX_Counter, Total_Hosts, "Всего зрителей сайта за время, меньшее суток.");
			FNC_OUT (BX_Counter, Total_Hits, "Всего (не подозрительных) хитов сайта.");
			FNC_OUT (BX_Counter, Total_AnonymousHits, "Всего анонимных посетителей сайта.");
			FNC_OUT (BX_Counter, Total_AnonymousHits_Prc, "Процент анонимных посетителей сайта от общего числа новых посетителей сайта.");
			FNC_OUT (BX_Counter, Total_SuspiciousHits_Prc, "Процент подозрительных хитов сайта от общего общего числа хитов на сайте (включая подозрительные).");
			FNC_OUT (BX_Counter, Total_SessionTime, "Суммарная продолжительность сессии на сайте.");
			FNC_OUT (BX_Counter, Total_Shows, "Всего показов баннеров на сайте.");
			FNC_OUT (BX_Counter, Total_Clicks, "Всего нажатий баннеров на сайте.");
			FNC_OUT (BX_Counter, Total_CTR_Prc, "CTR баннеров на этом сайте за всё время.");
			FNC_OUT (BX_Counter, Total_Votes, "Всего проголосовавших за сайт.");
			FNC_OUT (BX_Counter, Total_Votes_Sum, "Суммарная оценка голосования за сайт.");
			FNC_OUT (BX_Counter, Total_Votes_Ave, "Средняя оценка голосования за сайт.");
			FNC_OUT (BX_Counter, LM_Loads, "Всего загрузок сайта за последний месяц.");
			FNC_OUT (BX_Counter, LM_Visitors, "Новых посетителей сайта за последний месяц.");
			FNC_OUT (BX_Counter, LM_VisitorReturns, "Возвратов на сайт в течение месяца.");
			FNC_OUT (BX_Counter, LM_VisitorReturns_Prc, "Процент возвратившихся в течение месяца посетителей сайта от общего числа посетителей сайта в течение месяца.");
			FNC_OUT (BX_Counter, LM_Hosts, "Хостов на сайте за последний месяц.");
			FNC_OUT (BX_Counter, LM_Hits, "Хитов (не подозрительных) на сайте за последний месяц.");
			FNC_OUT (BX_Counter, LM_AnonymousHits, "Анонимных хитов сайта за последний месяц.");
			FNC_OUT (BX_Counter, LM_AnonymousHits_Prc, "Процент анонимных хитов сайта за последний месяц от общего числа (не подозрительных) хитов за последний месяц.");
			FNC_OUT (BX_Counter, LM_SuspiciousHits_Prc, "Процент подозрительных хитов сайта за последний месяц от общего числа хитов за последний месяц (включая подозрительные).");
			FNC_OUT (BX_Counter, LM_SessionTime, "Суммарная продолжительность сессии на сайте за последний месяц.");
			FNC_OUT (BX_Counter, LM_Shows, "Показов баннеров на сайте за последний месяц.");
			FNC_OUT (BX_Counter, LM_Clicks, "Нажатий баннеров на сайте за последний месяц.");
			FNC_OUT (BX_Counter, LM_CTR_Prc, "CTR за последний месяц.");
			FNC_OUT (BX_Counter, LW_Loads, "Всего загрузок сайта за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_Visitors, "Новых посетителей сайта за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_VisitorReturns, "Возвратов на сайт в течение недели.");
			FNC_OUT (BX_Counter, LW_VisitorReturns_Prc, "Процент возвратившихся в течение недели посетителей сайта от общего числа посетителей сайта в течение недели.");
			FNC_OUT (BX_Counter, LW_Hosts, "Хостов на сайте за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_Hits, "Хитов (не подозрительных) на сайте за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_AnonymousHits, "Анонимных хитов сайта за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_AnonymousHits_Prc, "Процент анонимных хитов сайта за последнюю неделю от общего числа (не подозрительных) хитов за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_SuspiciousHits_Prc, "Процент подозрительных хитов сайта за последнюю неделю от общего числа хитов за последнюю неделю (включая подозрительные).");
			FNC_OUT (BX_Counter, LW_SessionTime, "Суммарная продолжительность сессии на сайте за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_Shows, "Показов баннеров на сайте за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_Clicks, "Нажатий баннеров на сайте за последнюю неделю.");
			FNC_OUT (BX_Counter, LW_CTR_Prc, "CTR за последнюю неделю.");
			FNC_OUT (BX_Counter, LD_Loads, "Всего загрузок сайта за последние сутки.");
			FNC_OUT (BX_Counter, LD_Visitors, "Новых посетителей сайта за последние сутки.");
			FNC_OUT (BX_Counter, LD_VisitorReturns, "Возвратов на сайт в течение суток.");
			FNC_OUT (BX_Counter, LD_VisitorReturns_Prc, "Процент возвратившихся в течение суток посетителей сайта от общего числа посетителей сайта в течение суток.");
			FNC_OUT (BX_Counter, LD_Hosts, "Хостов на сайте за последние сутки.");
			FNC_OUT (BX_Counter, LD_Hits, "Хитов (не подозрительных) на сайте за последние сутки.");
			FNC_OUT (BX_Counter, LD_AnonymousHits, "Анонимных хитов сайта за последние сутки.");
			FNC_OUT (BX_Counter, LD_AnonymousHits_Prc, "Процент анонимных хитов сайта за последние сутки от общего числа (не подозрительных) хитов за последние сутки.");
			FNC_OUT (BX_Counter, LD_SuspiciousHits_Prc, "Процент подозрительных хитов сайта за последние сутки от общего числа хитов за последние сутки (включая подозрительные).");
			FNC_OUT (BX_Counter, LD_SessionTime, "Суммарная продолжительность сессии на сайте за последний день.");
			FNC_OUT (BX_Counter, LD_Shows, "Показов баннеров на сайте за последние сутки.");
			FNC_OUT (BX_Counter, LD_Clicks, "Нажатий баннеров на сайте за последние сутки.");
			FNC_OUT (BX_Counter, LD_CTR_Prc, "CTR за последние сутки.");
			FNC_OUT (BX_Counter, LH_Loads, "Всего загрузок сайта за последний час.");
			FNC_OUT (BX_Counter, LH_Visitors, "Новых посетителей сайта за последний час.");
			FNC_OUT (BX_Counter, LH_VisitorReturns, "Возвратов на сайт в течение часа.");
			FNC_OUT (BX_Counter, LH_VisitorReturns_Prc, "Процент возвратившихся в течение часа посетителей сайта от общего числа посетителей сайта в течение часа.");
			FNC_OUT (BX_Counter, LH_Hosts, "Хостов на сайте за последний час.");
			FNC_OUT (BX_Counter, LH_Hits, "Хитов (не подозрительных) на сайте за последний час.");
			FNC_OUT (BX_Counter, LH_AnonymousHits, "Анонимных хитов сайта за последний час.");
			FNC_OUT (BX_Counter, LH_AnonymousHits_Prc, "Процент анонимных хитов сайта за последний час от общего числа (не подозрительных) хитов за последний час.");
			FNC_OUT (BX_Counter, LH_SuspiciousHits_Prc, "Процент подозрительных хитов сайта за последний час от общего числа хитов за последний час (включая подозрительные).");
			FNC_OUT (BX_Counter, LH_SessionTime, "Суммарная продолжительность сессии на сайте за последний час.");
			FNC_OUT (BX_Counter, LH_Shows, "Показов баннеров на сайте за последние сутки.");
			FNC_OUT (BX_Counter, LH_Clicks, "Нажатий баннеров на сайте за последний час.");
			FNC_OUT (BX_Counter, LH_CTR_Prc, "CTR за последние сутки.");

   // TimeStats
      FNC        (BX_TimeStats_GetStatInfo, "Получение координат для вывода графика счётчика сайта за последние 24 часа.");
			FNC_IN  (BX_TimeStats, Site, "Идентификатор сайта.");
			FNC_IN  (BX_TimeStats, StatsName, "Название счётчика (Visitors,Hosts,Shows,Clicks,Hits,AnonymousHits,SuspiciousHits).");
			FNC_OUT (BX_TimeStats, XLabel, "X-координаты.");
			FNC_OUT (BX_TimeStats, YValue, "Y-координаты.");
			FNC_OUT (BX_TimeStats, YMax, "Максимальное значение Y-координаты.");
			FNC_OUT (BX_TimeStats, YMin, "Минимальное значение Y-координаты.");
			FNC_OUT (BX_TimeStats, VisitorsOnline, "Число посетителей за последние 3 минуты.");

   // Admin
      FNC        (BX_Admin_GetObjectNum, "Получить кол-во экземпляров объектов в базе данных.");
			FNC_OUT (BX_Admin, Result, "Информация по объектам, разделенная запятыми.");

   // Concept
      FNC        (BX_Concept_SetFilter, "Установить фильтрующиеся типы концептов для зрителя.");
			FNC_IN  (BX_Concept, ConceptType, "Типы концептов, подлежащих фильтрации перед копированием от сайта к зрителю.");
			FNC_OUT (BX_Concept, ConceptType, "Типы концептов, успешно установленных в фильтр.");
      FNC        (BX_Concept_GetFilter, "Получить фильтрующиеся типы концептов для зрителя.");
			FNC_OUT (BX_Concept, ConceptType, "Типы концептов, подлежащих фильтрации перед копированием от сайта к зрителю.");

   // SiteStats
      FNC        (BX_SiteStats_Referrer, "Возвращает информацию о реферерах.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}Идентификатор сайта.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "Пароль владельца информации.");
			FNC_IN  (BX_SiteStats, StatsPassword, "Пароль на доступ к статистике.");
			FNC_IN  (BX_SiteStats, Mode, "Режим вывода.");
			FNC_IN  (BX_SiteStats, SortOrder, "Способ обработки URL: ('Domain','Page')");
			FNC_IN  (BX_SiteStats, StartDate, "Начальная дата.");
			FNC_IN  (BX_SiteStats, EndDate, "Конечная дата.");
			FNC_IN  (BX_SiteStats, FirstPos, "Позиция в отсортированном списке первого объекта.");
			FNC_IN  (BX_SiteStats, LastPos, "Позиция в отсортированном списке последнего объекта.");
			FNC_OUT (BX_SiteStats, Name, "Название сайта.");
			FNC_OUT (BX_SiteStats, Description, "Описание сайта.");
			FNC_OUT (BX_SiteStats, CreationTime, "Время создания сайта (по Гринвичу).");
			FNC_OUT (BX_SiteStats, URL, "URL сайта.");
			FNC_OUT (BX_SiteStats, RawTable, "Строковый массив с упакованной статистической информацией.");
			FNC_OUT (BX_SiteStats, TotalObjects, "Количество строк в таблице RawTable.");
			FNC_OUT (BX_SiteStats, StartDate, "Начальная дата.");
			FNC_OUT (BX_SiteStats, EndDate, "Конечная дата.");
			FNC_OUT (BX_SiteStats, ExitCode, "Код возврата.");

   // Site
      FNC        (BX_Site_GetAliasByID, "Получить синоним сайта по ID.");
			FNC_IN  (BX_Site, objID, "{class:Site}Идентификатор сайта.");
			FNC_OUT (BX_Site, Alias, "Синоним сайта.");
      FNC        (BX_Site_GetIDByAlias, "Получить ID по синониму сайта.");
			FNC_IN  (BX_Site, Alias, "Синоним сайта.");
			FNC_OUT (BX_Site, objID, "Идентификатор сайта или NA если нет сайта с таким синонимом.");

   // Admin
      FNC        (BX_Admin_SaveBXObjects, "Сохранение основных объектов BX.");
			FNC_IN  (BX_Admin, Password, "Пароль администратора.");
			FNC_OUT (BX_Admin, Result, "Описания сохраненных объектов.");

   // Site
      FNC        (BX_Site_GetBriefInfo, "Краткая информация по сайту.");
			FNC_IN  (BX_Site, objID, "{class:Site}Идентификатор сайта.");
			FNC_OUT (BX_Site, Name, "Название сайта.");
			FNC_OUT (BX_Site, Description, "Описание.");
			FNC_OUT (BX_Site, URL, "URL сайта.");
			FNC_OUT (BX_Site, CreationTime, "Время создания (по Гринвичу).");

   // TimeStats
      FNC        (BX_TimeStats_GetData, "Получение данных из полновременного счетчика сайта.");
			FNC_IN  (BX_TimeStats, objID, "ID объекта-владельца счетчика.");
			FNC_IN  (BX_TimeStats, OwnerPassword, "Пароль владельца информации.");
			FNC_IN  (BX_TimeStats, StatsPassword, "Пароль на доступ к статистике.");
			FNC_IN  (BX_TimeStats, Object, "Название объекта-владельца счетчика (напр. 'Site').");
			FNC_IN  (BX_TimeStats, Counter, "Название счетчика (напр. 'Hits').");
			FNC_IN  (BX_TimeStats, Date_Start, "Начальная дата диапазона (сек).");
			FNC_IN  (BX_TimeStats, Date_End, "Конечная дата диапазона (сек).");
			FNC_IN  (BX_TimeStats, TZOffset, "Смещение часового пояса (сек).");
			FNC_IN  (BX_TimeStats, TimeDescrete, "Дикретизация (0-None,1-Hour,2-Day,3-Week,4-Month).");
			FNC_IN  (BX_TimeStats, TimeAggregate, "Агрегирование (0-None,1-HourOfDay,2-DayOfWeek,3-DayOfMonth,4-MonthOfYear).");
			FNC_IN  (BX_TimeStats, WeekdayLong, "Использовать длинные названия дней недели.");
			FNC_IN  (BX_TimeStats, MonthLong, "Использовать длинные названия месяцев.");
			FNC_OUT (BX_TimeStats, Data, "Значения выборки.");
			FNC_OUT (BX_TimeStats, Labels, "Метки значений выборки.");
			FNC_OUT (BX_TimeStats, ExitCode, "Код возврата.");

   // SiteStats
      FNC        (BX_SiteStats_WhatsNew, "Возвращает информацию о последних событиях и зрителях.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}Идентификатор сайта.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "Пароль владельца информации.");
			FNC_IN  (BX_SiteStats, StatsPassword, "Пароль на доступ к статистике.");
			FNC_OUT (BX_SiteStats, Name, "Название сайта.");
			FNC_OUT (BX_SiteStats, Description, "Описание сайта.");
			FNC_OUT (BX_SiteStats, CreationTime, "Время создания сайта (по Гринвичу).");
			FNC_OUT (BX_SiteStats, URL, "URL сайта.");
			FNC_OUT (BX_SiteStats, RawVector, "Строковый массив с упакованной статистической информацией.");
			FNC_OUT (BX_SiteStats, RawTable, "Строковый массив с упакованной статистической информацией.");
			FNC_OUT (BX_SiteStats, TotalObjects, "Количество строк в таблице RawTable.");
			FNC_OUT (BX_SiteStats, ExitCode, "Код возврата.");

   // Site
      FNC        (BX_Site_GetStatsPassword, "Получить пароль на доступ к статистике сайта.");
			FNC_IN  (BX_Site, objID, "{class:Site}Идентификатор сайта.");
			FNC_OUT (BX_Site, RateStatsViewPassword, "Пароль на доступ к статистике посещаемости для этого сайта.");
      FNC        (BX_Site_CheckStatsPassword, "Проверка пароля на доступ к статистике сайта.");
			FNC_IN  (BX_Site, objID, "{class:Site}Идентификатор сайта.");
			FNC_IN  (BX_Site, OwnerPassword, "Пароль владельца информации.");
			FNC_IN  (BX_Site, StatsPassword, "Пароль на доступ к статистике.");
			FNC_OUT (BX_Site, ExitCode, "True, если хотя бы один из паролей подходит к статистике сайта.");
      FNC        (BX_Site_GetVBN, "Получение ID VBN по ID сайта.");
			FNC_IN  (BX_Site, objID, "{class:Site}Идентификатор сайта.");
			FNC_OUT (BX_Site, VBN, "ID виртуальной подсети.");

   // SiteStats
      FNC        (BX_SiteStats_AudienceIntersect, "Возвращает информацию, касающуюся пересечения аудиторий сайта.");
			FNC_IN  (BX_SiteStats, objID, "{class:Site}Идентификатор сайта.");
			FNC_IN  (BX_SiteStats, OwnerPassword, "Пароль владельца информации.");
			FNC_IN  (BX_SiteStats, StatsPassword, "Пароль на доступ к статистике.");
			FNC_IN  (BX_SiteStats, SortOrder, "Порядок сортировки ('Hosts','Viewers').");
			FNC_IN  (BX_SiteStats, FirstPos, "Позиция в отсортированном списке первого объекта.");
			FNC_IN  (BX_SiteStats, LastPos, "Позиция в отсортированном списке последнего объекта.");
			FNC_OUT (BX_SiteStats, Name, "Название сайта.");
			FNC_OUT (BX_SiteStats, Description, "Описание сайта.");
			FNC_OUT (BX_SiteStats, CreationTime, "Время создания сайта (по Гринвичу).");
			FNC_OUT (BX_SiteStats, URL, "URL сайта.");
			FNC_OUT (BX_SiteStats, RawTable, "Строковый массив с упакованной статистической информацией.");
			FNC_OUT (BX_SiteStats, TotalObjects, "Количество строк в таблице RawTable.");
			FNC_OUT (BX_SiteStats, ExitCode, "Код возврата.");

   // IPRecord
      FNC        (BX_IPRecord_New, "Создать новый диапазон адресов.");
			FNC_IN  (BX_IPRecord, AdminPassword, "Пароль админа.");
			FNC_IN  (BX_IPRecord, First, "Начало диапазона.");
			FNC_IN  (BX_IPRecord, Last, "Конец диапазона.");
			FNC_IN  (BX_IPRecord, Checked, "Проверено администратором");
			FNC_IN  (BX_IPRecord, ConceptID, "Идентификаторы концептов, соответствующие этому диапазону.");
			FNC_OUT (BX_IPRecord, objID, "Идентификатор объекта диапазона.");
      FNC        (BX_IPRecord_GetData, "Получить параметры диапазона адресов.");
			FNC_IN  (BX_IPRecord, AdminPassword, "Пароль админа.");
			FNC_IN  (BX_IPRecord, objID, "{class:IRecord}Идентификатор объекта диапазона.");
			FNC_OUT (BX_IPRecord, Count, "Счётчик хитов с этого диапазона IP.");
			FNC_OUT (BX_IPRecord, Mask, "Маска диапазона адресов (т.е. адрес без последней цифры).");
			FNC_OUT (BX_IPRecord, First, "Начало диапазона.");
			FNC_OUT (BX_IPRecord, Last, "Конец диапазона.");
			FNC_OUT (BX_IPRecord, Checked, "Проверено администратором");
			FNC_OUT (BX_IPRecord, ConceptID, "Идентификаторы концептов, соответствующие этому диапазону.");
      FNC        (BX_IPRecord_Check, "Установить границы диапазона адресов и соответствующие ему концепты. Отличается от New тем, что не создает нового объекта, а устанавливает (помимо прочего) флаг checked у существующего. Если массив концептов пуст, то существующие у объекта концепты не меняются.");
			FNC_IN  (BX_IPRecord, AdminPassword, "Пароль админа.");
			FNC_IN  (BX_IPRecord, objID, "{class:IRecord}Идентификатор объекта диапазона.");
			FNC_IN  (BX_IPRecord, First, "Начало диапазона.");
			FNC_IN  (BX_IPRecord, Last, "Конец диапазона.");
			FNC_IN  (BX_IPRecord, ConceptID, "Идентификаторы концептов, соответствующие этому диапазону.");
      FNC        (BX_IPRecord_Enumerate, "Вывод зарегистрированных в системе IP-диапазонов.");
			FNC_IN  (BX_IPRecord, Checked, "Выводить сети с установленным флагом Checked (т.е. с установленными полями First и Last).");
			FNC_IN  (BX_IPRecord, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_IPRecord, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_IPRecord, objIDs, "Идентификаторы объектов.");
			FNC_OUT (BX_IPRecord, objNames, "Информация о диапазонах.");

   // Concept
      FNC        (BX_Concept_TypeEnumerate, "Возвращает номера типов концептов и их названия.");
			FNC_OUT (BX_Concept, objNums, "Массив номеров объектов.");
			FNC_OUT (BX_Concept, objNames, "Массив названий типов концептов.");

   // User
      FNC        (BX_User_GetLanguage, "Возвращает ID языка интерфейса пользователя. Пароль не требуется.");
			FNC_IN  (BX_User, objID, "{class:User}ID пользователя.");
			FNC_OUT (BX_User, InterfaceLanguage, "ID языка интерфейса пользователя.");

   // Site
      FNC        (BX_Site_GetAudienceIntersect, "Получить пересечение аудиторий для данного сайта.");
			FNC_IN  (BX_Site, objID, "{class:Site}ID cайта.");
			FNC_OUT (BX_Site, Audience_SiteID, "ID сайтов, на которых побывали посетители данного сайта.");
			FNC_OUT (BX_Site, Audience_SiteName, "Названия сайтов, на которых побывали посетители данного сайта.");
			FNC_OUT (BX_Site, Audience_Viewers, "Число посетителей сайта, побывавших на сайте соответствующего конкурента.");
			FNC_OUT (BX_Site, Audience_Hosts, "Кол-во хостов, которые посетители сайта сделали на сайте соответствующего конкурента.");

   // ConceptRate
      FNC        (BX_ConceptRate_Reg_InetAudience, "Получить распределение концептов для аудитории интернета.");
			FNC_IN  (BX_ConceptRate, TypeNums, "Номера типов концептов, которые хотелось бы увидеть в распределении.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "Номер языка, на котором будут выведены названия концептов (по умолчанию - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "Названия концептов, имеющихся в нормализованном распределении.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "Значения нормализованного распределения.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "Уровни концептов из CRN_Name.");
      FNC        (BX_ConceptRate_Site_Visitor, "Получить распределение концептов посетителей сайта.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Site}ID cайта.");
			FNC_IN  (BX_ConceptRate, TypeNums, "Номера типов концептов, которые хотелось бы увидеть в распределении.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "Номер языка, на котором будут выведены названия концептов (по умолчанию - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "Названия концептов, имеющихся в нормализованном распределении.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "Значения нормализованного распределения.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "Уровни концептов из CRN_Name.");
      FNC        (BX_ConceptRate_Viewer_Site, "Получить распределение концептов зрителя.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Viewer}ID зрителя.");
			FNC_IN  (BX_ConceptRate, TypeNums, "Номера типов концептов, которые хотелось бы увидеть в распределении.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "Номер языка, на котором будут выведены названия концептов (по умолчанию - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "Названия концептов, имеющихся в нормализованном распределении.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "Значения нормализованного распределения.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "Уровни концептов из CRN_Name.");
      FNC        (BX_ConceptRate_Viewer_Inquiry, "Получить распределение анкетных концептов зрителя.");
			FNC_IN  (BX_ConceptRate, objID, "{class:Viewer}ID зрителя.");
			FNC_IN  (BX_ConceptRate, TypeNums, "Номера типов концептов, которые хотелось бы увидеть в распределении.");
			FNC_IN  (BX_ConceptRate, objLanguageNo, "Номер языка, на котором будут выведены названия концептов (по умолчанию - 0).");
			FNC_OUT (BX_ConceptRate, CRN_Name, "Названия концептов, имеющихся в нормализованном распределении.");
			FNC_OUT (BX_ConceptRate, CRN_Value, "Значения нормализованного распределения.");
			FNC_OUT (BX_ConceptRate, CRN_Level, "Уровни концептов из CRN_Name.");

   // Admin
      FNC        (BX_Admin_MemoryManagerReport, "Получение отчета диспетчера памяти. Требуется пароль администратора.");
			FNC_OUT (BX_Admin, MemoryManagerReport, "Отчет диспетчера памяти.");

   // Viewer
      FNC        (BX_Viewer_Enumerate, "Перечислить зрителей.");
			FNC_IN  (BX_Viewer, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_Viewer, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_Viewer, objIDs, "Идентификаторы объектов.");
			FNC_OUT (BX_Viewer, objNames, "ID+IP зрителя.");
      FNC        (BX_Viewer_GetData, "Получить информацию по зрителю.");
			FNC_IN  (BX_Viewer, objID, "{class:Viewer}ID зрителя");
			FNC_IN  (BX_Viewer, IPAddress, "IP адрес (используется, если не указан objID). Если зритель с этим IP не найден, то здесь вернётся 'NotFound'.");
			FNC_OUT (BX_Viewer, Anonymous, "Является ли этот объект разделяемым между зрителями с одинаковым IP и неустановленным Cookie.");
			FNC_OUT (BX_Viewer, TotalShows, "Общее кол-во показов.");
			FNC_OUT (BX_Viewer, TotalClicks, "Общее кол-во кликов.");
			FNC_OUT (BX_Viewer, IPAddress, "IP адрес.");
			FNC_OUT (BX_Viewer, Referrer, "Хост зрителя.");
			FNC_OUT (BX_Viewer, CreationTime, "Время создания объекта.");
			FNC_OUT (BX_Viewer, sCreationTime, "Время создания объекта в строковом виде.");
			FNC_OUT (BX_Viewer, LastVisitTime, "Время последнего посещения.");
			FNC_OUT (BX_Viewer, sLastVisitTime, "Время последнего посещения в строковом виде.");
			FNC_OUT (BX_Viewer, TZOffset, "Смещение часового пояса зрителя в секундах.");
			FNC_OUT (BX_Viewer, Site, "ID сайтов, посещённых зрителем.");
			FNC_OUT (BX_Viewer, sSite, "Названия сайтов, посещённых зрителем.");
			FNC_OUT (BX_Viewer, sSite_LastVisited, "Время последнего посещения соответствующего сайта в строковом виде.");
			FNC_OUT (BX_Viewer, Site_Visits, "Общее число посещений соответствующего сайта.");

   // RateStats
      FNC        (BX_RateStats_Site, "Получить рейтинговую информацию по сайтам.");
			FNC_IN  (BX_RateStats, VBN, "{class:VBN}Идентификатор VBN, для объектов которой выводится индекс.");
			FNC_IN  (BX_RateStats, Concept, "{class:Concept}Массив концептов объектов.");
			FNC_IN  (BX_RateStats, FirstPos, "Позиция в рейтинге первого объекта.");
			FNC_IN  (BX_RateStats, LastPos, "Позиция в рейтинге последнего объекта.");
			FNC_IN  (BX_RateStats, Ascending, "Сортировка по возрастанию.");
			FNC_IN  (BX_RateStats, WithDescription, "Выдавать ли описания.");
			FNC_IN  (BX_RateStats, CreatedAfter, "Сайт создан после указанного времени");
			FNC_IN  (BX_RateStats, CreatedBefore, "Сайт создан до указанного времени");
			FNC_IN  (BX_RateStats, Indices, "Массив названий индексов, значения которых у сайтов надо выдать.");
			FNC_IN  (BX_RateStats, KeyIndex, "Название индекса, по которому происходит сортировка.");
			FNC_OUT (BX_RateStats, RawTable, "Строковый массив с упакованной рейтинговой таблицей.");
			FNC_OUT (BX_RateStats, ObjectsNum, "Количество объектов, данные по которым упакованы в RawTable.");
			FNC_OUT (BX_RateStats, Total, "Всего в VBN по запрошенным индексам.");
			FNC_OUT (BX_RateStats, SubTotal, "Всего в данной группе по запрошенным индексам.");
			FNC_OUT (BX_RateStats, VBNTotalObjects, "Всего объектов в данной VBN.");
			FNC_OUT (BX_RateStats, ReqTotal, "Всего по запрошенным индексам у удовлетворяющих сайтов.");
			FNC_OUT (BX_RateStats, VBNTotalObjectsAct, "Всего активных объектов в данной VBN.");
			FNC_OUT (BX_RateStats, ReqTotalObjects, "Всего объектов, удовлетворяющих выборке");
			FNC_OUT (BX_RateStats, ReqTotalObjectsAct, "Всего активных объектов, удовлетворяющих выборке");

   // Security
      FNC        (BX_Security_Authorize, "Авторизация пользователей, администраторов системы и VBN.");
			FNC_IN  (BX_Security, VBN, "ID виртуальной сети, нужен только для авторизации пользователя.");
			FNC_IN  (BX_Security, Level, "Кого авторизовать - может принимать одно из 3 значений: 'Root', 'VBN', 'User'.");
			FNC_IN  (BX_Security, Login, "Логин, для VBN - это имя VBN, для рута - это 'Root'.");
			FNC_IN  (BX_Security, Password, "Пароль.");
			FNC_OUT (BX_Security, Result, "True, если авторизация прошла успешно.");

   // User
      FNC        (BX_User_Enumerate, "Перечисления всех пользователей независимо от VBN.");
			FNC_IN  (BX_User, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_User, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_User, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_User, objNames, "Массив названий объектов на языке с номером objLanguageNo.");

   // SiteProfile
      FNC        (BX_SiteProfile_Enumerate, "Перечисления всех профилей сайта независимо от VBN.");
			FNC_IN  (BX_SiteProfile, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_SiteProfile, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_SiteProfile, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_SiteProfile, objNames, "Массив названий объектов на языке с номером objLanguageNo.");

   // Site
      FNC        (BX_Site_Enumerate, "Перечисления всех сайтов независимо от VBN.");
			FNC_IN  (BX_Site, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_Site, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_Site, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_Site, objNames, "Массив названий объектов на языке с номером objLanguageNo.");

   // BannerProfile
      FNC        (BX_BannerProfile_Enumerate, "Перечисления всех профилей баннеров независимо от VBN.");
			FNC_IN  (BX_BannerProfile, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_BannerProfile, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_BannerProfile, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_BannerProfile, objNames, "Массив названий объектов на языке с номером objLanguageNo.");

   // Banner
      FNC        (BX_Banner_Enumerate, "Перечисления всех баннеров независимо от VBN.");
			FNC_IN  (BX_Banner, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_Banner, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_Banner, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_Banner, objNames, "Массив названий объектов на языке с номером objLanguageNo.");

   // Language
      FNC        (BX_Language_New, "Создание нового языка. В случае создания в objID возвращается идентификатор созданного объекта.");
			FNC_IN  (BX_Language, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Language, ShortName, "Аббревиатура языка.");
			FNC_IN  (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_IN  (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_IN  (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_OUT (BX_Language, objID, "Идентификатор объекта.");
      FNC        (BX_Language_PutData, "Изменение параметров существующего языка с идентификатором objID.");
			FNC_IN  (BX_Language, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");
			FNC_IN  (BX_Language, ShortName, "Аббревиатура языка.");
			FNC_IN  (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_IN  (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_IN  (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
      FNC        (BX_Language_Enumerate, "Получение названий всех языков, зарегистрированных в системе. Названия возвращаются в поле objNames[] входной структуры. Соответствующие идентификаторы возвращаются в поле objIDs[] входной структуры.");
			FNC_IN  (BX_Language, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_Language, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_IN  (BX_Language, objLanguageNo, "Порядковый номер языка, на котором выдаются результаты функцией *Enumerate(). По умолчанию равен порядковому номеру каждого возвращенного языка.");
			FNC_OUT (BX_Language, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_Language, objNames, "Массив названий объектов на языке с номером objLanguageNo.");
      FNC        (BX_Language_GetData, "Получение информации о языке с указанным ID.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");
			FNC_OUT (BX_Language, ShortName, "Аббревиатура языка.");
			FNC_OUT (BX_Language, OwnName, "Название данного языка на самом себе.");
			FNC_OUT (BX_Language, Name, "Массив названий языка на всех поддерживаемых языках. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_OUT (BX_Language, Language, "Массив названий поддерживаемых языков на добавляемом языке. Порядок следования названий должен соответствовать порядку добавления языков в систему.");
			FNC_OUT (BX_Language, No, "Порядковый языка в системе");
      FNC        (BX_Language_Delete, "Удаление языка.");
			FNC_IN  (BX_Language, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Language, objID, "Идентификатор объекта.");

   // Concept
      FNC        (BX_Concept_New, "Создание концепта. В случае создания идентификатор созданного концепта возвращается в objID.");
			FNC_IN  (BX_Concept, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Concept, Parent, "{class:Concept}Id родителя - по идее должен быть равен NA только у корня дерева");
			FNC_IN  (BX_Concept, Name, "Массив названий концепта на всех языках, имеющихся в системе.");
			FNC_IN  (BX_Concept, Description, "Массив описаний концепта на всех языках, имеющихся в системе.");
			FNC_IN  (BX_Concept, ShortName, "Сокращённое имя.");
			FNC_IN  (BX_Concept, Type, "Тип концепта.");
			FNC_IN  (BX_Concept, TypeNo, "Номер типа концепта.");
			FNC_OUT (BX_Concept, objID, "Идентификатор объекта.");
      FNC        (BX_Concept_PutData, "Модификация параметров существующего концепта с идентификатором objID.");
			FNC_IN  (BX_Concept, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Concept, objID, "Идентификатор объекта.");
			FNC_IN  (BX_Concept, Name, "Массив названий концепта на всех языках, имеющихся в системе.");
			FNC_IN  (BX_Concept, Description, "Массив описаний концепта на всех языках, имеющихся в системе.");
			FNC_IN  (BX_Concept, ShortName, "Сокращённое имя.");
			FNC_IN  (BX_Concept, Type, "Тип концепта.");
			FNC_IN  (BX_Concept, TypeNo, "Номер типа концепта.");
      FNC        (BX_Concept_Enumerate, "Получение идентификаторов всех концептов на языке # objLanguageNo методом 'в ширину', т.е. в порядке возрастания уровня.");
			FNC_IN  (BX_Concept, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_Concept, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_IN  (BX_Concept, objLanguageNo, "Порядковый номер языка, на котором выдаются результаты функцией *Enumerate().");
			FNC_OUT (BX_Concept, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_Concept, objNames, "Массив названий объектов на языке с номером objLanguageNo.");
      FNC        (BX_Concept_ExtendedEnumerate, "Получить список идентификаторов и названий концептов заданного уровня на заданном языке с возможными отступами в соответствии с уровнем. Концепты выводятся 'в глубину', т.е. в порядке следования родителей. Если указан Level, то выводятся концепты с уровнем до Level включительно, иначе - все концепты.");
			FNC_IN  (BX_Concept, SiteCount, "Если SiteCount > 0, то к имени концепта добавляется (количество сайтов с данной тематикой).");
			FNC_IN  (BX_Concept, Indent, "Если Indent == true, то перед именем концепта вставляется нужное количество отступов в html-формате.");
			FNC_IN  (BX_Concept, VBN, "{class:VBN}Если указан VBN, то выводятся концепты заданной VBN.");
			FNC_IN  (BX_Concept, Level, "Если указан Level, то выводятся концепты с уровнем до Level включительно, иначе - все тематики.");
			FNC_IN  (BX_Concept, ConceptType, "Тип концепта (для Extended Enumerate).");
			FNC_IN  (BX_Concept, objLanguageNo, "Если указан номер языка objLanguage, то он определяет язык концептов, иначе язык равен языку VBN, иначе - нулевому языку.");
			FNC_OUT (BX_Concept, objIDs, "Массив идентификаторов концептов.");
			FNC_OUT (BX_Concept, objNames, "Массив названий концептов.");
      FNC        (BX_Concept_GetData, "Получение информации о концепте с указанным идентификатором objID.");
			FNC_IN  (BX_Concept, objID, "Идентификатор объекта.");
			FNC_OUT (BX_Concept, Parent, "Id родителя - по идее должен быть равен NA только у корня дерева.");
			FNC_OUT (BX_Concept, Name, "Массив названий концепта на всех языках, имеющихся в системе.");
			FNC_OUT (BX_Concept, Description, "Массив описаний концепта на всех языках, имеющихся в системе.");
			FNC_OUT (BX_Concept, ShortName, "Сокращённое имя.");
			FNC_OUT (BX_Concept, Type, "Тип концепта.");
			FNC_OUT (BX_Concept, TypeNo, "Номер типа концепта.");
			FNC_OUT (BX_Concept, Level, "Уровень тематики в дереве тематической иерархии.");
			FNC_OUT (BX_Concept, No, "Порядковый номер тематики.");
      FNC        (BX_Concept_Delete, "Удаление концепта с указанным идентификатором objID. Все потомки концепта также удаляются.");
			FNC_IN  (BX_Concept, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_Concept, objID, "Идентификатор объекта.");

   // VBN
      FNC        (BX_VBN_New, "Создание виртуальной баннерной сети. На входе нужен пароль владельца сети Password, который будет требоваться  для доступа ко всем функциям с данной VBN, а также пароль администратора AdminPassword. В случае создания в objID возвращается идентификатор созданного объекта.");
			FNC_IN  (BX_VBN, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_VBN, Password, "Пароль, который впоследствии будет использоваться для доступа к настройкам сети.");
			FNC_IN  (BX_VBN, Name, "Название сети.");
			FNC_IN  (BX_VBN, Description, "Описание сети.");
			FNC_IN  (BX_VBN, IsModerated, "Является ли сеть премодерируемой.");
			FNC_IN  (BX_VBN, DefaultLanguage, "{class:Language}ID языка сети по умолчанию.");
			FNC_IN  (BX_VBN, DefaultTZOffset, "Смещение часового пояса по умолчанию (в секундах).");
			FNC_IN  (BX_VBN, ConceptMask, "{class:Concept}Массив идентификаторов используемых в сети концептов (если он пуст, то используются все концепты).");
			FNC_OUT (BX_VBN, objID, "Идентификатор объекта.");
      FNC        (BX_VBN_PutData, "Изменение параметров виртуальной баннерной сети с идентификатором objID. На входе нужен пароль владельца сети Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к настройкам сети.");
			FNC_IN  (BX_VBN, Name, "Название сети.");
			FNC_IN  (BX_VBN, Description, "Описание сети.");
			FNC_IN  (BX_VBN, IsModerated, "Является ли сеть премодерируемой.");
			FNC_IN  (BX_VBN, DefaultLanguage, "{class:Language}ID языка сети по умолчанию.");
			FNC_IN  (BX_VBN, DefaultTZOffset, "Смещение часового пояса по умолчанию (в секундах).");
			FNC_IN  (BX_VBN, ConceptMask, "{class:Concept}Массив идентификаторов используемых в сети концептов (если он пуст, то используются все концепты).");
      FNC        (BX_VBN_Enumerate, "Получение идентификаторов (в objIDs) и названий (objNames) всех виртуальных банерных сетей, зарегистрированных в системе.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов на языке с номером objLanguageNo.");
      FNC        (BX_VBN_GetData, "Получение параметров виртуальной баннерной сети с указанным objID. Пароль владельца сети передавать не нужно.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_OUT (BX_VBN, Name, "Название сети.");
			FNC_OUT (BX_VBN, Description, "Описание сети.");
			FNC_OUT (BX_VBN, IsModerated, "Является ли сеть премодерируемой.");
			FNC_OUT (BX_VBN, DefaultLanguage, "ID языка сети по умолчанию.");
			FNC_OUT (BX_VBN, DefaultTZOffset, "Смещение часового пояса по умолчанию (в секундах).");
			FNC_OUT (BX_VBN, ConceptMask, "Массив идентификаторов используемых в сети концептов (если он пуст, то используются все концепты).");
			FNC_OUT (BX_VBN, No, "Порядковый номер сети.");
      FNC        (BX_VBN_ConceptEnumerate, "Получение идентификаторов (в objIDs) и названий (objNames) всех концептов виртуальной банерной сети с идентификатором objID.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, objLanguageNo, "Порядковый номер языка, на котором выдаются результаты, по умолчанию равен языку VBN.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов концептов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий концептов.");
      FNC        (BX_VBN_GetOwnerID, "Получение идентификатора владельца сети. На входе нужен пароль владельца сети Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к настройкам сети.");
			FNC_OUT (BX_VBN, Owner, "Владелец сети, которому идут проценты с показов.");
      FNC        (BX_VBN_Delete, "Удаление виртуальной баннерной сети с указанным идентификатором objID. Необходимо передать правильный пароль администратора AdminPassword.");
			FNC_IN  (BX_VBN, AdminPassword, "Пароль администратора системы.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
      FNC        (BX_VBN_UserEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена разрешённых пользователей из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_SiteEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена разрешённых сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_SiteProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена разрешённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_BannerEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена разрешённых баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_BannerProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена разрешённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_UnallowedUserEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена неразрешённых пользователей из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_UnallowedSiteEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена  неразрешённых сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_UnallowedSiteProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена  неразрешённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_UnallowedBannerEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена неразрешённых баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_UnallowedBannerProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена неразрешённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_NewUserEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена новых пользователей из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_NewSiteEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена новых сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_NewSiteProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена новых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_NewBannerEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена новых баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_NewBannerProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена новых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_ChangedUserEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена изменённых пользователей из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_ChangedSiteEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена изменённых сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_ChangedSiteProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена изменённых профилей сайтов из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_ChangedBannerEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена изменённых баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");
      FNC        (BX_VBN_ChangedBannerProfileEnumerate, "Возвращает в objIDs и objNames идентификаторы и имена изменённых профилей баннеров из VBN с id=objID. Необходимо указать пароль Password.");
			FNC_IN  (BX_VBN, objID, "Идентификатор виртуальной сети.");
			FNC_IN  (BX_VBN, Password, "Пароль для доступа к виртуальной баннерной сети.");
			FNC_IN  (BX_VBN, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_VBN, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_VBN, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_VBN, objNames, "Массив названий объектов.");

   // User
      FNC        (BX_User_GetForgetPassword, "Возвращает флаг перезагрузки пароля.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID виртуальной сети пользователя.");
			FNC_IN  (BX_User, Login, "Имя для доступа к объекту.");
			FNC_OUT (BX_User, ForgetPassword, "Значение флага.");
      FNC        (BX_User_SetForgetPassword, "Устанавливает флаг перезагрузки пароля.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID виртуальной сети пользователя.");
			FNC_IN  (BX_User, Login, "Имя для доступа к объекту.");
			FNC_IN  (BX_User, ForgetPassword, "Значение флага.");
      FNC        (BX_User_New, "Создание пользователя. Также создаются профили баннера и сайта по умолчанию.");
			FNC_IN  (BX_User, Login, "Имя для доступа к объекту.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, PasswordConfirm, "Подтверждение пароля.");
			FNC_IN  (BX_User, FullName, "Полное имя пользователя.");
			FNC_IN  (BX_User, Email, "E-mail.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID виртуальной сети пользователя.");
			FNC_OUT (BX_User, objID, "Идентификатор пользователя.");
			FNC_OUT (BX_User, ExitCode, "Код возврата (Okay=0;BadPasswordConfirm=1;InvalidEmail=2;PasswordTooShort=3;LoginTooShort=4;LoginAlreadyExists=5).");
      FNC        (BX_User_GetData, "Получение установок пользователя. Если не указан objID, то пользователь ищется по полям Login, Password и VBN, а идентификатор найденного пользователя возвращается в objID. В этом случае возможен возврат ошибок BXE_User_GetData_LoginNotFound или BXE_User_GetData_PasswordIncorrect. Пароль пользователя Password необходимо указать в любом случае.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Login, "Имя для доступа к объекту.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID виртуальной сети.");
			FNC_OUT (BX_User, objID, "Идентификатор найденного пользователя, если производился поиск по Login/Password.");
			FNC_OUT (BX_User, Login, "Имя для доступа к объекту.");
			FNC_OUT (BX_User, FullName, "Полное имя пользователя.");
			FNC_OUT (BX_User, InterfaceLanguage, "ID препочтительного языка интерфейса.");
			FNC_OUT (BX_User, InterfaceType, "Интерфейс пользователя (быстрый/точный).");
			FNC_OUT (BX_User, CreationTime, "Время создания объекта.");
			FNC_OUT (BX_User, sCreationTime, "Время создания объекта.");
			FNC_OUT (BX_User, VBN, "ID виртуальной сети пользователя.");
			FNC_OUT (BX_User, Email, "Email.");
			FNC_OUT (BX_User, Phone, "Телефон.");
			FNC_OUT (BX_User, Fax, "Fax.");
			FNC_OUT (BX_User, Address, "Адрес.");
			FNC_OUT (BX_User, URL, "URL-Адрес.");
			FNC_OUT (BX_User, Comment, "Комментарий.");
			FNC_OUT (BX_User, TZOffset, "Смещение временной зоны в секундах.");
			FNC_OUT (BX_User, NotifyFreq, "Как часто присылать статистику (не надо/ каждый день/неделю/месяц).");
			FNC_OUT (BX_User, NotifyHTML, "Присылать ли статистику в виде HTML.");
			FNC_OUT (BX_User, NotifyDepth, "Тип присылаемой статистики (её развёрнутость, глубина).");
			FNC_OUT (BX_User, ShowsLeft, "Общее число оставшихся показов.");
			FNC_OUT (BX_User, ClicksLeft, "Общее число оставшихся кликов.");
			FNC_OUT (BX_User, TradeStats, "Информация о продаже/покупке показов/кликов у пользователя.");
			FNC_OUT (BX_User, Allowed, "Информация пользователя разрешена модератором.");
			FNC_OUT (BX_User, ObjectState, "Состояние объекта: 0 - проверен; 1 - новый; 2 - изменено критическое поле; 3 - изменён.");
      FNC        (BX_User_GetEmail, "Получение адреса эл. почты пользователя по его логину и VBN.");
			FNC_IN  (BX_User, VBN, "{class:VBN}ID виртуальной сети пользователя.");
			FNC_IN  (BX_User, Login, "Имя для доступа к объекту.");
			FNC_OUT (BX_User, Email, "Email.");
      FNC        (BX_User_PutData, "Изменение установок пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, FullName, "Полное имя пользователя.");
			FNC_IN  (BX_User, InterfaceLanguage, "{class:Language}ID препочтительного языка интерфейса.");
			FNC_IN  (BX_User, InterfaceType, "Интерфейс пользователя (быстрый/точный).");
			FNC_IN  (BX_User, Email, "Email.");
			FNC_IN  (BX_User, Phone, "Телефон.");
			FNC_IN  (BX_User, Fax, "Fax.");
			FNC_IN  (BX_User, Address, "Адрес.");
			FNC_IN  (BX_User, URL, "URL-Адрес.");
			FNC_IN  (BX_User, Comment, "Комментарий.");
			FNC_IN  (BX_User, TZOffset, "Смещение временной зоны в секундах.");
			FNC_IN  (BX_User, NotifyFreq, "Как часто присылать статистику (не надо/ каждый день/неделю/месяц).");
			FNC_IN  (BX_User, NotifyHTML, "Присылать ли статистику в виде HTML.");
			FNC_IN  (BX_User, NotifyDepth, "Тип присылаемой статистики (её развёрнутость, глубина).");
      FNC        (BX_User_Delete, "Удаление пользователя с идентификатором objID. Удаляются все сайты, профили и баннеры пользователя. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
      FNC        (BX_User_SiteEnumerate, "Получение списка идентификаторов (в objIDs) и названий (в objNames) сайтов пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_User, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_User, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_User, objNames, "Массив названий объектов.");
      FNC        (BX_User_BannerEnumerate, "Получение списка идентификаторов (в objIDs) и названий (в objNames) баннеров пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_User, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_User, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_User, objNames, "Массив названий объектов.");
      FNC        (BX_User_SiteProfileEnumerate, "Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей сайтов пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_User, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_User, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_User, objNames, "Массив названий объектов.");
      FNC        (BX_User_BannerProfileEnumerate, "Получение списка идентификаторов (в objIDs) и названий (в objNames) профилей баннеров пользователя с идентификатором objID. Необходимо указать пароль пользователя Password.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к объекту.");
			FNC_IN  (BX_User, objFirstNo, "Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0.");
			FNC_IN  (BX_User, objLastNo, "Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.");
			FNC_OUT (BX_User, objIDs, "Массив идентификаторов объектов.");
			FNC_OUT (BX_User, objNames, "Массив названий объектов.");
      FNC        (BX_User_RegisterAsSystem, "Регистрация пользователя как системного (баннеры которого показываются в исключительных ситуациях). Необходимо указать Password для доступа к VBN пользователя.");
			FNC_IN  (BX_User, objID, "Идентификатор пользователя.");
			FNC_IN  (BX_User, Password, "Пароль для доступа к VBN пользователя.");

   // SiteProfile
      FNC        (BX_SiteProfile_New, "Создаёт профиль сайта для пользователя с идентификатором OwnerID. Если указан objFromID , то в созданный профиль копируются параметры из профиля с идентификатором objFromID. В objID возвращается id созданного профиля. В Name возвращается название созданного профиля. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_SiteProfile, OwnerID, "{class:User}Идентификатор пользователя-владельца.");
			FNC_IN  (BX_SiteProfile, objPassword, "Пароль пользователя-владельца объекта.");
			FNC_IN  (BX_SiteProfile, Name, "Название нового профиля (по умолчанию - timestamp).");
			FNC_IN  (BX_SiteProfile, objFromID, "Идентификатор source-профиля.");
			FNC_OUT (BX_SiteProfile, objID, "Идентификатор профиля сайта.");
			FNC_OUT (BX_SiteProfile, Name, "Название профиля.");
      FNC        (BX_SiteProfile_CopyData, "Копирование установок профиля сайта из профиля objFromID в профиль objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "Идентификатор профиля сайта.");
			FNC_IN  (BX_SiteProfile, objPassword, "Пароль пользователя-владельца объекта.");
			FNC_IN  (BX_SiteProfile, objFromID, "{class:SiteProfile}Идентификатор source-профиля.");
			FNC_OUT (BX_SiteProfile, Name, "Название профиля.");
      FNC        (BX_SiteProfile_GetData, "Получение установок профиля сайта с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "Идентификатор профиля сайта.");
			FNC_IN  (BX_SiteProfile, objPassword, "Пароль пользователя-владельца объекта.");
			FNC_OUT (BX_SiteProfile, Name, "Название профиля.");
			FNC_OUT (BX_SiteProfile, Site, "ID сайтов, пользующихся данным профилем.");
			FNC_OUT (BX_SiteProfile, sSite, "Имена сайтов, пользующихся данным профилем.");
			FNC_OUT (BX_SiteProfile, VBN, "ID виртуальной подсети.");
			FNC_OUT (BX_SiteProfile, LastModified, "Время последнего изменения профиля.");
			FNC_OUT (BX_SiteProfile, sLastModified, "Время последнего изменения профиля в строковом представлении.");
			FNC_OUT (BX_SiteProfile, OwnerID, "Идентификатор пользователя-владельца.");
			FNC_OUT (BX_SiteProfile, BannerInclude, "Список разрешённых к показу баннеров.");
			FNC_OUT (BX_SiteProfile, BannerExclude, "Список запрещённых к показу баннеров.");
			FNC_OUT (BX_SiteProfile, SiteInclude, "Список разрешённых к рекламе сайтов.");
			FNC_OUT (BX_SiteProfile, SiteExclude, "Список запрещённых к рекламе сайтов.");
			FNC_OUT (BX_SiteProfile, MaxFileSize, "Максимальный размер файла с баннерами.");
			FNC_OUT (BX_SiteProfile, UseKeywords, "Показывать баннеры в соответствии с ключевыми словами сайтов.");
			FNC_OUT (BX_SiteProfile, BannerConceptInclude, "Список разрешённыx к показу концептов ресурсов.");
			FNC_OUT (BX_SiteProfile, BannerConceptExclude, "Список запрещённых к показу концептов ресурсов.");
			FNC_OUT (BX_SiteProfile, Allowed, "Информация пользователя разрешена модератором.");
			FNC_OUT (BX_SiteProfile, ObjectState, "Состояние объекта: 0 - проверен; 1 - новый; 2 - изменено критическое поле; 3 - изменён.");
      FNC        (BX_SiteProfile_PutData, "Изменение установок профиля сайта с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "Идентификатор профиля сайта.");
			FNC_IN  (BX_SiteProfile, objPassword, "Пароль пользователя-владельца объекта.");
			FNC_IN  (BX_SiteProfile, Name, "Название профиля.");
			FNC_IN  (BX_SiteProfile, BannerInclude, "{class:Banner}Список разрешённых к показу баннеров.");
			FNC_IN  (BX_SiteProfile, BannerExclude, "{class:Banner}Список запрещённых к показу баннеров.");
			FNC_IN  (BX_SiteProfile, SiteInclude, "Список разрешённых к рекламе сайтов.");
			FNC_IN  (BX_SiteProfile, SiteExclude, "Список запрещённых к рекламе сайтов.");
			FNC_IN  (BX_SiteProfile, MaxFileSize, "Максимальный размер файла с баннерами.");
			FNC_IN  (BX_SiteProfile, UseKeywords, "Показывать баннеры в соответствии с ключевыми словами сайтов.");
			FNC_IN  (BX_SiteProfile, BannerConceptInclude, "{class:Concept}Список разрешённыx к показу концептов ресурсов.");
			FNC_IN  (BX_SiteProfile, BannerConceptExclude, "{class:Concept}Список запрещённых к показу концептов ресурсов.");
      FNC        (BX_SiteProfile_Delete, "Удаление установок профиля сайта с указанным ID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_SiteProfile, objID, "Идентификатор профиля сайта.");
			FNC_IN  (BX_SiteProfile, objPassword, "Пароль пользователя-владельца объекта.");

   // Site
      FNC        (BX_Site_New, "Создание сайта. Требуется идентификатор владельца OwnerID и URL сайта. Идентификатор созданного сайта возвращается в поле objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Site, OwnerID, "{class:User}ID пользователя-владельца сайта.");
			FNC_IN  (BX_Site, Profile, "{class:SiteProfile}Профиль баннера (по умолчанию не установлен).");
			FNC_IN  (BX_Site, Name, "Название сайта (по умолчанию=URL).");
			FNC_IN  (BX_Site, objPassword, "Пароль пользователя-владельца сайта.");
			FNC_IN  (BX_Site, URL, "URL сайта.");
			FNC_IN  (BX_Site, objFromID, "Идентификатор source-сайта.");
			FNC_OUT (BX_Site, objID, "Идентификатор объекта сайта.");
      FNC        (BX_Site_GetData, "Получение параметров сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Site, objID, "Идентификатор объекта сайта.");
			FNC_IN  (BX_Site, objPassword, "Пароль пользователя-владельца сайта.");
			FNC_OUT (BX_Site, OwnerID, "ID пользователя-владельца сайта.");
			FNC_OUT (BX_Site, VBN, "ID виртуальной подсети.");
			FNC_OUT (BX_Site, CreationTime, "Время создания в виде gmtime.");
			FNC_OUT (BX_Site, sCreationTime, "Время создания сайта в строковом виде.");
			FNC_OUT (BX_Site, MirrorInclude, "Список зеркал сайта.");
			FNC_OUT (BX_Site, MirrorExclude, "Список игнорируемых зеркал сайта.");
			FNC_OUT (BX_Site, MirrorSubstr, "Список слов, которые игнорируются в HTTP_REFERER при проверке зеркал.");
			FNC_OUT (BX_Site, IgnoredIP, "Список IP-адресов, хиты с которых не засчитываются (даже как подозрительные).");
			FNC_OUT (BX_Site, IgnoredViewerID, "Список ID зрителей, хиты с которых не засчитываются (даже как подозрительные).");
			FNC_OUT (BX_Site, Alias, "Синоним ID сайта.");
			FNC_OUT (BX_Site, Name, "Название сайта.");
			FNC_OUT (BX_Site, Description, "Описание (для категоризатора).");
			FNC_OUT (BX_Site, URL, "URL сайта.");
			FNC_OUT (BX_Site, CounterType, "Тип счётчика для этого сайта.");
			FNC_OUT (BX_Site, RateMySite, "Участвует ли этот сайт в рейтинге посещаемости.");
			FNC_OUT (BX_Site, RateStatsViewPassword, "Пароль на доступ к статистике посещаемости для этого сайта.");
			FNC_OUT (BX_Site, ShowAudience, "Разрешено ли участвовать в подсчётах пересечений аудиторий.");
			FNC_OUT (BX_Site, ShowAudienceOffTime, "Время последнего запрещения ShowAudience.");
			FNC_OUT (BX_Site, Profile, "ID объекта-профиля сайта.");
			FNC_OUT (BX_Site, Keyword, "Ключевые слова для этого сайта.");
			FNC_OUT (BX_Site, Concept, "Концепты сайта.");
			FNC_OUT (BX_Site, PageName, "Список названий страниц сайта.");
			FNC_OUT (BX_Site, PageNo, "Список номеров страниц сайта.");
			FNC_OUT (BX_Site, AdBannerProfile, "Список ID профилей баннеров, рекламирующих этот сайт.");
			FNC_OUT (BX_Site, SuspiciousInfo, "ID объекта со статистикой подозрительных событий.");
			FNC_OUT (BX_Site, Allowed, "Информация пользователя разрешена модератором.");
			FNC_OUT (BX_Site, ObjectState, "Состояние объекта: 0 - проверен; 1 - новый;2 - изменено критическое поле; 3 - изменён.");
      FNC        (BX_Site_PutData, "Изменение параметров сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Site, objID, "Идентификатор объекта сайта.");
			FNC_IN  (BX_Site, objPassword, "Пароль пользователя-владельца сайта.");
			FNC_IN  (BX_Site, MirrorInclude, "Список зеркал сайта.");
			FNC_IN  (BX_Site, MirrorExclude, "Список игнорируемых зеркал сайта.");
			FNC_IN  (BX_Site, MirrorSubstr, "Список слов, которые игнорируются в HTTP_REFERER при проверке зеркал.");
			FNC_IN  (BX_Site, IgnoredIP, "Список IP-адресов, хиты с которых не засчитываются (даже как подозрительные).");
			FNC_IN  (BX_Site, IgnoredViewerID, "Список ID зрителей, хиты с которых не засчитываются (даже как подозрительные).");
			FNC_IN  (BX_Site, Alias, "Синоним ID сайта.");
			FNC_IN  (BX_Site, Name, "Название сайта.");
			FNC_IN  (BX_Site, Description, "Описание (для категоризатора).");
			FNC_IN  (BX_Site, URL, "URL сайта.");
			FNC_IN  (BX_Site, CounterType, "Тип счётчика для этого сайта.");
			FNC_IN  (BX_Site, RateMySite, "Участвует ли этот сайт в рейтинге посещаемости.");
			FNC_IN  (BX_Site, RateStatsViewPassword, "Пароль на доступ к статистике посещаемости для этого сайта.");
			FNC_IN  (BX_Site, ShowAudience, "Разрешено ли участвовать в подсчётах пересечений аудиторий.");
			FNC_IN  (BX_Site, Profile, "{class:SiteProfile}ID объекта-профиля сайта.");
			FNC_IN  (BX_Site, Keyword, "Ключевые слова для этого сайта.");
			FNC_IN  (BX_Site, Concept, "{class:Concept}Концепты сайта.");
			FNC_IN  (BX_Site, PageName, "Список названий страниц сайта.");
      FNC        (BX_Site_Delete, "Удаление сайта с указанным идентификатором objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Site, objID, "Идентификатор объекта сайта.");
			FNC_IN  (BX_Site, objPassword, "Пароль пользователя-владельца сайта.");
      FNC        (BX_Site_GetCounterType, "Получить тип счетчика для сайта.");
			FNC_IN  (BX_Site, objID, "Идентификатор объекта сайта.");
			FNC_OUT (BX_Site, CounterType, "Тип счётчика для этого сайта.");

   // SiteSuspiciousInfo
      FNC        (BX_SiteSuspiciousInfo_GetData, "Получить информацию о подозрительных событиях, произошедших на сайте.");
			FNC_IN  (BX_SiteSuspiciousInfo, objID, "{class:Site}Идентификатор объекта сайта.");
			FNC_IN  (BX_SiteSuspiciousInfo, objPassword, "Пароль пользователя-владельца сайта.");
			FNC_OUT (BX_SiteSuspiciousInfo, sEventType, "Тип события (строка).");
			FNC_OUT (BX_SiteSuspiciousInfo, sTime, "Время возникновения события (московское).");
			FNC_OUT (BX_SiteSuspiciousInfo, Viewer, "ID зрителя, вызвавшего событие.");
			FNC_OUT (BX_SiteSuspiciousInfo, IP, "IP-адрес, вызвавший событие");
			FNC_OUT (BX_SiteSuspiciousInfo, Referrer, "URL, с которого пришло событие.");

   // BannerProfile
      FNC        (BX_BannerProfile_New, "Создаёт профиль баннера для пользователя OwnerID. Если указан objFromID , то в созданный профиль копируются параметры из профиля objFromID. В objID возвращается id созданного профиля. В Name  возвращается название созданного профиля. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_BannerProfile, OwnerID, "{class:User}Идентификатор пользователя-владельца профиля баннера.");
			FNC_IN  (BX_BannerProfile, objPassword, "Пароль пользователя-владельца профиля.");
			FNC_IN  (BX_BannerProfile, Name, "Название нового профиля (по умолчанию -Noname).");
			FNC_IN  (BX_BannerProfile, HREF, "{class:Site}ID сайта, на который надо перейти при нажатии на баннер.");
			FNC_IN  (BX_BannerProfile, objFromID, "Идентификатор source-профиля.");
			FNC_OUT (BX_BannerProfile, objID, "Идентификатор объекта профиля баннера.");
			FNC_OUT (BX_BannerProfile, Name, "Название профиля.");
      FNC        (BX_BannerProfile_CopyData, "Копирование установок профиля баннера из профиля objFromID в профиль objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "Идентификатор объекта профиля баннера.");
			FNC_IN  (BX_BannerProfile, objPassword, "Пароль пользователя-владельца профиля.");
			FNC_IN  (BX_BannerProfile, objFromID, "{class:BannerProfile}Идентификатор source-профиля.");
      FNC        (BX_BannerProfile_GetData, "Получение установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "Идентификатор объекта профиля баннера.");
			FNC_IN  (BX_BannerProfile, objPassword, "Пароль пользователя-владельца профиля.");
			FNC_OUT (BX_BannerProfile, Name, "Название профиля.");
			FNC_OUT (BX_BannerProfile, VBN, "ID виртуальной подсети.");
			FNC_OUT (BX_BannerProfile, LastModified, "Время последнего изменения профиля (gmtime).");
			FNC_OUT (BX_BannerProfile, sLastModified, "Время последнего изменения профиля в строковом виде.");
			FNC_OUT (BX_BannerProfile, OwnerID, "Идентификатор пользователя-владельца профиля баннера.");
			FNC_OUT (BX_BannerProfile, HREF, "ID сайта, на который надо перейти при нажатии на баннер.");
			FNC_OUT (BX_BannerProfile, Commercial, "Являются ли баннеры профиля коммерческими.");
			FNC_OUT (BX_BannerProfile, Banner, "Список баннеров, пользующихся данным профилем.");
			FNC_OUT (BX_BannerProfile, sBanner, "Список баннеров, пользующихся данным профилем в строковом виде.");
			FNC_OUT (BX_BannerProfile, Concept, "Концепты профиля.");
			FNC_OUT (BX_BannerProfile, State, "Состояние (вкл/выкл).");
			FNC_OUT (BX_BannerProfile, AltText, "Альтернативный текст.");
			FNC_OUT (BX_BannerProfile, SiteConceptInclude, "Концепты сайтов, на которых показывать баннер.");
			FNC_OUT (BX_BannerProfile, SiteConceptExclude, "Концепты сайтов, на которых НЕ показывать баннер.");
			FNC_OUT (BX_BannerProfile, SiteInclude, "Список разрешённых сайтов.");
			FNC_OUT (BX_BannerProfile, sSiteInclude, "Список имён разрешённых сайтов.");
			FNC_OUT (BX_BannerProfile, SiteExclude, "Список запрещённых сайтов.");
			FNC_OUT (BX_BannerProfile, sSiteExclude, "Список имён запрещённых сайтов.");
			FNC_OUT (BX_BannerProfile, ViewerIPEnable, "Разрешённые IP зрителей.");
			FNC_OUT (BX_BannerProfile, ViewerIPDisable, "Запрещённые IP зрителей.");
			FNC_OUT (BX_BannerProfile, ViewerConceptInclude, "Концепты зрителей, которым показывать баннер.");
			FNC_OUT (BX_BannerProfile, ViewerConceptExclude, "Концепты зрителей, которым НЕ показывать баннер.");
			FNC_OUT (BX_BannerProfile, UseLocalTime, "Применять ли расписание к локальному времени зрителя.");
			FNC_OUT (BX_BannerProfile, ScheduleTZOffset, "Часовой пояс расписания (если UseLocalTime==false).");
			FNC_OUT (BX_BannerProfile, ShowIfLocalUnknown, "Показывать ли баннер, если локальное время неизвестно (показывается с использованием ScheduleTZOffset).");
			FNC_OUT (BX_BannerProfile, Schedule, "Расписание - по биту на каждый час недели.");
			FNC_OUT (BX_BannerProfile, AutoOn, "Показывать в промежутке времени от ...");
			FNC_OUT (BX_BannerProfile, AutoOff, "до ...");
			FNC_OUT (BX_BannerProfile, RepeatCount, "Сколько раз показывать одному и тому же зрителю.");
			FNC_OUT (BX_BannerProfile, RepeatTime, "Показывать баннеры одному и тому же зрителю не чаще чем ...");
			FNC_OUT (BX_BannerProfile, CountTypeByShows, "Тип счета: на показы или на клики.");
			FNC_OUT (BX_BannerProfile, MaxDailyClicks, "Максимальное число кликов в день.");
			FNC_OUT (BX_BannerProfile, MaxDailyShows, "Максимальное число показов в день.");
			FNC_OUT (BX_BannerProfile, TotalShows, "Количество показов баннера этого профиля.");
			FNC_OUT (BX_BannerProfile, TotalClicks, "Количество нажатий на баннеры этого профиля.");
			FNC_OUT (BX_BannerProfile, Allowed, "Информация пользователя разрешена модератором (синоним Available).");
			FNC_OUT (BX_BannerProfile, ObjectState, "Состояние объекта: 0 - проверен 1 - новый 2 - изменено критическое поле 3 - изменён.");
      FNC        (BX_BannerProfile_PutData, "Изменение установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "Идентификатор объекта профиля баннера.");
			FNC_IN  (BX_BannerProfile, objPassword, "Пароль пользователя-владельца профиля.");
			FNC_IN  (BX_BannerProfile, Name, "Название профиля.");
			FNC_IN  (BX_BannerProfile, HREF, "ID сайта, на который надо перейти при нажатии на баннер.");
			FNC_IN  (BX_BannerProfile, Commercial, "Являются ли баннеры профиля коммерческими.");
			FNC_IN  (BX_BannerProfile, Banner, "Список баннеров, пользующихся данным профилем.");
			FNC_IN  (BX_BannerProfile, sBanner, "Список баннеров, пользующихся данным профилем в строковом виде.");
			FNC_IN  (BX_BannerProfile, Concept, "Концепты профиля.");
			FNC_IN  (BX_BannerProfile, State, "Состояние (вкл/выкл).");
			FNC_IN  (BX_BannerProfile, AltText, "Альтернативный текст.");
			FNC_IN  (BX_BannerProfile, SiteConceptInclude, "{class:Concept}Концепты сайтов, на которых показывать баннер.");
			FNC_IN  (BX_BannerProfile, SiteConceptExclude, "{class:Concept}Концепты сайтов, на которых НЕ показывать баннер.");
			FNC_IN  (BX_BannerProfile, SiteInclude, "Список разрешённых сайтов.");
			FNC_IN  (BX_BannerProfile, sSiteInclude, "Список имён разрешённых сайтов.");
			FNC_IN  (BX_BannerProfile, SiteExclude, "Список запрещённых сайтов.");
			FNC_IN  (BX_BannerProfile, sSiteExclude, "Список имён запрещённых сайтов.");
			FNC_IN  (BX_BannerProfile, ViewerIPEnable, "Разрешённые IP зрителей.");
			FNC_IN  (BX_BannerProfile, ViewerIPDisable, "Запрещённые IP зрителей.");
			FNC_IN  (BX_BannerProfile, ViewerConceptInclude, "{class:Concept}Концепты зрителей, которым показывать баннер.");
			FNC_IN  (BX_BannerProfile, ViewerConceptExclude, "{class:Concept}Концепты зрителей, которым НЕ показывать баннер.");
			FNC_IN  (BX_BannerProfile, UseLocalTime, "Применять ли расписание к локальному времени зрителя.");
			FNC_IN  (BX_BannerProfile, ScheduleTZOffset, "Часовой пояс расписания (если UseLocalTime==false).");
			FNC_IN  (BX_BannerProfile, ShowIfLocalUnknown, "Показывать ли баннер, если локальное время неизвестно (показывается с использованием ScheduleTZOffset).");
			FNC_IN  (BX_BannerProfile, Schedule, "Расписание - по биту на каждый час недели.");
			FNC_IN  (BX_BannerProfile, AutoOn, "Показывать в промежутке времени от ...");
			FNC_IN  (BX_BannerProfile, AutoOff, "до ...");
			FNC_IN  (BX_BannerProfile, RepeatCount, "Сколько раз показывать одному и тому же зрителю.");
			FNC_IN  (BX_BannerProfile, RepeatTime, "Показывать баннеры одному и тому же зрителю не чаще чем ...");
			FNC_IN  (BX_BannerProfile, CountTypeByShows, "Тип счета: на показы или на клики.");
			FNC_IN  (BX_BannerProfile, MaxDailyClicks, "Максимальное число кликов в день.");
			FNC_IN  (BX_BannerProfile, MaxDailyShows, "Максимальное число показов в день.");
      FNC        (BX_BannerProfile_Delete, "Удаление установок профиля баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_BannerProfile, objID, "Идентификатор объекта профиля баннера.");
			FNC_IN  (BX_BannerProfile, objPassword, "Пароль пользователя-владельца профиля.");

   // Banner
      FNC        (BX_Banner_New, "Создание баннера. Требуется OwnerID владельца, FileName баннера. Идентификатор созданного баннера возвращается в objID.  Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Banner, OwnerID, "{class:User}Идентификатор владельца баннера.");
			FNC_IN  (BX_Banner, objPassword, "Пароль пользователя-владельца баннера.");
			FNC_IN  (BX_Banner, FileName, "Имя баннера, с котором происходил upload.");
			FNC_IN  (BX_Banner, FileSize, "Размер файла баннера.");
			FNC_IN  (BX_Banner, Concept, "{class:Concept}Концепты, имеющие отношение к баннеру.");
			FNC_IN  (BX_Banner, Profile, "{class:BannerProfile}Профиль баннера (по умолчанию не установлен).");
			FNC_OUT (BX_Banner, objID, "Идентификатор объекта баннера.");
      FNC        (BX_Banner_GetData, "Получение параметров баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Banner, objID, "Идентификатор объекта баннера.");
			FNC_IN  (BX_Banner, objPassword, "Пароль пользователя-владельца баннера.");
			FNC_OUT (BX_Banner, OwnerID, "Идентификатор владельца баннера.");
			FNC_OUT (BX_Banner, FileName, "Имя баннера, с котором происходил upload.");
			FNC_OUT (BX_Banner, FileSize, "Размер файла баннера.");
			FNC_OUT (BX_Banner, UploadNo, "Количество повторных загрузок сайта.");
			FNC_OUT (BX_Banner, CreationTime, "Время создания объекта.");
			FNC_OUT (BX_Banner, sCreationTime, "Время создания объекта текстовом виде.");
			FNC_OUT (BX_Banner, VBN, "ID виртуальной сети, к которой принадлежит баннер.");
			FNC_OUT (BX_Banner, State, "Состояние баннера (выкл/вкл).");
			FNC_OUT (BX_Banner, Profile, "Идентификатор профиля баннера.");
			FNC_OUT (BX_Banner, Concept, "Концепты, имеющие отношение к баннеру.");
			FNC_OUT (BX_Banner, TotalShows, "Количество показов баннера.");
			FNC_OUT (BX_Banner, TotalClicks, "Количество нажатий на баннер.");
			FNC_OUT (BX_Banner, Allowed, "Информация пользователя разрешена модератором.");
			FNC_OUT (BX_Banner, ObjectState, "Состояние объекта: 0 - проверен 1 - новый 2 - изменено критическое поле 3 - изменён.");
      FNC        (BX_Banner_PutData, "Изменение параметров баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Banner, objID, "Идентификатор объекта баннера.");
			FNC_IN  (BX_Banner, objPassword, "Пароль пользователя-владельца баннера.");
			FNC_IN  (BX_Banner, FileName, "Имя баннера, с котором происходил upload.");
			FNC_IN  (BX_Banner, FileSize, "Размер файла баннера.");
			FNC_IN  (BX_Banner, UploadNo, "Количество повторных загрузок сайта.");
			FNC_IN  (BX_Banner, State, "Состояние баннера (выкл/вкл).");
			FNC_IN  (BX_Banner, Profile, "{class:BannerProfile}Идентификатор профиля баннера.");
			FNC_IN  (BX_Banner, Concept, "{class:Concept}Концепты, имеющие отношение к баннеру.");
      FNC        (BX_Banner_Delete, "Удаление баннера с указанным objID. Необходимо указать пароль пользователя-владельца objPassword.");
			FNC_IN  (BX_Banner, objID, "Идентификатор объекта баннера.");
			FNC_IN  (BX_Banner, objPassword, "Пароль пользователя-владельца баннера.");
   }
// Вызов обнаруженной функции или сообщение об ошибке.
   FNC_END;
}
//____________________________________________________________________________[]




