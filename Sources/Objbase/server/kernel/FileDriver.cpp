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

CFileDriver * CFileDriver::m_this	=	NULL;
bool			  CFileDriver::m_bInit	=	false;
bool			  CFileDriver::m_bError	=	false;




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






















//______________________________________________________________________________
//                                                                            []
//` CLevelFile																						[]
//                                                                            []
size_t CLevelFile::GetClusterSize() 
{ 
	DEBUG_STACK_NAME (GetClusterSize);

	return m_nClusterSize; 
}
//----------------------------------------------------------------------------[] 
unsigned long CLevelFile::MakeSizeForLevel (unsigned int nLevel)
{
	DEBUG_STACK_NAME (MakeSizeForLevel);

	unsigned long nSize = 1 << (nLevel+1)/2;
	if ((nLevel+1)%2)
	{
		nSize = (nSize+2*nSize)/2;
	}	
	return nSize;
}
//----------------------------------------------------------------------------[] 
size_t CLevelFile::GetMemSize ()
{
	DEBUG_STACK_NAME (GetMemSize);

	return m_nByteAllocSize;
}
//----------------------------------------------------------------------------[] 
const char * CLevelFile::GetSizeName (unsigned long nSize)
{
	DEBUG_STACK_NAME (GetSizeName);

	static char SSS [1024];
	static char sss [1024];
	SSS[0]=0;

	bool bSign=false;
	if (nSize>=1000*1000*1000)
	{
		sprintf (sss, "%d,", nSize/1000/1000/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000*1000*1000);
		bSign = true;
	}
	else 
		strcat (SSS, "  ");

	if (bSign || nSize>=1000*1000)
	{
		sprintf (sss, bSign? "%03d,": "%3d,", nSize/1000/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000*1000);
		bSign = true;
	}
	else 
		strcat (SSS, "    ");

	if (bSign || nSize>=1000)
	{
		sprintf (sss, bSign? "%03d,": "%3d,", nSize/1000);
		strcat (SSS, sss);
		nSize = nSize%(1000);
		bSign = true;
	}
	else 
		strcat (SSS, "    ");

	sprintf (sss, bSign? "%03d": "%3d", nSize);
	strcat (SSS, sss);
	return SSS;
}
//----------------------------------------------------------------------------[] 
const char * CLevelFile::MakeLevelName (unsigned int nLevel)
{
	DEBUG_STACK_NAME (MakeLevelName);

	unsigned long nSize = MakeSizeForLevel(nLevel);
	static char SSS[1024];
	sprintf (SSS, "[%02d]_%s", nLevel, GetSizeName (nSize));
	for (int j=0; SSS[j]; j++)	if (SSS[j]==' ')	
		SSS[j] = '_';
	return SSS;
}
//----------------------------------------------------------------------------[] 
CLevelFile::CLevelFile	(const char * sFileName, int nLevel)
{
	DEBUG_STACK_NAME (CLevelFile);

	umask(0);
	m_nLevel=nLevel;
	m_nClusterSize=MakeSizeForLevel (m_nLevel);
	
	m_nFirstEmpty	= 0;
	m_bFatChanged	= false;
	m_bDatChanged	= false;
	char	sFileFatName [1024];
	char	sFileDatName [1024];
	sprintf(sFileFatName, "%s_%s.fat", sFileName, MakeLevelName (m_nLevel));
	sprintf(sFileDatName, "%s_%s.dta", sFileName, MakeLevelName (m_nLevel));

	m_pFatMap=NULL;
// Считывание FAT
	if((m_hFileFat = fopen_64 (sFileFatName, (O_RDWR | O_BINARY) /*"r+b"*/)) >= 0) 
	{
		fseek_64 (m_hFileFat,0,SEEK_END);
		m_nByteFatSize= (size_t)ftell_64(m_hFileFat) - sizeof (m_nFirstEmpty);
		fseek_64 (m_hFileFat,0,SEEK_SET);
		m_nByteAllocSize=max(m_nByteFatSize,1);
		m_pFatMap=new byte[m_nByteAllocSize];
		memset(m_pFatMap,CLUSTER_FREE,m_nByteAllocSize);
		fread_64 (&m_nFirstEmpty,1, sizeof (m_nFirstEmpty),m_hFileFat);
		fread_64 (m_pFatMap,m_nByteFatSize,1,m_hFileFat);
	} 
// Создание FAT
	else 
	{
		m_hFileFat = fopen_64 (sFileFatName, (O_RDWR | O_CREAT | O_TRUNC | O_BINARY) /*"w+b"*/);
		SERVER_DEBUG_ASSERT (m_hFileFat >= 0, "CLevelFile: Can't create FAT-file");
		m_nByteFatSize		= 0;
		m_nByteAllocSize	= 1;
		m_pFatMap=new byte[m_nByteAllocSize];
		memset(m_pFatMap,0,m_nByteAllocSize);
		m_bFatChanged=true;
	}
	m_nClusterNumber=m_nByteFatSize*CLUSTERS_PER_BYTE;
// Открытие данных
	if((m_hFileDat = fopen_64 (sFileDatName, (O_RDWR | O_BINARY) /*"r+b"*/)) >= 0) 
	{
		// Do nothing
	} 
// Создание данных
	else 
	{
		m_hFileDat = fopen_64 (sFileDatName, (O_RDWR | O_CREAT | O_TRUNC | O_BINARY) /*"w+b"*/);
		SERVER_DEBUG_ASSERT (m_hFileDat >= 0, "CLevelFile: Can't create DAT-file");
	}
}
//----------------------------------------------------------------------------[] 
CLevelFile::~CLevelFile	() 
{
	DEBUG_STACK_NAME (_CLevelFile);

	close();
	if(m_pFatMap)
		delete m_pFatMap;
}
//----------------------------------------------------------------------------[] 
void CLevelFile::flush()
{
	DEBUG_STACK_NAME (flush);

	m_nFirstEmpty = 0;
	if(m_bFatChanged) 
	{
		m_bFatChanged=false;
		SERVER_DEBUG_ASSERT (m_hFileFat >= 0, "CLevelFile: Fat not open in flush()");
		fseek_64  (m_hFileFat, 0, SEEK_SET);
		fwrite_64 (&m_nFirstEmpty, 1, sizeof (m_nFirstEmpty), m_hFileFat);
		fwrite_64 (m_pFatMap, m_nByteFatSize, 1, m_hFileFat);
	} 
	else
	{
		SERVER_DEBUG_ASSERT (m_hFileFat >= 0, "CLevelFile: Fat not open in flush()");
	}
	SERVER_DEBUG_ASSERT (m_hFileDat >= 0, "CLevelFile: Dat not open in flush()");
}
//----------------------------------------------------------------------------[] 
void CLevelFile::close()
{
	DEBUG_STACK_NAME (close);

	flush();
	SERVER_DEBUG_ASSERT (m_hFileFat >= 0, "CLevelFile: Fat not open in close()");
	fclose_64 (m_hFileFat);
	SERVER_DEBUG_ASSERT (m_hFileDat >= 0, "CLevelFile: Dat not open in close()");
	fclose_64 (m_hFileDat);
}
//----------------------------------------------------------------------------[] 
BIT CLevelFile::GetClusterState(identifier nCluster)
{
	DEBUG_STACK_NAME (GetClusterState);

	SERVER_DEBUG_ASSERT_RETURN ((nCluster<m_nClusterNumber), "CLevelFile: Cluster address exceeds total number",0);
	#ifdef OPTIMIZED_FAT
	{
		byte bByte=m_pFatMap[nCluster/8];

		byte BP = (byte)(nCluster % 8);

		BIT bRetVal = (bByte & (1<<BP))? 1: 0;
		return bRetVal;
	}
	#else
	{
		return m_pFatMap[nCluster];
	}
	#endif
}
//----------------------------------------------------------------------------[] 
BIT CLevelFile::SetClusterState(identifier nCluster, BIT bSet)
{
	DEBUG_STACK_NAME (SetClusterState);

	SERVER_DEBUG_ASSERT_RETURN ((nCluster<m_nClusterNumber), "CLevelFile: Cluster address exceeds total number", 0);

	#ifdef OPTIMIZED_FAT
	{
		byte * pByte =	m_pFatMap + (nCluster/8);
		byte BV = byte(bSet? 1:0);
		byte BP = (byte)(nCluster % 8);

		m_bFatChanged = true;		

	// Прочистить бит в позиции BP
		*pByte = byte((*pByte) & ~(1<<BP));

	// Прописать бит BV в позиции BP
		*pByte = byte ((*pByte) | (BV<<BP));

		return bSet;
		}
	#else
	{
		return m_pFatMap[nCluster]=bSet;
	}
	#endif
}
//----------------------------------------------------------------------------[] 
size_t CLevelFile::ReadFile(identifier nCluster, byte *pData, size_t nSize)
{
	DEBUG_STACK_NAME (ReadFile);

	return ReadBlock(nCluster,pData,0,nSize);
}
//----------------------------------------------------------------------------[] 
size_t CLevelFile::ReadBlock(identifier nCluster, byte *pData, size_t nOffset, size_t nSize)
{
	DEBUG_STACK_NAME (ReadBlock);

	SERVER_DEBUG_ASSERT_RETURN ((nCluster<m_nClusterNumber), "CLevelFile: Cluster address exceeds total number",0);
	SERVER_DEBUG_ASSERT_RETURN (m_hFileDat >= 0, "CLevelFile: Dat not open in ReadFile()",0);
	SERVER_DEBUG_ASSERT_RETURN (nOffset>=0, "CLevelFile: Negative offset passed",0);
	SERVER_DEBUG_ASSERT_RETURN (nSize>=0, "CLevelFile: Negative size passed",0);

	if(pData==NULL)
		return m_nClusterSize;
	SERVER_DEBUG_ASSERT_RETURN ((nOffset+nSize)<=m_nClusterSize, "CLevelFile: Too large data amount requested",0);
	off_t			nSeek=((off_t)nCluster*(off_t)m_nClusterSize)+(off_t)nOffset;
	fseek_64		(m_hFileDat,nSeek,SEEK_SET);
	size_t		nRead = fread_64 (pData,1,nSize,m_hFileDat);
	return nRead;
}
//----------------------------------------------------------------------------[] 
void CLevelFile::WriteCluster(identifier nCluster, void *pData, size_t nSize)
{
	DEBUG_STACK_NAME (WriteCluster);

	m_bDatChanged=true;
	SERVER_DEBUG_ASSERT (nSize<=m_nClusterSize, "CLevelFile: Cluster overflow");
	off_t			nSeek=((off_t)nCluster*(off_t)m_nClusterSize);
	fseek_64		(m_hFileDat,nSeek,SEEK_SET);
	size_t		nWriten = fwrite_64 (pData,1,nSize,m_hFileDat);
	SERVER_DEBUG_ASSERT (nWriten==nSize, "CLevelFile: Cannot write data");
	SetClusterState(nCluster,CLUSTER_EXIST);
}
//----------------------------------------------------------------------------[] 
void CLevelFile::WriteClusterOffset(identifier nCluster, void *pData, size_t nOffset, size_t nSize)
{
	DEBUG_STACK_NAME (WriteClusterOffset);

	SERVER_DEBUG_ASSERT (nOffset>=0, "CLevelFile: Negative offset passed");
	SERVER_DEBUG_ASSERT (nSize>=0, "CLevelFile: Negative size passed");

	m_bDatChanged=true;
	SERVER_DEBUG_ASSERT ((nSize+nOffset)<=m_nClusterSize, "CLevelFile: Cluster overflow");
	off_t			nSeek=((off_t)nCluster*(off_t)m_nClusterSize)+(off_t)nOffset;
	fseek_64		(m_hFileDat,nSeek,SEEK_SET);
	size_t		nWriten = fwrite_64 (pData,1,nSize,m_hFileDat);
	SERVER_DEBUG_ASSERT (nWriten==nSize, "CLevelFile: Cannot write data");
	SetClusterState(nCluster,CLUSTER_EXIST);
}
//----------------------------------------------------------------------------[] 
identifier CLevelFile::ObtainFreeCluster()
{
	DEBUG_STACK_NAME (ObtainFreeCluster);

	identifier nNewCluster=UNKNOWN;
// Поиск свободного кластера
	for(identifier i=m_nFirstEmpty;i<m_nClusterNumber;i++) {
		if(GetClusterState(i)==CLUSTER_FREE) {
			nNewCluster=i;
			m_nFirstEmpty=nNewCluster+1;
			break;
		}
	}
// Свободный кластер найден
	if(nNewCluster!=UNKNOWN) {
		return nNewCluster;
	} 
// Свободный кластер не найден
	else {
	// Есть место в памяти
		if(m_nByteFatSize<m_nByteAllocSize) {
			m_nByteFatSize	  += 1;
			nNewCluster			= m_nClusterNumber;
			m_nFirstEmpty		= nNewCluster+1;
			m_nClusterNumber	= m_nByteFatSize*CLUSTERS_PER_BYTE;
			return nNewCluster;
		} 
	// Нет места в памяти
		else {
			size_t oldAllocSize = m_nByteAllocSize;
			m_nByteAllocSize += max (1024, m_nByteAllocSize/10);
			byte *pNewFatMap = new byte[m_nByteAllocSize];
			SERVER_DEBUG_ASSERT_RETURN (pNewFatMap, "CLevelFile: Cannot allocate memory", NA);
		// Память выделилась
			if(pNewFatMap) {
				memset(pNewFatMap,CLUSTER_FREE,m_nByteAllocSize);
				memcpy(pNewFatMap,m_pFatMap,oldAllocSize);

				delete m_pFatMap;
				m_pFatMap=pNewFatMap;
				m_nByteFatSize	  += 1;
				nNewCluster			= m_nClusterNumber;
				m_nFirstEmpty		= nNewCluster+1;
				m_nClusterNumber	= m_nByteFatSize*CLUSTERS_PER_BYTE;
				return nNewCluster;
			} 
		// Память не выделилась
			else {
				return NA;
			}
		}
	}
}
//----------------------------------------------------------------------------[] 
identifier CLevelFile::WriteFile(identifier nCluster, byte *pData, size_t nSize)
{
	DEBUG_STACK_NAME (WriteFile);

	SERVER_DEBUG_ASSERT_RETURN (m_hFileDat >= 0, "CLevelFile: Dat not open in WriteFile()", NA);
	SERVER_DEBUG_ASSERT_RETURN (pData, "CLevelFile: Nothing to write", NA);
// Кластер известен
	if(nCluster!=UNKNOWN) {
		SERVER_DEBUG_ASSERT_RETURN (nCluster<m_nClusterNumber, "CLevelFile: Invalid cluster", NA);
		WriteCluster(nCluster,pData,nSize);
		return nCluster;
	} 
// Новый файл
	else {
		identifier nNewCluster=ObtainFreeCluster();
	// Есть свободный кластер
		if(nNewCluster!=UNKNOWN) {
			WriteCluster(nNewCluster,pData,nSize);
			return nNewCluster;
		} 
	// Облом
		else {
			return NA;
		}
	}
}
//----------------------------------------------------------------------------[] 
identifier CLevelFile::WriteBlock(identifier nCluster, byte *pData, size_t nOffset, size_t nSize)
{
	DEBUG_STACK_NAME (WriteBlock);

	SERVER_DEBUG_ASSERT_RETURN (m_hFileDat >= 0, "CLevelFile: Dat not open in WriteFile()", NA);
	SERVER_DEBUG_ASSERT_RETURN (pData, "CLevelFile: Nothing to write", NA);
	SERVER_DEBUG_ASSERT_RETURN (nOffset>=0, "CLevelFile: Negative offset passed", NA);
	SERVER_DEBUG_ASSERT_RETURN (nSize>=0, "CLevelFile: Negative size passed", NA);

	// Кластер известен
	if(nCluster!=UNKNOWN) {
		SERVER_DEBUG_ASSERT_RETURN (nCluster<m_nClusterNumber, "CLevelFile: Invalid cluster", NA);
		WriteClusterOffset(nCluster,pData,nOffset,nSize);
		return nCluster;
	} 
// Новый файл
	else {
		identifier nNewCluster=ObtainFreeCluster();
	// Есть свободный кластер
		if(nNewCluster!=UNKNOWN) {
			WriteClusterOffset(nNewCluster,pData,nOffset,nSize);
			return nNewCluster;
		} 
	// Облом
		else {
			return NA;
		}
	}
}
//----------------------------------------------------------------------------[] 
void CLevelFile::DeleteFile(identifier nCluster)
{
	DEBUG_STACK_NAME (DeleteFile);

	SERVER_DEBUG_ASSERT (nCluster!=UNKNOWN, "CLevelFile: nCluster==UNKNOWN");
	SetClusterState(nCluster,CLUSTER_FREE);
	m_nFirstEmpty = min (m_nFirstEmpty, nCluster);
}
//____________________________________________________________________________[]





















//______________________________________________________________________________
//                                                                            []
//` CFileMapFile 																					[]
//                                                                            []
size_t CFileMapFile::GetMemSize ()
{
	DEBUG_STACK_NAME (GetMemSize);

	return m_nAllocSize*MAP_ITEM_SIZE;
}
//----------------------------------------------------------------------------[] 
bool CFileMapFile::GetLockByFileID (identifier nFileID)
{
	DEBUG_STACK_NAME (GetLockByFileID);

	SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", true);
	CMAPFILE_PTR(nFileID);
	return (ptr->m_bLock!=0);
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::SetLockByFileID (identifier nFileID, bool bLock)
{
	DEBUG_STACK_NAME (SetLockByFileID);

	SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");
	CMAPFILE_PTR(nFileID);
	ptr->m_bLock = bLock;
	m_bMapChanged= true;
}
//----------------------------------------------------------------------------[] 
bool CFileMapFile::GetFreezeLevelByFileID (identifier nFileID)
{
	DEBUG_STACK_NAME (GetFreezeLevelByFileID);

	CMAPFILE_PTR(nFileID);
	return (ptr->m_bFreezeLevel!=0);
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::SetFreezeLevelByFileID (identifier nFileID, bool bFreezeLevel)
{
	DEBUG_STACK_NAME (SetFreezeLevelByFileID);

	CMAPFILE_PTR(nFileID);
	ptr->m_bFreezeLevel	= bFreezeLevel;
}
//----------------------------------------------------------------------------[] 
int CFileMapFile::GetLevelByFileID (identifier nFileID)
{
	DEBUG_STACK_NAME (GetLevelByFileID);

	CMAPFILE_PTR(nFileID);
	int nLevel = ptr->m_nLevel;
	SERVER_DEBUG_ASSERT_RETURN (nLevel>=0 && nLevel<FILE_LEVEL_NUM, "CFileMapFile: Bad file level!", nLevel);
	return nLevel;
}
//----------------------------------------------------------------------------[] 
identifier CFileMapFile::GetClusterByFileID (identifier nFileID)
{
	DEBUG_STACK_NAME (GetClusterByFileID);

	CMAPFILE_PTR(nFileID);
	return ptr->m_nClusterID;
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::CreateMapEntry (identifier nFileID, int nLevel, identifier nClusterID)
{
	DEBUG_STACK_NAME (CreateMapEntry);

	CMAPFILE_PTR(nFileID);
	ptr->m_nClusterID		= nClusterID;
	ptr->m_nLevel			= nLevel;
	ptr->m_bLock			= false;
	ptr->m_bFreezeLevel	= false;
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::InitMap (byte * pMap)
{
	DEBUG_STACK_NAME (InitMap);

	for (size_t i=0; i<m_nAllocSize; i++)
	{
		CMapItem * ptr = (CMapItem *) (pMap+i*MAP_ITEM_SIZE);
		ptr->m_nLevel			= 0;
		ptr->m_bLock			= false;
		ptr->m_bFreezeLevel	= false;
		ptr->m_nClusterID		= UNKNOWN;
	}
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::UnFreezeAll ()
{
	DEBUG_STACK_NAME (UnFreezeAll);

	for (size_t i=0; i<m_nAllocSize; i++)
	{
		CMAPFILE_PTR(i);
		ptr->m_bFreezeLevel	= false;
	}
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::Print ()
{
	DEBUG_STACK_NAME (Print);

	printf ("\n\n---------------------------\nMapFile:");
	printf ("\n  m_nFileNum:   %4d",		m_nFileNum);
	printf ("\n  m_nMapSize:   %4d",		m_nMapSize);
	printf ("\n  m_nAllocSize: %4d\n",	m_nAllocSize);
	for (size_t i=0; i<m_nMapSize; i++)
	{
		CMAPFILE_PTR(i);
		printf ("\n    nFileID: %d", i);
		if (ptr->m_nClusterID==UNKNOWN)
			printf (" [-]");
		else 
		{
			printf (" [%d:%d%s]", ptr->m_nLevel,ptr->m_nClusterID,ptr->m_bFreezeLevel?":F":"");
		}
	}
	printf ("\n---------------------------\n\n");
}
//----------------------------------------------------------------------------[] 
CFileMapFile::CFileMapFile(const char * sFileName, bool* pInit)
{
	DEBUG_STACK_NAME (CFileMapFile);

	char sMapFileName[1024];
	sprintf(sMapFileName,"%s.map",sFileName);
	m_bMapChanged	=	false;
	m_nFirstEmpty	=	0;
	*pInit			=	false;
	if((m_hFile=fopen_64 (sMapFileName, (O_RDWR | O_BINARY) /*"r+b"*/)) >= 0) 	
	{
	// Файл есть на диске
		fseek_64 (m_hFile,0,SEEK_END);
		m_nMapSize=((size_t)ftell_64(m_hFile)-sizeof (m_nFileNum)-sizeof (m_nFirstEmpty))/MAP_ITEM_SIZE;
		fseek_64 (m_hFile,0,SEEK_SET);
		fread_64	(&m_nFileNum,1,sizeof(m_nFileNum),m_hFile);
		fread_64	(&m_nFirstEmpty,1,sizeof(m_nFirstEmpty),m_hFile);
		m_nAllocSize	=	max (m_nMapSize, 1);
		SERVER_DEBUG_ASSERT (m_nAllocSize*MAP_ITEM_SIZE < 2*1000*1000*1000, "CFileMapFile::CFileMapFile --  Invaid m_nAllocSize");
		m_pMap			=	new byte [m_nAllocSize*MAP_ITEM_SIZE];
		InitMap				(m_pMap);
		fread_64				(m_pMap,m_nMapSize,MAP_ITEM_SIZE,m_hFile);
	} 
	else 
	{
	// Файла нет на диске, создаём в памяти
		m_hFile=fopen_64 (sMapFileName, (O_RDWR | O_CREAT | O_TRUNC | O_BINARY) /*"w+b"*/);
		SERVER_DEBUG_ASSERT (m_hFile >= 0, "CFileMapFile: Can't create MAP-file");
		if (m_hFile < 0)
		{
			CFileDriver::m_bError = true;
			return;
		}
		m_nFileNum		= 0;
		m_nMapSize		= 0;
		m_nAllocSize	= 1;
		m_bMapChanged	= true;
		m_pMap			= new byte [m_nAllocSize*MAP_ITEM_SIZE];
		InitMap			(m_pMap);
		*pInit			= true;
	}
	for (size_t i=0; i<m_nAllocSize; i++)
	{
		CMAPFILE_PTR (i);
		ptr->m_bLock = 0;
	}
}
//----------------------------------------------------------------------------[] 
CFileMapFile::~CFileMapFile()
{
	DEBUG_STACK_NAME (_CFileMapFile);

	close();
	if(m_pMap)
		delete m_pMap;
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::flush() 
{
	DEBUG_STACK_NAME (flush);

	m_nFirstEmpty = 0;
	UnFreezeAll		();
	if(m_bMapChanged) 
	{
		m_bMapChanged=false;
		SERVER_DEBUG_ASSERT (m_hFile >= 0 , "CFileMapFile: Map file not open");
		fseek_64		(m_hFile,0,SEEK_SET);
		fwrite_64	(&m_nFileNum,1,sizeof(m_nFileNum),m_hFile);
		fwrite_64	(&m_nFirstEmpty,1,sizeof(m_nFirstEmpty),m_hFile);			
		fwrite_64	(m_pMap,m_nMapSize,MAP_ITEM_SIZE,m_hFile);
	} 
	else 
	{
		SERVER_DEBUG_ASSERT (m_hFile >= 0 , "CFileMapFile: Map file not open");
	}
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::close()
{
	DEBUG_STACK_NAME (close);

	flush();
	fclose_64 (m_hFile);
}
//----------------------------------------------------------------------------[] 
identifier CFileMapFile::ObtainFreeFileID()
{
	DEBUG_STACK_NAME (ObtainFreeFileID);

	SERVER_DEBUG_ASSERT_RETURN (m_nMapSize<=m_nAllocSize, "CFileMapFile: m_nMapSize>m_nAllocSize", NA);
	SERVER_DEBUG_ASSERT_RETURN (m_nFileNum<=m_nMapSize, "CFileMapFile: m_nFileNum>m_nMapSize", NA);
	identifier nNewFileID = UNKNOWN;
	for(identifier i=m_nFirstEmpty; i<m_nMapSize; i++) {
	// Ищем свободный среди существующих
		identifier nClusterID = GetClusterByFileID(i);
		if(nClusterID==UNKNOWN) {
			nNewFileID		= i;
			m_nFirstEmpty	= nNewFileID+1;
			break;
		}
	}
	if(nNewFileID != UNKNOWN) {
	// Свободный найден
		return nNewFileID;
	} else {
	// Свободный не найден
		if(m_nMapSize==m_nAllocSize) 
		{
		// Вся выделенная память занята
			m_nAllocSize += max (1024, m_nAllocSize/10);
			byte *pNewMap= new byte [m_nAllocSize*MAP_ITEM_SIZE];
			SERVER_DEBUG_ASSERT_RETURN (pNewMap, "CFileMapFile: Cannot allocate memory", NA);
			if(pNewMap) {
				InitMap (pNewMap);
				memcpy  (pNewMap,m_pMap,m_nMapSize*MAP_ITEM_SIZE);
				delete m_pMap;
				m_pMap=pNewMap;
			} else return NA;
		}
		nNewFileID=m_nMapSize;
		m_nFirstEmpty = nNewFileID+1;
		m_nMapSize++;
		return nNewFileID;
	}
}
//----------------------------------------------------------------------------[] 
identifier CFileMapFile::CreateNewFileID(int nLevel, identifier nCluster)
{
	DEBUG_STACK_NAME (CreateNewFileID);

	identifier nNewFileID = ObtainFreeFileID();
	SERVER_DEBUG_ASSERT_RETURN (nNewFileID!=UNKNOWN, "CFileMapFile: Cannot create new File ID", NA);
	if(nNewFileID==UNKNOWN) return NA;

	CreateMapEntry (nNewFileID, nLevel, nCluster);
	m_nFileNum++;
	SERVER_DEBUG_ASSERT_RETURN (m_nFileNum<=m_nMapSize, "CFileMapFile: m_nFileNum>m_nMapSize", NA);
	m_bMapChanged=true;
	return nNewFileID;
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::SetNewCluster(identifier nFileID, identifier nClusterID)
{
	DEBUG_STACK_NAME (SetNewCluster);

	SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");
	
	CMAPFILE_PTR(nFileID);
	ptr->m_nClusterID	= nClusterID;
	m_bMapChanged=true;
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::SetNewLevel(identifier nFileID, int nLevel)
{
	DEBUG_STACK_NAME (SetNewLevel);

	SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");

	CMAPFILE_PTR(nFileID);
	ptr->m_nLevel	= nLevel;

	m_bMapChanged=true;
}
//----------------------------------------------------------------------------[] 
identifier CFileMapFile::GetFileCluster(identifier nFileID)
{
	DEBUG_STACK_NAME (GetFileCluster);

	SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", NA);
	return GetClusterByFileID(nFileID);
}
//----------------------------------------------------------------------------[] 
bool CFileMapFile::FileExist(identifier nFileID)
{
	DEBUG_STACK_NAME (FileExist);

	if(nFileID>=m_nMapSize)
		return false;
	return GetClusterByFileID(nFileID)!=UNKNOWN;
}
//----------------------------------------------------------------------------[] 
int CFileMapFile::GetFileLevel(identifier nFileID)
{
	DEBUG_STACK_NAME (GetFileLevel);

	SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", -1);
	return GetLevelByFileID(nFileID);
}
//----------------------------------------------------------------------------[] 
void CFileMapFile::DeleteFileID(identifier nFileID)
{
	DEBUG_STACK_NAME (DeleteFileID);

	SERVER_DEBUG_ASSERT (nFileID!=UNKNOWN, "CFileMapFile: nFileID==UNKNOWN");
	SetNewCluster(nFileID,NA);
	m_bMapChanged	=	true;
	m_nFirstEmpty	=	min (m_nFirstEmpty, nFileID);

	m_nFileNum--;
}
//----------------------------------------------------------------------------[] 
size_t CFileMapFile::GetList (identifier * pFileID)
{
	DEBUG_STACK_NAME (GetList);

	if(pFileID)
	{
		size_t nCFileID=0;
		for(identifier i=0; i<m_nMapSize; i++) if(GetClusterByFileID(i)!=UNKNOWN) 
		{
			pFileID[nCFileID++]=i;
		}
	}
	return m_nFileNum;
}
//____________________________________________________________________________[]


















//______________________________________________________________________________
//                                                                            []
//` CFileDriver																					[]
//                                                                            []
//----------------------------------------------------------------------------[] 
CFileDriver::CFileDriver (const char * sFileName)
{
	SERVER_DEBUG_TEXT ("Драйвер файловой системы приступил к работе");

	m_pMapFile=new CFileMapFile (sFileName, &m_bInit);
	if (CFileDriver::m_bError)
	{
		SERVER_DEBUG_ERROR ("Драйвер файловой системы обнаружил ошибку");
		return;
	}

	for(int i=0;i<FILE_LEVEL_NUM;i++)
	{
		m_pLevelFileArr[i]=new CLevelFile(sFileName,i);
	}
	m_this=this;
	if (m_bInit)
	{
		for (int i=0; i<FILE_ID_LAST; i++) 
		{
			char Data=0;
			Write(&Data,sizeof(Data));
		}			
	}
	m_bInit = false;
}
//----------------------------------------------------------------------------[] 
CFileDriver * CFileDriver::GetObject()
{
	SERVER_DEBUG_ASSERT_RETURN (m_this, "CFileDriver::GetObject(): Object not constructed", NULL);
	return m_this;
}
//----------------------------------------------------------------------------[] 
void CFileDriver::PrintMemoryReport ()
{
	int nFatSize=0;

	for(int i=0;i<FILE_LEVEL_NUM;i++)
	{
		nFatSize += m_pLevelFileArr[i]->GetMemSize();
	}
	printf ("\n\n---------------------------");
	printf ("\nMemory statistics:");
	printf ("\n  Fat: %10d", nFatSize);
	printf ("\n  Map: %10d", m_pMapFile->GetMemSize ());
	printf ("\n---------------------------\n\n");
}
//----------------------------------------------------------------------------[] 
CFileDriver::~CFileDriver ()
{
	if (!m_bError)
	{
		flush();
		delete m_pMapFile;
	}
	else if (m_pMapFile)
	{
		delete (char*) m_pMapFile;
	}
	for(int i=0;i<FILE_LEVEL_NUM;i++) if(m_pLevelFileArr[i])
		delete m_pLevelFileArr[i];
	m_this=NULL;
	SERVER_DEBUG_TEXT ("Драйвер файловой системы завершил работу");
}
//----------------------------------------------------------------------------[] 
void CFileDriver::flush()
{
	m_pMapFile->flush();
	for(int i=0;i<FILE_LEVEL_NUM;i++)
		m_pLevelFileArr[i]->flush();
}
//----------------------------------------------------------------------------[] 
identifier CFileDriver::Write (identifier nFileID, void * _pData, size_t nSize)
{
	byte * pData = (byte *)_pData;
	int nOldLevel=UNKNOWN;
	identifier nNewFileCluster=UNKNOWN;
// Переписать
	if(nFileID!=UNKNOWN) {
		nOldLevel=m_pMapFile->GetFileLevel(nFileID);
		SERVER_DEBUG_ASSERT_RETURN ((nOldLevel>=0) && (nOldLevel<=FILE_LEVEL_NUM), "CFilDriver: Wrong file Level", NA);
		nNewFileCluster=m_pMapFile->GetFileCluster(nFileID);
	}
	int nNewFileLevel=0;
	for(nNewFileLevel=0;nNewFileLevel<FILE_LEVEL_NUM;nNewFileLevel++) {
		if(nSize<=m_pLevelFileArr[nNewFileLevel]->GetClusterSize()) {
			break;
		}
	}
	nNewFileLevel=min((FILE_LEVEL_NUM-1),nNewFileLevel);

// Замораживаем возможность перехода на нижний уровень
	if (nNewFileLevel!=UNKNOWN && nOldLevel!=UNKNOWN && nFileID!=UNKNOWN && nNewFileLevel<nOldLevel)
	{
		if (m_pMapFile->GetFreezeLevelByFileID (nFileID))
		{
			nNewFileLevel = nOldLevel;
		}
		m_pMapFile->SetFreezeLevelByFileID (nFileID, true);
	}

	if((nNewFileLevel!=nOldLevel)&&(nFileID!=UNKNOWN)) {
		m_pLevelFileArr[nOldLevel]->DeleteFile(m_pMapFile->GetFileCluster(nFileID));
		m_pMapFile->SetNewLevel(nFileID,nNewFileLevel);
		nNewFileCluster=UNKNOWN;
	}


	if(nFileID==UNKNOWN) {
		nFileID=m_pMapFile->CreateNewFileID(nNewFileLevel,UNKNOWN);
	}
	nNewFileCluster=m_pLevelFileArr[nNewFileLevel]->WriteFile(nNewFileCluster,pData,nSize);
	m_pMapFile->SetNewCluster(nFileID,nNewFileCluster);
	return nFileID;
}
//----------------------------------------------------------------------------[] 
identifier CFileDriver::WriteBlock (identifier nFileID, void * _pData, size_t nOffset, size_t nSize)
{
	byte * pData = (byte *)_pData;
	int nOldLevel=UNKNOWN;
	identifier nNewFileCluster=UNKNOWN;
// Переписать
	SERVER_DEBUG_ASSERT_RETURN (nFileID!=UNKNOWN, "CFilDriver: Cannot write block to unexistant file", NA);
	if(nFileID!=UNKNOWN) {
		nOldLevel=m_pMapFile->GetFileLevel(nFileID);
		SERVER_DEBUG_ASSERT_RETURN ((nOldLevel>=0) && (nOldLevel<=FILE_LEVEL_NUM), "CFilDriver: Wrong file Level", NA);
		nNewFileCluster=m_pMapFile->GetFileCluster(nFileID);
	}
	int nNewFileLevel=0;
	for(nNewFileLevel=nOldLevel;nNewFileLevel<FILE_LEVEL_NUM;nNewFileLevel++) {
		if((nOffset+nSize)<=m_pLevelFileArr[nNewFileLevel]->GetClusterSize()) {
			break;
		}
	}
	nNewFileLevel=min((FILE_LEVEL_NUM-1),nNewFileLevel);

	if(nNewFileLevel!=nOldLevel) {
		byte *pOldFile = new byte[nOffset+nSize];
		m_pLevelFileArr[nOldLevel]->ReadFile(m_pMapFile->GetFileCluster(nFileID),pOldFile,min(nOffset,m_pLevelFileArr[nOldLevel]->GetClusterSize()));
		m_pLevelFileArr[nOldLevel]->DeleteFile(m_pMapFile->GetFileCluster(nFileID));
		memcpy(pOldFile+nOffset,pData,nSize);
		m_pMapFile->SetNewLevel(nFileID,nNewFileLevel);
		nNewFileCluster=m_pLevelFileArr[nNewFileLevel]->WriteFile(UNKNOWN,pOldFile,nOffset+nSize);
		m_pMapFile->SetNewCluster(nFileID,nNewFileCluster);
		delete pOldFile;
		return nFileID;
	}

	nNewFileCluster=m_pLevelFileArr[nNewFileLevel]->WriteBlock(nNewFileCluster,pData,nOffset,nSize);
	return nFileID;
}
//----------------------------------------------------------------------------[] 
identifier CFileDriver::CreateNewFile ()
{ 
	byte Data=0xff;
	return Write(UNKNOWN,&Data,sizeof(Data));
}
//----------------------------------------------------------------------------[] 
identifier CFileDriver::Write (void* pData, size_t nSize)  
{ 
	return Write(UNKNOWN,pData,nSize);
}
//----------------------------------------------------------------------------[] 
void CFileDriver::SetSize(identifier nFileID, size_t nSize)
{
	int nOldLevel=UNKNOWN;
	identifier nNewFileCluster=UNKNOWN;
	SERVER_DEBUG_ASSERT (nFileID!=UNKNOWN, "CFilDriver: Cannot change size of unexistant file");
	SERVER_DEBUG_ASSERT (nSize, "CFilDriver::SetSize: Size == 0 (Размер файла не может быть выставлен в ноль)");
	if(nFileID!=UNKNOWN) {
		nOldLevel=m_pMapFile->GetFileLevel(nFileID);
		SERVER_DEBUG_ASSERT ((nOldLevel>=0) && (nOldLevel<=FILE_LEVEL_NUM), "CFilDriver: Wrong file Level");
		nNewFileCluster=m_pMapFile->GetFileCluster(nFileID);
	}
	int nNewFileLevel=0;
	for(nNewFileLevel=0;nNewFileLevel<FILE_LEVEL_NUM;nNewFileLevel++) {
		if(nSize<=m_pLevelFileArr[nNewFileLevel]->GetClusterSize()) {
			break;
		}
	}
	nNewFileLevel=min((FILE_LEVEL_NUM-1),nNewFileLevel);

	if(nNewFileLevel!=nOldLevel) {
		size_t nNewSize = min(nSize,min(m_pLevelFileArr[nOldLevel]->GetClusterSize(),m_pLevelFileArr[nNewFileLevel]->GetClusterSize()));
		byte * pData	 = new byte[nNewSize];
		m_pLevelFileArr[nOldLevel]->ReadFile(nNewFileCluster,pData,nNewSize);
		m_pLevelFileArr[nOldLevel]->DeleteFile(nNewFileCluster);
		nNewFileCluster=m_pLevelFileArr[nNewFileLevel]->WriteFile(UNKNOWN,pData,nNewSize);
		m_pMapFile->SetNewLevel(nFileID,nNewFileLevel);
		m_pMapFile->SetNewCluster(nFileID,nNewFileCluster);
		delete pData;
	}
}
//----------------------------------------------------------------------------[] 
size_t CFileDriver::GetMaxSize(identifier nFileID)
{
	return Read(nFileID);
}
//----------------------------------------------------------------------------[] 
size_t CFileDriver::Read (identifier nFileID, void * _pData, size_t nSize)
{
	byte * pData = (byte *)_pData;
	int nLevel=m_pMapFile->GetFileLevel(nFileID);
	return m_pLevelFileArr[nLevel]->ReadFile(m_pMapFile->GetFileCluster(nFileID),pData,nSize);
}
//----------------------------------------------------------------------------[] 
size_t CFileDriver::ReadBlock (identifier nFileID, void * _pData, size_t nOffset, size_t nSize)
{
	byte * pData = (byte *)_pData;
	int nLevel=m_pMapFile->GetFileLevel(nFileID);
	return m_pLevelFileArr[nLevel]->ReadBlock(m_pMapFile->GetFileCluster(nFileID),pData,nOffset,nSize);
}
//----------------------------------------------------------------------------[] 
void CFileDriver::Delete (identifier nFileID) 
{
	SERVER_DEBUG_ASSERT (nFileID!=UNKNOWN, "CFilDriver: nFileID==UNKNOWN");
	int nLevel=m_pMapFile->GetFileLevel(nFileID);
	m_pLevelFileArr[nLevel]->DeleteFile(m_pMapFile->GetFileCluster(nFileID));
	m_pMapFile->DeleteFileID(nFileID);
}
//----------------------------------------------------------------------------[] 
void CFileDriver::PrintMap ()
{
	m_pMapFile->Print ();
}
//----------------------------------------------------------------------------[] 
size_t CFileDriver::GetList (identifier * pFileID)
{
	return m_pMapFile->GetList(pFileID);
}
//----------------------------------------------------------------------------[] 
void CFileDriver::Lock(identifier nFileID)
{
	SERVER_DEBUG_ASSERT (!(m_pMapFile->GetLockByFileID(nFileID)), "CFilDriver: File already locked");
	m_pMapFile->SetLockByFileID(nFileID,true);
}
//----------------------------------------------------------------------------[] 
bool CFileDriver::isLocked(identifier nFileID)
{
	return m_pMapFile->GetLockByFileID(nFileID);
}
//----------------------------------------------------------------------------[] 
void CFileDriver::Unlock(identifier nFileID)
{
	SERVER_DEBUG_ASSERT ((m_pMapFile->GetLockByFileID(nFileID)), "CFilDriver: File not locked");
	m_pMapFile->SetLockByFileID(nFileID,false);
}
//----------------------------------------------------------------------------[] 
bool CFileDriver::Exist(identifier nFileID)
{
	return m_pMapFile->FileExist(nFileID);
}
//____________________________________________________________________________[]























/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` END OF FILE                                                               []           
[]                                                                            []
[]____________________________________________________________________________[]
*/
