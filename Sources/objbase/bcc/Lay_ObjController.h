/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjController.h                                       []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Controlers for database objects                           []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/

#ifndef Lay_ObjController_h
#define Lay_ObjController_h


#include "./../bcc/main.h"
#include "./../bcc/OBD.h"
#include "./../bcc/Object.h"
#include "Lay_ObjData.h"








#ifdef  USES_OC_ALL
#define USES_OC_Test_sort
#endif
#ifdef USES_OC_Test_sort
//------------------------------------------------------------------------------[]
// 
// Контроллер объектов базы данных класса "Test_sort"
// 
class OC_Test_sort: public OC_Object <OC_Test_sort, OD_Test_sort>
{
// Конструктор по умолчанию -- контроллер не установлен на объект!
   public: OC_Test_sort  ();// Конструктор по идентификатору -- загружается объект из базы
   public: OC_Test_sort  (identifier objID);
// Конструктор копирования из другого контроллера
   public: OC_Test_sort  (const OC_Test_sort& from);
// Деструктор контроллера объекта
   public: ~OC_Test_sort ();

// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_sort& operator= (const OC_Test_sort& from);
// 1. Копирование (размножение, дублирование) контроллеров одного оъекта
// 2. Загрузка объекта по идентификатору
   public: OC_Test_sort& operator= (identifier objID);

// Инициализация хитрожопых полей CSmartField<...>
   protected: void InitSmartFields();


// Копирование данных из другого контроллера
   public: void CopyDataFrom (OC_Test_sort& from);


// Копирование данных в другой контроллер
   public: void CopyDataTo (OC_Test_sort& to);

// Копирование данных из другого контроллера: to << from;
   public: OC_Test_sort& operator << (OC_Test_sort& from);

// Копирование данных в другой контроллер: from >> to;
   public: OC_Test_sort& operator >> (OC_Test_sort& from);

// Поле:   int Test_sort::n1
   public: CSmartField      <OD_Test_sort, int        >    m_n1;
// Поле:   int Test_sort::n2
   public: CSmartField      <OD_Test_sort, int        >    m_n2;
// Поле:   int Test_sort::n3
   public: CSmartField      <OD_Test_sort, int        >    m_n3;

// Установить текущий индекс по его идентификатору
// Возвращает старый индекс
   identifier SetIndex (identifier newIndex);
// Получить идентификатор текущего индекса
   identifier GetIndex ();

// Установить текущий индекс по набору полей [n1, -n2, n3]
   public: void SetIndex_n1__n2_n3 ();
};
#endif
//------------------------------------------------------------------------------[]



#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
