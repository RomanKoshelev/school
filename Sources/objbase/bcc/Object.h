/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain                                                 []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            Object.h																	[]
[] Date:            14.04.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     ������� ����� ��� ���� ������������ �������� ���� ������	[]
[]____________________________________________________________________________[]
*/
#ifndef Object_h
#define Object_h

#include "SmartField.h"

/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` OC_Object
[]                                                                            []
[]____________________________________________________________________________[]
*/
template <class OC> class OC_Object
{
// ��� ����� ��������-������������.
// ������������ ����������� (�� "������") ����� ����� ��������� --
// ������ � ���������. � ������ ������ ���������� �����
// ������������������� � ������� ����������� ��������������.
// �� ������ -- ���������� ���������� �� ������, ��������� 
// ��������� ������ � ��������� -- Find, Next, Prev, ....
// ��������: ����c� OC_xxx ������������� ��������� ������������ ���� ������.
   void About_class_OC_Object (){};

// ������������� ������ �������
   public:    identifier   classID;

// ���������� ������������� ��� ������� � ������ ����� OBD
   protected: OBD_pointer  coPtr;

// ���������� �� ������������� �������
   protected: CIndexInfo   curIndexInfo;

// �������� ���������� � ��������� ������� �������-������
   protected: void Release (OBD_pointer _coPtr=NULL)
	{
      if(_coPtr!=NULL)
		{
         OBD_ReleaseObject (classID, _coPtr);
		}
      else if(coPtr!=NULL) 
		{
			OBD_ReleaseObject (classID, coPtr);
			coPtr = NULL;
      }
   }

// ������� ���������� = Release
   public: void Close ()
	{
		Release();
   }


//RVK:>>>
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ����� ������																					[]
[]                                                                            []
[]____________________________________________________________________________[]
*/

// ���������� ������ � ������.
// ���� ������ �������� -- �������� � ������, ����� -- �� �����.
   public: void DebugPrint(string& dbg) const {OBD_DebugPrint(classID, dbg, coPtr);};
// ���������� ������ � ������.
// ���� ������ �������� -- �������� � ������, ����� -- �� �����.
   public: void DebugPrint() const {string dbg; OBD_DebugPrint(classID, dbg, coPtr); dbg.Print ();};

// �������� ����������� ������������� �����������
   public: bool IsValid () const {return OBD_IsObjectValid (classID, coPtr);};

// �������� ������������� ������� ������� ������ � ��������� ���������������
   public: bool Exist (identifier objID) const {return OBD_Exist (classID, objID);};

// �������� ����������� ������������� �����������
   public: operator bool () const {return IsValid ();};

// ���������� ���� ���� �� ���� (������� � �������)
// ��� ������ ���������� ����� ����������� ������� ~266 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������.
	public: void SaveAllBase ()  {OBD_SaveAllData ();}

// ���������� ���� ���������� �������� � �������� �� ����. �������� ������� 
// ��� ���������� ������. �� ������� ����������� �������� ��� -- ����� �������� � ����� ������.
// ��� ������ ���������� ����� ����������� ������� ~498 (266+232) ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������.
   public: void ReloadAllBase () const {OBD_ReloadAllBase();};

// ������ ��������� � �������� �������.
// ��� ������ ���������� ����� ����������� ������� ~7.7 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������.
   public: void FlushFileSystem () const {theFileDriver.flush ();};	


// 1. ��� ����������� ��������� �� ���� ������ ��� ��� �� ��������� �� �� ���� ������.
// 2. ��������� �������������� ����������� � ������-���������������.
// 3. �������� ����� �� �������� ������� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator== (const OC& to) {return coPtr==to.coPtr;};
// 1. ��� ����������� ��������� �� ���� ������ ��� ��� �� ��������� �� �� ���� ������.
// 2. ��������� �������������� ����������� � ������-���������������.
// 3. �������� ����� �� �������� ������� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator== (identifier objID)  {return objID == (coPtr? GetObjectID(): UNKNOWN);};

// 1. ��������� ������������ -- ��� ����������� ��������� �� 
// ������ ������� ��� ���� �� ��� ��������� �� ������, � ������ ���
// 2. ��������� �������������� ����������� � ������-���������������
// 3. �������� ����� �� �������� ������� �� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator!= (const OC& to) {return coPtr!=to.coPtr;};
// 1. ��������� ������������ -- ��� ����������� ��������� �� 
// ������ ������� ��� ���� �� ��� ��������� �� ������, � ������ ���
// 2. ��������� �������������� ����������� � ������-���������������
// 3. �������� ����� �� �������� ������� �� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator!= (identifier objID)  {return objID != (coPtr? GetObjectID(): UNKNOWN);};

// �������� ������������� ��������������� �������
   public: operator identifier () const        {return coPtr? GetObjectID(): UNKNOWN;};

// �������� ������� �� ��������������
   public: void Open (identifier objID) 
	{
		if (coPtr!=NULL && (objID==GetObjectID())) 
			return; 
		Release();
		if (objID==NA) 
		{
			SERVER_DEBUG_ERROR_1 ("OC_Object::Open (NA) -- ������� ��������� ����������� ������ ������ '%s'", GetClassName ());
			return; 
		}
		coPtr=OBD_GetObject(classID,objID);
	}






// �������������� ���������� ������� �� ����
   public: void Save () {if (coPtr) OBD_SaveObject(classID,coPtr);}


// ������� ����� ������� � �������� ��� � ����.
// ���������� ������������� ������ ������� � �������������
// �� ���� ������ ����������. 
// * ���������� � �������� ������-������!
   public: identifier New () {Release(); coPtr=OBD_CreateObject(classID); return GetObjectID();};

// 1. ������� ������ ������� ����������� �� ����.
// 2. ������� ������ � �������� ���������������.
// 3. ������� ��� ������� ��������������� ����� * ������ ��� ������������� �������
// * ���������� � �������� ������-������
   public: void Delete () {OBD_DeleteObject(classID,coPtr); if (!IsValid()) Release();};
// 1. ������� ������ ������� ����������� �� ����.
// 2. ������� ������ � �������� ���������������.
// 3. ������� ��� ������� ��������������� ����� * ������ ��� ������������� �������
// * ���������� � �������� ������-������
   public: void Delete (identifier objID) { OBD_DeleteObject(classID,objID); if (!IsValid()) Release();};


// �������� ������������� ��������������� �������.
   public: identifier GetObjectID () const {return coPtr? OBD_GetObjectID(classID, coPtr): UNKNOWN;};

// �������� ������������� ������ ��������������� �������.
   public: identifier GetClassID () const {return coPtr? OBD_GetClassID(classID, coPtr): classID;} 
// �������� ��� ������ ��������������� �������.
   public: const char * GetClassName () const {return className[GetClassID()];}




//RVK:>>>
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` ������ ��� ������������� ��������														[]
[]                                                                            []
[]____________________________________________________________________________[]
*/

// �������� ������ ��������������� ���� �������� ������� ������.
// ���� ����� ����, ������� ��������� ������ ���������������� 
// ���� ��������, ��������������� �����. 
// ������ �������� -- CPtr<identifier> id_list;
// �������������� ����� ������������� � ������������ � ������� ��������.
// * ������ ��� ������������� �������
   public: void GetClassIdList (identifier_arr& id_list, key_arr* ka=NULL) {OBD_GetClassIdList(id_list, classID, ka, curIndexInfo);};

// ������� ��� ������� ������� ������ �� ����.
// ��� ������ ���������� ����� ����������� ������� ~41 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������.
// * ������ ��� ������������� �������
// * ���������� � �������� ������-������
   public: void DeleteClassObjects () {key_arr ka; OBD_DeleteObject(classID,ka,curIndexInfo); if (!IsValid()) Release();};

// 1. ������� ������ ������� ����������� �� ����.
// 2. ������� ������ � �������� ���������������.
// 3. ������� ��� ������� ��������������� ����� * ������ ��� ������������� �������
// * ���������� � �������� ������-������
   public: void Delete (key_arr& ka)						{ OBD_DeleteObject(classID,ka,curIndexInfo); if (!IsValid()) Release();};

// �������������� ���������� �������� ������� �� ����
// * ������ ��� ������������� �������
   public: void SaveCurIndex () {OBD_SaveIndexToFile(classID,curIndexInfo);}
// �������� ������������� ������� ������� �� �������� �������
// * ������ ��� ������������� �������
   public: identifier First() const {return OBD_FirstIDInIndex (classID, curIndexInfo);};

// �������� ������������� ���������� ������� �� �������� �������
// * ������ ��� ������������� �������
   public: identifier Last() const {return OBD_LastIDInIndex (classID, curIndexInfo);};

// �������� ����� �� �������� ������� ������ �����-���������
// * ������ ��� ������������� �������
   public: bool operator< (key_arr& ka)  {return Compare (ka)< 0;};

// �������� ����� �� �������� ������� ������ ��� ����� �����-���������
// * ������ ��� ������������� �������
   public: bool operator<=(key_arr& ka)  {return Compare (ka)<=0;};

// �������� ����� �� �������� ������� ������ �����-���������
// * ������ ��� ������������� �������
   public: bool operator> (key_arr& ka)  {return Compare (ka)> 0;};

// �������� ����� �� �������� ������� ������ ��� ����� �����-���������
// * ������ ��� ������������� �������
   public: bool operator>=(key_arr& ka)  {return Compare (ka)>=0;};

// ��������� �������� ����� �� �������� ������� � ������-����������
// * ������ ��� ������������� �������
   public: int  Compare   (key_arr& ka)  {return coPtr? OBD_CompareToKeyVarArr (classID,curIndexInfo,coPtr,ka): -1;};

// 1. ��� ����������� ��������� �� ���� ������ ��� ��� �� ��������� �� �� ���� ������.
// 2. ��������� �������������� ����������� � ������-���������������.
// 3. �������� ����� �� �������� ������� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator== (key_arr& ka)  {return Compare (ka)==0;};

// 1. ��������� ������������ -- ��� ����������� ��������� �� 
// ������ ������� ��� ���� �� ��� ��������� �� ������, � ������ ���
// 2. ��������� �������������� ����������� � ������-���������������
// 3. �������� ����� �� �������� ������� �� ����� �����-��������� * ������ ��� ������������� �������
   public: bool operator!= (key_arr& ka)  {return Compare (ka)!=0;};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// ����� �� �������
//
//RVK:>>>

// ����� ������ � ������� ������� �� ������ ������ 'keyarr'.
// ��� ��������� ������ ��������� ������ � ������ ������� ��� ������ ����� ������:
//      key_arr ka; // ������ ���� = [���, �������, �������]
//      ka += "����"; ka += "������"; ka += 28;
//      Men.Find (ka); // ������� ���� ������� 28-� ��� � ������ �����.
//      Men.Find (ka, true); // ������� ���� ������� 28-� ��� ��� ���� ������� 27-� ��� 
//      // ��� ���� ���������� 92 ��� ��� ��������� ��������� 13 ���.
// ���� ����� ������ 'keyarr' ��������, ������������ ����, �� ���������� � 'keyarr':
//      ka += "����"; ka += "������";
//      Men.Find (ka); // ������� ������� ����������� ���� �������, ������
//      // ��� ������� ����� ����������� ����� ���� ��������� ����� ��������.
// * ������ ��� ������������� �������
   public: bool Find (key_arr& ka, bool bInexact=false) {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexFindObject  (classID,curIndexInfo,ka,bInexact); if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� ��������� ������ �� �������� �������.
// ���� ������ ���� (������ ��� ��������), ������� �� ��������� ������ � ��������������� ������.
// ���� ������ �������� bUnique=true, ������� �� ��������� ���������� �� ������� ������.
// * ������ ��� ������������� �������
   public: bool GoNext (key_arr* pka=NULL, bool bUnique=false) 
	{
		OBD_pointer _coPtr=coPtr; 
		coPtr=OBD_IndexNextObject  (classID,curIndexInfo,coPtr,pka,bUnique);   
		if(_coPtr)
			Release (_coPtr); 
		return coPtr!=NULL;
	}

// ������� �� ���������� ������ �� �������� �������.
// ���� ������ ���� (������ ��� ��������), ������� �� ���������� ������ � ��������������� ������.
// ���� ������ �������� bUnique=true, ������� �� ���������� ���������� �� ������� ������.
// * ������ ��� ������������� �������
   public: bool GoPrev (key_arr* pka=NULL, bool bUnique=false) {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexPrevObject  (classID,curIndexInfo,coPtr,pka,bUnique);   if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� �������� ������� �� ��������� ������, ������� ��� �� ����.
// * ������ ��� ������������� �������
   public: bool GoNextSame (key_arr* pka=NULL, bool bUnique=false) {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexNextObject  (classID,curIndexInfo,coPtr,pka,bUnique,true);   if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� �������� ������� �� ���������� ������, ������� ��� �� ����.
// * ������ ��� ������������� �������
   public: bool GoPrevSame (key_arr* pka=NULL, bool bUnique=false) {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexPrevObject  (classID,curIndexInfo,coPtr,pka,bUnique,true);   if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� ������ ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool GoFirst() {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexFirstObject (classID,curIndexInfo,coPtr);       if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� ��������� ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool GoLast () {OBD_pointer _coPtr=coPtr; coPtr=OBD_IndexLastObject  (classID,curIndexInfo,coPtr);       if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� ��������� ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool operator++() {return GoNext();}
// ������� �� ��������� ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool operator++(int) {return GoNext();}

// ������� �� ���������� ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool operator--() {return GoPrev();}
// ������� �� ���������� ������ �� �������� �������
// * ������ ��� ������������� �������
   public: bool operator--(int) {return GoPrev();}


// ������� �� �������� ������� �� ��������� ������, ������� ������ ����
// (���������� ����� ��� ���������� � ������ �������� ������� �������).
// * ������ ��� ������������� �������
   public: bool GoNextUnique () {OBD_pointer _coPtr=coPtr; key_arr ka; coPtr=OBD_IndexNextObject  (classID,curIndexInfo,coPtr,&ka,true);   if(_coPtr)Release(_coPtr); return coPtr!=NULL;}

// ������� �� �������� ������� �� ���������� ������, ������� ������ ����
// (���������� ����� ��� ���������� � ������ �������� ������� �������).
// * ������ ��� ������������� �������
   public: bool GoPrevUniqeu () {OBD_pointer _coPtr=coPtr; key_arr ka; coPtr=OBD_IndexPrevObject  (classID,curIndexInfo,coPtr,&ka,true);   if(_coPtr)Release(_coPtr); return coPtr!=NULL;}




// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//
// �������� �� �������
//
//RVK:>>> 



// ����� ���������� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ���������� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
// ��� ������ ���������� ����� ����������� ������� ~22.6 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������, ��� �������� ��� ����� (�� ����� �������).
   public: size_t GetIndexUniqueNum (key_arr& ka1, key_arr& ka2) const {
				  return OBD_GetIndexNumForKey(classID,curIndexInfo,ka1,ka2,true);}
// ����� ���������� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ���������� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
// ��� ������ ���������� ����� ����������� ������� ~22.6 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������, ��� �������� ��� ����� (�� ����� �������).
   public: size_t GetIndexUniqueNum (key_arr& ka) const {
				  key_arr ka2;
				  ka2.Init();
				  return OBD_GetIndexNumForKey(classID,curIndexInfo,ka,ka2,true);}
// ����� ���������� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ���������� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
// ��� ������ ���������� ����� ����������� ������� ~22.6 ������ @PII 233 ��� 4M ��������
// � ������������ �������� ����� � ����� ��������, ��� �������� ��� ����� (�� ����� �������).
   public: size_t GetIndexUniqueNum () const {
				  key_arr ka1; 
				  key_arr ka2; 
				  return OBD_GetIndexNumForKey(classID,curIndexInfo,ka1,ka2,true);}

// ����� ����� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ����� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
   public: size_t GetIndexTotalNum (key_arr& ka1, key_arr& ka2) const {
				  return OBD_GetIndexNumForKey(classID,curIndexInfo,ka1,ka2,false);}
// ����� ����� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ����� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
   public: size_t GetIndexTotalNum (key_arr& ka) const {
				  key_arr ka2;
				  ka2.Init();
				  return OBD_GetIndexNumForKey(classID,curIndexInfo,ka,ka2,false);}
// ����� ����� �������� � �������� ������ � ������� �������.
// ���� ���� �� ����� -- ����� ����� � ������� ������� (��� 
// ������� ������� -- ����� �������� ������� ������)
// ���� ������� ��� ����� -- ����� ��������, ��� ����� �����
// � ��������� ������-����������.
// * ������ ��� ������������� �������
   public: size_t GetIndexTotalNum () const {return OBD_IndexTotalNum (classID);}

// �������� ����� ����� �������� ������� ������
// * ������ ��� ������������� �������
   public: size_t GetTotalNum() const {return OBD_IndexTotalNum (classID);};
};
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/