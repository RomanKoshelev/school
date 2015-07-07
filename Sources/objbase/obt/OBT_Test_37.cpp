//______________________________________________________________________________
//                                                                            []
//` Проверка string::ParseURL																	[]
//                                                                            []
void Test37 ()
{
	int N = 100000;
	for (i=0; i< N; i++)
	{
		PRINT_PERCENT (i, N);
		string str1 = "http://vasya@www.chat.ru:8001/~vasya/pupkin/index.cgi/?num=10";
		string str2 = "http://vasya@www.chat.ru:8001/~vasya/pupkin/welcome/index.cgi?num=10";
		HTTP_URL http_url_parent = str1.c_str();
		HTTP_URL http_url_child  = str2.c_str();
		http_url_child.IsChildFor(http_url_parent);
	}

	//printf ("%s\n%s\n%s\n\n", str1.c_str(), str2.c_str(), http_url_child.IsChildFor(http_url_parent)?"YES":"NO");

//	string str;
//	http_url_parent.DomainPath (str);
//	str.Print();

//	http_url.Parse();

//	http_url.Parse("http://www.chat.ru/~vasya/pupkin/index.cgi?num=10");
//	http_url.Parse("av@bsd/index.php3?args");
//	http_url.Parse("http://www.chat.ru:8001/~vasya/pupkin/index.cgi?num=10");


//	http_url.DebugPrint ();
}
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Проверка USER_AGENT																			[]
//                                                                            []
void Test38_1 () // Часть первая
{
	string FileIn;
	FileIn.ReadFile ("N:/TSMC/public_html/-/agents/jjj");

	string FileOut;

	int			i,j;
	char *		STR1		=	"http://";
	char *		STR2		=	"\" \"";
	int			nSTR1		=	strlen (STR1);
	int			nSTR2		=	strlen (STR2);
	bool			bThisStr	=	false;
	char			USER_AGENT[1024];
	string_arr	FileOut_arr;
	int			NN			= (int)FileIn.Len();

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i/1000, NN/1000);
		if (memcmp (FileIn.GetPtr()+i, STR1, nSTR1)==0)
		{
			bThisStr = true;
		}

		if (FileIn[i]=='\n')
		{
			bThisStr = false;
		}

		if (bThisStr && (memcmp (FileIn.GetPtr()+i, STR2, nSTR2)==0))
		{
			bThisStr = false;
			for (j=0,i=i+nSTR2; FileIn[i]!='"'; i++,j++)
			{
				USER_AGENT[j  ] = FileIn[i];
				USER_AGENT[j+1] = 0;				
			}
			if (j>5)
			{
				string strUSER_AGENT = USER_AGENT;
				if (FileOut_arr.Find(strUSER_AGENT)==-1)
				{
					FileOut_arr += string(USER_AGENT);
				}
			}
		}		
	}

	FileOut_arr.Sort ();
	for (i=0; i<FileOut_arr.GetSize();i++)
	{
		FileOut += FileOut_arr[i];
		FileOut += "\n";
	}
	FileOut.WriteFile ("N:/TSMC/public_html/-/agents/USER_AGENT.txt");
	FileOut.Print();
}
//____________________________________________________________________________[]







//______________________________________________________________________________
//                                                                            []
//` Проверка USER_AGENT																			[]
//                                                                            []
void Test38 () // Часть вторая
{
	string FileIn;
	string FileOut;
	FileIn.ReadFile ("N:/TSMC/public_html/-/agents/USER_AGENT.txt");

	int				i;
	string_arr		FileIn_arr;
	FileIn.explode (FileIn_arr, "\r\n");
	string_arr		FileOut_arr;
	string			tmp_str;

	int NN = FileIn_arr.Size();
	for (i=0; i<NN; i++) if (FileIn_arr[i].Len()>3)
	{
		PRINT_PERCENT (i, NN);

		USER_AGENT user_agent (FileIn_arr[i].c_str());
		user_agent.UserAgent (tmp_str);

		if (FileOut_arr.Find (tmp_str)==-1)
		{
			FileOut_arr.Add(tmp_str);
		}
		FileOut += "";
		FileOut += FileIn_arr[i];
		FileOut += "\n";
		FileOut += tmp_str;
		FileOut += "\n\n";
	}


	FileOut_arr.Sort ();
	tmp_str.implode (FileOut_arr);
	
	FileOut += "\n-------------------------------------------------------------------\n\n\n\n\n\n\n\n\n\n";
	FileOut += "\n\n\n\n-------------------------------------------------------------------\n";
	FileOut += 	tmp_str;

	FileOut.WriteFile ("N:/TSMC/public_html/-/agents/USER_AGENT_PARSED.txt");
}
//____________________________________________________________________________[]




/*
//______________________________________________________________________________
//                                                                            []
//` string::GetCRC()																				[]
//                                                                            []
void Test40 ()
{
	int i=0;
	int NN=1000000;
	identifier_arr CRC_ARR;
	char SSS[256];
	OC_Test_CRC oc_test_crc;
	oc_test_crc.DeleteClassObjects();

	for (i=0; i<NN; i++)
	{
		PRINT_PERCENT (i,NN);
		MakeRandomStr ("qwertyuiopasdfghjklzxcvbnm", 8, SSS);
		oc_test_crc.New();
		oc_test_crc.m_CRC = string (SSS).GetCRC();
		oc_test_crc.m_STR = SSS;
	}

	puts ("\n\n");
	identifier	prev_crc = 0;
	string		prev_str = "";
	for (i=0, oc_test_crc.GoFirst(); oc_test_crc.IsValid(); oc_test_crc++, i++)
	{
		PRINT_PERCENT (i, oc_test_crc.GetTotalNum());
		if (oc_test_crc.m_CRC==prev_crc)
		{
			printf ("\n[%8x]  %s %s %s\n", prev_crc, prev_str.c_str(), ((string)(oc_test_crc.m_STR)).c_str(), (oc_test_crc.m_STR==prev_str)?"OK": "WARNING");
		}
		prev_crc = oc_test_crc.m_CRC;
		prev_str = oc_test_crc.m_STR;
	}

#if 0  //{ RomanVK
	puts ("\n\n");
	oc_test_crc.SetIndex_CRC();
	for (oc_test_crc.GoFirst(); oc_test_crc.IsValid(); oc_test_crc++)
	{
		printf ("[%8x]    %s\n", (identifier)oc_test_crc.m_CRC, ((string)(oc_test_crc.m_STR)).c_str());
	}

	puts ("\n\n");
	oc_test_crc.SetIndex_STR();
	for (oc_test_crc.GoFirst(); oc_test_crc.IsValid(); oc_test_crc++)
	{
		printf ("%s    [%8x]\n", ((string)(oc_test_crc.m_STR)).c_str(), (identifier)oc_test_crc.m_CRC);
	}
#endif //}
}
//____________________________________________________________________________[]

*/






//______________________________________________________________________________
//                                                                            []
// Компилятор концептов																			[]
//                                                                            []
struct ConceptItem
{
	identifier		m_objID;
	int				m_nParent;
	string_arr		m_Name;
	string_arr		m_Descr;
	string			m_SysComment;
	int				m_SysCommentNo;
	string			m_ShortName;
	int				m_Level;

	ConceptItem ()
	{
		m_Level			= 0;
		m_objID			= NA;
		m_nParent		= -1;
		m_SysCommentNo	= -1;
	}

	ConceptItem (const ConceptItem& from)
	{
		CopyFrom (from);
	}

	ConceptItem& operator = (const ConceptItem& from)
	{
		return CopyFrom (from);
	}

	ConceptItem& CopyFrom (const ConceptItem& from)
	{
		m_objID			=	 from.m_objID;     
		m_Level			=	 from.m_Level; 
		m_nParent		=	 from.m_nParent;   
		m_Name			=	 from.m_Name;      
		m_Descr			=	 from.m_Descr;     
		m_SysComment	=	 from.m_SysComment;
		m_SysCommentNo	=	 from.m_SysCommentNo;
		m_ShortName		=	 from.m_ShortName;   
		return *this;
	}

	void DebugPrint ()
	{
		string _m_Name;		_m_Name.implode (m_Name, ", ");
		string _m_Descr;		_m_Descr.implode (m_Descr, ", ");
      printf ("------------------------------------------------------\n");
      printf ("m_objID        = [%lu]\n",	m_objID);
      printf ("m_Level        = [%d]\n",	m_Level); 
      printf ("m_nParent      = [%d]\n",  m_nParent);   
      printf ("m_Name         = [%s]\n",	_m_Name.c_str());
      printf ("m_Descr        = [%s]\n",	_m_Descr.c_str());     
      printf ("m_SysComment   = [%s]\n",	m_SysComment.c_str());
      printf ("m_SysCommentNo = [%d]\n",	m_SysCommentNo);
      printf ("m_ShortName    = [%s]\n",	m_ShortName.c_str());
      printf ("------------------------------------------------------\n");
	}
};

void Test41 ()
{
	CPtr<ConceptItem> arr_ConceptItem;
	string_arr			arr_sys_comments;
	
	string srcfile;
	srcfile.ReadFile ("./../concepts.h");
	string_arr arr_srcfile;
	string_arr arr_srcfile_tmp;

	srcfile.explode (arr_srcfile_tmp, "\r\n");

	for (i=0; i<arr_srcfile_tmp.Size();i++)
	{
		arr_srcfile_tmp[i].rtrim();
		if (strlen (arr_srcfile_tmp[i].c_str()))
			arr_srcfile += arr_srcfile_tmp[i];
	}

	string cur_sys_comment="";

	for (i=0; i<arr_srcfile.Size();i++)
	{
	// Находим имена
		string CurString = arr_srcfile[i];
		string Names = "";
		CurString.SubStr (Names, 0, CurString.Find("{"));
		string_arr arr_Names;
		string_arr arr_Descr;
		int Level = 0;
		for (Level = 0; Names[Level] == '\t'; Level++)
		{
			(void)NULL;
		}
		Names.explode (arr_Names, "|");

		for (j=0; j<arr_Names.Size(); j++)
		{
			arr_Names[j].trim();
		// Находим описания
			string CurDescr="No description";
			char SSS[10240];
			strcpy (SSS, arr_Names[j].c_str());
			char * pSys1 = strtok (SSS, "[");
			char * pSys2 = strtok (NULL, "]");
			if (pSys1 && pSys2)
			{
				CurDescr = pSys2;
			}
			arr_Descr += CurDescr;
			arr_Names[j] = SSS;
			arr_Names[j].trim();
		}

	// Находим системный комментарий
		char SSS[10240];
		int cur_sys_comment_no=-1;
		strcpy (SSS, CurString.c_str());
		char * pSys1 = strtok (SSS, "{");
		char * pSys2 = strtok (NULL, "}");
		if (pSys1 && pSys2)
		{
			cur_sys_comment = pSys2;
			cur_sys_comment.trim();
		}
		cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		if (cur_sys_comment_no==-1)
		{
			arr_sys_comments+=cur_sys_comment;
			cur_sys_comment_no = arr_sys_comments.Find(cur_sys_comment);
		}

		int Parent=0;
		for (Parent=arr_ConceptItem.Size()-1; Parent>=0; Parent--)
		{
			if (arr_ConceptItem[Parent].m_Level<Level)
			{
				break;
			}
		}
		ConceptItem concept_item;
		concept_item.m_objID			= NA;
		concept_item.m_Level			= Level;
		concept_item.m_nParent		= Parent;
		concept_item.m_Name			= arr_Names;
		concept_item.m_Descr			= arr_Descr;
		concept_item.m_SysComment	= cur_sys_comment;
		concept_item.m_SysCommentNo= cur_sys_comment_no;
		concept_item.m_ShortName	= "";


		arr_ConceptItem += concept_item;
	}

	for (i=0; i<arr_sys_comments.Size(); i++)
	{
		printf ("%2d [%s]\n", i, arr_sys_comments[i].c_str());
	}
	printf ("\n\n");

	int MaxLangNo =0;
	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		MaxLangNo = max (MaxLangNo, arr_ConceptItem[i].m_Name.Size());
	}

	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		while (arr_ConceptItem[i].m_Name.Size()<MaxLangNo)
		{
			const char *pName = "No name";
			if (arr_ConceptItem.Size() && strlen (arr_ConceptItem[i].m_Name[0].c_str()))
			{
				pName = arr_ConceptItem[i].m_Name[0].c_str();
			}

			arr_ConceptItem[i].m_Name += pName;
		}

		while (arr_ConceptItem[i].m_Descr.Size()<MaxLangNo)
		{
			const char *pDescr = "No description";
			if (arr_ConceptItem.Size() && strlen (arr_ConceptItem[i].m_Descr[0].c_str()))
			{
				pDescr = arr_ConceptItem[i].m_Descr[0].c_str();
			}

			arr_ConceptItem[i].m_Descr += pDescr;
		}
	}

	for (i=0; i<arr_ConceptItem.Size(); i++)
	{
		printf ("\n[%d]\n", i);
		arr_ConceptItem[i].DebugPrint();
	}
}
//____________________________________________________________________________[]

