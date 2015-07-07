/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            FileDriver.cpp															[]
[] Date:            02/03/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     File driver																[]
[]____________________________________________________________________________[]
*/
#define	USES_STATIC_FILE_ID_h
#define	USES_FileDriver_h
#define	USES_File_h
#include "main.h"

CFileDriver * CFileDriver::m_this=NULL;
bool			  CFileDriver::m_bInit=false;





//______________________________________________________________________________
//                                                                            []
//` fseek_64                                                                  []        
//                                                                            []
off_t fseek_64 (int hFile, off_t nSeek, int whence)
{
	#ifdef WIN32
		return _lseeki64 (hFile, nSeek, whence);
	#else
		return lseek (hFile, nSeek, whence);
	#endif
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` ftell_64                                                                  []        
//                                                                            []
off_t ftell_64 (int hFile)
{
	return fseek_64 (hFile, 0, SEEK_CUR);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` fread_64                                                                  []        
//                                                                            []
size_t fread_64 (void * buffer, size_t size, size_t count, int hFile)
{
	return read (hFile, buffer, size*count);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` fwrite_64                                                                 []         
//                                                                            []
size_t fwrite_64 (const void *buffer, size_t size, size_t count, int hFile)
{
	return write (hFile, buffer, size*count);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` fopen_64                                                                  []        
//                                                                            []
int fopen_64 (const char * pFileName, int flag)
{
//	int hFile = open (pFileName, flag, 0666);

//	return hFile<0 ? NULL: hFile;
	return open (pFileName, flag, 0666);
}
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` fclose_64                                                                 []         
//                                                                            []
int fclose_64 (int hFile)
{
	return close (hFile);
}
//____________________________________________________________________________[]








/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
