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
		mii.dwTypeData = TEXT("外部ツールはありません");
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
		msgboxf(NULL, TEXT("追加するツールIDが範囲を超えました。\n")
			TEXT("このエラーはバグの可能性があります。"), TEXT("error"), MB_OK | MB_ICONERROR);
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
		TEXT("メモリまたはリソースが不足しています。"), NULL, TEXT("指定されたファイルが見つかりませんでした。"),
		TEXT("指定されたパスが見つかりませんでした。"), NULL,
		TEXT("オペレーティングシステムが、指定されたファイルへのアクセスを拒否しました。"),
		NULL, NULL, TEXT("操作を完了するのに十分なメモリがありません。"), NULL, NULL,
		TEXT(".exe ファイルが無効です。Win32 の .exe ではないか、.exe イメージ内にエラーがあります。"),
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
		TEXT("共有違反が発生しました。 "), TEXT("ファイル名の関連付けが不完全または無効です。"), NULL,
		TEXT("要求がタイムアウトしたので、DDE トランザクションを完了できませんでした。"),
		TEXT("DDE トランザクションが失敗しました。"),
		TEXT("ほかの DDE トランザクションが現在処理中なので、DDE トランザクションを完了できませんでした。"),
		TEXT("指定されたファイル拡張子に関連付けられたアプリケーションがありません。\n")
		TEXT("印刷可能ではないファイルを印刷しようとした場合も、このエラーが返ります。"),
		TEXT("指定されたダイナミックリンクライブラリ（DLL）が見つかりませんでした。"),
	};

	if(nToolID >= (unsigned int)nSize || lpExtToolInfo[nToolID].Used == false){
		msgboxf(hWnd, TEXT("ツールIDが範囲を超えているため、\"%s\"を開くことができませんでした。\n")
			TEXT("このエラーはバグの可能性が大きいです。"), TEXT("error"), MB_OK | MB_ICONERROR);
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
		msgboxf(hWnd, TEXT("コマンドラインが長すぎるため、\"%s\"を開くことができませんでした。"), 
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
		msgboxf(hWnd, TEXT("外部ツールの起動に失敗しました。\n失敗原因は下記の通りです。\n\n%s"),
			TEXT("error"), MB_OK | MB_ICONERROR, lpErrMsg[(int)hRet] != NULL ? lpErrMsg[(int)hRet] : TEXT("未知のエラーです。"));
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
