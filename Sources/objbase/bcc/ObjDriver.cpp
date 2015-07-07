/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjDriver.cpp															[]
[] Date:            14.03.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Object-control layer													[]
[]____________________________________________________________________________[]
*/
#include "ObjDriver_inc.h"

#ifdef WIN32  // WINDOWS
	#ifdef LAY_COMPILER_PROJECT
		bool PRINT_PROGRESS		= true;
		bool PRINT_PROGRESS_IND = false;
		bool PRINT_FORMAT			= false;
	#else
		bool PRINT_PROGRESS		= false;
		bool PRINT_PROGRESS_IND = false;
		bool PRINT_FORMAT			= false;
	#endif
#else // UNIX
	#ifdef LAY_COMPILER_PROJECT
		bool PRINT_PROGRESS		= true;
		bool PRINT_PROGRESS_IND = false;
		bool PRINT_FORMAT			= false;
	#else
		bool PRINT_PROGRESS		= false;
		bool PRINT_PROGRESS_IND = false;
		bool PRINT_FORMAT			= false;
	#endif
#endif


//----------------------------------------------------------------------------[] 
#define	PRINT_CREATION_PERCENT																\
	int Percent = objtype.GetIndex()*100/m_FormatArr.GetSize();						\
	if (PRINT_PROGRESS) 																			\
	{																									\
		char C='%';																					\
		printf ("\r                                                          ");\
		printf ("\r    %3d%c:  %s",Percent, C, objtype->name.c_str());			   \
	}
//----------------------------------------------------------------------------[] 

bool b_CREATE_INTERFACE_ONLY	= false;
bool bDoDbgStop					= false;
//----------------------------------------------------------------------------[] 
#define COMPILE_ERROR(sError)																	\
	{																									\
	if (bDoDbgStop) DBG_STOP_ASK;																\
	char SyntaxError[1024];																		\
	sprintf (SyntaxError, "Компиляция базы: '%s' (%d:%d): %s", 						\
				fileName, nLine, nPos, sError);												\
	SERVER_DEBUG_ERROR (SyntaxError);														\
	return false;																					\
	}
//----------------------------------------------------------------------------[] 


//______________________________________________________________________________
//                                                                            []
//` ENCODE_STRING																					[]
//                                                                            []
void ENCODE_STRING (size_t size, char * str)
{
	for (size_t i=0; i<size; i++) 
	{
		str[i] = (char) ((str[i] + 1278 + size*size + i*i*size) ^ (i+63) ^ (size>>i));
	}
}
//----------------------------------------------------------------------------[] 
void DECODE_STRING (size_t size, char * str)
{
	for (size_t i=0; i<size; i++) 
	{
		str[i] = (char) ((str[i]^(i+63)^(size>>i)) - 1278 - i*i*size - size*size);
	}
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Init 																							[]
//                                                                            []
void CObjDriver::Init ()
{
	SERVER_DEBUG_TEXT ("Драйвер базы данных приступил к работе");

	LoadFormat ();
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Загрузка и печать формата																	[]
//                                                                            []
#ifdef LAY_COMPILER_PROJECT
void CObjDriver::Verify	() 
{
	if (PRINT_PROGRESS && !PRINT_FORMAT)
		printf ("\nVerification...");
	LoadFormat(); 
	if (PRINT_PROGRESS && PRINT_FORMAT) 
		PrintFormat();
	if (PRINT_PROGRESS && !PRINT_FORMAT)
	{
		printf ("\r                          \r");
		puts ("OK\n\n");
	}
};
#endif

//______________________________________________________________________________
//                                                                            []
//` PrintFormat 																					[]
//                                                                            []
void CObjDriver::PrintFormat ()
{
	int	i=0;
	for (CPtr<CObjFormat>::Iterator objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		puts ("\n------------------------------------------------------------");
		printf (objtype->isMaster? "master ": "");
		printf ("class ");
		printf (objtype->name.c_str());
		printf (":\n{\n");
		for (CPtr<CFieldFormat>::Iterator field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++)
		{
			char * FT_NAME []= {"id       ", "int      ", "byte     ", "bool     ", "float    ", "string   "};

			printf("   ");
			printf(FT_NAME[field->type]);
			printf(field->name.c_str());
			printf(field->isArray? "[]": "");

			if (field->defValue!="")
			{
				printf (" = ");
				if (field->type==FT_string)
					printf ("\"");
				printf("%s", field->defValue.c_str());
				if (field->type==FT_string)
					printf ("\"");
			}

			printf (";");

			if (field->indexArr.GetSize()>0) 
			{
				printf (" // [");

				int N = field->indexArr.GetSize();
				for (i=0; i<N; i++)
				{
					printf ("%d", field->indexArr[i]);
					if ((N>1) && (i<N-1))
						printf (", ");
				}
				printf ("]");
			}
			printf ("\n");
		}

		if (objtype->indexArr.GetSize()) 
			printf ("\n");
		for (CPtr<CObjIndex>::Iterator index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++)
		{
			printf("   index    [");

			size_t N = index->fieldArr.GetSize();
			for (size_t k=0; k<N; k++)
			{
				identifier	fid	= (identifier) index->fieldArr			[k];
				bool			bAsc	= (bool)			index->fieldArr_ascend	[k];
				
				printf ("%s%s", bAsc? "": "-", objtype->fieldArr[fid].name.c_str());

				printf (":%d", fid);

				if ((N>1) && (k<N-1))
					printf (", ");
			}
			printf("]; // fileID = %d", index->fileID);
			printf("\n");
		}

		printf ("}");
		if (PRINT_PROGRESS) puts ("\n------------------------------------------------------------\n\n\n\n");
	}
}
//______________________________________________________________________________
//                                                                            []
//` SaveFormat																						[]
//                                                                            []
void CObjDriver::SaveFormat ()
{
	int	i=0;

	CFile formatFile (FILE_ID_LAYOUT);

	formatFile.WriteData (m_FormatArr.GetSize());
	for (CPtr<CObjFormat>::Iterator objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		formatFile.WriteData (objtype->isMaster);
		formatFile.WriteData (objtype->name);

		formatFile.WriteData (objtype->fieldArr.GetSize());
		for (CPtr<CFieldFormat>::Iterator field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++)
		{
			formatFile.WriteData (field->type);
			formatFile.WriteData (field->name);
			formatFile.WriteData (field->isArray);
			formatFile.WriteData (field->defValue);
			
			formatFile.WriteData ((CPtr_info)(field->indexArr));
		}

		formatFile.WriteData (objtype->indexArr.GetSize());
		for (i=0; i< objtype->indexArr.GetSize(); i++)
		{
			formatFile.WriteData ((int)objtype->indexArr[i].fileID);
			formatFile.WriteData ((CPtr_info)(objtype->indexArr[i].fieldArr));
			formatFile.WriteData ((CPtr_info)(objtype->indexArr[i].fieldArr_ascend));
			objtype->indexArr[i].bChanged = true;
			objtype->indexArr[i].Save();
		}
	}
	theFileDriver.flush();
}
//______________________________________________________________________________
//                                                                            []
//` LoadFormat																						[]
//                                                                            []
void CObjDriver::LoadFormat ()
{
	if	(CFile::GetMaxSize (FILE_ID_LAYOUT) < 16)
	{
		Compile	(SRC_LAYOUT_FILE);
	}

	Erase ();
	int	i=0,j=0;

	CFile formatFile;
	formatFile.Open(FILE_ID_LAYOUT);

	int							formatNumber;
	formatFile.ReadData		(formatNumber);

	for (i=0; i<formatNumber; i++)
	{
		CObjFormat format;

		formatFile.ReadData		(format.isMaster);
		formatFile.ReadData		(format.name);

		int							fieldNumber;
		formatFile.ReadData		(fieldNumber);

		for (j=0; j<fieldNumber; j++)
		{
			CFieldFormat field;

			formatFile.ReadData	((int&)field.type);
			formatFile.ReadData	(field.name);
			formatFile.ReadData	(field.isArray);
			formatFile.ReadData	(field.defValue);
			
			formatFile.ReadData	(field.indexArr);
			format.fieldArr.Add	(field);
		}

		int							indexNumber;
		formatFile.ReadData		(indexNumber);

		for (j=0; j<indexNumber; j++)
		{
			CObjIndex				index;

			formatFile.ReadData (index.fileID);
			formatFile.ReadData (index.fieldArr);
			formatFile.ReadData (index.fieldArr_ascend);

			format.indexArr.Add (index);
		}
		m_FormatArr.Add (format);
	}
	LoadIndexes ();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` SaveIndexes																					[]
//                                                                            []
void CObjDriver::SaveIndexes ()
{
	if (PRINT_PROGRESS_IND) puts ("\n\n\n\n\n\n");
	for (CPtr<CObjFormat>::Iterator objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		if (PRINT_PROGRESS_IND) printf ("%s::SaveIndexes(): ", objtype->name.c_str());
		size_t nPrevItems = NA;
		identifier indexID=0; 
		for (CPtr<CObjIndex>::Iterator index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++) 
		{
			if (PRINT_PROGRESS_IND) printf (" %d", indexID+1);
			if (index->bChanged)
			{
				size_t nItems = index->Save();
				if (nPrevItems!=NA && nItems!=nPrevItems)
				{
					SERVER_DEBUG_ERROR_5 ("CObjDriver::SaveIndexes (): В индексах %d и %d класса '%s' разное число элементов (%d и %d).", indexID-1, indexID, objtype->name.c_str(), nPrevItems, nItems);
				}
				nPrevItems = nItems;
			}
			indexID ++;
		}
		if (PRINT_PROGRESS_IND) puts ("");
	}
	theFileDriver.flush();
	if (PRINT_PROGRESS_IND) puts ("All indexes saved.\n");
}
//____________________________________________________________________________[]


//______________________________________________________________________________
//                                                                            []
//` LoadIndexes																					[]
//                                                                            []
void CObjDriver::LoadIndexes ()
{
	for (CPtr<CObjFormat>::Iterator objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		if (PRINT_PROGRESS_IND) printf ("%s::LoadIndexes(): ", objtype->name.c_str());
		size_t nPrevItems = NA;
		identifier indexID=0; 
		for (CPtr<CObjIndex>::Iterator index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++)
		{
			if (PRINT_PROGRESS_IND) printf (" %d", indexID+1);
			size_t nItems = index->Load();
			if (nPrevItems!=NA && nItems!=nPrevItems)
			{
				SERVER_DEBUG_ERROR_5 ("CObjDriver::LoadIndexes (): В индексах %d и %d класса '%s' разное число элементов (%d и %d).", indexID-1, indexID, objtype->name.c_str(), nPrevItems, nItems);
			}
			nPrevItems = nItems;
			indexID ++;
		}
		if (PRINT_PROGRESS_IND) puts ("");
	}
}
//____________________________________________________________________________[]














/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` О П Т И М И З И Р О В А Н Н Ы Е  ФАЙЛОВЫЕ ОПЕРАЦИИ С ИНДЕКСАМИ				[]
[]                                                                            []
[]____________________________________________________________________________[]
*/
//#define INDEX_OPTIMIZE /*!!!*/

static CFile*	pIndexFile				=	NULL;
static byte	*	pIndexBuff				=	NULL;
static size_t	MAX_INDEX_BUF_SIZE	=	0;
static size_t	CUR_INDEX_BUF_SIZE	=	0;

#define SET_MAX_INDEX_BUF_SIZE MAX_INDEX_BUF_SIZE=min(nCount*100,10*1024*1024);

//----------------------------------------------------------------------------[] 
#define DECODE_BUF(B,i) ((byte)((B^i) - i - i*i))
#define ENCODE_BUF(B,i) ((byte)(B + i + i*i ^i))
//----------------------------------------------------------------------------[] 

//______________________________________________________________________________
//                                                                            []
//` Вспомогательные функции																	[]
//                                                                            []
bool WriteIndexHelper (BYTE * pBlock, int nNumInBlock)
{
// Буферизуем число сохраняемых элементов
	*((int *)(pIndexBuff+CUR_INDEX_BUF_SIZE)) = nNumInBlock;
	CUR_INDEX_BUF_SIZE += sizeof (int);

// Буферизуем блок вершин из дерева-индекса
	size_t nBlockSize  = sizeof(CObjIndex_AVTree_Item)*16+4;
	memcpy (pIndexBuff+CUR_INDEX_BUF_SIZE, pBlock, nBlockSize);
	CUR_INDEX_BUF_SIZE += nBlockSize;

// Буферизуем данные, лежащие по указателям
	for (int i=0; i<nNumInBlock; i++)
	{
		CObjIndex_AVTree_Item * pItem = (CObjIndex_AVTree_Item*) (pBlock + 4 + sizeof (CObjIndex_AVTree_Item)*i);
		size_t nKeySize = *((size_t*)(pItem->m_pData));
		memcpy (pIndexBuff+CUR_INDEX_BUF_SIZE, pItem->m_pData, nKeySize);
		CUR_INDEX_BUF_SIZE += nKeySize;
	}

// Записываем буфер
	if (CUR_INDEX_BUF_SIZE >= (MAX_INDEX_BUF_SIZE*9/10))
	{
	// Записываем размер буфера
		pIndexFile->Write (&CUR_INDEX_BUF_SIZE, sizeof (CUR_INDEX_BUF_SIZE));
	// Кодируем буфер
		for (size_t i=0; i<CUR_INDEX_BUF_SIZE; i++) {
			pIndexBuff[i] = ENCODE_BUF (pIndexBuff[i], i);
		}
		pIndexFile->Write (pIndexBuff, CUR_INDEX_BUF_SIZE);
		CUR_INDEX_BUF_SIZE = 0;
	}

	return true;
}
//----------------------------------------------------------------------------[] 
bool ReadIndexHelper (BYTE * pBlock)
{
// Смещение в текущем буфере
	static size_t nBufPointer=0;

//	Считываем из файла очередной буфер
	if (nBufPointer>=CUR_INDEX_BUF_SIZE)
	{
		pIndexFile->Read (&CUR_INDEX_BUF_SIZE, sizeof(CUR_INDEX_BUF_SIZE));
		pIndexFile->Read (pIndexBuff, CUR_INDEX_BUF_SIZE);
	// Декодируем буфер
		for (size_t i=0; i<CUR_INDEX_BUF_SIZE; i++) {
			pIndexBuff[i] = DECODE_BUF (pIndexBuff[i],i);
		}
		nBufPointer = 0;
	}

// Считываем из буфера число сохранённых элементов
	int nNumInBlock = *((int *)(pIndexBuff+nBufPointer));
	nBufPointer		+= sizeof (int);

// Считываем из буфера блок вершин из дерева-индекса
	size_t nBlockSize  = sizeof(CObjIndex_AVTree_Item)*16+4;
	memcpy (pBlock, pIndexBuff+nBufPointer, nBlockSize);
	nBufPointer += nBlockSize;

// Восстанавливаем из буфера данные, которые должны лежать по указателям
	for (int i=0; i<nNumInBlock; i++)
	{
	// [size_t Size, byte KeyNum, key1, ... keyN]

	// Размер сохранённого ключа.
		size_t nSize = *((size_t *)(pIndexBuff+nBufPointer));
		nBufPointer += sizeof (size_t);

	// Выделяем память под ключ
		pbyte pka = new byte [nSize];

	// Прописываем в ключ его размер
		((size_t *)pka)[0] = nSize;

	// Считываем из буфера остальные данные ключа.
		//pIndexFile->Read (pka+sizeof (nSize), nSize-sizeof (nSize));

		memcpy (pka+sizeof (nSize), pIndexBuff+nBufPointer, nSize-sizeof (nSize));
		nBufPointer += nSize - sizeof (nSize);


	// Прописываем в дереве указатель на восстановленный ключ
		*((pbyte*)(pBlock + 4 + sizeof (CObjIndex_AVTree_Item)*i)) = pka;
	}

	return true;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Считывание индекса																			[]
//                                                                            []
#ifdef INDEX_OPTIMIZE
size_t CObjIndex::Load ()
{
// Проверяем существование индекса
	if (fileID==UNKNOWN)
	{
		SERVER_DEBUG_ERROR ("CObjIndex::Load (): Попытка загрузки несуществующего индекса");
		return 0;
	}

// Очищаем дерево
	AVTree.RemoveAll ();

// Открываем файл и создаём буфер
	int nCount=0;
	pIndexFile = new CFile ();
	pIndexFile->Open (fileID);
	pIndexFile->ReadData (nCount);

	SET_MAX_INDEX_BUF_SIZE;
	pIndexBuff = new byte [MAX_INDEX_BUF_SIZE];
	CUR_INDEX_BUF_SIZE = 0;


// Если есть данные в индексе -- считываем их через буферизацию
	if (nCount>0)
	{
		AVTree.ConvertBinaryDataToTree (ReadIndexHelper);
	}

// Закрываем файл и удаляем буфер
	pIndexFile->Close ();
	delete pIndexFile;
	delete [] pIndexBuff;
	CUR_INDEX_BUF_SIZE=0;
	bChanged = false;
	
	return AVTree.Count();
}
#endif
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Запись индекса																				[]
//                                                                            []
#ifdef INDEX_OPTIMIZE
size_t CObjIndex::Save ()
{
	if (fileID==UNKNOWN || !bChanged) return 0;

// Открываем файл и создаём буфер
	pIndexFile = new CFile ();
	pIndexFile->Open (fileID);
	pIndexFile->SetSize   (4);
	int nCount = AVTree.Count();

	SET_MAX_INDEX_BUF_SIZE;
	pIndexBuff = new byte [MAX_INDEX_BUF_SIZE];	
	CUR_INDEX_BUF_SIZE = 0;
	pIndexFile->WriteData (nCount);


// Если есть данные в индексе -- записываем их через буферизацию
	if (nCount>0)
	{
		AVTree.ConvertTreeToBinaryData (WriteIndexHelper);
	}

// Записываем остатки буфера
	if (CUR_INDEX_BUF_SIZE > 0)
	{
	// Записываем размер буфера
		pIndexFile->Write (&CUR_INDEX_BUF_SIZE, sizeof (CUR_INDEX_BUF_SIZE));
	// Кодируем буфер
		for (size_t i=0; i<CUR_INDEX_BUF_SIZE; i++) {
			pIndexBuff[i] = ENCODE_BUF (pIndexBuff[i], i);
		}
		pIndexFile->Write (pIndexBuff, CUR_INDEX_BUF_SIZE);
		CUR_INDEX_BUF_SIZE = 0;
	}

// Закрываем файл и удаляем буфер
	pIndexFile->Close ();
	delete pIndexFile;
	delete [] pIndexBuff;
	CUR_INDEX_BUF_SIZE=0;
	bChanged = false;
	
	return nCount;
}
#endif
//____________________________________________________________________________[]






















/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Н Е О П Т И М И З И Р О В А Н Н Ы Е  ФАЙЛОВЫЕ ОПЕРАЦИИ С ИНДЕКСАМИ			[]
[]                                                                            []
[]____________________________________________________________________________[]
*/








//______________________________________________________________________________
//                                                                            []
//` Сохранение индекса (неоптимизированние)												[]
//                                                                            []
#ifndef INDEX_OPTIMIZE
size_t CObjIndex::Save ()
{
	if (fileID==UNKNOWN || !bChanged) return 0;

	int i=0;
	int I=0;
	int nCount=0;

	size_t BUFF_SIZE		= 10*1024*1024;
	CPtr<byte> Buffer		= BUFF_SIZE;
	int nStoredSize	= 0;

	CFile File (fileID);
	File.Seek (0);

	for (OBD_pointer coPtr = AVTree.Last(); coPtr!=NULL; coPtr=AVTree.Prev(coPtr))
	{
		nCount++;
		CObjIndex_AVTree_Item * pItem = AVTree.ItemPointer(coPtr);
		if (pItem==NULL)
		{
			SERVER_DEBUG_ERROR ("CObjIndex::Save (): AVTree.ItemPointer(coPtr)==NULL");
		}
		else
		{
			size_t itemSize = pItem->GetSize();
			if (nStoredSize + itemSize >= BUFF_SIZE)
			{
				for (i =0; i< nStoredSize; i++, I++)
				{
					Buffer[i] = ENCODE_BUF (Buffer[i], I);
				}
				File.Write (Buffer, nStoredSize);
				nStoredSize = 0;
			}
			memcpy ((void*)(Buffer+nStoredSize), pItem->GetPtr(), pItem->GetSize());
			nStoredSize += itemSize;
		}
	}

	for (i =0; i< nStoredSize; i++, I++)
	{
		Buffer[i] = ENCODE_BUF (Buffer[i], I);
	}

	byte SSS [] = {0,0,0,0};
	for (i =0; i< 4; i++, I++)
	{
		SSS[i] = ENCODE_BUF (SSS[i], I);
	}

	File.Write (Buffer, nStoredSize);
	File.Write (SSS, 4);

	bChanged = false;

	return nCount;
}
#endif
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Считывание индекса (неоптимизированние)												[]
//                                                                            []
#ifndef INDEX_OPTIMIZE
size_t CObjIndex::Load ()
{
	if (fileID==UNKNOWN)
	{
		SERVER_DEBUG_ERROR ("CObjIndex::Load (): Попытка загрузки несуществующего индекса");
		return 0;
	}

	AVTree.RemoveAll ();

	size_t nCount =0;
	int	 I=0;

	CFile Buffer (fileID);

	Buffer.Load();
	size_t nShift = 0;

	for (I=0; I<Buffer.GetSize(); I++) 
	{
		Buffer[I] = DECODE_BUF (Buffer[I], I);
	}

	for (;;)
	{
		if (nShift+3 >= (size_t)Buffer.GetSize())
		{
			SERVER_DEBUG_ERROR ("CObjIndex::Load (): Отсутствует признак конца индекса");
			break;			
		}

		size_t itemSize = *((size_t*)(Buffer+nShift));

		if (itemSize == 0)
			break;

		nCount++;

		CObjIndex_AVTree_Item Item;

		Item.FromPtr  (Buffer+nShift);
		nShift	+=	itemSize;

		AVTree.Insert (Item);		
	}

	bChanged = false;

	return nCount;
}
#endif
//____________________________________________________________________________[]












//----------------------------------------------------------------------------[] 
enum COMPILE_STATE
{
	CS_TERM_WAITING,
	CS_TERM,

	CS_STRING,

	CS_COMMENT_FIRST,
	CS_COMMENT_STARTED,			// Ожидаем начало комментария (встретился '/')
	CS_COMMENT_LINE,				// Встретили // -- начался линейный комментарий, ждём конец строки
	CS_COMMENT_BLOCK,
	CS_COMMENT_BLOCK_ASTERISK, // *
	CS_COMMENT_LAST,


	CS_CLASS_MODIFIER_WAITING,
	CS_CLASS_WAITING,
	CS_CLASS_NAME_WAITING,
	CS_CLASS_NAME_DEFINED,
	
	CS_CLASS_NUM,
	CS_CLASS_NUM_END_WAITING,

	CS_CLASS_PARENT_WAITING,
	CS_CLASS_PARENT,

	CS_CLASS_BODY,
	CS_FIELD_NAME_WAITING,
	CS_FIELD_NAME_DEFINED,
	CS_FIELD_DEFVAL_WAITING,
	
	CS_FIELD_ARR,


	CS_INDEX_ARR_WITING,
	CS_INDEX_FIELD,
	CS_INDEX_DEFINED,
	CS_INDEX_FIELD_WAITING,

	CS_NOTHING,
	CS_END
};
//- - - - - - - - - - - - - - - - - - - - - - - - - -[]`
enum TERM_TYPE
{
	TT_master,				//	master
	TT_class,				//	class

	TT_index,				//	index

	TT_id,					//	id
	TT_byte,					// byte
	TT_int,					// int 
	TT_string,				//	string
	TT_bool,					//	bool
	TT_float,				// float

	TT_Comment,				// Комментарий

	TT_L_Brace,				//	{
	TT_R_Brace,				// }

	TT_L_Bracket,			// [
	TT_R_Bracket,			// ]

	TT_MinusName,			// index [.., -fieldname, ..]
	TT_Name,					// Произвольное корректное имя

	TT_Comma,				// ,
	TT_Colon,				// :
	TT_Semicolon,			// ;
	TT_EqualsSign,			// =

	TT_Value_Number,		// 3.14  Число
	TT_Value_Integer,		// 24		Целое число

	TT_Value_true,			// true
	TT_Value_false,		// fasle

	TT_Value_NA,			// NA
	TT_Value_UNKNOWN,		//	UNKNOWN

	TT_Value_Text,			// "Какой-то текст" в кавычках
	
	TT_Reserved,			// Зарезервированное слово
	TT_WrongName,			// Кривое имя

	TT_End,
	
	TT_NOTHING,
};
struct CTerm
{
	int			line;
	int			pos;
	TERM_TYPE	type;
	string		text;
	CTerm			(){type=TT_NOTHING; text=""; line=pos=0;};
};
typedef CPtr<CTerm>	CTermArray;
//----------------------------------------------------------------------------[] 

//______________________________________________________________________________
//                                                                            []
//` IsCorrectSymbol																				[]
//                                                                            []
bool IsCorrectSymbol (BYTE C)
{
	static bool bInit = true;
	static bool ARR_CORRECT_SYMBOL [256];
	if (bInit)
	{		
		int i,j;
		bool * ARR = ARR_CORRECT_SYMBOL;
		char * STR = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM1234567890_:;=.-";
		for (i=0; i<256;  i++)	ARR[i]=false;
		for (j=0; STR[j]; j++)	ARR[(int)(BYTE)STR[j]]=true;		
	}
	return ARR_CORRECT_SYMBOL [C];	
}
//______________________________________________________________________________
//                                                                            []
//` GetTermName																					[]
//                                                                            []
#define CHECK_TERM_TYPE(name) if (term==#name) return TT_##name
TERM_TYPE GetTermType (string term)
{
	CHECK_TERM_TYPE (master);
	CHECK_TERM_TYPE (class);
	CHECK_TERM_TYPE (index);
	CHECK_TERM_TYPE (id);
	CHECK_TERM_TYPE (int);
	CHECK_TERM_TYPE (string);
	CHECK_TERM_TYPE (byte);
	CHECK_TERM_TYPE (bool);
	CHECK_TERM_TYPE (float);


	struct TT2NAME
	{
		TERM_TYPE type;
		char *	 name;
	} TT2N_ARR [] = 
	{
		{TT_master,			"master"},
		{TT_class,			"class"},
		{TT_index,			"index"},
		{TT_id,				"id"},
		{TT_id,				"identifier"},
		{TT_id,				"object"},
		{TT_byte,			"byte"}, 
		{TT_int,				"int"}, 
		{TT_int,				"long"}, 
		{TT_int,				"datetime"}, 
		{TT_int,				"date"}, 
		{TT_int,				"time"}, 
		{TT_string,			"string"},
		{TT_bool,			"bool"},
		{TT_float,			"float"},
		{TT_L_Brace,		"{"},
		{TT_R_Brace,		"}"},
		{TT_L_Bracket,		"["},
		{TT_R_Bracket,		"]"},
		{TT_Comma,			","},
		{TT_Colon,			":"},
		{TT_Semicolon,		";"},
		{TT_EqualsSign,	"="},
		{TT_Value_true,	"true"},
		{TT_Value_false,	"false"},
		{TT_Value_true,	"TRUE"},
		{TT_Value_false,	"FALSE"},
		{TT_Value_NA,		"NA"},
		{TT_Value_UNKNOWN,"UNKNOWN"},
		{TT_Reserved,		"Object"},
		{TT_Reserved,		"Exist"},
		{TT_Reserved,		"Delete"},
		{TT_Reserved,		"exist"},
		{TT_Reserved,		"delete"},
		{TT_Reserved,		"classID"}
	};

	size_t TT2N_NUM = sizeof (TT2N_ARR)/sizeof (TT2N_ARR[0]);
	int	 i;

	for (i=0; i<(int)TT2N_NUM; i++)
	{
		if (TT2N_ARR[i].name == term)
			return TT2N_ARR[i].type;
	}
	
	
	int nDot=0;

	bool bStartAsDigit = false;
	bool bHasSymbols	 = false;
	bool bHasMinuse	 = false;
	for (i=0; i<(int)term.length(); i++)
	{
		char C = term[i];

		if (C=='.')
			nDot++;
		if (i==0 && C=='.')
			bStartAsDigit = true;
		if (i==0 && ('0'<=C) && (C<='9'))
			bStartAsDigit = true;
		if (((C<'0') || ('9'<C)) && C!='.' && !(C=='-' && i==0))
			bHasSymbols = true;
		
		if (C=='-')
			bHasMinuse = true;

		if (nDot>1)
			return TT_WrongName;
		if (nDot>=1 && bHasSymbols)
			return TT_WrongName;
		if (bStartAsDigit && bHasSymbols)
			return TT_WrongName;
	}

	if (term=="-") {
		return TT_WrongName;
	}

	if (bHasMinuse && bHasSymbols) {
		if (term[0]=='-')	{
			for (i=0; i<(int)term.length(); i++) {
				if (term[i]=='-' && i!=0) {
					return TT_WrongName;
				}
			}
		}
		else {
			return TT_WrongName;
		}
	}

	nDot = 0;
	for (i=0; i<(int)term.length(); i++)
	{
		char C = term[i];

		if (C=='.')
			nDot++;
		else if (((C<'0') || ('9'<C)) && !(C=='-' && i==0))
			return term[0] == '-'? TT_MinusName: TT_Name;
		if (nDot>1)
			return TT_WrongName;
	}

	if (i==(int)term.length())
		return nDot==0? TT_Value_Integer: TT_Value_Number;

	return TT_Name;
}
//----------------------------------------------------------------------------[] 
void AddTermToArray (int nLine, int nPos, string& text, CTermArray& Array, TERM_TYPE type = TT_NOTHING)
{
	if (text.size()>0)
	{
		CTerm term;
		
		term.line	= nLine;
		term.pos		= nPos;
		term.text	= text;
		term.type	= (type==TT_NOTHING)? GetTermType (text): type;

		Array.Add (term);	
	}
	text = "";
}
//____________________________________________________________________________[]



#define CSPOP bPopCS++
#define CSPUSH	CS_Stack[++CS_StackTop]=CS

#define STORE_TERM(term)		AddTermToArray (nLine, nPos, term, Terms)
#define STORE_COMMENT(term)	AddTermToArray (nLine, nPos, term, Terms, TT_Comment)
#define STORE_STRING(term)		AddTermToArray (nLine, nPos, term, Terms, TT_Value_Text)
#define STORE_END					{string _s_EOF ="EOF"; AddTermToArray (nLine, nPos, _s_EOF, Terms, TT_End);}


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Compile Base Format 																		[]
[]                                                                            []
[]____________________________________________________________________________[]
*/

bool CObjDriver::Compile (const char * fileName, bool bCreateCPP)
{
	Erase ();

	CPtr <byte> Src;
	size_t nLen = Src.ReadFile(fileName);
	if (nLen == 0)
	{
		printf ("can't read Lay-file %s\n", fileName);
		return false;
	}
	Src[nLen] = 0;

	
	//----------------------------------------------------------------------------[] 
	COMPILE_STATE	CS		= CS_TERM_WAITING;
	int				nLine	= 1;
	int				nPos	= 0;
	string			term	= "";
	string			comment="";
	int				bPopCS=0;
	int				i=0,j=0,k=0,l=0;
	
	COMPILE_STATE	CS_Stack			[1024];
	int				CS_StackTop =	0;

	CSPUSH;
	CTermArray	Terms;
	//----------------------------------------------------------------------------[] 



	//______________________________________________________________________________
	//                                                                            []
	//` Лексичесий анализатор.																		[]
	//                                                                            []
	if (PRINT_PROGRESS) puts ("Analization...");
	int old_line = -1;
	for (i=0; CS!=CS_END; i++, nPos++)
	{
		if (old_line!=nLine)
		{
			if (PRINT_PROGRESS) printf (" %3d%% [line %4d]  \r", i*100/nLen, nLine);
			old_line=nLine;
		}

		char C = Src[i];
		if (C=='\t') 
			nPos+=2;
		while (bPopCS)
		{
			SERVER_DEBUG_ASSERT_RETURN (CS_StackTop>0, "Испорчен стек состояния компиляции", false);
			CS = CS_Stack [CS_StackTop];
			CS_StackTop--;
			bPopCS--;
		}
		//----------------------------------------------------------------------------[] 

		//----------------------------------------------------------------------------[] 
		switch (C)
		{
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
		// Комментарий -- ожидаем /* // или начался // или */
			case '/': switch (CS)
			{
			// Символ внутри строки
				case CS_STRING:
					term += C;
				break;

			// Начался линейный комментарий -- встретили //
				case CS_COMMENT_STARTED:
					STORE_TERM (term);
					comment = "";
					CS = CS_COMMENT_LINE;
				break;
				
			// Кончился блочный комментарий -- встретили */
				case CS_COMMENT_BLOCK_ASTERISK:
					{
					char SSS[10240];
					strcpy (SSS, comment.c_str());
					SSS[comment.length()-1]=0;
					comment = SSS;
					STORE_COMMENT (comment);
					CSPOP;
					CSPOP;
					}
				break;

			// Символ внутри комментария
				case CS_COMMENT_LINE:
				case CS_COMMENT_BLOCK:
					comment += C;
				break;

			// Встретили '/' -- ожидаем комментарий
				default:
					CSPUSH;
					CS = CS_COMMENT_STARTED;
				break;
			}
			break;
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 



		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
		// Комментарий -- дождались /* или начался */
			case '*': switch (CS)
			{
			// Символ внутри строки
				case CS_STRING:
					term += C;
				break;

			// Начался блочный комментарий -- встретили /*
				case CS_COMMENT_STARTED:
					comment = "";
					CS = CS_COMMENT_BLOCK;
				break;
				
			// Ожидаем возможного завершения блочного комментария
				case CS_COMMENT_BLOCK:
					CSPUSH;
					CS = CS_COMMENT_BLOCK_ASTERISK;
					comment += C;
				break;

			// Символ внутри комментария
				case CS_COMMENT_LINE:
				case CS_COMMENT_BLOCK_ASTERISK:
					comment += C;
				break;

				default:
					COMPILE_ERROR ("'*'");
				break;
				}
			break;
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 

			

		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
		// Конец строки
			case 0:
			case 10: switch (CS) 
			{
			// Кончился линейный комментарий
				case CS_COMMENT_LINE: 
					STORE_COMMENT (comment);
					CSPOP;
				break;
				
				case CS_STRING:
					COMPILE_ERROR ("Перенос строки недопустим.");
				break;
			}
			nLine++;
		// Разделители
			case	13:
				nPos =0;
			case ' ':
			case '\t': switch (CS) 
				{
				case CS_TERM:
					STORE_TERM (term);
					CSPOP;
				break;

			// Символ внутри строки
				case CS_STRING:
					term += C;
				break;

			// Символ внутри комментария
				case CS_COMMENT_LINE:
				case CS_COMMENT_BLOCK:
					if (C!=13)
						comment += C==10? ' ': C;
				break;
				}
				if (C==0)
				{
					CS = CS_END;
				}
			break;
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 


		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 				
		// Строковые значения
			case '"': switch (CS) 
				{
				case CS_TERM_WAITING:
					CSPUSH;
					CS = CS_STRING;
					term="";
				break;
				
				case CS_STRING:
					STORE_STRING (term);
					CSPOP;
				break;

			// Символ внутри комментария
				case CS_COMMENT_LINE:
				case CS_COMMENT_BLOCK:
					comment += C;
				break;

				default:
					COMPILE_ERROR ("Кавычка неожиданная");
				break;
				}
			break;
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
			

		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
		// Спец символы
			case ',':
			case '[':
			case ']':
			case ';':
			case ':':
			case '{':
			case '}':
			case '=': switch (CS) 
				{
			// Символ внутри строки
				case CS_STRING:
					term += C;
				break;

				case CS_TERM:
					STORE_TERM (term);
					term = C;
					STORE_TERM (term);
					CSPOP;
				break;

				case CS_TERM_WAITING:
					term = C;
					STORE_TERM (term);
				break;

			// Символ внутри комментария
				case CS_COMMENT_LINE:
				case CS_COMMENT_BLOCK:
					comment += C;
				break;
				}
			break;
		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 



		//- - - - - - - - - - - - - - - - - - - - - - - - - -[]` 
		// Произвольный символ
			default:
			{
				switch (CS)
				{
				// Начался терм
					case CS_TERM_WAITING:
						CSPUSH;
						CS	  = CS_TERM;
						term = C;
					break;
					
					case CS_COMMENT_BLOCK_ASTERISK:
						CSPOP;
						comment += C;
					break;

				// Символ внутри комментария
					case CS_COMMENT_LINE:
					case CS_COMMENT_BLOCK:
						comment += C;
					break;

				// Символ внутри терма или строки
					case CS_STRING:
					case CS_TERM:
						term += C;
					break;
				}

				if (CS == CS_TERM && !IsCorrectSymbol(C))
				{
					string err = "Кривые символы в термине: ";
					err += term;
					term = err;
					COMPILE_ERROR (term.c_str());
				}
			}
			break;
		} // end switch (C)
	}
	STORE_END;
	//____________________________________________________________________________[]





	//----------------------------------------------------------------------------[] 
	string Tmp="";
	CTermArray::Iterator it;
	for (it = Terms.begin(); it!=Terms.end(); it++)
	{
		if (it->type!=TT_Comment) 
		{
			Tmp += it->text;
			Tmp += "\n";
		}
	}

	//CPtr <char> TmpFile (Tmp.c_str(), Tmp.length());
	//TmpFile.WriteFile ("allterms.txt");
	//printf (Tmp.c_str());
	//----------------------------------------------------------------------------[] 


	//______________________________________________________________________________
	//                                                                            []
	//` Компилятор.																					[]
	//                                                                            []
	CS					= CS_CLASS_MODIFIER_WAITING;
	CS_StackTop		= -10000000;
	bool				bExistMaster = false;

	int				classNum	= 1;
					
	string			text;
	TERM_TYPE		type;	

	CObjFormat			format;
	CFieldFormat		field;
	CPtr<string>		index;
	CPtr<string_arr>	indexarr;

	if (PRINT_PROGRESS) puts ("Compilation...                                             ");
	for (it = Terms.begin(); it!=Terms.end() && CS!=CS_END; it++)
	{
		nLine = it->line;
		nPos	= it->pos;
		text	= it->text;
		type	= it->type;

		if ((type == TT_MinusName) && (CS!=CS_INDEX_FIELD_WAITING))
		{
			char SSS [256];
			sprintf (SSS, "Недопустимое использование знака '-': '%s'.", text.c_str());
			COMPILE_ERROR  (SSS);																
		}

		switch (type)
		{
		// Произвольное корректное имя или index [-fieldname]
			case TT_MinusName:
			case TT_Name: switch (CS)
				{
				// Имя класса
					case CS_CLASS_NAME_WAITING:
						format.name = text;						
						if (GetFormatIndex (text) != UNKNOWN)
						{
							char SSS [256];
							sprintf (SSS, "Тип '%s' уже существует.", text.c_str());
							COMPILE_ERROR  (SSS);																
						}

						field.Erase();
						field.type		= FT_identifier;
						field.isArray	= false;
						field.name		= "classID";
						field.defValue	= "???";
						format.fieldArr.Add (field);
						field.Erase();

						CS = CS_CLASS_NAME_DEFINED;
					break;

				// Имя родителя класса
					case CS_CLASS_PARENT_WAITING:
						format._parentArr.Add (text);
						CS = CS_CLASS_PARENT;
					break;

				// Имя поля
					case CS_FIELD_NAME_WAITING:
					{
						field.name = text;
						if (format.GetFieldIndex (text)!=UNKNOWN)
						{
							static char SSS[256];
							sprintf (SSS, "'%s' -- поле с таким именем уже есть.", text.c_str());
							COMPILE_ERROR  (SSS);
						}
						CS = CS_FIELD_NAME_DEFINED;
					}
					break;
						
				// Имя индексируемого поля
					case CS_INDEX_FIELD_WAITING:
					{
						index.Add (text);
						if (index.GetSize()>MAX_KEY_NUM_IN_INDEX)
						{
							static char SSS[256];
							sprintf (SSS, "'%s' -- слишком много ключей в индексе.", text.c_str());
							COMPILE_ERROR  (SSS);								
						}
						CS = CS_INDEX_FIELD;
					}
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		//	master
			case TT_master: 
				if (bExistMaster)
				{
					COMPILE_ERROR  ("Мастер-класс уже существует. В системе не может быть определено более одного мастер-класса.");
				}
				else switch (CS)
				{
					case CS_CLASS_MODIFIER_WAITING:
						CS = CS_CLASS_WAITING;
						format.isMaster = true;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
				bExistMaster = true;
			break;
			
		//	class
			case TT_class: switch (CS)
				{
					case CS_CLASS_MODIFIER_WAITING:
					case CS_CLASS_WAITING:
						CS = CS_CLASS_NAME_WAITING;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Символ [
			case TT_L_Bracket: switch (CS)
				{
					case CS_CLASS_NAME_DEFINED:
						CS = CS_CLASS_NUM;
					break;

					case CS_INDEX_ARR_WITING:
						CS = CS_INDEX_FIELD_WAITING;
					break;

					case CS_FIELD_NAME_DEFINED:
						CS = CS_FIELD_ARR;
					break;
					
					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Значение -- Целое число
			case TT_Value_Integer: switch (CS)
				{
					case CS_CLASS_NUM:
						CS = CS_CLASS_NUM_END_WAITING;
						classNum = atoi (text.c_str());
					break;

					case CS_FIELD_DEFVAL_WAITING:
						field.defValue = text;
						if (field.type!=FT_int && field.type!=FT_byte && field.type!=FT_float)
						{
							COMPILE_ERROR ("Значение по умолчанию неправильного типа");
						}

						CS = CS_FIELD_NAME_DEFINED;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Символ ]
			case TT_R_Bracket: switch (CS)
				{
					case CS_CLASS_NUM_END_WAITING:
						CS = CS_CLASS_NAME_DEFINED;
					break;

					case CS_FIELD_ARR:
						field.isArray = true;
						CS = CS_FIELD_NAME_DEFINED;
					break;

					case CS_INDEX_FIELD:
						indexarr.Add(index);
						index.Erase();
						CS = CS_INDEX_DEFINED;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Знак ,
			case TT_Comma: switch (CS)
				{
					case CS_CLASS_PARENT:
						CS = CS_CLASS_PARENT_WAITING;
					break;

					case CS_INDEX_FIELD:
						CS = CS_INDEX_FIELD_WAITING;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Знак : 
			case TT_Colon: switch (CS)
				{
					case CS_CLASS_NAME_DEFINED:
						CS = CS_CLASS_PARENT_WAITING;
					break;
					default: COMPILE_ERROR  (text.c_str());
				}
			break;


		//	Символ {
			case TT_L_Brace: switch (CS)
				{
					case CS_CLASS_PARENT:
					case CS_CLASS_PARENT_WAITING:
					case CS_CLASS_NAME_DEFINED:
						CS = CS_CLASS_BODY;
					break;
					default: COMPILE_ERROR  (text.c_str());
				}
			break;
		
		// Символ }
			case TT_R_Brace: switch (CS)
				{
					case CS_CLASS_BODY:
						for (i=0; i<classNum; i++)
						{
							string origName = format.name;
							char SSS [256];
							sprintf (SSS, "_%d", i+1);
							if (classNum!=1)
								format.name += SSS;
							
							for (j =0; j<(int)format._parentArr.GetSize(); j++)
							{
								identifier parentID = GetFormatIndex (format._parentArr[j]);
								if (parentID==UNKNOWN)
								{
									static char SSS [1024];
									sprintf (SSS, "Неизвестный предок '%s'.", format._parentArr[j].c_str());
									COMPILE_ERROR  (SSS);
								}

								for (k=0; k<(int)m_FormatArr[parentID].fieldArr.GetSize(); k++) // по полям предка
								{
									identifier fieldID = format.GetFieldIndex(m_FormatArr[parentID].fieldArr[k].name);
									if (fieldID == UNKNOWN)
									{
										format.fieldArr.Add (m_FormatArr[parentID].fieldArr[k]);
									}
									else
									{
										string		fieldName = format.fieldArr[fieldID].name;

										string		defValue1 = format.fieldArr[fieldID].defValue;
										string		defValue2 = m_FormatArr[parentID].fieldArr[k].defValue;
										bool			isArray1	 = format.fieldArr[fieldID].isArray;
										bool			isArray2	 = m_FormatArr[parentID].fieldArr[k].isArray;
										FIELD_TYPE	nftype1	 = format.fieldArr[fieldID].type;
										FIELD_TYPE	nftype2	 = m_FormatArr[parentID].fieldArr[k].type;
										if (strcmp(fieldName.c_str(),"classID")) if (strcmp(defValue1.c_str(), defValue2.c_str()) || (isArray1 != isArray2) || (nftype1 != nftype2))
										{
											static char SSS [1024];
											sprintf (SSS, "Поле '%s' у предка определено иначе.", fieldName.c_str());
											COMPILE_ERROR  (SSS);
										}
									}
								}
							}

						// Записываем индексы по именам полей
							if (i==0) for (j=0; j<(int)indexarr.GetSize(); j++)
							{
								CObjIndex _index;
								for (k=0; k<(int)indexarr[j].GetSize(); k++)
								{
									bool bIndexFieldAscend	= (indexarr[j][k][0] != '-');
									string fname = indexarr[j][k].c_str()+(bIndexFieldAscend? 0: 1);
									identifier nf = format.GetFieldIndex(fname);
									if (nf==UNKNOWN)
									{
										static char SSS [1024];
										sprintf (SSS, "Неизвестное поле '%s' в индексе.", fname.c_str());
										COMPILE_ERROR  (SSS);
									}
									if (format.fieldArr[nf].isArray)
									{
										static char SSS [1024];
										sprintf (SSS, "Поле '%s' не может быть индексировано, т.к. является массивом.", fname.c_str());
										COMPILE_ERROR  (SSS);
									}
									_index.fieldArr.Add (nf);
									_index.fieldArr_ascend.Add (bIndexFieldAscend);
								}
								format.indexArr.Add (_index);
							}

							char SSS_0 [256];
							sprintf (SSS_0, "%d", m_FormatArr.GetSize());
							format.fieldArr[0].defValue = SSS_0;

						// Добавляем обратные ссылки из полей в индексы
							for (j=0; j<(int)format.fieldArr.GetSize(); j++)
							{
								format.fieldArr[j].indexArr.Erase ();
								for (k=0; k<(int)format.indexArr.GetSize(); k++)
								{
									for (l=0; l<(int)format.indexArr[k].fieldArr.GetSize(); l++)
									{
										if ((int)format.indexArr[k].fieldArr[l] == j)
										{
											format.fieldArr[j].indexArr.Add(k);
										}
									}
								}
							}

							m_FormatArr.Add (format);

							format.name = origName;
						}
						format.Erase ();
						indexarr.Erase();
						classNum = 1;
						CS = CS_CLASS_MODIFIER_WAITING;
					break;
					default: COMPILE_ERROR  (text.c_str());
				}
			break;
		//----------------------------------------------------------------------------[] 


		//----------------------------------------------------------------------------[] 
		//	index
			case TT_index: 
				if (format.isMaster)
				{
					COMPILE_ERROR  ("Мастер-класс не может иметь индексы");
				}
				else switch (CS)
				{
					case CS_CLASS_BODY:
						CS = CS_INDEX_ARR_WITING;
					break;
					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		//	Типы полей
			case TT_id:
				if (field.type == FT_nothing) field.type = FT_identifier;
			case TT_int:
				if (field.type == FT_nothing) field.type = FT_int;
			case TT_string:
				if (field.type == FT_nothing) field.type = FT_string;
			case TT_bool:
				if (field.type == FT_nothing) field.type = FT_bool;
			case TT_byte:
				if (field.type == FT_nothing) field.type = FT_byte;
			case TT_float: 
				if (field.type == FT_nothing) field.type = FT_float;
				switch (CS)
				{
					case CS_CLASS_BODY:
						CS = CS_FIELD_NAME_WAITING;
					break;
					default: 
						{
							char SSS [256];
							sprintf (SSS, "'%s' не на месте. Возможно пропущена точка с запятой.", text.c_str());
							COMPILE_ERROR  (SSS);
						}
				}
			break;

		// Комментарий
			case TT_Comment:
			break;

		// знак ;
			case TT_Semicolon: switch (CS)
				{
					case CS_FIELD_NAME_DEFINED:
						format.fieldArr.Add (field);
						field.Erase ();
						CS = CS_CLASS_BODY;
					break;

					case CS_INDEX_DEFINED:
						CS = CS_CLASS_BODY;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// знак =
			case TT_EqualsSign: switch (CS)
				{
					case CS_FIELD_NAME_DEFINED:
						CS = CS_FIELD_DEFVAL_WAITING;
					break;

					default: COMPILE_ERROR  (text.c_str());
				}
			break;

		// Значения по умолчанию
			case TT_Value_NA:
			case TT_Value_UNKNOWN:
			case TT_Value_true:
			case TT_Value_false:
			case TT_Value_Number:
			case TT_Value_Text: switch (CS)
				{
					case CS_FIELD_DEFVAL_WAITING:
						field.defValue = text;
						if (field.isArray)
						{
							COMPILE_ERROR ("У массива не может быть значения по умолчанию");
						}
						CS = CS_FIELD_NAME_DEFINED;
						if (	type==TT_Value_true && field.type!=FT_bool			||
								type==TT_Value_false && field.type!=FT_bool 			||
								type==TT_Value_Number && (field.type!=FT_float)		||
								type==TT_Value_Text && field.type!=FT_string			||
								type==TT_Value_UNKNOWN && field.type!=FT_identifier||
								type==TT_Value_NA && field.type!=FT_identifier)

						{
							COMPILE_ERROR ("Значение по умолчанию неправильного типа");
						}
					break;

					default: COMPILE_ERROR (text.c_str());
				}
			break;

		// Конец
			case TT_End: switch (CS)
				{
					case CS_CLASS_MODIFIER_WAITING:
						CS = CS_END;
					break;

					default: COMPILE_ERROR  ("Неправильно завершён файл.");
				}
			break;

			case TT_WrongName:
			{
				static char SSS[256];
				sprintf (SSS, "Кривое имя: %s", text.c_str());
				COMPILE_ERROR  (SSS);	
			}
			break;
			
			case TT_Reserved:
			{
				static char SSS[256];
				sprintf (SSS, "Зарезервированное слово: %s", text.c_str());
				COMPILE_ERROR  (SSS);	
			}
			break;

		// Неизвестный термин
			default:
				COMPILE_ERROR  ("Неизвестный термин");
			break;
		}
	}
	//____________________________________________________________________________[]



	CPtr<CObjFormat>::Iterator objtype;

	//----------------------------------------------------------------------------[] 
	// Присваиваем уникальные ID файлам храненияи индексов
	//
	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		for (CPtr<CObjIndex>::Iterator index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++)
		{
			index->fileID = CFile::CreateNewFile();
		}
	}
	//----------------------------------------------------------------------------[] 

	if (PRINT_PROGRESS) puts ("Saving...                                  ");
	SaveFormat	();

	if (bCreateCPP)
	{
		if (!b_CREATE_INTERFACE_ONLY)
		{
			if (PRINT_PROGRESS) puts ("\n\rCreating:  Lay_ObjController.h                                  ");
			string sObjController;
			Create_ObjController_h (sObjController);
			CPtr<char> ObjController_ptr (sObjController.c_str(), sObjController.size());
			ObjController_ptr.WriteFile ("../Lay_ObjController.h");

			if (PRINT_PROGRESS) puts ("\rCreating:  Lay_ObjController.cpp                                ");
			Create_ObjController_cpp (sObjController);
			ObjController_ptr.CopyFrom (sObjController.c_str(), sObjController.size());
			ObjController_ptr.WriteFile ("../Lay_ObjController.cpp");

			if (PRINT_PROGRESS) puts ("\rCreating:  Lay_ObjData.h                                  ");
			string sObjData_h;
			Create_ObjData_h (sObjData_h);
			CPtr<char> ObjData_h_ptr (sObjData_h.c_str(), sObjData_h.size());
			ObjData_h_ptr.WriteFile ("../Lay_ObjData.h");

			if (PRINT_PROGRESS) puts ("\rCreating:  Lay_ObjData.cpp                                  ");
			string sObjData_cpp;
			Create_ObjData_cpp (sObjData_cpp);
			CPtr<char> ObjData_cpp_ptr (sObjData_cpp.c_str(), sObjData_cpp.size());
			ObjData_cpp_ptr.WriteFile ("../Lay_ObjData.cpp");

			if (PRINT_PROGRESS) puts ("\rCreating:  Lay_Stubs.cpp                                  ");
			string sStubs_h;
			Create_Stubs_h (sStubs_h);
			CPtr<char> Stubs_h_ptr (sStubs_h.c_str(), sStubs_h.size());
			Stubs_h_ptr.WriteFile ("../Lay_Stubs.cpp");
		}

		string sInterface_h;
		CPtr<char> Interface_h_ptr;

		CPtr <INTERFACE_FORMAT> Format;
		string Prefix="";
		
		CompileInterface (Format, SRC_INTERFACE_FILE, Prefix);

		if (PRINT_PROGRESS) puts ("\rCreating:  Interface_Dispatch.cpp                              ");
		Create_Interface_Dispatch_cpp	(sInterface_h, Format, Prefix);
		Interface_h_ptr.CopyFrom(sInterface_h.c_str(), sInterface_h.size());
		Interface_h_ptr.WriteFile ("./../Interface_Dispatch.cpp");

		if (PRINT_PROGRESS) puts ("\rCreating:  Interface_Auto.h                                    ");
		Create_Interface_Auto_h	(sInterface_h, Format, Prefix);
		Interface_h_ptr.CopyFrom (sInterface_h.c_str(), sInterface_h.size());
		Interface_h_ptr.WriteFile ("./../Interface_Auto.h");

		if (PRINT_PROGRESS) puts ("\rCreating:  Interface_Auto.cpp                                  ");
		Create_Interface_Auto_cpp	(sInterface_h, Format, Prefix);
		Interface_h_ptr.CopyFrom  (sInterface_h.c_str(), sInterface_h.size());
		Interface_h_ptr.WriteFile ("./../Interface_Auto.cpp");	
	}

	return true;
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` GetIndexPtr																					[]
//                                                                            []
CObjIndex* CObjDriver::GetIndexPtr (identifier classID, identifier indexID)
{
	CObjFormat& format = m_FormatArr.At(classID);
	CObjIndex& formatIndex = format.indexArr.At(indexID);
	return &formatIndex;
}
//______________________________________________________________________________
//                                                                            []
//` GetFieldPtr																					[]
//                                                                            []
CFieldFormat* CObjDriver::GetFieldPtr (identifier classID, identifier fieldID)
{
	CObjFormat& format = m_FormatArr.At(classID);
	CFieldFormat& fieldFormat = format.fieldArr.At(fieldID);
	return &fieldFormat;
}
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

