;
;	HSP help manager用 HELPソースファイル
;	(先頭が;の行はコメントとして処理されます)
;

%type
内蔵命令
%ver
3.1
%note
ver3.1標準命令
%date
2004/10/12
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
cls命令で画面をクリアすると、 画面にあるボタンや入力ボックスなどのオブ
ジェクト類、フォントやカラー設定が初期状態に戻ります。
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
メッセージは、カレントポジションと呼ばれるウィンドウ上の仮想的なカーソ
ル位置から表示され、カレントポジションが次の行に自動的に移動します。
^
表示されるメッセージのフォントは、font命令で指定することができます。
表示するメッセージに改行コードが含まれていた場合には、改行され次の行か
ら表示を続けます。
%href
print
font
%port+
Let


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
メッセージは、カレントポジションと呼ばれるウィンドウ上の仮想的なカーソ
ル位置から表示され、カレントポジションが次の行に自動的に移動します。
^
表示されるメッセージのフォントは、font命令で指定することができます。
表示するメッセージに改行コードが含まれていた場合には、改行され次の行か
ら表示を続けます。
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
p1の指定が省略されている場合には、ウィンドウのタイトルバーキャプション
を、"strings"の内容に設定します。
(タイトルバーキャプションは、「Hot Soup Processor ver3.x」と通常は表示
されている部分のことです)
^p
例 ：
	title "Window Title"
^p
上の例では、「Window Title」という文字をウィンドウのタイトルバーに表示
します。

%href
objprm
%port+
Let
%portinfo
HSPLetアプレットの場合はステータスバーのテキストが変化します。



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
dialog命令で出したダイアログは、 HSPのウィンドウとは別にポップアップし
て現われます。
^
ユーザーの操作によりダイアログを閉じるまでは、 HSPスクリプトの続きは実
行されません。
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
タイプ0〜3の場合は、"message" で指定した内容を表示するメッセージボック
スが現われます。また、"option"でメッセージボックスのタイトルバー文字列
を指定することができます。(省略した場合はタイトルに何も表示されません)
メッセージボックスが閉じられると、押したボタンの情報がシステム変数stat
に代入されます。この時、変数statの内容は、
^p
  1 :「OK」ボタンが押された
  6 :「はい」ボタンが押された
  7 :「いいえ」ボタンが押された
^p
のようになります。
^
タイプ16〜17の場合は、ファイル一覧から選択をするためのファイル選択ダイ
アログが現われます。この時、 "message"にロード(またはセーブ)するファイ
ルの拡張子(3文字まで)を指定して、 その拡張子だけが表示されるようにする
ことができます。("*"を指定するとすべてのファイルが表示されます)
また、"option"で拡張子の詳細、たとえば "txt"ならば、"テキストファイル"
などの補助的な説明がダイアログの「ファイルの種類」に表示されます。
"option"は省略することも可能です。
ファイル選択が完了すると、その結果がシステム変数statに代入されます。
変数statが1ならば、正常に選択されたことを意味します。変数statが0ならば
、キャンセルされたかエラーが発生したことを意味しています。
^
ファイル選択が正常に完了していれば、文字列型のシステム変数refstrに選択
されたファイル名がパス名も含めて代入されます。
^p
例 :
	dialog "as",16,"ｿｰｽｽｸﾘﾌﾟﾄ"
	dialog "STAT="+stat+"\nNAME="+refstr,0,"結果"
	stop
^p
タイプ32〜33の場合は、カラー選択をするダイアログが表示されます。色選択
が終了すると、選択した色のRGBデータがシステム変数、 ginfo_r,ginfo_g,ginfo_bに
代入されます。また、変数 statが0ならば、キャンセルされたかエラーが発生し
たことを意味しています。1ならば、正常に選択されたことを意味します。
^p
例 :
	dialog "",33
	dialog "R="+ginfo_r+"/G="+ginfo_g+"/B="+ginfo_b,0,"結果"
	stop
^p
タイプ64以降の値は、ランタイムごとに用意される拡張ダイアログのために
予約されています。サポート外のタイプが指定された場合には、何も実行されません。
%port+
Let



%index
bgscr
ウィンドウIDを初期化
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7,p8
p1=0〜(0)  : ウィンドウID
p2,p3      : 初期化する画面サイズX,Y（1ドット単位）
p4=0〜1(0) : 初期化する画面モード
p5,p6(0,0) : ウィンドウの配置X,Y（1ドット単位）
p7,p8      : ウィンドウのサイズX,Y（1ドット単位）

%inst
ウィンドウIDを初期化して枠のないウィンドウを作成します。
このウィンドウは、スクリーンセーバー作成などの特殊な用途で使用されます。
p4の初期化する画面モードは、以下から選ぶことができます。
^p
   1 : パレットモード(1670万色中256色)で作成する
   2 : 非表示のウィンドウを作成する
^p
p4パラメータに「+1」(パレットモードで作成する)を指定した場合は、パレッ
トあり256色のモードで画面が作成されます。 このモードを指定しなかった場
合は、フルカラー(24bitカラー)の画面が作成されます。
^
p4パラメータに「+2」(非表示のウィンドウを作成する)を指定した場合は、
実行時にはウィンドウが表示されませんが、「gsel ID,1」 で表示させること
が可能です。


%href
screen
buffer
%port+
Let
%portinfo
HSPLet使用時は、パレットモードを使用できません。




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
"filename"で指定された名前でファイルが作成されます。拡張子も含めてファ
イル名を指定する必要があります。
^
セーブされる画像サイズは、対象となるウィンドウが初期化されたサイズにな
ります。サイズを変更する場合には、一旦別なサイズのウィンドウに内容をコ
ピーしてから、bmpsaveをするようにしてください。




%index
boxf
矩形を塗りつぶす
%group
画面制御命令
%prm
p1,p2,p3,p4
p1,p2 : 矩形の左上X,Y座標
p3,p4 : 矩形の右下X,Y座標

%inst
画面上に、 (p1,p2)と(p3,p4) を左上、右下の点として、現在の描画色で矩形
(四角形)を塗りつぶします。


%href
color
hsvcolor
palcolor
line
circle
%port+
Let



%index
buffer
ウィンドウIDを初期化
%group
画面制御命令
%prm
p1,p2,p3,p4
p1=0〜 (0) : ウィンドウID
p2,p3      : 初期化する画面サイズX,Y（1ドット単位）
p4=0〜1(0) : 初期化する画面モード

%inst
screen命令と同じく、指定したウィンドウIDを初期化して使用できるようにし
ます。初期化する画面サイズと、画面モードはscreen命令と変わりませんが、
buffer命令では、メモリ上に仮想画面が作られるだけで、実際の画面には表示
されません。
これで作成した仮想画面は、通常の画面と同じようにprint命令やpicload命令
を使用することができます。 gcopy命令などで別の画面にコピーするためのス
トック場所に使ったり、現在の画面を一時的に残しておくための保管場所に使
うことができます。
^
なお、screenで初期化されたウィンドウIDをbuffer命令で再初期化することは
できません。
^
buffer命令で画面を初期化した後はそのウィンドウIDが画面制御命令の描画先
になります。

%href
screen
bgscr
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
モードは、1がフルカラーモード(32bit)、 2がパレットモード(8bit)となりま
す。変更モードが0の場合は、最初の状態(変更前)に復帰します。
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
フォント名は、"ＭＳ 明朝"、"ＭＳ ゴシック"などのフォント名を直接指定し
てください。
フォントの大きさはドット数に比例した論理サイズで指定します。
数が大きいほど、文字も大きくなります。フォントのスタイルは、
^p
  スタイル 1  : 太文字
  スタイル 2  : イタリック体
  スタイル 4  : 下線
  スタイル 8  : 打ち消し線
  スタイル16  : アンチエイリアス
^p
となります。数値を合計することで複数のスタイルを同時に指定することも可
能です。p2を省略すると、0(通常のスタイル)になります。
^
スタイル16を指定すると、文字の縁にあるギザギザが消えて滑らかな表示にな
ります。ただし、画面モードがフルカラーで初期化されている必要があるほか、
Windows9X環境はサポートされないのでご注意下さい。
(WindowsXPでは、常にアンチエイリアスが有効になります。)
^
初期設定やシステム指定のフォントに戻すには、 sysfont命令を使用してくだ
さい。また、オブジェクトのフォントを変更する場合には、 objmode命令でモ
ードの指定を行なう必要があります。
^
指定されたフォントが発見できなかった場合には、代用のフォントが自動的に検索されます。
代用フォントの検索にも失敗した場合には、システム変数statに-1が代入されます。
フォントが正常に設定された場合には、システム変数statに0が代入されます。

%href
sysfont
objmode
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
p2,p3     : コピー元の左上X,Y座標
p4,p5     : コピーする大きさX,Y（ドット単位）

%inst
gcopy命令は、 指定したウィンドウIDの画面の一部を、現在の描画先カレント
ポジションにコピーします。
コピー元のウィンドウIDは、自分のウィンドウIDと同じかまたは、screen命令
やbuffer命令で初期化されたウィンドウIDでなければなりません。
^
gcopy命令でコピーする場合は、gmode命令によってコピーするモードをいくつ
か選ぶことができます。
^
gcopy命令でパレットモード画面の画像をコピーする際には注意が必要です。
コピーする２つのウィンドウのパレットが同じものでも問題のない画像を準備する必要があります。
また、パレットモード時のパレットは、ユーザー側で正しいものを設定するようにしてください。
(画像ファイル使用時に、picload命令だけではパレット設定は行なわれません。)

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
p2,p3        : コピーする大きさX,Y（ドット単位）
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
動作は モード0と同じですが、非常に小さいサイズ(16*16ドット以下等)のコピーを
行った際 モード0よりも 若干 高速になる場合があります。
^p
・モード2 = 透明色付きコピー
^p
モード1と同様の方法でコピーを行ないますが、 RGBがすべて0(完全な黒)のド
ットは透明色とみなされコピーされません。
^p
・モード3 = 半透明合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による半透明合成コピーを
行ないます。ブレンド率は0〜256の値となり、256で完全なコピーになります。
ブレンド率が0の場合はコピーは実行されません。
また、ブレンド率が256以上はメモリ間コピーが実行されます。
^p
・モード4 = 透明色付き半透明合成コピー
^p
モード3と同様の方法でコピーを行ないますが、RGB値が color命令で設定され
た色と同じドットは透明色とみなされコピーされません。
ブレンド率が0の場合はコピーは実行されません。
^p
・モード5 = 色加算合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による色加算合成コピーを
行ないます。色加算では、コピー先のRGB値に、コピー元のRGB値を加算します。
加算時に輝度が255を越える場合は、255にクランプされます。
^p
・モード6 = 色減算合成コピー
^p
フルカラーモード時のみ使用することができます。
gmodeの4番目のパラメーターで指定したブレンド率による色減算合成コピーを
行ないます。色減算では、コピー先のRGB値から、コピー元のRGB値を減算しま
す。減算時に輝度が0を下回る場合は、0にクランプされます。
^p
・モード7 = ピクセルアルファブレンドコピー
^p
フルカラーモード時のみ使用することができます。
gmodeで指定されたサイズの画像を、元画像の右側に用意しておき、 右側の画
像をアルファブレンド成分として背景合成コピーを行ないます。
アルファブレンド成分が255の場合は、 そのまま元画像のピクセルがコピーさ
れ、255より小さい場合には、そのブレンド率で背景と合成されます。
ピクセルはRGB単位で参照されるため、RGBに異なるブレンド率を設定可能です。
アルファブレンド画像は、通常 (0,0,0)〜(255,255,255) のグレースケールで
表現するといいでしょう。
^p
これらのモードは、gzoom命令では使用されません。
あくまでもgcopy命令使用時なので注意してください。
また、gmodeは現在 gsel命令で選択されているウィンドウIDのモードが変更さ
れます。gmodeの設定後に、別なウィンドウIDでgcopy命令を実行しても設定が
反映されないので注意してください。
^
(p2,p3)はコピーサイズのデフォルトを設定します。この値は、gcopy,gzoom命
令でコピーする大きさの値を省略した場合にデフォルトで使われるサイズです。

%href
gcopy
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
これ以降は、p1で指定したウィンドウIDの画面に対して、mes命令やpicload命
令などの画面描画に関する命令が実行されるようになります。
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
p2=-1で非表示にした場合は、 指定したウィンドウが消えますが完全に消去さ
れるわけではありません。再びp2=1か2でアクティブにすると復帰します。
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
p1,p2      : 画面にコピーする時の大きさX,Y（ドット単位）
p3=0〜(0)  : ウィンドウID
p4,p5      : コピー元の左上X,Y座標
p6,p7      : コピーする大きさX,Y（ドット単位）
p8=0〜1(0) : ズームのモード

%inst
gzoom命令は、 指定したウィンドウIDの画面の一部を現在の描画先カレントポ
ジションに、任意の大きさに変倍してコピーします。
コピー元のウィンドウIDは、自分のウィンドウIDと同じかまたは、screen命令
やbuffer命令で初期化されたウィンドウIDでなければなりません。
^
p8でズームのモードを指定することができます。
p8に1を指定した場合には、 拡大縮小時にハーフトーンを使用した高品質な画
像を生成します。(Windows9Xでは動作しません。)
^
p8が0か、または省略されている場合は、ハーフトーンを使用しませんが、 そ
のぶん高速に画像処理を行なうことができます。

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
p1はパレットコードになります。パレットコードは、 
パレットモード画面のために用意された256色(palette命令により設定された色)の
中で何番目かを示すものです。
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
p5が0か省略されている時は、パレットに値を設定しますが、 すぐには画面上
に反映されません。
p5が1の時は、設定したパレット全体が画面上にも反映されます。
画面上に反映されるまでには時間がかかるため、パレットをまとめて更新する
場合には、一番最後に更新スイッチを1にするようにしてください。

%href
palcolor




%index
pget
1dotの点を取得
%group
画面制御命令
%prm
p1,p2
p1,p2 : 画面上のX,Y座標

%inst
画面上の1ドットの色データを読みだします。
^
指定した座標にあるドットの色データが選択色として設定されます。
(color命令で指定したのと同じ状態になります)

%href
ginfo
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
とするだけで、"test.bmp"で指定された画像ファイルが現在の画面にロードさ
れ、ウィンドウサイズが自動的に絵のサイズに合わせられます。
^
p1の画像ロードモードは、
^p
  モード０：ウィンドウを初期化してロード
  モード１：現在の画面の上にロード
^p
p1のロードモードを省略もしくは０にすることで、画像のサイズで初期化した
ウィンドウにロードされます。
^
p1にロードモード１を指定することで、現在のウィンドウのサイズなどを一切
変更せず指定した座標からロードすることができます。 この場合は、pos命令
で指定した座標が左上となります。
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
picload命令は、screen、buffer、 bgscr命令で初期化
された画面に対して実行することができます。

%href
screen
buffer
bgscr
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
p1,p2 : カレントポジションのX,Y座標

%inst
メッセージ表示、オブジェクトの表示などの基本座標となるカレントポジショ
ンの座標を指定します。
^
Xは一番左が0に、Yは上が0になり、1ドット単位の指定になります。
パラメータの省略をすると、現在の値が使われます。

%href
mes
%port+
Let



%index
pset
1dotの点を表示
%group
画面制御命令
%prm
p1,p2
p1,p2 : 画面上のX,Y座標

%inst
画面上に現在設定されている描画色で1ドットの点を描画します。
^
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
p2,p3      : 再描画する左上X,Y座標
p4,p5      : 再描画する大きさX,Y（ドット単位）

%inst
画面の描画モードを指定します。描画モードとは、
^
描画モード0:
^p
mes,print,gcopy,gzoom などの画面制御命令が実行されても仮想画面を書き換
えるだけで、実際の画面には反映されません。
^p
描画モード1:
^p
画面制御命令が実行されると、実際の画面にも反映されます。
^p
となっています。通常は描画モード１です。
描画モード0で画面内に画像をコピーしたり、メッセージを表示しておいて、
最後にモード1にすることで画面の書き換えのちらつきをなくしスムーズに見
せることができます。
^
モード1を指定した場合は即座に画面の更新を行います。
^
モード値に2を足した値を指定すると、描画モードのみを変更し画面の更新はされません。
^
また、p2〜p5までのパラメータにより、画面の一部だけを再描画させることが
可能です。通常は省略すれば、全画面の更新を行ないます。
%port+
Let



%index
screen
ウィンドウIDを初期化
%group
画面制御命令
%prm
p1,p2,p3,p4,p5,p6,p7,p8
p1=0〜(0)   : ウィンドウID
p2,p3       : 初期化する画面サイズX,Y（1ドット単位）
p4=0〜31(0) : 初期化する画面モード
p5,p6       : ウィンドウの配置X,Y（1ドット単位）
p7,p8       : クライアントエリアのサイズX,Y（1ドット単位）

%inst
指定したウィンドウIDを初期化して使用できるようにします。 
HSPの初期状態では、ウィンドウID0の画面しか使用されていませんが、
ウィンドウID1以上を指定することで、新しいウィンドウを作成することができます。
ID1以上のウィンドウは、標準でサイズを自由に変えることが可能なスタイルを
持つことになります。
^
p4の初期化する画面モードは、以下から選ぶことができます。
^p
   1 : パレットモード(1670万色中256色)で作成する
   2 : 非表示のウィンドウを作成する
   4 : サイズ固定ウィンドウ
   8 : ツールウィンドウ
  16 : 深い縁のあるウィンドウ
^p
p4パラメータに「+1」(パレットモードで作成する)を指定した場合は、パレッ
トあり256色のモードで画面が作成されます。 このモードを指定しなかった場
合は、フルカラー(24bitカラー)の画面が作成されます。
^
p4パラメータに「+2」(非表示のウィンドウを作成する)を指定した場合は、
実行時にはウィンドウが表示されませんが、「gsel ID,1」 で表示させること
が可能です。
^
p4パラメータのうち「+4」「+8」「+16」 はそれぞれウィンドウのスタイルを
設定するためのものです。
「サイズ固定ウィンドウ」は、ID1以降のウィンドウでも、ID0のウィンドウと
同様のサイズ変更が不可能なスタイルで作成されます。
「ツールウィンドウ」は、タイトルバーのサイズが小さくなりタスクバーにウ
インドゥ名が表示されないウィンドウが作成されます。
^
p4パラメータが省略された場合は、 現在のWindows画面モードがパレットあり
(256色) の場合はパレットモードで作成され、そうでない場合はフルカラーの
画面として作成されます。
^
画面モードの値は、値を合計することで複数の設定を行なうことができます。
たとえば、
^p
	screen 2,320,240,4+8
^p
は、サイズ固定+ツールウィンドウのスタイルを持ったものが作成されます。
^
screen命令は、すでに初期化されているウィンドウIDをふたたび別の設定で再
初期化することも可能です。
^p
例 ：
	screen 0,640,480,1
^p
上の例では、ウィンドウID0、つまりメインウィンドウを640x480ドット、パレ
ットモードで再初期化します。
^
p7,p8のパラメータで、ウィンドウのクライアントサイズ(実際に表示される大
きさ)を指定することができます。
^
screen命令で画面を初期化した後はそのウィンドウIDが画面制御命令の描画先
になります。

%href
bgscr
buffer
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
p1,p2 : クライアントエリアのサイズX,Y（1ドット単位）
p3,p4 : ディスプレイ上でのウィンドウX,Y座標（1ドット単位）

%inst
ウィンドウのクライアントサイズ(実際に表示される大きさ)とウィンドウ表示
位置を変更します。
クライアントサイズは、screen命令やbuffer,bgscr命令で初期化された画面サ
イズより大きくすることはできません。
^
p1,p2およびp3,p4パラメータが省略された場合は、現在の設定が使われます。

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
    0 : HSP標準システムフオント
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
p1,p2 : ラインの終点X,Y座標
p3,p4 : ラインの始点X,Y座標

%inst
画面上に、(p1,p2)と(p3,p4)を結ぶ直線を描画します。
(p3,p4)を省略した場合は、カレントポジションから(p1,p2)まで、現在設定さ
れている色で直線が描画されます。
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
p1,p2      : 矩形の左上X,Y座標
p3,p4      : 矩形の右下X,Y座標
p5=0〜1(1) : 描画モード(0=線,1=塗りつぶし)

%inst
画面上に、(p1,p2)と(p3,p4)を左上、右下の点として、矩形(四角形)に収まる
大きさの円を描画します。
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
 2 : アクティブウィンドウのタイトルバーの色
 (グラデーションの場合はアクティブウィンドウのタイトルバーの左側の色)

 3 : 非アクティブウィンドウのタイトルバーのテキストの色
 (グラデーションの場合は非アクティブウィンドウのタイトルバーの左側の色)

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
29 : (Windows XP以上) メニューがフラットメニューとして表示されるときに
     メニューアイテムをハイライト表示するのに使用される色
30 : (Windows XP以上) メニューがフラットメニューとして表示されるときの
     メニューバーの背景色
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
p1=0〜(0) : 取得するタイプ

%inst
p1で指定したタイプのウィンドウ関連情報値を返します。
取得できるタイプは以下の通りです。
^p
  0 : スクリーン上のマウスカーソルX座標
  1 : スクリーン上のマウスカーソルY座標
      スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標では
      なく、デスクトップ画面全体から見た座標になります。

  2 : アクティブなウィンドウID

      現在アクティブになっているウィンドウIDを返します。
      もし、 アクティブになっているウィンドウがHSP以外の場合は-1になり
      ます。

  3 : 操作先ウィンドウID

      gsel命令で指定した画面の操作先ウィンドウIDが代入されます。

  4 : ウィンドウの左上X座標
  5 : ウィンドウの左上Y座標

    スクリーン座標系で現在のウィンドウの左上座標を返します。
    スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、
    デスクトップ画面全体から見た座標になります。

  6 : ウィンドウの右下X座標
  7 : ウィンドウの右下Y座標

      スクリーン座標系で現在のウィンドウの右下座標を返します。
      スクリーン座標系は、 pos命令などで使用するウィンドウ内の座標ではなく、
      デスクトップ画面全体から見た座標になります。

  8 : ウィンドウの描画基点X座標
  9 : ウィンドウの描画基点Y座標

      現在の操作先ウィンドウの描画基点座標を返します。
      これは、描画内容をスクロール可能な(初期化サイズよりも表示サイズが
      小さい)ウィンドウにおいて、どれだけスクロールされているかを示す値です。
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

      最後にmes, print命令により出力されたメッセージのサイズが返されま
      す。サイズは、 X,Y座標にどれだけのドット数で描画されたかを示しま
      す。画面上の絶対座標ではないので注意してください。また、複数行あ
      る文字列を出力した場合は、最後の行にあたるサイズが取得されます。

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

      oncmd命令により設定されたメッセージ割り込み時のウィンドウIDが返
      されます。

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
(p1,p2)で指定した座標を中心として、 (p4,p5)で指定したサイズの矩形(長方
形)を現在設定されている色で描画します。
p3で回転角度を実数で指定することができます。
角度の単位は、ラジアン(0から始まって、2πで一周)となります。
grect命令は、gmodeで設定されたコピーモードの指定が反映されます。
^
gmodeが 0,1の場合は、通常の塗りつぶし。
gmodeが 3の場合は、指定されたレートで半透明になります。
gmodeが 5, 6の場合は、それぞれ色加算、色減算処理となります。
また、(p4,p5)のサイズ指定を省略した場合には、gmode命令で設定されている
コピーサイズが使用されます。
^
 パレットモード時には 指定した描画色で塗りつぶしが行なわれますが、
半透明処理は行われません。

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
p1で、コピー元のウィンドウIDを指定、(p2,p3) でコピーされる元の画像にあ
たる座標を指定します。(gcopy命令と同様です)
コピー先は、現在の描画先に指定されているウィンドウIDで、 pos命令で設定
された場所を中心とした座標にコピーを行ないます。その際に、p3で回転角度
を実数で指定することができます。
角度の単位は、ラジアン(0から始まって、2πで一周)となります。
(p5,p6)で、コピーされた後のX,Yサイズを指定します。
また、コピー元のX,Yサイズはgmode命令で設定されたデフォルトのコピーサイ
ズが使用されます。
つまり、gmode命令で指定されたサイズよりも大きなサイズを(p5,p6)で指定し
た場合には、拡大されることになります。
(p5,p6) を省略した場合には、コピー元と同じサイズ、つまり等倍でコピーが
行なわれます。
^
grotate命令は、gmodeで設定されたコピーモードの指定が反映されます。
(モード7のピクセルアルファブレンドコピーは適用されません。)
透明色の設定や、半透明の設定はすべて gcopy命令でコピーした場合と同等に
機能します。(詳しくはgmode命令のリファレンスを参照)
^
パレットモード時には半透明処理は実行されません。
また、異なる画面モード(パレットモードとフルカラーモード)間でのコピーは
エラーになります。

%href
grect
gsquare
gmode
%port+
Let


%index
gsquare
任意の四角形画像をコピー
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
p1に-1などマイナス値を指定した場合は、画像コピーではなく塗りつぶしが行
なわれます。
その際、フルカラーモード時には 描画色による塗りつぶしとなります。
パレットモード時は、p1で指定した値-1をパレットコードとして塗りつぶしを
行ないます。
(-1〜-256がパレットコード0〜255に対応します)
^
p2,p3にはコピー先の座標４つを配列に格納した変数を指定します。
p4,p5にはコピー元の座標４つを配列に格納した変数を指定します。
配列変数には、左上(0),右上(1),右下(2),左下(3) の順番に座標を入れておく
必要があります。
塗りつぶしを行なう場合には、(p4,p5)を指定する必要はありません。
^
gsquare命令は、gmodeで設定されたコピーモードの指定が反映されます。
(モード7のピクセルアルファブレンドコピーは適用されません。)
透明色の設定や、半透明の設定はすべて gcopy命令でコピーした場合と同等に
機能します。(詳しくはgmode命令のリファレンスを参照)
^
パレットモード時には半透明処理は実行されません。
また、異なる画面モード(パレットモードとフルカラーモード)間でのコピーは
エラーになります。

%href
grect
grotate
gmode
color
hsvcolor
palcolor
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
現在アクティブなウィンドウに配置されている、特定のウィンドウオブジェク
トに関連する情報値を返します。
p1にウィンドウオブジェクトID、p2に取得タイプを指定することで、該当する
情報データが返されます。
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
外部API(DLL)等にウィンドウオブジェクトのハンドル(HWND)を渡す場合など、
特殊な用途に利用することができます。

%href
ginfo
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
p2,p3 : オブジェクトのX,Yサイズ


%inst
"IID"で指定されたクラスIDまたは、プログラムID(ProgID)を持つActiveXコン
トロール(OLEコントロール)をウィンドウオブジェクトとして配置します。
p2,p3で配置するX,Yサイズを指定します。 
サイズの指定が省略されるか0以下の場合は、objsizeで設定されている値が使
用されます。
配置に成功した場合は、システム変数statにオブジェクトIDが代入され、p1の
変数をコントロールのためのCOMオブジェクト型変数として初期化します。
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
winobjは、 Windowsのシステムがサポートするウィンドウをオブジェクトとし
て配置します。
p3,p4で配置するX,Yサイズを指定します。 サイズの指定が省略されるか0以下
の場合は、objsizeで設定されている値が使用されます。
^
指定したウィンドウオブジェクトが生成されるとシステム変数statにオブジェ
クトIDが代入されます。
このオブジェクトIDは、clrobj命令を始めとするオブジェクト操作命令で使用
することができます。
(生成されたウィンドウは、 現在アクティブなウィンドウが管理するオブジェ
クトとして登録されます。)
内部エラーなどでウィンドウオブジェクトが正常に生成されなかった場合には
、システム変数statに-1が代入されます。
^
winobjによって配置したオブジェクトに対してobjprm命令を使用することはできません。
^
この命令は、HSPの命令がサポートしていないウィンドウオブジェクトを
Windows APIを通して配置するためのもので、WIN32API のCreateWindowExと同
様のパラメーターを受け取ります。 外部DLLとのやり取りや、モジュール作成
に使用するもので通常覚えておく必要はありません。



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
p5(0) : lParamの取得モード

%inst
p1で指定したウィンドウハンドルに対して、 p2のメッセージとp3,p4のパラメ
ーターを送信します。
^
p1で指定するウィンドウハンドルの値は、 HSPのウィンドウであれば
システム変数hwndを、HSPのウィンドウオブジェクトの場合はobjinfo関数により
取得することができます。
^
p3をwParam、p4をlParamの情報としてウィンドウメッセージが送信されます。
p3パラメーターは、整数値を指定することが可能です。
p4パラメーターには、整数値、文字列、変数のいずれかを指定することができます。
整数値の場合は、値そのものをlParamとして扱います。
文字列の場合は、文字列ポインタ値をlParamとして扱います。
p4が変数の場合にのみ、扱うモードをp5で指定することができます。
p5が0の場合は、変数の情報が格納されているメモリポインタ値をlParamとして
扱います。p5が0以外の場合には、変数が保存している整数値をlParamとして
扱うことになります。
^
この命令は、 HSPの命令がサポートしていないウィンドウオブジェクトに対し
てWindowsのメッセージを送信するためのものです。
外部DLLとのやり取りや、 モジュール作成に使用するもので通常覚えておく必
要はありません。

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
p1,p2      : ウィンドウに描画する基点となるX,Y座標

%inst
ウィンドウに描画する基点座標を設定します。
基点座標は、描画内容をスクロール可能な(初期化サイズよりも表示サイズが
小さい)ウィンドウにおいて、X,Y方向にどれだけスクロールされているかを示すものです。
(0,0)を設定すると、スクロールさせていない通常の状態になります。
現在設定されている基点座標は、ginfo関数によって取得することができます。

%href
ginfo
%port+
Let


