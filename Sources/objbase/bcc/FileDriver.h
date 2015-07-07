/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            FileDriver.h																[]
[] Date:            01/22/99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     File driver																[]
[]____________________________________________________________________________[]
*/
#ifndef FileDriver_H
#define FileDriver_H

#ifndef O_BINARY
#define O_BINARY	0
#endif

#define	CLUSTER_EXIST	((BIT)1)
#define	CLUSTER_FREE	((BIT)0)

#define  OPTIMIZED_FAT
#ifdef OPTIMIZED_FAT
	#define CLUSTERS_PER_BYTE 8
#else
	#define CLUSTERS_PER_BYTE 1
#endif

#ifdef STUPID_SKY_WEB // !!!
	#define FILE_LEVEL_NUM 50
#else
	#define FILE_LEVEL_NUM 62
#endif

#ifdef WIN32
	#define off_t __int64
#else
	#include <unistd.h>
#endif

off_t		fseek_64		(int hFile, off_t nSeek, int whence);
off_t		ftell_64		(int hFile);

size_t	fread_64		(      void * buffer, size_t size, size_t count, int hFile);
size_t	fwrite_64	(const void * buffer, size_t size, size_t count, int hFile);

int		fopen_64		(const char * pFileName, int flag);
int		fclose_64	(int hFile);


/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[]` CFileDriver
[]                                                                            []
[]____________________________________________________________________________[]
*/





//______________________________________________________________________________
//                                                                            []
//` CLevelFile																						[]
//                                                                            []
class CLevelFile 
{
	int			m_hFileFat;
	int			m_hFileDat;
	size_t		m_nByteFatSize;
	size_t		m_nByteAllocSize;
	size_t		m_nClusterNumber;
	byte *		m_pFatMap;
	int			m_nLevel;
	size_t		m_nClusterSize;
	bool			m_bFatChanged;
	bool			m_bDatChanged;
	identifier	m_nFirstEmpty;

	public: size_t GetClusterSize() { return m_nClusterSize; }

	protected: unsigned long MakeSizeForLevel (unsigned int nLevel)
	{
		unsigned long nSize = 1 << (nLevel+1)/2;
		if ((nLevel+1)%2)
		{
			nSize = (nSize+2*nSize)/2;
		}	
		return nSize;
	}

	public: size_t GetMemSize ()
	{
		return m_nByteAllocSize;
	}

	protected: const char * GetSizeName (unsigned long nSize)
	{
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

	protected: const char * MakeLevelName (unsigned int nLevel)
	{
		unsigned long nSize = MakeSizeForLevel(nLevel);
		static char SSS[1024];
		sprintf (SSS, "[%02d]_%s", nLevel, GetSizeName (nSize));
		for (int j=0; SSS[j]; j++)	if (SSS[j]==' ')	
			SSS[j] = '_';
		return SSS;
	}

	public: CLevelFile	(const char * sFileName, int nLevel)
	{
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
	public: ~CLevelFile	() {
		close();
		if(m_pFatMap)
			delete m_pFatMap;
	}

	public: void flush()
	{
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
	protected: void close()
	{
		flush();
		SERVER_DEBUG_ASSERT (m_hFileFat >= 0, "CLevelFile: Fat not open in close()");
		fclose_64 (m_hFileFat);
		SERVER_DEBUG_ASSERT (m_hFileDat >= 0, "CLevelFile: Dat not open in close()");
		fclose_64 (m_hFileDat);
	}

	public: BIT GetClusterState(identifier nCluster)
	{
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
	protected: BIT SetClusterState(identifier nCluster, BIT bSet)
	{
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

	public: size_t ReadFile(identifier nCluster, byte *pData=NULL, size_t nSize=0)
	{
		return ReadBlock(nCluster,pData,0,nSize);
	}

	public: size_t ReadBlock(identifier nCluster, byte *pData=NULL, size_t nOffset=0, size_t nSize=0)
	{
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

	protected: void WriteCluster(identifier nCluster, void *pData, size_t nSize)
	{
		m_bDatChanged=true;
		SERVER_DEBUG_ASSERT (nSize<=m_nClusterSize, "CLevelFile: Cluster overflow");
		off_t			nSeek=((off_t)nCluster*(off_t)m_nClusterSize);
		fseek_64		(m_hFileDat,nSeek,SEEK_SET);
		size_t		nWriten = fwrite_64 (pData,1,nSize,m_hFileDat);
		SERVER_DEBUG_ASSERT (nWriten==nSize, "CLevelFile: Cannot write data");
		SetClusterState(nCluster,CLUSTER_EXIST);
	}

	protected: void WriteClusterOffset(identifier nCluster, void *pData, size_t nOffset, size_t nSize)
	{
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

	protected: identifier ObtainFreeCluster()
	{
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

	public: identifier WriteFile(identifier nCluster, byte *pData, size_t nSize)
	{
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

	public: identifier WriteBlock(identifier nCluster, byte *pData, size_t nOffset, size_t nSize)
	{
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

	public: void DeleteFile(identifier nCluster)
	{
		SERVER_DEBUG_ASSERT (nCluster!=UNKNOWN, "CLevelFile: nCluster==UNKNOWN");
		SetClusterState(nCluster,CLUSTER_FREE);
		//m_nFirstEmpty = min (m_nFirstEmpty, nCluster);
	}

};
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` CFileMapFile 																					[]
//                                                                            []
class CFileMapFile 
{
	int				m_hFile;
	byte			 *	m_pMap;
	size_t			m_nMapSize;			// В элементах
	size_t			m_nAllocSize;		// В элементах
	bool				m_bMapChanged;
	size_t			m_nFileNum;
	identifier		m_nFirstEmpty;

	struct CMapItem
	{
		identifier		m_nClusterID	: 32;
		unsigned int	m_nLevel			: 6;
		unsigned int	m_bLock			: 1;
		unsigned int	m_bFreezeLevel	: 1;
	};
	#define CMAPFILE_PTR(i)		CMapItem * ptr = (CMapItem *) (m_pMap+i*MAP_ITEM_SIZE);
	#define MAP_ITEM_SIZE 5

	public: size_t GetMemSize ()
	{
		return m_nAllocSize*MAP_ITEM_SIZE;
	}

	public: bool GetLockByFileID (identifier nFileID)
	{
		SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", true);
		CMAPFILE_PTR(nFileID);
		return (ptr->m_bLock!=0);
	}
	public: void SetLockByFileID (identifier nFileID, bool bLock)
	{
		SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");
		CMAPFILE_PTR(nFileID);
		ptr->m_bLock = bLock;
		m_bMapChanged= true;
	}

	public: bool GetFreezeLevelByFileID (identifier nFileID)
	{
		CMAPFILE_PTR(nFileID);
		return (ptr->m_bFreezeLevel!=0);
	}
	public: void SetFreezeLevelByFileID (identifier nFileID, bool bFreezeLevel)
	{
		CMAPFILE_PTR(nFileID);
		ptr->m_bFreezeLevel	= bFreezeLevel;
	}


	int GetLevelByFileID (identifier nFileID)
	{
		CMAPFILE_PTR(nFileID);
		int nLevel = ptr->m_nLevel;
		SERVER_DEBUG_ASSERT_RETURN (nLevel>=0 && nLevel<FILE_LEVEL_NUM, "CFileMapFile: Bad file level!", nLevel);
		return nLevel;
	}
	identifier GetClusterByFileID (identifier nFileID)
	{
		CMAPFILE_PTR(nFileID);
		return ptr->m_nClusterID;
	}
	void CreateMapEntry (identifier nFileID, int nLevel, identifier nClusterID)
	{
		CMAPFILE_PTR(nFileID);
		ptr->m_nClusterID		= nClusterID;
		ptr->m_nLevel			= nLevel;
		ptr->m_bLock			= false;
		ptr->m_bFreezeLevel	= false;
	}

	protected: void InitMap (byte * pMap)
	{
		for (size_t i=0; i<m_nAllocSize; i++)
		{
			CMapItem * ptr = (CMapItem *) (pMap+i*MAP_ITEM_SIZE);
			ptr->m_nLevel			= 0;
			ptr->m_bLock			= false;
			ptr->m_bFreezeLevel	= false;
			ptr->m_nClusterID		= UNKNOWN;
		}
	}
	
	protected: void UnFreezeAll ()
	{
		for (size_t i=0; i<m_nAllocSize; i++)
		{
			CMAPFILE_PTR(i);
			ptr->m_bFreezeLevel	= false;
		}
	}

	public: void Print ()
	{
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

	public: CFileMapFile(const char * sFileName, bool* pInit)
	{
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

	public: ~CFileMapFile()
	{
		close();
		if(m_pMap)
			delete m_pMap;
	}

	public: void flush() 
	{
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

	protected: void close()
	{
		flush();
		fclose_64 (m_hFile);
	}

	protected: identifier ObtainFreeFileID()
	{
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

	public: identifier CreateNewFileID(int nLevel, identifier nCluster)
	{
		identifier nNewFileID = ObtainFreeFileID();
		SERVER_DEBUG_ASSERT_RETURN (nNewFileID!=UNKNOWN, "CFileMapFile: Cannot create new File ID", NA);
		if(nNewFileID==UNKNOWN) return NA;

		CreateMapEntry (nNewFileID, nLevel, nCluster);
		m_nFileNum++;
		SERVER_DEBUG_ASSERT_RETURN (m_nFileNum<=m_nMapSize, "CFileMapFile: m_nFileNum>m_nMapSize", NA);
		m_bMapChanged=true;
		return nNewFileID;
	}

	public: void SetNewCluster(identifier nFileID, identifier nClusterID)
	{
		SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");
		
		CMAPFILE_PTR(nFileID);
		ptr->m_nClusterID	= nClusterID;
		m_bMapChanged=true;
	}

	public: void SetNewLevel(identifier nFileID, int nLevel)
	{
		SERVER_DEBUG_ASSERT (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID");

		CMAPFILE_PTR(nFileID);
		ptr->m_nLevel	= nLevel;

		m_bMapChanged=true;
	}

	public: identifier GetFileCluster(identifier nFileID)
	{
		SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", NA);
		return GetClusterByFileID(nFileID);
	}

	public: bool FileExist(identifier nFileID)
	{
		if(nFileID>=m_nMapSize)
			return false;
		return GetClusterByFileID(nFileID)!=UNKNOWN;
	}

	public: int GetFileLevel(identifier nFileID)
	{
		SERVER_DEBUG_ASSERT_RETURN (nFileID<m_nMapSize, "CFileMapFile: Invalid File ID", -1);
		return GetLevelByFileID(nFileID);
	}

	public: void DeleteFileID(identifier nFileID)
	{
		SERVER_DEBUG_ASSERT (nFileID!=UNKNOWN, "CFileMapFile: nFileID==UNKNOWN");
		SetNewCluster(nFileID,NA);
		m_bMapChanged	=	true;
		//m_nFirstEmpty	=	min (m_nFirstEmpty, nFileID);

		m_nFileNum--;
	}

	public: size_t GetList (identifier * pFileID=NULL)
	{
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
};
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` CFileDriver																					[]
//                                                                            []
class CFileDriver
{
	CLevelFile		* m_pLevelFileArr[FILE_LEVEL_NUM];
	CFileMapFile	* m_pMapFile;

	static	CFileDriver * m_this;
	static	bool			  m_bInit;

	public: CFileDriver (const char * sFileName)
	{
		SERVER_DEBUG_TEXT ("Драйвер файловой системы приступил к работе");

		m_pMapFile=new CFileMapFile(sFileName, &m_bInit);
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

	public: static CFileDriver * GetObject()
	{
		SERVER_DEBUG_ASSERT_RETURN (m_this, "CFileDriver::GetObject(): Object not constructed", NULL);
		return m_this;
	}

	public: void PrintMemoryReport ()
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

	public: ~CFileDriver ()
	{
//		ofstream chkdsk("list.cd");
//		CheckDisk(chkdsk);
		flush();
		delete m_pMapFile;
		for(int i=0;i<FILE_LEVEL_NUM;i++) if(m_pLevelFileArr[i])
			delete m_pLevelFileArr[i];
		m_this=NULL;
		SERVER_DEBUG_TEXT ("Драйвер файловой системы завершил работу");
	}


	public: void flush()
	{
		m_pMapFile->flush();
		for(int i=0;i<FILE_LEVEL_NUM;i++)
			m_pLevelFileArr[i]->flush();
	}

	public: identifier Write (identifier nFileID, void * _pData, size_t nSize)
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

	public: identifier WriteBlock (identifier nFileID, void * _pData, size_t nOffset, size_t nSize)
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
	public: identifier CreateNewFile ()
	{ 
		byte Data=0xff;
		return Write(UNKNOWN,&Data,sizeof(Data));
	}

	public: identifier Write (void* pData, size_t nSize)  
	{ 
		return Write(UNKNOWN,pData,nSize);
	}

	public: void SetSize(identifier nFileID, size_t nSize)
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
	public: size_t GetMaxSize(identifier nFileID)
	{
		return Read(nFileID);
	}
	public: size_t Read (identifier nFileID, void * _pData=NULL, size_t nSize=0)
	{
		byte * pData = (byte *)_pData;
		int nLevel=m_pMapFile->GetFileLevel(nFileID);
		return m_pLevelFileArr[nLevel]->ReadFile(m_pMapFile->GetFileCluster(nFileID),pData,nSize);
	}
	public: size_t ReadBlock (identifier nFileID, void * _pData=NULL, size_t nOffset=0, size_t nSize=0)
	{
		byte * pData = (byte *)_pData;
		int nLevel=m_pMapFile->GetFileLevel(nFileID);
		return m_pLevelFileArr[nLevel]->ReadBlock(m_pMapFile->GetFileCluster(nFileID),pData,nOffset,nSize);
	}
	public: void Delete (identifier nFileID) 
	{
		SERVER_DEBUG_ASSERT (nFileID!=UNKNOWN, "CFilDriver: nFileID==UNKNOWN");
		int nLevel=m_pMapFile->GetFileLevel(nFileID);
		m_pLevelFileArr[nLevel]->DeleteFile(m_pMapFile->GetFileCluster(nFileID));
		m_pMapFile->DeleteFileID(nFileID);
	}

	public: void PrintMap ()
	{
		m_pMapFile->Print ();
	}

	public: size_t GetList (identifier * pFileID=NULL)
	{
		return m_pMapFile->GetList(pFileID);
	}

	public: void Lock(identifier nFileID)
	{
		SERVER_DEBUG_ASSERT (!(m_pMapFile->GetLockByFileID(nFileID)), "CFilDriver: File already locked");
		m_pMapFile->SetLockByFileID(nFileID,true);
	}

	public: bool isLocked(identifier nFileID)
	{
		return m_pMapFile->GetLockByFileID(nFileID);
	}

	public: void Unlock(identifier nFileID)
	{
		SERVER_DEBUG_ASSERT ((m_pMapFile->GetLockByFileID(nFileID)), "CFilDriver: File not locked");
		m_pMapFile->SetLockByFileID(nFileID,false);
	}

	public: bool Exist(identifier nFileID)
	{
		return m_pMapFile->FileExist(nFileID);
	}

#if 0 //{` 16.03.99 RomanVK: 
	public: void CheckDisk (ofstream fsOut, bool bCorrect=false)
	{
		flush();
	// Map to free first cluster
		size_t		nFileNum	= GetList();
		identifier	* pList	= new identifier[nFileNum];
		GetList(pList);
		identifier	i;
		fsOut << "\n\nChecking disk.\n\n";
		fsOut << "Total " << nFileNum << " files.\n";

	// Check for invalid Map entries
		for(i=0; i<nFileNum; i++) {
			int			nLevel=m_pMapFile->GetFileLevel(pList[i]);
			identifier	nCluster=m_pMapFile->GetFileCluster(pList[i]);
			SERVER_DEBUG_ASSERT (m_pLevelFileArr[nLevel]->GetClusterState(nCluster)==CLUSTER_EXIST, "CFilDriver: m_pLevelFileArr[nLevel]->GetClusterState(nCluster)!=CLUSTER_EXIST");
			if(m_pLevelFileArr[nLevel]->GetClusterState(nCluster)==CLUSTER_FREE) {
				fsOut << "First cluster not allocated for file ID " << pList[i] << "\n";
				if(bCorrect) {
					m_pMapFile->SetNewCluster(pList[i], NA);
					fsOut << "Removed invalid Map entry\n";
				}
			}
		}

		delete pList;

		fsOut << "\n\nCheckDisk finished\n";
	}
#endif //}0
};

extern CFileDriver theFileDriver;
//____________________________________________________________________________[]

#define FD (*CFileDriver::GetObject())

#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/