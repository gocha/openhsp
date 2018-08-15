/*------------------------------------------------------------------------------
	�A�C�R���ƃ��\�[�X���ߍ��� for HSP Script Editor by inovia
	�쐬 2012.02.24
	�C�� 2012.04.08
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

#include "PackIconResource.h"
#include "CustomColorKeywords.h"

// PathFileExists�Ŏg�p
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#pragma warning( disable : 4996 )
#pragma warning( disable : 4006 )

void RunIconChange(int activeFootyID){
	/* inovia */
	TCHAR fpath[1024+1] = {0};	// EXE
	TCHAR ipath[1024+1] = {0};	// ico
	TCHAR rpath[1024+1] = {0};	// �o�[�W�������\�[�X
	TCHAR mpath[1024+1] = {0};	// manifest by Tetr@pod
	TCHAR extension[1024+1] = {0};	// �g���q�i�I�v�V�����j
	int upx = 0;	// UPX�i�I�v�V�����j
	int lang = -1;	// ����ID�i�I�v�V�����j
	TCHAR cmd[8192+1] = {0};	// �R�}���h���C��

	GetIconResourcePath(fpath, ipath, rpath, mpath/*manifest by Tetr@pod*/, activeFootyID, &upx, &lang, extension);

	// #packopt name "hogehoge" ���Ȃ��ꍇ
	if (_tcscmp(fpath, TEXT("")) == 0){
		_tcscpy(fpath, TEXT("hsptmp"));
	}

	// EXE(hsed3.exe)�̂���f�B���N�g��
	TCHAR exepath[_MAX_PATH+1];
	GetModuleFileName(0, exepath, _MAX_PATH);
	_PathRemoveFileSpec(exepath);	// �f�B���N�g���݂̂ɂ���
	_tcscat(exepath, TEXT("\\iconins.exe"));

	// �X�N���v�g�\�[�X�̃t�H���_(*.hsp)
	TCHAR tmpfn[_MAX_PATH+1] = {0};
	GetCurrentDirectory( _MAX_PATH, tmpfn );

	// ���R�}���h���C���ɓn��������������Ă���
	_tcscat(cmd, TEXT("-e\""));
	_tcscat(cmd, tmpfn);
	_tcscat(cmd, TEXT("\\"));
	_tcscat(cmd, fpath);
	// �g���q��ύX����I�v�V�����i�w��Ȃ��̏ꍇ��.exe�j
	if (_tcscmp(extension, TEXT("")) == 0){
		_tcscat(cmd, TEXT(".exe\""));
	}else{
		_tcscat(cmd, extension);
		_tcscat(cmd, TEXT("\""));
	}
	// �A�C�R���p�X
	if (_tcscmp(ipath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -i\""));
		_tcscat(cmd, ipath);
		_tcscat(cmd, TEXT("\""));
	}
	// ���\�[�X�i�o�[�W�����j�p�X
	if (_tcscmp(rpath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -v\""));
		_tcscat(cmd, rpath);
		_tcscat(cmd, TEXT("\""));
	}
	// ���\�[�X�imanifest�j�p�X by Tetr@pod
	if (_tcscmp(mpath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -m\""));
		_tcscat(cmd, mpath);
		_tcscat(cmd, TEXT("\""));
	}

	
	if (upx == 1){
		// UPX���g���ꍇ
		_tcscat(cmd, TEXT(" -u\"1\""));
	}
	if (lang != -1){
		// ����ID
		TCHAR tmp[1024+1] = {0};
		_stprintf(tmp, TEXT(" -l\"%d\""), lang);
		_tcscat(cmd, tmp);
	}
	//ShellExecute( NULL, "explore", tmpfn, NULL, NULL, SW_SHOWNORMAL );

	// �ǂ��炩�Ƀp�X�������Ă���ꍇ�͎��s����
	if ((_tcscmp(ipath, TEXT("")))||(_tcscmp(rpath, TEXT("")))||(upx == 1)){
		if (_PathFileExists(exepath)){
			//char runpath[4096+1];memset( fpath, '\0', sizeof(runpath) );	// �p�X
			//memset( runpath, '\0', sizeof(runpath) );
			//sprintf( runpath, "\"%s\" %s", exepath, cmd );
			//WinExec( runpath, SW_SHOW );
			
			// �I���܂őҋ@�������̂ł�������g�p
			SHELLEXECUTEINFO sei = {sizeof(sei)};
			sei.cbSize = sizeof(SHELLEXECUTEINFO);
			sei.hwnd = 0;
			sei.nShow = SW_SHOWNORMAL;
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;
			sei.lpFile = exepath;
			sei.lpParameters = cmd;
			ShellExecuteEx(&sei);
			// �I���҂�
			WaitForSingleObject(sei.hProcess, INFINITE) ;
			
		}else{
			//
			MessageBox(GetActiveWindow(), TEXT("iconins.exe ��������܂���B�A�C�R���̖��ߍ��݂͎��s���܂����B"), TEXT("�G���["), MB_OK | MB_ICONERROR);
		}
	}
	/* inovia */
}

BOOL _PathFileExists(LPCTSTR pszPath)
{
	return PathFileExists(pszPath);
}

BOOL _PathRemoveFileSpec(LPTSTR pszPath)
{
	return PathRemoveFileSpec(pszPath);
}

// ���C���X�N���v�g����p�X������
int GetIconResourcePath(LPTSTR exepath, LPTSTR iconpath, LPTSTR respath, LPTSTR manifestpath/*manifest by Tetr@pod*/, int _activeFootyID, int *upx, int *lang, LPTSTR extension){
	
	LPTSTR buffer,dummy;
	LPCTSTR cbuffer;
	// Footy2����P�s���擾
	int lines = Footy2GetLines(_activeFootyID);
	if (lines == FOOTY2ERR_NOID) return 0;	// ����ID��������Ȃ��ꍇ�͂��̂܂܃��^�[��
	int i = 0;
	int flag2 = 0;
	// �S�s���ׂ�
	for (i = 0;i <= lines; i++){
		// �P�s�̃T�C�Y���擾
		int linesize = Footy2GetLineLength(_activeFootyID, i);
		// ��肪�������ꍇ�͒��~
		if ( (linesize == FOOTY2ERR_ARGUMENT) || (linesize == FOOTY2ERR_NOID) ) break;
		// �P�s�̕�������0�̏ꍇ�i��s�̎��ɎQ�Ƃ���Ɨ�����j
		if (linesize == 0) continue;
		// ���I�m��
		buffer = (LPTSTR) calloc( linesize * 2 + 2 , sizeof(TCHAR) );
#ifndef UNICODE
		// �P�s�擾(Footy2GetLineA�̃}�j���A���̈������Ԉ���Ă���̂Œ���)
		int res = Footy2GetLine(_activeFootyID, buffer, i, linesize * 2);
#else
		cbuffer = Footy2GetLine(_activeFootyID, i);
		int res = FOOTY2ERR_NONE;
#endif
		// ���������Ă��܂��ق��̃o�b�t�@�[��buffer����dummy�փR�s�[
		dummy = (LPTSTR) calloc( linesize * 2 + 2 , sizeof(TCHAR) );
#ifndef UNICODE
		memcpy(dummy, buffer, linesize * 2);
#else
		memcpy(dummy, cbuffer, linesize * 2);
		memcpy(buffer, cbuffer, linesize * 2);
#endif
	
		// ��肪�������ꍇ�͒��~
		if ( (res == FOOTY2ERR_ARGUMENT) || (res == FOOTY2ERR_NOID) ){
			free(dummy);dummy = 0;
#ifndef UNICODE
			free(buffer);buffer = 0;
#endif
			break;
		}
		
		// dummy����^�u�Ƌ󔒂���菜��
		/*
			0 #pack
			1 #packopt
			2  #packopt
			3 // #packopt 0 

			�̂悤�ȏꍇ�A#packopt �̑O�ɃX�y�[�X��^�u�������Ă��Ă����삷��悤�ɂ��邽��
		*/
		StrReplaceALL(dummy, TEXT("\t"), TEXT(""));
		StrReplaceALL(dummy, TEXT(" "), TEXT(""));

		// #packopt �����邩���ׂ�
		LPTSTR pos = _tcsstr(dummy, TEXT("#packopt"));
		if ((pos != NULL) && (pos-dummy == 0)){
			/*
			char test[128];
			sprintf(test,"%d",pos-dummy);
			MessageBoxA(0,test,"",0);
			*/
			// �^�u���󔒂ɕϊ�����(����)
			StrReplaceALL(buffer, TEXT("\t"), TEXT(" "));
			
			// �{���� #packopt �����ׂ�B
			// #packopt2 �Ƃ� #packopts �Ȃǂ̃P�[�X�ɑΉ�
			int splits = GetSplitNum(buffer, TEXT(" "));
			int flag = 0;	// ��v�����ꍇ�̃t���O
			// �������������ׂ�
			int j;
			for (j = 0;j <= splits; j++){
				// �m��
				LPTSTR tmp = (LPTSTR)calloc(linesize * 2 + 2, sizeof(TCHAR));
				// �X�y�[�X�ŕ����������ʂ�tmp�ɑ��
				GetSplitString(buffer, TEXT(" "), j, tmp);
				// ��v�����ꍇ�̓t���O�𗧂Ă�
				if (_tcscmp(tmp, TEXT("#packopt")) == 0) flag = 1;
				// ���
				free(tmp);tmp = 0;
			}
			// #packopt����v�����ꍇ�̂ݑ��s
			if (flag == 1){
				// �L�[���[�h���擾�Ƃ�������r���ăt���O�𗧂Ă�
				// #packopt name "test"
				//           �� �R��
				splits = GetSplitNum(buffer, TEXT(" "));
				int j;
				for (j = 0;j <= splits; j++){
					// �m��
					LPTSTR tmp = (LPTSTR)calloc(linesize * 2 + 2, sizeof(TCHAR));
					// �X�y�[�X�ŕ����������ʂ�tmp�ɑ��
					GetSplitString(buffer, TEXT(" "), j, tmp);
					// ��v�����ꍇ�̓t���O�𗧂Ă�
					if (_tcscmp(tmp, TEXT("name")) == 0){
						//MessageBoxA(0,tmp,tmp,0);
						flag2 = 1;
					}
					if (_tcscmp(tmp, TEXT("icon")) == 0) flag2 = 2;
					if (_tcscmp(tmp, TEXT("version")) == 0) flag2 = 3;
					if (_tcscmp(tmp, TEXT("upx")) == 0) flag2 = 4;
					if (_tcscmp(tmp, TEXT("lang")) == 0) flag2 = 5;
					if (_tcscmp(tmp, TEXT("ext")) == 0) flag2 = 6;
					if (_tcscmp(tmp, TEXT("last")) == 0) flag2 = 7;
					if (_tcscmp(tmp, TEXT("manifest")) == 0) flag2 = 8;// manifest by Tetr@pod
					// ���
					free(tmp);tmp = 0;
				}
				// �� #packopt name "hogehoge" �̂������̊ԁi�͈́j���擾
				LPCTSTR sp, ep;
				LPTSTR outpath = (LPTSTR)calloc(linesize * 2 + 2, sizeof(TCHAR));
				sp = _tcsstr(buffer, TEXT("\""));
				if (sp != NULL){
					ep = _tcsstr(sp+1, TEXT("\""));
					if (ep != NULL){
						_tcsncpy(outpath, sp+1, ep-sp-1);
						//MessageBox(0,outpath,"",0);
					}
				}

				// �����񂪒�������ꍇ�̓G���[������������
				if (_tcslen(outpath) > 512){
					_tcscpy(outpath, TEXT("::ERROR::"));
				}

				// ��������
				switch (flag2) {
					case 1 : 
						// name
						_tcscpy(exepath, outpath);
						
						//MessageBoxA(0,exepath,exepath,0);
						break;
					case 2 : 
						// icon
						_tcscpy(iconpath, outpath);
						break;
					case 3 : 
						// version
						_tcscpy(respath, outpath);
						break;
					case 4 : 
						// upx
						TCHAR use_upx[1024+1];memset( use_upx, TEXT('\0'), sizeof(use_upx) );
						_tcscpy(use_upx, outpath);
						*upx = _ttoi(use_upx);
						break;
					case 5 : 
						// lang(����ID)
						TCHAR langid[1024+1];memset( langid, TEXT('\0'), sizeof(langid) );
						_tcscpy(langid, outpath);
						*lang = _ttoi(langid);
						break;
					case 6 : 
						// extension(�g���q)
						_tcscpy(extension, outpath);
						break;
					case 8 : 
						// manifest by Tetr@pod
						_tcscpy(manifestpath, outpath);
						break;
					default : 
						// ����ȊO�B�������Ȃ��B
						break;
				}
				// ���
				free(outpath);outpath = 0;flag2 = 0;

			}

		}

		// �K�����
		free(dummy);dummy = 0;
#ifndef UNICODE
		free(buffer);buffer = 0;
#endif

		// 7 �̏ꍇ�������E
		if (flag2 == 7)
			break;
	} 
	return 0;
}

// �P�̂ݒu������
int StrReplace(LPTSTR buf, LPTSTR mae, LPTSTR ato)
{
    LPTSTR pos;
    size_t maelen, atolen;
    
    maelen = _tcslen(mae);
    atolen = _tcslen(ato);
    if (maelen == 0 || (pos = _tcsstr(buf, mae)) == 0) return 0;
    memmove(pos + atolen, pos + maelen, _tcslen(buf) - (pos + maelen - buf ) + 1);
    memcpy(pos, ato, atolen);
    return 1;
}

// �Ώە���������ׂĒu������
int StrReplaceALL(LPTSTR buf, LPTSTR mae, LPTSTR ato)
{
	int i = 0;
	while (StrReplace(buf, mae, ato)){
		i++;
	}
	return i;
}

