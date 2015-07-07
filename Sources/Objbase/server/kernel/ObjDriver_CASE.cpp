/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1999-2000 by the author(s).                                  []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            ObjDriver_CASE.cpp														[]
[] Author:          Roman V. Koshelev														[]
[] Description:     Object-control layer													[]
[]____________________________________________________________________________[]
*/

#include "ObjDriver_inc.h"



char * FT_NAME_SHORT	[]	= {"identifier",			"guid",					"int",					"byte",					"bool",					"float",					"string"};
char * FT_NAME			[]	= {"identifier     ",	"guid           ",	"int            ",	"byte           ",	"bool           ",	"float          ",	"string         "};
char * FT_NAME_ARR	[]	= {"identifier_arr ",	"guid_arr       ",	"int_arr        ",	"byte_arr       ",	"bool_arr       ",	"float_arr      ",	"string_arr     "};
char * FT_VOID				=  "void       ";
char * FT_SIZE_T			=  "size_t     ";



char * sLF   ="\n";
char * sLINE ="\n//------------------------------------------------------------------------------[]\n";


#define NEW_LINE	header+=sLF;
#define DELIMITER header+=sLINE;


	
//______________________________________________________________________________
//                                                                            []
//` Create_ObjController_cpp                                                  []                        
//                                                                            []
void CObjDriver::Create_ObjController_cpp	(string& header)
{
	DEBUG_STACK_NAME (Create_ObjController_cpp);

#ifdef ZOOB_UTILS
	int	i=0,f=0;
	int   k=0;
	CPtr<CObjFormat>::Iterator objtype;
	CPtr<CFieldFormat>::Iterator field;
	CPtr<CObjIndex>::Iterator index;
	char   SSS[10240];

	header = "";

	header += "/*";
	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Lay_ObjController.cpp                                     []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev, Alex Vershinin                         []";	NEW_LINE;
	header += "[] Description:     Controlers for database objects                           []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Lay.h-file         []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
	NEW_LINE;


	header += "#define USES_OC_ALL";								NEW_LINE;
	header += "#define USES_string_h";							NEW_LINE;
	header += "#define USES_key_arr_h";							NEW_LINE;
	header += "#define USES_EventMonitor_h";					NEW_LINE;
	header += "#define USES_FileDriver_h";						NEW_LINE;
	header += "#define USES_File_h";								NEW_LINE;
	header += "#define USES_ObjDriver_h";						NEW_LINE;
	NEW_LINE;
	header += "#include \"Lay_ObjController.h\"";			NEW_LINE;
	NEW_LINE;

//	������
	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++) if (!objtype->isVirtual)
	{
		PRINT_CREATION_PERCENT;
		NEW_LINE;
		header += "// ===============================================================================";
		NEW_LINE;
		header += "// ";
		header += objtype->name.c_str();
		NEW_LINE;
		NEW_LINE;
		if (objtype->isMaster)
		{
			header += "void OC_";
			header += objtype->name.c_str();
			header += "::About_class_OC_Master (){return;}";											NEW_LINE;
			NEW_LINE;
		}

		//----------------------------------------------------------------------------[] 
		// ����������� �� ��������� -- ���������� �� ���������� �� ������!
		header += "// ����������� �� ���������"; NEW_LINE;
		header += "OC_";
		header += objtype->name.c_str();
		header += "::OC_";
		header += objtype->name.c_str();
		header += " ()";	NEW_LINE;
		header += "{";	NEW_LINE;
		sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_OC_%s);", objtype->name.c_str(), objtype->name.c_str()); header += SSS;	NEW_LINE;
		header += "   curIndexInfo.Init(); InitSmartFields(); coPtr=";
		if (objtype->isMaster)
		{
			header += "OBD_OpenMasterObject(classID);";
		}
		else 
		{
			header += "NULL;";		
		}
		NEW_LINE;
		header += "}";
		NEW_LINE;
		NEW_LINE;
		//----------------------------------------------------------------------------[] 
		// ����������� �� �������������� -- ����������� ������ �� ����

		if (!objtype->isMaster)
		{
		// ����������� �� �������������� -- ����������� ������ �� ����
			NEW_LINE;
			header += "// ����������� �� �������������� -- ����������� ������ �� ����";
			NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "::OC_";
			header += objtype->name.c_str();
			header += "  (identifier objID)";
			NEW_LINE; header += "{"; NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_OC_%s);", objtype->name.c_str(), objtype->name.c_str()); header += SSS;	NEW_LINE;
			header += "   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; Open (objID);";
			NEW_LINE;
			header += "}";
			NEW_LINE;
			NEW_LINE;

		// ����������� ����������� �� ������� �����������
			header += "// ����������� ����������� �� ������� �����������";
			NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "::OC_";
			header += objtype->name.c_str();
			header += "  (const OC_";
			header += objtype->name.c_str();
			header += "& from)";
			NEW_LINE;
			header += "{";			NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_OC_%s);", objtype->name.c_str(), objtype->name.c_str()); header += SSS;	NEW_LINE;
			header += "   curIndexInfo.Init(); InitSmartFields(); coPtr=NULL; if (from.coPtr==NULL) return; coPtr=OBD_CopyObject(classID, from.coPtr);";			NEW_LINE; 
			header += "}";
		}
		NEW_LINE;
		NEW_LINE;
		
		//----------------------------------------------------------------------------[] 
		//	����������

		header += "// ���������� ����������� �������";
		NEW_LINE;
		header += "OC_";
		header += objtype->name.c_str();
		header += "::~OC_";
		header += objtype->name.c_str();
		header += " ()";
		NEW_LINE; header += "{";NEW_LINE;
		sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_Destructor);", objtype->name.c_str()); header += SSS;	NEW_LINE;
      header += "   Release();";
		NEW_LINE; header += "}";
		NEW_LINE;
		NEW_LINE;


		//----------------------------------------------------------------------------[] 
		// �����������

		if (!objtype->isMaster)
		{
			header += "// 1. ����������� (�����������, ������������) ������������ ������ ������";
			NEW_LINE;
			header += "// 2. �������� ������� �� ��������������";
			NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "& OC_";
			header += objtype->name.c_str();
			header += "::operator= (const OC_";
			header += objtype->name.c_str();
			header += "& from)";NEW_LINE;
			header += "{";NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_operator_assign);", objtype->name.c_str()); header += SSS;	NEW_LINE;
			header += "   Release(); if (from.coPtr==NULL) return *this; coPtr=OBD_CopyObject(classID, from.coPtr); curIndexInfo=from.curIndexInfo; return *this;";			NEW_LINE; 
			header += "}";
			NEW_LINE;
			NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "& OC_";
			header += objtype->name.c_str();
			header += "::operator= (identifier objID)";
			NEW_LINE; header += "{"; NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_operator_assign);", objtype->name.c_str()); header += SSS;	NEW_LINE;
 			header += "   Open (objID); return *this;";
			NEW_LINE; header += "}";
			NEW_LINE;
			NEW_LINE;
		}

		//----------------------------------------------------------------------------[] 
		//	������������� ���������� �����
		NEW_LINE;
		NEW_LINE;
		header += "// ������������� ���������� ����� CSmartField<...>";				NEW_LINE;
		header += "void OC_";
		header += objtype->name.c_str();
		header += "::InitSmartFields (void)";													NEW_LINE;
		header += "{";																					NEW_LINE;
		sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_InitSmartFields);", objtype->name.c_str()); header += SSS;	NEW_LINE;
		header += "   classID = ";
		sprintf (SSS, "OBJ_CLASS_ID_%s;", objtype->name.c_str()); header += SSS;	NEW_LINE;

		int maxflen=0;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
		{
			maxflen = max (maxflen, (int)field->name.length());
		}

		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
		{
			char SPACES[256] = "                                                                               ";
			SPACES[maxflen-field->name.length()] = 0;
			sprintf (SSS, "   m_%s._init%s (classID, %d, &coPtr, &OD_%s::d_%s%s );", 
				field->name.c_str(), SPACES, f, objtype->name.c_str(), field->name.c_str(),SPACES);
			header += SSS;
			NEW_LINE;
		}
		if (objtype->indexArr.GetSize()!=0)
		{
			header += "   SetIndex (0);"; NEW_LINE;			
		}
		header += "}";
		NEW_LINE;
		NEW_LINE;

		//----------------------------------------------------------------------------[] 
		//	����������� ������ �� ������� �����������	
		if (!objtype->isMaster)
		{
			NEW_LINE;
			header += "// ����������� ������ �� ������� �����������";						NEW_LINE;
			header += "void OC_";
			header += objtype->name.c_str();
			sprintf (SSS, "::CopyDataFrom (OC_%s& from)", objtype->name.c_str()); header += SSS;	NEW_LINE;
			header += "{";																									NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_CopyDataFrom);", objtype->name.c_str()); header += SSS;	NEW_LINE;
			maxflen=0;
			for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
			{
				maxflen = max (maxflen, (int)field->name.length());
			}

			for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
			{
				char SPACES[256] = "                                                                               ";
				SPACES[maxflen-field->name.length()] = 0;
				sprintf (SSS, "   m_%s%s = from.m_%s;", field->name.c_str(), SPACES, field->name.c_str());
				header += SSS;
				NEW_LINE;
			}
			header += "}";
			NEW_LINE;
			NEW_LINE;


		//	����������� ������ � ������ ����������
			NEW_LINE;
			header += "// ����������� ������ � ������ ����������";						NEW_LINE;
			header += "void OC_";
			header += objtype->name.c_str();
			sprintf (SSS, "::CopyDataTo (OC_%s& to)", objtype->name.c_str()); header += SSS; NEW_LINE;
			header += "{";																							NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_CopyDataTo);", objtype->name.c_str()); header += SSS;	NEW_LINE;
			maxflen=0;
			for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
			{
				maxflen = max (maxflen, (int)field->name.length());
			}

			for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
			{
				char SPACES[256] = "                                                                               ";
				SPACES[maxflen-field->name.length()] = 0;
				sprintf (SSS, "   to.m_%s%s = m_%s;", field->name.c_str(), SPACES, field->name.c_str());
				header += SSS;
				NEW_LINE;
			}
			header += "}";
			NEW_LINE;
			NEW_LINE;

		//	����������� ������ �� ������� ����������� <<
			header += "// ����������� ������ �� ������� �����������: to << from;";		NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "&  OC_";
			header += objtype->name.c_str();
			sprintf (SSS, "::operator << (OC_%s& from)", objtype->name.c_str()); header += SSS; NEW_LINE;
			header += "{";																				NEW_LINE;
			header += "   CopyDataFrom (from);";												NEW_LINE;
			header += "   return *this;";															NEW_LINE;
			header += "}";
			NEW_LINE;
			NEW_LINE;

		//	����������� ������ � ������ ���������� >>
			header += "// ����������� ������ � ������ ����������: from >> to;";			NEW_LINE;
			header += "OC_";
			header += objtype->name.c_str();
			header += "&  OC_";
			header += objtype->name.c_str();
			sprintf (SSS, "::operator >> (OC_%s& from)", objtype->name.c_str()); header += SSS; NEW_LINE;
			header += "{";																				NEW_LINE;
			header += "   CopyDataTo (from);";													NEW_LINE;
			header += "   return *this;";															NEW_LINE;
			header += "}";
			NEW_LINE;
			NEW_LINE;
		}
		//----------------------------------------------------------------------------[] 
		
	//----------------------------------------------------------------------------[] 
	//	������ � ���������
		if (objtype->indexArr.GetSize())
		{
			header += "// ���������� ������� ������ �� ��� ��������������";		NEW_LINE;
			header += "identifier OC_";
			header += objtype->name.c_str();
			header += "::SetIndex (identifier newIndex)";							NEW_LINE;
			header += "{";																		NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_SetIndex);", objtype->name.c_str()); header += SSS;	NEW_LINE;	NEW_LINE;
			header += "   identifier oldIndex = curIndexInfo.m_id;";				NEW_LINE;
			header += "   switch (newIndex)";											NEW_LINE;
			header += "   {";																	NEW_LINE;
			for (i=0, index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++, i++)
			{
				sprintf (SSS, "      case %d: SetIndex", i); header += SSS;

				for (k=0; k < index->fieldArr.GetSize(); k++)
				{
					identifier	fid	= (identifier) index->fieldArr[k];
					bool			bAsc	= (bool)			index->fieldArr_ascend[k];
					header += bAsc? "_": "__";
					header += objtype->fieldArr[fid].name.c_str();
				}
				header += " ();"; NEW_LINE;
				header += "              return oldIndex;"; NEW_LINE;
			}
			header += "   }";																	NEW_LINE;
			header += "   SERVER_DEBUG_ERROR_2 (\"SetIndex: ������� ��������� ������������� ������� %d � ������� ������ %s \", newIndex, className[classID]);"; NEW_LINE;
			header += "   return oldIndex;"; NEW_LINE;
			header += "}";																		NEW_LINE;
			NEW_LINE;

			header += "// �������� ������������� �������� �������";				NEW_LINE;
			header += "identifier OC_";
			header += objtype->name.c_str();
			header += "::GetIndex ()";														NEW_LINE;				
			header += "{";																		NEW_LINE;
			sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_GetIndex);", objtype->name.c_str()); header += SSS;	NEW_LINE;
			header += "   return curIndexInfo.m_id;";									NEW_LINE;
			header += "}";																		NEW_LINE;
			
			NEW_LINE;			NEW_LINE;
			
			for (i=0, index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++, i++)
			{
				NEW_LINE;
				header += "// ���������� ������� ������ �� ";
				header += index->fieldArr.GetSize()>1? "������ �����": "����";
				NEW_LINE;
				header += "void OC_";
				header += objtype->name.c_str();
				header += "::SetIndex";
				for (k=0; k<index->fieldArr.GetSize(); k++)
				{
					identifier	fid	= (identifier) index->fieldArr[k];
					bool			bAsc	= (bool)			index->fieldArr_ascend[k];
					header += bAsc? "_": "__";
					header += objtype->fieldArr[fid].name.c_str();
				}
				header += " ()";
				NEW_LINE;
				header += "{";
				NEW_LINE;

				sprintf (SSS, "   DEBUG_STACK_NAME (OC_%s_SetIndex_xxx);", objtype->name.c_str()); header += SSS;	NEW_LINE;

				sprintf (SSS,"   curIndexInfo.m_id         = %d; ",i);
				header += SSS;
				NEW_LINE;
				sprintf (SSS,"   curIndexInfo.m_keyNum     = %d; ",index->fieldArr.GetSize());
				header += SSS;
				NEW_LINE;

				for (k=0; k<index->fieldArr.GetSize(); k++)
				{
					identifier fid = (identifier) index->fieldArr[k];

					sprintf (SSS,"   curIndexInfo.m_keyType[%d] = (byte)FT_%s; ", k, FT_NAME_SHORT[objtype->fieldArr[fid].type]);
					header += SSS;
					NEW_LINE;
				}
				header += "};";
				NEW_LINE;
			}

			NEW_LINE;header += "// * * * * * * * * * * * * * * * * * * * * * * * * * * ";NEW_LINE;NEW_LINE;
		}

	}		
		
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;

	return;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
#endif
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Create_ObjController_h																		[]
//                                                                            []
void CObjDriver::Create_ObjController_h (string& header)
{
	DEBUG_STACK_NAME (Create_ObjController_h);

#ifdef ZOOB_UTILS
	int	i=0,f=0;
	int   k=0;
	CPtr<CObjFormat>::Iterator objtype;
	CPtr<CFieldFormat>::Iterator field;
	CPtr<CObjIndex>::Iterator index;
	char   SSS[10240];

	header = "";

	header += "/*";
	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Lay_ObjController.h                                       []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev                                         []";	NEW_LINE;
	header += "[] Description:     Controlers for database objects                           []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Lay.h-file         []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
	NEW_LINE;
	header += "#ifndef Lay_ObjController_h";	NEW_LINE;
	header += "#define Lay_ObjController_h";	NEW_LINE;
	NEW_LINE;
	NEW_LINE;

//	�������� ���� � ��������� ���� ��������

	header += "#include \"./../../kernel/main.h\"";		NEW_LINE; // !!! -- �������� ��� include ��� �� �����
	header += "#include \"./../../kernel/OBD.h\"";		NEW_LINE;
#ifdef USE_CObject
	header += "#include \"./../../kernel/Object.h\"";	NEW_LINE;
#endif
	header += "#include \"Lay_ObjData.h\"";		NEW_LINE;
	NEW_LINE;
	NEW_LINE;


//	������
	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++) if (!objtype->isVirtual)
	{
		PRINT_CREATION_PERCENT;

		NEW_LINE; NEW_LINE; NEW_LINE; NEW_LINE;	NEW_LINE; NEW_LINE;
		header += "#ifdef  USES_OC_ALL";				NEW_LINE;
		header += "#define USES_OC_";
		header += objtype->name.c_str();				NEW_LINE;
		header += "#endif";								NEW_LINE;
		header += "#ifdef USES_OC_";
		header += objtype->name.c_str();				DELIMITER;

		header += "// ";									NEW_LINE;
		header += "// ���������� �������� ���� ������ ������ \"";
		header += objtype->name.c_str();
		header += "\"";									NEW_LINE;
		header += "// ";									NEW_LINE;

		header += "class OC_";
		header += objtype->name.c_str();

#ifdef USE_CObject
//		sprintf (SSS, ": public OC_Object <OC_%s>", objtype->name.c_str());
		sprintf (SSS, ": public OC_Object");
		header += SSS;
#endif
		NEW_LINE;
		header += "{";										
		NEW_LINE;


#ifndef USE_CObject
	//	ID �������
		header += "// ���������� ������������� ��� ������� � ������ ����� OBD";		NEW_LINE;
		header += "   protected: OBD_pointer  coPtr;";										NEW_LINE;
		header += "// ���������� �� ������������� �������";								NEW_LINE;
		header += "   protected: CIndexInfo   curIndexInfo;";								NEW_LINE;
		NEW_LINE;
#endif

	//	����������� ()
		if (objtype->isMaster)
		{
			header += "// ��� ����� ����������� ������-�������.";								NEW_LINE;
			header += "// ��� �������� ����������� �� ������������� ���������������";	NEW_LINE;
			header += "// �� ������������ ������-������ ����� ������.";						NEW_LINE;
			header += "// ��� ���� ������������ ������ �������� � ������������� (New,";NEW_LINE;
			header += "// Open, ...), �������� (Delete) � ������ � ���������.";			NEW_LINE;
			header += "   void About_class_OC_Master ();";										NEW_LINE;
			NEW_LINE;

			header += "// ����������� ������-������.";													NEW_LINE;
			header += "// ���������� ������������� ���������� �� ������!";							NEW_LINE;
			header += "// * ������������ ������ �������� � ������������� (New, Open, ...)";	NEW_LINE;
			header += "//   �������� (Delete) � ������ � ���������.";								NEW_LINE;
		}
		else
		{
			header += "// ����������� �� ��������� -- ���������� �� ���������� �� ������!";	NEW_LINE;
		}
		header += "   public: OC_";
		header += objtype->name.c_str();
		header += "  ();";

		if (!objtype->isMaster)
		{
		//	����������� (nID)
			header += "// ����������� �� �������������� -- ����������� ������ �� ����";
			NEW_LINE;
			header += "   public: OC_";
			header += objtype->name.c_str();
			sprintf (SSS, "  (identifier objID);");
			header += SSS;
			NEW_LINE;

		//	����������� (OC)
			header += "// ����������� ����������� �� ������� �����������";
			NEW_LINE;
			header += "   public: OC_";
			header += objtype->name.c_str();
			header += "  (const OC_";
			header += objtype->name.c_str();
			header +=  "& from);";
			NEW_LINE;
		}

	//	����������
		header += "// ���������� ����������� �������";
		NEW_LINE;
		header += "   public: ~OC_";
		header += objtype->name.c_str();
		header += " ();";
		NEW_LINE;
		NEW_LINE;

		if (!objtype->isMaster)
		{
		// �����������
			header += "// 1. ����������� (�����������, ������������) ������������ ������ ������";
			NEW_LINE;
			header += "// 2. �������� ������� �� ��������������";
			NEW_LINE;
			header += "   public: OC_";
			header += objtype->name.c_str();
			header += "& operator= (const OC_";
			header += objtype->name.c_str();
			header += "& from);";
			NEW_LINE;
			header += "// 1. ����������� (�����������, ������������) ������������ ������ ������";
			NEW_LINE;
			header += "// 2. �������� ������� �� ��������������";
			NEW_LINE;
			header += "   public: OC_";
			header += objtype->name.c_str();
			header += "& operator= (identifier objID);";
			NEW_LINE;
		}

	//	������������� ���������� �����
		NEW_LINE;
		header += "// ������������� ���������� ����� CSmartField<...>";				NEW_LINE;
		header += "   protected: void InitSmartFields();";									NEW_LINE;
		NEW_LINE;

	//	����������� ������ �� ������� �����������
		if (!objtype->isMaster)
		{
			NEW_LINE;
			header += "// ����������� ������ �� ������� �����������";						NEW_LINE;
			sprintf (SSS, "   public: void CopyDataFrom (OC_%s& from);", objtype->name.c_str()); header += SSS; NEW_LINE;
			NEW_LINE;


		//	����������� ������ � ������ ����������
			NEW_LINE;
			header += "// ����������� ������ � ������ ����������";						NEW_LINE;
			sprintf (SSS, "   public: void CopyDataTo (OC_%s& to);", objtype->name.c_str()); header += SSS; NEW_LINE;
			NEW_LINE;

		//	����������� ������ �� ������� ����������� <<
			header += "// ����������� ������ �� ������� �����������: to << from;";		NEW_LINE;
			sprintf (SSS, "   public: OC_%s& operator << (OC_%s& from);", objtype->name.c_str(), objtype->name.c_str()); header += SSS; NEW_LINE;
			NEW_LINE;

		//	����������� ������ � ������ ���������� >>
			header += "// ����������� ������ � ������ ����������: from >> to;";			NEW_LINE;
			sprintf (SSS, "   public: OC_%s& operator >> (OC_%s& from);", objtype->name.c_str(), objtype->name.c_str()); header += SSS; NEW_LINE;
			NEW_LINE;
		}

#ifndef USE_CObject
	//	�������� ����������
		sprintf (SSS, "// �������� ���������� � ��������� ������� �������-������");								header += SSS; NEW_LINE;
		sprintf (SSS, "   protected: void Release (OBD_pointer _coPtr=NULL);");										header += SSS; NEW_LINE;
		NEW_LINE;
		NEW_LINE;

	// �������� ������������� ������� ������� �� �������� �������
		sprintf (SSS, "// �������� ������������� ������� ������� �� �������� �������");							header += SSS; NEW_LINE
		sprintf (SSS, "   public: identifier First() const;"																header += SSS; NEW_LINE
	// �������� ������������� ���������� ������� �� �������� �������
		sprintf (SSS, "// �������� ������������� ���������� ������� �� �������� �������");						header += SSS; NEW_LINE
		sprintf (SSS, "   public: identifier Last() const;");																header += SSS; NEW_LINE

	//	���������� ������
		header += "// ���������� ������";
		header += "// ���� ������ �������� -- �������� � ������, ����� -- �� �����.";
		NEW_LINE;
		sprintf (SSS, "   public: void DebugPrint(string& dbg) const;");
		header += SSS;
		NEW_LINE;

	//	���������� ������
		header += "// ���������� ������";
		header += "// ���� ������ �������� -- �������� � ������, ����� -- �� �����.";
		NEW_LINE;
		sprintf (SSS, "   public: void DebugPrint() const;");
		header += SSS;
		NEW_LINE;

	// ��������
		header += "// �������� ����������� ������������� �����������";
		NEW_LINE;
		sprintf (SSS, "   public: bool IsValid () const;");
		header += SSS;
		NEW_LINE;
	// ��������
		header += "// �������� ����������� ������������� �����������";
		NEW_LINE;
		sprintf (SSS, "   public: operator bool () const;");
		header += SSS;
		NEW_LINE;
   

		header += "// �������� ����� �� �������� ������� ����� �����-���������";					NEW_LINE;
		header += "   public: bool operator==(key_arr& ka);";			NEW_LINE;
		header += "// �������� ����� �� �������� ������� ������ �����-���������";					NEW_LINE;
		header += "   public: bool operator< (key_arr& ka);";			NEW_LINE;
		header += "// �������� ����� �� �������� ������� ������ ��� ����� �����-���������";		NEW_LINE;
		header += "   public: bool operator<=(key_arr& ka);";			NEW_LINE;
		header += "// �������� ����� �� �������� ������� ������ �����-���������";					NEW_LINE;
		header += "   public: bool operator> (key_arr& ka);";			NEW_LINE;
		header += "// �������� ����� �� �������� ������� ������ ��� ����� �����-���������";		NEW_LINE;
		header += "   public: bool operator>=(key_arr& ka);";			NEW_LINE;
		header += "// ��������� �������� ����� �� �������� ������� � ������-����������";			NEW_LINE;
		sprintf(SSS, "   public: int  Compare   (key_arr& ka);");
		header += SSS;
		NEW_LINE;

	// ��������� == 
		header += "// ��� ����������� ��������� �� ���� ������ ���";	NEW_LINE;
		header += "// ��� �� ��������� �� �� ���� ������";					NEW_LINE;		
		header += "   public: bool operator== (const ";
		header += "OC_";
		header += objtype->name.c_str();
		sprintf (SSS, "& to);");
		header += SSS;
		NEW_LINE;

	// ��������� != 
		header += "// ��� ����������� ��������� �� ������ ������� ���";	NEW_LINE;
		header += "// ���� �� ��� ��������� �� ������, � ������ ���";		NEW_LINE;
		header += "   public: bool operator!= (const ";
		header += "OC_";
		header += objtype->name.c_str();
		sprintf (SSS, "& to);");
		header += SSS;
		NEW_LINE;


	// ��������� ���������������
		header += "// ��������� ���������������";							 NEW_LINE;
		header += "   public: bool operator== (identifier objID);";  NEW_LINE;
		header += "// ��������� ���������������";							 NEW_LINE;
		header += "   public: bool operator!= (identifier objID);";  NEW_LINE;
		header += "// �������� ������������� ��������������� �������";NEW_LINE;
		header += "   public: operator identifier () const      ;";	 NEW_LINE;

	// �������� �� ��������������
		header += "// �������� ������� �� ��������������";
		NEW_LINE;
		sprintf (SSS, "   public: void Open (identifier objID);");
		header += SSS;
		NEW_LINE;

	// �������������� ���������� ������� �� ����
		header += "// �������������� ���������� ������� �� ����";
		NEW_LINE;
		sprintf (SSS, "   public: void Save ();");
		header += SSS;
		NEW_LINE;

	// �������������� ���������� �������� ������� �� ����
		header += "// �������������� ���������� �������� ������� �� ����"; NEW_LINE;
   	header += "   public: void SaveCurIndex ();"; NEW_LINE;
	// �������������� ���������� ���� ���� �� ����
		header += "// �������������� ���������� ���� ���� �� ����"; NEW_LINE;
   	header += "   public: void SaveAllBase ();"; NEW_LINE;

	//	�������� ������ �������
		header += "// �������� ������ ������� � ���������� ��� � ����";
		header += "// ������� ���������� ������������� ������ �������";
		NEW_LINE;
		sprintf (SSS, "   public: identifier New ();");
		header += SSS;
		NEW_LINE;

	//	�������� ������� �� ����
		header += "// ������� ������ �� ���� (���� �� ���)";
		NEW_LINE;
		sprintf (SSS, "   public: void Delete ();");
		header += SSS;
		NEW_LINE;

	//	����� ID �������
		header += "// �������� ������������� ��������������� �������";
		NEW_LINE;
		sprintf (SSS, "   public: identifier GetObjectID () const;");
		header += SSS;
		NEW_LINE;

	//	����� ID ����
		header += "// �������� ������������� ������ ��������������� �������";
		NEW_LINE;
		sprintf (SSS, "   public: identifier GetClassID () const;");
		header += SSS;
		NEW_LINE;

	//______________________________________________________________________________
	//                                                                            []
	//` ������ � ����� ����� SmartFields														[]
	//                                                                            []
		NEW_LINE;
		NEW_LINE;
		NEW_LINE;
		header += "// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
		NEW_LINE;
		header += "//";
		NEW_LINE;
		header += "// ������ � ����� ����� CSmartField<..>";
		NEW_LINE;
		header += "//";
		NEW_LINE;
		NEW_LINE;
#endif
	// ������� ����
		bool bNL = true;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID")) if (!field->isArray)
		{
			header += "// ����:   ";
			header += FT_NAME_SHORT[field->type];
			header += " ";
			header += objtype->name.c_str();
			header += "::";
			header += field->name.c_str();
			NEW_LINE;
			sprintf (SSS, "   public: CSmartField      <OD_%s, %s>    m_%s;", objtype->name.c_str(), FT_NAME[field->type], field->name.c_str());
			header += SSS;
			NEW_LINE;
			bNL=false;
		}
	// �������
		bNL = true;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID")) if (field->isArray)
		{
			header += "// ����:   ";
			header += FT_NAME_SHORT[field->type];
			header += " ";
			header += objtype->name.c_str();
			header += "::";
			header += field->name.c_str();
			header += " []";
			NEW_LINE;

			sprintf (SSS, "   public: CSmartFieldArray <OD_%s, %s>    m_%s;", objtype->name.c_str(), FT_NAME[field->type], field->name.c_str());
			header += SSS;
			NEW_LINE;
			bNL=false;
		}
	//____________________________________________________________________________[]



	
	//	������ � ���������
		if (objtype->indexArr.GetSize()!=0)
		{
			NEW_LINE;
#ifndef USE_CObject
			NEW_LINE;
			NEW_LINE;
			header += "// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
			NEW_LINE;
			header += "//";
			NEW_LINE;
			header += "// ��������� ��� ������ � ���������";
			NEW_LINE;
			header += "//";
			NEW_LINE;
#endif
			header += "// ���������� ������� ������ �� ��� ��������������";		NEW_LINE;
			header += "// ���������� ������ ������";										NEW_LINE;
			header += "   identifier SetIndex (identifier newIndex);";				NEW_LINE;

			header += "// �������� ������������� �������� �������";					NEW_LINE;
			header += "   identifier GetIndex ();";										NEW_LINE;				
			
			NEW_LINE;

			for (i=0, index=objtype->indexArr.begin(); index!=objtype->indexArr.end(); index++, i++)
			{
				header += "// ���������� ������� ������ �� ";
				header += index->fieldArr.GetSize()>1? "������ ����� [": "���� [";
				for (k=0; k<index->fieldArr.GetSize(); k++)
				{
					if (k!=0)
					{					
						header += ", ";
					}
					identifier	fid	= (identifier) index->fieldArr[k];
					bool			bAsc	= (bool)			index->fieldArr_ascend[k];
					
					header += bAsc? "": "-";
					header += objtype->fieldArr[fid].name.c_str();
				}
				header += "]";

				NEW_LINE;
				header += "   public: void SetIndex";
				for (k=0; k<index->fieldArr.GetSize(); k++)
				{
					identifier	fid	= (identifier) index->fieldArr[k];
					bool			bAsc	= (bool)			index->fieldArr_ascend[k];
					header += bAsc? "_": "__";
					header += objtype->fieldArr[fid].name.c_str();
				}
				header += " ();";
				NEW_LINE;
			}
		}
	//	����� ����������� ������
		header += "};";		NEW_LINE;
		header += "#endif";	DELIMITER;
	}
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	header += "#endif";
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
#endif
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` IsLikeSpace																					[]
//                                                                            []
bool IsLikeSpace (char C)
{
	return C==' ' || C=='\t' || C=='\r' || C=='\n' || C==0;
}
//____________________________________________________________________________[]


















//______________________________________________________________________________
//                                                                            []
//` Create_ObjData_h																				[]
//                                                                            []
void CObjDriver::Create_ObjData_h (string& header)
{
	DEBUG_STACK_NAME (Create_ObjData_h);

#ifdef ZOOB_UTILS
	int	i=0,f=0;
	CPtr<CObjFormat>::Iterator objtype;
	CPtr<CFieldFormat>::Iterator field;
	char   SSS[10240];

	header = "";

	header += "/*";
	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Lay_ObjData.h                                             []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev                                         []";	NEW_LINE;
	header += "[] Description:     Data contents for database objects                        []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Lay.h-file         []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	header += "#ifndef Lay_ObjData_h";	NEW_LINE;
	header += "#define Lay_ObjData_h";	NEW_LINE;

	NEW_LINE;
	NEW_LINE;
	header += "//----------------------------------------------------------------------------[] ";	NEW_LINE;
	header += "#define LAY_MEMCPY(to, from, offset, size, maxsize, field)						   \\";	NEW_LINE;
	header += "	if (int(offset+size) > (int)maxsize)													\\";		NEW_LINE;
	header += "	{																									\\";		NEW_LINE;
	header += "		SERVER_DEBUG_ERROR_6(\"LAY_MEMCPY: ������� �������� ������������ ������.\"\\";	NEW_LINE;
	header += "			\" %s[%d].m_%s:  offset=%d size=%d filesize=%d\", 							\\";		NEW_LINE;
	header += "			className[classID], objID, #field, offset, size, maxsize);				\\";		NEW_LINE;
	header += "		return 0;																					\\";		NEW_LINE;
	header += "	}																									\\";		NEW_LINE;
	header += "	memcpy (to, from+offset, size);															 ";		NEW_LINE;
	header += "//----------------------------------------------------------------------------[]";	NEW_LINE;
	header += "#define OD_SAVE_SIMPLE_ARRAY(type,field)													\\";	NEW_LINE;
	header += "		memcpy (file.GetPtr()+nOffset, 														\\";		NEW_LINE;
	header += "			d_##field.GetPtr(), 																	\\";		NEW_LINE;
	header += "			d_##field.GetSize()*sizeof(type));												\\";		NEW_LINE;
	header += "		nOffset  += d_##field.GetSize()*sizeof(type);									";			NEW_LINE;
	header += "//----------------------------------------------------------------------------[]";	NEW_LINE;
	header += "#define OD_LOAD_SIMPLE_ARRAY(type,field)													\\";	NEW_LINE;
	header += "		LAY_MEMCPY (																				\\";		NEW_LINE;
	header += "			d_##field.GetPtr(), 																	\\";		NEW_LINE;
	header += "			file.GetPtr(),																			\\";		NEW_LINE;
	header += "			nOffset, 																				\\";		NEW_LINE;
	header += "			arr_size_##field*sizeof(type),													\\";		NEW_LINE;
	header += "			file.GetSize(),																		\\";		NEW_LINE;
	header += "		field);																						\\";		NEW_LINE;
	header += "		nOffset  += arr_size_##field*sizeof(type);";													NEW_LINE;
	header += "//----------------------------------------------------------------------------[]";	NEW_LINE;


//	�������������� �������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";
	NEW_LINE;
	header += "// �������������� �������";
	NEW_LINE;
	header += "//";
	NEW_LINE;
	header += "enum OBJ_CLASS_ID";
	NEW_LINE;
	header += "{";

	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		NEW_LINE;
		sprintf (SSS, "   OBJ_CLASS_ID_%s = %d,", objtype->name.c_str(),i);
		header += SSS;
	};
	NEW_LINE;	
	header += "   OBJ_CLASS_ID_END";
	NEW_LINE;
	header += "};";
	NEW_LINE;

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment start
#if 0  //{ Commented on 27.03.2000 by AlexV
	header += "extern char * className[];";
	DELIMITER
	NEW_LINE;

// ������� �����
	NEW_LINE;
	DELIMITER;
	header += "//";										NEW_LINE;
	header += "// ������� �����";						NEW_LINE;
	header += "//";										NEW_LINE;
	header += "class OD_BASE";							NEW_LINE;
	header += "{";											NEW_LINE;
	header += "// ������������� ������";			NEW_LINE;
	header += "   public: identifier  classID;";	NEW_LINE;
	header += "};";										DELIMITER
	NEW_LINE;


#endif //}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * Comment end *

//	������
	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++) if (!objtype->isVirtual)
	{
		PRINT_CREATION_PERCENT;
		NEW_LINE;NEW_LINE;NEW_LINE;NEW_LINE;NEW_LINE;DELIMITER;
		header += "// ";							NEW_LINE;
		header += "// ������-������ ��� ������ ";
		header += "\"";
		header += objtype->name.c_str();
		header += "\"";									NEW_LINE;
		header += "// ";									NEW_LINE;
		header += "#ifdef  USES_OC_ALL";				NEW_LINE;
		header += "#define USES_OC_";
		header += objtype->name.c_str();				NEW_LINE;
		header += "#endif";								NEW_LINE;
		header += "#ifdef USES_OC_";
		header += objtype->name.c_str();				NEW_LINE;

		header += "class ";
		header += "OD_";
		header += objtype->name.c_str();
		header += ": public OD_BASE";			NEW_LINE;
		header += "{";								NEW_LINE;
		header += "public:";						NEW_LINE;


	//----------------------------------------------------------------------------[] 
	//	�����������
		header += "// �����������";		NEW_LINE;
		header += "   OD_";
		header += objtype->name.c_str();
		header += " (bool bFieldsInit);";	
		NEW_LINE;
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// ����������
		header += "// ����������";				NEW_LINE;
		header += "  ~OD_"; 
		header += objtype->name.c_str();	
		header += " ();";
		NEW_LINE;
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	// �������� ������ ������
		bool bCanCreate_ka = false;
		int  maxfieldname = 0;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
		{
			if (f!=0 && field->isArray==false)
			{
				bCanCreate_ka = true;
				maxfieldname  = max (maxfieldname, (int)field->name.length());
			}
		}
		if (bCanCreate_ka)
		{
			header += "// �������� �������� ������ ������";										NEW_LINE;
			header += "   void AddKeyVarForField (key_arr& ka, identifier fieldID);";	NEW_LINE;
			NEW_LINE;
		}
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	//	����
		header += "// ����-������";
		NEW_LINE;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
		{
			header += "   ";
			if (field->isArray)
				header += FT_NAME_ARR[field->type];
			else 
				header += FT_NAME[field->type];

			header += "d_";
			header += field->name.c_str();
			header += ";";
			NEW_LINE;
		}
	//----------------------------------------------------------------------------[] 










	//----------------------------------------------------------------------------[] 
	//	�������� � ����� 
		NEW_LINE;
		header += "// �������� ������� � �����";								NEW_LINE;
		header += "   size_t LoadFromFile (identifier objID);";			NEW_LINE;
	//----------------------------------------------------------------------------[]









	//----------------------------------------------------------------------------[] 
	//	������� �������
		NEW_LINE;
		NEW_LINE;
		header += "// ������� ������� ������� ��� ��������� �� ����";	NEW_LINE;
		header += "   size_t CalculateSize ();";								NEW_LINE;
	//----------------------------------------------------------------------------[] 









	//----------------------------------------------------------------------------[] 
	//	������ �� ����
		NEW_LINE;
		header += "// ������ ������ �� ����";								NEW_LINE;
		header += "   bool WriteToFile (identifier objID);";			NEW_LINE;
	//----------------------------------------------------------------------------[] 





	//----------------------------------------------------------------------------[] 
	//	���������� ������
		NEW_LINE;
		header += "// ���������� ������";					NEW_LINE;
		header += "   bool DebugPrint (string& dbg, identifier objID);";	NEW_LINE;
	//----------------------------------------------------------------------------[] 




	//	����� ����������� ������
		header += "};";				NEW_LINE;
		header += "#endif";			DELIMITER;
	}

	NEW_LINE;
	NEW_LINE;
	header += "#endif";				NEW_LINE;
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
#endif
}
//____________________________________________________________________________[]













//______________________________________________________________________________
//                                                                            []
//` CreateConstructor                                                         []                 
//                                                                            []
void CreateConstructor (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateConstructor);

#ifdef ZOOB_UTILS
	int i, f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	header += "// �����������";		NEW_LINE;
	header += "   OD_";
	header += objtype->name.c_str();
	header += "::OD_";
	header += objtype->name.c_str();
	header += " (bool bFieldsInit)";	NEW_LINE;
	header += "   {";						NEW_LINE;

	sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_OD_%s);", objtype->name.c_str(), objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;

	header += "      classID = ";
	sprintf (SSS, "OBJ_CLASS_ID_%s;", objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	sprintf    (SSS, "      m_CoIndexPtr = new OBD_pointer [%d];", (int)objtype->indexArr.GetSize());
	header += SSS;
	NEW_LINE;
	for (i = 0; i<(int)objtype->indexArr.GetSize(); i++)
	{
		sprintf (SSS, "      m_CoIndexPtr[%d] = NULL;", i);
		header += SSS;
		NEW_LINE;
	}
	header += "      if (!bFieldsInit) return;";											NEW_LINE;
	NEW_LINE;
	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID"))
	{
	// INIT -- �������� �� ���������.
		if ((field->isArray || field->defValue!=""))
		{
			if (field->isArray)
			{
				header += "      d_";
				header += field->name.c_str();
				header += ".Alloc (0);";
				NEW_LINE;
			}
			else
			{
				header += "      d_";
				header += field->name.c_str();
				header += " = ";
				header += field->type==FT_float? "(float) ": "";
				
				if (field->type==FT_string)
					header += "\"";

				header += field->defValue;

				if (field->type==FT_string)
					header += "\"";

				header += ";";
				NEW_LINE;
			}
		}
	}

	header += "   }";
	NEW_LINE;
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void) objtype;
#endif
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` �������� ������ ������                                                    []                      
//                                                                            []
void CreateKeySet (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateKeySet);

#ifdef ZOOB_UTILS
	int f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	bool bCanCreate_ka = false;
	int  maxfieldname = 0;
	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
	{
		if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID") && field->isArray==false)
		{
			bCanCreate_ka = true;
			maxfieldname  = max (maxfieldname, (int)field->name.length());
		}
	}
	if (bCanCreate_ka)
	{
		header += "// �������� �������� ������ ������";										NEW_LINE;
		header += "   void OD_";
		header += objtype->name.c_str();
		header += "::AddKeyVarForField (key_arr& ka, identifier fieldID)";			NEW_LINE;
		header += "   {";																				NEW_LINE;

		sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_AddKeyVarForField);", objtype->name.c_str()); header += SSS;	NEW_LINE;
		NEW_LINE;

		header += "      switch (fieldID)";														NEW_LINE;
		header += "      {";																			NEW_LINE;

		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++) if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID"))
		{
			if (field->isArray==false)
			{
				char SSS_KA[256] = "                                                                 ";
				int len = field->name.length();
				SSS_KA[maxfieldname-len] =0;
				sprintf (SSS, "         case %d: ka += d_%s;%s      break;", f, field->name.c_str(), SSS_KA);
				header += SSS;																							NEW_LINE;
			}
		}
		header += "      }";																							NEW_LINE;
		header += "   }";																								NEW_LINE;
		NEW_LINE;
	}
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void)objtype;
#endif
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` �������� � �����                                                          []                 
//                                                                            []
void CreateLoadFromDisk (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateLoadFromDisk);

#ifdef ZOOB_UTILS
	int f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	NEW_LINE;
	header += "// �������� ������� � �����";								NEW_LINE;
	header += "   size_t OD_";
	header += objtype->name.c_str();
	header += "::LoadFromFile (identifier objID)";						NEW_LINE;
	header += "   {";																NEW_LINE;

	sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_LoadFromFile);", objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;

	header += "      CFile file;";											NEW_LINE;
	header += "      if (!file.Exist(objID))";							NEW_LINE;
	header += "          return false;";									NEW_LINE;
	header += "      file.Open (objID);";									NEW_LINE;
	header += "      file.Load ();";						  					NEW_LINE;
	NEW_LINE;
	header += "      size_t nOffset=0;";
	NEW_LINE;
	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
	{
		NEW_LINE;

	// ��������� ������������� ������
		if (f==0) 
		{
			header += "   // �������� ��������������";
			NEW_LINE;
			header += "      identifier tmp_classID = (*(identifier*)(file+nOffset));";
			NEW_LINE;
			header += field->isArray? "   ": "";
			header += "      nOffset += sizeof(";
			header += FT_NAME_SHORT[field->type];
			header += ");";
			NEW_LINE;
			header += "      if (tmp_classID!=classID)";																							NEW_LINE
			header += "      {";																															NEW_LINE
			header += "         if (!bIGNORE_LOAD_ERROR) {SERVER_DEBUG_ERROR_3 (\"������������ ���� ��� ���������� ������� %d (���!='%s'); tmp_classID==%d\", objID, className[classID], classID);}";	NEW_LINE
			header += "         return 0;";																											NEW_LINE;
			header += "      }";																															NEW_LINE
			continue;
		}

		header += "   // ";
		header += FT_NAME_SHORT[field->type];
		header += " ";
		header += field->name.c_str();
		if (field->isArray)
		{
			header += " []";
		}
		NEW_LINE;

		if (field->isArray)
		{
			header += "      int arr_size_";
			header += field->name.c_str();
			header += " = (*(size_t*)(file+nOffset));";			
			NEW_LINE;
			header += "      nOffset += sizeof(size_t);";
			NEW_LINE;
			header += "      d_";
			header += field->name.c_str();
			header += ".Alloc (";
			header += "arr_size_";
			header += field->name.c_str();
			header += ");";
			NEW_LINE;

			if (field->type==FT_string)
			{
				sprintf (SSS, "      for (int i%s=0; i%s<(int)arr_size_%s; i%s++)", field->name.c_str(),field->name.c_str(),field->name.c_str(),field->name.c_str());
				header += SSS;
				NEW_LINE;
				header += "      {";
				NEW_LINE;
				header += "         ";
				header += FT_NAME_SHORT[field->type];
				header += " tmp_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;
			}
			else
			{
				header += "      OD_LOAD_SIMPLE_ARRAY (";
				header += FT_NAME_SHORT[field->type];
				header += ",";
				header += field->name.c_str();
				header += ");";
				NEW_LINE;
			}
		}


		if ((!field->isArray) || (field->type==FT_string)) switch (field->type)
		{
			case FT_int:
			case FT_byte:
			case FT_bool:
			case FT_float:
			case FT_identifier:
			case FT_guid:
				header += field->isArray? "   ": "";
				header += field->isArray? "      tmp_": "      d_";
				header += field->name.c_str();
				header += " = (*(";
				header += FT_NAME_SHORT[field->type];
				header += "*)(file+nOffset));";
				NEW_LINE;
				header += field->isArray? "   ": "";
				header += "      nOffset += sizeof(";
				header += FT_NAME_SHORT[field->type];
				header += ");";
				NEW_LINE;
			break;

			case FT_string:
				header += field->isArray? "   ": "";
				header += "      size_t n_";
				header += field->name.c_str();
				header += " = (*(size_t*)(file+nOffset));";
				header += "  // n_";
				header += field->name.c_str();
				header += " = strlen (s_";
				header += field->name.c_str();
				header += ")+1;";
				NEW_LINE;
				header += field->isArray? "   ": "";
				header += "      nOffset += sizeof(size_t);";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      char * s_";
				header += field->name.c_str();
				header += " = new char [n_";
				header += field->name.c_str();
				header += "+1];";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      LAY_MEMCPY (s_";
				header += field->name.c_str();
				header += ", file, nOffset, n_";
				header += field->name.c_str();
				header += ", file.GetSize(), ";
				header += field->name.c_str();
				header += ");";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      nOffset += n_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      DECODE_STRING (n_";
				header += field->name.c_str();
				header += ", s_";
				header += field->name.c_str();
				header += ");";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += field->isArray? "      tmp_": "      d_";
				header += field->name.c_str();
				header += " = s_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      delete [] s_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;
			break;

			default:
				SERVER_DEBUG_ERROR ("Unknown field->type");
			return;
		}

		if (field->isArray && (field->type==FT_string))
		{
			NEW_LINE;
			sprintf (SSS, "         d_%s[i%s] = tmp_%s;", field->name.c_str(),field->name.c_str(),field->name.c_str());
			header += SSS;
			NEW_LINE;
			header += "      }";
			NEW_LINE;
		}
	} 
	header += "      return nOffset;";
	NEW_LINE;
	header += "   }";
	NEW_LINE;
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void) objtype;
#endif
}
//____________________________________________________________________________[]









//______________________________________________________________________________
//                                                                            []
//` ������� �������                                                           []                
//                                                                            []
void CreateCalculateSize (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateCalculateSize);

#ifdef ZOOB_UTILS
	int f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	NEW_LINE;
	NEW_LINE;

	header += "// ������� ������� ������� ��� ��������� �� ����";	NEW_LINE;
	header += "   size_t OD_";
	header += objtype->name.c_str();
	header += "::CalculateSize ()";											NEW_LINE;
	header += "   {";																NEW_LINE;

	sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_CalculateSize);", objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;

	header += "      size_t n_size=0;";										NEW_LINE;

	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
	{
		NEW_LINE;
		header += "   // ";
		header += FT_NAME_SHORT[field->type];
		header += " ";
		header += field->name.c_str();
		if (field->isArray) header += " []";

		NEW_LINE;
		if (field->isArray)
		{
			header += "      n_size += sizeof (size_t);";
			NEW_LINE;

			if (field->type == FT_string)
			{
				sprintf (SSS, "      for (int i%s=0; i%s<d_%s.GetSize(); i%s++)", field->name.c_str(),field->name.c_str(),field->name.c_str(),field->name.c_str());
				header += SSS;
				NEW_LINE;
				header += "      {";
				NEW_LINE;
			}
			else
			{
				header += "      n_size += d_";
				header += field->name.c_str();
				header += ".GetSize() * ";

				header += "sizeof(";
				header += FT_NAME_SHORT[field->type];
				header += ");";
				NEW_LINE;
			}
		}

		if (!field->isArray || field->type == FT_string) switch (field->type)
		{
			case FT_int:
			case FT_byte:
			case FT_bool:
			case FT_float:
			case FT_identifier:
			case FT_guid:
				header += field->isArray? "   ": "";
				header += "      n_size += sizeof (";
				header += FT_NAME_SHORT[field->type];
				header += ");";
				NEW_LINE;
			break;

			case FT_string:
				header += field->isArray? "   ": "";
				header += "      n_size += sizeof (size_t);";
				NEW_LINE;
				header += field->isArray? "   ": "";
				header += "      n_size += d_";
				header += field->name.c_str();
				if (field->isArray)
				{
					header += "[i";
					header += field->name.c_str();
					header += "]";
				}
				header += ".length()+1;";
				NEW_LINE;
			break;

			default:
				SERVER_DEBUG_ERROR("Unknown field->type");
			return;
		}

		if (field->isArray && field->type == FT_string)
		{
			header += "      }";
			NEW_LINE;
		}
	}
	NEW_LINE;
	header += "      return n_size;"; 		NEW_LINE;
	header += "   }";								NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void) objtype;
#endif
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` ������ �� ����                                                            []              
//                                                                            []
void CreateWriteToDisk (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateWriteToDisk);

#ifdef ZOOB_UTILS
	int f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	NEW_LINE;
	header += "// ������ ������ �� ����";								NEW_LINE;
	header += "   bool OD_";
	header += objtype->name.c_str();
	header += "::WriteToFile (identifier objID)";					NEW_LINE;
	header += "   {";															NEW_LINE;

	sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_WriteToFile);", objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;

	header += "      CFile file;";										NEW_LINE;
	header += "      if (!file.Exist(objID))";						NEW_LINE;
	header += "          return false;";								NEW_LINE;
	header += "      file.Open (objID);";								NEW_LINE;
	header += "      size_t n_size = CalculateSize ();";			NEW_LINE;
	header += "      file.Alloc (n_size);";							NEW_LINE;

	NEW_LINE;
	header += "      size_t nOffset=0;";
	NEW_LINE;
	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
	{
		NEW_LINE;

		header += "   // ";
		header += FT_NAME_SHORT[field->type];
		header += " ";
		header += field->name.c_str();
		if (field->isArray) header += " []";
		NEW_LINE;

		if (field->isArray)
		{
			header += "      (*(size_t*)(file+nOffset)) = d_";
			header += field->name.c_str();
			header += ".GetSize();";
			NEW_LINE;
			header += "      nOffset += sizeof(size_t);";
			NEW_LINE;

			if (field->type==FT_string)
			{
				sprintf (SSS, "      for (int i%s=0; i%s<d_%s.GetSize(); i%s++)", field->name.c_str(),field->name.c_str(),field->name.c_str(),field->name.c_str());
				header += SSS;
				NEW_LINE;
				header += "      {";
				NEW_LINE;
			}
			else
			{
				header += "      OD_SAVE_SIMPLE_ARRAY (";
				header += FT_NAME_SHORT[field->type];
				header += ",";
				header += field->name.c_str();
				header += ");";
				NEW_LINE;
			}
		}


		if ((!field->isArray) || (field->type==FT_string)) switch (field->type)
		{
			case FT_int:
			case FT_byte:
			case FT_bool:
			case FT_float:
			case FT_identifier:
			case FT_guid:
				header += field->isArray? "         ": "      ";
				header += "(*(";
				header += FT_NAME_SHORT[field->type];
				header += "*)(file+nOffset)) = ";
				if (f!=0) header += "d_";
				header += field->name.c_str();
				if (field->isArray) 
				{
					header += "[i";
					header += field->name.c_str();
					header += "]";
				}
				header += ";";
				NEW_LINE;
				header += field->isArray? "         ": "      ";
				header += "nOffset += sizeof (";
				header += FT_NAME_SHORT[field->type];
				header += ");";
				NEW_LINE;
			break;

			case FT_string:
				header += field->isArray? "   ": "";
				header += "      size_t n_";
				header += field->name.c_str();
				header += " = d_";
				header += field->name.c_str();
				if (field->isArray)
				{
					header += "[i";
					header += field->name.c_str();
					header += "]";
				}
				header += ".length()+1;";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      (*(size_t";
				header += "*)(file+nOffset)) = n_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      nOffset += sizeof (size_t);";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      memcpy ((file+nOffset), d_";
				header += field->name.c_str();
				if (field->isArray) 
				{
					header += "[i";
					header += field->name.c_str();
					header += "]";
				}
				header += ".c_str(), n_";
				header += field->name.c_str();
				header += ");";
				NEW_LINE;

				header += field->isArray? "   ": "";
				header += "      ENCODE_STRING (n_";
				header += field->name.c_str();
				header += ", (char*)(file+nOffset));";
				NEW_LINE;


				header += field->isArray? "   ": "";
				header += "      nOffset += n_";
				header += field->name.c_str();
				header += ";";
				NEW_LINE;
			break;

			default:
				SERVER_DEBUG_ERROR ("Unknown field->type");
			return;
		}

		if (field->isArray && (field->type==FT_string))
		{
			header += "      }";
			NEW_LINE;
		}
	} 
	header += "      file.Save();";	NEW_LINE;
	header += "      return true;";	NEW_LINE;
	header += "   }";						NEW_LINE;
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void) objtype;
#endif
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` ���������� ������                                                         []                 
//                                                                            []
void CreateDebugPrint (string& header, CPtr<CObjFormat>::Iterator& objtype)
{
	DEBUG_STACK_NAME (CreateDebugPrint);

#ifdef ZOOB_UTILS
	int f;
	char SSS[10240];
	CPtr<CFieldFormat>::Iterator field;

	NEW_LINE;
	header += "// ���������� ������";									NEW_LINE;
	header += "   bool OD_";
	header += objtype->name.c_str();
	header += "::DebugPrint (string& dbg, identifier objID)";	NEW_LINE;
	header += "   {";															NEW_LINE;

	sprintf (SSS, "   DEBUG_STACK_NAME (OD_%s_DebugPrint);", objtype->name.c_str()); header += SSS;	NEW_LINE;
	NEW_LINE;

	header += "      string SSS;";
	NEW_LINE;
	
	header += "      dbg += \"\\n\\n------------------------------------------\\n\";"; NEW_LINE;
	sprintf (SSS, "      SSS.Format (\"[%%s: ID=%%d RN=%%d]\\n\\n\", className[OBJ_CLASS_ID_%s], objID, d_randID);", objtype->name.c_str());
	header += SSS;
	NEW_LINE;
	header += "      dbg += SSS;";
	NEW_LINE;

	for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)  if (strcmp (field->name.c_str(), "classID") && strcmp(field->name.c_str(),"randID"))
	{
		NEW_LINE;
		header += "   // ";
		header += FT_NAME_SHORT[field->type];
		header += " ";
		header += field->name.c_str();
		if (field->isArray) header += " []";

		NEW_LINE;
		if (field->isArray)
		{
			sprintf (SSS, "      SSS.Format (\"%s[].size = %%d:\\n\", d_%s.GetSize());", field->name.c_str(), field->name.c_str());
			header += SSS;
			NEW_LINE;
			header +=     "      dbg += SSS;";
			NEW_LINE;
			sprintf (SSS, "      for (int i%s=0; i%s<d_%s.GetSize(); i%s++)", field->name.c_str(),field->name.c_str(),field->name.c_str(),field->name.c_str());
			header += SSS;
			NEW_LINE;
			header += "      {";
			NEW_LINE;
		}


		header += field->isArray? "         ": "      ";
		char SSS0[1024]="";
		char SSS1[1024]="";
		char SSS2[1024]="";
		char SSS4[1024]="";
		if (field->isArray)
		{
			sprintf (SSS0, "   ");
			sprintf (SSS1, "[%%d]");
			sprintf (SSS2, "[i%s]", field->name.c_str());
			sprintf (SSS4, "i%s, ", field->name.c_str());
		}

		switch (field->type)
		{
			case FT_int:
			case FT_byte:
			case FT_identifier:
				sprintf (SSS, "SSS.Format (\"%s%s%s = %%d\\n\", %s%s%s%s);", SSS0, field->name.c_str(), SSS1, SSS4, f==0?"":"d_", field->name.c_str(), SSS2);
			break;

			case FT_guid:
				sprintf (SSS, "SSS.Format (\"%s%s%s = {%%d,%%d,%%d}\\n\", %sd_%s%s.cl, %sd_%s%s.id, %sd_%s%s.rn);", 
													 SSS0, field->name.c_str(), SSS1, 
																							SSS4, field->name.c_str(), SSS2, 
																												SSS4, field->name.c_str(), SSS2,
																																SSS4, field->name.c_str(), SSS2);
			break;

			case FT_bool:
				sprintf (SSS, "SSS.Format (\"%s%s%s = %%s\\n\", %sd_%s%s?\"true\":\"false\");", SSS0, field->name.c_str(), SSS1, SSS4, field->name.c_str(), SSS2);
			break;

			case FT_float:
				sprintf (SSS, "SSS.Format (\"%s%s%s = %%f\\n\", %sd_%s%s);", SSS0, field->name.c_str(), SSS1, SSS4, field->name.c_str(), SSS2);
			break;

			case FT_string:
				sprintf (SSS, "SSS.Format (\"%s%s%s = '%%s'\\n\", %sd_%s%s.c_str());", SSS0, field->name.c_str(), SSS1, SSS4, field->name.c_str(), SSS2);
			break;
		}
		header += SSS;
		NEW_LINE;
		header += field->isArray? "         ": "      ";
		header += "dbg += SSS;";
		NEW_LINE;

		if (field->isArray)
		{
			header += "      }";
			NEW_LINE;
		}
	}
	header += "      dbg += \"\\n\";";
	NEW_LINE;
	header += "      return true;";
	NEW_LINE;
	header += "   }";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void) objtype;
#endif
}
//____________________________________________________________________________[]






//______________________________________________________________________________
//                                                                            []
//` Create_ObjData_cpp																			[]
//                                                                            []
void CObjDriver::Create_ObjData_cpp (string& header)
{
	DEBUG_STACK_NAME (Create_ObjData_cpp);

#ifdef ZOOB_UTILS
	CPtr<CObjFormat>::Iterator objtype;

	header = "";

	header += "/*";
	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Lay_ObjData.cpp                                           []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev                                         []";	NEW_LINE;
	header += "[] Description:     Data contents for database objects                        []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Lay.h-file         []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;

	NEW_LINE;
	header += "#define USES_OC_ALL";							NEW_LINE;
	NEW_LINE;
	header += "#define USES_key_arr_h";						NEW_LINE;
	header += "#define USES_ObjDriver_h";					NEW_LINE;
	NEW_LINE;
	header += "#include \"./../../kernel/main.h\"";		NEW_LINE;
	header += "#include \"./../../kernel/OBD.h\"";		NEW_LINE;
	header += "#include \"Lay_ObjData.h\"";				NEW_LINE;
	NEW_LINE;
	header += "bool bIGNORE_LOAD_ERROR=true;";			NEW_LINE;
	NEW_LINE;
	NEW_LINE;

//	�������������� ������ 
	NEW_LINE;
	NEW_LINE;
	header += "char * className[10240]=";	NEW_LINE;
	header += "{";	NEW_LINE;

	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++)
	{
		if (objtype!=m_FormatArr.begin()) 
		{
			header += ","; NEW_LINE;
		}
		header += "   \"";
		header += objtype->name.c_str();
		header += "\"";
	}
	NEW_LINE;
	header += "};";

	NEW_LINE;
	NEW_LINE;
	NEW_LINE;

	for (objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++) if (!objtype->isVirtual)
	{
		PRINT_CREATION_PERCENT;
		string tmp;

		// �����������
		CreateConstructor (header, objtype);


		// ����������
		header += "// ����������";				NEW_LINE;
		header += "  OD_"; 
		header += objtype->name.c_str();	
		header += "::~OD_"; 
		header += objtype->name.c_str();	
		header += " () {classID = NA; delete [] m_CoIndexPtr; m_CoIndexPtr=NULL;}";		NEW_LINE;
		NEW_LINE;
		NEW_LINE;

		// �������� ������ ������
		CreateKeySet			(header, objtype);

		// �������� � �����
		CreateLoadFromDisk	(header, objtype);

		// ������� �������
		CreateCalculateSize	(header, objtype);

		// ������ �� ����
		CreateWriteToDisk		(header, objtype);

		// ���������� ������
		CreateDebugPrint		(header, objtype);

	}


	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
#endif
}
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Create_Stubs_h																				[]
//                                                                            []
void CObjDriver::Create_Stubs_h (string& header)
{
	DEBUG_STACK_NAME (Create_Stubs_h);

#ifdef ZOOB_UTILS
	int	i=0;
	CPtr<CObjFormat>::Iterator objtype;
	char   SSS[10240];

	header = "";

	header += "/*";	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Lay_Stubs.cpp															  []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev                                         []";	NEW_LINE;
	header += "[] Description:     ������ ������� ��� ����� ������������                     []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Lay.h-file         []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
	header += "#ifndef Lay_Stubs_H";			NEW_LINE;
	header += "#define Lay_Stubs_H";			NEW_LINE;
	NEW_LINE;

	header += "#define USES_OC_ALL";						NEW_LINE;
	header += "#include \"./../../kernel/main.h\"";			NEW_LINE;
	header += "#include \"./../../kernel/OBD.h\"";			NEW_LINE;
	header += "#include \"Lay_ObjData.h\"";			NEW_LINE;

// �����������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// �����������";																	NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "void * new_OD (identifier classID, bool bInit)";							NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (new_OD);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return new OD_%s (bInit);", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)bInit;";								NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return NULL;";																	NEW_LINE;
	header += "}";																						DELIMITER;
	


// ����������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ����������";																		NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "void delete_pData (identifier classID, void * pData)";					NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (delete_pData);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: delete ((OD_%s*)pData); return;", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData;";								NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "}";																						DELIMITER;



// ������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ������";																			NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "bool pData_DebugPrint (identifier classID, void * pData, string& dbg, identifier objID)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_DebugPrint);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return ((OD_%s*)pData)->DebugPrint(dbg, objID);", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData; (void)objID; (void)dbg;";NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return false;";																	NEW_LINE;
	header += "}";																						DELIMITER;



// ����������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ����������";																		NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "bool pData_WriteToFile (identifier classID, void * pData, identifier objID)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_WriteToFile);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return ((OD_%s*)pData)->WriteToFile (objID);", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData; (void)objID;";				NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return false;";																	NEW_LINE;
	header += "}";																						DELIMITER;



// ��������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ��������";																		NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "size_t pData_LoadFromFile (identifier classID, void * pData, identifier objID)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_LoadFromFile);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return ((OD_%s*)pData)->LoadFromFile (objID);", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData; (void)objID;";				NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return 0;";																	NEW_LINE;
	header += "}";																						DELIMITER;



// ��������� ��������� � �������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ��������� ��������� � �������";											NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "void pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID, OBD_pointer coIndexPtr)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_m_CoIndexPtr);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: ((OD_%s*)pData)->m_CoIndexPtr[indexID] = coIndexPtr; return;", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData; (void)indexID; (void)coIndexPtr;";NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "}";																						DELIMITER;



// ��������� ��������� � �������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ��������� ��������� � �������";											NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "OBD_pointer pData_m_CoIndexPtr (identifier classID, void * pData, identifier indexID)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_m_CoIndexPtr);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return ((OD_%s*)pData)->m_CoIndexPtr[indexID];", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData; (void)indexID;";			NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return NULL;";																	NEW_LINE;
	header += "}";																						DELIMITER;



// ������������� ������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ������������� ������";														NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "identifier pData_classID (identifier classID, void * pData)";		NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_classID);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		sprintf (SSS, "      case OBJ_CLASS_ID_%s: return ((OD_%s*)pData)->classID;", objtype->name.c_str(), objtype->name.c_str());
		header += SSS; NEW_LINE;
	};
	header += "      case -1: (void)classID; (void)pData;";								NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "   return NA;";																		NEW_LINE;
	header += "}";																						DELIMITER;



// ���������� ������
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	DELIMITER;
	header += "//";																					NEW_LINE;
	header += "// ���������� ������";															NEW_LINE;
	header += "//";																					NEW_LINE;
	header += "void pData_AddKeyVarForField (identifier classID, void * pData, key_arr& ka, identifier fieldID)"; NEW_LINE;
	header += "{";																						NEW_LINE;
	sprintf (SSS, "   DEBUG_STACK_NAME (pData_AddKeyVarForField);"); header += SSS; NEW_LINE; NEW_LINE;
	header += "   switch (classID)";																NEW_LINE;
	header += "   {";																					NEW_LINE;
	for (i=0, objtype=m_FormatArr.begin(); objtype!=m_FormatArr.end(); objtype++, i++) if (!objtype->isVirtual)
	{
		bool bCanCreate_ka = false;
		int  maxfieldname = 0;
		int f;
		CPtr<CFieldFormat>::Iterator field;
		for (f=0, field=objtype->fieldArr.begin(); field!=objtype->fieldArr.end(); field++, f++)
		{
			if (strcmp (field->name.c_str(), "classID") && strcmp (field->name.c_str(), "randID") && field->isArray==false)
			{
				bCanCreate_ka = true;
				maxfieldname  = max (maxfieldname, (int)field->name.length());
			}
		}
		if (bCanCreate_ka)
		{
			sprintf (SSS, "      case OBJ_CLASS_ID_%s: ((OD_%s*)pData)->AddKeyVarForField (ka, fieldID ); return;", objtype->name.c_str(), objtype->name.c_str());
			header += SSS; NEW_LINE;
		}
	};
	header += "      case -1: (void)classID; (void)pData; (void)ka; (void)fieldID;";NEW_LINE;
	header += "   }";																					NEW_LINE;
	header += "   SERVER_DEBUG_ERROR_1 (\"����������� ����� %d\", classID);";		NEW_LINE;
	header += "}";																						DELIMITER;


	
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	header += "#endif";
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
#endif
}
//____________________________________________________________________________[]







/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` �������� ������� ������������ �������                                     []
[]                                                                            []
[]____________________________________________________________________________*/

INTERFACE_FORMAT_ARG::INTERFACE_FORMAT_ARG ()
{
	return;
}

INTERFACE_FORMAT_ARG::INTERFACE_FORMAT_ARG (const INTERFACE_FORMAT_ARG& from)
{
	Name			= from.Name;
	Description	= from.Description;
}

INTERFACE_FORMAT_ARG& INTERFACE_FORMAT_ARG::operator= (const INTERFACE_FORMAT_ARG& from)
{
	Name			= from.Name;
	Description	= from.Description;
	return *this;
}

INTERFACE_FORMAT::INTERFACE_FORMAT ()
{
	return;
}

INTERFACE_FORMAT::INTERFACE_FORMAT (const INTERFACE_FORMAT& from)
{
	Description = from.Description;
	ObjName		= from.ObjName;
	Action		= from.Action;
	InArg			= from.InArg;
	OutArg		= from.OutArg;
}

INTERFACE_FORMAT& INTERFACE_FORMAT::operator= (const INTERFACE_FORMAT& from)
{
	Description = from.Description;
	ObjName		= from.ObjName;
	Action		= from.Action;
	InArg			= from.InArg;
	OutArg		= from.OutArg;
	return *this;
}

void INTERFACE_FORMAT::Erase()
{
	Description.Erase();
	ObjName.Erase();
	Action.Erase();
	InArg.Erase();
	OutArg.Erase();
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` CompileInterface                                                          []                
//                                                                            []
void CObjDriver::CompileInterface (CPtr<INTERFACE_FORMAT>& Format, const char * sFile, string& Prefix)
{
	DEBUG_STACK_NAME (CompileInterface);

#ifdef ZOOB_UTILS
	Format.Erase ();
	CPtr <byte> Src;
	size_t nLen = Src.ReadFile(sFile);
	Src[nLen] = 0;
	if (nLen<=0)
	{
		return;
	}

	int i, j;

// ������ ������ �����
	string_arr sArr;
	string tmpString="";
	for (i=0, j=0; i<(int)nLen; i++)
	{
		if (Src[i]=='\r' || Src[i]=='\n')
		{
			sArr += tmpString;
			tmpString = "";

			if (Src[i+1]=='\r' || Src[i+1]=='\n') i++;
		}
		else{
			tmpString += Src[i];
		}
	}


// ������������ ������ �����
	INTERFACE_FORMAT curFunc;
	for (i=0; i<sArr.Size(); i++)
	{
		char C = sArr[i][0];
		switch (C)
		{
		case '@': // ��������
			curFunc.Description = sArr[i].GetPtr()+1;
			curFunc.Description.trim ();
		break;

		case '#': // �������
			Prefix = sArr[i].GetPtr()+1;
			Prefix.trim ();
		break;

		case '&': // ������
			curFunc.ObjName = sArr[i].GetPtr()+1;
			curFunc.ObjName.trim ();
		break;

		case '.': // ��������
			curFunc.Action = sArr[i].GetPtr()+1;
			curFunc.Action.trim ();
		break;

		case '<': // ������� ��������
		case '>': // �������� ��������
		{
			INTERFACE_FORMAT_ARG curArg;
			for (j=1; j< (int)sArr[i].Len() && !IsLikeSpace(sArr[i][j]); j++)
			{
				curArg.Name += sArr[i][j];
			}
			for (; j<(int)sArr[i].Len() && IsLikeSpace(sArr[i][j]); j++)
			{
				// ���������� �������
			}
			curArg.Description = sArr[i].GetPtr()+j;
			curArg.Description.trim ();
			
			if (C=='<')
				curFunc.InArg += curArg;
			if (C=='>')
				curFunc.OutArg += curArg;
		}
		break;

		default:
			if (curFunc.ObjName!="")
			{
				Format.Add (curFunc);
				curFunc.Erase();
			}
		break;
		}
	}
	if (curFunc.ObjName!="")
	{
		Format.Add (curFunc);
		curFunc.Erase();
	}
#else
	(void)Format;
	(void)sFile;
	(void)Prefix;
#endif
}
//____________________________________________________________________________[]








//______________________________________________________________________________
//                                                                            []
//` Create_Interface_Auto_h																	[]
//                                                                            []
void CObjDriver::Create_Interface_Auto_h (string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix)
{
	DEBUG_STACK_NAME (Create_Interface_Auto_h);

#ifdef ZOOB_UTILS
	int	 i=0;
	char   SSS[10240];
	header = "";

	(void) i;
	(void) SSS;
	(void) header;

	header += "/*";	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Interface_Auto.h                                          []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev, Alex Vershinin                         []";	NEW_LINE;
	header += "[] Description:     ��������� ������������ ������� ��� ������ � ����� ������. []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Interface.h-file   []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
	header += "#ifndef Interface_Auto_H"; NEW_LINE;
	header += "#define Interface_Auto_H"; NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;


	//----------------------------------------------------------------------------[] 
	for (i=0; i<Format.Size(); i++)
	{
		header += "   void OBServer_";
		header += Prefix;		
		header += "_";
		header += Format[i].ObjName;
		header += "_";
		header += Format[i].Action;
		header += " (const char * inStr, const char * outStr, void ** ppData);";
		NEW_LINE;
	}
	//----------------------------------------------------------------------------[] 

	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	header += "#endif";
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void)Format;
	(void)Prefix;
#endif
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Create_Interface_Auto_cpp																	[]
//                                                                            []
void CObjDriver::Create_Interface_Auto_cpp (string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix)
{
	DEBUG_STACK_NAME (Create_Interface_Auto_cpp);

#ifdef ZOOB_UTILS
	int	 i=0,j=0;
	char   SSS[10240];
	header = "";

	header += "/*";	NEW_LINE;
	header += "________________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Interface_Auto.cpp                                        []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Roman V. Koshelev, Alex Vershinin                         []";	NEW_LINE;
	header += "[] Description:     ������������ ������� ��� ������ � ����� ������.           []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Interface.h-file   []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;


	//----------------------------------------------------------------------------[] 
	header += "#include \"";
	header += "problem_interface.h\"";
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	//----------------------------------------------------------------------------[] 




	//----------------------------------------------------------------------------[] 
	for (i=0; i<Format.Size(); i++)
	{
		PRINT_PERCENT (i, Format.Size());
		NEW_LINE;
		NEW_LINE;
		NEW_LINE;
		header += "//______________________________________________________________________________"; NEW_LINE;
		header += "//                                                                            []"; NEW_LINE;
		header += "// "; 
		if (Format[i].Description!=""){
			header += Format[i].Description;
		}
		else{
			header += Prefix;
			header += "_";
			header += Format[i].ObjName;
			header += "_";
			header += Format[i].Action;
			header += " ()";
		}
		NEW_LINE;
		header += "//                                                                            []"; NEW_LINE;

		
		sprintf (SSS, "void OBServer_%s_%s_%s (const char * inStr, const char * outStr, void ** ppData)", Prefix.c_str(), Format[i].ObjName.c_str(), Format[i].Action.c_str());
		header += SSS;
		NEW_LINE;

		header += "{"; NEW_LINE;
		sprintf (SSS, "   DEBUG_STACK_NAME (OBServer_%s_%s_%s);", Prefix.c_str(), Format[i].ObjName.c_str(), Format[i].Action.c_str());
		header += SSS;
		NEW_LINE;
		header += "   OBServer_WRAPPER_START;";		NEW_LINE;
		header += "   AVOID_WARNING_ON_ARGS;"; NEW_LINE;

		NEW_LINE;
		header += "// ����������, ����������� ��� ������ ���������� �������:"; NEW_LINE;
		sprintf (SSS, "   %s_%s_Args        OBServer_args;", Prefix.c_str(), Format[i].ObjName.c_str()); header += SSS; NEW_LINE;
		header += "   int                  OBServer_result;"; NEW_LINE;
	
		NEW_LINE;
		if (Format[i].InArg.Size())
		{
			header += "// �������� ������ ��������� �� ������ inStr � ��������� OBServer_args:"; NEW_LINE;
		}
		else 
		{
			header += "// ������� ���������� ���."; NEW_LINE;
		}
   
		for (j=0; j<Format[i].InArg.Size(); j++)
		{
			header += "   GET_ARG (";
			header += Format[i].InArg[j].Name;
			header += ");";
			NEW_LINE;
		}

		NEW_LINE;
		header += "// ������� ���������� �������:"; NEW_LINE;
		sprintf (SSS, "   OBServer_result = %s_%s_%s (OBServer_args);", Prefix.c_str(), Format[i].ObjName.c_str(), Format[i].Action.c_str()); header+=SSS; NEW_LINE;

		NEW_LINE;
		header += "// ���� ������� ���������� �������, �� ������� ��������� �������� ���������:"; NEW_LINE;
		header += "   if (OBServer_result == OBServer_OK)"; NEW_LINE;
		header += "   {"; NEW_LINE;

		if (Format[i].OutArg.Size()==0)
		{
			header += "   // �������� ���������� ���."; NEW_LINE;
		}

		for (j=0; j<Format[i].OutArg.Size(); j++)
		{
			header += "      PACK_ARG (";
			header += Format[i].OutArg[j].Name;
			header += ");";
			NEW_LINE;
		}

		header += "   }"; NEW_LINE;

		header += "   OBServer_WRAPPER_END;"; NEW_LINE;
		header += "}"; NEW_LINE;
		header += "//____________________________________________________________________________[]"; NEW_LINE;
	}
	printf ("\r                                                                                    \r");
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] END OF FILE                                                                []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[]____________________________________________________________________________[]";	NEW_LINE;
	header += "*/";
	NEW_LINE;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void)Format;
	(void)Prefix;
#endif
}
//____________________________________________________________________________[]









/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` Create_Interface_Dispatch_cpp	                                          []                                
[]                                                                            []
[]____________________________________________________________________________*/
void CObjDriver::Create_Interface_Dispatch_cpp	(string& header, const CPtr <INTERFACE_FORMAT>& Format, const string& Prefix)
{
	DEBUG_STACK_NAME (Create_Interface_Dispatch_cpp);

#ifdef ZOOB_UTILS
	int	 i=0,j=0;
	char   SSS[10240];
	header = "";

	header += "/*______________________________________________________________________________";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] This is a part of the PROJECT: 'ObjBase'                                   []";	NEW_LINE;
	header += "[] Copyright (C) 1999-2000 by the author(s).                                  []";	NEW_LINE;
	header += "[] All rights reserved.                                                       []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Name:            Interface_Dispatch.cpp                                    []";	NEW_LINE;
	header += "[] Date:            NA                                                        []";	NEW_LINE;
	header += "[] Author:          Alex Vershinin, Roman V. Koshelev                         []";	NEW_LINE;
	header += "[] Description:     ��������� ��� ������ �������� ���������� �������.         []";	NEW_LINE;
	header += "[] __________________________________________________________________________ []";	NEW_LINE;
	header += "[]                                                                            []";	NEW_LINE;
	header += "[] Attention:       This file is auto created by compiling Interface.h-file   []";	NEW_LINE;
	header += "[]____________________________________________________________________________*/";	NEW_LINE;
	NEW_LINE;

	//----------------------------------------------------------------------------[] 
	header += "#define	USES_OBServer_Interface_h";								NEW_LINE;
	header += "#define	USES_Problem_Interface_h";									NEW_LINE;
	header += "#include	\"include.h\"";												NEW_LINE;

	NEW_LINE;
	NEW_LINE;
	//----------------------------------------------------------------------------[] 


	//----------------------------------------------------------------------------[] 

	header += "//______________________________________________________________________________";NEW_LINE;
	header += "//                                                                            []";NEW_LINE;
	header += "// ��������� ������� ���������� ������                                        []";NEW_LINE;
	header += "//                                                                            []";NEW_LINE;
	header += "void OBServer_Interface (const char* OBServer_Function, const char* InputArgs, const char* OutputArgs, void ** ppData)";NEW_LINE;
	header += "{";NEW_LINE;
	header += "   DEBUG_STACK_NAME (OBServer_Interface);";NEW_LINE;
	header += "// ����� ������������������ �������";NEW_LINE;
	header += "   FNC_BEGIN;";NEW_LINE;
	header += "   {";NEW_LINE;

	string cur_objName="";
	for (i=0; i<Format.Size(); i++)
	{
		if (cur_objName!=Format[i].ObjName){
			if (i!=0) NEW_LINE;
			header += "   // ";
			header += Format[i].ObjName;
			cur_objName=Format[i].ObjName;
			NEW_LINE;
		}
      header += "      FNC        (";
		header += Prefix;
      header += "_";
		header += Format[i].ObjName;
      header += "_";
		header += Format[i].Action;
      header += ", \"";
		header += Format[i].Description;
      header += "\");";
		NEW_LINE;
		for (j=0; j<Format[i].InArg.Size(); j++)
		{
			sprintf (SSS, "			FNC_IN  (%s_%s, %s, \"%s\");", Prefix.c_str(), Format[i].ObjName.c_str(), Format[i].InArg[j].Name.c_str(), Format[i].InArg[j].Description.c_str());
			header += SSS;
			NEW_LINE;
		}
		for (j=0; j<Format[i].OutArg.Size(); j++)
		{
			sprintf (SSS, "			FNC_OUT (%s_%s, %s, \"%s\");", Prefix.c_str(), Format[i].ObjName.c_str(), Format[i].OutArg[j].Name.c_str(), Format[i].OutArg[j].Description.c_str());
			header += SSS;
			NEW_LINE;
		}
	}

	header += "   }";NEW_LINE;
	header += "// ����� ������������ ������� ��� ��������� �� ������.";NEW_LINE;
	header += "   FNC_END;";NEW_LINE;
	header += "}";NEW_LINE;
	header += "//____________________________________________________________________________[]";NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	NEW_LINE;
	//----------------------------------------------------------------------------[] 



	return;
#else
	header = "\nERROR -- ZOOB_UTILS not defined\n";
	(void)Format;
	(void)Prefix;
#endif
}
//____________________________________________________________________________[]



/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/

