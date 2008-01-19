
//
//	HSP3 window manager
//	onion software/onitama 2004/6
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../hsp3config.h"
#include "../hsp3debug.h"
#include "../hspwnd.h"
#include "../dpmread.h"
#include "../strbuf.h"
#include "../strnote.h"
#include "../supio.h"

#include <ocidl.h>
#include <olectl.h>

#define HIMETRIC_INCH	2540
#define MAP_LOGHIM_TO_PIX(x,ppli)   ( ((ppli)*(x) + HIMETRIC_INCH/2) / HIMETRIC_INCH )
#define WM_MOUSEWHEEL 0x020A

#define MM_MCINOTIFY    0x03B9
#define MCI_NOTIFY_SUCCESSFUL   1

static HspWnd *curwnd;
static MM_NOTIFY_FUNC notifyfunc;

/*------------------------------------------------------------*/
/*
		constructor
*/
/*------------------------------------------------------------*/

HspWnd::HspWnd()
{
	//		������
	//
	Reset( NULL, "hspwnd0" );
}

HspWnd::HspWnd( HANDLE instance, char *wndcls )
{
	//		������
	//
	Reset( instance, wndcls );
}

HspWnd::~HspWnd()
{
	//		���ׂĔj��
	//
	Dispose();
}


/*------------------------------------------------------------*/
/*
		Window interface in C
*/
/*------------------------------------------------------------*/

Bmscr *TrackBmscr( HWND hwnd )
{
	int id;
	id = GetWindowLong( hwnd, GWL_USERDATA );
	if ( id < 0 ) return NULL;
	return curwnd->GetBmscr( id );
}


void WM_Paint( HWND hwnd, Bmscr *bm )
{
	//		WM_PAINT process
	//
	PAINTSTRUCT ps;
	HDC hdc;
	if ( bm->flag == BMSCR_FLAG_NOUSE ) return;
	hdc = BeginPaint ( hwnd, &ps );
	bm->Bmspnt( hdc );
	EndPaint ( hwnd, &ps );
}


LRESULT CALLBACK WndProc( HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam )
{
	int id;
	int retval;
	Bmscr *bm;

	if ( code_isuserirq() ) {
		if ( code_checkirq( GetWindowLong( hwnd, GWL_USERDATA ), (int)uMessage, (int)wParam, (int)lParam ) ) {
			if ( code_irqresult( &retval ) ) return retval;
		}
	}

	switch (uMessage)
	{
	case WM_CREATE:
		SetWindowLong( hwnd, GWL_USERDATA, -1 );
		return 0;

	case WM_PALETTECHANGED:
		if ( wParam == (WPARAM)hwnd ) break;
	case WM_QUERYNEWPALETTE:
		bm = TrackBmscr( hwnd );
		if ( bm == NULL ) break;
		if (bm->hpal != NULL) {				// �p���b�g�ύX���ɂ��}�b�`���O������
			int a;
			HDC hdc;
			HPALETTE opal;
			hdc=GetDC( hwnd );
			opal=SelectPalette( hdc, bm->hpal, 0 );
			a=RealizePalette( hdc );
			SelectPalette( hdc, opal, 0 );
			ReleaseDC( hwnd, hdc );
			if ( a > 0) InvalidateRect( hwnd, NULL, TRUE );
			return a;
		}
		break;

	case WM_PAINT:
		//		Display �S�`��
		//
		bm = TrackBmscr( hwnd );
		if ( bm != NULL ) WM_Paint( hwnd, bm );
		return 0 ;

	case WM_GETMINMAXINFO:
		{
		LPMINMAXINFO lpmm;
		bm = TrackBmscr( hwnd );
		if ( bm != NULL ) {
			lpmm = (LPMINMAXINFO)lParam;
			lpmm->ptMaxTrackSize.x = bm->sx + bm->framesx;
			lpmm->ptMaxTrackSize.y = bm->sy + bm->framesy;
		}
		break;
		}

	case WM_SIZE:
		bm = TrackBmscr( hwnd );
		if ( bm != NULL ) {
			bm->wx = lParam & 0xFFFF;				// x�T�C�Y
			bm->wy = (lParam >> 16) & 0xFFFF;		// y�T�C�Y
			bm->SetScroll( bm->viewx, bm->viewy );
		}
		break;

	case WM_MOUSEWHEEL:
		bm = TrackBmscr( hwnd );
		if ( bm != NULL ) {
			bm->savepos[BMSCR_SAVEPOS_MOSUEZ] = LOWORD(wParam);
			bm->savepos[BMSCR_SAVEPOS_MOSUEW] = HIWORD(wParam);
		}
		return 0;

	case WM_MOUSEMOVE:
		bm = TrackBmscr( hwnd );
		if ( bm != NULL ) {
			bm->savepos[BMSCR_SAVEPOS_MOSUEX] = LOWORD(lParam);
			bm->savepos[BMSCR_SAVEPOS_MOSUEY] = HIWORD(lParam);
		}
		return 0;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		if ( code_isirq( HSPIRQ_ONCLICK ) ) {
			code_sendirq( HSPIRQ_ONCLICK, (int)uMessage - (int)WM_LBUTTONDOWN, (int)wParam, (int)lParam );
		}
		break;
	case WM_COMMAND:
		if ( wParam & MESSAGE_HSPOBJ ) {
			id = GetWindowLong( hwnd, GWL_USERDATA );
			bm =curwnd->GetBmscr( id );
			//Alertf( "%d,%x,%x (%d)",id,wParam,lParam , ( wParam & (MESSAGE_HSPOBJ-1)) );
			bm->SendHSPObjectNotice( (int)wParam );
		}
		return 0;

	case MM_MCINOTIFY:
		if ( wParam == MCI_NOTIFY_SUCCESSFUL ) {
			if ( notifyfunc != NULL ) notifyfunc( hwnd );
		}
		return 0;

	case WM_QUERYENDSESSION:
	case WM_CLOSE:
		id = GetWindowLong( hwnd, GWL_USERDATA );
		if ( code_isirq( HSPIRQ_ONEXIT ) ) {
			int iparam = 0;
			if ( uMessage == WM_QUERYENDSESSION ) iparam++;
			retval = code_sendirq( HSPIRQ_ONEXIT, iparam, id, 0 );
			if ( retval == RUNMODE_INTJUMP ) retval = code_execcmd2();	// onexit goto���͎��s���Ă݂�
			if ( retval != RUNMODE_END ) return 0;
			break;
		}
		code_puterror( HSPERR_NONE );
		break;
	}
	return DefWindowProc (hwnd, uMessage, wParam, lParam) ;
}


/*------------------------------------------------------------*/
/*
		interface
*/
/*------------------------------------------------------------*/

void HspWnd::Dispose( void )
{
	//		�j��
	//
	int i;
	HWND hwnd;
	Bmscr *bm;
	for(i=0;i<bmscr_max;i++) {
		bm = mem_bm[i];
		if ( bm != NULL ) {
			hwnd = bm->hwnd;
			if ( hwnd != NULL ) DestroyWindow( hwnd );
			delete bm;
		}
	}
	free( mem_bm );
	UnregisterClass( defcls, hInst );
}


int HspWnd::GetActive( void )
{
	//
	//		detect active window
	int i;
	HWND hwnd;
	Bmscr *bm;

	hwnd = GetActiveWindow();

	for(i=0;i<bmscr_max;i++) {
		bm = mem_bm[i];
		if ( bm != NULL ) {
			if ( bm->hwnd != NULL ) if ( bm->hwnd == hwnd ) return i;
		}
	}
	if (( wnd_parent != NULL )&&( wnd_parent == hwnd )) return 0;

	return -1;
}


void HspWnd::ExpandScreen( int id )
{
	int i;
	int idmax;
	Bmscr **new_bm;

	//Alertf("Expand:%d:%d",idmax,bmscr_max);
	idmax = id + 1;
	if ( idmax <= bmscr_max ) return;
	new_bm = (Bmscr **)malloc( sizeof( Bmscr * ) * idmax );

	for(i=0;i<idmax;i++) {
		if (( i >= bmscr_max )||( bmscr_max == 0 )) {
			new_bm[i] = NULL;
		} else {
			//if ( mem_bm[i] != NULL ) 
			new_bm[i] = mem_bm[i];
		}
	}
	if ( mem_bm != NULL ) free( mem_bm );

	bmscr_max = idmax;
	mem_bm = new_bm;
}


void HspWnd::Reset( HANDLE instance, char *wndcls )
{
	//		all window initalize
	//
	int i;
	WNDCLASS    wndclass ;
	hInst=(HINSTANCE)instance;
	strcpy( defcls, wndcls );

	//		alloc Bmscr
	//
	bmscr_max = 0;
	mem_bm = NULL;
	ExpandScreen( 31 );									// �Ƃ肠����

	//		global vals
	//
	wfy=GetSystemMetrics( SM_CYCAPTION )+GetSystemMetrics( SM_CYFRAME )*2;
	wfx=GetSystemMetrics( SM_CXFRAME )*2;
	wbx=GetSystemMetrics( SM_CXHTHUMB );
	wby=GetSystemMetrics( SM_CYVTHUMB );
	mwfy=GetSystemMetrics( SM_CYCAPTION )+GetSystemMetrics( SM_CYFIXEDFRAME )*2;
	mwfx=GetSystemMetrics( SM_CXFIXEDFRAME )*2;

	//		main window class
	//
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = (WNDPROC) WndProc ;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInst;
	wndclass.hIcon         = LoadIcon( hInst, MAKEINTRESOURCE(128) );
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = defcls;
	RegisterClass (&wndclass);

	//		Reset palette
	//
	for(i=0;i<256*3;i++) {
		pstpt[i] = i/3;						// �O���[�X�P�[���p���b�g���쐬
	}

	//		save pointer for C
	//
	SetNotifyFunc( NULL );
	SetEventNoticePtr( &bmscr_res );
	SetParentWindow( NULL );
	curwnd = this;
}


void HspWnd::SetEventNoticePtr( int *ptr )
{
	resptr = ptr;
	SetObjectEventNoticePtr( resptr );
}


void HspWnd::SetNotifyFunc( void *func )
{
	notifyfunc = (MM_NOTIFY_FUNC)func;
}


void HspWnd::MakeBmscrOff( int id, int sx, int sy, int palsw )
{
	//		Bmscr����(�I�t�X�N���[��)
	//
	Bmscr		*bm;
	HWND		hwnd;

	ExpandScreen( id );
	hwnd = NULL;
	bm = mem_bm[id];
	if ( bm != NULL ) {
		hwnd = bm->hwnd;
		ShowWindow( hwnd, SW_HIDE );
		delete bm;
	}
		
	bm = new Bmscr;
	mem_bm[id] = bm;

	bm->wid = id;
	bm->master_hspwnd = (void *)this;
	bm->type = HSPWND_TYPE_BUFFER;

	bm->Init( hInst, hwnd, sx, sy, palsw );

	bm->wx = 0; bm->wy = 0;
	bm->wchg = 0;
	bm->viewx=0; bm->viewy=0;
}


void HspWnd::MakeBmscr( int id, int type, int xx, int yy, int wx, int wy, int sx, int sy, int palsw )
{
	//		Bmscr����
	//
	HWND		hwnd;
	HWND		par_hwnd;
	DWORD		style;
	int			wndtype;
	int			scr_x,scr_y;
	int			winx,winy;
	int			palmode;
	int			exstyle;
	int			defstyle;
	int			framesx,framesy;
	int			swtype;
	Bmscr		*bm;

	if ( type == HSPWND_TYPE_BUFFER ) {
		MakeBmscrOff( id, sx, sy, palsw );
		return;
	}

	ExpandScreen( id );
	palmode = palsw & 1;
	scr_x=wx; scr_y=wy;
	winx=CW_USEDEFAULT; winy=CW_USEDEFAULT;
	if (xx!=-1) winx=xx;
	if (yy!=-1) winy=yy;

	par_hwnd = NULL;
	wndtype = type;

//	style = WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_VISIBLE | WS_THICKFRAME | WS_CLIPCHILDREN;
	style = WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER | WS_CLIPCHILDREN;

	framesx = 0;
	framesy = 0;
	exstyle = 0;

	defstyle = palsw>>2;
	if ( wndtype == HSPWND_TYPE_BGSCR ) {
		style=WS_POPUP|WS_CLIPCHILDREN;
	} else {
		framesx = mwfx;
		framesy = mwfy;
		if (( id > 0 )&&( (defstyle & 1)==0 )) {
			style |= WS_THICKFRAME;
			framesx = wfx;
			framesy = wfy;
		}
		if ( defstyle & 2 ) {
			exstyle |= WS_EX_TOOLWINDOW;
			framesy = GetSystemMetrics( SM_CYSMCAPTION )+(GetSystemMetrics( SM_CYFRAME )*2);
		}
		if ( defstyle & 4 ) {
			exstyle |= WS_EX_OVERLAPPEDWINDOW;
			framesx += 4; framesy += 4;
		}
		if ( palsw & 0x100 ) {
			style = WS_CHILD|WS_CLIPCHILDREN;
			wndtype = HSPWND_TYPE_SSPREVIEW;
			par_hwnd = (HWND)wnd_parent;
		}
	}

	bm = mem_bm[id];
	if ( bm == NULL ) {

//		if ( !(palsw & 2 ) ) { style |= WS_VISIBLE; }

		hwnd = CreateWindowEx (
				exstyle,								// extra window style
				defcls,									// window class name

#ifdef HSPDEBUG
				HSPTITLE hspver,						// window caption
#else
				NULL,									// window caption
#endif

				style,									// window style
	            winx,									// initial x position
	            winy,									// initial y position
	            scr_x,									// initial x size
	            scr_y,									// initial y size
	            par_hwnd,								// parent window handle
	            NULL,									// window menu handle
	            hInst,									// program instance handle
			NULL) ;										// creation parameters

	} else {
		hwnd = bm->hwnd;
		wndtype = bm->type;
		delete bm;
		if ( wndtype != HSPWND_TYPE_BUFFER ) {
			swtype = SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE;
//			if ( !(palsw & 2 ) ) { style |= WS_VISIBLE; } else {
//				swtype |= SWP_HIDEWINDOW;
//			}
			if ( IsWindowVisible( hwnd ) ) { style |= WS_VISIBLE; }
			//style |= WS_VISIBLE;
			SetWindowLong( hwnd, GWL_EXSTYLE, exstyle );
			SetWindowLong( hwnd, GWL_STYLE, style );
			SetWindowPos( hwnd,HWND_TOP,0,0,0,0, swtype );
		}
	}

	bm = new Bmscr;
	mem_bm[id] = bm;

	bm->wid = id;
	bm->master_hspwnd = (void *)this;
	bm->type = wndtype;

	bm->Init( hInst, hwnd, sx, sy, palmode );
	bm->framesx = framesx;
	bm->framesy = framesy;

	swtype = SW_SHOWDEFAULT;
	if ( palsw & 2 ) {
		swtype = SW_HIDE;
	}

	bm->Width( wx, wy, -1, -1, 1 );
	bm->wchg=0;
	bm->viewx=0; bm->viewy=0;

	SetWindowLong( hwnd, GWL_USERDATA, id );

	ShowWindow( hwnd, swtype );
	bm->Update();
}


int HspWnd::Picload( int id, char *fname, int mode )
{
	//		picload
	//		( mode:0=resize/1=overwrite )
	//
	Bmscr *bm;
	void *pBuf;
    HGLOBAL h;
	RECT rc;
	int i,size,x,y,psx,psy;
    HRESULT hr;
	long hmWidth, hmHeight;
	LPPICTURE gpPicture;							// IPicture
    LPSTREAM pstm = NULL;							// IStream���擾����

	bm = GetBmscr( id );
	if ( bm == NULL ) return 1;
	if ( bm->flag == BMSCR_FLAG_NOUSE ) return 1;

	//�@�t�@�C���T�C�Y���擾
	size = dpm_exist( fname );
	if ( size <= 0 ) return 1;

	// �O���[�o���̈���m��
	h = GlobalAlloc( GMEM_MOVEABLE, size );
    if( h == NULL) return 2;
	pBuf = GlobalLock( h );
    if( pBuf == NULL ) return 2;
	i = dpm_read( fname, pBuf, size, 0 );
	if ( i <= 0 ) return 1;
	GlobalUnlock( h );

	hr = CreateStreamOnHGlobal( h, TRUE, &pstm );	// �O���[�o���̈悩��IStream���쐬
    if( !SUCCEEDED(hr) ) return 3;
    hr = OleLoadPicture( pstm, size, FALSE, IID_IPicture, (LPVOID *)&gpPicture );    // IPicture�̃I�u�W�F�N�g�̃A�h���X���擾
    pstm->Release();							    // IStream�I�u�W�F�N�g���J��
	if( SUCCEEDED( hr ) == FALSE || gpPicture == NULL ) {
		return 3;
    }

	// get width and height of picture
	gpPicture->get_Width(&hmWidth);
	gpPicture->get_Height(&hmHeight);
	// convert himetric to pixels
	psx = MulDiv( hmWidth, GetDeviceCaps( bm->hdc, LOGPIXELSX ), HIMETRIC_INCH );
	psy = MulDiv( hmHeight, GetDeviceCaps( bm->hdc, LOGPIXELSY ), HIMETRIC_INCH );

	if ( mode == 0 ) {
		int palsw,type;
		//int wx,wy;
		type = bm->type; palsw = bm->palmode;
		//wx = bm->wx; wy = bm->wy;
		MakeBmscr( id, type, -1, -1, psx, psy, psx, psy, palsw );
		//MakeBmscr( id, type, -1, -1, wx, wy, psx, psy, palsw );
		bm = GetBmscr( id );
	}

	// setup initial position
	x = bm->cx; y = bm->cy;
	GetClientRect( bm->hwnd, &rc );
	// display picture using IPicture::Render
	gpPicture->Render( bm->hdc, x, y, psx, psy, 0, hmHeight, hmWidth, -hmHeight, &rc );
	bm->Send( x, y, psx, psy );

	gpPicture->Release();
	return 0;
}


/*------------------------------------------------------------*/
/*
		Bmscr interface
*/
/*------------------------------------------------------------*/

Bmscr::Bmscr()
{
	//		bmscr������
	//
	flag = BMSCR_FLAG_NOUSE;
}

Bmscr::~Bmscr()
{
	//		Bmscr�j��
	//
	if ( flag == BMSCR_FLAG_INUSE ) {

		//		object remove
		//
		ResetHSPObject();

		//		resource remove
		//
		Delfont();

		//		remove HBRUSH
		//
		if ( hbr != NULL ) {
			DeleteObject( hbr );
		}

		//		remove HPEN
		//
		if ( hpn != NULL ) {
			DeleteObject( hpn );
		}

		//		remove HPALETTE
		//
		if ( hpal != NULL ) {
			SelectPalette( hdc, holdpal, TRUE );
			DeleteObject( hpal );
		}

		//		remove DIB section
		//
		SelectObject( hdc, old );
		DeleteObject( dib );
		DeleteDC( hdc );
		GlobalFree( pbi );
	}
}

/*----------------------------------------------------------------*/
//		font&text related routines
/*----------------------------------------------------------------*/

void Bmscr::Init( HANDLE instance, HWND p_hwnd, int p_sx, int p_sy, int palsw )
{
	//		bitmap buffer make
	//
	HDC srchdc;
 	HBITMAP hbDib,hbOld;
	int msize,bsize;

	hwnd = p_hwnd;
	hInst= (HINSTANCE)instance;

	flag = BMSCR_FLAG_INUSE;
	objmax = 0;
	mem_obj = NULL;
	sx = p_sx; sy = p_sy;

	palmode = palsw;
	bsize = sx;

	if ( palmode == BMSCR_PALMODE_FULLCOLOR ) {
		msize=sizeof(BITMAPINFOHEADER);
		pbi=(LPBITMAPINFOHEADER)GlobalAlloc( GPTR, msize );
		pbi->biBitCount = 24;
		bsize*=3;
	} else {
		msize=sizeof(BITMAPINFOHEADER) + 256*sizeof(RGBQUAD);
		pbi=(LPBITMAPINFOHEADER)GlobalAlloc( GPTR, msize );
		pbi->biBitCount = 8;
	}
	bsize = ( bsize + 3 )&~3;
	sx2 = bsize;
	bsize *= sy;

	infsize = msize;
	bmpsize = bsize;
	
	pbi->biSize = sizeof(BITMAPINFOHEADER);
	pbi->biWidth = sx;
	pbi->biHeight = sy;
	pbi->biPlanes = 1;

	srchdc = GetDC(hwnd);
	hbDib=CreateDIBSection( srchdc,(BITMAPINFO *)pbi,DIB_RGB_COLORS,
			(void **)&pBit, NULL, 0 );
	hdc=CreateCompatibleDC(srchdc);
	hbOld = (HBITMAP)SelectObject( hdc, hbDib );
	ReleaseDC( hwnd, srchdc );

	dib = hbDib;
	old = hbOld;
	pal = (RGBQUAD *)(pbi+1);
	hpal = NULL;
	hbr  = NULL;
	hpn  = NULL;
	focflg = 0;
	objmode = 1;
	tabmove = 1;
	hfont=NULL;
	fl_dispw = 0;

	Cls( 0 );

	fl_dispw = 1;
	fl_udraw = 1;
}


void Bmscr::Cls( int mode )
{
	//		screen setting reset
	//
	int i;
	HBRUSH hbr, hbrOld;

	//		Font initalize
	//
	Sysfont(0);

	//		object initalize
	//
	ResetHSPObject();

	//		text setting initalize
	//
	cx=0;cy=0;
	Setcolor(0,0,0);

	//		palette initalize
	//
	UpdatePalette();

	//		screen clear
	//
	hbr = (HBRUSH)GetStockObject( mode );
	hbrOld = (HBRUSH)SelectObject( hdc, hbr );
	Rectangle( hdc, -1, -1, sx+1, sy+1);
	SelectObject( hdc, hbrOld );

	//		vals initalize
	//
	textspeed=0;
	ox=64;oy=24;py=0;
	gx=32;gy=32;gmode=0;
	objstyle = WS_CHILD|WS_VISIBLE;
	for(i=0;i<BMSCR_SAVEPOS_MAX;i++) { savepos[i] = 0; }
	palcolor = 0;

	//		all update
	//
	fl_udraw = fl_dispw;
	Update();
}


void Bmscr::Bmspnt( HDC disthdc )
{
	HPALETTE opal;

	if ( hpal != NULL ) {
		opal=SelectPalette( disthdc, hpal, 0 );
		RealizePalette( disthdc );
	}
	BitBlt( disthdc, 0, 0, wx, wy, hdc, viewx, viewy, SRCCOPY );
	if ( hpal != NULL ) {
		SelectPalette( disthdc, opal, 0 );
	}
}


void Bmscr::Update( void )
{
	HDC disthdc;
	if ( fl_udraw == 0 ) return;
	if ( type < HSPWND_TYPE_MAIN ) return;
	disthdc=GetDC( hwnd );
	Bmspnt( disthdc );
	ReleaseDC( hwnd, disthdc );
}


void Bmscr::Title( char *str )
{
	if ( type < HSPWND_TYPE_MAIN ) return;
	SetWindowText( hwnd, str );
}


void Bmscr::Width( int x, int y, int wposx, int wposy, int mode )
{
	RECT rw;
	int sizex, sizey;

	if ( x > 0 ) {
		wx = x; if ( x > sx ) wx = sx;
	}
	if ( y > 0 ) {
		wy = y; if ( y > sy ) wy = sy;
	}

	if (( type < HSPWND_TYPE_MAIN )||( type == HSPWND_TYPE_SSPREVIEW )) return;

	sizex = wx + framesx;
	sizey = wy + framesy;
	GetWindowRect( hwnd,&rw );
	if ( wposx >= 0 ) rw.left = wposx;
	if ( wposy >= 0 ) rw.top = wposy;
	MoveWindow( hwnd, rw.left, rw.top, sizex, sizey, (mode>0) );
}


void Bmscr::Send( int x, int y, int p_sx, int p_sy )
{
	HDC dhdc;
	HPALETTE opal;
	if ( fl_udraw == 0 ) return;
	if ( type < HSPWND_TYPE_MAIN ) return;
	dhdc=GetDC( hwnd );
	if ( hpal != NULL ) {
		opal=SelectPalette( dhdc, hpal, 0 );
		RealizePalette( dhdc );
	}
	BitBlt( dhdc, x-viewx, y-viewy, p_sx, p_sy, hdc,x,y, SRCCOPY );
	if ( hpal != NULL ) {
		SelectPalette( dhdc, opal, 0 );
	}
	ReleaseDC( hwnd, dhdc );
}


void Bmscr::Posinc( int pp )
{
	if ( pp<py ) { cy+=py; } else { cy+=pp; }
}


void Bmscr::Delfont( void )
{
	//	destroy font
	//
	if (hfont!=NULL) {
		SelectObject( hdc, holdfon );
		DeleteObject( hfont );
		hfont=NULL;
	}
}


void Bmscr::Fontupdate( void )
{
	//	update new font
	//
	TEXTMETRIC	tm;
	if (hfont!=NULL) {
		holdfon = (HFONT)SelectObject( hdc, hfont );
		GetTextMetrics( hdc, &tm );
		texty = tm.tmHeight + tm.tmExternalLeading;
	}
/*
	{
		HDC hdcwnd = GetDC(hwndbmp);
		HFONT holdfontwnd = (HFONT)SelectObject(hdcwnd, hfont);

		holdfont = (HFONT)SelectObject(hdc, hfont);

		SelectObject(hdcwnd, holdfontwnd);
		ReleaseDC(hwndbmp, hdcwnd);
	}
*/

}


int Bmscr::Newfont( char *fonname, int fpts, int fopt, int angle )
{
	//	select new font
	//		fopt : bit0=BOLD       bit1=Italic
	//		       bit2=Underline  bit3=Strikeout
	//		       bit4=Anti-alias
	//		fpts : point size
	//		angle: rotation
	//
	int a;
	BYTE b;
	PLOGFONT pLogFont;			// logical FONT ptr
	unsigned char chk;
	HFONT hf_new;

	pLogFont=(PLOGFONT) &logfont;
	strcpy( pLogFont->lfFaceName, fonname );
	pLogFont->lfHeight			= -fpts;
	pLogFont->lfWidth			= 0;
	pLogFont->lfOutPrecision	= 0 ;
	pLogFont->lfClipPrecision	= 0 ;

	if (fopt&4) {
		pLogFont->lfUnderline		= TRUE;
	} else {
		pLogFont->lfUnderline		= FALSE;
	}

	if (fopt&8) {
		pLogFont->lfStrikeOut		= TRUE;
	} else {
		pLogFont->lfStrikeOut		= FALSE;
	}

	if ( fopt & 16 ) {
		pLogFont->lfQuality			= ANTIALIASED_QUALITY ;
	} else {
		pLogFont->lfQuality			= DEFAULT_QUALITY;
	}

	pLogFont->lfPitchAndFamily	= 0 ;
	pLogFont->lfEscapement		= angle ;
	pLogFont->lfOrientation		= 0 ;

	b=DEFAULT_CHARSET;
	a=0;while(1) {
		chk=fonname[a++];
		if (chk==0) break;
		if (chk>=0x80) { b=SHIFTJIS_CHARSET;break; }
	}
	pLogFont->lfCharSet = b;

	if (fopt&1) {
		pLogFont->lfWeight = FW_BOLD;
	} else {
		pLogFont->lfWeight = FW_NORMAL;
	}

	if (fopt&2) {
		pLogFont->lfItalic = TRUE;
	} else {
		pLogFont->lfItalic = FALSE;
	}

	hf_new = CreateFontIndirect( pLogFont );
	if ( hf_new == NULL ) return -1;

	Delfont();
	hfont = hf_new;
	Fontupdate();
	return 0;
}


void Bmscr::Sysfont( int p1 )
{
	/*
		Reserved Font List
	#define OEM_FIXED_FONT      10
	#define ANSI_FIXED_FONT     11
	#define ANSI_VAR_FONT       12
	#define SYSTEM_FONT         13
	#define DEVICE_DEFAULT_FONT 14
	#define DEFAULT_PALETTE     15
	#define SYSTEM_FIXED_FONT   16
	#define DEFAULT_GUI_FONT    17
	*/
	HFONT hf;
	Delfont();
	if (p1) {
		hf=(HFONT)GetStockObject(p1);
		if (hf!=NULL) {
			hfont=hf;
			Fontupdate();
			return;
		}
	}
	Newfont( "FixedSys", 14,0,0 );
}


void Bmscr::Setcolor( int a1, int a2, int a3 )
{
	COLORREF c;
	if (a1==-1) c = PALETTEINDEX(a2);
		   else c = color = RGB(a1,a2,a3);
	SetBkMode( hdc,TRANSPARENT );
	SetTextColor( hdc, c );
	if ( hbr != NULL ) DeleteObject( hbr );
	hbr = CreateSolidBrush( c );
	if ( hpn != NULL ) DeleteObject( hpn );
	hpn = CreatePen( PS_SOLID,0,c );
}


void Bmscr::Setcolor( COLORREF rgbcolor )
{
	Setcolor( GetRValue(rgbcolor), GetGValue(rgbcolor), GetBValue(rgbcolor) );
}


void Bmscr::SetSystemcolor( int id )
{
	Setcolor( (COLORREF)GetSysColor( id ) );
}


void Bmscr::UpdatePalette( void )
{
	//		set palette to DIB & HPALETTE
	//			*rgbptr : R,G,B order palette entry
	//
	int a,colors;
	BYTE *pt;
	RGBQUAD *bpal;
	LOGPALETTE *lpPal;
	HPALETTE hGetPal;
	HspWnd *wnd;
	void *rgbptr;
	//FILE *fp;

	wnd = (HspWnd *)master_hspwnd;
	rgbptr = wnd->pstpt;
	colors = 256;

	if ( palmode == 0 ) return;

	if ( hpal != NULL ) {
		SelectPalette( hdc, holdpal, TRUE );
		DeleteObject( hpal );
	}

	bpal = pal;
	pt=(BYTE *)rgbptr;
	for(a=0;a<colors;a++) {
		bpal[a].rgbBlue  = pt[2];
		bpal[a].rgbRed   = pt[0];
		bpal[a].rgbGreen = pt[1];
		bpal[a].rgbReserved = 0;
		pt+=3;
	}
	SetDIBColorTable( hdc, 0, colors, bpal );

	//		make HPALETTE
	//
	lpPal = (LOGPALETTE *) malloc( 0x800 );		// size of Pal buffer 
	lpPal->palVersion = 0x300;
	lpPal->palNumEntries = (WORD) colors;
	pt=(BYTE *)rgbptr;
	for( a=0; a<colors; a++ ) {
		lpPal->palPalEntry[a].peRed		= pt[0];
		lpPal->palPalEntry[a].peGreen	= pt[1];
		lpPal->palPalEntry[a].peBlue	= pt[2];
		lpPal->palPalEntry[a].peFlags	= PC_NOCOLLAPSE;
		pt+=3;
	}
	hGetPal = CreatePalette( lpPal );
	hpal = hGetPal;
	holdpal = SelectPalette( hdc, hGetPal, TRUE );
	free( lpPal );
	pals = colors;
}


void Bmscr::SetPalette( int palno, int rv, int gv, int bv )
{
	int a;
	BYTE a1,a2,a3;
	HspWnd *wnd;
	BYTE *pstpt;

	if ( palmode == 0 ) return;

	wnd = (HspWnd *)master_hspwnd;
	pstpt = wnd->pstpt;

	a=palno*3;
	a1=rv;a2=gv;a3=bv;
	pstpt[a++]=a1; pstpt[a++]=a2; pstpt[a++]=a3;
	//UpdatePalette();
}


void Bmscr::SetPalcolor( int palno )
{
	RGBQUAD *p;
	p=&pal[ palno ];
	color = RGB( p->rgbRed, p->rgbGreen, p->rgbBlue );
	Setcolor( -1, palno, 0 );
	palcolor = palno;
}


void Bmscr::Print( char *mes )
{
	int a;
	long res;
	SIZE *size;
	size = &printsize;
	a=(int)strlen(mes);
	if (a) {

		//GetTextExtentPoint32( hdc, mes, a, size );
		//HDC hdcwnd = GetDC( hwnd );
		//HFONT holdfontwnd = (HFONT)SelectObject( hdcwnd, hfont );

		//TextOut( hdc, cx, cy , mes, a );

		res = TabbedTextOut( hdc, cx, cy, mes, a, 0, NULL, 0 );
		size->cx = res & 0xffff;
		size->cy = res>>16;

		//SelectObject( hdcwnd, holdfontwnd );
		//ReleaseDC( hwnd, hdcwnd );

		Send( cx, cy, size->cx, size->cy );
	} else {
		GetTextExtentPoint32( hdc, " ", 1, size );
	}
	Posinc( size->cy );
}


void Bmscr::Boxfill( int x1,int y1,int x2,int y2 )
{
	//		boxf
	RECT bx;
	bx.left=x1;bx.top=y1;bx.right=x2+1;bx.bottom=y2+1;
	FillRect( hdc, &bx, hbr );
	Send( x1,y1,x2-x1+1,y2-y1+1 );
}


COLORREF Bmscr::Pget( int xx, int yy )
{
	//		pget
	//
	COLORREF c;
	c = GetPixel( hdc, xx, yy );
	Setcolor( c );
	return c;
}


void Bmscr::Pset( int xx,int yy )
{
	//		pset
	//
	SetPixel( hdc,xx,yy,color );
	Send( xx,yy,1,1 );
}


void Bmscr::Line( int xx,int yy )
{
	//		line
	//
	HPEN oldpen;
	int x,y,x1,y1,x2,y2;
	x=cx;y=cy;
	MoveToEx( hdc,x,y,NULL );
	if (cx<xx)   { x1=x;x2=xx-x; }
				else { x1=xx;x2=x-xx; }
	if (cy<yy)   { y1=y;y2=yy-y; }
				else { y1=yy;y2=y-yy; }
	oldpen=(HPEN)SelectObject(hdc,hpn);
	LineTo( hdc,xx,yy );
	SelectObject(hdc,oldpen);
	Send( x1,y1,x2+1,y2+1 );
	cx=xx;cy=yy;
}


void Bmscr::Circle( int x1,int y1,int x2,int y2, int mode )
{
	//		circle
	//		mode: 0=outline/1=fill
	//
	HPEN oldpen;
	HBRUSH old;
	int ix,iy;
	oldpen = (HPEN)SelectObject(hdc,hpn);
	if ( mode ) {
		old = (HBRUSH)SelectObject( hdc, hbr );
	} else {
		old = (HBRUSH)SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
	}
	::Ellipse( hdc,x1,y1,x2,y2 );
	if ( mode ) SelectObject( hdc, old );
	SelectObject( hdc, oldpen );
	ix = x1; iy = y1;
	if (x2<x1) ix=x2;
	if (y2<y1) iy=y2;
	Send( ix,iy,abs(x2-x1)+1,abs(y2-y1)+1 );
}


/*----------------------------------------------------------------*/

void Bmscr::Blt( int mode, Bmscr *src, int xx, int yy, int asx, int asy )
{
	//		fast blt
	//
	BYTE *p;
	BYTE *p2;
	int *palpt;
	int a,b,bsx,bsy,tofs,sofs,pand;
	int vv,cx,cy,sx,sy;
	int ssx, ssy, ssx2;
	BYTE a1,a2,a3;

	ssx = src->sx; ssy = src->sy; ssx2 = src->sx2;

	cx=this->cx;sx=asx;bsx=this->sx;
	if (xx<0) { sx+=xx;cx-=xx;xx=0; }
	if ((xx+sx)>=ssx) sx-=(xx+sx)-ssx;
	if (cx>bsx) return;
	if (cx<0) {
		sx=cx+sx;
		if (sx<=0) return;
		xx-=cx;cx=0;
	}
	vv=bsx-sx;
	if (cx>vv) { sx-=cx-vv; }
	
	cy=this->cy;sy=asy;bsy=this->sy;
	if (yy<0) { sy+=yy;cy-=yy;yy=0; }
	if ((yy+sy)>=ssy) sy-=(yy+sy)-ssy;
	if (cy>bsy) return;
	if (cy<0) {
		sy=cy+sy;
		if (sy<=0) return;
		yy-=cy;cy=0;
	}
	vv=bsy-sy;
	if (cy>vv) { sy-=cy-vv; }

	p=(BYTE *)this->pBit;
	p+=(bsy-cy-1) * this->sx2;
	p2=(BYTE *)(src->pBit);
	p2+=(ssy-yy-1)*ssx2;

	if (!palmode) goto blt24;

	p+=cx; p2+=xx;
	tofs = this->sx2 + sx;
	sofs = ssx2 + sx;

	if (mode==2) goto tblt;

	for(b=0;b<sy;b++) {
		for(a=0;a<sx;a++) {
			*p++=*p2++;
		}
		p-=tofs;p2-=sofs;
	}
	return;

tblt:
	palpt=(int *)this->pal;pand=0xffffff;
	for(b=0;b<sy;b++) {
		for(a=0;a<sx;a++) {
			a1=*p2++;
			if (palpt[a1]&pand) *p++=a1; else p++;
		}
		p-=tofs;p2-=sofs;
	}
	return;

blt24:
	p+=cx*3; p2+=xx*3;
	tofs = this->sx2 + (sx*3);
	sofs = ssx2 + (sx*3);

	switch( mode ) {
	case 1:
		break;
	case 2:
		//		FC trans copy
		for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				a1=*p2++;a2=*p2++;a3=*p2++;
				if (a1|a2|a3) {
					*p++=a1;*p++=a2;*p++=a3;
				} else {
					p+=3;
				}
			}
			p-=tofs;p2-=sofs;
		}
		return;
	case 3:
		{
		// �������R�s�[(�W��)
		short srcht,dstht,ha;
		srcht = this->gfrate;
		if ( srcht>256 ) srcht=256;
		if ( srcht<=0 ) return;
		dstht = 256-srcht;
		if ( dstht == 0 ) break;
		  sx*=3;
		  for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				ha=(((short)*p)*dstht>>8) + (((short)*p2++)*srcht>>8);
				if (ha>255) ha=255;
				*p++=(BYTE)ha;
			}
			p-=tofs;p2-=sofs;
		  }
		}
		return;
	case 4:
		{
		// �������R�s�[(�J���[���O)
		short ha,ha1,ha2,ha3,cl1,cl2,cl3;
		short srcht,dstht;
		srcht = this->gfrate;
		if ( srcht>256 ) srcht=256;
		if ( srcht<=0 ) return;
		dstht = 256-srcht;

		cl3 = (short)( this->color & 0xff );
		  cl2 = (short)( (this->color>>8) & 0xff );
		  cl1 = (short)( (this->color>>16) & 0xff );
		  // 0x00bbggrr 
		  for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				ha1=(short)*p2++;ha2=(short)*p2++;ha3=(short)*p2++;
				if ( (ha1!=cl1)||(ha2!=cl2)||(ha3!=cl3)) {
					ha=(((short)*p)*dstht>>8) + (ha1*srcht>>8);
					if (ha>255) ha=255;
					*p++=(BYTE)ha;
					ha=(((short)*p)*dstht>>8) + (ha2*srcht>>8);
					if (ha>255) ha=255;
					*p++=(BYTE)ha;
					ha=(((short)*p)*dstht>>8) + (ha3*srcht>>8);
					if (ha>255) ha=255;
					*p++=(BYTE)ha;
				}
				else {
					p+=3;
				}
			}
			p-=tofs;p2-=sofs;
		  }
		}
		return;
	case 5:
		{
		// �F���Z�R�s�[
		short srcht,ha;
		srcht = this->gfrate;
		if ( srcht>256 ) srcht=256;
		if ( srcht<=0 ) return;
		sx*=3;
		  for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				ha=((short)*p) + (((short)*p2++)*srcht>>8);
				if (ha>255) ha=255;
				*p++=(BYTE)ha;
			}
			p-=tofs;p2-=sofs;
		  }
		}
		return;
	case 6:
		{
		// �F���Z�R�s�[
		short srcht,ha;
		srcht = this->gfrate;
		if ( srcht>256 ) srcht=256;
		if ( srcht<=0 ) return;
		sx*=3;
		  for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				ha=((short)*p) - (((short)*p2++)*srcht>>8);
				if (ha<0) ha=0;
				*p++=(BYTE)ha;
			}
			p-=tofs;p2-=sofs;
		  }
		}
		return;
	case 7:
		{
		// �s�N�Z���A���t�@�u�����h�R�s�[
		int sx2;
		short srcht,ha;
		  sx *= 3;
		  sx2 = asx*3;
		  for(b=0;b<sy;b++) {
			for(a=0;a<sx;a++) {
				srcht=(short)( *(p2+sx2) );
				if ( srcht!=0 ) {
					if ( srcht==255 ) {
						*p = *p2;
					} else {
						ha=(((short)*p)*(255-srcht)>>8) + (((short)*p2)*srcht>>8);
						*p=(BYTE)ha;
					}
				}
				p++;p2++;
			}
			p-=tofs;p2-=sofs;
		  }
		}
		return;
	}

	//		FC normal copy
	sx*=3;
	for(b=0;b<sy;b++) {
		for(a=0;a<sx;a++) {
			*p++=*p2++;
		}
		p-=tofs;p2-=sofs;
	}
	return;
}


int Bmscr::Copy( Bmscr *src, int xx, int yy, int psx, int psy )
{
	//		copy
	//
	switch( gmode ) {
	case 0:
		BitBlt( hdc, cx, cy, psx, psy, src->hdc, xx, yy, SRCCOPY );
		break;
	case 1:
	case 2:
		if ( palmode != src->palmode ) return 1;
		Blt( gmode, src, xx, yy, psx, psy );
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		if (( palmode==BMSCR_PALMODE_PALETTECOLOR )|( src->palmode == BMSCR_PALMODE_PALETTECOLOR )) return 1;
		Blt( gmode, src, xx, yy, psx, psy );
		break;
	}
	Send( cx, cy, psx, psy );
	return 0;
}


int Bmscr::Zoom( int dx, int dy, Bmscr *src, int xx, int yy, int psx, int psy, int mode )
{
	//		zoom
	//		(mode:0=normal/1=halftone)
	//
	int i;
	if ( mode ) i = HALFTONE; else i = COLORONCOLOR;
	SetStretchBltMode( hdc, i );
	StretchBlt(  hdc, cx, cy, dx, dy,
				 src->hdc, xx, yy, psx, psy, SRCCOPY );
	Send( cx, cy, dx, dy );
	return 0;
}


int Bmscr::BmpSave( char *fname )
{
	//		save BMP,DIB file
	//
	BITMAPFILEHEADER bmFH;
	FILE *fp;
	int bsize;
	bsize = bmpsize;
	fp=fopen( fname, "wb" );
	if (fp==NULL) return -1;
	bmFH.bfType = 0x4d42;
	bmFH.bfSize = (infsize) + (bsize) + sizeof(BITMAPFILEHEADER);
	bmFH.bfOffBits = (infsize) + sizeof(BITMAPFILEHEADER);
	bmFH.bfReserved1 = 0;
	bmFH.bfReserved2 = 0;
	fwrite( &bmFH, 1, sizeof(BITMAPFILEHEADER), fp );
	fwrite( pbi, 1, infsize, fp );
	fwrite( pBit, 1, bsize, fp );
	fclose(fp);
	return 0;
}


void Bmscr::SetHSVColor( int hval, int sval, int vval )
{
	//		hsv�ɂ��F�w��
	//			h(0-191)/s(0-255)/v(0-255)
	//
	int h,s,v;
	int save_r, save_g, save_b;
	int t,i,v1,v2,v3;
	int mv=8160;		// 255*32
	int mp=4080;		// 255*16
	//		overflow check
	//
	v = vval & 255;
	s = sval & 255;		// /8
	//		hsv -> rgb �ϊ�
	//
	h = hval % 192;
	i = h/32;
	t = h % 32;
	v1 = (v*(mv-s*32) 	+mp)/mv;
	v2 = (v*(mv-s*t) 	+mp)/mv;
	v3 = (v*(mv-s*(32-t))+mp)/mv;
	switch(i){
		case 0:
		case 6:
				save_r=v;	save_g=v3;	save_b=v1;	break;
		case 1:
				save_r=v2;	save_g=v;	save_b=v1;	break;
		case 2:
				save_r=v1;	save_g=v;	save_b=v3;	break;
		case 3:
				save_r=v1;	save_g=v2;	save_b=v;	break;
		case 4:
				save_r=v3;	save_g=v1;	save_b=v;	break;
		case 5:
				save_r=v;	save_g=v1;	save_b=v2;	break;
	}
	Setcolor( save_r, save_g, save_b );
}


void Bmscr::GetClientSize( int *xsize, int *ysize )
{
	//		�E�B���h�E�̃N���C�A���g�̈�̃T�C�Y�����߂�
	//
	RECT rw;
	GetClientRect( hwnd, &rw );
	*xsize = rw.right;
	*ysize = rw.bottom;
}


void Bmscr::SetScroll( int xbase, int ybase )
{
	//		�X�N���[����_��ݒ�
	//
	int ax,ay, _vx, _vy;
	_vx = viewx;
	_vy = viewy;
	viewx = xbase;
	if ( viewx < 0 ) viewx = 0;
	viewy = ybase;
	if ( viewy < 0 ) viewy = 0;

	GetClientSize( &ax, &ay );
	if ( ( viewx + ax ) > sx ) viewx = sx - ax;
	if ( ( viewy + ay ) > sy ) viewy = sy - ay;

	if (( _vx != viewx )||( _vy != viewy )) Update();
}

