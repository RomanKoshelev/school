/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the project 'ObjBase'                                    []
[] Copyright (C) 1999-2000 by the author(s) -- see below.                     []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjDriver.h                                               []
[] Date:            01.04.2000                                                []
[] Author:          Roman V. Koshelev, Alex Vershinin                         []
[] Description:     Object-control layer													[]
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
#ifndef ObjDriver_H
#define ObjDriver_H


#define	SRC_LAYOUT_FILE		"./../Lay.h"
#define	SRC_INTERFACE_FILE	"./../Interface.h"

#define	MAX_KEY_NUM_IN_INDEX  16

void AVTree_Write_Start	(identifier fileID, size_t nSize, size_t nBlockSize);
bool AVTree_Write			(BYTE * pData);
void AVTree_Write_End	();

typedef	key_arr CObjIndex_AVTree_Item;
int		CompareFunction_CObjIndex_AVTree_Item (pbyte& a, pbyte& b);
typedef	IT_AVTree <CObjIndex_AVTree_Item, pbyte, pbyte CObjIndex_AVTree_Item::*> CObjIndex_AVTree;



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Описание формата интерфесных функций                                      []                                    
[]                                                                            []
[]____________________________________________________________________________*/

/*______________________________________________________________________________
[]                                                                            []
[]` INTERFACE_FORMAT_ARG                                                      []                    
[]                                                                            */
struct INTERFACE_FORMAT_ARG
{
	string Name;
	string Description;

	INTERFACE_FORMAT_ARG ();

	INTERFACE_FORMAT_ARG (const INTERFACE_FORMAT_ARG& from);

	INTERFACE_FORMAT_ARG& operator= (const INTERFACE_FORMAT_ARG& from);
};
//____________________________________________________________________________[]


/*______________________________________________________________________________
[]                                                                            []
[]` INTERFACE_FORMAT                                                          []                
[]                                                                            */
struct INTERFACE_FORMAT
{
	string Description;
	string ObjName;
	string Action;

	CPtr<INTERFACE_FORMAT_ARG> InArg;
	CPtr<INTERFACE_FORMAT_ARG> OutArg;

	INTERFACE_FORMAT ();
	INTERFACE_FORMAT (const INTERFACE_FORMAT& from);

	INTERFACE_FORMAT& operator= (const INTERFACE_FORMAT& from);

	void Erase();
};
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` CObjIndex																						[]
//                                                                            []
struct CObjIndex
{
	CPtr<identifier>		fieldArr;
	CPtr<bool>				fieldArr_ascend; // Сортировать по возрастанию.

	identifier				fileID;
	CObjIndex_AVTree		AVTree;
	bool						bChanged;

	CObjIndex& operator= (const CObjIndex& from)
	{
		fieldArr				= from.fieldArr;
		fieldArr_ascend	= from.fieldArr_ascend;
		fileID				= from.fileID;
		bChanged				= false;
		return *this;
	}
	CObjIndex (const CObjIndex& from): AVTree (&CObjIndex_AVTree_Item::m_pData, CompareFunction_CObjIndex_AVTree_Item)
	{
		fieldArr				= from.fieldArr;
		fieldArr_ascend	= from.fieldArr_ascend;
		fileID				= from.fileID;
		bChanged				= false;
	}
	void Erase ()
	{
		bChanged	= false;
		fileID	= UNKNOWN;
		fieldArr.Erase();
		fieldArr_ascend.Erase();
		AVTree.RemoveAll();
	}

	size_t Save ();
	size_t Load ();

	CObjIndex () : AVTree (&CObjIndex_AVTree_Item::m_pData, CompareFunction_CObjIndex_AVTree_Item)
	{
		Erase  ();
	};
};
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//` CFieldFormat																					[]
//                                                                            []
struct CFieldFormat
{
	FIELD_TYPE			type;
	bool					isArray;
	string				name;
	
	CPtr<identifier>	indexArr;
	
	string				defValue;
	
	void Erase ()
	{
		type = FT_nothing;
		isArray = false;
		name = "";
		indexArr.Erase();
		defValue = "";
	}
	CFieldFormat (){Erase();};
	CFieldFormat& operator= (const CFieldFormat& from)
	{
		type			= from.type;
		isArray		= from.isArray;
		name			= from.name;
		indexArr		= from.indexArr;
		defValue		= from.defValue;
		
		return *this;
	}
	CFieldFormat (const CFieldFormat& from)
	{
		type			= from.type;
		isArray		= from.isArray;
		name			= from.name;
		indexArr		= from.indexArr;
		defValue		= from.defValue;
	}
};
//____________________________________________________________________________[]










//______________________________________________________________________________
//                                                                            []
//` CObjFormat																						[]
//                                                                            []
struct CObjFormat
{
	string					name;
	bool						isMaster;
	bool						isVirtual;
	CPtr<CFieldFormat>	fieldArr;
	CPtr<CObjIndex>		indexArr;
	CPtr<string>			_parentArr;


	void Erase ()
	{
		_parentArr.Erase();
		fieldArr.Erase();
		indexArr.Erase();
		name = "";
		isMaster = false;
		isVirtual= false;
	}

	identifier GetFieldIndex (string& name)
	{
		identifier nf=0;
		for (CPtr<CFieldFormat>::Iterator f=fieldArr.begin(); f!=fieldArr.end(); f++, nf++)
		{
			if (f->name==name)
				return nf;
		}	
		return UNKNOWN;
	}

	CObjFormat () {Erase();}
	
	CObjFormat& operator= (const CObjFormat& from)
	{
		name			= from.name;
		isMaster		= from.isMaster;
		isVirtual	= from.isVirtual;
		fieldArr		= from.fieldArr;
		indexArr		= from.indexArr;
		_parentArr	= from._parentArr;
		
		return *this;
	}
	CObjFormat (const CObjFormat& from)
	{
		name			= from.name;
		isMaster		= from.isMaster;
		isVirtual	= from.isVirtual;
		fieldArr		= from.fieldArr;
		indexArr		= from.indexArr;
		_parentArr	= from._parentArr;
	}
};
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CObjDriver
[]                                                                            []
[]____________________________________________________________________________[]
*/
class CObjDriver
{
	protected:	identifier GetFormatIndex (string& name)
	{
		identifier nf=0;
		for (CPtr<CObjFormat>::Iterator f=m_FormatArr.begin(); f!=m_FormatArr.end(); f++, nf++)
		{
			if (f->name==name)
				return nf;
		}	
		return UNKNOWN;
	}

// Набор форматов для каждого класса
	public:	CPtr<CObjFormat> m_FormatArr;

// Внутренняя функция для получения информации об индексе
	public: CObjIndex* GetIndexPtr (identifier classID, identifier indexID);

// Внутренняя функция для получения информации о поле
	public: CFieldFormat* GetFieldPtr (identifier classID, identifier fieldID);

// Внутренняя функция для очистки форматов
	protected:	void Erase ()
	{
		for (CPtr<CObjFormat>::Iterator objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
		{
			objtype->Erase ();
		}
		m_FormatArr.Erase();
	}

	protected:	void SaveFormat							();
	protected:	void LoadFormat							();
	protected:	void Create_ObjController_h			(string& header);
	protected:	void Create_ObjController_cpp			(string& header);
	protected:	void Create_ObjData_h					(string& header);
	protected:	void Create_ObjData_cpp					(string& header);
	protected:	void Create_Stubs_h						(string& header);
	protected:	void CompileInterface					(CPtr<INTERFACE_FORMAT>& Format, const char * sFile, string& Prefix);
	protected:	void Create_Interface_Dispatch_cpp	(string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix);
	protected:	void Create_Interface_Auto_h			(string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix);
	protected:	void Create_Interface_Auto_cpp		(string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix);
	protected:	void SaveIndexes ();
	protected:	void LoadIndexes ();
	protected:	void Init ();

	
	//______________________________________________________________________________
	//                                                                            []
	//` И Н Т Е Р Ф Е Й С 																			[]
	//                                                                            []
		public: CObjDriver			(const char *str)	{Compile (str, true);}
		public: CObjDriver			()	{Init ();}
		public: ~CObjDriver			()	
		{
			SERVER_DEBUG_TEXT ("Драйвер базы данных завершил работу");
			SaveIndexes ();
		}

		#ifdef ZOOB_UTILS
	// Загрузка и печать формата
		public: void Verify	();
		#endif

	// Печатать формат базы данных 
		public: void PrintFormat	();

	// Компилировать формат базы данных (*.lay)
	// Второй параметр указывает на необходимость генерации текстов C++
		public: bool Compile (const char * fileName, bool bCreateCPP=false);
	//____________________________________________________________________________[]

};
//____________________________________________________________________________[]


//----------------------------------------------------------------------------[]

extern CObjDriver theObjDriver;

//----------------------------------------------------------------------------[]


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/
