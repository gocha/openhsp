/*------------------------------------------------------------------------------
	色定義追加 for HSP Script Editor by inovia
	作成 2011.12.20
	修正 2011.12.26
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

// PathIsDirectoryで使用
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#include "CustomColorKeywords.h"

#pragma warning( disable : 4996 )

extern BOOL bCustomColor;

extern BOOL CustomMatchCase;// by Tetr@pod


// classify.cpp	の SetClassify()から呼び出されます
void SetCumtomColorKeywords(int FootyID, MYCOLOR color)
{
	// 設定ファイルで使用しない設定の場合は色付けしない
	if (bCustomColor == FALSE)
		return;
	// 色定義(デフォの色)
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
	// 大小比較記号、OR記号、演算子、ifの{}、演算子の() などを許可 by Tetr@pod
	int FuncParam = EMP_IND_BLANKS | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_ANGLE_BRACKET | EMP_IND_PARENTHESIS;
	int CFuncParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_ANGLE_BRACKET; 
	int VarParam = EMP_IND_BLANKS | EMP_IND_PARENTHESIS | EMP_IND_OTHER_ASCII_SIGN | EMP_IND_BRACE | EMP_IND_OPERATORS | EMP_IND_ANGLE_BRACKET;

	// エディタから設定読み出し
	FuncColor = color.Character.Function.Conf;
	CFuncColor = color.Character.Function.Conf;
	OwnFuncColor = color.Character.Function.Conf;
	OwnCFuncColor = color.Character.Function.Conf;
	Win32APIFuncColor = color.Character.Function.Conf;
	Win32APICFuncColor = color.Character.Function.Conf;
	SysVarColor = color.Character.Function.Conf;
	MacroColor = color.Character.Macro.Conf;

	// EXEのあるディレクトリ
	TCHAR exepath[MAX_PATH+1];
	GetModuleFileName(0, exepath, MAX_PATH);
	PathRemoveFileSpec(exepath);

	// カスタム色定義ファイル読み込み
	TCHAR cumtompath[MAX_PATH+1];
	_tcscpy(cumtompath, exepath);
	_tcscat(cumtompath, TEXT("\\keywords\\color.ini"));

	FILE *fpini = _tfopen(cumtompath,TEXT("r"));
	if (fpini != NULL){
		TCHAR tmp[1024+1];
		while ((_fgetts(tmp, 1024, fpini)) != NULL) {
			// 改行コードだった場合
			if (tmp[_tcslen(tmp)-1] == 0x0A){
				tmp[_tcslen(tmp)-1] = TEXT('\0');	// 余計な改行コードをNULLで埋めて削除
			}
			// 分割数が２の場合
			if (GetSplitNum(tmp, TEXT(" ")) == 2){
				LPTSTR p = (LPTSTR)calloc(1024+1, sizeof(char));
				LPTSTR c = (LPTSTR)calloc(1024+1, sizeof(char));
				GetSplitString(tmp, TEXT(" "), 0, p); // スペースで分離して０番目の要素を取得
				GetSplitString(tmp, TEXT(" "), 1, c);	// スペースで分離して１番目の要素を取得
				// キーワードチェック
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


	// キーワードフォルダをチェック
	TCHAR crDir[MAX_PATH + 1];
	//GetCurrentDirectoryA(MAX_PATH+1, crDir);
	//strcat(crDir, "\\keywords\\");
	_tcscpy(crDir, exepath);
	_tcscat(crDir, TEXT("\\keywords\\"));

	// キーワードフォルダが存在しているかどうか
	if (PathIsDirectory(crDir)){
		// ある場合(最後に\\がついていること)
		// フォルダ内のファイルの数を取得
		int fnum = GetFileListNum(crDir);
		// (MAX_PATH＋2)×fnum bytes分の領域を確保(改行コードも含む)
		LPTSTR flist = (LPTSTR)calloc(fnum*(MAX_PATH+2)+1,sizeof(TCHAR));
		// ファイルの一覧を取得(\nで分けられた形式)
		GetFileList(crDir, flist);
		// ファイルの数だけ繰り返す
		int i = 0;
		for(i = 0; i<GetSplitNum(flist, TEXT("\n")); i++){
			// ファイル名を格納する変数を確保
			LPTSTR fname = (LPTSTR)calloc(MAX_PATH+1, sizeof(TCHAR));
			_tcscpy(fname, exepath);
			_tcscat(fname, TEXT("\\keywords\\"));// フォルダ名を先に付加
			// ファイル名を取得する
			GetSplitString(flist, TEXT("\n"), i, fname);
			// ファイルをオープンする
			FILE *fp = _tfopen(fname,TEXT("r"));
			if (fp != NULL){
				// 1行分のデータ保存用（こんなにいらないと思うけど）
				LPTSTR line = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
				// 1行ずつ読み取り
				while ((_fgetts(line, 1024, fp)) != NULL) {
					// 改行コードだった場合
					if (line[_tcslen(line)-1] == 0x0A){
						line[_tcslen(line)-1] = TEXT('\0');	// 余計な改行コード削除
					}
					// 分割数が３の場合は処理する
					if (GetSplitNum(line, TEXT(" ")) == 3){
						int footy2col = 0;
						int footy2flg = 0;
						LPTSTR param = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
						LPTSTR flg = (LPTSTR)calloc(1024+1, sizeof(TCHAR));
						LPTSTR col = (LPTSTR)calloc(1024+1, sizeof(TCHAR));

						GetSplitString(line, TEXT(" "), 0, param);
						GetSplitString(line, TEXT(" "), 1, flg);
						GetSplitString(line, TEXT(" "), 2, col);

						// 色のキーワードチェック
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
							// それ以外の場合は数値とみなす。
							int customcolor = _ttoi(col);
							footy2col = customcolor;
						}
						// 独立性の設定
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
							// それ以外の場合は数値とみなす。
							footy2flg = _ttoi(flg);
						}
						// Footy2側に適用
						
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
				// 1行を格納した変数を解放
				free(line);
				// ファイルをクローズ
				fclose(fp);
			}
			// ファイル名を格納した変数を解放
			free(fname);
		}
		
		// 解放
		free(flist);
		flist = NULL;

	}else{
		// フォルダがない
		//MessageBoxA(0, "ない", "ない", 0);
	}

}

// 内部的に使用している関数

// 戻り値はテキストファイルの数
int GetFileListNum(LPTSTR folder){
	// 1回目はデータのサイズを取得するため
	TCHAR temp[_MAX_PATH];
	WIN32_FIND_DATA lp;
	HANDLE hFile;

	// パスのコピー＆*.txtの付加
	_tcscpy(temp, folder);
	_tcscat(temp, TEXT("*.txt"));
	// 検索する
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
	// クローズ
	FindClose(hFile);

	return num;
}

// 戻り値はテキストファイルの数
int GetFileList(LPTSTR folder,LPTSTR flist){
	// 2回目はデータを取得するため
	TCHAR temp[_MAX_PATH];
	WIN32_FIND_DATA lp;
	HANDLE hFile;

	// パスのコピー＆*.txtの付加
	_tcscpy(temp, folder);
	_tcscat(temp, TEXT("*.txt"));
	// 検索する
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
	// クローズ
	FindClose(hFile);

	// 最後に\nを削除
	flist[_tcslen(flist)-1] = TEXT('\0');

	return num;
}

// 区切られた数を取得
int GetSplitNum(LPCTSTR _s1,LPCTSTR s2){
	LPTSTR tok;
	int num = 0;

	// コピーして使用するため確保(かならず+1する)
	LPTSTR s1 = (LPTSTR)calloc(_tcslen(_s1)+1,sizeof(TCHAR));
	_tcscpy(s1, _s1);

	tok = _tcstok( s1, s2 );
	while( tok != NULL ){
		num++;
		tok = _tcstok( NULL, s2 );  /* 2回目以降 */
	}
	
	free(s1);
	return num;
}

// 指定された行の文字列を取得
int GetSplitString(LPCTSTR _s1, LPCTSTR s2, int num, LPTSTR res){

	LPTSTR tok;

	// コピーして使用するため確保(かならず+1する)
	LPTSTR s1 = (LPTSTR)calloc(_tcslen(_s1)+1,sizeof(TCHAR));
	_tcscpy(s1, _s1);

	int i = 0;
	tok = _tcstok( s1, s2 );
	while( tok != NULL ){
		if (num == i){
			_tcscat(res, tok);
			free(s1);	// 解放忘れてたので追加
			return 1;
		}
		i++;
		tok = _tcstok( NULL, s2 );  /* 2回目以降 */
	}
	
	free(s1);
	return 0;
}