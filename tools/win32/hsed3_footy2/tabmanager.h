/*------------------------------------------------------------------------------
	Header of tab management routines
------------------------------------------------------------------------------*/

#ifndef __tabmanager_h
#define __tabmanager_h

// Tab Information structure
typedef struct tagTabInfo {
	TCHAR FileName[_MAX_PATH];
	TCHAR TitleName[_MAX_FNAME + _MAX_EXT];
    TCHAR DirName[_MAX_PATH];
	ULONGLONG FileIndex;
	int LatestUndoNum;
	BOOL NeedSave;
	int FootyID;
	struct {
		struct tagTabInfo *prev;
		struct tagTabInfo *next;
	} ZOrder;
} TABINFO;

// Functions
void CreateTab(int, LPCTSTR , LPCTSTR , LPCTSTR );
void DeleteTab(int);
TABINFO *GetTabInfo(int);
int SearchTab(LPCTSTR , LPCTSTR , LPCTSTR , ULONGLONG);
void SetTabInfo(int, LPCTSTR , LPCTSTR , LPCTSTR , BOOL);
void ActivateTab(int, int);
void ChangeZOrder(int, int);
int GetTabID(int);

#endif // #ifndef __tabmanager_h