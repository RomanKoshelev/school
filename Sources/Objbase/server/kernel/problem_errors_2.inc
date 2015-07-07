	ERR_SYSTEM_ERROR = -1									// Сработал ASSERT
};




const char * GET_ERROR_DESCRIPTION (int nErr);
//______________________________________________________________________________
//                                                                            []
//` Возврат в аргументах кода ошибки и её описания										[]          
//                                                                            []
#define	ERR_RETURN(_retcode_)																\
{																										\
	arg.ExitCode = (int)_retcode_;															\
	ERR_RESULT err_ok=ERR_OK;																	\
	if (_retcode_!=err_ok) 																		\
	{																									\
		string sErr = GET_ERROR_DESCRIPTION ((int)_retcode_);							\
		if (!sErr.IsEmpty())																		\
		{																								\
			string FILE_LINE;																		\
			FILE_LINE.Format ("%s:%d", __FILE__, __LINE__);								\
			arg.ExitCodeComment += "[";														\
			arg.ExitCodeComment += FILE_LINE;												\
			arg.ExitCodeComment += ": {ERR_CODE=";											\
			arg.ExitCodeComment += sErr;														\
			arg.ExitCodeComment += "}]";														\
		}																								\
	}																									\
	return ERR_OK;																					\
}
//----------------------------------------------------------------------------[] 
#define	ERR_RETURN_COMMENT(_retcode_,_comment_)										\
{																										\
	arg.ExitCodeComment = _comment_; 														\
	arg.ExitCodeComment+= " "; 																\
	ERR_RETURN (_retcode_);																		\
}
//----------------------------------------------------------------------------[] 
#define	ERR_RETURN_COMMENT_1(_retcode_,_comment_,a1)									\
{																										\
	string sErr;																					\
	sErr.Format (_comment_, a1);																\
	ERR_RETURN_COMMENT (_retcode_,(sErr.c_str()));										\
}
//----------------------------------------------------------------------------[] 
#define	ERR_RETURN_COMMENT_2(_retcode_,_comment_,a1,a2)								\
{																										\
	string sErr;																					\
	sErr.Format (_comment_, a1,a2);															\
	ERR_RETURN_COMMENT (_retcode_,(sErr.c_str()));										\
}
//----------------------------------------------------------------------------[] 
#define	ERR_RETURN_COMMENT_3(_retcode_,_comment_,a1,a2,a3)							\
{																										\
	string sErr;																					\
	sErr.Format (_comment_, a1,a2,a3);														\
	ERR_RETURN_COMMENT (_retcode_,(sErr.c_str()));										\
}
//----------------------------------------------------------------------------[] 
#define	ERR_RETURN_COMMENT_4(_retcode_,_comment_,a1,a2,a3,a4)						\
{																										\
	string sErr;																					\
	sErr.Format (_comment_, a1,a2,a3,a4);													\
	ERR_RETURN_COMMENT (_retcode_,(sErr.c_str()));										\
}
//____________________________________________________________________________[]


#define CASE_PRINT_EXIT_CODE(ec)			case ec: printf ("ERROR: ExitCode = "#ec);					break
#define CASE_PRINT_EXIT_CODE_DEFAULT	default: printf ("ERROR: ExitCode = %d", arg.ExitCode);	break
