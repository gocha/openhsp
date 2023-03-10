;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
;

%type
拡張命令
%ver
3.7
%note
hgimg3.asまたはhspogg.asをインクルードすること。

%date
2022/10/23
%author
onitama
%dll
hspogg
%url
https://hsp.tv/
%port
Win
%portinfo
Windows XP以降(DirectX7)環境が必要です。





%index
dmmini
サウンド機能初期化
%group
拡張マルチメディア制御命令
%prm
%inst
サウンド機能の初期化を行ないます。
プログラム実行時の最初に１回だけ初期化を行なう必要があります。
これ以降は、dmm〜で始まる命令を使用して、DirectSoundによるサウンド再生機能を使用することが可能になります。
dmmini命令により、初期化が行なわれた時にのみサウンド機能が使用されます。
HGIMG3使用時でも、サウンド関連機能の初期化が行なわれない場合は、DirectSoundなどサウンドに関するAPIが使用されることはありません。
HGIMG3と他のサウンド関連プラグインを使用する場合は、通常通りお使い頂けます。

%href
dmmreset
dmmbye


%index
dmmreset
サウンド機能の設定をリセット
%group
拡張マルチメディア制御命令
%prm
%inst
サウンド機能の設定をリセットします。
読み込まれていた、すべてのサウンドデータは破棄されます。

%href
dmmini
dmmbye


%index
dmmbye
サウンド機能終了処理
%group
拡張マルチメディア制御命令
%prm
%inst
サウンド機能の終了処理を行ないます。
通常は、終了処理が自動的に行なわれるので、この命令を入れる必要はありません。

%href
dmmreset
dmmini


%index
dmmdel
サウンドデータを削除
%group
拡張マルチメディア制御命令
%prm
p1
p1(0) : サウンドID
%inst
p1で指定したサウンドIDの情報を破棄します。
%href
dmmload


%index
dmmvol
サウンドデータの音量設定
%group
拡張マルチメディア制御命令
%prm
p1,p2
p1(0) : サウンドID
p2(0) : 音量(-10000〜0)
%inst
p1で指定したサウンドIDの音量(ボリューム)を設定します。
p2で設定する音量を指定します。0が最大の音量(0db)となり、-10000が最小の音量(無音)になります。
設定値の単位は、db(デシベル)になっているため、人間が感じる音量と異なっています。人が聞いた際に自然な音量を設定するサンプルとして、volsamp.hspが用意されていますので参考にしてみてください。
※mmvol命令とは値の分解能、指定される値の意味が異なるので注意してください

%href
dmmpan
dmmload


%index
dmmpan
サウンドデータのパン設定
%group
拡張マルチメディア制御命令
%prm
p1,p2
p1(0) : サウンドID
p2(0) : パンニング値(-10000〜10000)
%inst
p1で指定したサウンドIDのパン(ステレオバランス)を設定します。
p2で設定するパンニング値を指定します。
-10000で左側100%となり、10000で右側100%になります。
※mmpan命令とは値の分解能が異なるので注意してください

%href
dmmvol
dmmload


%index
dmmloop
サウンドデータのループ設定
%group
拡張マルチメディア制御命令
%prm
p1,p2
p1(0) : サウンドID
p2(0) : ループポイント(-1=ループなし)
%inst
p1で指定したサウンドIDのループ情報を設定します。
p2に0以上の値を指定した場合には、再生が繰り返されます。
p2がマイナス値の場合は、ループを行ないません。
oggファイル再生時は、p2でループポイントの指定を行なうことが可能です。ループポイントは、サンプル単位(44.1kHzの場合は、44100分の1秒)で数値を指定します。

%href
dmmload


%index
dmmload
サウンドデータの読み込み
%group
拡張マルチメディア制御命令
%prm
"ファイル名",p1,p2
"ファイル名" : 読み込みを行なうファイル名
p1(-1) : 登録するサウンドID (-1=自動割り当て)
p2(0)  : 再生モード(0=通常、1=リピート)
%inst
"ファイル名"で指定されたファイルをサウンドデータとして登録します。
サウンドデータは、wave形式(拡張子.wav)または、ogg vorbis形式(拡張子.ogg)のファイルを指定します。
p1に登録するサウンドID番号(0から始まる任意の数値)を指定することで、これ以降はサウンドID番号をもとに各種機能を使用することができるようになります。
p1の指定を省略、またはマイナス値にした場合は、登録されていないサウンドID番号を自動的に割り当てます。
割り当てられたサウンドID番号は、dmmload命令実行後にシステム変数statに代入されます。
p2で再生モードを指定することができます。
再生モードが、0の場合は１回のみの再生。1の場合は、繰り返し(リピート)再生になります。(ogg vorbis形式の繰り返し再生については、dmmloop命令を使用してください。)
wave形式(拡張子.wav)及び、ogg vorbis形式(拡張子.ogg)のファイルは、memfile命令で指定したメモリ内のイメージを含め、dpmファイルなどHSPで使用可能なファイルをすべて利用することができます。
その際にファイルサイズ分のデータを目盛りに展開するので、大きなファイルを使用する際には注意してください。
また、ogg vorbis形式として拡張子「.s」を使用することが可能です。この場合は、ファイルをメモリに展開せず、ストリーミングにより再生されます。大きいサイズのファイルを再生する場合は、拡張子を「.s」として再生することも検討ください。
%href
dmmloop
dmmdel


%index
dmmplay
サウンドデータの再生
%group
拡張マルチメディア制御命令
%prm
p1,p2
p1(0) : サウンドID
p2(0) : 開始ポイント
%inst
p1で指定したサウンドIDを再生します。
すでに指定されたサウンドIDが再生中の場合は、最初から再生されます。
p2で開始ポイントを指定することができます。
p2が省略されるか0の場合は、サウンドデータの最初から再生され、それ以外の場合は最初からのオフセット位置として途中から再生されます。
p2で指定する単位は、サウンドデータがwav形式の場合は、バイト数(byte)。
ストリームデータ(ogg vorbis形式)の場合は、サンプル数(samples)になります。
尚、ストリームデータの同時再生には対応していません。

%href
dmmstop
dmmvol
dmmpan
dmmloop
dmmload


%index
dmmstop
サウンドデータの再生停止
%group
拡張マルチメディア制御命令
%prm
p1
p1(0) : サウンドID (-1=すべてのサウンド)
%inst
p1で指定したサウンドIDの再生を停止します。
p1にマイナス値を指定した場合には、再生中のすべてのサウンドを停止します。

%href
dmmplay
dmmload


%index
dmmstat
サウンドデータの状態取得
%group
拡張マルチメディア制御命令
%prm
p1,p2,p3
p1 : 状態が取得される変数
p2(0) : サウンドID
p3(0) : 取得モード
%inst
p2で指定したサウンドIDの状態を取得して、p1の変数に代入します。
p3で取得するモードを指定することができます。
取得モードの値は、以下の通りです。
^p
	モード値  内容
	------------------------------------------------------
	    0     設定フラグ値
	    1     ボリューム値
	    2     パンニング値
	    3     再生レート(0=オリジナル)
	    4,5   ループポイント(下位、上位16bit)
	    16    再生中フラグ(0=停止中/1=再生中)
	   $100   oggサウンドの再生位置(実数値)
	   $101   oggサウンドの全体サイズ(実数値)
^p

%href
dmmplay
dmmload


