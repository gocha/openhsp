
//
//	HSP3 C++ runtime manager
//	onion software/onitama 2008/5
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hsp3r.h"
#include "../hsp3/hsp3config.h"
#include "../hsp3/hsp3debug.h"
#include "../hsp3/dpmread.h"
#include "../hsp3/supio.h"

/*------------------------------------------------------------*/
/*
		constructor
*/
/*------------------------------------------------------------*/

Hsp3r::Hsp3r()
{
	//		初期化
	//
	memset( &hspctx, 0, sizeof(HSPCTX) );
	code_setctx( &hspctx );
	code_init();
	hspctx.mem_mcs = NULL;
}

Hsp3r::~Hsp3r()
{
	//		すべて破棄
	//
	code_termfunc();
	Dispose();
	code_bye();
	VarUtilTerm();
}

/*------------------------------------------------------------*/
/*
		interface
*/
/*------------------------------------------------------------*/

void Hsp3r::Dispose( void )
{
	//		axを破棄
	//
	if ( hspctx.mem_var != NULL ) {
		int i;
		for(i=0;i<maxvar;i++) {
			HspVarCoreDispose( &hspctx.mem_var[i] );
		}
		delete [] hspctx.mem_var;	hspctx.mem_var = NULL;
	}
}

int Hsp3r::Reset( int ext_vars, int ext_hpi )
{
	//		HSP3Rを初期化
	//			ext_vars = 変数IDの数
	//			ext_hpi  = 拡張HPIの数
	//
//	int i;
//	char *ptr;
//	char fname[512];
	if ( hspctx.mem_mcs != NULL ) Dispose();

	//		load HSP execute object
	//
	dpm_ini( "data.dpm",0,-1,-1 );				// original EXE mode

	maxvar = ext_vars;
	max_varhpi = ext_hpi;
	hspctx.mem_mcs = (unsigned short *)this;
/*
	hspctx.hsphed = hsphed;
	hspctx.mem_mcs = (unsigned short *)( ptr + hsphed->pt_cs );
	hspctx.mem_mds = (char *)( ptr + hsphed->pt_ds );
	hspctx.mem_ot = (int *)( ptr + hsphed->pt_ot );
	hspctx.mem_di = (unsigned char *)( ptr + hsphed->pt_dinfo );

	hspctx.mem_linfo = (LIBDAT *)( ptr + hsphed->pt_linfo );
	hspctx.mem_minfo = (STRUCTPRM *)( ptr + hsphed->pt_minfo );
	hspctx.mem_finfo = (STRUCTDAT *)( ptr + hsphed->pt_finfo );
*/
	code_resetctx( &hspctx );		// hsp3code setup
	HspVarCoreResetVartype( max_varhpi );		// 型の初期化

	//		HspVar setup
	hspctx.mem_var = NULL;
	if ( maxvar ) {
		int i;
		hspctx.mem_var = new PVal[maxvar];

		for(i=0;i<maxvar;i++) {
			PVal *pval = &hspctx.mem_var[i];
			pval->mode = HSPVAR_MODE_NONE;
			pval->flag = HSPVAR_FLAG_INT;				// 仮の型
			HspVarCoreClear( pval, HSPVAR_FLAG_INT );	// グローバル変数を0にリセット
		}
	}

	return 0;
}


void Hsp3r::SetPackValue( int sum, int dec )
{
	hsp_sum = sum;
	hsp_dec = dec;
}


