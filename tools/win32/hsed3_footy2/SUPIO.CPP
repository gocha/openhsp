
//
//	Basic I/O and Message buffer support
//	For both console and Windows application development
//	"supio.cpp"
//	onion software/onitama 1997
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdarg.h>
#include <direct.h>


//
//		basic C I/O support
//

LPTSTR mem_ini( int size ) { return (LPTSTR )malloc(size); }
void mem_bye( void *ptr ) { free(ptr); }
int mem_load( LPTSTR fname, void *mem, int msize )
{
	FILE *fp;
	int flen;
	fp=_tfopen(fname,TEXT("rb"));
	if (fp==NULL) return -1;
	flen = (int)fread( mem, 1, msize, fp );
	fclose(fp);
	return flen;
}
int mem_save( LPTSTR fname, void *mem, int msize )
{
	FILE *fp;
	int flen;
	fp=_tfopen(fname,TEXT("wb"));
	if (fp==NULL) return -1;
	flen = (int)fwrite( mem, 1, msize, fp );
	fclose(fp);
	return flen;
}

int filecopy( LPTSTR fname, LPTSTR sname )
{
	FILE *fp;
	FILE *fp2;
	int flen, rval;
	int max=0x8000;
	LPTSTR mem;
	rval=1;
	mem=mem_ini(max);
	fp=_tfopen(fname,TEXT("rb"));if (fp==NULL) goto jobov;
	fp2=_tfopen(sname,TEXT("wb"));if (fp2==NULL) goto jobov;
	for(;;) {
		flen = (int)fread( mem, 1, max, fp );
		if (flen==0) break;
		fwrite( mem, 1, flen, fp2 );
		if (flen<max) break;
	}
	fclose(fp2);fclose(fp);
	rval=0;
jobov:
	mem_bye(mem);
	return rval;
}

static	LPTSTR ermes;			// info message buffer
static	int mespt;				// info message buffer (index)
#define	maxmes 2048				// message buffer max

void prtini( LPTSTR mes )
{
	ermes=mes;
	mespt=0;
}

void prt( LPTSTR mes )
{
	//		message buffer send
	//
	TCHAR a1;
	int a;
	a=0;
	for(;;) {
		if (mespt>=maxmes) break;
		a1=mes[a++];
		if (a1==10) ermes[mespt++]=13;
		ermes[mespt]=a1;
		if (a1==0) break;
		mespt++;
	}
}

void strcase( LPTSTR str )
{
	//	string case to lower
	//
	int a;
	TCHAR a1;
	_TUCHAR *ss;
	ss=(_TUCHAR*)str;
	a=0;
	for(;;) {
		a1=(_TUCHAR)tolower(ss[a]);
		if (a1==0) break;
		ss[a++]=a1;
	}
}

int tstrcmp( LPTSTR str1, LPTSTR str2 )
{
	//	string compare (0=not same/-1=same)
	//
	int ap;
	TCHAR as;
	ap=0;
	for(;;) {
		as=str1[ap];
		if (as!=str2[ap]) return 0;
		if (as==0) break;
		ap++;
	}
	return -1;
}


void getpath( LPTSTR stmp, LPTSTR outbuf, int p2 )
{
	LPTSTR p;
	TCHAR p_drive[_MAX_PATH];
	TCHAR p_dir[_MAX_DIR];
	TCHAR p_fname[_MAX_FNAME];
	TCHAR p_ext[_MAX_EXT];

	p = outbuf;
	if (p2&16) strcase( stmp );
	_tsplitpath( stmp, p_drive, p_dir, p_fname, p_ext );
	_tcscat( p_drive, p_dir );
	if ( p2&8 ) {
		_tcscpy( stmp, p_fname ); _tcscat( stmp, p_ext );
	} else if ( p2&32 ) {
		_tcscpy( stmp, p_drive );
	}
	switch( p2&7 ) {
	case 1:			// Name only ( without ext )
		stmp[ _tcslen(stmp)-_tcslen(p_ext) ] = 0;
		_tcscpy( p, stmp );
		break;
	case 2:			// Ext only
		_tcscpy( p, p_ext );
		break;
	default:		// Direct Copy
		_tcscpy( p, stmp );
		break;
	}
}


