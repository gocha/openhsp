/*------------------------------------------------------------------------------
	Suport routines for HSP Script Editor
------------------------------------------------------------------------------*/

#include <windows.h>
#include <stdarg.h>
#include <stdlib.h>
#include <tchar.h>

#include "support.h"

#define BUF_BLOCK_SIZE (_MAX_PATH + 1) * 16
#define IDX_BLOCK_SIZE 16

int __cdecl msgboxf(HWND hWnd, LPCTSTR lpFormat, LPCTSTR lpCaption, UINT uType, ...)
{
	va_list al;
	TCHAR szBuf[1280];

	va_start(al, uType);
	wvsprintf(szBuf, lpFormat, al);
	va_end(al);

	return MessageBox(hWnd, szBuf, lpCaption, uType);
}

LPTSTR *CommandLineToArgvA(LPTSTR CmdLine, int *_argc)
{
	LPTSTR *argv, _argv;
	unsigned long len, argc, i, j;
	TCHAR tmp;
	BOOL in_QM, in_TEXT, in_SPACE;

	len = lstrlen(CmdLine);
	i = (((len+2)/2)*sizeof(LPTSTR) + sizeof(LPTSTR));

	argv = (LPTSTR *)GlobalAlloc(GMEM_FIXED, i + (len+2)*sizeof(TCHAR));
	_argv = (LPTSTR)(((PUCHAR)argv)+i);

	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;

	while( tmp = CmdLine[i] ) {
		if(in_QM) {
			if(tmp == TEXT('\"')) in_QM = FALSE;
			else {
				_argv[j] = tmp;
				j++;
			}
		} else {
			switch(tmp) {
				case TEXT('\"'):
					in_QM = TRUE;
					in_TEXT = TRUE;
					if(in_SPACE) {
						argv[argc] = _argv+j;
						argc++;
					}
					in_SPACE = FALSE;
					break;
				case TEXT(' '):
				case TEXT('\t'):
				case TEXT('\n'):
				case TEXT('\r'):
					if(in_TEXT) {
						_argv[j] = TEXT('\0');
						j++;
					}
					in_TEXT = FALSE;
					in_SPACE = TRUE;
					break;
				default:
					in_TEXT = TRUE;
					if(in_SPACE) {
						argv[argc] = _argv+j;
						argc++;
					}
					_argv[j] = tmp;
					j++;
					in_SPACE = FALSE;
					break;
			}
		}
		i++;
	}
	_argv[j] = TEXT('\0');
	argv[argc] = NULL;

	*_argc = argc;
	return argv;
}

size_t strlcpy(LPTSTR dest, LPTSTR source, size_t size)
{
	size_t i;

	if(size <= 0) return 0;
	size--;
	for(i = 0; source[i] != TEXT('\0') && i < size; i++)
		dest[i] = source[i];
	dest[i] = TEXT('\0');
	return i;
}

FileList::FileList()
{
	bufsize = BUF_BLOCK_SIZE;
	idxsize = IDX_BLOCK_SIZE;
	buf = (LPTSTR )malloc(bufsize * sizeof(TCHAR));
	buf2 = NULL;
	index = (LPTSTR *)malloc(idxsize * sizeof(LPTSTR ));
	offset = idxoffset = 0;
}

FileList::~FileList()
{
	free(buf);
	free(buf2);
	free(index);
}

void FileList::add(LPCTSTR filename)
{
	int length = (lstrlen(filename) + 1)*sizeof(TCHAR);
	if(offset + length >= bufsize)
		buf = (LPTSTR )realloc(buf, (bufsize += BUF_BLOCK_SIZE));
	if(idxoffset >= idxsize)
		index = (LPTSTR *)realloc(index, ((idxsize += IDX_BLOCK_SIZE) * sizeof(LPTSTR )));

	index[idxoffset] = buf + offset;
	lstrcpy(index[idxoffset], filename);

	offset += length;
	idxoffset++;
	return;
}

void FileList::reset()
{
	offset = idxoffset = 0;
}

LPCTSTR FileList::get(int offset)
{
	return index[offset];
}

size_t FileList::num()
{
	return idxoffset;
}

void FileList::setlist(LPCTSTR filelist)
{
	int length = lstrlen(filelist)*sizeof(TCHAR), num = 1;
	LPCTSTR pfilelist;
	offset = idxoffset = 0;

	if(bufsize < length)
		buf = (LPTSTR )realloc(buf, (bufsize = length));
	lstrcpy(buf, filelist);


	for(pfilelist = filelist; *pfilelist != TEXT('\0'); pfilelist++)
		if(*pfilelist == TEXT('*'))
			num++;

	if(num > idxsize)
		index = (LPTSTR *)realloc(index, (idxsize = num)*sizeof(LPTSTR));

	pfilelist = _tcstok(buf, TEXT("*"));
	if(lstrlen(pfilelist) > 0)
		index[idxoffset++] = (LPTSTR )pfilelist;
	
	while((pfilelist = _tcstok(NULL, TEXT("*"))) != NULL)
		if(lstrlen(pfilelist) > 0)
            index[idxoffset++] = (LPTSTR )pfilelist;

	return;
}

LPCTSTR FileList::getlist()
{
	TCHAR *pbuf, *pbuf2;

	pbuf2 = buf2 = (LPTSTR )realloc(buf2, bufsize);
	for(int i = 0; i < (int)num(); i++){
		pbuf = index[i];
		while(*pbuf != TEXT('\0'))
			*pbuf2++ = *pbuf++;
		*pbuf2++ = TEXT('*');
	}
	if(num() > 0)
		pbuf2[-1] = TEXT('\0');
	else
		pbuf2[0] = TEXT('\0');
	return buf2;
}

void ShowLastError()
{
	TCHAR s[1024];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), NULL, s, sizeof(s), NULL);
	MessageBox(0, s, TEXT("Error"), MB_OK);
	return;
}

ULONGLONG GetFileIndex(LPCTSTR szFileName)
{
	BY_HANDLE_FILE_INFORMATION FileInformation;
	ULARGE_INTEGER uliFileIndex;
	HANDLE hFile;

	hFile = CreateFile(szFileName, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != NULL){
		GetFileInformationByHandle(hFile, &FileInformation);
		CloseHandle(hFile);

		uliFileIndex.HighPart = FileInformation.nFileIndexHigh;
		uliFileIndex.LowPart  = FileInformation.nFileIndexLow;
		return uliFileIndex.QuadPart;
	} else {
		return 0;
	}
}

int getStrLinesSize(LPCTSTR s)
{
	int result = 0;
	while (*s != TEXT('\0')) {
		while (*s != TEXT('\0')) {
			TCHAR c = *s++;
			if(c == TEXT('\n')) break;
		}
		result ++;
	}
	return result;
}

void GetDirName(LPTSTR dirName, LPCTSTR path)
{
	int i = 0;
	int pos = -1;
	while (1) {
		TCHAR c = path[i];
		if (c==TEXT('\0')) break;
		if (c==TEXT('\\') || c==TEXT('/')) pos = i;
#ifndef UNICODE
		i += IsDBCSLeadByte(c) ? 2 : 1;
#else
		i++;
#endif
	}
	memcpy(dirName, path, (pos + 1)*sizeof(TCHAR));
	dirName[pos + 1] = TEXT('\0');
}

#ifdef UNICODE
UINT WinExec(LPCTSTR lpCmdLine, UINT uCmdShow)
{
	STARTUPINFO sui = {
		sizeof(STARTUPINFO),
		NULL,
		NULL,
		NULL,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		STARTF_USESHOWWINDOW,
		uCmdShow,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	};
	PROCESS_INFORMATION pi = {
		NULL,NULL,0,0
	};
	CreateProcess(NULL,(LPTSTR)lpCmdLine,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&sui,&pi);
	return 0;
}
#endif