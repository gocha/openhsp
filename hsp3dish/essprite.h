#ifndef	__ESSPRITE_H__
#define	__ESSPRITE_H__

#include "hspwnd.h"

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

#define ESSPFLAG_NONE (0)
#define ESSPFLAG_STATIC (0x100)
#define ESSPFLAG_MOVE (0x200)
#define ESSPFLAG_GRAVITY (0x400)
#define ESSPFLAG_SPLINK (0x800)
#define ESSPFLAG_NOWIPE (0x1000)
#define ESSPFLAG_XBOUNCE (0x2000)
#define ESSPFLAG_YBOUNCE (0x4000)
#define ESSPFLAG_BLINK (0x8000)
#define ESSPFLAG_NODISP (0x10000)

#define ESSPOPT_NONE (0)
#define ESSPOPT_EXTDISP (1)
#define ESSPOPT_FADEIN (4)
#define ESSPOPT_FADEOUT (8)
#define ESSPOPT_ADDCOLOR (16)
#define ESSPOPT_SUBCOLOR (32)

#define ESSPLINK_BGMAP (0x10000)

//
//	sprite move flag (fl) condition :
//			( fl=0 : no sprite )
//
//			bit 0-7 : countdown wipe (0=none)
//
//			bit 8 :  $100 static sprite
//			bit 9 :  $200 move (px,py) every
//			bit10 :  $400 gravity move
//			bit11 :  $800 background link move
//			bit12 : $1000 no border wipe
//			bit13 : $2000 X-border bounce
//			bit14 : $4000 Y-border bounce
//
//
//		info number :
//			0,1 = flag (32bit)
//			2,3 = X axis (32bit)
//			4,5 = Y axis (32bit)
//			6,7 = PX prm (32bit)
//			8,9 = PY prm (32bit)
//			 10 = progress counter
//			 11 = Animation counter
//			 12 = CHR code
//			 13 = TYPE code
//		  14,15 = Exec ptr.
//

typedef struct CHRREF
{
	short wid;			//  buffer ID
	short tpflag;		//  Transparent flag
	short lktime, lknum;	//	chr link information
	short bx, by;		//	chr base X,Y
	short bsx, bsy;		//	chr base size of X,Y
	int colx, coly;		//	Collision X,Y offset
	int colsx, colsy;	//	Collision size of X,Y
} CHRREF;

typedef struct BGMAP
{
	int* varptr;		//	Map reference ptr.
	int mapsx, mapsy;	//	Map alloc size
	int sizex, sizey;	//	Map view size (cel)
	int viewx, viewy;	//	Map view axis
	int buferid;		//	Map parts buffer ID
	int bgoption;		//	BG option
	int tpflag;			//	合成パラメーター
} BGMAP;

typedef struct SPOBJ
{
	int	fl;				//	exist flag (ESSPFLAG_*)
	int xx;				//  X axis (16bit固定少数)
	int yy;				//	Y axis (16bit固定少数)
	int px;				//	Gravity/Move X parameters
	int py;				//	Gravity/Move X parameters
	int prg;			//	Move program counter
	int ani;			//	chr anim counter
	int chr;			//	chr code
	int type;			//	Attribute type
	int fspx,fspy;		//  落下速度
	int bound;			//  固さ
	int boundflag;		//  バウンドさせるフラグ(1=X 2=Y)
	int option;			//	表示オプション (ESSPOPT_*)
	int priority;		//	優先順位
	int tpflag;			//	α値(0-255)+effectパラメーター
	int fadeprm;		//	αフェードパラメーター
	int zoomx;			//	X方向倍率(16bit固定少数)
	int zoomy;			//	Y方向倍率(16bit固定少数)
	int	rotz;			//	回転角度
	int	splink;			//	link to other sprite
} SPOBJ;

class essprite {
public:
	essprite();
	~essprite();
	void reset(void);
	int init(int maxsprite=512, int maxchr=1024, int rotrate=64, int maxmap=16);
	void setResolution(HspWnd *wnd, int sx, int sy);
	void setArea(int x, int y, int sx, int sy );
	void setSize(int p1, int p2, int p3, int p4);
	void setLand(int p1, int p2);
	int setGravity(int p1, int p2, int p3);
	int setBound(int p1, int p2, int p3);
	void setOffset(int p1, int p2);
	int setPattern(int p1, int p2, int p3, int p4, int window_id);
	int setLink(int p1, int p2);

	void clear(int spno);
	void clear(int p1, int p2);
	void setTransparentMode(int tp);
	SPOBJ* resetSprite(int spno);
	int put(int x, int y, int chr, int tpflag=-1, int zoomx=0x10000, int zoomy=0x10000, int rotz=0);
	int drawSub(SPOBJ* sp);
	int draw(int start, int num, int dispflag, int sortflag);
	int find(int chktype, int spno, int endspno = -1, int step = 0);
	int checkCollisionSub(SPOBJ *sp);
	int checkCollision(int spno, int chktype);

	int putMap(int x, int y, int id);
	int setMap(int bgno, int* varptr, int mapsx, int mapsy, int sx, int sy, int buffer, int option);
	int setMapPos(int bgno, int x, int y);
	int setMapMes(int bgno, int x, int y, char *msg, int offset=0);

	int setSpriteFlag(int spno, int flag);
	int setSpritePosChr(int spno, int xx, int yy, int chrno, int option, int pri);
	int setSpritePos(int spno, int xx, int yy, bool realaxis=false);
	int setSpriteAddPos(int spno, int xx, int yy, bool realaxis = false);
	int setSpriteAddPosRate(int spno, int xx, int yy, int rate);
	int setSpriteChr(int spno, int chrno);
	int setSpriteType(int spno, int type);
	int setSpriteAddDir(int spno, int direction, int dirrate);
	int setSpriteAim(int spno, int xx, int yy, int dirrate);
	int getSpritePos(int* xpos, int* ypos, int spno, int option);
	int modifySpriteAxis(int spno, int endspno, int type, int x, int y, int option);

	int setSpriteParent(int spno, int parent, int option);
	int setSpriteFade(int p1, int p2, int p3);
	int setSpriteEffect(int id, int tpflag, int mulcolor);
	int setSpriteRotate(int id, int angle, int zoomx, int zoomy);

	SPOBJ* getObj(int id);
	BGMAP* getMap(int id);
	CHRREF* getChr(int id);
	int getSpriteParentAxis(SPOBJ *sp, int *xx, int *yy, int depth);

	int getEmptyChrNo(void);
	int getEmptySpriteNo(void);
	int getEmptySpriteNo(int sp_from, int sp_to, int step);
	int getParameter(int spno, int prmid);
	void setParameter(int spno, int prmid, int value);
	int getMaxSprites(void) { return spkaz; };
	int getMaxCharacters(void) { return chrkaz; };
	void getDefaultPatternSize(int* xsize, int* ysize);

	int utilGetAngle(int p1, int p2, int p3, int p4);
	int utilGetSin(int p1);
	int utilGetCos(int p1);
	int utilGetDistance(int x1, int y1, int x2, int y2);

	//	Open Parameters
	//
	bool	sprite_enable;

private:
	//	Parameters
	//
	HspWnd* hspwnd;	// Parent Window Handle
	Bmscr* bmscr;

	int		spkaz;	// Max sprite object
	SPOBJ* mem_sp;
	int		chrkaz;	// Max pattern object
	CHRREF* mem_chr;
	CHRREF* chr;
	int		mapkaz;	// Max map object
	BGMAP* mem_map;

	int		main_sx, main_sy;	// default window size
	int		ofsx, ofsy;			// for sprite offset
	int		ox1, oy1, ox2, oy2;	// valid area
	int		land_x, land_y;		// common ground axis
	double	pi, pans;
	int		resox, resoy;		// 画面解像度
	int		rrate;				// 周の分解能
	int* vpx, *vpy;				// sin,cosテーブル

	int		dotshift;			// 座標シフト値
	int		dotshift_base;		// 座標シフト値(1.0)

	int		df_bsx, df_bsy, df_colx, df_coly;
	int		df_colsx, df_colsy, df_tpflag;
	int		def_fspx, def_fspy;
	int		def_bound;
	int		def_boundflag;

	int		colx, coly, colex, coley;
	int		fade_mode, fade_upd, fade_val, fade_tar;
};


/*---------------------------------------------------------------------------*/

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
