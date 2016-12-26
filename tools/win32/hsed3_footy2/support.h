/*------------------------------------------------------------------------------
	Header of HSED support routines
------------------------------------------------------------------------------*/

#ifndef __support_h
#define __support_h

int __cdecl msgboxf(HWND, LPCTSTR, LPCTSTR, UINT, ...);
void ShowLastError();
LPTSTR *CommandLineToArgvA(LPTSTR, int *);
size_t strlcpy(LPTSTR , LPTSTR , size_t);
ULONGLONG GetFileIndex(LPCTSTR );
int getStrLinesSize(LPCTSTR );
void GetDirName(LPTSTR dirName, LPCTSTR path);
#ifdef UNICODE
UINT WinExec(LPCTSTR lpCmdLine, UINT uCmdShow);
#endif

class FileList{
private:
	TCHAR *buf, *buf2;
	LPTSTR *index;
	int bufsize, idxsize, offset, idxoffset;

public:
	FileList();
	~FileList();
	void reset();
	void add(LPCTSTR );
	LPCTSTR get(int);
	void setlist(LPCTSTR );
	LPCTSTR getlist();
	size_t num();
};

#endif // #ifndef __support_h