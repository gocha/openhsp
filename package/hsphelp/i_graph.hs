;
;	HSP help manager用 HELPソースファイル
;	(先頭が;の行はコメントとして処理されます)
;

%type
内蔵命令
%ver
3.2
%note
ver3.2標準命令
%date
2009/05/15
%author
onitama
%url
http://www.onionsoft.net/
%port
Win



%index
cls
画面クリア
%group
画面制御命令
%prm
p1
p1=0〜4(0) : クリアする時の色

%inst
ウィンドウ内の情報をすべてクリアします。
^
p1でクリアする５種類の色を指定することができます。
^p
色の指定値 :
 ( 0=白 / 1=明るい灰色 / 2=灰色 / 3=暗い灰色 / 4=黒 )
^p
cls命令で画面をクリアすると、 画面にあるボタンや入力ボックスなどのオブジェクト類、フォントやカラー設定が初期状態に戻ります。
%port+
Let



%index
mes
メッセージ表示
%group
画面制御命令
%prm
"strings"
"strings" : 表示するメッセージ、または変数
%inst
ウィンドウ内に、指定されたメッセージを表示します。
メッセージは、カレントポジションと呼ばれるウィンドウ上の仮想的なカーソル位置から表示され、カレントポジションが次の行に自動的に移動します。
^
表示されるメッセージのフォントは、font命令で指定することができます。
表示するメッセージに改行コードが含まれていた場合には、改行され次の行から表示を続けます。
%href
print
font
%port+
Let
%sample
	mes "mes命令は文字列を表示します"

	mes {"複数行の文字列も
表示できます"}

	font msmincho, 20, font_bold
	mes "font命令によって文字の大きさなどを変えられます"

%index
print
メッセージ表示
%group
画面制御命令
%prm
"strings"
"strings" : 表示するメッセージまたは変数

%inst
ウィンドウ内に、指定されたメッセージを表示します。
メッセージは、カレントポジションと呼ばれるウィンドウ上の仮想的なカーソル位置から表示され、カレントポジションが次の行に自動的に移動します。
^
表示されるメッセージのフォントは、font命令で指定することができます。
表示するメッセージに改行コードが含まれていた場合には、改行され次の行から表示を続けます。
^
print命令はmes命令の別名であり、どちらも同じ意味になります。
HSPでは、mes命令を使用することを推奨しています。

%href
mes
font
%port+
Let



%index
title
タイトルバー設定
%group
画面制御命令
%prm
"strings"
"strings" : 指定する文字列

%inst
p1の指定が省略されている場合には、ウィンドウのタイトルバーキャプションを、"strings"の内容に設定します。
(タイトルバーキャプションは、通常「Hot Soup Processor ver3.x」と表示されている部分のことです)

%href
objprm
%port+
Let
%portinfo
HSPLetアプレットの場合はステータスバーのテキストが変化します。

%sample
	// 「Window Title」という文字をウィンドウのタイトルバーに表示
	title "Window Title"

%index
dialog
ダイアログを開く
%group
画面制御命令
%prm
"message",p1,"option"
p1=0〜(0) : ダイアログのタイプ設定

%inst
Windowsの標準的な各種ダイアログボックスを画面に表示します。
dialog命令で出したダイアログは、 HSPのウィンドウとは別にポップアップして現われます。
^
ユーザーの操作によりダイアログを閉じるまでは、 HSPスクリプトの続きは実行されません。
^
ダイアログのタイプは、p1の設定によって変わります。
^p
   タイプ : 内容
 -----------------------------------------------------
     0    : 標準メッセージボックス + [OK]ボタン
     1    : 警告メッセージボックス + [OK]ボタン
     2    : 標準メッセージボックス + [はい][いいえ]ボタン
     3    : 警告メッセージボックス + [はい][いいえ]ボタン
    16    : ファイルOPEN(開く)ダイアログ
    17    : ファイルSAVE(保存)ダイアログ
    32    : カラー選択ダイアログ(固定色)
    33    : カラー選択ダイアログ(RGBを自由に選択)
    64〜  : 拡張ダイアログ
^p
タイプ0〜3の場合は、"message" で指定した内容を表示するメッセージボックスが現われます。また、"option"でメッセージボックスのタイトルバー文字列を指定することができます。(省略した場合はタイトルに何も表示されません)
メッセージボックスが閉じられると、押したボタンの情報がシステム変数statに代入されます。この時、変数statの内容は、
^p
  1 :「OK」ボタンが押された
  6 :「はい」ボタンが押された
  7 :「いいえ」ボタンが押された
^p
のようになります。
^
タイプ16〜17の場合は、ファイル一覧から選択をするためのファイル選択ダイアログが現われます。この時、 "message"にロード(またはセーブ)するファイルの拡張子(3文字まで)を指定して、 その拡張子だけが表示されるようにすることができます。("*"を指定するとすべてのファイルが表示されます)
また、"option"で拡張子の詳細、たとえば "txt"ならば、"テキストファイル"などの補助的な説明がダイアログの「ファイルの種類」に表示されます。
"option"は省略することも可能です。
^p
例 :
	dialog "txt",16,"テキストファイル"
	dialog "STAT="+stat+"\nNAME="+refstr,0,"結果"
	stop
^p
ファイル選択が完了すると、その結果がシステム変数statに代入されます。
変数statが1ならば、正常に選択されたことを意味します。変数statが0ならば、キャンセルされたかエラーが発生したことを意味しています。
「|」記号により区切ることで複数のファイル種別を指定することが可能です。
^p
例 :
	dialog "txt|log",16,"テキストファイル|ログファイル"
	dialog "STAT="+stat+"\nNAME="+refstr,0,"結果"
	stop
^p
タイプ32〜33の場合は、カラー選択をするダイアログが表示されます。色選択が終了すると、選択した色のRGBデータがシステム変数、 ginfo_r,ginfo_g,ginfo_bに代入されます。また、変数 statが0ならば、キャンセルされたかエラーが発生したことを意味しています。1ならば、正常に選択されたことを意味します。
^p
例 :
	dialog "",33
	dialog "R="+ginfo_r+"/G="+ginfo_g+"/B="+ginfo_b,0,"結果"
	stop
^p
タイプ64以降の値は、ランタイムごとに用意される拡張ダイアログのために予約されています。サポート外のタイプが指定された場合には、何も実行されません。
%port+
Let



%index
bgscr
枠のないウィンドウを初期化
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7,p8
p1=0〜(0)  : ウィンドウID
p2=0〜(640): 初期化する画面サイズX（1ドット単位）
p3=0〜(480): 初期化する画面サイズY（1ドット単位）
p4=0〜1(0) : 初期化する画面モード
p5=0〜(-1) : ウィンドウの配置X（1ドット単位）
p6=0〜(-1) : ウィンドウの配置Y（1ドット単位）
p7=0〜     : ウィンドウのサイズX（1ドット単位）
p8=0〜     : ウィンドウのサイズY（1ドット単位）

%inst
ウィンドウIDを初期化して枠のないウィンドウを作成します。
このウィンドウは、スクリーンセーバー作成などの特殊な用途で使用されます。
p2,p3パラメーターにより、初期化される画面サイズを指定します。
p4の初期化する画面モードは、以下から選ぶことができます。
^p
   1 : パレットモード(1670万色中256色)で作成する
   2 : 非表示のウィンドウを作成する
^p
p4パラメータに「+1」(パレットモードで作成する)を指定した場合は、パレットあり256色のモードで画面が作成されます。 このモードを指定しなかった場合は、フルカラー(24bitカラー)の画面が作成されます。
^
p4パラメータに「+2」(非表示のウィンドウを作成する)を指定した場合は、実行時にはウィンドウが表示されませんが、「gsel ID,1」 で表示させることが可能です。
^
p5,p6パラメーターにより、デスクトップ画面上に表示されるウィンドウの位置を指定することができます。
p5,p6を省略またはマイナス値にした場合は、システム規定の座標が使用されます。
p2,p3パラメーターで指定された画面サイズの一部だけをウィンドウに表示したい場合には、
p7,p8のパラメータで、ウィンドウのクライアントサイズ(実際に表示される大きさ)を指定することができます。
その場合は、groll命令によりウィンドウ内に表示される位置を設定することができるようになります。
通常は、p7,p8パラメーターの指定は省略して構いません。その場合は、p2,p3で指定された画面サイズと同じクライアントサイズで表示します。
^
bgscr命令で画面を初期化した後はそのウィンドウIDが画面制御命令の描画先になります。

%href
screen
buffer
groll
screen_hide
screen_normal
screen_palette
%port+
Let
%portinfo
HSPLet使用時は、パレットモードを使用できません。
%sample
	mes "プログラムを終了するにはこのウィンドウを閉じてください"

	// 枠のないウィンドウを作成
	bgscr 2, 320, 240
	boxf

%index
bmpsave
画面イメージセーブ
%group
画面制御命令
%prm
"filename"
"filename" : セーブするファイル名

%inst
現在の画面イメージをそのままBMP形式の画像ファイルとしてセーブします。
"filename"で指定された名前でファイルが作成されます。拡張子も含めてファイル名を指定する必要があります。
^
セーブされる画像サイズは、対象となるウィンドウが初期化されたサイズになります。サイズを変更する場合には、一旦別なサイズのウィンドウに内容をコピーしてから、bmpsaveをするようにしてください。




%index
boxf
矩形を塗りつぶす
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜(0)  : 矩形の左上X座標
p2=0〜(0)  : 矩形の左上Y座標
p3=0〜     : 矩形の右下X座標
p4=0〜     : 矩形の右下Y座標

%inst
画面上に、 (p1,p2)と(p3,p4) を左上、右下の点として、現在の描画色で矩形
(四角形)を塗りつぶします。
(p1,p2)を省略した場合は、画面の左上(0,0)が設定されます。
(p3,p4)を省略した場合は、画面の右下(描画サイズいっぱいまで)が設定されます。

%href
color
hsvcolor
palcolor
line
circle
gradf
%port+
Let
%sample
	// 全パラメータを省略すると全体塗りつぶし
	boxf

	color 255, 128, 0
	boxf 80, 80, 150, 130

%index
buffer
仮想画面を初期化
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜 (0) : ウィンドウID
p2=0〜(640): 初期化する画面サイズX（1ドット単位）
p3=0〜(480): 初期化する画面サイズY（1ドット単位）
p4=0〜1(0) : 初期化する画面モード

%inst
screen命令と同じく、指定したウィンドウIDを初期化して使用できるようにします。初期化する画面サイズと、画面モードはscreen命令と変わりませんが、buffer命令では、メモリ上に仮想画面が作られるだけで、実際の画面には表示されません。
これで作成した仮想画面は、通常の画面と同じようにprint命令やpicload命令を使用することができます。 gcopy命令などで別の画面にコピーするためのストック場所に使ったり、現在の画面を一時的に残しておくための保管場所に使うことができます。
^
なお、screenで初期化されたウィンドウIDをbuffer命令で再初期化することはできません。
^
buffer命令で画面を初期化した後はそのウィンドウIDが画面制御命令の描画先になります。

%href
screen
bgscr
screen_normal
screen_palette
%port+
Let
%portinfo
HSPLet使用時は、パレットモードを使用できません。



%index
chgdisp
画像解像度を変更する
%group
画面制御命令
%prm
p1,p2,p3
p1=0〜2(0)  : モードの設定
p2=0〜(640) : X方向の画像解像度の設定
p3=0〜(480) : Y方向の画像解像度の設定

%inst
現在の表示解像度を強制的に変更します。
(p2,p3)でX,Y解像度を設定し、p1で変更モードを設定します。
モードは、1がフルカラーモード(32bit)、 2がパレットモード(8bit)となります。変更モードが0の場合は、最初の状態(変更前)に復帰します。
^p
例 :
	chgdisp 1,640,480	; 640x480フルカラーに設定する
^p
(p2,p3)のパラメーターの指定を省略した場合は、(640,480)となります。
^
chgdisp命令が実行されると、 その結果がシステム変数statに反映されます。
システム変数statの内容は以下の通りになります。
^p
  stat=0 : 正常に解像度が設定された。
  stat=1 : カラーモードの変更はできなかったが、
           解像度の変更は正常に行なわれた。
  stat=2 : 解像度の変更ができなかった。
^p



%index
color
カラー設定
%group
画面制御命令
%prm
p1,p2,p3
p1,p2,p3=0〜255(0) : 色コード（R,G,Bの輝度）

%inst
メッセージ表示、描画などの色を指定した値に設定します。
p1,p2,p3がそれぞれ、R,G,Bの輝度になります。
^
0が最も暗く、255が最も明るくなります。
color 0,0,0 は黒に、color 255,255,255 は白になります。
パレットモードの画面では、指定した色に一番近いパレットが選択されます。

%href
palcolor
hsvcolor
%port+
Let




%index
font
フォント設定
%group
画面制御命令
%prm
"fontname",p1,p2
p1=1〜99(12) : フォントの大きさ
p2=0〜(0)    : フォントのスタイル

%inst
mesおよびprint命令などで表示するテキスト書体の設定をします。
"fontname"でフォントの名前を指定します。
^
フォント名は、"ＭＳ 明朝"、"ＭＳ ゴシック"などのフォント名を直接指定してください。
フォントの大きさはドット数に比例した論理サイズで指定します。
数が大きいほど、文字も大きくなります。フォントのスタイルは、
^p
  スタイル 1  : 太文字
  スタイル 2  : イタリック体
  スタイル 4  : 下線
  スタイル 8  : 打ち消し線
  スタイル16  : アンチエイリアス
^p
となります。数値を合計することで複数のスタイルを同時に指定することも可能です。p2を省略すると、0(通常のスタイル)になります。
^
スタイル16を指定すると、文字の縁にあるギザギザが消えて滑らかな表示になります。ただし、画面モードがフルカラーで初期化されている必要があるほか、Windows9X環境はサポートされないのでご注意下さい。(WindowsXPでは、常にアンチエイリアスが有効になります。)
^
初期設定やシステム指定のフォントに戻すには、 sysfont命令を使用してください。また、オブジェクトのフォントを変更する場合には、 objmode命令でモードの指定を行なう必要があります。
^
指定されたフォントが発見できなかった場合には、代用のフォントが自動的に検索されます。代用フォントの検索にも失敗した場合には、システム変数statに-1が代入されます。フォントが正常に設定された場合には、システム変数statに0が代入されます。

%href
sysfont
objmode
font_antialias
font_bold
font_italic
font_normal
font_strikeout
font_underline
%port+
Let




%index
gcopy
画面コピー
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜(0) : ウィンドウID
p2=0〜(0) : コピー元の左上X座標
p3=0〜(0) : コピー元の左上Y座標
p4=0〜    : コピーする大きさX（ドット単位）
p5=0〜    : コピーする大きさY（ドット単位）

%inst
gcopy命令は、 指定したウィンドウIDの画面の一部を、現在の描画先カレントポジションにコピーします。
コピー元のウィンドウIDは、自分のウィンドウIDと同じかまたは、screen命令やbuffer命令で初期化されたウィンドウIDでなければなりません。
^
gcopy命令でコピーする場合は、gmode命令によってコピーするモードをいくつか選ぶことができます。
^
gcopy命令でパレットモード画面の画像をコピーする際には注意が必要です。
コピーする２つのウィンドウのパレットが同じものでも問題のない画像を準備する必要があります。
また、パレットモード時のパレットは、ユーザー側で正しいものを設定するようにしてください。(画像ファイル使用時に、picload命令だけではパレット設定は行なわれません。)

%href
gmode
gzoom
%port+
Let




%index
gmode
画面コピーモード設定
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜6(0)   : 画面コピーモード
p2=0〜(32)   : コピーする大きさX（ドット単位）
p3=0〜(32)   : コピーする大きさY（ドット単位）
p4=0〜256(0) : 半透明合成時のブレンド率
%inst
gcopyで使用されるモードおよび、サイズ、ブレンド率などを設定します。
それぞれのコピーモード動作は以下の通りです。
^
・モード0 = 通常のコピー
^p
WindowsのシステムAPI(BitBlt関数)を使った画像コピーを行ないます。
最も標準的なモードです。
多くの場合、他のモードよりも高速に処理されます。
^p
・モード1 = メモリ間コピー
^p
画像バッファ間のメモリコピーを行ないます。
コピー元とコピー先は、同じ画像モード(パレットモード・フルカラーモード)でなければなりません。
動作は モード0と同じですが、非常に小さいサイズ(16*16ドット以下等)のコピーを行った際 モード0よりも 若干 高速になる場合があります。
^p
・モード2 = 透明色付きコピー
^p
モード1と同様の方法でコピーを行ないますが、 RGBがすべて0(完全な黒)のドットは透明色とみなされコピーされません。
^p
・モード3 = 半透明合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による半透明合成コピーを行ないます。ブレンド率は0〜256の値となり、256で完全なコピーになります。
ブレンド率が0の場合はコピーは実行されません。
また、ブレンド率が256以上はメモリ間コピーが実行されます。
^p
・モード4 = 透明色付き半透明合成コピー
^p
モード3と同様の方法でコピーを行ないますが、RGB値が color命令で設定された色と同じドットは透明色とみなされコピーされません。
ブレンド率が0の場合はコピーは実行されません。
^p
・モード5 = 色加算合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による色加算合成コピーを行ないます。色加算では、コピー先のRGB値に、コピー元のRGB値を加算します。
加算時に輝度が255を越える場合は、255にクランプされます。
^p
・モード6 = 色減算合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による色減算合成コピーを行ないます。色減算では、コピー先のRGB値から、コピー元のRGB値を減算します。減算時に輝度が0を下回る場合は、0にクランプされます。
^p
・モード7 = ピクセルアルファブレンドコピー
^p
フルカラーモード時のみ使用することができます。
gmodeで指定されたサイズの画像を、元画像の右側に用意しておき、 右側の画像をアルファブレンド成分として背景合成コピーを行ないます。
アルファブレンド成分が255の場合は、 そのまま元画像のピクセルがコピーされ、255より小さい場合には、そのブレンド率で背景と合成されます。
ピクセルはRGB単位で参照されるため、RGBに異なるブレンド率を設定可能です。
アルファブレンド画像は、通常 (0,0,0)〜(255,255,255) のグレースケールで表現するといいでしょう。
^p
これらのモードは、gzoom命令では使用されません。
あくまでもgcopy命令使用時なので注意してください。
また、gmodeは現在 gsel命令で選択されているウィンドウIDのモードが変更されます。gmodeの設定後に、別なウィンドウIDでgcopy命令を実行しても設定が反映されないので注意してください。
^
(p2,p3)はコピーサイズのデフォルトを設定します。この値は、gcopy,gzoom命令でコピーする大きさの値を省略した場合にデフォルトで使われるサイズです。

%href
gcopy
gmode_add
gmode_alpha
gmode_gdi
gmode_mem
gmode_pixela
gmode_rgb0
gmode_rgb0alpha
gmode_sub
%port+
Let
%portinfo
HSPLet時、モード7はサポートしていません。



%index
gsel
描画先指定、ウィンドウ最前面、非表示設定
%group
画面制御命令
%prm
p1,p2
p1=0〜(0)  : ウィンドウID
p2=0〜2(0) : ウィンドウアクティブスイッチ

%inst
画面制御命令の描画先を指定したウィンドウIDの画面に変更します。
これ以降は、p1で指定したウィンドウIDの画面に対して、mes命令やpicload命令などの画面描画に関する命令が実行されるようになります。
^
p2でオプションのスイッチが指定できます。p2の値が、
^p
  -1 : 指定したウィンドウを非表示にする
   0 : 指定したウィンドウに特に影響はない
   1 : 指定したウィンドウがアクティブになる
   2 : 指定したウィンドウがアクティブになり、さらに常に最前面になる
^p
のようにウィンドウの状態を変更することができます。
p2の指定を省略した場合は、特に何も影響はありません。
^
p2=-1で非表示にした場合は、 指定したウィンドウが消えますが完全に消去されるわけではありません。再びp2=1か2でアクティブにすると復帰します。
%port+
Let
%portinfo
HSPLet時、モード2はサポートされていません、またモード1で必ずアクティブになるとは限りません。




%index
gzoom
変倍して画面コピー
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7,p8
p1=0〜     : 画面にコピーする時の大きさX（ドット単位）
p2=0〜     : 画面にコピーする時の大きさY（ドット単位）
p3=0〜(0)  : ウィンドウID
p4=0〜(0)  : コピー元の左上X座標
p5=0〜(0)  : コピー元の左上Y座標
p6=0〜     : コピーする大きさX（ドット単位）
p7=0〜     : コピーする大きさY（ドット単位）
p8=0〜1(0) : ズームのモード

%inst
gzoom命令は、 指定したウィンドウIDの画面の一部を現在の描画先カレントポジションに、任意の大きさに変倍してコピーします。
コピー元のウィンドウIDは、自分のウィンドウIDと同じかまたは、screen命令やbuffer命令で初期化されたウィンドウIDでなければなりません。
^
p8でズームのモードを指定することができます。
p8に1を指定した場合には、 拡大縮小時にハーフトーンを使用した高品質な画像を生成します。(Windows9Xでは動作しません。)
^
p8が0か、または省略されている場合は、ハーフトーンを使用しませんが、 そのぶん高速に画像処理を行なうことができます。

%href
gcopy
%port+
Let




%index
palcolor
描画パレット設定
%group
画面制御命令
%prm
p1
p1=0〜255(0) : パレットコード

%inst
メッセージ表示、描画などの色を指定した値に設定します。
p1はパレットコードになります。パレットコードは、 パレットモード画面のために用意された256色(palette命令により設定された色)の中で何番目かを示すものです。
通常フルカラーモードを利用している限りでは使用する必要はありません。

%href
color
hsvcolor
palette




%index
palette
パレット設定
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜255(0)       : パレットコード
p2,p3,p4=0〜255(0) : 色コード（R,G,Bの輝度）
p5=0〜1(0)         : 更新スイッチ

%inst
現在の画面に設定されているパレットの色データを変更します。
p1のパレットコードにp2,p3,p4で指定した輝度のRGBカラーを設定します。
p1の値がマイナスの場合は、設定は無視されます。
p5の値によって、画面上の更新を指定することができます。
p5が0か省略されている時は、パレットに値を設定しますが、 すぐには画面上に反映されません。
p5が1の時は、設定したパレット全体が画面上にも反映されます。
画面上に反映されるまでには時間がかかるため、パレットをまとめて更新する場合には、一番最後に更新スイッチを1にするようにしてください。

%href
palcolor




%index
pget
1dotの点を取得
%group
画面制御命令
%prm
p1,p2
p1=0〜 : 画面上のX座標
p2=0〜 : 画面上のY座標

%inst
画面上の1ドットの色データを読みだします。
^
p1,p2で指定した座標にあるドットの色データが選択色として設定されます。(color命令で指定したのと同じ状態になります)
p1,p2の指定を省略した場合には、pos命令で設定されたカレントポジションの座標が使用されます。
取得した色の情報は、ginfo関数またはginfo_r,ginfo_g,ginfo_bマクロにより参照することができます。

%href
ginfo
ginfo_r
ginfo_g
ginfo_b
%port+
Let



%index
picload
画像ファイルをロード
%group
画面制御命令
%prm
"filename",p1
"filename" : ロードするファイル名
p1=0〜1(0) : 画像ロードモード

%inst
画像ファイルをロードします。通常は、
^p
picload "test.bmp"
^p
とするだけで、"test.bmp"で指定された画像ファイルが現在の画面にロードされ、ウィンドウサイズが自動的に絵のサイズに合わせられます。
^
p1の画像ロードモードは、
^p
  モード０：ウィンドウを初期化してロード
  モード１：現在の画面の上にロード
^p
p1のロードモードを省略もしくは０にすることで、画像のサイズで初期化したウィンドウにロードされます。
^
p1にロードモード１を指定することで、現在のウィンドウのサイズなどを一切変更せず指定した座標からロードすることができます。 この場合は、pos命令で指定した座標が左上となります。
^
現在ロードできる、ファイル形式は以下の通りです。
^p
BMP形式  : 拡張子 BMP : Windows標準の4,8,24bitのデータ。
                        RLE圧縮のデータも扱うことができます。
GIF形式  : 拡張子 GIF : GIF形式のデータ。
                        アニメーション形式は扱えません。
JPEG形式 : 拡張子 JPG : JFIF標準のJPEGデータ。
                        グレイスケールデータでもOKです。
ICO形式  : 拡張子 ICO : Windows標準のICO形式のアイコンデータ。
^p
picload命令は、screen、buffer、 bgscr命令で初期化された画面に対して実行することができます。

%href
screen
buffer
bgscr
imgload
%port+
Let
%portinfo
HSPLet時には、BMP、JPEG、GIF、PNGの読み込みをサポートしています。 ICOの読み込みはサポートしていません。

%index
pos
カレントポジション設定
%group
画面制御命令
%prm
p1,p2
p1=0〜     : カレントポジションのX座標
p2=0〜     : カレントポジションのY座標

%inst
メッセージ表示、オブジェクトの表示などの基本座標となるカレントポジションの座標を指定します。
^
Xは一番左が0に、Yは上が0になり、1ドット単位の指定になります。
パラメータの省略をすると、現在の値が使われます。

%href
mes
gcopy
line
%port+
Let



%index
pset
1dotの点を表示
%group
画面制御命令
%prm
p1,p2
p1=0〜 : 画面上のX座標
p2=0〜 : 画面上のY座標

%inst
画面上に、現在設定されている描画色で1ドットの点を描画します。
p1,p2の指定を省略した場合には、pos命令で設定されたカレントポジションの座標が使用されます。

%href
pget
color
palcolor
hsvcolor
%port+
Let





%index
redraw
再描画の設定
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜3(1) : 描画モードの設定
p2=0〜(0)  : 再描画する左上X座標
p3=0〜(0)  : 再描画する左上Y座標
p4=0〜(0)  : 再描画する大きさX（ドット単位）
p5=0〜(0)  : 再描画する大きさY（ドット単位）

%inst
画面の描画モードを指定します。描画モードとは、
^
描画モード0:
^p
mes,print,gcopy,gzoom などの画面制御命令が実行されても仮想画面を書き換えるだけで、実際の画面には反映されません。
^p
描画モード1:
^p
画面制御命令が実行されると、実際の画面にも反映されます。
^p
となっています。通常は描画モード１です。
描画モード0で画面内に画像をコピーしたり、メッセージを表示しておいて、最後にモード1にすることで画面の書き換えのちらつきをなくしスムーズに見せることができます。
^
モード1を指定した場合は即座に画面の更新を行います。
^
モード値に2を足した値を指定すると、描画モードのみを変更し画面の更新はされません。
^
また、p2〜p5までのパラメータにより、画面の一部だけを再描画させることが可能です。通常は省略すれば、全画面の更新を行ないます。
%port+
Let
%sample
// redraw命令のサンプル
// redraw命令を消すとちらつきが確認できます

*main_loop
	redraw 0

	color 255, 255, 255
	boxf

	pos 0, 0
	color 0, 0, 0
	mes "描画と消去を繰り返しても文字がちらつきません"

	redraw 1

	wait 1
	goto *main_loop


%index
screen
ウィンドウを初期化
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7,p8
p1=0〜(0)  : ウィンドウID
p2=0〜(640): 初期化する画面サイズX（1ドット単位）
p3=0〜(480): 初期化する画面サイズY（1ドット単位）
p4=0〜1(0) : 初期化する画面モード
p5=0〜(-1) : ウィンドウの配置X（1ドット単位）
p6=0〜(-1) : ウィンドウの配置Y（1ドット単位）
p7=0〜     : ウィンドウのサイズX（1ドット単位）
p8=0〜     : ウィンドウのサイズY（1ドット単位）
%inst
指定したウィンドウIDを初期化して使用できるようにします。 
HSPの初期状態では、ウィンドウID0の画面しか使用されていませんが、ウィンドウID1以上を指定することで、新しいウィンドウを作成することができます。
ID1以上のウィンドウは、標準でサイズを自由に変えることが可能なスタイルを持つことになります。
^
p4の初期化する画面モードは、以下から選ぶことができます。
^p
   0(screen_normal)    : フルカラーモードで作成する
  +1(screen_palette)   : パレットモード(1670万色中256色)で作成する
  +2(screen_hide)      : 非表示のウィンドウを作成する
  +4(screen_fixedsize) : サイズ固定ウィンドウ
  +8(screen_tool)      : ツールウィンドウ
 +16(screen_frame)     : 深い縁のあるウィンドウ
^p
p4パラメータに「+1」(パレットモードで作成する)を指定した場合は、パレットあり256色のモードで画面が作成されます。 0を指定した場合は、フルカラー(24bitカラー)の画面が作成されます。
^
p4パラメータに「+2」(非表示のウィンドウを作成する)を指定した場合は、実行時にはウィンドウが表示されませんが、「gsel ID,1」 で表示させることが可能です。
^
p4パラメータのうち「+4」「+8」「+16」 はそれぞれウィンドウのスタイルを設定するためのものです。
「サイズ固定ウィンドウ」は、ID1以降のウィンドウでも、ID0のウィンドウと同様のサイズ変更が不可能なスタイルで作成されます。
「ツールウィンドウ」は、タイトルバーのサイズが小さくなりタスクバーにウインドゥ名が表示されないウィンドウが作成されます。
^
p4パラメータが省略された場合は、 現在のWindows画面モードがパレットあり(256色) の場合はパレットモードで作成され、そうでない場合はフルカラーの画面として作成されます。
^
画面モードの値は、値を合計することで複数の設定を行なうことができます。
たとえば、
^p
	screen 2,320,240,4+8
^p
は、サイズ固定+ツールウィンドウのスタイルを持ったものが作成されます。
^
screen命令は、すでに初期化されているウィンドウIDをふたたび別の設定で再初期化することも可能です。
^p
例 ：
	screen 0,640,480,1
^p
上の例では、ウィンドウID0、つまりメインウィンドウを640x480ドット、パレットモードで再初期化します。
^
p5,p6パラメーターにより、デスクトップ画面上に表示されるウィンドウの位置を指定することができます。
p5,p6を省略またはマイナス値にした場合は、システム規定の座標が使用されます。
p2,p3パラメーターで指定された画面サイズの一部だけをウィンドウに表示したい場合には、
p7,p8のパラメータで、ウィンドウのクライアントサイズ(実際に表示される大きさ)を指定することができます。
その場合は、groll命令によりウィンドウ内に表示される位置を設定することができるようになります。
通常は、p7,p8パラメーターの指定は省略して構いません。その場合は、p2,p3で指定された画面サイズと同じクライアントサイズで表示します。
^
screen命令で画面を初期化した後はそのウィンドウIDが画面制御命令の描画先になります。

%href
bgscr
buffer
groll
screen_fixedsize
screen_frame
screen_hide
screen_normal
screen_palette
screen_tool
%port+
Let
%portinfo
HSPLet時、パレットモード・ツールウィンドウ・深い淵のあるウィンドウは使用できません。



%index
width
ウィンドウサイズ設定
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜(-1) : クライアントエリアのサイズX（1ドット単位）
p2=0〜(-1) : クライアントエリアのサイズY（1ドット単位）
p3=0〜(-1) : ディスプレイ上でのウィンドウX座標（1ドット単位）
p4=0〜(-1) : ディスプレイ上でのウィンドウY座標（1ドット単位）

%inst
ウィンドウのクライアントサイズ(実際に表示される大きさ)とウィンドウ表示位置を変更します。
クライアントサイズは、screen命令やbuffer,bgscr命令で初期化された画面サイズより大きくすることはできません。
^
p1,p2およびp3,p4パラメータが省略されるか、またはマイナス値の場合は、現在の設定が使われます。

%href
screen
buffer
bgscr
%port+
Let



%index
sysfont
システムフォント選択
%group
画面制御命令
%prm
p1
p1=0〜 : フォント種類指定

%inst
システム標準のフォントを選択します。
p1で、フォントの種類を指定します。これは以下の中から選びます。
^p
   p1 : font set
 --------------------------------------------------------------------
    0 : HSP標準システムフォント
   10 : OEM 文字セットの固定幅フォント
   11 : Windows 文字セットの固定幅システムフォント
   12 : Windows 文字セットの可変幅システムフォント
   13 : 標準システムフォント
   17 : デフォルトGUIフォント
        (標準の環境でメニューやダイアログボックスに使われています)
^p
p1が省略された場合は、標準システムフォントが選択されます。


%href
font
%port+
Let





%index
line
直線を描画
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜(0)  : ラインの終点X座標
p2=0〜(0)  : ラインの終点Y座標
p3=0〜     : ラインの始点X座標
p4=0〜     : ラインの始点Y座標

%inst
画面上に、(p1,p2)と(p3,p4)を結ぶ直線を描画します。
(p3,p4)を省略した場合は、カレントポジションから(p1,p2)まで、現在設定されている色で直線が描画されます。
^
line命令実行後は、(p1,p2)の座標がカレントポジションになります。
これにより、連続した直線を描画していくことが可能です。

%href
pos
color
palcolor
boxf
circle
%port+
Let



%index
circle
円を描画する
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜(0)  : 矩形の左上X座標
p2=0〜(0)  : 矩形の左上Y座標
p3=0〜     : 矩形の右下X座標
p4=0〜     : 矩形の右下Y座標
p5=0〜1(1) : 描画モード(0=線,1=塗りつぶし)

%inst
画面上に、(p1,p2)と(p3,p4)を左上、右下の点として、矩形(四角形)に収まる大きさの円を描画します。
描画色は、color命令等で設定されたものになります。
^
p5に0が指定されている場合は、輪郭だけを線で描画します。
p5が1または省略されている場合は、円の内部も塗りつぶします。

%href
boxf
line
color
palcolor
hsvcolor
%port+
Let



%index
syscolor
システムカラーを設定する
%group
画面制御命令
%prm
p1
p1 : 設定するシステムカラーインデックス

%inst
p1で指定したシステムカラーインデックスを選択色として設定します。
(color命令で指定したのと同じ状態になります)
p1で指定できるシステムカラーインデックスは、以下の値となります。
^p
 0 : スクロールバーの軸の色
 1 : デスクトップの色
 2 : アクティブウィンドウのタイトルバーの色 (グラデーションの場合はアクティブウィンドウのタイトルバーの左側の色)
 3 : 非アクティブウィンドウのタイトルバーのテキストの色 (グラデーションの場合は非アクティブウィンドウのタイトルバーの左側の色)
 4 : メニューの背景色
 5 : ウィンドウの背景色
 6 : ウィンドウの枠の色
 7 : メニュー内のテキストの色
 8 : ウィンドウ内のテキストの色
 9 : アクティブウィンドウのタイトルバーのテキストの色
10 : アクティブウィンドウの境界の色
11 : 非アクティブウィンドウの境界色
12 : MDIアプリケーションの背景色
13 : コントロール内における選択された項目の色
14 : コントロール内における選択された項目のテキストの色
15 : 3D オブジェクトの表面色
16 : 3D オブジェクトの影の色 (光源の反対方向の縁用)
17 : 淡色状態 (無効状態) のテキストの色
18 : プッシュボタンのテキストの色
19 : 非アクティブウィンドウのタイトルバーのテキストの色
20 : 3D オブジェクトの最も明るい色 (光源方向の縁用)
21 : 3D オブジェクトの暗い影の色
22 : 3D オブジェクトの明るい色 (光源方向の縁用)
23 : ツールチップコントロールのテキストの色
24 : ツールチップコントロールの背景色
26 : ホットトラックアイテムの色
27 : グラデーションの場合はアクティブウィンドウのタイトルバーの右側の色
28 : グラデーションの場合は非アクティブウィンドウのタイトルバーの右側の色
29 : (Windows XP以上) メニューがフラットメニューとして表示されるときにメニューアイテムをハイライト表示するのに使用される色
30 : (Windows XP以上) メニューがフラットメニューとして表示されるときのメニューバーの背景色
^p

%href
color
palcolor
hsvcolor
%port+
Let



%index
hsvcolor
HSV形式でカラーを設定する
%group
画面制御命令
%prm
p1,p2,p3
p1=0〜191(0) : HSV形式 H値
p2=0〜255(0) : HSV形式 S値
p3=0〜255(0) : HSV形式 V値

%inst
色の指定をHSV形式で行ないます。
color命令と同様に、以降の描画命令で設定された色が使用されます。

%href
color
palcolor
%port+
Let



%index
ginfo
ウィンドウ情報の取得
%group
基本入出力関数
%prm
(p1)
p1=0〜 : 取得するタイプ

%inst
p1で指定したタイプのウィンドウ関連情報値を返します。
取得できるタイプは以下の通りです。
^p
  0 : スクリーン上のマウスカーソルX座標
  1 : スクリーン上のマウスカーソルY座標
      スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。

  2 : アクティブなウィンドウID

      現在アクティブになっているウィンドウIDを返します。
      もし、 アクティブになっているウィンドウがHSP以外の場合は-1になります。

  3 : 操作先ウィンドウID

      gsel命令で指定した画面の操作先ウィンドウIDが代入されます。

  4 : ウィンドウの左上X座標
  5 : ウィンドウの左上Y座標

    スクリーン座標系で現在のウィンドウの左上座標を返します。
    スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。

  6 : ウィンドウの右下X座標
  7 : ウィンドウの右下Y座標

      スクリーン座標系で現在のウィンドウの右下座標を返します。
      スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、デスクトップ画面全体から見た座標になります。

  8 : ウィンドウの描画基点X座標
  9 : ウィンドウの描画基点Y座標

      現在の操作先ウィンドウの描画基点座標を返します。
      これは、描画内容をスクロール可能な(初期化サイズよりも表示サイズが小さい)ウィンドウにおいて、どれだけスクロールされているかを示す値です。
      スクロールさせていない通常の状態では、(0,0)になります。
      描画基点を設定する場合は、groll命令を使用します。

 10 : ウィンドウ全体のXサイズ
 11 : ウィンドウ全体のYサイズ

      現在の操作先ウィンドウの横幅、縦幅が返されます。
      これは、ウィンドウの枠やタイトルバーなども含めたサイズになります。

 12 : クライアント領域Xサイズ
 13 : クライアント領域Yサイズ

      現在の操作先ウィンドウのクライアント領域サイズが返されます。
      クライアント領域はウィンドウ内に表示されている描画可能な部分を指します。

 14 : メッセージの出力Xサイズ
 15 : メッセージの出力Yサイズ

      最後にmes, print命令により出力されたメッセージのサイズが返されます。
      サイズは、 X,Y座標にどれだけのドット数で描画されたかを示します。
      画面上の絶対座標ではないので注意してください。
      また、複数行ある文字列を出力した場合は、最後の行にあたるサイズが取得されます。

 16 : 現在設定されているカラーコード(R)
 17 : 現在設定されているカラーコード(G)
 18 : 現在設定されているカラーコード(B)

      color命令などにより指定された色コードが返されます。

 19 : デスクトップのカラーモード

      現在のデスクトップカラーモード(色モード)が返されます。
      フルカラーモードの場合は0が、パレットモードの場合は1が返されます。

 20 : デスクトップ全体のXサイズ
 21 : デスクトップ全体のYサイズ

      デスクトップ全体のサイズ(画面解像度)が返されます。

 22 : カレントポジションのX座標
 23 : カレントポジションのY座標

      pos命令により設定されたカレントポジションのX,Y座標が返されます。

 24 : メッセージ割り込み時のウィンドウID

      oncmd命令により設定されたメッセージ割り込み時のウィンドウIDが返されます。

 25 : 未使用ウィンドウID

      screen命令やbuffer命令などで初期化されていない未使用のウィンドウIDが返されます。

 26 : 画面の初期化Xサイズ
 27 : 画面の初期化Yサイズ

      現在の操作先ウィンドウの初期化サイズが返されます。
      最初にscreen,bgscr,buffer命令で初期化された画面サイズになります。

^p

%href
objinfo
%port+
Let
%portinfo
HSPLet時、タイプ 19、画面のカラーモードは常に 0 を返します。
HSPLet時、タイプ 24、oncmd の割り込みウィンドウ ID はサポートされていません。
HSPLet時、タイプ 25はサポートされていません。


%index
grect
回転する矩形で塗りつぶす
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6
p1=0〜(0)   : 矩形の中心X座標
p2=0〜(0)   : 矩形の中心Y座標
p3=0〜(0.0) : 回転角度(単位はラジアン)
p4=0〜(?)   : Xサイズ
p5=0〜(?)   : Yサイズ

%inst
(p1,p2)で指定した座標を中心として、 (p4,p5)で指定したサイズの矩形(長方形)を現在設定されている色で描画します。
p3で回転角度を実数で指定することができます。
角度の単位は、ラジアン(0から始まって、2πで一周)となります。
grect命令は、gmodeで設定されたコピーモードの指定が反映されます。
^
gmodeが 0,1の場合は、通常の塗りつぶし。
gmodeが 3の場合は、指定されたレートで半透明になります。
gmodeが 5, 6の場合は、それぞれ色加算、色減算処理となります。
また、(p4,p5)のサイズ指定を省略した場合には、gmode命令で設定されているコピーサイズが使用されます。
^
 パレットモード時には 指定した描画色で塗りつぶしが行なわれますが、半透明処理は行われません。

%href
color
hsvcolor
palcolor
grotate
gsquare
gmode
%port+
Let


%index
grotate
矩形画像を回転してコピー
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6
p1=0〜(0)   : コピー元のウィンドウID
p2=0〜(0)   : コピー元の左上X座標
p3=0〜(0)   : コピー元の左上Y座標
p4=0〜(0.0) : 回転角度(単位はラジアン)
p5=0〜(?)   : Xサイズ
p6=0〜(?)   : Yサイズ

%inst
grotate命令は、gcopy命令に回転を含めた処理を行ないます。
p1で、コピー元のウィンドウIDを指定、(p2,p3) でコピーされる元の画像にあたる座標を指定します。(gcopy命令と同様です)
コピー先は、現在の描画先に指定されているウィンドウIDで、 pos命令で設定された場所を中心とした座標にコピーを行ないます。その際に、p4で回転角度を実数で指定することができます。
角度の単位は、ラジアン(0から始まって、2πで一周)となります。
(p5,p6)で、コピーされた後のX,Yサイズを指定します。
また、コピー元のX,Yサイズはgmode命令で設定されたデフォルトのコピーサイズが使用されます。
つまり、gmode命令で指定されたサイズよりも大きなサイズを(p5,p6)で指定した場合には、拡大されることになります。
(p5,p6) を省略した場合には、コピー元と同じサイズ、つまり等倍でコピーが行なわれます。
^
grotate命令は、gmodeで設定されたコピーモードの指定が反映されます。(モード7のピクセルアルファブレンドコピーは適用されません。)
透明色の設定や、半透明の設定はすべて gcopy命令でコピーした場合と同等に機能します。(詳しくはgmode命令のリファレンスを参照)
^
パレットモード時には半透明処理は実行されません。
また、異なる画面モード(パレットモードとフルカラーモード)間でのコピーはエラーになります。

%href
grect
gsquare
gmode
%port+
Let


%index
gsquare
任意の四角形を描画
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜(0) : コピー元のウィンドウID (マイナス値ならば塗りつぶし)
p2=変数名 : コピー先X座標が格納される数値型配列変数名
p3=変数名 : コピー先Y座標が格納される数値型配列変数名
p4=変数名 : コピー元X座標が格納される数値型配列変数名
p5=変数名 : コピー元Y座標が格納される数値型配列変数名

%inst
任意の４点を持つ四角形をコピーまたは塗りつぶします。
p1で、画像コピー元のウィンドウIDを指定します。
^
p2,p3にはコピー先の座標４つを配列に格納した変数を指定します。
p4,p5にはコピー元の座標４つを配列に格納した変数を指定します。
配列変数には、左上(0),右上(1),右下(2),左下(3) の順番に座標を入れておく必要があります。
^
gsquare命令は、gmodeで設定されたコピーモードの指定が反映されます。(モード7のピクセルアルファブレンドコピーは適用されません。)
透明色の設定や、半透明の設定はすべて gcopy命令でコピーした場合と同等に機能します。(詳しくはgmode命令のリファレンスを参照)
^
パレットモード時には半透明処理は実行されません。
また、異なる画面モード(パレットモードとフルカラーモード)間でのコピーはエラーになります。
^
p1に-1などマイナス値を指定した場合は、画像コピーではなく塗りつぶしが行なわれます。
塗りつぶしは、単色による塗りつぶしと、グラデーションによる塗りつぶしを選択することができます。
p1に、-1から-256の値を指定した場合は、単色による塗りつぶしとなります。
単色塗りつぶしを行なう場合には、p4,p5パラメーターを指定する必要はありません。
その際、フルカラーモード時には 描画色による塗りつぶしとなります。
パレットモード時は、p1で指定した値-1をパレットコードとして塗りつぶしを行ないます。(-1〜-256がパレットコード0〜255に対応します)
^
p1に、-257またはgsquare_grad(-257のマクロ定義)を指定した場合は、グラデーションによる塗りつぶしが実行されます。
グラデーション塗りつぶしを行なう場合には、p4パラメーターに頂点の色を示すRGBコードを格納した配列変数を指定してください。
(RGBコードは、gradf命令で指定される色コードと同一のものになります。)
グラデーション塗りつぶしでは、gmodeで設定されたコピーモードの指定は反映されず、常に不透明の描画になるので注意してください。


%href
grect
grotate
gmode
color
hsvcolor
palcolor
gradf
%port+
Let



%index
objinfo
ウィンドウオブジェクト情報の取得
%group
基本入出力関数
%prm
(p1,p2)
p1=0〜 : ウィンドウオブジェクトID
p2=0〜 : 取得するタイプ

%inst
現在アクティブなウィンドウに配置されている、特定のウィンドウオブジェクトに関連する情報値を返します。
p1にウィンドウオブジェクトID、p2に取得タイプを指定することで、該当する情報データが返されます。
取得できるタイプは以下の通りです。
^p
     0  : モード(下位16bit)及びオプションデータ(上位16bit)
     1  : objectが配置されているBMSCR構造体のポインタ
     2  : ウィンドウオブジェクトのハンドル(HWND)
     3  : owid (内部汎用データ)
     4  : owsize (内部汎用データ)
  5〜8  : 代入変数の情報
  9〜11 : ウィンドウオブジェクトコールバックの情報
^p
ウィンドウオブジェクト情報は、通常の使用では利用する必要はありません。
外部API(DLL)等にウィンドウオブジェクトのハンドル(HWND)を渡す場合など、特殊な用途に利用することができます。

%href
ginfo
objinfo_bmscr
objinfo_hwnd
objinfo_mode
%port+
Let
%portinfo
HSPLet時、ウィンドウハンドル（type==2）のみが利用可能です。


%index
axobj
ActiveXコントロールの配置
%group
画面制御命令
%prm
p1,"IID",p2,p3
p1    : COMオブジェクトが代入される変数名
"IID" : COMオブジェクトのクラスIDまたはプログラムID
p2=0〜: オブジェクトのXサイズ
p3=0〜: オブジェクトのYサイズ


%inst
"IID"で指定されたクラスIDまたは、プログラムID(ProgID)を持つActiveXコントロール(OLEコントロール)をウィンドウオブジェクトとして配置します。
p2,p3で配置されるオブジェクトのX,Yサイズを指定します。 
サイズの指定が省略されるか0以下の場合は、ウインドゥ全体のサイズが使用されます。
配置に成功した場合は、システム変数statにオブジェクトIDが代入され、p1の変数をコントロールのためのCOMオブジェクト型変数として初期化します。
ActiveXコントロールの配置に失敗した場合は、システム変数statに-1が代入されて終了します。
^p
例 :
	axobj ie, "Shell.Explorer.2",640,480
	ie->"Navigate" "www.onionsoft.net"
^p

%href
newcom
delcom
querycom
%portinfo
ActiveXコントロールの配置には、「atl.dll」を使用します。
「atl.dll」がインストールされていない環境では、「サポートされない機能を選択しました」エラーが表示されます。



%index
winobj
ウィンドウオブジェクトの配置
%group
画面制御命令
%prm
"Class","Title",p1,p2,p3,p4,p5,p6
"Class" : ウィンドウクラス名
"Title" : ウィンドウ名
p1(0)   : 拡張ウィンドウスタイル
p2(0)   : ウィンドウスタイル
p3(0)   : Xサイズ
p4(0)   : Yサイズ
p5(0)   : メニューハンドルまたは子ウィンドウID
p6(0)   : ウィンドウ作成データ

%inst
winobjは、 Windowsのシステムがサポートするウィンドウをオブジェクトとして配置します。
p3,p4で配置するX,Yサイズを指定します。 サイズの指定が省略されるか0以下の場合は、objsizeで設定されている値が使用されます。
^
指定したウィンドウオブジェクトが生成されるとシステム変数statにオブジェクトIDが代入されます。
このオブジェクトIDは、clrobj命令を始めとするオブジェクト操作命令で使用することができます。
(生成されたウィンドウは、 現在アクティブなウィンドウが管理するオブジェクトとして登録されます。)
内部エラーなどでウィンドウオブジェクトが正常に生成されなかった場合には、システム変数statに-1が代入されます。
^
winobjによって配置したオブジェクトに対してobjprm命令を使用することはできません。
^
この命令は、HSPの命令がサポートしていないウィンドウオブジェクトをWindows APIを通して配置するためのもので、WIN32API のCreateWindowExと同様のパラメーターを受け取ります。 外部DLLとのやり取りや、モジュール作成に使用するもので通常覚えておく必要はありません。



%href
pos
objsize
clrobj



%index
sendmsg
ウィンドウメッセージの送信
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1(0) : ウィンドウハンドル
p2(0) : メッセージID
p3(0) : wParam値
p4(0) : lParam値

%inst
p1で指定したウィンドウハンドルに対して、 p2のメッセージとp3,p4のパラメーターを送信します。
^
p1で指定するウィンドウハンドルの値は、 HSPのウィンドウであればシステム変数hwndを、HSPのウィンドウオブジェクトの場合はobjinfo関数により取得することができます。
^
p3をwParam、p4をlParamの情報としてウィンドウメッセージが送信されます。
p3パラメーターは、整数値を指定することが可能です。
p4パラメーターには、整数値、文字列のいずれかを指定することができます。
整数値の場合は、値そのものをlParamとして扱います。
文字列の場合は、文字列ポインタ値をlParamとして扱います。
^
この命令は、 HSPの命令がサポートしていないウィンドウオブジェクトに対してWindowsのメッセージを送信するためのものです。
外部DLLとのやり取りや、 モジュール作成に使用するもので通常覚えておく必要はありません。

%href
hwnd
objinfo
winobj
%port+
Let
%portinfo
HSPLet時、以下のメッセージのみ実装済みです。 
0x00B0:EM_GETSEL 
0x00B1:EM_SETSEL 
0x00C6:EM_CANUNDO 
0x00C7:EM_UNDO 
0x00CC:EM_SETPASSWORDCHAR 
0x0300:WM_CUT 
0x0301:WM_COPY 
0x0302:WM_PASTE 
0x0303:WM_CLEAR 

%index
groll
ウィンドウの描画基点を設定
%group
画面制御命令
%prm
p1,p2
p1=0〜(0)  : ウィンドウに描画する基点となるX座標
p2=0〜(0)  : ウィンドウに描画する基点となるY座標

%inst
ウィンドウに描画する基点座標を設定します。
基点座標は、描画内容をスクロール可能な(初期化サイズよりも表示サイズが小さい)ウィンドウにおいて、X,Y方向にどれだけスクロールされているかを示すものです。
(0,0)を設定すると、スクロールさせていない通常の状態になります。
現在設定されている基点座標は、ginfo関数によって取得することができます。

%href
ginfo
%port+
Let



%index
gradf
矩形をグラデーションで塗りつぶす
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7
p1=0〜(0)  : 矩形の左上X座標
p2=0〜(0)  : 矩形の左上Y座標
p3=0〜     : 矩形の右下X座標
p4=0〜     : 矩形の右下Y座標
p5=0〜(0)  : グラデーションのモード
p6=0〜     : 塗りつぶし色1(RGBカラーコード)
p7=0〜     : 塗りつぶし色2(RGBカラーコード)

%inst
(p1,p2)と(p3,p4) を左上、右下の点として、グラデーションで矩形(四角形)を塗りつぶします。
塗りつぶす色は、p6,p7で指定されたRGBカラーコードとなります。
RGBカラーコードは、color命令で指定するR,G,Bそれぞれの輝度をまとめて24ビット数値で表現したものです。
スクリプトで記述する場合は、最初に「$」を付けた16進表現を行なうと便利です。
「$112233」のように記述した場合は、R輝度が$11、G輝度が$22、B輝度が$33という値になります。この場合、輝度は$00〜$ffまでとなります。(10進数の0〜255にあたります)
p5でグラデーションのモードを指定することができます。
^p
   p5 : グラデーションのモード
 --------------------------------------------------------------------
    0 : 横方向のグラデーション
    1 : 縦方向のグラデーション
^p
グラデーションの塗りつぶしは、左上をp6、右下をp7で指定された色として行なわれます。
p6及びp7の指定を省略した場合は、現在の描画色を使用します。
(p1,p2)を省略した場合は、画面の左上(0,0)が設定されます。
(p3,p4)を省略した場合は、画面の右下(描画サイズいっぱいまで)が設定されます。
^p
例 :
	; グラデーションで矩形を塗りつぶし
	gradf 120,180,400,100, 1, $ff00ff, $ffffff
^p
単色で矩形を塗りつぶす場合は、boxf命令を使用してください。
また、四角形の頂点それぞれの色を指定したグラデーション描画を行なう場合は、gsquare命令を使用してください。

%href
boxf
gsquare



%index
celload
画像ファイルをバッファにロード
%group
画面制御命令
%prm
"filename",p1,p2
"filename" : ロードするファイル名
p1=1〜(-1) : 読み込み先ウインドゥID
p2=0〜1(0) : 初期化する画面モード

%inst
画像ファイルを指定した仮想画面に読み込みます。
celload命令は、主にcelput命令やgcopy命令でコピーを行なうための画像素材を
仮想画面(非表示のウィンドウ)に読み込むためのものです。
buffer命令によって仮想画面を初期化して、picload命令で画像ファイルを読み込む
という動作と、基本的に同一です。
^
"filename"パラメーターで、読み込む画像ファイル名を指定します。
使用できる画像ファイルの形式は、picload命令と同じです。
p1で、読み込み先のウインドゥIDを指定することができます。
p1が省略されるか、マイナス値の場合は未使用のウインドゥIDが自動的に使用されます。
(命令実行後、システム変数statに読み込まれたウィンドウIDが代入されます。)
p2で、仮想画面の初期化モードを指定することができます。
p2が省略されるか、0の場合はフルカラーモード。1の場合は、パレットモードが選択されます。
^
celload命令により、画像素材を効率的に読み込み管理することができます。
詳しくは、プログラミングマニュアル(hspprog.htm)のCEL関連命令についてを参照してください。

%href
picload
buffer
celdiv
celput


%index
celdiv
画像素材の分割サイズを設定
%group
画面制御命令
%prm
p1,p2,p3,p4,p5
p1=0〜(1)  : ウインドゥID
p2=1〜(0)  : 横方向の分割サイズ
p3=1〜(0)  : 縦方向の分割サイズ
p4=0〜(0)  : 横方向の中心座標
p5=0〜(0)  : 縦方向の中心座標

%inst
指定したウィンドウIDが持つ画像素材の分割サイズを設定します。
分割された画像素材は、celput命令により画像を描画する際に参照されます。
たとえば、256×256ドットの画像を128×64ドットで分割する設定にした場合、
celput命令により128×64ドットの画像8枚分として扱うことができるようになります。
^
p1で、画像素材を持つウインドゥIDを指定します。
(p2,p3)で、横(X)・縦(Y)方向の分割サイズ(分割された領域１つあたりのドット数)を指定します。
分割サイズを省略、または0以下の値にした場合は、素材のサイズがそのまま使用されます。
^
(p4,p5)で、描画の中心座標を設定することができます。
これは、celput命令で描画を行なった際に、描画の基点位置になります。
たとえば、(0,0)を中心座標として指定した場合は、celput命令で描画される位置(pos命令で指定した座標)に、画像素材の(0,0)が参照されることになります。
また、回転した画像の描画を行なう際にも、回転の中心となります。
通常は、(0,0)の位置、つまり左上が基点位置となっています。これは、gcopy命令での基点位置と同様です。

^
画像素材の分割設定は、ウィンドウIDごとに保存されており、cls命令などで初期化された
時点では、分割なし(画面全体をサイズとして指定)の設定になっています。
分割の設定は、必ず指定されたウィンドウIDに画像素材が読み込まれた状態で行なってください。
分割の設定を行なった後に、画像素材の読み込みを行なった場合は、分割設定はリセットされます。
詳しくは、プログラミングマニュアル(hspprog.htm)のCEL関連命令についてを参照してください。

%href
celload
celput


%index
celput
画像素材を描画
%group
画面制御命令
%prm
id,no,zoomx,zoomy,angle
id=0〜(1) : 画像素材を持つウインドゥID
no=0〜(0) : 分割画像No.
zoomx=0.0〜(1.0) : 横方向の表示倍率(実数)
zoomy=0.0〜(1.0) : 縦方向の表示倍率(実数)
angle=0.0〜(0.0) : 回転角度(単位はラジアン)

%inst
仮想画面に読み込まれた画像素材を、現在の操作先ウィンドウに描画します。
idで、画像素材を持つウインドゥIDを指定します。
noで、分割画像No.を指定します。分割画像No.は、画像素材を持つウインドゥIDの中で
分割された画像を特定する番号となります。
zoomx,zoomyにより、描画される画像の横(X)・縦(Y)方向倍率を指定できます。
zoomx,zoomyの指定は、実数で指定することが可能です。
また、angleにより画像の回転角度を指定することも可能です。
angleに指定される値は、実数で単位はラジアン(0から始まって、2πで一周)となります。(grotate、grect命令と同様の値になります)
^
celput命令は、gcopy命令と同様に指定されたウインドゥIDの画像をコピーして描画します。
gcopy命令と同様に、gmode命令により指定されたコピーモード、ブレンド率が反映されます。
描画位置は、現在のカレントポジション(pos命令で指定された値)が基点となります。
描画される画像のサイズは、通常は(指定されたウィンドウIDにある)元画像と同じものになります。
描画される画像のサイズ及び、描画や回転の中心位置は、celdiv命令によって変更することが可能です。
^
zoomx,zoomy,angleの指定を省略するか、等倍の設定(1,1,0)になっている場合は、
自動的に高速なコピーが内部で実行されます。逆に、等倍でない描画を行なう場合は、
grotate命令と同様の描画処理が実行されます。
描画終了後は、描画したサイズに応じてカレントポジションを右に移動します。
(ただし、角度は考慮されません。あくまでも描画の横サイズ分を右に移動させます)
^
celput命令とその関連命令により、画像素材を効率的に管理することができます。
詳しくは、プログラミングマニュアル(hspprog.htm)のCEL関連命令についてを参照してください。

%href
celload
celdiv
gcopy
grotate




