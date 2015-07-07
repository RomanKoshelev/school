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

	public: size_t GetClusterSize();

	protected: unsigned long MakeSizeForLevel (unsigned int nLevel);

	public: size_t GetMemSize ();

	protected: const char * GetSizeName (unsigned long nSize);

	protected: const char * MakeLevelName (unsigned int nLevel);

	public: CLevelFile	(const char * sFileName, int nLevel);

	public: ~CLevelFile	();
	
	public: void flush();

	protected: void close();

	public: BIT GetClusterState(identifier nCluster);

	protected: BIT SetClusterState(identifier nCluster, BIT bSet);

	public: size_t ReadFile(identifier nCluster, byte *pData=NULL, size_t nSize=0);

	public: size_t ReadBlock(identifier nCluster, byte *pData=NULL, size_t nOffset=0, size_t nSize=0);

	protected: void WriteCluster(identifier nCluster, void *pData, size_t nSize);

	protected: void WriteClusterOffset(identifier nCluster, void *pData, size_t nOffset, size_t nSize);

	protected: identifier ObtainFreeCluster();

	public: identifier WriteFile(identifier nCluster, byte *pData, size_t nSize);

	public: identifier WriteBlock(identifier nCluster, byte *pData, size_t nOffset, size_t nSize);

	public: void DeleteFile(identifier nCluster);
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

	public: size_t GetMemSize ();

	public: bool GetLockByFileID (identifier nFileID);
	public: void SetLockByFileID (identifier nFileID, bool bLock);

	public: bool GetFreezeLevelByFileID (identifier nFileID);
	public: void SetFreezeLevelByFileID (identifier nFileID, bool bFreezeLevel);

	int GetLevelByFileID (identifier nFileID);
	identifier GetClusterByFileID (identifier nFileID);
	void CreateMapEntry (identifier nFileID, int nLevel, identifier nClusterID);

	protected: void InitMap (byte * pMap);
	
	protected: void UnFreezeAll ();

	public: void Print ();

	public: CFileMapFile(const char * sFileName, bool* pInit);
	public: ~CFileMapFile();

	public: void flush();

	protected: void close();

	protected: identifier ObtainFreeFileID();

	public: identifier CreateNewFileID(int nLevel, identifier nCluster);

	public: void SetNewCluster(identifier nFileID, identifier nClusterID);

	public: void SetNewLevel(identifier nFileID, int nLevel);

	public: identifier GetFileCluster(identifier nFileID);

	public: bool FileExist(identifier nFileID);

	public: int GetFileLevel(identifier nFileID);

	public: void DeleteFileID(identifier nFileID);

	public: size_t GetList (identifier * pFileID=NULL);
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

	static	CFileDriver *	m_this;
	static	bool				m_bInit;
	public:	static	bool	m_bError;

	public: CFileDriver (const char * sFileName);

	public: static CFileDriver * GetObject();

	public: void PrintMemoryReport ();

	public: ~CFileDriver ();

	public: void flush();
	public: identifier Write (identifier nFileID, void * _pData, size_t nSize);

	public: identifier WriteBlock (identifier nFileID, void * _pData, size_t nOffset, size_t nSize);
	public: identifier CreateNewFile ();

	public: identifier Write (void* pData, size_t nSize);
	public: void SetSize(identifier nFileID, size_t nSize);
	public: size_t GetMaxSize(identifier nFileID);
	public: size_t Read (identifier nFileID, void * _pData=NULL, size_t nSize=0);
	public: size_t ReadBlock (identifier nFileID, void * _pData=NULL, size_t nOffset=0, size_t nSize=0);
	public: void Delete (identifier nFileID);

	public: void PrintMap ();

	public: size_t GetList (identifier * pFileID=NULL);

	public: void Lock(identifier nFileID);

	public: bool isLocked(identifier nFileID);

	public: void Unlock(identifier nFileID);

	public: bool Exist(identifier nFileID);
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