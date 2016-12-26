
//
//	membuf.cpp structures
//
#ifndef __membuf_h
#define __membuf_h

//  growmem class
class CMemBuf {
public:
	CMemBuf();
	CMemBuf( int sz );
	~CMemBuf();
	void AddIndexBuffer( void );
	void AddIndexBuffer( int sz );

	LPTSTR GetBuffer( void );
	int GetBufferSize( void );
	int *GetIndexBuffer( void );
	void SetIndex( int idx, int val );
	int GetIndex( int idx );
	int GetIndexBufferSize( void );
	int SearchIndexValue( int val );

	void RegistIndex( int val );
	void Index( void );
	void Put( int data );
	void Put( short data );
	void Put( TCHAR data );
	void Put( unsigned char data );
	void Put( float data );
	void Put( double data );
	void PutStr( LPTSTR data );
	void PutStrBlock( LPTSTR data );
	void PutCR( void );
	void PutData( void *data, int sz );
	int PutFile( LPTSTR fname );
	int SaveFile( LPTSTR fname );
	LPTSTR GetFileName( void );
	int GetSize( void ) { return cur; }
private:
	virtual void InitMemBuf( int sz );
	virtual void InitIndexBuf( int sz );
	LPTSTR PreparePtr( int sz );

	//		Data
	//
	int		limit_size;			// Separate size
	int		size;				// Main Buffer Size
	int		cur;				// Current Size
	LPTSTR	mem_buf;			// Main Buffer

	int		idxflag;			// index Mode Flag
	int		*idxbuf;			// Index Buffer
	int		idxmax;				// Index Buffer Max
	int		curidx;				// Current Index

	TCHAR	name[256];			// File Name
};


#endif
