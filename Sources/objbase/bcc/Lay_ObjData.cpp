/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'                                   []
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Lay_ObjData.cpp                                           []
[] Date:            NA                                                        []
[] Author:          Roman V. Koshelev                                         []
[] Description:     Data contents for database objects                        []
[] __________________________________________________________________________ []
[]                                                                            []
[] Attention:       This file is auto created by compiling Lay.h-file         []
[]____________________________________________________________________________[]
*/

#define USES_OC_ALL

#define USES_key_arr_h
#define USES_ObjDriver_h

#include "../bcc/main.h"
#include "../bcc/OBD.h"
#include "Lay_ObjData.h"




char * className[]=
{
   "Test_sort"
};


// Конструктор
   OD_Test_sort::OD_Test_sort (bool bFieldsInit)
   {
      classID = OBJ_CLASS_ID_Test_sort;
      m_CoIndexPtr[0] = NULL;
      if (!bFieldsInit) return;

   }

// Деструктор
  OD_Test_sort::~OD_Test_sort () {classID = NA;}


// Создание внешнего набора ключей
   void OD_Test_sort::AddKeyVarForField (key_arr& ka, identifier fieldID)
   {
      switch (fieldID)
      {
         case 1: ka += d_n1;      break;
         case 2: ka += d_n2;      break;
         case 3: ka += d_n3;      break;
      }
   }


// Загрузка объекта с диска
   bool OD_Test_sort::LoadFromFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      file.Load ();

      size_t nOffset=0;

   // Проверка идентификатора
      identifier tmp_classID = (*(identifier*)(file+nOffset));
      nOffset += sizeof(identifier);
      if (tmp_classID!=classID)
      {
         SERVER_DEBUG_ERROR_3 ("Несовпадение типа при считывании объекта %d (тип!='%s'); tmp_classID==%d", objID, className[classID], classID);
         return false;
      }

   // int n1
      d_n1 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int n2
      d_n2 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);

   // int n3
      d_n3 = (*(int*)(file+nOffset));
      nOffset += sizeof(int);
      return true;
   }



// Подсчёт размера объекта для сохраения на диск
   size_t OD_Test_sort::CalculateSize ()
   {
      size_t n_size=0;

   // identifier classID
      n_size += sizeof (identifier);

   // int n1
      n_size += sizeof (int);

   // int n2
      n_size += sizeof (int);

   // int n3
      n_size += sizeof (int);

      return n_size;
   }

// Запись данных на диск
   bool OD_Test_sort::WriteToFile (identifier objID)
   {
      CFile file;
      if (!file.Exist(objID))
          return false;
      file.Open (objID);
      size_t n_size = CalculateSize ();
      file.Alloc (n_size);

      size_t nOffset=0;

   // identifier classID
      (*(identifier*)(file+nOffset)) = classID;
      nOffset += sizeof (identifier);

   // int n1
      (*(int*)(file+nOffset)) = d_n1;
      nOffset += sizeof (int);

   // int n2
      (*(int*)(file+nOffset)) = d_n2;
      nOffset += sizeof (int);

   // int n3
      (*(int*)(file+nOffset)) = d_n3;
      nOffset += sizeof (int);
      file.Save();
      return true;
   }


// Отладочная печать
   bool OD_Test_sort::DebugPrint (string& dbg, identifier objID)
   {
      string SSS;
      dbg += "\n\n------------------------------------------\n";
      SSS.Format ("[%s:%d]\n\n", className[OBJ_CLASS_ID_Test_sort], objID);
      dbg += SSS;

   // int n1
      SSS.Format ("n1 = %d\n", d_n1);
      dbg += SSS;

   // int n2
      SSS.Format ("n2 = %d\n", d_n2);
      dbg += SSS;

   // int n3
      SSS.Format ("n3 = %d\n", d_n3);
      dbg += SSS;
      dbg += "\n";
      return true;
   }

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
