;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
;

%type
拡張命令
%ver
3.51
%note
hspinet.asをインクルードすること。

%date
2017/09/13
%author
onitama
%dll
hspinet
%url
http://hsp.tv/
%port
Win


%index
netinit
ネット接続の初期化
%group
拡張入出力制御命令
%inst
Wininet.dllの初期化を行ないます。
net〜で始まる命令を使用する際には、最初に１回だけ必ず実行する必要があります。
実行後に結果がシステム変数statに格納されます。
0ならば正常終了、それ以外はエラーが発生したことを示しています。
%href
netterm



%index
netterm
ネット接続の終了
%group
拡張入出力制御命令
%inst
Wininet.dllの終了処理を行ないます。
通常、この命令はプログラム終了時に自動的に呼び出されるため、特にスクリプトに記述する必要はありません。
%href
netinit



%index
netexec
最小単位の処理を実行
%group
拡張入出力制御命令
%prm
p1
p1 : 処理の結果が代入される変数

%inst
最小単位の処理を実行します。
サーバーからの応答待ちや、ダウンロード中など時間のかかる処理を細かい単位で実行します。
メインプログラムでは、await命令などで細かく待ち時間(ウェイト)を取りながらnetexec命令を呼び出す必要があります。
^p
例:
	;	結果待ちのためのループ
	repeat
	netexec res
	if res : break
	await 50
	loop
^p
実行後、結果がp1で指定された変数に代入されます。
内容が0の場合は、処理が継続中であることを意味します。
内容が1の場合は、処理が正常に終了していることを意味します。
内容がマイナス値の場合は、何らかのエラーが発生したことを示しています。
statが0以外の値になった場合は、それに応じた処理を適宜スクリプト側で処理するようにしてください。

%href
netmode
netsize



%index
netmode
モードの取得
%group
拡張入出力制御命令
%prm
p1
p1 : モード値が代入される変数

%inst
現在の処理モードを取得します。
p1で指定された変数にモード値が代入されます。
モード値の内容は以下の通りです。
httpリクエストは、INET_MODE_READYの状態で発行するようにしてください。
ftpリクエストは、INET_MODE_FTPREADYの状態で発行するようにしてください。
^p
ラベル             | 値    状態
------------------------------------------------------
INET_MODE_NONE     |  0    未初期化の状態
INET_MODE_READY    |  1    待機状態
INET_MODE_REQUEST  |  2    httpリクエスト受付
INET_MODE_REQSEND  |  3    httpリクエスト送信中
INET_MODE_DATAWAIT |  4    httpデータ受信中
INET_MODE_DATAEND  |  5    httpデータ受信終了処理中
INET_MODE_INFOREQ  |  6    http情報リクエスト送信中
INET_MODE_INFORECV |  7    http情報データ受信中
INET_MODE_FTPREADY |  8    ftp待機状態
INET_MODE_FTPDIR   |  9    ftpディレクトリ情報取得中
INET_MODE_FTPREAD  |  10   ftpファイル受信中
INET_MODE_FTPWRITE |  11   ftpファイル送信中
INET_MODE_FTPCMD   |  12   ftpコマンド送信終了処理中
INET_MODE_FTPRESULT|  13   ftpサーバー返信データ受信中
INET_MODE_ERROR    |  14   エラー状態
^p

%href
netexec



%index
neterror
ネットエラー文字列の取得
%group
拡張入出力制御命令
%prm
p1
p1 : エラー文字列が代入される変数

%inst
エラー発生時の詳細を示す文字列を取得します。
p1で指定した変数に、文字列として代入されます。



%index
neturl
URLの設定
%group
拡張入出力制御命令
%prm
"URL"
"URL" : URLを示す文字列

%inst
httpリクエストを行なうURLを設定します。
URLは、ファイル名を除いた形でスキーム名を含めて設定する必要があります。
「http://www.onionsoft.net/hsp/index.html」の場合は、「http://www.onionsoft.net/hsp/」までを設定してください。
httpリクエストは必ず、neturl命令によるURL設定を先に行なっておいてください。neturl命令実行の時点では、まだhttpリクエストは発行されません。
httpリクエストの発行は、netrequest命令またはnetload命令によって行なわれます。
SSL接続によるリクエストを行なう場合には、「https://」から始まるURLを指定してください。
%href
netrequest
netload
netfileinfo



%index
netrequest
httpリクエスト発行
%group
拡張入出力制御命令
%prm
"FileName"
"FileName" : リクエストを行なうファイル名

%inst
httpリクエストを行ないます。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
netrequest命令でhttpリクエストを発行した後は、netexec命令により受信処理をスクリプト側で行なう必要があります。
受信処理を自動で行なうためのnetload命令も別途用意されています。
%href
neturl
netload
netfileinfo



%index
netload
httpファイル取得
%group
拡張入出力制御命令
%prm
"FileName"
"FileName" : リクエストを行なうファイル名

%inst
httpリクエストを行ないます。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
netload命令は、ファイルの取得が終了するまで、処理を中断します。
手軽にファイルの取得を行なうことが可能ですが、大きなファイルや受信状態の悪い場合などは、そのまま画面が停止したままになる可能性もあるので注意してください。
ファイルの受信中に、並行して別な処理を行ないたい場合には、netrequest命令を使用してhttpリクエストを行なってください。
%href
neturl
netrequest
netfileinfo



%index
netfileinfo
httpファイル情報取得
%group
拡張入出力制御命令
%prm
p1,"FileName"
p1         : ファイル情報が代入される変数名
"FileName" : リクエストを行なうファイル名

%inst
httpサーバー上にあるファイル情報を取得します。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
取得に成功すると、システム変数statの値が0となり、p1で指定した変数に文字列型でサーバーが返した情報文字列が代入されます。
取得に失敗した場合は、システム変数statに0以外が代入されます。
サーバーが返す情報の種類は、httpサーバーによって異なります。
詳しくは、RFCなどhttpプロトコルの解説を参照してください。
netfileinfo命令は、ファイルの取得が終了するまで、処理を中断します。
%href
neturl
netload



%index
netdlname
ダウンロード名の設定
%group
拡張入出力制御命令
%prm
"FileName"
"FileName" : ダウンロードされた時のファイル名

%inst
ファイルを取得する際のファイル名を設定します。
netdlname命令によってファイル名を設定していない場合は、httpリクエストを行なったファイル名が使用されます。
netdlname命令に、空の文字列("")を指定した場合も、httpリクエストを行なったファイル名が使用されます。
%href
netrequest
netload



%index
netproxy
プロキシの設定
%group
拡張入出力制御命令
%prm
"ServerName",p1,p2
"ServerName" : リクエストを行なうファイル名
p1 (0)       : ポート番号
p2 (0)       : ローカル接続フラグ

%inst
http接続の際に使用されるプロキシ(代理)サーバーを設定します。
"ServerName"で、プロキシサーバー名を設定します。
空の文字列("")を指定した場合には、プロキシは設定されません。
p1でhttpが使用するプロキシサーバーのポート番号を指定します。
p2で、ローカルアドレスをプロキシ経由のアクセスから除外するかどうかを設定します。1の場合は、ローカルアドレスのみプロキシから除外されます。0の場合は、ローカルアドレスも含めてプロキシを使用します。
netproxy命令が実行されると、それまでのセッションが解除され、neturl命令や、netheader命令による設定はリセットされます。
^p
	例:
	netinit
	if stat : dialog "ネット接続できません。" : end
	netproxy "proxy_server",8080,1
	neturl "http://www.onionsoft.net/hsp/"
	netload "index.html"
^p
%href
netagent
netheader



%index
netagent
エージェントの設定
%group
拡張入出力制御命令
%prm
"AgentName"
"AgentName" : 設定するエージェント名

%inst
http接続の際にサーバーに渡されるエージェント情報の文字列を設定します。"AgentName"で指定したエージェント名が設定されます。
空の文字列("")を指定した場合には、デフォルトの設定になります。
netagent命令が実行されると、それまでのセッションが解除され、neturl命令や、netheader命令による設定はリセットされます。
%href
netproxy
netheader



%index
netheader
ヘッダ文字列の設定
%group
拡張入出力制御命令
%prm
"HeaderString"
"HeaderString" : ヘッダに追加される文字列

%inst
http接続の際にサーバーに渡されるヘッダ文字列を設定します。
空の文字列("")を指定した場合には、無設定になります。
ヘッダ文字列は、通常設定する必要ありませんが、何からの付加情報や動作設定を行なう場合に使用することができます。
netheader命令で設定したヘッダ文字列は、それ以降のリクエストすべてに適用されます。
^p
	例:
	; リファラーを追加する
	netheader "Referer:http://www.onionsoft.net/\n\n"
^p
%href
netagent



%index
netsize
ファイル受信サイズの取得
%group
拡張入出力制御命令
%prm
p1
p1 : ファイル受信サイズが代入される変数

%inst
netrequest命令で発行されたhttpリクエストに対するファイルがどれだけのサイズを受信したかを取得します。
p1で指定された変数にファイル受信サイズが代入されます。
ファイル受信サイズは、netexec命令で受信が行なわれた内容を調べるためのものです。あらかじめ、ファイル情報取得でファイルサイズを調べておけば、進行の割合を計ることが可能です。
%href
netexec



%index
filecrc
ファイルのCRC32を取得
%group
拡張入出力制御命令
%prm
p1,"FileName"
p1         : CRC値が代入される変数名
"FileName" : CRCチェックを行なうファイル名

%inst
指定されたファイルのCRC32を求めてp1の変数に代入します。
CRC32は、ファイルの内容をもとに算出された32bitの数値です。
ファイル内容のチェックなどに使用することができます。
%href
filemd5



%index
filemd5
ファイルのMD5を取得
%group
拡張入出力制御命令
%prm
p1,"FileName"
p1         : MD5値が代入される変数名
"FileName" : MD5チェックを行なうファイル名

%inst
指定されたファイルのMD5を求めてp1の変数に代入します。
MD5値は、文字列型で「f96b697d7cb7938d525a2f31aaf161d0」のような32文字の16進数として表現されます。
MD5値は、ファイルの内容を一意に表わすハッシュ値として使用することができます。詳しくは、MD5についての資料などを参照してください。
ファイル内容のチェックなどに使用することができます。
%href
varmd5
filecrc



%index
ftpopen
FTPセッションの開始
%group
拡張入出力制御命令
%prm
p1,p2,p3,p4,p5
p1 : ftpサーバーアドレス(文字列)
p2 : ftpログインユーザー名(文字列)
p3 : ftpログインユーザーパスワード(文字列)
p4 : ポート番号(省略可能)
p5 : PASSIVEモードフラグ(省略可能)

%inst
ftpサーバーに接続してセッションを開始します。
p1にサーバーのアドレス、p2にユーザー名、p3にパスワードを指定してftpに接続します。
p4パラメーターでポート番号を指定することができます。
p4の指定を省略した場合は、標準のポート番号が使用されます。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
p5パラメーターで接続時のPASSIVEモードフラグを設定することができます。
p5に1を設定した場合は、PASSIVEモードでftp接続を行ないます。0または省略した場合は、通常のftp接続となります。
^
あらかじめ、netinit命令によって初期化を行なう必要があります。
ftpセッションを開始した後は、ftp関連命令のみ使用することができます。httpなど他のネット操作を行なう場合には、必ずftpclose命令によりftpセッションを終了させるようにしてください。

%href
ftpclose


%index
ftpclose
FTPセッションの終了
%group
拡張入出力制御命令

%inst
ftpopen命令で開始されたセッションを終了させます。

%href
ftpopen


%index
ftpresult
FTP処理結果文字列の取得
%group
拡張入出力制御命令
%prm
p1
p1 : FTP処理結果文字列が代入される変数

%inst
ftp関連命令による処理に対するサーバーの返信メッセージを
取得して、p1に指定された変数に代入します。
p1の変数には、文字列データとして代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen


%index
ftpdir
FTPディレクトリ移動
%group
拡張入出力制御命令
%prm
p1,p2
p1 : 現在のディレクトリ位置が代入される変数
p2 : 移動先のディレクトリ名(文字列)

%inst
p1で指定した変数に、ftpサーバー上のカレントディレクトリ名を文字列データとして代入します。
p2にディレクトリ名を指定した場合には、その場所へ移動を行ないます。
p2の指定を省略した場合には、ディレクトリ移動は行なわれません。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen


%index
ftpdirlist
FTPディレクトリリスト取得1
%group
拡張入出力制御命令

%inst
ftpサーバー上のカレントディレクトリにあるファイルリストを取得するためのリクエストを行ないます。
実際のファイルリストは、ftpdirlist2命令で行ないます。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftpdirlist2


%index
ftpdirlist2
FTPディレクトリリスト取得2
%group
拡張入出力制御命令
%prm
p1
p1 : ファイルリストが代入される変数

%inst
この命令は、必ずftpopen命令によりftpセッションを開始し、ftpdirlist命令によりファイルリスト取得が終了した後で使用してください。
以下は、ファイルリスト取得するまでの例です。
^p
例:
	;	結果待ちのためのループ
	ftpdirlist
	repeat
	netexec mode
	if res : break
	await 50
	loop
	ftpdirlist2 res
^p
ファイルリスト取得は、ftpdirlist命令によるリクエスト、netexec命令による受信待ち、ftpdirlist2命令による結果の取得という３つの手順に分けて行なう必要があります。
p1に代入されるファイルリストは、１行あたり１エントリごとに区切られている複数行文字列データになります。
１行は、「"ファイル名"」、ファイルサイズ、更新日時の順番に「,」で区切られた形になります。

%href
ftpopen
ftpdirlist
netexec


%index
ftpcmd
FTPコマンドの実行
%group
拡張入出力制御命令
%prm
p1
p1 : 実行するFTPコマンド文字列

%inst
p1で指定されたFTPコマンドを実行します。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen


%index
ftprmdir
FTPディレクトリの削除
%group
拡張入出力制御命令
%prm
p1
p1 : 削除するディレクトリを示す文字列

%inst
p1で指定されたディレクトリを削除します。
実行に成功した場合は、システム変数statに0が代入され、
失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftpmkdir


%index
ftpmkdir
FTPディレクトリの作成
%group
拡張入出力制御命令
%prm
p1
p1 : 作成するディレクトリを示す文字列

%inst
p1で指定されたディレクトリを作成します。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftprmdir


%index
ftpget
FTPファイル取得
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : サーバー上から取得するファイル名(文字列)
p2("") : ローカルに作成されるファイル名(文字列)
p3(0)  : 転送モード(0=バイナリ/1=アスキー)

%inst
ftpサーバー上のファイルを取得します。
p1でサーバー上のファイル名を指定します。
p2でダウンロードして作成されるファイル名を指定します。
p2の指定を省略または""にした場合は、p1と同じ名前が使用されます。
p3で転送モードを指定します。転送モードを省略または0に指定した場合はバイナリデータとして、1に指定した場合は、アスキーデータとして転送を行ないます。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftpput


%index
ftpput
FTPファイル送信
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : サーバー上に作成するファイル名(文字列)
p2("") : ローカルから送信されるファイル名(文字列)
p3(0)  : 転送モード(0=バイナリ/1=アスキー)

%inst
ftpサーバー上にファイルを送信します。
p1でサーバー上に作成するファイル名を指定します。
p2でローカルから送信されるファイル名を指定します。
p2の指定を省略または""にした場合は、p1と同じ名前が使用されます。
p3で転送モードを指定します。転送モードを省略または0に指定した場合はバイナリデータとして、1に指定した場合は、アスキーデータとして転送を行ないます。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftpget


%index
ftprename
FTPファイル名前変更
%group
拡張入出力制御命令
%prm
p1,p2
p1 : 変更元のファイル名(文字列)
p2 : 新しいファイル名(文字列)

%inst
ftpサーバー上のファイル名を変更します。
p1で変更元のファイル名を、p2で新しいファイル名を指定します。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftpdelete


%index
ftpdelete
FTPファイル削除
%group
拡張入出力制御命令
%prm
p1
p1 : 削除するファイル名(文字列)

%inst
ftpサーバー上のファイルを削除します。
実行に成功した場合は、システム変数statに0が代入され、失敗した場合はそれ以外の値が代入されます。
この命令は、必ずftpopen命令によりftpセッションを開始してから使用してください。

%href
ftpopen
ftprename


%index
netrequest_get
httpリクエスト発行(GET)
%group
拡張入出力制御命令
%prm
"FileName"
"FileName" : リクエストを行なうファイル名

%inst
httpリクエストを行ないます。
netrequest命令と同様ですが、ダウンロードしたデータイメージをファイルではなく、メモリ上のデータとして取得できます。
^
"FileName"で、リクエストを行なうファイル名を指定します。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
^
netrequest命令でhttpリクエストを発行した後は、netexec命令により受信処理を
スクリプト側で行なう必要があります。
処理が完了した後は、netgetv命令またはnetgetv_data命令により任意の変数でデータを受け取ることができます。
POST形式でCGIにデータをリクエストする場合は、netrequest_post命令を使用してください。

%href
netgetv
netgetv_data
netgetv_size
netrequest
netrequest_post
netrequest_put
netrequest_delete
neturl


%index
netrequest_post
httpリクエスト発行(POST)
%group
拡張入出力制御命令
%prm
"FileName",p1
"FileName" : リクエストを行なうファイル名
p1         : POST用のデータを格納した文字列型変数名

%inst
httpリクエストを行ないます。
netrequest命令と同様ですが、ダウンロードしたデータイメージをファイルではなく、メモリ上のデータとして取得できます。
また、POST形式によるCGIパラメーター受け渡しに対応しています。
^
"FileName"で、リクエストを行なうファイル名を指定します。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
p1に、POST用のデータを格納した変数名を指定します。
あらかじめ、変数は文字列型でPOST形式のデータを格納しておく必要があります。
POST形式のデータは、GET形式のURLで指定される「&」で区切られたパラメーターと同様のものになります。
ただし、バイナリデータを送付する場合は、データを文字列にエンコードする必要があります。
netrequest_post命令は、渡された文字列をそのままPOSTデータとして発行するため、このエンコードは事前に行なっておいてください。
^p
例:
;	URLを指定
neturl "http://www.onionsoft.net/hsp/beta/"

;	POST形式でCGIにパラメーターを渡す
prm = "mode=find&cond=and&log=0&word=script"
netrequest_post "betabbs.cgi",prm
^p
netrequest命令でhttpリクエストを発行した後は、netexec命令により受信処理をスクリプト側で行なう必要があります。
処理が完了した後は、netgetv命令またはnetgetv_data命令により任意の変数でデータを受け取ることができます。
GET形式でCGIにデータをリクエストする場合は、netrequest_get命令を使用してください。

%href
netgetv
netgetv_data
netgetv_size
netrequest
netrequest_get
netrequest_put
netrequest_delete
neturl


%index
netrequest_delete
httpリクエスト発行(DELETE)
%group
拡張入出力制御命令
%prm
"FileName"
"FileName" : リクエストを行なうファイル名

%inst
httpリクエストを行ないます。
netrequest_delete命令により、DELETEリクエストを送信し、指定されたリソース(ファイル名)を削除します。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
^
netrequest命令でhttpリクエストを発行した後は、netexec命令により受信処理を
スクリプト側で行なう必要があります。
処理が完了した後は、netgetv命令またはnetgetv_data命令により任意の変数でデータを受け取ることができます。

%href
netgetv
netgetv_data
netgetv_size
netrequest
netrequest_put
netrequest_get
neturl


%index
netrequest_put
httpリクエスト発行(PUT)
%group
拡張入出力制御命令
%prm
"FileName",p1
"FileName" : リクエストを行なうファイル名
p1         : PUT用のデータを格納した文字列型変数名

%inst
httpリクエストを行ないます。
netrequest_put命令により、PUTリクエストを送信し、指定されたリソースの更新を行うことができます。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
パラメーターの情報は、netrequest_post命令と同様に、POST形式によるCGIパラメーター受け渡しに対応しています。
^
"FileName"で、リクエストを行なうファイル名を指定します。
先に、neturl命令によりファイル名を除いたURLを指定しておく必要があります。
p1に、POST用のデータを格納した変数名を指定します。
あらかじめ、変数は文字列型でPOST形式のデータを格納しておく必要があります。
POST形式のデータは、GET形式のURLで指定される「&」で区切られたパラメーターと同様のものになります。
^
netrequest命令でhttpリクエストを発行した後は、netexec命令により受信処理をスクリプト側で行なう必要があります。
処理が完了した後は、netgetv命令またはnetgetv_data命令により任意の変数でデータを受け取ることができます。
GET形式でCGIにデータをリクエストする場合は、netrequest_get命令を使用してください。

%href
netgetv
netgetv_data
netgetv_size
netrequest
netrequest_get
netrequest_post
netrequest_delete
neturl


%index
netgetv
httpリクエストの結果を取得
%group
拡張入出力制御命令
%prm
p1
p1 : データが代入される変数

%inst
netrequest_get、netrequest_post命令によるhttpリクエストの結果を取得します。
必ず、netexec命令による受信処理で、ダウンロードが完了したことを確認してから、データを取得するようにしてください。
p1で指定された変数は、自動的に必要なサイズを確保した文字列型として初期化されます。
(あらかじめ変数を初期化したり、メモリを確保しておく必要はありません。)
取得されるデータはテキスト(文字列)として処理されます。それ以外のデータ(バイナリ)を取得する場合は、netgetv_data命令を使用してください。
命令実行後に、システム変数statにデータサイズが代入されます。

%href
netgetv_data
netgetv_size
netrequest_get
netrequest_post
netrequest_put
netrequest_delete



%index
varmd5
変数バッファのMD5を取得
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1    : MD5値が代入される変数名
p2    : 参照される変数名
p3(0) : バッファサイズ

%inst
指定された変数バッファの内容からMD5を求めてp1の変数に代入します。
MD5値は、文字列型で「f96b697d7cb7938d525a2f31aaf161d0」のような32文字の16進数として表現されます。
MD5値は、メモリの内容を一意に表わすハッシュ値として使用することができます。詳しくは、MD5についての資料などを参照してください。
ファイルの内容からMD5を求める場合は、filemd5命令を使用してください。
%href
filemd5


%index
b64encode
BASE64エンコード
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : BASE64変換された文字列が代入される変数名
p2     : 変換元データを持つ変数名
p3(-1) : バッファサイズ

%inst
p2で指定された変数バッファの内容をBASE64エンコード(変換)してp1の変数に代入します。
p3の値を省略またはマイナス値にした場合は、p2に含まれるデータを文字列として自動的にサイズが決定されます。
BASE64は、文字列型として格納されます。バイナリデータなどを一時的に文字列に変換する場合などに使用されます。
BASE64形式の文字列をもとのデータにデコード(戻す)場合は、b64decode命令を使用してください。
%href
b64decode


%index
b64decode
BASE64デコード
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : デコードされたデータが代入される変数名
p2     : BASE64形式のデータを持つ変数名
p3(-1) : バッファサイズ

%inst
p2で指定された変数バッファの内容をBASE64デコードしてp1の変数に代入します。
p2の変数には、BASE64エンコードされた文字列が代入されている必要があります。
%href
b64encode


%index
rc4encode
RC4エンコード
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : 変数名
p2     : パスワード文字列
p3(-1) : バッファサイズ

%inst
p1で指定された変数バッファの内容をRC4互換(ARCFOUR)アルゴリズムで暗号化します。
暗号化の際に、p2で指定されたパスワード文字列をキーとして使用します。
p3でバッファサイズを指定します。p3を省略またはマイナス値とした場合には、変数バッファの内容を文字列として自動的にサイズを決定します。
RC4暗号では、暗号化する前と後でデータサイズに変更はありません。
また、エンコードとデコードは同じプロセスで行われるため、エンコードを行ったデータに対して、再度同じキーで暗号化することでもとのデータに復号されます。

%href
b64encode
b64decode


%index
urlencode
URLエンコード
%group
拡張入出力制御命令
%prm
p1,p2
p1     : URLエンコードされた文字列が代入される変数名
p2     : 変換元データを持つ変数名

%inst
p2で指定された変数バッファの内容(文字列)をURLエンコード(変換)してp1の変数に代入します。
p1で指定される変数は自動的に文字列型として初期化されます。
URLエンコードで出力される文字数は最大で4095文字までの制限がありますので注意してください。
URLエンコード形式の文字列をもとのデータにデコード(戻す)場合は、urldecode命令を使用してください。
%href
urldecode


%index
urldecode
URLデコード
%group
拡張入出力制御命令
%prm
p1,p2
p1     : デコードされたデータが代入される変数名
p2     : URLエンコード形式のデータを持つ変数名

%inst
URLエンコードされた文字列を元の文字列に戻します。
p2で指定された変数バッファの内容をデコードしてp1の変数に代入します。
デコードで出力される文字数は最大で4095文字までの制限がありますので注意してください。
%href
urlencode


%index
jsonopen
JSON形式を開く
%group
拡張入出力制御命令
%prm
p1,p2
p1     : JSONポインタ値が代入される変数名
p2     : JSON形式のデータを持つ変数名

%inst
JSON形式の文字列を読み込み、内容にアクセス可能な状態にします。
p2で指定された変数に格納されている文字列をJSON形式とみなして、データのパースを行ないます。
読み込み後は、p1で指定された変数にJSONポインタ値が代入されます。
JSON形式を扱う命令でJSONポインタ値を指定することにより、各種データにアクセスすることが可能になります。
jsonopen命令でデータを読み込ませた後は、必ず最後にjsonclose命令を実行してメモリを解放する必要があります。
%href
jsonclose


%index
jsonclose
JSON形式の終了処理
%group
拡張入出力制御命令

%inst
jsonopen命令で読み込ませたデータのメモリを解放します。
%href
jsonopen


%index
jsonout
JSON形式データを変数に出力する
%group
拡張入出力制御命令
%prm
p1,p2
p1     : JSON形式のデータが代入される変数名
p2(-1) : JSONポインタ値

%inst
JSON形式データをp1で指定した変数に出力します。
p2で出力するJSONデータのポインタ値を指定します。
p2を省略またはマイナス値とした場合は、jsonopen命令で読み込まれたデータが対象になります。
p1で指定された変数は文字列型として初期化されサイズも自動的に確保されます。

%href
jsonopen


%index
jsongetobj
JSONオブジェクトを得る
%group
拡張入出力制御命令
%prm
p1,"name",p2
p1     : JSONポインタ値が代入される変数名
"name" : オブジェクト識別名
p2(-1) : JSONポインタ値

%inst
"name"で指定した名前のオブジェクトを取得し、p1で指定した変数にJSONポインタ値を代入します。
p2で検索対象となるオブジェクト(JSONポインタ値)を指定します。
p2を省略またはマイナス値にするとjsonopen命令で読み込ませたデータのルート階層が使用されます。
指定された名前が存在しなかった場合はJSONポインタ値として0が代入されます。
p2に空(NULL)のJSONポインタ値を指定した場合は、システム変数statが1になり実行は行なわれません。
%href
jsonnext


%index
jsonnext
次のJSONオブジェクトを得る
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1     : JSONポインタ値が代入される変数名
p2(-1) : JSONポインタ値
p3(0)  : 取得オプション

%inst
p2で指定されたJSONオブジェクト(JSONポインタ値)に関連する値を取得し、p1で指定した変数に代入します。
取得される値は、p3の取得オプションによって変わります。p3は以下の値を指定することができます。
^p
取得オプション   内容
--------------------------------------------
  0              次のオブジェクト(next)
  1              前のオブジェクト(prev)
  2              子階層のオブジェクト(child)
  3              オブジェクトのtype値
^p
jsonnext命令により、同じ階層にあるオブジェクトや、子階層(配列)内のオブジェクトを得ることができます。
p2を省略またはマイナス値にするとjsonopen命令で読み込ませたデータのルート階層が使用されます。
指定されたJSONオブジェクトが存在しなかった場合はJSONポインタ値として0が代入されます。
p2に空(NULL)のJSONポインタ値を指定した場合は、システム変数statが1になり実行は行なわれません。
%href
jsongetobj


%index
jsongets
JSONオブジェクトから文字列を得る
%group
拡張入出力制御命令
%prm
p1,"name",p2
p1     : 取得された文字列が代入される変数名
"name" : オブジェクト識別名
p2(-1) : JSONポインタ値

%inst
オブジェクトに記録された文字列を取得し、p1で指定した変数に代入します。
p2で対象となるオブジェクト(JSONポインタ値)を指定します。
"name"を省略または中身のない文字列("")に指定した場合は、p2で指定されたオブジェクトそのものに記録されている文字列を取得します。
"name"で名前を指定した場合、p2で指定されたオブジェクトと同階層にあるオブジェクトから同じ名前を持つオブジェクトを検索し、値を取得します。
指定された名前が存在しない場合は、p1に代入は行なわれずにシステム変数statに1を代入して終了します。
p2を省略またはマイナス値にするとjsonopen命令で読み込ませたデータのルート階層が使用されます。
p2に空(NULL)のJSONポインタ値を指定した場合は、システム変数statが1になり実行は行なわれません。
%href
jsongeti
jsonnkf


%index
jsongeti
JSONオブジェクトから整数値を得る
%group
拡張入出力制御命令
%prm
p1,"name",p2
p1     : 取得された整数値が代入される変数名
"name" : オブジェクト識別名
p2(-1) : JSONポインタ値

%inst
オブジェクトに記録された整数値を取得し、p1で指定した変数に代入します。
p2で対象となるオブジェクト(JSONポインタ値)を指定します。
"name"を省略または中身のない文字列("")に指定した場合は、p2で指定されたオブジェクトそのものに記録されている整数値を取得します。
"name"で名前を指定した場合、p2で指定されたオブジェクトと同階層にあるオブジェクトから同じ名前を持つオブジェクトを検索し、値を取得します。
指定された名前が存在しない場合は、p1に代入は行なわれずにシステム変数statに1を代入して終了します。
p2を省略またはマイナス値にするとjsonopen命令で読み込ませたデータのルート階層が使用されます。
p2に空(NULL)のJSONポインタ値を指定した場合は、システム変数statが1になり実行は行なわれません。
%href
jsongets


%index
jsonnewobj
JSONオブジェクトを新規作成
%group
拡張入出力制御命令
%prm
p1,p2,"name"
p1     : JSONポインタ値が代入される変数名
p2(-1) : 親のJSONポインタ値
"name" : オブジェクト識別名

%inst
JSONオブジェクトを新規作成して、p1で指定した変数にJSONポインタ値を代入します。
p2で親になるオブジェクト(JSONポインタ値)を指定します。
p2を省略またはマイナス値にするとjsonopen命令で読み込ませたデータのルート階層が使用されます。
ユーザーが独自にJSONオブジェクトを作成する際に使用します。
JSONオブジェクトを新規作成した後は、最後に最も親の階層をjsondelobj命令で削除する必要があるので注意してください。
%href
jsondelobj


%index
jsondelobj
JSONオブジェクトを削除
%group
拡張入出力制御命令
%prm
p1
p1(0) : JSONポインタ値

%inst
JSONオブジェクトを削除します。
jsonnewobj命令によりJSONオブジェクトを新規作成した後は、最後に最も親の階層をjsondelobj命令で削除する必要があるので注意してください。
jsonopen命令で読み込ませたデータは、jsonclose命令により解放してください。(jsondelobj命令で解放する必要はありません。)
%href
jsonnewobj


%index
jsonsetprm
JSONオブジェクトに値を設定する
%group
拡張入出力制御命令
%prm
p1,p2,p3
p1(0)  : JSONポインタ値
p2(0)  : 設定値
p3(0)  : 設定オプション

%inst
p1で指定されたJSONオブジェクト(JSONポインタ値)に関連するパラメーターを設定します。
設定するパラメーターは、p3のオプションによって変わります。p3は以下の値を指定することができます。
^p
設定オプション   内容
--------------------------------------------
  0              次のオブジェクト(next)
  1              前のオブジェクト(prev)
  2              子階層のオブジェクト(child)
  3              オブジェクトのtype値
  4              オブジェクトに設定された整数値
^p
jsonsetprm命令により、子階層(配列)内のオブジェクトやオブジェクトの連結を直接設定することができます。
既に設定されている値を上書きすることで、階層構造が壊れる可能性がありますので、設定する場合には注意するようにしてください。
p1に空(NULL)のJSONポインタ値を指定した場合は、システム変数statが1になり実行は行なわれません。
%href
jsongetobj


%index
jsonputs
JSONオブジェクトに文字列を追加
%group
拡張入出力制御命令
%prm
p1,"name","strings"
p1(0)     : JSONポインタ値
"name"    : オブジェクト識別名
"strings" : 設定する文字列

%inst
p1で指定されたJSONオブジェクト(JSONポインタ値)に文字列のデータを持つオブジェクトを追加します。
"name"で、追加されるオブジェクトの識別名を、"strings"で文字列を指定します。

%href
jsonputi
jsonnkf


%index
jsonputi
JSONオブジェクトに数値を追加
%group
拡張入出力制御命令
%prm
p1,"name",p2,p3
p1(0)  : JSONポインタ値
"name" : オブジェクト識別名
p2(0)  : 設定する値
p3(0)  : 設定オプション

%inst
p1で指定されたJSONオブジェクト(JSONポインタ値)に数値のデータを持つオブジェクトを追加します。
"name"で、追加されるオブジェクトの識別名を、p2で数値を指定します。
p
設定する数値の種類は、p3のオプションによって変わります。p3は以下の値を指定することができます。
^p
設定オプション   内容
--------------------------------------------
  0              整数値
  1              BOOL値(False,True)
^p
設定オプションがBOOL値の場合は、p2の値が0以外ならばTrueを、0ならばFalseが設定されます。

%href
jsonputs


%index
jsonnkf
JSON文字列変換の設定
%group
拡張入出力制御命令
%prm
"option1","option2"
"option1" : 取得時変換オプション
"option2" : 設定時変換オプション

%inst
JSONで扱う文字列のコード変換を設定します。
jsongets、jsonputs命令で使用する文字列を変換することで、JSONデータを任意の文字コードで保持することができます。
"option1"及び、"option2"パラメーターにより、NKFによるコード変換パラメーターを指定します。
"option1"は、jsongets命令による文字列取得時に、"option2"は、jsonputs命令による文字列設定時に使用されます。
オプションの文字列は、nkfcnv命令で使用されるものと同じです。
NKFの変換でSJISの入出力を指定することにより、HSPで扱う文字コードをそのまま指定することができるようになります。

%href
jsongets
jsonputs
nkfcnv


%index
nkfcnv
NKFによる文字コード変換を行なう
%group
拡張入出力制御命令
%prm
p1,p2,"option",p3,p4
p1 : 変換後の文字列が代入される変数
p2 : 変換元の文字列が代入されている変数
"option" : NKF変換オプション
p3(-1) : 変換元の文字列サイズ
p4(-1) : 出力先の最大バッファサイズ

%inst
p2で指定された変数に格納されている文字列に対して、NKFによる文字コード変換を行ない、結果をp1で指定された変数に代入します。
"option"でNKFの変換オプションを指定することができます。これにより、入力される文字コードと出力される文字コードを任意に指定することができます。
"option"パラメーターを省略した場合は、入力コードを自動判別してSJISに変換されます。
主なオプションの一覧は以下の通りです。(オプション文字列は複数を続けて指定することも可能です)これ以外にも、多くの指定が可能です。詳しくは、doclibフォルダ内のnkf_doc.txtを参照してください。
^p
設定オプション   内容
--------------------------------------------
    j  	      JISに変換する
    e  	      EUCに変換する
    s  	      SJISに変換する
    w  	      UTF8に変換する
    J  	      変換元はJIS(ISO-2022-JP)を仮定する。
    E  	      変換元はEUC(AT&T)を仮定する。
    S  	      変換元はSJISを仮定する
    W  	      変換元はUTF-8を仮定する
    W16       変換元はUTF-16 (Little Endian)を仮定する
    W16B      変換元はUTF-16 (Big Endian)を仮定する
^p
p3で、変換元の文字列サイズ(byte数)を指定します。p3を省略するかマイナス値の場合は、入力がC言語形式のansi文字列として自動計算されます。
p4で、出力先のバッファサイズを指定します。このサイズを超えた変換は行なわれません。p4を省略するかマイナス値の場合は、デフォルトサイズ(32KB)が使用されます。
p1で指定された変数は、自動的に文字列サイズのバッファを確保した上で初期化されます。あらかじめsdimで初期化しておく必要はありません。

%href
nkfguess


%index
nkfguess
NKFによる文字コード認識結果を取得する
%group
拡張入出力制御命令
%prm
p1
p1 : 結果の文字列が代入される変数

%inst
nkfcnv命令により変換された際に、認識された変換元の文字コードを取得します。
結果は、p1で指定された変数に文字列として代入されます。必ず、先にnkfcnv命令で変換を行なっておく必要があります。

%href
nkfcnv


%index
getenv
環境変数の取得
%group
拡張入出力制御命令
%prm
p1,"name"
p1 : 結果の文字列が代入される変数
"name" : 環境変数名

%inst
環境変数の値を取得し、変数に代入します。
結果は文字列型で代入されます。
変数のバッファは文字列に合わせて自動的に調整されます。

%href


%index
getctime
文字列による日付と時刻の取得
%group
拡張入出力制御命令
%prm
p1,p2
p1 : 結果の文字列が代入される変数
mode(0) : 取得される形式の指定

%inst
日付と時刻を文字列で取得します。
modeの値により、取得するフォーマットを指定します。
^p
 mode   内容
---------------------------------------------
   0    C言語のasctime関数による現在時刻(ローカル)
        例: Sun Nov  6 08:49:37 1994
   1    C言語のasctime関数による現在時刻(GMT/UTC)
        例: Sun Nov  6 08:49:37 1994
   2    RFC 1123で定義される日付フォーマット
        例: Sun, 06 Nov 1994 08:49:37 GMT
^p

%href
gettime


%index
getenvprm
指定文字列要素の取得
%group
拡張入出力制御命令
%prm
p1, p2, "name", code
p1 : 結果の文字列が代入される変数
p2 : 検索内容が代入されている文字列型変数
"name" : 要素名
code : 区切り文字コード(省略時は'&')

%inst
getenvprm命令は、「A=123&B=456&C=789」のように特定の区切り
文字コード(この場合は「&」)で区切られた文字列の中から、
先頭部分が"name"と一致したものを取り出します。
CGIのパラメーター受け渡しなどで複数の情報が文字列として
渡されている中から、特定の項目を取り出す場合に使用します。
たとえば、変数aに「A=123&B=456&C=789」が代入されている場合、
「getenvprm res,a,"B="」を実行すると、変数resには「789」という
文字列が代入されます。
p2で指定された変数は、文字列型であらかじめ初期化されている
必要があります。
該当する要素名がなかった場合は、""(長さ0の文字列)が
代入されます。
codeに区切り文字のコードを指定することが可能です。
codeの指定を省略した場合は、'&'が使用されます。

%href


%index
netgetv_data
httpリクエストの結果を取得
%group
拡張入出力制御命令
%prm
p1
p1 : データが代入される変数

%inst
netrequest_get、netrequest_post命令によるhttpリクエストの結果を取得します。
必ず、netexec命令による受信処理で、ダウンロードが完了したことを確認してから、データを取得するようにしてください。
netgetv命令と同様の動作ですが、netgetv命令はテキスト(文字列)を取得するのに対して、netgetv_data命令はバイナリデータをバッファに取得します。
そのため、p1で指定された変数には、あらかじめダウンロードに必要なメモリバッファを文字列型として確保しておく必要があります。(必要なサイズは、netgetv_size関数によって取得することができます。)
命令実行後に、システム変数statにデータサイズが代入されます。

%href
netgetv
netgetv_size
netrequest_get
netrequest_post


%index
netgetv_size
ファイル受信サイズの取得
%group
拡張入出力関数

%inst
netrequest_get、netrequest_post命令によるhttpリクエストの結果で取得したデータのサイズを戻します。
必ず、netexec命令による受信処理で、ダウンロードが完了したことを確認してから、データを取得するようにしてください。
%href
netexec
netgetv_data



