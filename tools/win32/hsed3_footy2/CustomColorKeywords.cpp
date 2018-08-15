/*------------------------------------------------------------------------------
	�F��`�ǉ� for HSP Script Editor by inovia
	�쐬 2011.12.20
	�C�� 2011.12.26
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

// PathIsDirectory�Ŏg�p
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#include "CustomColorKeywords.h"

#pragma warning( disable : 4996 )

extern BOOL bCustomColor;

extern BOOL CustomMatchCase;// by Tetr@pod


// classify.cpp	�� SetClassify()����Ăяo����܂�
void SetCumtomColorKeywords(int FootyID, MYCOLOR color)
{
	// �ݒ�t�@�C���Ŏg�p���Ȃ��ݒ�̏ꍇ�͐F�t�����Ȃ�
	if (bCustomColor == FALSE)
		return;
	// �F��`(�f�t�H�̐F)
	int FuncColor = RGB(  0, 255, 255);
	int OwnFuncColor = RGB(  0, 255, 255);
	int CFuncColor = RGB(  0, 255, 255);
	int OwnCFuncColor = RGB(  0, 255, 255);
	int Win32APIFuncColor = RGB(  0, 255, 255);
	int Win32APICFuncColor = RGB(  0, 255, 255);
	int MacroColor = RGB(192, 255, 255);
	int SysVarColor = RGB(  0, 255, 255);
	/*int FuncParam = EMP_IND_BLANKS;
	int CFuncParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS; 
	int VarParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS | EMP_IND_OTHER_ASCII_SIGN;*/
	// �召��r�L���AOR�L���A���Z�q�Aif��{}�A���Z�q��() �Ȃǂ����� by Tetr@pod
	int FuncParam = EMP_IND_BLANKS | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_ANGLE_BRACKET | EMP_IND_PARENTHESIS;
	int CFuncParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_ANGLE_BRACKET; 
	int VarParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_ANGLE_BRACKET;

	// �G�f�B�^����ݒ�ǂݏo��
	FuncColor = color.Character.Function.Conf;
	CFuncColor = color.Character.Function.Conf;
	OwnFuncColor = color.Character.Function.Conf;
	OwnCFuncColor = color.Character.Function.Conf;
	Win32APIFuncColor = color.Character.Function.Conf;
	Win32APICFuncColor = color.Character.Function.Conf;
	SysVarColor = color.Character.Function.Conf;
	MacroColor = color.Character.Macro.Conf;

	// EXE�̂���f�B���N�g��
	TCHAR exepath[MAX_PATH+1];
	GetModuleFileName(0, exepath, MAX_PATH);
	PathRemoveFileSpec(exepath);

	// �J�X�^���F��`�t�@�C���ǂݍ���
	TCHAR cumtompath[MAX_PATH+1];
	_tcscpy(cumtompath, exepath);
	_tcscat(cumtompath, TEXT("\\keywords\\color.ini"));

	FILE *fpini = _tfopen(cumtompath,TEXT("r"));
	if (fpini != NULL){
		TCHAR tmp[1024+1];
		while ((_fgetts(tmp, 1024, fpini)) != NULL) {
			// ���s�R�[�h�������ꍇ
			if (tmp[_tcslen(tmp)-1] == 0x0A){
				tmp[_tcslen(tmp)-1] = TEXT('\0');	// �]�v�ȉ��s�R�[�h��NULL�Ŗ��߂č폜
			}
			// ���������Q�̏ꍇ
			if (GetSplitNum(tmp, TEXT(" ")) == 2){
				LPTSTR p = (LPTSTR)calloc(1024+1, sizeof(char));
				LPTSTR c = (LPTSTR)calloc(1024+1, sizeof(char));
				GetSplitString(tmp, TEXT(" "), 0, p); // �X�y�[�X�ŕ������ĂO�Ԗڂ̗v�f���擾
				GetSplitString(tmp, TEXT(" "), 1, c);	// �X�y�[�X�ŕ������ĂP�Ԗڂ̗v�f���擾
				// �L�[���[�h�`�F�b�N
				if (_tcscmp(p,TEXT("FUNC")) == 0){
					FuncColor = _ttoi(c);
				}else if(_tcscmp(p,TEXT("OWNFUNC")) == 0){
					OwnFuncColor = _ttoi(c);
				}else if (_tcscmp(p,TEXT("CFUNC")) == 0){
					CFuncColor = _ttoi(c);
				}else if(_tcscmp(p,TEXT("OWNCFUNC")) == 0){
					OwnCFuncColor = _ttoi(c);
				}else if(_tcscmp(p,TEXT("MACRO")) == 0){
					MacroColor = _ttoi(c);
				}else if(_tcscmp(p,TEXT("SYSVAR")) == 0){
					SysVarColor = _ttoi(c);
				}else if((_tcscmp(p,TEXT("W32APIFUNC")) == 0) || (_tcscmp(p,TEXT("WIN32APIFUNC")) == 0)){
					Win32APIFuncColor = _ttoi(c);
				}else if((_tcscmp(p,TEXT("W32APICFUNC")) == 0) || (_tcscmp(p,TEXT("WIN32APICFUNC")) == 0)){
					Win32APICFuncColor = _ttoi(c);
				}
				free(p);
				free(c);
			}
		}
		fclose(fpini);
	}


	// �L�[���[�h�t�H���_���`�F�b�N
	TCHAR crDir[MAX_PATH + 1];
	//GetCurrentDirectoryA(MAX_PATH+1, crDir);
	//strcat(crDir, "\\keywords\\");
	_tcscpy(crDir, exepath);
	_tcscat(crDir, TEXT("\\keywords\\"));

	// �L�[���[�h�t�H���_�����݂��Ă��邩�ǂ���
	if (PathIsDirectory(crDir)){
		// ����ꍇ(�Ō��\\�����Ă��邱��)
		// �t�H���_���̃t�@�C���̐����擾
		int fnum = GetFileListNum(crDir);
		// (MAX_PATH�{2)�~fnum bytes���̗̈���m��(���s�R�[�h���܂�)
		LPTSTR flist = (LPTSTR)calloc(fnum*(MAX_PATH+2)+1,sizeof(TCHAR));
		// �t�@�C���̈ꗗ���擾(\n�ŕ�����ꂽ�`��)
		GetFileList(crDir, flist);
		// �t�@�C���̐������J��Ԃ�
		int i = 0;
		for(i = 0; i<GetSplitNum(flist, TEXT("\n")); i++){
			// �t�@�C�������i�[����ϐ����m��
			LPTSTR fname = (LPTSTR)calloc(MAX_PATH+1, sizeof(TCHAR));
			_tcscpy(fname, exepath);
			_tcscat(fname, TEXT("\\keywords\\"));// �t�H���_�����ɕt��
			// �t�@�C�������擾����
			GetSplitString(flist, TEXT("\n"), i, fname);
			// �t�@�C�����I�[�v������
			FILE *fp = _tfopen(fname,TEXT("r"));
			if (fp != NULL){
				// 1�s���̃f�[�^�ۑ��p�i����Ȃɂ���Ȃ��Ǝv�����ǁj
				LPTSTR line = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
				// 1�s���ǂݎ��
				while ((_fgetts(line, 1024, fp)) != NULL) {
					// ���s�R�[�h�������ꍇ
					if (line[_tcslen(line)-1] == 0x0A){
						line[_tcslen(line)-1] = TEXT('\0');	// �]�v�ȉ��s�R�[�h�폜
					}
					// ���������R�̏ꍇ�͏�������
					if (GetSplitNum(line, TEXT(" ")) == 3){
						int footy2col = 0;
						int footy2flg = 0;
						LPTSTR param = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
						LPTSTR flg = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
						LPTSTR col = (LPTSTR)calloc(1024+1, sizeof(TCHAR));

						GetSplitString(line, TEXT(" "), 0, param);
						GetSplitString(line, TEXT(" "), 1, flg);
						GetSplitString(line, TEXT(" "), 2, col);

						// �F�̃L�[���[�h�`�F�b�N
						if (_tcscmp(col,TEXT("FUNC")) == 0){
							footy2col = FuncColor;
						}else if(_tcscmp(col,TEXT("OWNFUNC")) == 0){
							footy2col = OwnFuncColor;
						}else if (_tcscmp(col,TEXT("CFUNC")) == 0){
							footy2col = CFuncColor;
						}else if(_tcscmp(col,TEXT("OWNCFUNC")) == 0){
							footy2col = OwnCFuncColor;
						}else if(_tcscmp(col,TEXT("MACRO")) == 0){
							footy2col = MacroColor;
						}else if(_tcscmp(col,TEXT("SYSVAR")) == 0){
							footy2col = SysVarColor;
						}else if((_tcscmp(col,TEXT("W32APIFUNC")) == 0) || (_tcscmp(col,TEXT("WIN32APIFUNC")) == 0)){
							footy2col = Win32APIFuncColor;
						}else if((_tcscmp(col,TEXT("W32APICFUNC")) == 0) || (_tcscmp(col,TEXT("WIN32APICFUNC")) == 0)){
							footy2col = Win32APICFuncColor;
						}else{
							// ����ȊO�̏ꍇ�͐��l�Ƃ݂Ȃ��B
							int customcolor = _ttoi(col);
							footy2col = customcolor;
						}
						// �Ɨ����̐ݒ�
						if (_tcscmp(flg,TEXT("FUNC")) == 0){
							footy2flg = FuncParam;
						}else if(_tcscmp(flg,TEXT("OWNFUNC")) == 0){
							footy2flg = FuncParam;
						}else if (_tcscmp(flg,TEXT("CFUNC")) == 0){
							footy2flg = CFuncParam;
						}else if(_tcscmp(flg,TEXT("OWNCFUNC")) == 0){
							footy2flg = CFuncParam;
						}else if(_tcscmp(flg,TEXT("MACRO")) == 0){
							footy2flg = VarParam;
						}else if((_tcscmp(flg,TEXT("W32APIFUNC")) == 0) || (_tcscmp(flg,TEXT("WIN32APIFUNC")) == 0)){
							footy2flg = FuncParam;
						}else if((_tcscmp(flg,TEXT("W32APICFUNC")) == 0) || (_tcscmp(flg,TEXT("WIN32APICFUNC")) == 0)){
							footy2flg = CFuncParam;
						}else if(_tcscmp(flg,TEXT("SYSVAR")) == 0){
							footy2flg = VarParam;
						}else{
							// ����ȊO�̏ꍇ�͐��l�Ƃ݂Ȃ��B
							footy2flg = _ttoi(flg);
						}
						// Footy2���ɓK�p
						
						if (CustomMatchCase) {// by Tetr@pod
							int res= Footy2AddEmphasis(FootyID, param, 0, EMP_WORD, 0, 1, 1, footy2flg, footy2col);
						} else {
							int res= Footy2AddEmphasis(FootyID, param, 0, EMP_WORD, 2, 1, 1, footy2flg, footy2col);
						}

						free(param);
						free(flg);
						free(col);
					}
				}
				// 1�s���i�[�����ϐ������
				free(line);
				// �t�@�C�����N���[�Y
				fclose(fp);
			}
			// �t�@�C�������i�[�����ϐ������
			free(fname);
		}
		
		// ���
		free(flist);
		flist = NULL;

	}else{
		// �t�H���_���Ȃ�
		//MessageBoxA(0, "�Ȃ�", "�Ȃ�", 0);
	}

}

// �����I�Ɏg�p���Ă���֐�

// �߂�l�̓e�L�X�g�t�@�C���̐�
int GetFileListNum(LPTSTR folder){
	// 1��ڂ̓f�[�^�̃T�C�Y���擾���邽��
	TCHAR temp[_MAX_PATH];
	WIN32_FIND_DATA lp;
	HANDLE hFile;

	// �p�X�̃R�s�[��*.txt�̕t��
	_tcscpy(temp, folder);
	_tcscat(temp, TEXT("*.txt"));
	// ��������
	hFile = FindFirstFile(temp, &lp);

	if (hFile == INVALID_HANDLE_VALUE) {
		return 0;
	}

	int num = 0;
	do{      
		if((lp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=FILE_ATTRIBUTE_DIRECTORY){
			num++;
		}
	}while(FindNextFile(hFile, &lp));
	// �N���[�Y
	FindClose(hFile);

	return num;
}

// �߂�l�̓e�L�X�g�t�@�C���̐�
int GetFileList(LPTSTR folder,LPTSTR flist){
	// 2��ڂ̓f�[�^���擾���邽��
	TCHAR temp[_MAX_PATH];
	WIN32_FIND_DATA lp;
	HANDLE hFile;

	// �p�X�̃R�s�[��*.txt�̕t��
	_tcscpy(temp, folder);
	_tcscat(temp, TEXT("*.txt"));
	// ��������
	hFile = FindFirstFile(temp, &lp);

	if (hFile == INVALID_HANDLE_VALUE) {
		return 0;
	}

	int num = 0;
	do{      
		if((lp.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=FILE_ATTRIBUTE_DIRECTORY){
			_tcscat(flist, lp.cFileName);
			_tcscat(flist, TEXT("\n"));
			num++;
		}
	}while(FindNextFile(hFile, &lp));
	// �N���[�Y
	FindClose(hFile);

	// �Ō��\n���폜
	flist[_tcslen(flist)-1] = TEXT('\0');

	return num;
}

// ��؂�ꂽ�����擾
int GetSplitNum(LPCTSTR _s1,LPCTSTR s2){
	LPTSTR tok;
	int num = 0;

	// �R�s�[���Ďg�p���邽�ߊm��(���Ȃ炸+1����)
	LPTSTR s1 = (LPTSTR)calloc(_tcslen(_s1)+1,sizeof(TCHAR));
	_tcscpy(s1, _s1);

	tok = _tcstok( s1, s2 );
	while( tok != NULL ){
		num++;
		tok = _tcstok( NULL, s2 );  /* 2��ڈȍ~ */
	}
	
	free(s1);
	return num;
}

// �w�肳�ꂽ�s�̕�������擾
int GetSplitString(LPCTSTR _s1, LPCTSTR s2, int num, LPTSTR res){

	LPTSTR tok;

	// �R�s�[���Ďg�p���邽�ߊm��(���Ȃ炸+1����)
	LPTSTR s1 = (LPTSTR)calloc(_tcslen(_s1)+1,sizeof(TCHAR));
	_tcscpy(s1, _s1);

	int i = 0;
	tok = _tcstok( s1, s2 );
	while( tok != NULL ){
		if (num == i){
			_tcscat(res, tok);
			free(s1);	// ����Y��Ă��̂Œǉ�
			return 1;
		}
		i++;
		tok = _tcstok( NULL, s2 );  /* 2��ڈȍ~ */
	}
	
	free(s1);
	return 0;
}