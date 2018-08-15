/*------------------------------------------------------------------------------
	Executing extension tool routines for HSP Script Editor
------------------------------------------------------------------------------*/

#include <windows.h>
#include <tchar.h>

#include "resource.h"
#include "poppad.h"
#include "exttool.h"
#include "support.h"

extern TCHAR szFileName[_MAX_PATH];

static int nSize;
static EXTTOOLINFO *lpExtToolInfo;
static HMENU hMainMenu, hPopupMenu;
extern HMENU hSubMenu;
extern HWND hwbak;

bool InitExtTool(int nNewSize)
{
//	MENUITEMINFO mii;
	if(nSize < nNewSize){
		lpExtToolInfo = (EXTTOOLINFO *)realloc(lpExtToolInfo, nNewSize * sizeof(EXTTOOLINFO));
		if(lpExtToolInfo == NULL){
			nSize = 0;
			return false;
		} else {
			nSize = nNewSize;
		}
	}
	if(nSize > 0)
		ZeroMemory(lpExtToolInfo, sizeof(EXTTOOLINFO) * nSize);
	return true;
}

void ReleaseExtTool()
{
	free(lpExtToolInfo);

	lpExtToolInfo = NULL;
	nSize = 0;
}

void SetMenuExtTool()
{
	MENUITEMINFO mii;
	int i, j, k;
	bool bNoMainMenuItem, bNoPopupMenuItem;

	if(hMainMenu == NULL)
		hMainMenu = GetSubMenu(GetMenu(hwbak), POS_EXTTOOL);
	if(hPopupMenu == NULL)
		hPopupMenu = hSubMenu;

	while(DeleteMenu(hMainMenu, POS_TOOLMAINBASE, MF_BYPOSITION));
	while(DeleteMenu(hPopupMenu, POS_TOOLPOPUPSEP, MF_BYPOSITION));
	
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask  = MIIM_ID | MIIM_TYPE;

	bNoMainMenuItem = bNoPopupMenuItem = true;
	for(i = 0, j = 0, k = 0; i < nSize; i++){
		if(lpExtToolInfo[i].ShowOnMainMenu){
			if(bNoMainMenuItem)
				bNoMainMenuItem = false;

			mii.fType      = MFT_STRING;
			mii.wID        = IDM_EXTTOOL + i;
			mii.dwTypeData = lpExtToolInfo[i].ToolName;
			InsertMenuItem(hMainMenu, POS_TOOLMAINBASE + j, TRUE, &mii);
			j++;
		}
		if(lpExtToolInfo[i].ShowOnPopupMenu){
			if(bNoPopupMenuItem){
				mii.fType = MFT_SEPARATOR;
				InsertMenuItem(hPopupMenu, POS_TOOLPOPUPSEP, TRUE, &mii);
				bNoPopupMenuItem = false;
			}
			mii.fType      = MFT_STRING;
			mii.wID        = IDM_EXTTOOL + i;
			mii.dwTypeData = lpExtToolInfo[i].ToolName;
			InsertMenuItem(hPopupMenu, POS_TOOLPOPUPBASE + k, TRUE, &mii);
			k++;
		}
	}
	if(bNoMainMenuItem){
		mii.fMask      = MIIM_TYPE | MIIM_STATE;
		mii.fType      = MFT_STRING;
		mii.fState     = MFS_GRAYED;
		mii.wID        = 0;
#ifdef JPNMSG
		mii.dwTypeData = TEXT("�O���c�[���͂���܂���");
#else
		mii.dwTypeData = TEXT("No external tools");
#endif
		InsertMenuItem(hMainMenu, POS_TOOLMAINBASE, TRUE, &mii);
	}
	DrawMenuBar(hwbak);
}

bool AddExtTool(unsigned int nToolID, EXTTOOLINFO *lpAddExtToolInfo)
{
	if(nToolID >= (unsigned int)nSize){
		msgboxf(NULL, TEXT("�ǉ�����c�[��ID���͈͂𒴂��܂����B\n")
			TEXT("���̃G���[�̓o�O�̉\��������܂��B"), TEXT("error"), MB_OK | MB_ICONERROR);
		return false;
	}
	lpExtToolInfo[nToolID] = *lpAddExtToolInfo;
	lpExtToolInfo[nToolID].Used = true;
	return true;
}

bool ExecExtTool(HWND hWnd, unsigned int nToolID, bool bStartup)
{
	int i, j, nLength;
	TCHAR szCmdLine[SIZE_OF_CMDLINE], szCurDir[_MAX_PATH + 1], szWorkDir[_MAX_PATH + 1];
	bool bEscSeq = false;
	HINSTANCE hRet;
	LPCTSTR lpErrMsg[] = {
		TEXT("�������܂��̓��\�[�X���s�����Ă��܂��B"), NULL, TEXT("�w�肳�ꂽ�t�@�C����������܂���ł����B"),
		TEXT("�w�肳�ꂽ�p�X��������܂���ł����B"), NULL,
		TEXT("�I�y���[�e�B���O�V�X�e�����A�w�肳�ꂽ�t�@�C���ւ̃A�N�Z�X�����ۂ��܂����B"),
		NULL, NULL, TEXT("�������������̂ɏ\���ȃ�����������܂���B"), NULL, NULL,
		TEXT(".exe �t�@�C���������ł��BWin32 �� .exe �ł͂Ȃ����A.exe �C���[�W���ɃG���[������܂��B"),
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		TEXT("���L�ᔽ���������܂����B "), TEXT("�t�@�C�����̊֘A�t�����s���S�܂��͖����ł��B"), NULL,
		TEXT("�v�����^�C���A�E�g�����̂ŁADDE �g�����U�N�V�����������ł��܂���ł����B"),
		TEXT("DDE �g�����U�N�V���������s���܂����B"),
		TEXT("�ق��� DDE �g�����U�N�V���������ݏ������Ȃ̂ŁADDE �g�����U�N�V�����������ł��܂���ł����B"),
		TEXT("�w�肳�ꂽ�t�@�C���g���q�Ɋ֘A�t����ꂽ�A�v���P�[�V����������܂���B\n")
		TEXT("����\�ł͂Ȃ��t�@�C����������悤�Ƃ����ꍇ���A���̃G���[���Ԃ�܂��B"),
		TEXT("�w�肳�ꂽ�_�C�i�~�b�N�����N���C�u�����iDLL�j��������܂���ł����B"),
	};

	if(nToolID >= (unsigned int)nSize || lpExtToolInfo[nToolID].Used == false){
		msgboxf(hWnd, TEXT("�c�[��ID���͈͂𒴂��Ă��邽�߁A\"%s\"���J�����Ƃ��ł��܂���ł����B\n")
			TEXT("���̃G���[�̓o�O�̉\�����傫���ł��B"), TEXT("error"), MB_OK | MB_ICONERROR);
		return false;
	}

	nLength = lstrlen(szFileName);
	for(i = 0, j = 0; lpExtToolInfo[nToolID].CmdLine[i] != TEXT('\0') && j + 1 < SIZE_OF_CMDLINE; i++){
		switch(lpExtToolInfo[nToolID].CmdLine[i]){
			case TEXT('%'):
				if(bEscSeq)
					szCmdLine[j++] = TEXT('%');
				else
					bEscSeq = true;
				break;

			case TEXT('f'): case TEXT('F'):
				if(bEscSeq){
					strlcpy(szCmdLine + j, szFileName, SIZE_OF_CMDLINE - j);
					j += nLength;
					bEscSeq = false;
					break;
				}

			case TEXT('d'): case TEXT('D'):
				if(bEscSeq){
					GetCurrentDirectory(sizeof(szCurDir), szCurDir);
					strlcpy(szCmdLine + j, szCurDir, SIZE_OF_CMDLINE - j);
					j += lstrlen(szCurDir);
					bEscSeq = false;
					break;
				}

			default:
				if(bEscSeq){
					szCmdLine[j++] = TEXT('%');
					bEscSeq = false;
				}
				szCmdLine[j++] = lpExtToolInfo[nToolID].CmdLine[i];
				break;
		}
	}
	if(j + 1 >= SIZE_OF_CMDLINE){
		msgboxf(hWnd, TEXT("�R�}���h���C�����������邽�߁A\"%s\"���J�����Ƃ��ł��܂���ł����B"), 
			TEXT("error"), MB_OK | MB_ICONERROR, lpExtToolInfo->ToolName);
		return false;
	}
	szCmdLine[j] = TEXT('\0');

	bEscSeq = false;
	for(i = 0, j = 0; lpExtToolInfo[nToolID].WorkDir[i] != TEXT('\0') && j + 1 < MAX_PATH + 1; i++){
		switch(lpExtToolInfo[nToolID].WorkDir[i]){
			case TEXT('%'):
				if(bEscSeq)
					szWorkDir[j++] = TEXT('%');
				else
					bEscSeq = true;
				break;

			case TEXT('f'): case TEXT('F'):
				if(bEscSeq){
					TCHAR *pLastDirSep = _tcsrchr(szFileName, TEXT('\\'));
					nLength = pLastDirSep ? (int)(pLastDirSep - szFileName) : lstrlen(szFileName);
					strlcpy(szWorkDir + j, szFileName, min(MAX_PATH + 1 - j, nLength + 1));
					j += nLength;
					bEscSeq = false;
					break;
				}

			case TEXT('d'): case TEXT('D'):
				if(bEscSeq){
					GetCurrentDirectory(sizeof(szCurDir), szCurDir);
					strlcpy(szWorkDir + j, szCurDir, MAX_PATH + 1 - j);
					j += lstrlen(szCurDir);
					bEscSeq = false;
					break;
				}

			default:
				if(bEscSeq){
					szWorkDir[j++] = TEXT('%');
					bEscSeq = false;
				}
				szWorkDir[j++] = lpExtToolInfo[nToolID].WorkDir[i];
				break;
		}
	}
	szWorkDir[j] = TEXT('\0');

	if(lpExtToolInfo[nToolID].ExecWithOverwrite && !bStartup)
		SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_SAVE, 0), NULL);

	hRet = ShellExecute(hWnd, NULL, lpExtToolInfo[nToolID].FileName, szCmdLine, szWorkDir,
		SW_SHOWNORMAL);
	if((int)hRet <= 32){
		msgboxf(hWnd, TEXT("�O���c�[���̋N���Ɏ��s���܂����B\n���s�����͉��L�̒ʂ�ł��B\n\n%s"),
			TEXT("error"), MB_OK | MB_ICONERROR, lpErrMsg[(int)hRet] != NULL ? lpErrMsg[(int)hRet] : TEXT("���m�̃G���[�ł��B"));
		return false;
	}

	return true;
}

void ExecStartupTools(HWND hWnd)
{
	int i;

	for(i = 0; i < nSize; i++)
		if(lpExtToolInfo[i].ExecOnStartup)
			ExecExtTool(hWnd, i, true);
}

int GetExtToolSize()
{
	return nSize;
}

EXTTOOLINFO *GetExtTool(unsigned int nToolID)
{
	if(nToolID >= (unsigned int)nSize) return NULL;
	return lpExtToolInfo + nToolID;
}
