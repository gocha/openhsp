//---------------------------------------------------------------------------
#ifndef __geometry_h
#define __geometry_h

#define PI 3.14159265358979f
#define PI2 6.28318530717958f
#define HPI 1.570796326794895f

#define DEG2ANG(x) ((int)((x) * 32768.0f / 180.0f) & 0xffff)
#define RAD2ANG(x) ((int)((x) * 32768.0f / PI) & 0xffff)
#define DEG2RAD(x) ((x) * PI / 180.0f)
#define RAD2DEG(x) ((x) * 180.0f / PI)

typedef struct {
	float x, y, z, w;
} VECTOR;

typedef struct {
  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;
} MATRIX;

typedef float FVECTOR[4];
typedef float * FVRef;
typedef int * IVRef;
typedef float (*FMatRef)[4];

#define VECREF (VECTOR *)(FVRef)

// ®VECTOR^
typedef struct {
int x,y,z,w;
} IVECTOR;

/*
// ¬VECTOR^
typedef struct {
float x,y,z,w;
} FVECTOR;
*/

// ®AXIS^
typedef struct {
int x,y;
} IAXIS;

// ¬AXIS^
typedef struct {
float x,y;
} FAXIS;

// ®AXIS2^(UVt«)
typedef struct {
short x,y,tx,ty;
} IAXIS2;

#define setIAXIS( a,b,c ) a.x=(int)b;a.y=(int)c;
#define setIAXIS2( a,b,c,d,e ) a.x=(int)b;a.y=(int)c;a.tx=(int)d;a.ty=(int)e;

typedef struct {
	VECTOR a;			// §Ï·sñÌW(x, y, z0, z1)
	VECTOR b;			// §Ï·sñÌÁZl (0, 0, z2, z3)
	VECTOR ra;			// WÌt(1/K)
	VECTOR rb;			// ÁZlÌâ (-K)
	VECTOR v;			// yobt@ÆtHOÌp[^
	VECTOR t;			// ItZbgwxÀWÆyobt@ÆtHOÌp[^
	VECTOR cmin;		// NbvÅ¬ÍÍ{eNX`â³W
	VECTOR cmax;		// NbvÅåÍÍ
} ViewScreen;


//---------------------------------------------------------------------------

void GeometryInit(void);
void GeometryTerm(void);

//void CopyVector( VECTOR *dst, VECTOR *src );
#define CopyVector( dst,src ) *(dst) = *(src)

//void SetVector( VECTOR *dst, float x, float y, float z, float w );
#define SetVector(dst,xarg,yarg,zarg,warg)	(dst)->x=xarg;(dst)->y=yarg;(dst)->z=zarg;(dst)->w=warg


void AddVector( VECTOR *dst, VECTOR *v0, VECTOR *v1 );
void SubVector( VECTOR *dst, VECTOR *v0, VECTOR *v1 );
void MulVector( VECTOR *dst, VECTOR *v0, VECTOR *v1 );
void DivVector( VECTOR *dst, VECTOR *v0, float r );
void ScaleVector( VECTOR *dst, VECTOR *v0, float r );

//  }gbNXú»
void  InitMatrix(void);
//  ¶ènÉ·é
void  LeftHand(void);
//  EènÉ·é(default)
void  RightHand(void);
//  }gbNXÌRs[
void  CopyMatrix( MATRIX *src, MATRIX *dst );
//  }gbNXÞð
void  PushMatrix(void);
//  }gbNXA
void  PopMatrix(void);
//  Jg}gbNXæ¾
void  GetCurrentMatrix(MATRIX *dst);
MATRIX *GetCurrentMatrixPtr( void );
//  Jg}gbNXÝè
void  SetCurrentMatrix(MATRIX *dst);
//  Jg}gbNXÌgXð¾é
void  GetCurrentTrans(VECTOR *v);
//  PÊ}gbNX
void  UnitMatrix(void);
//  w²ñ]
void  RotX(float x);
//  x²ñ]
void  RotY(float y);
//  y²ñ]
void  RotZ(float z);
//  ½sÚ®
void  Trans(float x, float y, float z);
//  XP[
void  Scale(float x, float y, float z);
//  §e
void  Perspective(float r);
//  §e©Âyðyobt@lÉ
void  PerspectiveWithZBuffer(float r, float N, float F, float Zn, float Zf);
//  }gbNX¯mÌÏiJg}gbNXÉ¶©ç|¯éj
void  MulMatrix(MATRIX *left);
//  }gbNX¯mÌÏiJg}gbNXÉE©ç|¯éj
void  MulMatrixR(MATRIX *right);
//  ]usñ
void  Transpose(MATRIX *mat);
//  }gbNXÌsñ®
float  Determinant(MATRIX *mat);
//  3x3sñ®Ìlitsñpj
float  Determinant3(MATRIX *src);
//  tsñ
int  InverseMatrix(MATRIX *mat);
//  xNg}gbNX -> xNg
void  ApplyMatrix(VECTOR *v0, VECTOR *v1);
void  ApplyMatrixN(VECTOR *v0, VECTOR *v1, int nb);
//  xNg}gbNX -> xNgiñ]ÌÝj
void  ApplyMatrixRot(VECTOR *v0, VECTOR *v1);
//  xNg}gbNX -> xNgi½sÚ®ÌÝj
void  ApplyMatrixTrans(VECTOR *v0, VECTOR *v1);
//  QxNgÌOÏ
void  OuterProduct(VECTOR *v1, VECTOR *v2, VECTOR *dst);
//  QxNgÌàÏ
float  InnerProduct(VECTOR *v1, VECTOR *v2);
//  PÊxNg
void  UnitVector(VECTOR *v);
//  J}gbNX¶¬
void  LookAt(VECTOR *cam_pos, VECTOR *cam_int);
void  LookAtWithRoll(VECTOR *cam_pos, VECTOR *cam_int, float roll);

//	View->Screen}gNX¶¬
void PerspectiveViewScreen( ViewScreen * vs, float scrz, float ax, float ay, 
	       float xcenter, float ycenter, float zbufsmall, float zbufbig, float D, float F, float fognearz, float fogfarz, float W, float H);

//	|SÚG»è
int HasPoint2D( float x, float y, VECTOR *v );
int HasPoint3D( VECTOR *p, VECTOR *v );
int IntersectLinePlane( VECTOR *lpoint, VECTOR *lvector, VECTOR *ppoint, VECTOR *pnormal, VECTOR *result );
float GetVectorDistance( VECTOR *v1, VECTOR *v2 );


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif
