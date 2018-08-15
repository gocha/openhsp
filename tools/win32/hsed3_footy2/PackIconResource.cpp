/*------------------------------------------------------------------------------
	アイコンとリソース埋め込み for HSP Script Editor by inovia
	作成 2012.02.24
	修正 2012.04.08
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

#include "PackIconResource.h"
#include "CustomColorKeywords.h"

// PathFileExistsで使用
#include "shlwapi.h"
#pragma comment(lib, "shlwapi.lib")

#pragma warning( disable : 4996 )
#pragma warning( disable : 4006 )

void RunIconChange(int activeFootyID){
	/* inovia */
	TCHAR fpath[1024+1] = {0};	// EXE
	TCHAR ipath[1024+1] = {0};	// ico
	TCHAR rpath[1024+1] = {0};	// バージョンリソース
	TCHAR mpath[1024+1] = {0};	// manifest by Tetr@pod
	TCHAR extension[1024+1] = {0};	// 拡張子（オプション）
	int upx = 0;	// UPX（オプション）
	int lang = -1;	// 言語ID（オプション）
	TCHAR cmd[8192+1] = {0};	// コマンドライン

	GetIconResourcePath(fpath, ipath, rpath, mpath/*manifest by Tetr@pod*/, activeFootyID, &upx, &lang, extension);

	// #packopt name "hogehoge" がない場合
	if (_tcscmp(fpath, TEXT("")) == 0){
		_tcscpy(fpath, TEXT("hsptmp"));
	}

	// EXE(hsed3.exe)のあるディレクトリ
	TCHAR exepath[_MAX_PATH+1];
	GetModuleFileName(0, exepath, _MAX_PATH);
	_PathRemoveFileSpec(exepath);	// ディレクトリのみにする
	_tcscat(exepath, TEXT("\\iconins.exe"));

	// スクリプトソースのフォルダ(*.hsp)
	TCHAR tmpfn[_MAX_PATH+1] = {0};
	GetCurrentDirectory( _MAX_PATH, tmpfn );

	// ↓コマンドラインに渡す文字列を代入していく
	_tcscat(cmd, TEXT("-e\""));
	_tcscat(cmd, tmpfn);
	_tcscat(cmd, TEXT("\\"));
	_tcscat(cmd, fpath);
	// 拡張子を変更するオプション（指定なしの場合は.exe）
	if (_tcscmp(extension, TEXT("")) == 0){
		_tcscat(cmd, TEXT(".exe\""));
	}else{
		_tcscat(cmd, extension);
		_tcscat(cmd, TEXT("\""));
	}
	// アイコンパス
	if (_tcscmp(ipath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -i\""));
		_tcscat(cmd, ipath);
		_tcscat(cmd, TEXT("\""));
	}
	// リソース（バージョン）パス
	if (_tcscmp(rpath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -v\""));
		_tcscat(cmd, rpath);
		_tcscat(cmd, TEXT("\""));
	}
	// リソース（manifest）パス by Tetr@pod
	if (_tcscmp(mpath, TEXT("")) != 0){
		_tcscat(cmd, TEXT(" -m\""));
		_tcscat(cmd, mpath);
		_tcscat(cmd, TEXT("\""));
	}

	
	if (upx == 1){
		// UPXを使う場合
		_tcscat(cmd, TEXT(" -u\"1\""));
	}
	if (lang != -1){
		// 言語ID
		TCHAR tmp[1024+1] = {0};
		_stprintf(tmp, TEXT(" -l\"%d\""), lang);
		_tcscat(cmd, tmp);
	}
	//ShellExecute( NULL, "explore", tmpfn, NULL, NULL, SW_SHOWNORMAL );

	// どちらかにパスが入っている場合は実行する
	if ((_tcscmp(ipath, TEXT("")))||(_tcscmp(rpath, TEXT("")))||(upx == 1)){
		if (_PathFileExists(exepath)){
			//char runpath[4096+1];memset( fpath, '\0', sizeof(runpath) );	// パス
			//memset( runpath, '\0', sizeof(runpath) );
			//sprintf( runpath, "\"%s\" %s", exepath, cmd );
			//WinExec( runpath, SW_SHOW );
			
			// 終了まで待機したいのでこちらを使用
			SHELLEXECUTEINFO sei = {sizeof(sei)};
			sei.cbSize = sizeof(SHELLEXECUTEINFO);
			sei.hwnd = 0;
			sei.nShow = SW_SHOWNORMAL;
			sei.fMask = SEE_MASK_NOCLOSEPROCESS;
			sei.lpFile = exepath;
			sei.lpParameters = cmd;
			ShellExecuteEx(&sei);
			// 終了待ち
			WaitForSingleObject(sei.hProcess, INFINITE) ;
			
		}else{
			//
			MessageBox(GetActiveWindow(), TEXT("iconins.exe が見つかりません。アイコンの埋め込みは失敗しました。"), TEXT("エラー"), MB_OK | MB_ICONERROR);
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

// メインスクリプトからパスを検索
int GetIconResourcePath(LPTSTR exepath, LPTSTR iconpath, LPTSTR respath, LPTSTR manifestpath/*manifest by Tetr@pod*/, int _activeFootyID, int *upx, int *lang, LPTSTR extension){
	
	LPTSTR buffer,dummy;
	LPCTSTR cbuffer;
	// Footy2から１行ずつ取得
	int lines = Footy2GetLines(_activeFootyID);
	if (lines == FOOTY2ERR_NOID) return 0;	// そのIDが見つからない場合はそのままリターン
	int i = 0;
	int flag2 = 0;
	// 全行調べる
	for (i = 0;i <= lines; i++){
		// １行のサイズを取得
		int linesize = Footy2GetLineLength(_activeFootyID, i);
		// 問題があった場合は中止
		if ( (linesize == FOOTY2ERR_ARGUMENT) || (linesize == FOOTY2ERR_NOID) ) break;
		// １行の文字数が0の場合（空行の時に参照すると落ちる）
		if (linesize == 0) continue;
		// 動的確保
		buffer = (LPTSTR) calloc( linesize * 2 + 2 , sizeof(TCHAR) );
#ifndef UNICODE
		// １行取得(Footy2GetLineAのマニュアルの引数が間違っているので注意)
		int res = Footy2GetLine(_activeFootyID, buffer, i, linesize * 2);
#else
		cbuffer = Footy2GetLine(_activeFootyID, i);
		int res = FOOTY2ERR_NONE;
#endif
		// いじくってしまうほうのバッファーをbufferからdummyへコピー
		dummy = (LPTSTR) calloc( linesize * 2 + 2 , sizeof(TCHAR) );
#ifndef UNICODE
		memcpy(dummy, buffer, linesize * 2);
#else
		memcpy(dummy, cbuffer, linesize * 2);
		memcpy(buffer, cbuffer, linesize * 2);
#endif
	
		// 問題があった場合は中止
		if ( (res == FOOTY2ERR_ARGUMENT) || (res == FOOTY2ERR_NOID) ){
			free(dummy);dummy = 0;
#ifndef UNICODE
			free(buffer);buffer = 0;
#endif
			break;
		}
		
		// dummyからタブと空白を取り除く
		/*
			0 #pack
			1 #packopt
			2  #packopt
			3 // #packopt 0 

			のような場合、#packopt の前にスペースやタブが入っていても動作するようにするため
		*/
		StrReplaceALL(dummy, TEXT("\t"), TEXT(""));
		StrReplaceALL(dummy, TEXT(" "), TEXT(""));

		// #packopt があるか調べる
		LPTSTR pos = _tcsstr(dummy, TEXT("#packopt"));
		if ((pos != NULL) && (pos-dummy == 0)){
			/*
			char test[128];
			sprintf(test,"%d",pos-dummy);
			MessageBoxA(0,test,"",0);
			*/
			// タブを空白に変換する(統一)
			StrReplaceALL(buffer, TEXT("\t"), TEXT(" "));
			
			// 本当に #packopt か調べる。
			// #packopt2 とか #packopts などのケースに対応
			int splits = GetSplitNum(buffer, TEXT(" "));
			int flag = 0;	// 一致した場合のフラグ
			// 分割数だけ調べる
			int j;
			for (j = 0;j <= splits; j++){
				// 確保
				LPTSTR tmp = (LPTSTR)calloc(linesize * 2 + 2, sizeof(TCHAR));
				// スペースで分割した結果をtmpに代入
				GetSplitString(buffer, TEXT(" "), j, tmp);
				// 一致した場合はフラグを立てる
				if (_tcscmp(tmp, TEXT("#packopt")) == 0) flag = 1;
				// 解放
				free(tmp);tmp = 0;
			}
			// #packoptが一致した場合のみ続行
			if (flag == 1){
				// キーワードを取得というか比較してフラグを立てる
				// #packopt name "test"
				//           ↑ コレ
				splits = GetSplitNum(buffer, TEXT(" "));
				int j;
				for (j = 0;j <= splits; j++){
					// 確保
					LPTSTR tmp = (LPTSTR)calloc(linesize * 2 + 2, sizeof(TCHAR));
					// スペースで分割した結果をtmpに代入
					GetSplitString(buffer, TEXT(" "), j, tmp);
					// 一致した場合はフラグを立てる
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
					// 解放
					free(tmp);tmp = 0;
				}
				// 例 #packopt name "hogehoge" のかっこの間（範囲）を取得
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

				// 文字列が長すぎる場合はエラー文字を代入する
				if (_tcslen(outpath) > 512){
					_tcscpy(outpath, TEXT("::ERROR::"));
				}

				// 条件分岐
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
						// lang(言語ID)
						TCHAR langid[1024+1];memset( langid, TEXT('\0'), sizeof(langid) );
						_tcscpy(langid, outpath);
						*lang = _ttoi(langid);
						break;
					case 6 : 
						// extension(拡張子)
						_tcscpy(extension, outpath);
						break;
					case 8 : 
						// manifest by Tetr@pod
						_tcscpy(manifestpath, outpath);
						break;
					default : 
						// それ以外。何もしない。
						break;
				}
				// 解放
				free(outpath);outpath = 0;flag2 = 0;

			}

		}

		// 必ず解放
		free(dummy);dummy = 0;
#ifndef UNICODE
		free(buffer);buffer = 0;
#endif

		// 7 の場合強制離脱
		if (flag2 == 7)
			break;
	} 
	return 0;
}

// １つのみ置き換え
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

// 対象文字列をすべて置き換え
int StrReplaceALL(LPTSTR buf, LPTSTR mae, LPTSTR ato)
{
	int i = 0;
	while (StrReplace(buf, mae, ato)){
		i++;
	}
	return i;
}

