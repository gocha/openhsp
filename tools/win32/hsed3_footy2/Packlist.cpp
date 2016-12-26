/*--------------------------------------------------------
	listbox window proc
									  1997/10  onitama
  --------------------------------------------------------*/

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <direct.h>
#include "poppad.h"
#include "resource.h"

static TCHAR szCDir[_MAX_PATH];
static TCHAR szDefDir[_MAX_PATH];
static TCHAR szFilt[128];
static int enc_mode;			// 暗号化モード(1=normal/2=encode)

typedef struct PFDIR
{
	//		PackFile directory list structure
	//
	int		flag;
	TCHAR	fname[128];
	TCHAR	pname[_MAX_PATH];

} PFDIR;

#define pfmax 2048
static PFDIR *mem_pf;
static PFDIR *pf;
int pid;

//
//		PackFile manager routines
//

void pf_ini( void )
{
	int a;
	mem_pf=(PFDIR *)malloc(sizeof(PFDIR)*pfmax);
	for(a=0;a<pfmax;a++) {
		pf=&mem_pf[a];
		pf->flag=0;pf->fname[0]=0;pf->pname[0]=0;
	}
	pid=0;
	enc_mode=1;
}

void pf_bye( void )
{
	free(mem_pf);
}

void pf_add( HWND hDlg, LPTSTR fname, LPTSTR pname )
{
	int a,i;
	TCHAR nam[128];
	if (*fname==0) return;
	if (pname[_tcslen(pname)-1]!=TEXT('\\')) _tcscat(pname,TEXT("\\"));

	a=0;
	if (pid) {
		for(i=0;i<pid;i++) {
			pf=&mem_pf[i];
			if (_tcscmp(pf->fname,fname)==0) a++;
		}
	}
	if (a) {
#ifdef JPNMSG
		MessageBox ( hDlg, TEXT("すでに登録されているファイル名です。"),
						   TEXT("packfile warning"), MB_OK | MB_ICONEXCLAMATION);
#else
		MessageBox ( hDlg, TEXT("Already in use."),
						   TEXT("packfile warning"), MB_OK | MB_ICONEXCLAMATION);
#endif
		return;
	}
	pf=&mem_pf[pid];
	pf->flag = enc_mode;
	_tcscpy(pf->fname,fname);
	_tcscpy(pf->pname,pname);
	pid++;

	if ( enc_mode==1 ) {
		_tcscpy( nam, fname );
	}
	else {
		_tcscpy( nam,TEXT("+") );_tcscat( nam, fname );
	}
	SendDlgItemMessage( hDlg,IDC_LIST3, LB_ADDSTRING,(WPARAM)-1,(LPARAM)nam );
}

int pf_find( LPTSTR fname )
{
	int a,sel;
	LPTSTR p;
	if (pid==0) return -1;
	sel=-1;
	p = fname; if ( *p==TEXT('+') ) p++;
	for(a=0;a<pid;a++) {
		pf=&mem_pf[a];
		if (_tcscmp( pf->fname, p )==0) sel=a;
	}
	return sel;
}

void pf_del( int id )
{
	int a,i;
	i=id;
	if ( pid<=0 ) return;
	for(;;) {
		a=i+1;
		mem_pf[i].flag = mem_pf[a].flag;
		_tcscpy( mem_pf[i].fname, mem_pf[a].fname );
		_tcscpy( mem_pf[i].pname, mem_pf[a].pname );
		i++;
		if (i>=pid) break;
	}
	pid--;
}


int pf_save( void )
{
	TCHAR szNow[_MAX_PATH];
	TCHAR szDir[_MAX_PATH];
	TCHAR stt[256];
	FILE *fp;
	int a,l;

	_tcscpy(szNow,szDefDir);
	if (szNow[_tcslen(szNow)-1]!=TEXT('\\')) _tcscat(szNow,TEXT("\\"));

	fp=_tfopen(TEXT("packfile"),TEXT("wb"));
	if (fp==NULL) return -1;
	wsprintf( stt,TEXT(";  packfile list for DPM\r\n") );
	_fputts( stt,fp );
	wsprintf( stt,TEXT(";  Current dir is [%s]\r\n"),szNow );
	_fputts( stt,fp );

	if (pid) {
		for(a=0;a<pid;a++) {
			pf=&mem_pf[a];
			if ( pf->flag ) {
				_tcscpy(szDir,pf->pname);l=(int)_tcslen(szNow);
				if (_tcsncmp(szNow,szDir,l)==0) {
					_tcscpy(szDir,szDir+l);
				}
				if ( pf->flag==1 ) {
					wsprintf( stt,TEXT("%s%s\r\n"), szDir, pf->fname );
				}
				else {
					wsprintf( stt,TEXT("+%s%s\r\n"), szDir, pf->fname );
				}
				_fputts( stt,fp );
			}
		}
	}
	fclose(fp);
	return 0;
}

int pf_load( HWND hDlg )
{
	TCHAR s0[256];
	TCHAR s1[256];
	TCHAR s2[256];
	TCHAR a1;
	FILE *fp;
	int a,b;
	int enc_bak;

	enc_bak = enc_mode;
	fp=_tfopen(TEXT("packfile"),TEXT("rb"));
	if (fp==NULL) return -1;
	for(;;) {
		if ( _fgetts(s0,256,fp)==NULL ) break;
		a1=*s0;
		if ((a1!=TEXT(';'))&&(a1!=0)) {
			if ( a1==TEXT('+') ) {
				enc_mode = 2;
				_tcscpy( s1,s0+1 );
			}
			else {
				enc_mode = 1;
				_tcscpy( s1,s0 );
			}
			b=-1;
			for(a=0;a<(int)_tcslen(s1);a++) {
				a1=s1[a];if (a1<32) s1[a]=0;
				if (a1==0x5c) b=a;
			}
			if (b==-1)  {
				_tcscpy( s2,szDefDir );
				pf_add( hDlg,s1,s2 );
			}
			else {
				_tcscpy( s2,s1+b+1 );s1[b]=0;
				pf_add( hDlg,s2,s1 );
			}
		}
	}
	fclose(fp);
	enc_mode = enc_bak;
	return 0;
}



//
//		Dialog proc
//

void set_dirlist( HWND hDlg )
{
	HWND h;
	_tgetcwd( szCDir, _MAX_PATH ) ;
	h=GetDlgItem( hDlg,IDC_CDIR );SetWindowText( h,szCDir );
	SendDlgItemMessage( hDlg,IDC_LIST1,LB_RESETCONTENT, 0, 0L );
	SendDlgItemMessage( hDlg,IDC_LIST2,LB_RESETCONTENT, 0, 0L );
	SendDlgItemMessage( hDlg,IDC_LIST1,LB_DIR,DDL_READWRITE,(LPARAM)szFilt );
	SendDlgItemMessage( hDlg,IDC_LIST2,
		LB_DIR,DDL_DIRECTORY|DDL_DRIVES|DDL_EXCLUSIVE,(LPARAM)TEXT("*.*") );
}

BOOL CALLBACK PlistDlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM /*lParam*/)
{
	HWND h;
	TCHAR szText[128];
	int ctrl_id, i, j;

	switch (message)
	{
	case WM_INITDIALOG:
		h=GetDlgItem( hDlg,IDC_EDIT1 );
		_tcscpy( szFilt,TEXT("*.*") );
		SetWindowText( h,szFilt );
		_tgetcwd( szDefDir, 128 ) ;
		set_dirlist( hDlg );
		pf_ini();
		pf_load( hDlg );
		return TRUE ;

	case WM_CLOSE:
		_tchdir( szDefDir );
		pf_bye();
		EndDialog (hDlg, 0);
		return TRUE;

	case WM_COMMAND:
		ctrl_id = GET_WM_COMMAND_ID(wParam, lParam);
		if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_DBLCLK ) {
			i = (int)SendDlgItemMessage( hDlg,ctrl_id, LB_GETCURSEL,0,0L );
			SendDlgItemMessage( hDlg,ctrl_id, LB_GETTEXT,i,(LPARAM)szText );
			if ( ctrl_id==IDC_LIST2 ) {
				szText[_tcslen(szText)-1]=0;
				if (szText[1]==TEXT('-')) {
					szText[3]=TEXT(':');_tchdir(szText+2);
				}
				else _tchdir(szText + 1);
				set_dirlist( hDlg );
			}
			if ( ctrl_id==IDC_LIST1 ) {
				pf_add( hDlg,szText,szCDir );
			}
			break;
		}
		if ( ctrl_id==IDC_EDIT1 ) {
			GetDlgItemText( hDlg,IDC_EDIT1,szFilt,128 );
			set_dirlist( hDlg );
			break;
		}
		if ( ctrl_id==IDC_CHECK1 ) {
			enc_mode = 1;
			if ( IsDlgButtonChecked( hDlg,IDC_CHECK1 )==BST_CHECKED ) enc_mode=2;
			break;
		}
		switch (ctrl_id)
		{
		case IDCM_ADD:
			h=GetDlgItem( hDlg,IDC_LIST1 );
			j=(int)SendMessage( h,LB_GETCOUNT,0,0L );
			if (j==0) break;
			for(i=0;i<j;i++) {
				if ( SendMessage( h,LB_GETSEL,i,0L ) ) {
					SendMessage( h, LB_GETTEXT,i,(LPARAM)szText );
					pf_add( hDlg,szText,szCDir );
				}
			}
			break;

		case IDCM_ALLSEL:
			h=GetDlgItem( hDlg,IDC_LIST1 );
			j=(int)SendMessage( h,LB_GETCOUNT,0,0L );
			if (j==0) break;
			for(i=0;i<j;i++) {
				SendMessage( h, LB_GETTEXT,i,(LPARAM)szText );
				pf_add( hDlg,szText,szCDir );
			}
			break;

		case IDCM_DEL:
			i=(int)SendDlgItemMessage( hDlg,IDC_LIST3, LB_GETCURSEL,0,0L );
			if (i>=0) {
				SendDlgItemMessage( hDlg,IDC_LIST3, LB_GETTEXT,i,(LPARAM)szText );
				SendDlgItemMessage( hDlg,IDC_LIST3, LB_DELETESTRING,i,0L );
				i=pf_find( szText );
				pf_del( i );
			}
			break;

		case IDCM_CLR:
			SendDlgItemMessage( hDlg,IDC_LIST3,LB_RESETCONTENT, 0, 0L );
			pf_bye();
			pf_ini();
			break;

		case IDOK:
			_tchdir( szDefDir );
			pf_save();
			pf_bye();
			EndDialog (hDlg, 0);
			return TRUE;

		case IDCANCEL:
			_tchdir( szDefDir );
			pf_bye();
			EndDialog (hDlg, 0);
			return TRUE;
		}
		break ;
	}
	return FALSE ;
}

