
//
//	webtask_linux.cpp functions
//
#ifndef __webtask_linux_h
#define __webtask_linux_h

#define INETURL_MAX 2048
#define INETBUF_MAX 0x10000

#include <string>

enum {
CZHTTP_MODE_NONE = 0,		// ネット接続なし
CZHTTP_MODE_READY,			// ネット接続待機
CZHTTP_MODE_VARREQUEST,		// リクエスト準備
CZHTTP_MODE_VARREQSEND,		// リクエスト送信
CZHTTP_MODE_VARDATAWAIT,	// リクエスト受信中
CZHTTP_MODE_VARDATAEND,		// リクエスト受信終了
CZHTTP_MODE_MAX
};

#define CZHTTP_MODE_ERROR -1	// エラー発生

#define HTTPINFO_MODE 0		// 現在のモード
#define HTTPINFO_SIZE 1		// データサイズ
#define HTTPINFO_DATA 16		// 取得データ
#define HTTPINFO_ERROR 17	// エラー文字列

typedef void CURL;
typedef void CURLM;

class WebTask {
public:
	WebTask();
	~WebTask();

	int Exec( void );									// 毎フレームごとに呼ばれる
	int Request( char *url, char *post );				// HTTPリクエスト

	//	外部とのインターフェース
	int getStatus( int id );							// ステータス値の取得
	char *getData( int id );							// データの取得
	void setData( int id, char *str );					// データの設定

        static size_t OnReceive(char* ptr, size_t size, size_t nmemb, void* stream);
protected:

	//	内部使用
	void Terminate( void );								// 破棄
	void Reset( void );									// リセット

	char *getVarData( void ) { return vardata; };		// 受信データポインタの取得
	char *getError( void ) { return errstr; };			// エラー文字列のポインタを取得
	int getMode( void ) { return mode; };				// 現在のモードを返す
	int getSize( void ) { return (int)size; };				// 受信データサイズの取得
	int getVarSize( void ) { return varsize; };			// 受信バッファサイズの取得
	void SetURL( char *url );							// サーバーのURLを設定
	void ClearVarData( void );
	void ClearPostData( void );
	void SetError( char *mes );
	void SetPostData( char *post );
	void SetVarServerFromURL( char *url );				// URL文字列を解析する

  // オプション項目
	void SetAgent( char *agent );						// エージェントの設定
	void SetProxy( char *url, int port, int local );	// プロキシの設定
	void SetHeader( char *header );						// ヘッダ文字列の設定

	//	リクエスト
	void SetVarRequestGet( char *path );
	void SetVarRequestPost( char *path, char *post );

	char *str_agent;				// User Agent (optonal)
	int mode;						// Current Mode
	size_t size;						// File Size

	char errstr[256];				// Error string buffer

	std::string req_url;			// Request URL
	char proxy_url[1024];			// Proxy URL
	int proxy_local;				// ProxyLocal flag

	char *req_header;				// Request Header (optonal)

	char varstr[256];				// VarRequest request token
	char *postdata;					// Post data
	char *vardata;					// Transfer destination
	size_t varsize;					// Transfer max size
	CURL *curl;
	CURLM *mcurl;
};


#endif
