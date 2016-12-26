
//
//	supio.cpp functions
//

LPTSTR mem_ini( int size );
void mem_bye( void *ptr );
int mem_load( LPTSTR fname, void *mem, int msize );
int mem_save( LPTSTR fname, void *mem, int msize );
int filecopy( LPTSTR fname, LPTSTR sname );

void prtini( LPTSTR mes );
void prt( LPTSTR mes );
int tstrcmp( LPTSTR str1, LPTSTR str2 );
void strcase( LPTSTR str );
void getpath( LPTSTR stmp, LPTSTR outbuf, int p2 );
