/*------------------------------------------------------------------------------
	Editor configration routines for HSP Script Editor
------------------------------------------------------------------------------*/
#include <windows.h>
#include <string.h>
#include <tchar.h>

#include "hsed_config.h"
#include "poppad.h"
#include "config.h"
#include "classify.h"
#include "support.h"
#include "exttool.h"

// Global variables
static TCHAR szIniFileName[_MAX_PATH + 1];

// Variable changed by this program
extern TCHAR	    hsp_cmdopt[TMPSIZE];
extern TCHAR	    hsp_laststr[TMPSIZE];
extern TCHAR	    hsp_helpdir[TMPSIZE];
extern int      hscroll_flag;
extern int      hsp_wx;
extern int      hsp_wy;
extern int      hsp_wd;
extern int      hsp_orgpath;
extern int	    hsp_debug;
extern int	    hsp_extobj;
extern TCHAR	    hsp_extstr[TMPSIZE];
extern int	    hsp_helpmode;
extern int	    hsp_logmode;
extern int	    hsp_logadd;
extern int      hsp_extmacro;
extern int      hsp_clmode;
extern int	    startflag;
extern TCHAR     startdir[_MAX_PATH];
extern LOGFONT  chg_font;
extern int      flg_statbar;
extern int      flg_toolbar;
extern int		flg_hspat;
extern TCHAR     hdir[_MAX_PATH];
extern TCHAR     helpopt[TMPSIZE];
extern int      hsp_fullscr;
extern int      posx;
extern int      posy;
extern int      winflg;
extern int      winx;
extern int      winy;
extern MYCOLOR  color;
extern LOGFONT	tchg_font;
extern int      tabEnabled;
extern int      hsEnabled;
extern int      fsEnabled;
extern int      nlEnabled;
extern int      eofEnabled;
extern int      ulEnabled;
extern int      tabsize;
extern int      rulerheight;
extern int      linewidth;
extern int      linespace;
extern FileList filelist;
extern int      ColumnWidth[2];
extern bool	    bUseIni;
extern BOOL     bAutoIndent;

static int      hsed_ver;
static int      hsed_private_ver;

// Registry I/O routines
static int reg_getkey( HKEY, LPTSTR, int * );
static int reg_sgetkey( HKEY, LPTSTR, LPTSTR, unsigned long );
static int reg_bgetkey( HKEY, LPTSTR, BYTE *, int );
static void reg_setkey( HKEY, LPTSTR, int );
static void reg_ssetkey( HKEY, LPTSTR , LPTSTR );
static void reg_bsetkey( HKEY, LPTSTR, BYTE *, int );
static void reg_save( void );
static void reg_load( void );

// INI file I/O routines
static inline void ini_getkey( LPCTSTR, LPCTSTR, LPTSTR , int * );
static inline DWORD ini_sgetkey( LPCTSTR, LPCTSTR,LPTSTR , LPTSTR , int );
static int ini_bgetkey( LPCTSTR, LPCTSTR, LPTSTR , BYTE *, int );
static void ini_setkey( LPCTSTR, LPCTSTR, LPTSTR , int );
static inline void ini_ssetkey( LPCTSTR, LPCTSTR, LPTSTR , LPTSTR  );
static void ini_bsetkey( LPCTSTR, LPCTSTR, LPTSTR , BYTE *, int );
static void ini_save( void );
static void ini_load( void );

// Functions in main.cpp
int CheckWndFlag ( void );

// Global variable in main.cpp
extern TCHAR szExeDir[_MAX_PATH];

// Functions in poppad.cpp
int fileok( LPTSTR fname );
void gethdir( void );

// Functions in popfont.cpp
LOGFONT PopFontGetELG ( void );
LOGFONT PopFontGetTLG( void );
void PopFontMakeFont( LOGFONT *pLogFont, LPCTSTR fonname, int fpts, int fopt, int angle );

void LoadConfig()
{
	HKEY hKey;
	int nTemp = 0;

	TCHAR szFileName[_MAX_PATH + 1];
	wsprintf(szFileName, TEXT("%s\\%s"), szExeDir, INI_FILE);

	bUseIni = false;

	if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX, 0, KEY_READ, &hKey) == ERROR_SUCCESS){
		reg_getkey(hKey, TEXT("useini"), &nTemp);
		if(nTemp)
			bUseIni = true;
		RegCloseKey(hKey);
	}
	else if(!fileok(szFileName))
		bUseIni = true;

	if(bUseIni)
		ini_load();
	else
		reg_load();
	return;
}

void SaveConfig()
{
	HKEY hKey;

	if(bUseIni){
		ini_save();
		if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS){
			reg_setkey(hKey, TEXT("useini"), TRUE);
			RegCloseKey(hKey);
		}
	}
	else
		reg_save();
	return;
}

/*
		Registry I/O routines
*/

static int reg_getkey( HKEY hKey, LPTSTR readkey, int *value )
{
	unsigned long RVSize = 4;
	DWORD	RVal, RKind = REG_DWORD;
	if (RegQueryValueEx(hKey, readkey, NULL, &RKind, (BYTE *)(&RVal), &RVSize) == ERROR_SUCCESS) {
		*value=RVal;
		return 0;
	}
	else return -1;
}

static int reg_sgetkey( HKEY hKey, LPTSTR readkey, LPTSTR strbuf, unsigned long RVSize )
{
	DWORD	RKind = REG_SZ;
	if (RegQueryValueEx(hKey, readkey, NULL, &RKind, (BYTE *)strbuf, &RVSize) == ERROR_SUCCESS)
	return 0;
	else return -1;
}

static int reg_bgetkey( HKEY hKey, LPTSTR readkey, BYTE *buf, int length )
{
	unsigned long RVSize;
	DWORD	RKind = REG_BINARY;
	RVSize=(unsigned long)length;
	if (RegQueryValueEx(hKey, readkey, NULL, &RKind, buf, &RVSize) == ERROR_SUCCESS)
	return 0;
	else return -1;
}

static void reg_setkey( HKEY hKey, LPTSTR writekey, int value )
{
	int		RVSize = 4;
	DWORD	dw = REG_DWORD;
	RegSetValueEx(hKey, writekey, 0, dw, (BYTE*)&value, RVSize);
}

static void reg_ssetkey( HKEY hKey, LPTSTR writekey, LPTSTR string )
{
	int		RVSize = 128;
	DWORD	sz = REG_SZ;
	RegSetValueEx(hKey, writekey, 0, sz, (BYTE*)string, RVSize);
}

static void reg_bsetkey( HKEY hKey, LPTSTR writekey, BYTE *buf, int length )
{
	RegSetValueEx(hKey, writekey, 0, REG_BINARY, buf, length);
}

static DWORD reg_getsize( HKEY hKey, LPTSTR readkey )
{
	DWORD dwType = REG_BINARY, nSize;

	RegQueryValueEx(hKey, readkey, NULL, &dwType, NULL, &nSize);
	return nSize;
}

/* DEFCOLOR_*は、classify.hにあります。 */
void DefaultColor(MYCOLOR *dest)
{
	ZeroMemory(dest, sizeof(MYCOLOR));
	dest->Character.Default.Conf       = DEFCOLOR_FONT;
	dest->Character.String.Conf        = DEFCOLOR_STRING;
	dest->Character.Function.Conf      = DEFCOLOR_FUNC;
	dest->Character.Preprocessor.Conf  = DEFCOLOR_PREPROCESSOR;
	dest->Character.Macro.Conf         = DEFCOLOR_MACRO;
	dest->Character.Comment.Conf       = DEFCOLOR_COMMENT;
	dest->Character.Label.Conf         = DEFCOLOR_LABEL;
	dest->NonCharacter.HalfSpace.Conf  = DEFCOLOR_HALF_SPACE;
	dest->NonCharacter.FullSpace.Conf  = DEFCOLOR_FULL_SPACE;
	dest->NonCharacter.Tab.Conf        = DEFCOLOR_TAB;
	dest->NonCharacter.NewLine.Conf    = DEFCOLOR_NEWLINE;
	dest->NonCharacter.EndOfFile.Conf  = DEFCOLOR_EOF;
	dest->Edit.Background.Conf         = DEFCOLOR_BACKGROUND;
	dest->Edit.CaretUnderLine.Conf     = DEFCOLOR_CARET_UNDERLINE;
	dest->Edit.BoundaryLineNumber.Conf = DEFCOLOR_BOUNDARY_LINENUM;
	dest->LineNumber.Number.Conf       = DEFCOLOR_LINENUM;
	dest->LineNumber.CaretLine.Conf    = DEFCOLOR_CARET_LINE;
	dest->Ruler.Number.Conf            = DEFCOLOR_RULER_FONT;
	dest->Ruler.Background.Conf        = DEFCOLOR_RULER_BACKGROUND;
	dest->Ruler.Division.Conf          = DEFCOLOR_RULER_DIVISION;
	dest->Ruler.Caret.Conf             = DEFCOLOR_RULER_CARET;
}

void DefaultFont(LOGFONT *editfont, LOGFONT *tabfont)
{
	//GetObject (GetStockObject(SYSTEM_FIXED_FONT), sizeof(LOGFONT), (PSTR)editfont);
	PopFontMakeFont( editfont, TEXT("ＭＳ ゴシック"), 14, 0, 0 );
	
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
	*tabfont = ncm.lfMenuFont;	
}

static void DefaultExtToolInfo(EXTTOOLINFO *lpExtToolInfo)
{
	lstrcpy(lpExtToolInfo->ToolName, TEXT(""));
	lstrcpy(lpExtToolInfo->FileName, TEXT(""));
	lstrcpy(lpExtToolInfo->CmdLine, TEXT(""));
	lstrcpy(lpExtToolInfo->WorkDir, TEXT(""));
	lpExtToolInfo->ShowOnMainMenu    = true;
	lpExtToolInfo->ShowOnPopupMenu   = false;
	lpExtToolInfo->ExecOnStartup     = false;
	lpExtToolInfo->ExecWithOverwrite = false;
	return;
}

static void for_obsolete( HKEY hKey )
{
	MYCOLORREF crObsoleteColor[19];
	int nSize;

	nSize = reg_getsize(hKey, TEXT("color"));
	if(nSize == 19 * sizeof(MYCOLORREF)){ // - 1.02b3
		reg_bgetkey(hKey, TEXT("color"), (BYTE *)crObsoleteColor, sizeof(crObsoleteColor));
		CopyMemory(&color, crObsoleteColor, sizeof(MYCOLORREF) * 2);
		CopyMemory(((MYCOLORREF *)&color) + 4, crObsoleteColor + 2, sizeof(MYCOLORREF) * 17);        
	} else if(nSize == 21 * sizeof(MYCOLORREF)){ // 1.02b4
		reg_bgetkey(hKey, TEXT("color"), (BYTE *)&color, sizeof(MYCOLOR));
	}
}

static void set_default( void )
{
	//		デフォルトの設定を行なう(onitama追加:050218)
	//
	hsp_cmdopt[0]=0;
	hsp_laststr[0]=0;
	hscroll_flag=1;
	hsp_helpdir[0]=0;
	hsp_wx=640;hsp_wy=480;
	hsp_wd=0;
	hsp_orgpath=0;
	hsp_debug=0;
	hsp_extobj=0;
	hsp_extstr[0]=0;
	hsp_helpmode=2;
	hsp_logmode = 15;
	hsp_logadd = 1;
	hsp_extmacro = 1;
	hsp_clmode = 0;
	hsed_ver = 0;
	hsed_private_ver = 0;
	startflag = STARTDIR_MYDOC;
	startdir[0] = 0;

	tabEnabled = FALSE;
	hsEnabled  = FALSE;
	fsEnabled  = FALSE;
	nlEnabled  = FALSE;
	eofEnabled = TRUE;
	ulEnabled  = TRUE;
	tabsize = 4;
	rulerheight = 10;
	linewidth = 50;
	linespace = 2;

	flg_statbar = 1;
	flg_toolbar = 1;
	flg_hspat = 1;

	bAutoIndent = TRUE;

	ColumnWidth[0] = 120;
	ColumnWidth[1] = 280;

	DefaultColor(&color);
	DefaultFont(&chg_font, &tchg_font);
}


static void reg_save( void )
{
	//		レジストリに書き込む
	//
	HKEY	hKey;
	int		/*RVSize = 4, */nSize, i;
//	DWORD	dw = REG_DWORD;
//	DWORD	sz = REG_SZ;
	EXTTOOLINFO *lpExtToolInfo;
	TCHAR szKeyName[256];

	RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX, 0, TEXT(""), 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	reg_setkey( hKey,TEXT("fullscr"), hsp_fullscr );
	reg_setkey( hKey,TEXT("hscroll"), hscroll_flag );
	reg_ssetkey( hKey,TEXT("cmdopt"), hsp_cmdopt );
	reg_ssetkey( hKey,TEXT("laststr"), hsp_laststr );
	chg_font=PopFontGetELG();
	reg_bsetkey(hKey,TEXT("font"), (BYTE *)&chg_font, sizeof(LOGFONT) );
	tchg_font=PopFontGetTLG();
	reg_bsetkey( hKey,TEXT("tabfont"), (BYTE *)&tchg_font, sizeof(LOGFONT) );

	CheckWndFlag();						// Window attribute check
	reg_setkey( hKey,TEXT("winflg"), winflg );

	if (winflg==0) {
		reg_setkey( hKey,TEXT("winx"), winx );
		reg_setkey( hKey,TEXT("winy"), winy );
		reg_setkey( hKey,TEXT("posx"), posx );
		reg_setkey( hKey,TEXT("posy"), posy );
	}

	reg_setkey( hKey,TEXT("toolbar"), flg_toolbar );
	reg_setkey( hKey,TEXT("statbar"), flg_statbar );
	reg_setkey( hKey,TEXT("hspat"), flg_hspat );
	reg_ssetkey( hKey,TEXT("helpdir"), hsp_helpdir );
	reg_setkey( hKey,TEXT("exewx"), hsp_wx );
	reg_setkey( hKey,TEXT("exewy"), hsp_wy );
	reg_setkey( hKey,TEXT("exewd"), hsp_wd );
	reg_setkey( hKey,TEXT("debug"), hsp_debug );
	reg_setkey( hKey,TEXT("extobj"), hsp_extobj );
	reg_ssetkey( hKey,TEXT("extstr"), hsp_extstr );
	reg_setkey( hKey,TEXT("helpmode"), hsp_helpmode );
	reg_setkey( hKey,TEXT("logmode"), hsp_logmode );
	reg_setkey( hKey,TEXT("logadd"), hsp_logadd );
	reg_setkey( hKey,TEXT("hsedver"), hsed_ver );
	reg_setkey( hKey,TEXT("hsedprivatever"), hsed_private_ver );
	reg_setkey( hKey,TEXT("extmacro"), hsp_extmacro );
	reg_setkey( hKey,TEXT("clmode"), hsp_clmode );
	reg_setkey( hKey,TEXT("orgpath"), hsp_orgpath );

	reg_setkey( hKey,TEXT("startmode"), startflag );
	reg_ssetkey( hKey,TEXT("startdir"), startdir );
	
	reg_setkey( hKey,TEXT("tabenabled"),tabEnabled );
	reg_setkey( hKey,TEXT("hsenabled"), hsEnabled );
	reg_setkey( hKey,TEXT("fsenabled"), fsEnabled );
	reg_setkey( hKey,TEXT("nlenabled"), nlEnabled );
	reg_setkey( hKey,TEXT("eofenabled"), eofEnabled );
	reg_setkey( hKey,TEXT("underlineenabled"), ulEnabled );
	reg_setkey( hKey,TEXT("tabsize"), tabsize );
	reg_setkey( hKey,TEXT("rulerheight"), rulerheight );
	reg_setkey( hKey,TEXT("linewidth"), linewidth );
	reg_setkey( hKey,TEXT("linespace"), linespace );

	reg_setkey( hKey,TEXT("column1width"), ColumnWidth[0] );
	reg_setkey( hKey,TEXT("column2width"), ColumnWidth[1] );

	reg_ssetkey( hKey,TEXT("keyfile"), (LPTSTR )filelist.getlist() );
	reg_setkey( hKey,TEXT("useini"), FALSE );

	reg_setkey( hKey, TEXT("autoindent"), bAutoIndent );

	RegCloseKey(hKey);

	RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\Color"), 0, TEXT(""), 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	reg_setkey( hKey, TEXT("Default"), color.Character.Default.Conf );
	reg_setkey( hKey, TEXT("String"), color.Character.String.Conf );
	reg_setkey( hKey, TEXT("Function"), color.Character.Function.Conf );
	reg_setkey( hKey, TEXT("PreProcessor"), color.Character.Preprocessor.Conf );
	reg_setkey( hKey, TEXT("Macro"), color.Character.Macro.Conf );
	reg_setkey( hKey, TEXT("Comment"), color.Character.Comment.Conf );
	reg_setkey( hKey, TEXT("Label"), color.Character.Label.Conf );
	reg_setkey( hKey, TEXT("HalfSpace"), color.NonCharacter.HalfSpace.Conf );
	reg_setkey( hKey, TEXT("FullSpace"), color.NonCharacter.FullSpace.Conf );
	reg_setkey( hKey, TEXT("Tab"), color.NonCharacter.Tab.Conf );
	reg_setkey( hKey, TEXT("NewLine"), color.NonCharacter.NewLine.Conf );
	reg_setkey( hKey, TEXT("EOF"), color.NonCharacter.EndOfFile.Conf );
	reg_setkey( hKey, TEXT("BackGround"), color.Edit.Background.Conf );
	reg_setkey( hKey, TEXT("UnderLine"), color.Edit.CaretUnderLine.Conf );
	reg_setkey( hKey, TEXT("BoundaryLineNum"), color.Edit.BoundaryLineNumber.Conf );
	reg_setkey( hKey, TEXT("LineNum"), color.LineNumber.Number.Conf );
	reg_setkey( hKey, TEXT("LineNumCaret"), color.LineNumber.CaretLine.Conf );
	reg_setkey( hKey, TEXT("RulerNum"), color.Ruler.Number.Conf );
	reg_setkey( hKey, TEXT("RulerBackGround"), color.Ruler.Background.Conf );
	reg_setkey( hKey, TEXT("RulerDivision"), color.Ruler.Division.Conf );
	reg_setkey( hKey, TEXT("RulerCaret"), color.Ruler.Caret.Conf );
	RegCloseKey(hKey);

	RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\UserColor"), 0, TEXT(""), 
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	reg_setkey( hKey, TEXT("Default"), color.Character.Default.Combo );
	reg_setkey( hKey, TEXT("String"), color.Character.String.Combo );
	reg_setkey( hKey, TEXT("Function"), color.Character.Function.Combo );
	reg_setkey( hKey, TEXT("PreProcessor"), color.Character.Preprocessor.Combo );
	reg_setkey( hKey, TEXT("Macro"), color.Character.Macro.Combo );
	reg_setkey( hKey, TEXT("Comment"), color.Character.Comment.Combo );
	reg_setkey( hKey, TEXT("Label"), color.Character.Label.Combo );
	reg_setkey( hKey, TEXT("HalfSpace"), color.NonCharacter.HalfSpace.Combo );
	reg_setkey( hKey, TEXT("FullSpace"), color.NonCharacter.FullSpace.Combo );
	reg_setkey( hKey, TEXT("Tab"), color.NonCharacter.Tab.Combo );
	reg_setkey( hKey, TEXT("NewLine"), color.NonCharacter.NewLine.Combo );
	reg_setkey( hKey, TEXT("EOF"), color.NonCharacter.EndOfFile.Combo );
	reg_setkey( hKey, TEXT("BackGround"), color.Edit.Background.Combo );
	reg_setkey( hKey, TEXT("UnderLine"), color.Edit.CaretUnderLine.Combo );
	reg_setkey( hKey, TEXT("BoundaryLineNum"), color.Edit.BoundaryLineNumber.Combo );
	reg_setkey( hKey, TEXT("LineNum"), color.LineNumber.Number.Combo );
	reg_setkey( hKey, TEXT("LineNumCaret"), color.LineNumber.CaretLine.Combo );
	reg_setkey( hKey, TEXT("RulerNum"), color.Ruler.Number.Combo );
	reg_setkey( hKey, TEXT("RulerBackGround"), color.Ruler.Background.Combo );
	reg_setkey( hKey, TEXT("RulerDivision"), color.Ruler.Division.Combo );
	reg_setkey( hKey, TEXT("RulerCaret"), color.Ruler.Caret.Combo );
	RegCloseKey(hKey);

	RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\ExtTools"), 0, TEXT(""),
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);

	nSize = GetExtToolSize();
	reg_setkey( hKey, TEXT("numoftools"), nSize );
	for(i = 1; i <= nSize; i++){
		lpExtToolInfo = GetExtTool(i - 1);
		if(lpExtToolInfo->Used){
			wsprintf(szKeyName, TEXT("toolname%d"), i);
			reg_ssetkey( hKey, szKeyName, lpExtToolInfo->ToolName);
			wsprintf(szKeyName, TEXT("filename%d"), i);
			reg_ssetkey( hKey, szKeyName, lpExtToolInfo->FileName);
			wsprintf(szKeyName, TEXT("cmdline%d"), i);
			reg_ssetkey( hKey, szKeyName, lpExtToolInfo->CmdLine);
			wsprintf(szKeyName, TEXT("workdir%d"), i);
			reg_ssetkey( hKey, szKeyName, lpExtToolInfo->WorkDir);
			wsprintf(szKeyName, TEXT("mainmenu%d"), i);
			reg_setkey( hKey, szKeyName, lpExtToolInfo->ShowOnMainMenu);
			wsprintf(szKeyName, TEXT("popupmenu%d"), i);
			reg_setkey( hKey, szKeyName, lpExtToolInfo->ShowOnPopupMenu);
			wsprintf(szKeyName, TEXT("startup%d"), i);
			reg_setkey( hKey, szKeyName, lpExtToolInfo->ExecOnStartup);
			wsprintf(szKeyName, TEXT("overwrite%d"), i);
			reg_setkey( hKey, szKeyName, lpExtToolInfo->ExecWithOverwrite);
		} else {
			wsprintf(szKeyName, TEXT("toolname%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("filename%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("workdir%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("mainmenu%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("popupmenu%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("startup%d"), i);
			RegDeleteValue( hKey, szKeyName );
			wsprintf(szKeyName, TEXT("overwrite%d"), i);
			RegDeleteValue( hKey, szKeyName );
		}
	}


	RegCloseKey(hKey);
}

static void reg_load( void )
{
	//		レジストリから読み込む
	//
	HKEY	hKey;
	TCHAR    szKeyFile[32000] = TEXT(""), szKeyName[1280];
	EXTTOOLINFO ExtToolInfo;
	int     nTemp, nSize, i;

	//		Reset to default value

	set_default();

	//		Read keys

	if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX, 0,
		KEY_READ, &hKey) == ERROR_SUCCESS) {
			reg_getkey( hKey,TEXT("fullscr"), &hsp_fullscr );
			reg_getkey( hKey,TEXT("hscroll"), &hscroll_flag );
			reg_sgetkey( hKey,TEXT("cmdopt"), hsp_cmdopt, sizeof(hsp_cmdopt) );
			reg_sgetkey( hKey,TEXT("laststr"), hsp_laststr, sizeof(hsp_laststr) );
			reg_bgetkey( hKey,TEXT("font"), (BYTE *)&chg_font, sizeof(LOGFONT) );
			reg_bgetkey( hKey,TEXT("tabfont"), (BYTE *)&tchg_font, sizeof(LOGFONT) );
			reg_getkey( hKey,TEXT("winflg"), &winflg );
			reg_getkey( hKey,TEXT("winx"), &winx );
			reg_getkey( hKey,TEXT("winy"), &winy );
			reg_getkey( hKey,TEXT("posx"), &posx );
			reg_getkey( hKey,TEXT("posy"), &posy );
			reg_getkey( hKey,TEXT("toolbar"), &flg_toolbar );
			reg_getkey( hKey,TEXT("statbar"), &flg_statbar );
			reg_getkey( hKey,TEXT("hspat"), &flg_hspat );
			reg_sgetkey( hKey,TEXT("helpdir"), hsp_helpdir, sizeof(hsp_helpdir) );
			reg_getkey( hKey,TEXT("exewx"), &hsp_wx );
			reg_getkey( hKey,TEXT("exewy"), &hsp_wy );
			reg_getkey( hKey,TEXT("exewd"), &hsp_wd );
			reg_getkey( hKey,TEXT("debug"), &hsp_debug );
			reg_sgetkey( hKey,TEXT("extstr"), hsp_extstr, sizeof(hsp_extstr) );
			reg_getkey( hKey,TEXT("extobj"), &hsp_extobj );
			reg_getkey( hKey,TEXT("helpmode"), &hsp_helpmode );
			reg_getkey( hKey,TEXT("logmode"), &hsp_logmode );
			reg_getkey( hKey,TEXT("logadd"), &hsp_logadd );
			reg_getkey( hKey,TEXT("extmacro"), &hsp_extmacro );
			reg_getkey( hKey,TEXT("clmode"), &hsp_clmode );
			reg_getkey( hKey,TEXT("orgpath"), &hsp_orgpath );

			reg_getkey( hKey,TEXT("startmode"), &startflag );
			reg_sgetkey( hKey,TEXT("startdir"), startdir, sizeof(startdir) );
			reg_getkey( hKey,TEXT("tabenabled"),&tabEnabled );
			reg_getkey( hKey,TEXT("hsenabled"), &hsEnabled );
			reg_getkey( hKey,TEXT("fsenabled"), &fsEnabled );
			reg_getkey( hKey,TEXT("nlenabled"), &nlEnabled );
			reg_getkey( hKey,TEXT("eofenabled"), &eofEnabled );
			reg_getkey( hKey,TEXT("underlineenabled"), &ulEnabled );
			reg_getkey( hKey,TEXT("tabsize"), &tabsize );
			reg_getkey( hKey,TEXT("rulerheight"), &rulerheight );
			reg_getkey( hKey,TEXT("linewidth"), &linewidth );
			reg_getkey( hKey,TEXT("linespace"), &linespace );

			reg_getkey( hKey,TEXT("autoindent"), &bAutoIndent );
			
			reg_getkey( hKey,TEXT("column1width"), &ColumnWidth[0] );
			reg_getkey( hKey,TEXT("column2width"), &ColumnWidth[1] );

			for_obsolete( hKey );

			reg_sgetkey( hKey, TEXT("keyfile"), szKeyFile, sizeof(szKeyFile) );
			filelist.setlist(szKeyFile);

			if ( reg_getkey( hKey,TEXT("hsedver"), &hsed_ver ) ) {
				hsp_helpmode=2;
			}
			reg_getkey( hKey,TEXT("hsedprivatever"), &hsed_private_ver );

			RegCloseKey(hKey);
	}

	if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\Color"),
		0, KEY_READ, &hKey) == ERROR_SUCCESS){
			reg_getkey( hKey, TEXT("Default"), (int *)&(color.Character.Default.Conf) );
			reg_getkey( hKey, TEXT("String"), (int *)&(color.Character.String.Conf) );
			reg_getkey( hKey, TEXT("Function"), (int *)&(color.Character.Function.Conf) );
			reg_getkey( hKey, TEXT("PreProcessor"), (int *)&(color.Character.Preprocessor.Conf) );
			reg_getkey( hKey, TEXT("Macro"), (int *)&(color.Character.Macro.Conf) );
			reg_getkey( hKey, TEXT("Comment"), (int *)&(color.Character.Comment.Conf) );
			reg_getkey( hKey, TEXT("Label"), (int *)&(color.Character.Label.Conf) );
			reg_getkey( hKey, TEXT("HalfSpace"), (int *)&(color.NonCharacter.HalfSpace.Conf) );
			reg_getkey( hKey, TEXT("FullSpace"), (int *)&(color.NonCharacter.FullSpace.Conf) );
			reg_getkey( hKey, TEXT("Tab"), (int *)&(color.NonCharacter.Tab.Conf) );
			reg_getkey( hKey, TEXT("NewLine"), (int *)&(color.NonCharacter.NewLine.Conf) );
			reg_getkey( hKey, TEXT("EOF"), (int *)&(color.NonCharacter.EndOfFile.Conf) );
			reg_getkey( hKey, TEXT("BackGround"), (int *)&(color.Edit.Background.Conf) );
			reg_getkey( hKey, TEXT("UnderLine"), (int *)&(color.Edit.CaretUnderLine.Conf) );
			reg_getkey( hKey, TEXT("BoundaryLineNum"), (int *)&(color.Edit.BoundaryLineNumber.Conf) );
			reg_getkey( hKey, TEXT("LineNum"), (int *)&(color.LineNumber.Number.Conf) );
			reg_getkey( hKey, TEXT("LineNumCaret"), (int *)&(color.LineNumber.CaretLine.Conf) );
			reg_getkey( hKey, TEXT("RulerNum"), (int *)&(color.Ruler.Number.Conf) );
			reg_getkey( hKey, TEXT("RulerBackGround"), (int *)&(color.Ruler.Background.Conf) );
			reg_getkey( hKey, TEXT("RulerDivision"), (int *)&(color.Ruler.Division.Conf) );
			reg_getkey( hKey, TEXT("RulerCaret"), (int *)&(color.Ruler.Caret.Conf) );

			RegCloseKey(hKey);
	}

	if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\UserColor"), 
		0, KEY_READ, &hKey) == ERROR_SUCCESS){
			reg_getkey( hKey, TEXT("Default"), (int *)&(color.Character.Default.Combo) );
			reg_getkey( hKey, TEXT("String"), (int *)&(color.Character.String.Combo) );
			reg_getkey( hKey, TEXT("Function"), (int *)&(color.Character.Function.Combo) );
			reg_getkey( hKey, TEXT("PreProcessor"), (int *)&(color.Character.Preprocessor.Combo) );
			reg_getkey( hKey, TEXT("Macro"), (int *)&(color.Character.Macro.Combo) );
			reg_getkey( hKey, TEXT("Comment"), (int *)&(color.Character.Comment.Combo) );
			reg_getkey( hKey, TEXT("Label"), (int *)&(color.Character.Label.Combo) );
			reg_getkey( hKey, TEXT("HalfSpace"), (int *)&(color.NonCharacter.HalfSpace.Combo) );
			reg_getkey( hKey, TEXT("FullSpace"), (int *)&(color.NonCharacter.FullSpace.Combo) );
			reg_getkey( hKey, TEXT("Tab"), (int *)&(color.NonCharacter.Tab.Combo) );
			reg_getkey( hKey, TEXT("NewLine"), (int *)&(color.NonCharacter.NewLine.Combo) );
			reg_getkey( hKey, TEXT("EOF"), (int *)&(color.NonCharacter.EndOfFile.Combo) );
			reg_getkey( hKey, TEXT("BackGround"), (int *)&(color.Edit.Background.Combo) );
			reg_getkey( hKey, TEXT("UnderLine"), (int *)&(color.Edit.CaretUnderLine.Combo) );
			reg_getkey( hKey, TEXT("BoundaryLineNum"), (int *)&(color.Edit.BoundaryLineNumber.Combo) );
			reg_getkey( hKey, TEXT("LineNum"), (int *)&(color.LineNumber.Number.Combo) );
			reg_getkey( hKey, TEXT("LineNumCaret"), (int *)&(color.LineNumber.CaretLine.Combo) );
			reg_getkey( hKey, TEXT("RulerNum"), (int *)&(color.Ruler.Number.Combo) );
			reg_getkey( hKey, TEXT("RulerBackGround"), (int *)&(color.Ruler.Background.Combo) );
			reg_getkey( hKey, TEXT("RulerDivision"), (int *)&(color.Ruler.Division.Combo) );
			reg_getkey( hKey, TEXT("RulerCaret"), (int *)&(color.Ruler.Caret.Combo) );

			RegCloseKey(hKey);
	}

	if(RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\OnionSoftware\\hsed") REG_SUFFIX TEXT("\\ExtTools"),
		0, KEY_READ, &hKey) == ERROR_SUCCESS){
			nSize = 0;
			reg_getkey( hKey, TEXT("numoftools"), &nSize );
			InitExtTool(nSize);
			for(i = 1; i <= nSize; i++){
				DefaultExtToolInfo(&ExtToolInfo);

				wsprintf(szKeyName, TEXT("filename%d"), i);
				if(reg_sgetkey( hKey, szKeyName, ExtToolInfo.FileName, sizeof(ExtToolInfo.FileName) ) == -1) continue;

				wsprintf(szKeyName, TEXT("toolname%d"), i);
				reg_sgetkey( hKey, szKeyName, ExtToolInfo.ToolName, sizeof(ExtToolInfo.ToolName) );

				wsprintf(szKeyName, TEXT("cmdline%d"), i);
				reg_sgetkey( hKey, szKeyName, ExtToolInfo.CmdLine, sizeof(ExtToolInfo.CmdLine) );

				wsprintf(szKeyName, TEXT("workdir%d"), i);
				reg_sgetkey( hKey, szKeyName, ExtToolInfo.WorkDir, sizeof(ExtToolInfo.WorkDir) );

				wsprintf(szKeyName, TEXT("mainmenu%d"), i);
				reg_getkey( hKey, szKeyName,  &nTemp);
				ExtToolInfo.ShowOnMainMenu = (0 != nTemp);

				wsprintf(szKeyName, TEXT("popupmenu%d"), i);
				reg_getkey( hKey, szKeyName, &nTemp );
				ExtToolInfo.ShowOnPopupMenu = (0 != nTemp);

				wsprintf(szKeyName, TEXT("startup%d"), i);
				reg_getkey( hKey, szKeyName, &nTemp );
				ExtToolInfo.ExecOnStartup = (0 != nTemp);

				wsprintf(szKeyName, TEXT("overwrite%d"), i);
				reg_getkey( hKey, szKeyName, &nTemp);
				ExtToolInfo.ExecWithOverwrite = (0 != nTemp);

				AddExtTool(i - 1, &ExtToolInfo);
			}
			RegCloseKey(hKey);
	} else {
		InitExtTool(0);
	}

	hsed_ver = HSED_VER;
	hsed_private_ver = HSED_PRIVATE_VER;

	//		Check helpdir

	if (hsp_helpmode==0) {
		gethdir();
		wsprintf(helpopt,TEXT("%shsppidx.htm"),hdir);
		if (fileok(helpopt)) {
			hsp_helpdir[0]=0;
		}
	}
}

/*
		INI file I/O routines
*/

LPCTSTR base64_map = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

typedef union tagBase64_Block{
	struct{
		unsigned int c1 : 6;
		unsigned int c2 : 6;
		unsigned int c3 : 6;
		unsigned int c4 : 6;
	} n;
	char c[3];
} BASE64_BLOCK;

static inline void ini_getkey( LPCTSTR filename, LPCTSTR secname, LPTSTR readkey, int *value )
{
	*value = GetPrivateProfileInt(secname, readkey, *value, filename);
}

static inline DWORD ini_sgetkey( LPCTSTR filename, LPCTSTR secname, LPTSTR readkey, LPTSTR strbuf, int size )
{
	return GetPrivateProfileString(secname, readkey, TEXT(""), strbuf, size, filename);
}

static int ini_bgetkey( LPCTSTR filename, LPCTSTR secname, LPTSTR readkey, BYTE *buf, int length )
{
	TCHAR strbuf[1280], membuf[1280];
	LPCTSTR tmp;
	int offset, memoffset, buflen, validbuflen;
	BASE64_BLOCK block;
	ini_sgetkey(filename, secname, readkey, strbuf, sizeof(strbuf));

	// Base64 decode
	buflen = lstrlen(strbuf);
	if(buflen % 4 != 0)
		return -1;
	for(validbuflen = buflen; validbuflen > 0 && strbuf[validbuflen-1] == TEXT('='); validbuflen--);
	if(validbuflen * 3 / 4 != length) return -1;

	for(offset = 0, memoffset = 0; offset < buflen; offset += 4, memoffset += 3){
		tmp = strbuf[offset] == TEXT('=') ? base64_map : _tcschr(base64_map, strbuf[offset]);
		block.n.c1 = tmp - base64_map;
		tmp = strbuf[offset+1] == TEXT('=') ? base64_map : _tcschr(base64_map, strbuf[offset+1]);
		if(tmp == NULL) return -1;
		block.n.c2 = tmp - base64_map;
		tmp = strbuf[offset+2] == TEXT('=') ? base64_map : _tcschr(base64_map, strbuf[offset+2]);
		if(tmp == NULL) return -1;
		block.n.c3 = tmp - base64_map;
		tmp = strbuf[offset+3] == TEXT('=') ? base64_map : _tcschr(base64_map, strbuf[offset+3]);
		if(tmp == NULL) return -1;
		block.n.c4 = tmp - base64_map;
		memcpy(membuf + memoffset, block.c, sizeof(BASE64_BLOCK));
	}
	memcpy(buf, membuf, length);
	return 0;
}

static void ini_setkey( LPCTSTR filename, LPCTSTR secname, LPTSTR writekey, int value )
{
	TCHAR buf[32];
	wsprintf(buf, TEXT("%d"), value);
	ini_ssetkey(filename, secname, writekey, buf);
}

static inline void ini_ssetkey( LPCTSTR filename, LPCTSTR secname, LPTSTR writekey, LPTSTR string )
{
	WritePrivateProfileString(secname, writekey, string, filename);
}

static void ini_bsetkey( LPCTSTR filename, LPCTSTR secname, LPTSTR writekey, BYTE *buf, int length )
{
	TCHAR strbuf[1280];
	BASE64_BLOCK block;
	int offset = 0, i, n;

	// Base64 encode
	for(i = 2; i < length; i += 3, buf += 3){
		memcpy(block.c, buf, sizeof(BASE64_BLOCK));
		strbuf[offset++] = base64_map[block.n.c1];
		strbuf[offset++] = base64_map[block.n.c2];
		strbuf[offset++] = base64_map[block.n.c3];
		strbuf[offset++] = base64_map[block.n.c4];
	}
	n = length % 3;
	if(n > 0){
		ZeroMemory(&block, sizeof(BASE64_BLOCK));
		memcpy(block.c, buf, sizeof(BASE64_BLOCK));
		strbuf[offset++] = base64_map[block.n.c1];
		strbuf[offset++] = base64_map[block.n.c2];
		if(n == 2) strbuf[offset++] = base64_map[block.n.c3];
		else strbuf[offset++] = TEXT('=');
		strbuf[offset++] = TEXT('=');
	}
	strbuf[offset] = TEXT('\0');

	ini_ssetkey(filename, secname, writekey, strbuf);
}


static void ini_save( void )
{
	//		INIファイルに書き込む
	//

	// 暫定(a temporary step)
	TCHAR filename[_MAX_PATH + 1];
	wsprintf(filename, TEXT("%s\\%s"), szExeDir, INI_FILE);

	int i;
	int nSize/*, nTemp*/;
	EXTTOOLINFO *lpExtToolInfo;
	TCHAR szKeyName[256];

	ini_setkey( filename, TEXT("Compile"), TEXT("fullscr"), hsp_fullscr );
	ini_setkey( filename, TEXT("View"), TEXT("hscroll"), hscroll_flag );
	ini_ssetkey( filename, TEXT("Compile"), TEXT("cmdopt"), hsp_cmdopt );
	ini_ssetkey( filename, TEXT("Compile"), TEXT("laststr"), hsp_laststr );
	chg_font=PopFontGetELG();
	ini_bsetkey( filename, TEXT("Edit"), TEXT("font"), (BYTE *)&chg_font, sizeof(LOGFONT) );
	tchg_font=PopFontGetTLG();
	ini_bsetkey( filename, TEXT("Edit"), TEXT("tabfont"), (BYTE *)&tchg_font, sizeof(LOGFONT) );

	CheckWndFlag();						// Window attribute check
	ini_setkey( filename, TEXT("Startup"), TEXT("winflg"), winflg );

	if (winflg==0) {
		ini_setkey( filename, TEXT("Startup"), TEXT("winx"), winx );
		ini_setkey( filename, TEXT("Startup"), TEXT("winy"), winy );
		ini_setkey( filename, TEXT("Startup"), TEXT("posx"), posx );
		ini_setkey( filename, TEXT("Startup"), TEXT("posy"), posy );
	}

	ini_setkey( filename, TEXT("View"), TEXT("toolbar"), flg_toolbar );
	ini_setkey( filename, TEXT("View"), TEXT("statbar"), flg_statbar );
	ini_setkey( filename, TEXT("View"), TEXT("hspat"), flg_hspat );
	ini_ssetkey( filename, TEXT("Help"), TEXT("helpdir"), hsp_helpdir );
	ini_setkey( filename, TEXT("Compile"), TEXT("exewx"), hsp_wx );
	ini_setkey( filename, TEXT("Compile"), TEXT("exewy"), hsp_wy );
	ini_setkey( filename, TEXT("Compile"), TEXT("exewd"), hsp_wd );
	ini_setkey( filename, TEXT("Compile"), TEXT("debug"), hsp_debug );
	ini_setkey( filename, TEXT("Compile"), TEXT("extobj"), hsp_extobj );
	ini_ssetkey( filename, TEXT("Compile"), TEXT("extstr"), hsp_extstr );
	ini_setkey( filename, TEXT("Help"), TEXT("helpmode"), hsp_helpmode );
	ini_setkey( filename, TEXT("Compile"), TEXT("logmode"), hsp_logmode );
	ini_setkey( filename, TEXT("Compile"), TEXT("logadd"), hsp_logadd );
	ini_setkey( filename, TEXT("Version"), TEXT("hsedver"), hsed_ver );
	ini_setkey( filename, TEXT("Version"), TEXT("hsedprivatever"), hsed_private_ver );
	ini_setkey( filename, TEXT("Compile"), TEXT("extmacro"), hsp_extmacro );
	ini_setkey( filename, TEXT("Compile"), TEXT("clmode"), hsp_clmode );
	ini_setkey( filename, TEXT("Compile"), TEXT("orgpath"), hsp_orgpath );

	ini_setkey( filename, TEXT("Startup"), TEXT("startmode"), startflag );
	ini_ssetkey( filename, TEXT("Startup"), TEXT("startdir"), startdir );

	ini_setkey( filename, TEXT("Edit"), TEXT("tabenabled"),tabEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("hsenabled"), hsEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("fsenabled"), fsEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("nlenabled"), nlEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("eofenabled"), eofEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("underlineenabled"), ulEnabled );
	ini_setkey( filename, TEXT("Edit"), TEXT("tabsize"), tabsize );
	ini_setkey( filename, TEXT("Edit"), TEXT("rulerheight"), rulerheight );
	ini_setkey( filename, TEXT("Edit"), TEXT("linewidth"), linewidth );
	ini_setkey( filename, TEXT("Edit"), TEXT("linespace"), linespace );

	ini_setkey( filename, TEXT("Behavior"), TEXT("autoindent"), bAutoIndent );

	ini_setkey( filename, TEXT("Option"), TEXT("column1width"), ColumnWidth[0] );
	ini_setkey( filename, TEXT("Option"), TEXT("column2width"), ColumnWidth[1] );

	ini_setkey( filename, TEXT("Color"), TEXT("Default"), color.Character.Default.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("String"), color.Character.String.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("Function"), color.Character.Function.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("PreProcessor"), color.Character.Preprocessor.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("Macro"), color.Character.Macro.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("Comment"), color.Character.Comment.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("Label"), color.Character.Label.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("HalfSpace"), color.NonCharacter.HalfSpace.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("FullSpace"), color.NonCharacter.FullSpace.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("Tab"), color.NonCharacter.Tab.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("NewLine"), color.NonCharacter.NewLine.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("EOF"), color.NonCharacter.EndOfFile.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("BackGround"), color.Edit.Background.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("UnderLine"), color.Edit.CaretUnderLine.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("BoundaryLineNum"), color.Edit.BoundaryLineNumber.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("LineNum"), color.LineNumber.Number.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("LineNumCaret"), color.LineNumber.CaretLine.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("RulerNum"), color.Ruler.Number.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("RulerBackGround"), color.Ruler.Background.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("RulerDivision"), color.Ruler.Division.Conf );
	ini_setkey( filename, TEXT("Color"), TEXT("RulerCaret"), color.Ruler.Caret.Conf );

	ini_setkey( filename, TEXT("UserColor"), TEXT("Default"), color.Character.Default.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("String"), color.Character.String.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("Function"), color.Character.Function.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("PreProcessor"), color.Character.Preprocessor.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("Macro"), color.Character.Macro.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("Comment"), color.Character.Comment.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("Label"), color.Character.Label.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("HalfSpace"), color.NonCharacter.HalfSpace.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("FullSpace"), color.NonCharacter.FullSpace.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("Tab"), color.NonCharacter.Tab.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("NewLine"), color.NonCharacter.NewLine.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("EOF"), color.NonCharacter.EndOfFile.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("BackGround"), color.Edit.Background.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("UnderLine"), color.Edit.CaretUnderLine.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("BoundaryLineNum"), color.Edit.BoundaryLineNumber.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("LineNum"), color.LineNumber.Number.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("LineNumCaret"), color.LineNumber.CaretLine.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("RulerNum"), color.Ruler.Number.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("RulerBackGround"), color.Ruler.Background.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("RulerDivision"), color.Ruler.Division.Combo );
	ini_setkey( filename, TEXT("UserColor"), TEXT("RulerCaret"), color.Ruler.Caret.Combo );

	nSize = GetExtToolSize();
	ini_setkey( filename, TEXT("ExtTools"), TEXT("numoftools"), nSize );
	for(i = 1; i <= nSize; i++){
		lpExtToolInfo = GetExtTool(i - 1);
		if(lpExtToolInfo->Used){
			wsprintf(szKeyName, TEXT("toolname%d"), i);
			ini_ssetkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->ToolName);
			wsprintf(szKeyName, TEXT("filename%d"), i);
			ini_ssetkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->FileName);
			wsprintf(szKeyName, TEXT("cmdline%d"), i);
			ini_ssetkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->CmdLine);
			wsprintf(szKeyName, TEXT("workdir%d"), i);
			ini_ssetkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->WorkDir);
			wsprintf(szKeyName, TEXT("mainmenu%d"), i);
			ini_setkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->ShowOnMainMenu);
			wsprintf(szKeyName, TEXT("popupmenu%d"), i);
			ini_setkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->ShowOnPopupMenu);
			wsprintf(szKeyName, TEXT("startup%d"), i);
			ini_setkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->ExecOnStartup);
			wsprintf(szKeyName, TEXT("overwrite%d"), i);
			ini_setkey( filename, TEXT("ExtTools"), szKeyName, lpExtToolInfo->ExecWithOverwrite);
		} else {
			wsprintf(szKeyName, TEXT("filename%d"), i);
			ini_ssetkey( filename, TEXT("ExtTools"), szKeyName, TEXT(""));
		}
	}

	ini_ssetkey( filename, TEXT("Keywords"), TEXT("keyfile"), (LPTSTR )filelist.getlist() );

}

static void ini_load()
{
	//		INIファイルから読み込む
	//

	TCHAR filename[_MAX_PATH + 1];
	wsprintf(filename, TEXT("%s\\%s"), szExeDir, INI_FILE);

	TCHAR szKeyFile[32000];

	EXTTOOLINFO ExtToolInfo;
	int nSize, nTemp, i;
	TCHAR szKeyName[256];

	//		Reset to default value

	set_default();

	//		Read keys

	if (!fileok(filename)) {

		ini_getkey( filename, TEXT("Compile"), TEXT("fullscr"), &hsp_fullscr );
		ini_getkey( filename, TEXT("View"), TEXT("hscroll"), &hscroll_flag );
		ini_sgetkey( filename, TEXT("Compile"), TEXT("cmdopt"), hsp_cmdopt, sizeof(hsp_cmdopt) );
		ini_sgetkey( filename, TEXT("Compile"), TEXT("laststr"), hsp_laststr, sizeof(hsp_laststr) );
		ini_bgetkey( filename, TEXT("Edit"), TEXT("font"), (BYTE *)&chg_font, sizeof(LOGFONT) );
		ini_bgetkey( filename, TEXT("Edit"), TEXT("tabfont"), (BYTE *)&tchg_font, sizeof(LOGFONT) );
		ini_getkey( filename, TEXT("Startup"), TEXT("winflg"), &winflg );
		ini_getkey( filename, TEXT("Startup"), TEXT("winx"), &winx );
		ini_getkey( filename, TEXT("Startup"), TEXT("winy"), &winy );
		ini_getkey( filename, TEXT("Startup"), TEXT("posx"), &posx );
		ini_getkey( filename, TEXT("Startup"), TEXT("posy"), &posy );
		ini_getkey( filename, TEXT("View"), TEXT("toolbar"), &flg_toolbar );
		ini_getkey( filename, TEXT("View"), TEXT("statbar"), &flg_statbar );
		ini_getkey( filename, TEXT("View"), TEXT("hspat"), &flg_hspat );
		ini_sgetkey( filename, TEXT("Help"), TEXT("helpdir"), hsp_helpdir, sizeof(hsp_helpdir) );
		ini_getkey( filename, TEXT("Compile"), TEXT("exewx"), &hsp_wx );
		ini_getkey( filename, TEXT("Compile"), TEXT("exewy"), &hsp_wy );
		ini_getkey( filename, TEXT("Compile"), TEXT("exewd"), &hsp_wd );
		ini_getkey( filename, TEXT("Compile"), TEXT("debug"), &hsp_debug );
		ini_sgetkey( filename, TEXT("Compile"), TEXT("extstr"), hsp_extstr, sizeof(hsp_extstr) );
		ini_getkey( filename, TEXT("Compile"), TEXT("extobj"), &hsp_extobj );
		ini_getkey( filename, TEXT("Help"), TEXT("helpmode"), &hsp_helpmode );
		ini_getkey( filename, TEXT("Compile"), TEXT("logmode"), &hsp_logmode );
		ini_getkey( filename, TEXT("Compile"), TEXT("logadd"), &hsp_logadd );
		ini_getkey( filename, TEXT("Compile"), TEXT("extmacro"), &hsp_extmacro );
		ini_getkey( filename, TEXT("Compile"), TEXT("clmode"), &hsp_clmode );
		ini_getkey( filename, TEXT("Compile"), TEXT("orgpath"), &hsp_orgpath );

		ini_getkey( filename, TEXT("Startup"), TEXT("startmode"), &startflag );
		ini_sgetkey( filename, TEXT("Startup"), TEXT("startdir"), startdir, sizeof(startdir) );

		ini_getkey( filename, TEXT("Edit"), TEXT("tabenabled"),&tabEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("hsenabled"), &hsEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("fsenabled"), &fsEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("nlenabled"), &nlEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("eofenabled"), &eofEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("underlineenabled"), &ulEnabled );
		ini_getkey( filename, TEXT("Edit"), TEXT("tabsize"), &tabsize );
		ini_getkey( filename, TEXT("Edit"), TEXT("rulerheight"), &rulerheight );
		ini_getkey( filename, TEXT("Edit"), TEXT("linewidth"), &linewidth );
		ini_getkey( filename, TEXT("Edit"), TEXT("linespace"), &linespace );

		ini_getkey( filename, TEXT("Behavior"), TEXT("autoindent"), &bAutoIndent );

		ini_getkey( filename, TEXT("Option"), TEXT("column1width"), &ColumnWidth[0] );
		ini_getkey( filename, TEXT("Option"), TEXT("column2width"), &ColumnWidth[1] );

		ini_getkey( filename, TEXT("Color"), TEXT("Default"), (int *)&(color.Character.Default.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("String"), (int *)&(color.Character.String.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("Function"), (int *)&(color.Character.Function.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("PreProcessor"), (int *)&(color.Character.Preprocessor.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("Macro"), (int *)&(color.Character.Macro.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("Comment"), (int *)&(color.Character.Comment.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("Label"), (int *)&(color.Character.Label.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("HalfSpace"), (int *)&(color.NonCharacter.HalfSpace.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("FullSpace"), (int *)&(color.NonCharacter.FullSpace.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("Tab"), (int *)&(color.NonCharacter.Tab.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("NewLine"), (int *)&(color.NonCharacter.NewLine.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("EOF"), (int *)&(color.NonCharacter.EndOfFile.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("BackGround"), (int *)&(color.Edit.Background.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("UnderLine"), (int *)&(color.Edit.CaretUnderLine.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("BoundaryLineNum"), (int *)&(color.Edit.BoundaryLineNumber.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("LineNum"), (int *)&(color.LineNumber.Number.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("LineNumCaret"), (int *)&(color.LineNumber.CaretLine.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("RulerNum"), (int *)&(color.Ruler.Number.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("RulerBackGround"), (int *)&(color.Ruler.Background.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("RulerDivision"), (int *)&(color.Ruler.Division.Conf) );
		ini_getkey( filename, TEXT("Color"), TEXT("RulerCaret"), (int *)&(color.Ruler.Caret.Conf) );

		ini_getkey( filename, TEXT("UserColor"), TEXT("Default"), (int *)&(color.Character.Default.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("String"), (int *)&(color.Character.String.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("Function"), (int *)&(color.Character.Function.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("PreProcessor"), (int *)&(color.Character.Preprocessor.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("Macro"), (int *)&(color.Character.Macro.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("Comment"), (int *)&(color.Character.Comment.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("Label"), (int *)&(color.Character.Label.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("HalfSpace"), (int *)&(color.NonCharacter.HalfSpace.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("FullSpace"), (int *)&(color.NonCharacter.FullSpace.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("Tab"), (int *)&(color.NonCharacter.Tab.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("NewLine"), (int *)&(color.NonCharacter.NewLine.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("EOF"), (int *)&(color.NonCharacter.EndOfFile.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("BackGround"), (int *)&(color.Edit.Background.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("UnderLine"), (int *)&(color.Edit.CaretUnderLine.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("BoundaryLineNum"), (int *)&(color.Edit.BoundaryLineNumber.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("LineNum"), (int *)&(color.LineNumber.Number.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("LineNumCaret"), (int *)&(color.LineNumber.CaretLine.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("RulerNum"), (int *)&(color.Ruler.Number.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("RulerBackGround"), (int *)&(color.Ruler.Background.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("RulerDivision"), (int *)&(color.Ruler.Division.Combo) );
		ini_getkey( filename, TEXT("UserColor"), TEXT("RulerCaret"), (int *)&(color.Ruler.Caret.Combo) );

		ini_sgetkey( filename, TEXT("Keywords"), TEXT("keyfile"), szKeyFile, sizeof(szKeyFile));

		nSize = 0;
		ini_getkey( filename, TEXT("ExtTools"), TEXT("numoftools"), &nSize );
		InitExtTool(nSize);
		for(i = 1; i <= nSize; i++){
			DefaultExtToolInfo(&ExtToolInfo);

			wsprintf(szKeyName, TEXT("filename%d"), i);
			if(ini_sgetkey( filename, TEXT("ExtTools"), szKeyName, ExtToolInfo.FileName, sizeof(ExtToolInfo.FileName) ) == 0) continue;

			wsprintf(szKeyName, TEXT("toolname%d"), i);
			ini_sgetkey( filename, TEXT("ExtTools"), szKeyName, ExtToolInfo.ToolName, sizeof(ExtToolInfo.ToolName) );

			wsprintf(szKeyName, TEXT("cmdline%d"), i);
			ini_sgetkey( filename, TEXT("ExtTools"), szKeyName, ExtToolInfo.CmdLine, sizeof(ExtToolInfo.CmdLine) );

			wsprintf(szKeyName, TEXT("workdir%d"), i);
			ini_sgetkey( filename, TEXT("ExtTools"), szKeyName, ExtToolInfo.WorkDir, sizeof(ExtToolInfo.WorkDir) );

			wsprintf(szKeyName, TEXT("mainmenu%d"), i);
			ini_getkey( filename, TEXT("ExtTools"), szKeyName,  &nTemp);
			ExtToolInfo.ShowOnMainMenu = (0 != nTemp);

			wsprintf(szKeyName, TEXT("popupmenu%d"), i);
			ini_getkey( filename, TEXT("ExtTools"), szKeyName, &nTemp );
			ExtToolInfo.ShowOnPopupMenu = (0 != nTemp);

			wsprintf(szKeyName, TEXT("startup%d"), i);
			ini_getkey( filename, TEXT("ExtTools"), szKeyName, &nTemp );
			ExtToolInfo.ExecOnStartup = (0 != nTemp);

			wsprintf(szKeyName, TEXT("overwrite%d"), i);
			ini_getkey( filename, TEXT("ExtTools"), szKeyName, &nTemp);
			ExtToolInfo.ExecWithOverwrite = (0 != nTemp);

			AddExtTool(i - 1, &ExtToolInfo);
		}

		ini_getkey( filename, TEXT("Version"), TEXT("hsedver"), &hsed_ver );
		ini_getkey( filename, TEXT("Version"), TEXT("hsedprivatever"), &hsed_private_ver );
	}
	hsed_ver = HSED_VER;
	hsed_private_ver = HSED_PRIVATE_VER;

	//		Check helpdir

	if (hsp_helpmode==0) {
		gethdir();
		wsprintf(helpopt,TEXT("%shsppidx.htm"),hdir);
		if (fileok(helpopt)) {
			hsp_helpdir[0]=0;
		}
	}
}