/*------------------------------------------------------------------------------
	カスタム設定ファイル読み込み for HSP Script Editor by inovia
	作成 2012.06.21
	修正 2012.06.21
------------------------------------------------------------------------------*/

// ↓いらないのがあるかも
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Footy2.h"
#include "hsed_config.h"
#include "poppad.h"
#include "config.h"
#include "classify.h"
#include "support.h"
#include "exttool.h"
#include <tchar.h>

#include "CustomConfig.h"
#include "PackIconResource.h"

// PathFileExistsで使用
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#pragma warning( disable : 4996 )
#pragma warning( disable : 4006 )

// フルパスゲット
void GetINIFullPath(LPTSTR inipath){
	GetModuleFileName(0, inipath, _MAX_PATH);
	PathRemoveFileSpec(inipath);	// ディレクトリのみにする
	_tcscat(inipath, TEXT("\\custom.ini"));
}

// 設定が増えそうなので汎用的に使えるように変更
void SetINICustomInt(int f, LPTSTR s){
	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	_stprintf(tmp,TEXT("%d"),f);
	WritePrivateProfileString(TEXT("HSED3"), s, tmp, inipath);
}

void SetINICustomBOOL(BOOL f, LPTSTR s){
	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	if (f == TRUE){
		_stprintf(tmp, TEXT("1"));
	}else{
		_stprintf(tmp, TEXT("0"));
	}
	WritePrivateProfileString(TEXT("HSED3"), s, tmp, inipath);
}

void SetINICustomString(LPTSTR key, LPTSTR value){
	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	WritePrivateProfileString(TEXT("HSED3"), key, value, inipath);
}

int GetINICustomInt(LPTSTR s){

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// パスがない場合は設定を0にして返却
	if (!_PathFileExists(inipath))
		return 0;

	// INIファイル読み込み(失敗したときは0)
	return GetPrivateProfileInt(TEXT("HSED3"), s, 0, inipath);
}

// あらかじめ呼び出し元でバッファの確保&0埋めが必要
DWORD GetINICustomString(LPTSTR key, LPTSTR value, int maxLength){

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// パスがない場合は0にして返却
	if (!_PathFileExists(inipath))
		return 0;

	// INIファイル読み込み(失敗したときは0)
	return GetPrivateProfileString(TEXT("HSED3"), key, TEXT(""), value, (DWORD)maxLength, inipath);
}

BOOL GetINICustomBOOL(LPTSTR s){

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// パスがない場合は設定を0にして返却
	if (!_PathFileExists(inipath))
		return FALSE;

	// INIファイル読み込み(失敗したときは0)
	return GetPrivateProfileInt(TEXT("HSED3"), s, FALSE, inipath);
}

// ↑変更

void SetINIForceFont(BOOL f){
	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	if (f == TRUE){
		_stprintf(tmp, TEXT("1"));
	}else{
		_stprintf(tmp, TEXT("0"));
	}
	WritePrivateProfileString(TEXT("HSED3"), TEXT("ForceFont"), tmp, inipath);
}


void SetINICustomColor(int f){
	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	_stprintf(tmp,TEXT("%d"),f);
	WritePrivateProfileString(TEXT("HSED3"), TEXT("CustomColor"), tmp, inipath);
}

// INIファイルのフォント強制設定を読み込む
int GetINIForceFont(void){

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// パスがない場合は設定を0にして返却
	if (!_PathFileExists(inipath))
		return 0;

	// INIファイル読み込み(失敗したときは0)
	return GetPrivateProfileInt(TEXT("HSED3"), TEXT("ForceFont"), 0, inipath);
}

// INIファイルのカスタムカラー設定を読み込む
BOOL GetINICustomColor(void){

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// パスがない場合は設定を0にして返却
	if (!_PathFileExists(inipath))
		return FALSE;

	// INIファイル読み込み(失敗したときは0)
	return GetPrivateProfileInt(TEXT("HSED3"), TEXT("CustomColor"), FALSE, inipath);
}

