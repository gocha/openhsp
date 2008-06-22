
//
//		Label Manager class
//			onion software/onitama 2002/2
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "label.h"

//-------------------------------------------------------------
//		Routines
//-------------------------------------------------------------

int CLabel::StrCase( char *str )
{
	//	string case to lower
	//
	int hash;
	unsigned char a1;
	unsigned char a2;
	unsigned char *ss;
	hash = 0;
	ss = (unsigned char *)str;
	while(1) {
		a1=*ss;
		if (a1==0) break;
		if (a1>=0x80) {
			ss++;
			a1=*ss++;
			if (a1==0) break;
			hash += (int)a1;
		}
		else {
			a2 = tolower(a1);
			hash += (int)a2;
			*ss++ = a2;
		}
	}
	return hash;
}


int CLabel::GetHash( char *str )
{
	//		HUSH�l�𓾂�
	//
	int hash;
	unsigned char a1;
	unsigned char *ss;
	hash = 0;
	ss = (unsigned char *)str;
	while(1) {
		a1=*ss;
		if (a1==0) break;
		if (a1>=0x80) {
			ss++;
			a1=*ss++;
			if (a1==0) break;
			hash += (int)a1;
		}
		else {
			hash += (int)a1;
			ss++;
		}
	}
	return hash;
}


int CLabel::StrCmp( char *str1, char *str2 )
{
	//	string compare (0=not same/-1=same)
	//  (case sensitive)
	int ap;
	char as;
	ap=0;
	while(1) {
		as=str1[ap];
		if (as!=str2[ap]) return 0;
		if (as==0) break;
		ap++;
	}
	return -1;
}


int CLabel::Regist( char *name, int type, int opt )
{
	int a;

	if ( name[0]==0 ) return -1;
	if ( cur>=maxlab ) {				// ���x���o�b�t�@�g��
		LABOBJ *tmp;
		int i,oldsize;
		oldsize = sizeof(LABOBJ)*maxlab;
		maxlab += def_maxlab;
		tmp = (LABOBJ *)malloc( sizeof(LABOBJ)*maxlab );
		for(i=0;i<maxlab;i++) { tmp[i].flag = -1; }
		memcpy( (char *)tmp, (char *)mem_lab, oldsize );
		free( mem_lab );
		mem_lab = tmp;
	}

	a = cur;
	lab=&mem_lab[cur++];
	lab->flag = 1;
	lab->type = type;
	lab->opt  = opt;
	lab->eternal = 0;
	lab->ref = 0;
	lab->name = RegistSymbol( name );
	lab->data = NULL;
	lab->data2 = NULL;
	lab->hash = StrCase( lab->name );
	lab->rel = NULL;
	return a;
}


void CLabel::SetEternal( int id )
{
	//		set eternal flag
	//
	mem_lab[id].eternal=1;
}


int CLabel::GetEternal( int id )
{
	//		set eternal flag
	//
	return mem_lab[id].eternal;
}


void CLabel::SetFlag( int id, int val )
{
	//		set eternal flag
	//
	mem_lab[id].flag = val;
}


void CLabel::SetOpt( int id, int val )
{
	//		set option
	//
	mem_lab[id].opt = val;
}


void CLabel::SetData( int id, char *str )
{
	//		set data
	//
	lab=&mem_lab[id];
	if ( str == NULL ) {
		lab->data = NULL;
		return;
	}
	lab->data = RegistTable( str, strlen(str)+1 );
}


void CLabel::SetData2( int id, char *str, int size )
{
	//		set data
	//
	lab=&mem_lab[id];
	if ( str == NULL ) {
		lab->data2 = NULL;
		return;
	}
	lab->data2 = RegistTable( str, size );
}


int CLabel::Search( char *oname )
{
	//		object name search
	//
	char as;
	int a;
	int hash;
	char *str1,*str2;
	if (cur==0) return -1;

	hash = StrCase( oname );
	lab = mem_lab;
	for(a=0;a<cur;a++) {
		if ( lab->flag >= 0 ) {
			if ( hash == lab->hash ) {
				str1=oname;
				str2=lab->name;
				while(1) {
					as=*str1;
					if (as!=*str2) break;
					if (as==0) return a;
					str1++;str2++;
				}
			}
		}
		lab++;
	}
	return -1;
}


int CLabel::SearchLocal( char *oname, char *loname )
{
	//		object name search ( for local )
	//
	char as;
	int a;
	int hash,hash2,myhash;
	char *str1,*str2;
	if (cur==0) return -1;

	hash = StrCase( oname );
	hash2 = GetHash( loname );
	lab = mem_lab;
	for(a=0;a<cur;a++) {
		if ( lab->flag >= 0 ) {
			if (lab->eternal) {
				str1 = oname;
				myhash = hash;
			} else {
				str1 = loname;
				myhash = hash2;
			}
			if ( lab->hash == myhash ) {
				str2=lab->name;
				while(1) {
					as=*str1;
					if (as!=*str2) break;
					if (as==0) return a;
					str1++;str2++;
				}
			}
		}
		lab++;
	}
	return -1;
}


//-------------------------------------------------------------
//		Interfaces
//-------------------------------------------------------------

CLabel::CLabel( void )
{
	int i;
	maxsymbol = def_maxsymbol;
	maxlab = def_maxlab;
	mem_lab = (LABOBJ *)malloc( sizeof(LABOBJ)*maxlab );
	for(i=0;i<def_maxblock;i++) { symblock[i] = NULL; }
	Reset();
}


CLabel::CLabel( int symmax, int worksize )
{
	int i;
	maxsymbol = worksize;
	maxlab = symmax;
	mem_lab = (LABOBJ *)malloc( sizeof(LABOBJ)*maxlab );
	for(i=0;i<def_maxblock;i++) { symblock[i] = NULL; }
	Reset();
}


void CLabel::Reset( void )
{
	int i;
	cur = 0;
	for(i=0;i<maxlab;i++) { mem_lab[i].flag = -1; }
	DisposeSymbolBuffer();
	MakeSymbolBuffer();
}


CLabel::~CLabel( void )
{
	DisposeSymbolBuffer();
	if ( mem_lab != NULL ) free( mem_lab );
}


void CLabel::MakeSymbolBuffer( void )
{
	symbol = (char *)malloc( maxsymbol );
	symblock[curblock] = symbol;
	curblock++;
	symcur = 0;
}


void CLabel::DisposeSymbolBuffer( void )
{
	int i;
	for(i=0;i<def_maxblock;i++) {
		if ( symblock[i] != NULL ) {
			free( symblock[i] );
			symblock[i] = NULL;
		}
	}
	curblock = 0;
}


char *CLabel::ExpandSymbolBuffer( int size )
{
	char *p;
	p = symbol + symcur;
	symcur += size;
	if ( symcur >= maxsymbol ) {
		MakeSymbolBuffer();
		symcur += size;
		return symbol;
	}
	return p;
}


int CLabel::GetCount( void )
{
	return cur;
}


int CLabel::GetSymbolSize( void )
{
	return ((maxsymbol * (curblock-1))+symcur);
}


int CLabel::GetFlag( int id )
{
	return mem_lab[id].flag;
}


int CLabel::GetOpt( int id )
{
	return mem_lab[id].opt;
}


int CLabel::GetType( int id )
{
	return mem_lab[id].type;
}


char *CLabel::GetName( int id )
{
	return mem_lab[id].name;
}


char *CLabel::GetData( int id )
{
	return mem_lab[id].data;
}


char *CLabel::GetData2( int id )
{
	return mem_lab[id].data2;
}


LABOBJ *CLabel::GetLabel( int id )
{
	return &mem_lab[id];
}


char *CLabel::RegistSymbol( char *str )
{
	//		�V���{���e�[�u���ɕ������o�^
	//
	char *p;
	char *pmaster;
	char *src;
	char a1,a2;
	int i;
	//int hush;
	i = 0;
	p = ExpandSymbolBuffer( strlen(str)+1 );
	pmaster = p;
	src = str;
	a2 = *src;
	while(1) {
		a1=*src++;
		*p++ = a1;
		if ( a1 == 0 ) break;
		if ( i >= (maxname-1) ) { *p=0; i++; break; }
		i++;
	}
	//if (i) a1 = str[i-1];
	//symcur+=i+1;
	//hush = (a1+a2+i)&31;
	//return hush;
	return pmaster;
}


char *CLabel::RegistTable( char *str, int size )
{
	//		�V���{���e�[�u���Ƀe�[�u���f�[�^��o�^
	//
	char *p;
	char *src;
	src = str;
	p = ExpandSymbolBuffer( size );
	memcpy( p, src, size );
	return p;
}


char *CLabel::GetListToken( char *str )
{
	char *p;
	char *dst;
	char a1;
	p = str;
	while(1) {
		a1=*p;if ( a1!=32 ) break;
		p++;
	}
	dst = token;
	while(1) {
		a1=*p;if (( a1==0 )||( a1==32 )) break;
		*dst++=a1;
		p++;
	}
	*dst=0;
	return p;
}


int CLabel::RegistList( void *list, char *modname )
{
	//		�L�[���[�h���X�g��o�^����
	//
	char *p;
	char **plist;
	char tmp[256];
	int id,i,type,opt;
	i = 1;
	plist = (char **)list;
	p = (char *)list;
	while(1) {
		p = tmp;
		strcpy( p, plist[i++] );
		if (p[0]!='$') break;
		p++;
		p = GetListToken( p );
		opt = HtoI();
		p = GetListToken( p );
		type = atoi( token );
		p = GetListToken( p );
		strcat( token, modname );
		id = Regist( token, type, opt );
		SetEternal( id );
	}
	return 0;
}


int CLabel::RegistList2( void *list, char *modname )
{
	//		�L�[���[�h���X�g��word@modname�̑�փ}�N���Ƃ��ēo�^����
	//
	char *p;
	char **plist;
	char tmp[256];
	int id,i,type,opt;
	i = 1;
	plist = (char **)list;
	p = (char *)list;
	while(1) {
		p = tmp;
		strcpy( p, plist[i++] );
		if (p[0]!='$') break;
		p++;
		p = GetListToken( p );
		opt = HtoI();
		p = GetListToken( p );
		type = atoi( token );
		p = GetListToken( p );
		//id = Regist( token, type, opt );

		id = Regist( token, LAB_TYPE_PPINTMAC, 0 );		// �����}�N���Ƃ��Ē�`
		strcat( token, modname );
		SetData( id, token );
		SetEternal( id );
	}
	return 0;
}


int CLabel::RegistList3( void *list )
{
	//		�L�[���[�h���X�g��F�����e�[�u���p�ɓo�^����
	//
	char *p;
	char **plist;
	char tmp[256];
	int id,i,type,opt;
	static int kwcnv[]={

	LAB_TYPE_PPEX_PRECMD,	//TYPE_MARK 0
	LAB_TYPE_PPMAC,			//TYPE_VAR 1
	LAB_TYPE_PPEX_INTCMD,	//TYPE_STRING 2
	LAB_TYPE_PPEX_INTCMD,	//TYPE_DNUM 3
	LAB_TYPE_PPEX_INTCMD,	//TYPE_INUM 4
	LAB_TYPE_PPEX_INTCMD,	//TYPE_STRUCT 5
	LAB_TYPE_PPEX_INTCMD,	//TYPE_XLABEL 6
	LAB_TYPE_PPEX_INTCMD,	//TYPE_LABEL 7
	LAB_TYPE_PPEX_INTCMD,	//TYPE_INTCMD 8
	LAB_TYPE_PPEX_INTCMD,	//TYPE_EXTCMD 9
	LAB_TYPE_PPEX_INTCMD,	//TYPE_EXTSYSVAR 10
	LAB_TYPE_PPEX_INTCMD,	//TYPE_CMPCMD 11
	LAB_TYPE_PPEX_INTCMD,	//TYPE_MODCMD 12
	LAB_TYPE_PPEX_INTCMD,	//TYPE_INTFUNC 13
	LAB_TYPE_PPEX_INTCMD,	//TYPE_SYSVAR 14
	LAB_TYPE_PPEX_INTCMD,	//TYPE_PROGCMD 15
	LAB_TYPE_PPEX_INTCMD,	//TYPE_DLLFUNC 16
	LAB_TYPE_PPEX_EXTCMD,	//TYPE_DLLCTRL 17
	LAB_TYPE_PPEX_INTCMD,	//TYPE_USERDEF 18

	};

	i = 1;
	plist = (char **)list;
	p = (char *)list;
	while(1) {
		p = tmp;
		strcpy( p, plist[i++] );
		if (p[0]!='$') break;
		p++;
		p = GetListToken( p );
		opt = HtoI();
		p = GetListToken( p );
		type = atoi( token );
		p = GetListToken( p );
		id = Regist( token, kwcnv[ type ], opt );
		SetEternal( id );
	}
	return 0;
}


//-------------------------------------------------------------
//		For debug
//-------------------------------------------------------------

char *CLabel::Prt( char *str, char *str2 )
{
	char *p;
	p = str;
	strcpy( str, str2 );
	p+=strlen(str2);
	*p++=13;
	*p++=10;
	return p;
}


int CLabel::HtoI( void )
{
	//	Convert token(hex) to int
	char *wp;
	char a1;
	int val,b;
	val=0;
	wp = token;
	while(1) {
		a1=toupper(*wp);b=-1;
		if (a1==0) { wp=NULL;break; }
		if ((a1>=0x30)&&(a1<=0x39)) b=a1-0x30;
		if ((a1>=0x41)&&(a1<=0x46)) b=a1-55;
		if (a1=='_') b=-2;
		if (b==-1) break;
		if (b>=0) { val=(val<<4)+b; }
		wp++;
	}
	return val;
}


void CLabel::DumpLabel( char *str )
{
	char tmp[256];
	char *p;
	int a;
	p = str;
	p=Prt( p,"#Debug dump" );
	sprintf( tmp,"#Labels:%d",cur );
	p=Prt( p,tmp );
	for(a=0;a<cur;a++) {
		lab=&mem_lab[a];
		sprintf( tmp,"#ID:%d (%s) flag:%d  type:%d  opt:%x",a,lab->name,lab->flag,lab->type,lab->opt );
		p=Prt( p,tmp );
//		lab = GetLabel( Search( lab->name) );
//		sprintf( tmp,"#ID:%d (%s) flag:%d  type:%d  opt:%x",a,lab->name,lab->flag,lab->type,lab->opt );
//		p=Prt( p,tmp );
	}
	*p=0;
}


void CLabel::DumpHSPLabel( char *str, int option )
{
	char tmp[256];
	char *typem;
//	char optm[256];
	char *p;
	int a;
	p = str;
	for(a=0;a<cur;a++) {
		lab=&mem_lab[a]; typem = NULL;
		switch( lab->type ) {
		case LAB_TYPE_PPEX_PRECMD:
			if ( option & LAB_DUMPMODE_RESCMD ) typem = "pre|func";
			break;
		case LAB_TYPE_PPEX_EXTCMD:
			if ( option & LAB_DUMPMODE_RESCMD ) typem = "sys|func|1";
			break;
		case LAB_TYPE_PPDLLFUNC:
			if ( option & LAB_DUMPMODE_DLLCMD ) typem = "sys|func|2";
			break;
		case LAB_TYPE_PPMODFUNC:
			if ( option & LAB_DUMPMODE_DLLCMD ) typem = "sys|func|3";
			break;
		case LAB_TYPE_PPMAC:
		case LAB_TYPE_PPVAL:
			if ( option & LAB_DUMPMODE_RESCMD ) typem = "sys|macro";
			break;
		default:
			if ( option & LAB_DUMPMODE_RESCMD ) typem = "sys|func";
			break;
		}
/*
		if ( lab->opt >= 0x100 ) {
			if (( lab->opt & 0xff )<0x10 ) {
				optm[0]='|';
				optm[1]=48+(lab->opt>>8); optm[2]=0;
				strcat( typem,optm );
			}
		}
*/
		if ( typem != NULL ) {
			sprintf( tmp,"%s\t,%s",lab->name,typem );
			p=Prt( p,tmp );
		}
	}
	*p=0;
}


void CLabel::AddReference( int id )
{
	//		�Q�Ɖ񐔂�+1����
	//
	lab=&mem_lab[id];
	lab->ref++;
}


int CLabel::GetReference( int id )
{
	//		�Q�Ɖ񐔂��擾����(�ˑ��֌W���܂߂�)
	//
	int total;
	LABREL *rel;
	lab=&mem_lab[id];
	total = lab->ref;
	rel = lab->rel;
	if ( rel != NULL ) {
		while(1) {
			total += GetReference( rel->rel_id );
			if ( rel->link == NULL ) break;
			rel = (LABREL *)rel->link;
		}
	}
	return total;
}


int CLabel::SearchRelation( int id, int rel_id )
{
	//		���x���ˑ��̓���ID�f�[�^�����邩������
	//		(0=�Ȃ�/1=����)
	//
	LABREL *tmp;
	lab=&mem_lab[id];
	tmp = lab->rel;
	if ( tmp == NULL ) return 0;
	while(1) {
		if ( tmp->link == NULL ) break;
		if ( tmp->rel_id == rel_id ) return 1;
		tmp = (LABREL *)tmp->link;
	}
	return 0;
}


void CLabel::AddRelation( int id, int rel_id )
{
	//		���x���ˑ���ID�f�[�^��ǉ�����
	//
	LABREL *rel;
	LABREL *tmp;

	if ( id == rel_id ) return;				// �z����悤�ȃf�[�^�͓o�^���Ȃ�

	rel = (LABREL *)ExpandSymbolBuffer( sizeof(LABREL) );
	rel->link = NULL;
	rel->rel_id = rel_id;

	lab=&mem_lab[id];
	if ( lab->rel == NULL ) {
		lab->rel = rel;
		return;
	}
	tmp = lab->rel;
	while(1) {
		if ( tmp->link == NULL ) break;
		tmp = (LABREL *)tmp->link;
	}
	tmp->link = rel;
}


void CLabel::AddRelation( char *name, int rel_id )
{
	int i;
	i = Search( name );
	if ( i < 0 ) return;
	AddRelation( i, rel_id );
}
