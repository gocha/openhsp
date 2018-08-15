/*------------------------------------------------------------------------------
	�J�X�^���ݒ�t�@�C���ǂݍ��� for HSP Script Editor by inovia
	�쐬 2012.06.21
	�C�� 2012.06.21
------------------------------------------------------------------------------*/

// ������Ȃ��̂����邩��
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

// PathFileExists�Ŏg�p
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#pragma warning( disable : 4996 )
#pragma warning( disable : 4006 )

// �t���p�X�Q�b�g
void GetINIFullPath(LPTSTR inipath){
	GetModuleFileName(0, inipath, _MAX_PATH);
	PathRemoveFileSpec(inipath);	// �f�B���N�g���݂̂ɂ���
	_tcscat(inipath, TEXT("\\custom.ini"));
}

// �ݒ肪���������Ȃ̂Ŕėp�I�Ɏg����悤�ɕύX
void SetINICustomInt(int f, LPTSTR s){
	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	_stprintf(tmp,TEXT("%d"),f);
	WritePrivateProfileString(TEXT("HSED3"), s, tmp, inipath);
}

void SetINICustomBOOL(BOOL f, LPTSTR s){
	// EXE(hsed3.exe)�̂���f�B���N�g��
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
	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	WritePrivateProfileString(TEXT("HSED3"), key, value, inipath);
}

int GetINICustomInt(LPTSTR s){

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// �p�X���Ȃ��ꍇ�͐ݒ��0�ɂ��ĕԋp
	if (!_PathFileExists(inipath))
		return 0;

	// INI�t�@�C���ǂݍ���(���s�����Ƃ���0)
	return GetPrivateProfileInt(TEXT("HSED3"), s, 0, inipath);
}

// ���炩���ߌĂяo�����Ńo�b�t�@�̊m��&0���߂��K�v
DWORD GetINICustomString(LPTSTR key, LPTSTR value, int maxLength){

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// �p�X���Ȃ��ꍇ��0�ɂ��ĕԋp
	if (!_PathFileExists(inipath))
		return 0;

	// INI�t�@�C���ǂݍ���(���s�����Ƃ���0)
	return GetPrivateProfileString(TEXT("HSED3"), key, TEXT(""), value, (DWORD)maxLength, inipath);
}

BOOL GetINICustomBOOL(LPTSTR s){

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// �p�X���Ȃ��ꍇ�͐ݒ��0�ɂ��ĕԋp
	if (!_PathFileExists(inipath))
		return FALSE;

	// INI�t�@�C���ǂݍ���(���s�����Ƃ���0)
	return GetPrivateProfileInt(TEXT("HSED3"), s, FALSE, inipath);
}

// ���ύX

void SetINIForceFont(BOOL f){
	// EXE(hsed3.exe)�̂���f�B���N�g��
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
	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	TCHAR tmp[64];
	_stprintf(tmp,TEXT("%d"),f);
	WritePrivateProfileString(TEXT("HSED3"), TEXT("CustomColor"), tmp, inipath);
}

// INI�t�@�C���̃t�H���g�����ݒ��ǂݍ���
int GetINIForceFont(void){

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// �p�X���Ȃ��ꍇ�͐ݒ��0�ɂ��ĕԋp
	if (!_PathFileExists(inipath))
		return 0;

	// INI�t�@�C���ǂݍ���(���s�����Ƃ���0)
	return GetPrivateProfileInt(TEXT("HSED3"), TEXT("ForceFont"), 0, inipath);
}

// INI�t�@�C���̃J�X�^���J���[�ݒ��ǂݍ���
BOOL GetINICustomColor(void){

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR inipath[_MAX_PATH+1];
	GetINIFullPath(inipath);

	// �p�X���Ȃ��ꍇ�͐ݒ��0�ɂ��ĕԋp
	if (!_PathFileExists(inipath))
		return FALSE;

	// INI�t�@�C���ǂݍ���(���s�����Ƃ���0)
	return GetPrivateProfileInt(TEXT("HSED3"), TEXT("CustomColor"), FALSE, inipath);
}

