#ifndef		__SYSREQ_H__
#define		__SYSREQ_H__

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

// システム初期化コード
enum {
SYSREQ_NONE = 0,
SYSREQ_MAXMODEL,
SYSREQ_MAXOBJ,
SYSREQ_MAXTEX,
SYSREQ_MAXMOC,
SYSREQ_DXMODE,
SYSREQ_DXHWND,
SYSREQ_DXWIDTH,
SYSREQ_DXHEIGHT,
SYSREQ_COLORKEY,
SYSREQ_RESULT,
SYSREQ_RESVMODE,
SYSREQ_PKTSIZE,
SYSREQ_MAXEVENT,
SYSREQ_PTRD3D,
SYSREQ_PTRD3DDEV,
SYSREQ_MDLANIM,
SYSREQ_CALCNORMAL,
SYSREQ_2DFILTER,
SYSREQ_3DFILTER,
SYSREQ_OLDCAM,
SYSREQ_QUATALG,
SYSREQ_DXVSYNC,
SYSREQ_DEFTIMER,
SYSREQ_NOMIPMAP,
SYSREQ_DEVLOST,
SYSREQ_MAXEMITTER,
SYSREQ_THROUGHFLAG,
SYSREQ_OBAQMATBUF,
SYSREQ_2DFILTER2,
SYSREQ_FPUPRESERVE,
SYSREQ_CLSMODE,
SYSREQ_CLSCOLOR,
SYSREQ_CLSTEX,
SYSREQ_TIMER,
SYSREQ_PLATFORM,
SYSREQ_FPS,
SYSREQ_VSYNC,
SYSREQ_MAXMATERIAL,

SYSREQ_PHYSICS_RATE,
SYSREQ_MAXOBAQ,
SYSREQ_MAXLOG,
SYSREQ_DEFAULT_WEIGHT,
SYSREQ_DEFAULT_MOMENT,
SYSREQ_DEFAULT_DAMPER,
SYSREQ_DEFAULT_FRICTION,

SYSREQ_MESCACHE_MAX,
SYSREQ_DLIGHT_MAX,
SYSREQ_PLIGHT_MAX,
SYSREQ_SLIGHT_MAX,
SYSREQ_LOGWRITE,

SYSREQ_FIXEDFRAME,

SYSREQ_MAX
};

#define PLATFORM_WINDOWS 0
#define PLATFORM_IOS 1
#define PLATFORM_ANDROID 2
#define PLATFORM_EMSCRIPTEN 3
#define PLATFORM_LINUX 4
#define PLATFORM_RASPBIAN 5

void InitSysReq( void );
void SetSysReq( int reqid, int val );
int GetSysReq( int reqid );
void SetSysReqF( int reqid, float val );
float GetSysReqF( int reqid );
void DebugMsg( char *format, ... );
char *GetDebug( void );

/*---------------------------------------------------------------------------*/

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
