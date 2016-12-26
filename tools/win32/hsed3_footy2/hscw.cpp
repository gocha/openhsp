#include<Windows.h>
#ifdef UNICODE
typedef BOOL(CALLBACK *DLLFUNC)(int, int, int, int);
extern DLLFUNC hsc_ini;
extern DLLFUNC hsc_refname;
extern DLLFUNC hsc_objname;
extern DLLFUNC hsc_comp;
extern DLLFUNC hsc_getmes;
extern DLLFUNC hsc_clrmes;
extern DLLFUNC hsc_ver;
extern DLLFUNC hsc_bye;
extern DLLFUNC pack_ini;
extern DLLFUNC pack_make;
extern DLLFUNC pack_exe;
extern DLLFUNC pack_opt;
extern DLLFUNC pack_rt;
extern DLLFUNC hsc3_getsym;
extern DLLFUNC hsc3_make;
extern DLLFUNC hsc3_messize;
extern DLLFUNC hsc3_getruntime;
extern DLLFUNC hsc3_run;

static DLLFUNC hsc_ini_old;
static DLLFUNC hsc_refname_old;
static DLLFUNC hsc_objname_old;
static DLLFUNC hsc_comp_old;
static DLLFUNC hsc_getmes_old;
static DLLFUNC hsc_clrmes_old;
static DLLFUNC hsc_ver_old;
static DLLFUNC hsc_bye_old;
static DLLFUNC pack_ini_old;
static DLLFUNC pack_make_old;
static DLLFUNC pack_exe_old;
static DLLFUNC pack_opt_old;
static DLLFUNC pack_rt_old;
static DLLFUNC hsc3_getsym_old;
static DLLFUNC hsc3_make_old;
static DLLFUNC hsc3_messize_old;
static DLLFUNC hsc3_getruntime_old;
static DLLFUNC hsc3_run_old;

#define HSPAPICHAR wchar_t

static HSPAPICHAR *ansichartoapichar(const char *orig, HSPAPICHAR **pphac)
{

	int reslen;
	wchar_t *resw;
	reslen = MultiByteToWideChar(CP_ACP, 0, orig, -1, (LPWSTR)NULL, 0);
	resw = (wchar_t*)calloc(reslen + 1, sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, orig, -1, resw, reslen);
	*pphac = resw;
	return resw;
}

static char *apichartoansichar(const HSPAPICHAR *orig, char **ppac)
{
	int plen;
	char *p = 0;
	plen = WideCharToMultiByte(CP_ACP, NULL, orig, -1, NULL, 0, NULL, NULL);
	p = (char *)calloc(plen + 1, sizeof(char*));
	WideCharToMultiByte(CP_ACP, NULL, orig, -1, p, plen, NULL, NULL);
	*ppac = p;
	return p;
}

static void freehac(HSPAPICHAR **pphac)
{
	free(*pphac);
	*pphac = 0;
}
static void freeac(char **ppac)
{
	free(*ppac);
	*ppac = 0;
}
static BOOL CALLBACK hsc_ini_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1=0;
	//
	res = hsc_ini_old(p1,(int)apichartoansichar((const wchar_t*)p2,&actmp1),p3,p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc_refname_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1 = 0;
	//
	res = hsc_refname_old(p1,(int)apichartoansichar((const wchar_t*)p2, &actmp1), p3, p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc_objname_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1 = 0;
	//
	res = hsc_objname_old(p1, (int)apichartoansichar((const wchar_t*)p2, &actmp1), p3, p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc_comp_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = hsc_comp_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK hsc_getmes_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *p1i = 0;
	HSPAPICHAR *hactmp1 = 0;
	int messize;
	//
	hsc3_messize_old((int)&messize, 0, 0, 0);
	p1i = (char *)malloc((messize+1)*sizeof(wchar_t));
	res = hsc_getmes_old((int)p1i, p2, p3, p4);
	ansichartoapichar(p1i, &hactmp1);
	wcscpy((wchar_t *)p1, hactmp1);
	freehac(&hactmp1);
	return res;
}
static BOOL CALLBACK hsc_clrmes_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = hsc_clrmes_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK hsc_ver_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char p4i[4096];
	HSPAPICHAR *hactmp1 = 0;
	//
	res = hsc_ver_old(p1, p2, p3, (int)p4i);
	ansichartoapichar(p4i, &hactmp1);
	wcscpy((wchar_t *)p4, hactmp1);
	freehac(&hactmp1);
	return res;
}
static BOOL CALLBACK hsc_bye_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = hsc_bye_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK pack_ini_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1;
	//
	res = pack_ini_old((int)apichartoansichar((wchar_t *)p1,&actmp1), p2, p3, p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK pack_make_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = pack_make_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK pack_exe_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = pack_exe_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK pack_opt_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = pack_opt_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK pack_rt_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1;
	//
	res = pack_rt_old(p1, (int)apichartoansichar((wchar_t*)p2,&actmp1), p3, p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc3_getsym_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	//
	res = hsc3_getsym_old(p1, p2, p3, p4);
	return res;
}
static BOOL CALLBACK hsc3_make_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1;
	//
	res = hsc3_make_old(p1, (int)apichartoansichar((wchar_t*)p2,&actmp1), p3, p4);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc3_messize_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1=0;
	//
	res = hsc3_messize_old(p1, (int)apichartoansichar( (wchar_t*)p2,&actmp1), p3, p4);
	freeac(&actmp1);
	return res;
}

static BOOL CALLBACK hsc3_getruntime_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1;
	HSPAPICHAR *hactmp1=0;
	char p1i[256];
	//
	res = hsc3_getruntime_old((int)p1i, (int)apichartoansichar( (wchar_t*)p2,&actmp1), p3, p4);
	wcscpy((wchar_t *)p1,ansichartoapichar( p1i, &hactmp1));
	freehac(&hactmp1);
	freeac(&actmp1);
	return res;
}
static BOOL CALLBACK hsc3_run_w(int p1, int p2, int p3, int p4)
{
	BOOL res;
	char *actmp1;
	//
	res = hsc3_run_old((int)apichartoansichar((wchar_t*)p1, &actmp1), p2, p3, p4);
	freeac(&actmp1);
	return res;
}

void wraphscw(void)
{

	hsc_ini_old = hsc_ini;
	hsc_refname_old = hsc_refname;
	hsc_objname_old = hsc_objname;
	hsc_comp_old = hsc_comp;
	hsc_getmes_old = hsc_getmes;
	hsc_clrmes_old = hsc_clrmes;
	hsc_ver_old = hsc_ver;
	hsc_bye_old = hsc_bye;
	pack_ini_old = pack_ini;
	pack_make_old = pack_make;
	pack_exe_old = pack_exe;
	pack_opt_old = pack_opt;
	pack_rt_old = pack_rt;
	hsc3_getsym_old = hsc3_getsym;
	hsc3_make_old = hsc3_make;
	hsc3_messize_old = hsc3_messize;
	hsc3_getruntime_old = hsc3_getruntime;
	hsc3_run_old = hsc3_run;
	hsc_ini = hsc_ini_w;
	hsc_refname = hsc_refname_w;
	hsc_objname = hsc_objname_w;
	hsc_comp = hsc_comp_w;
	hsc_getmes = hsc_getmes_w;
	hsc_clrmes = hsc_clrmes_w;
	hsc_ver = hsc_ver_w;
	hsc_bye = hsc_bye_w;
	pack_ini = pack_ini_w;
	pack_make = pack_make_w;
	pack_exe = pack_exe_w;
	pack_opt = pack_opt_w;
	pack_rt = pack_rt_w;
	hsc3_getsym = hsc3_getsym_w;
	hsc3_make = hsc3_make_w;
	hsc3_messize = hsc3_messize_w;
	hsc3_getruntime = hsc3_getruntime_w;
	hsc3_run = hsc3_run_w;
}

#endif