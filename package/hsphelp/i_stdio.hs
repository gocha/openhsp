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
Cli
Let




%index
getkey
キー入力チェック
%group
基本入出力制御命令
%prm
p1,p2
p1=変数   : 読み込むための変数
p2=1〜(1) : キーコード

%inst
キーボード及びマウスボタンの状態をチェックして変数に代入します。指定したボタンが押されていれば、1を代入し、押されていなければ0が代入されます。
キーコードで指定する値の詳細は、以下の通りです。
^p
  キーコード : 実際のキー
 ------------------------------------------
        1    : マウスの左ボタン
        2    : マウスの右ボタン
        3    : キャンセル（[CTRL]+[BREAK]）
        4    : ３ボタンマウスのまん中のボタン
        8    : [BACKSPACE]（PC98の[BS]）
        9    : [TAB]
       13    : [ENTER]
       16    : [SHIFT]
       17    : [CTRL]
       18    : [ALT]（PC98の[GRPH]）
       20    : [CAPSLOCK]
       27    : [ESC]
       32    : スペースキー
       33    : [PAGEUP]（PC98の[ROLLDOWN]）
       34    : [PAGEDOWN]（PC98の[ROLLUP]）
       35    : [END]（PC98の[HELP]）
       36    : [HOME]（PC98の[HOMECLR]）
       37    : カーソルキー[←]
       38    : カーソルキー[↑]
       39    : カーソルキー[→]
       40    : カーソルキー[↓]
   48〜57    : [0]〜[9]（メインキーボード）
   65〜90    : [A]〜[Z]
  96〜105    : [0]〜[9]（テンキー）
 112〜121    : ファンクションキー [F1]〜[F10]
^p
この表に載っているキー以外でも、取得できる場合があります。(サンプルを実行するとキーコードを調べることができます。)


%sample
title "キー入力してください(^^)v"
onkey *inkey
onclick *inkey
stop
*inkey
if lparam>>30:stop
mes iparam
stop


%href
stick




%index
mouse
マウスカーソル座標設定
%group
基本入出力制御命令
%prm
p1,p2
p1,p2 : 設定するX,Y座標

%inst
マウスカーソルをp1,p2で指定した座標に変更します。
指定する座標は、  ウィンドウ内の座標ではなくディスプレイでの座標(X=0〜ginfo_dispx/Y=0〜ginfo_dispy)を指定します。
p1または、p2が-1の場合は、HSPウィンドウ上でのマウスカーソルの表示をOFFにします。
p1やp2の指定を省略した場合は、現在の座標がそのまま適用されます。
マウスカーソルの表示をOFFにした後は、p1とp2を省略した「mouse」のみを実行すると再び表示されるようになります。

マウスカーソル表示の設定は、システムの内部カウンタにより制御されています。
OFFにした表示を、再度表示するためには、OFFにした回数分だけ表示のリクエストを行なう必要があるので注意してください。

%port-
Let




%index
randomize
乱数発生の初期化
%group
基本入出力制御命令
%prm
p1
p1=0〜(不定) : 乱数の初期化パラメーター

%inst
rnd関数で発生させる乱数のパターンを初期化します。
^
p1に同じ値を指定して初期化された乱数は、常に同じパターンで乱数を発生させられます。
p1を省略した場合は、 Windowsのタイマから得られた不定な値を使って初期化します。これによって、毎回まったく違う乱数を発生させることができます。

%href
rnd




%index
stick
キー入力情報取得
%group
基本入出力制御命令
%prm
p1,p2,p3
p1=変数    : 読み込むための変数
p2=0〜(0)  : 非トリガータイプキー指定
p3=0〜1(1) : ウィンドウアクティブチェックON/OFF

%inst
よく使われるキーボード及びマウスボタンの状態をまとめてチェックして変数に代入します。
^
stick命令が実行されると以下のような複数のボタン情報が１つの数値として、p1で指定した変数に代入されます。
^p
    1 : カーソルキー左(←)
    2 : カーソルキー上(↑)
    4 : カーソルキー右(→)
    8 : カーソルキー下(↓)
   16 : スペースキー
   32 : Enterキー
   64 : Ctrlキー
  128 : ESCキー
  256 : マウスの左ボタン
  512 : マウスの右ボタン
 1024 : TABキー
^p
何もボタンが押されていない場合には0が代入されます。
^
もし複数のボタンが同時に押されていた場合には、それらの数値がすべて加算されます。
たとえば、カーソルキーの右とスペースキーが同時に押されている場合には、4+16の20が変数に読み込まれます。
この数値をif命令などでチェックする場合には、演算子「&」が役に立ちます。
^p
例 :
	stick a,0            ; 変数aにキー状態を読み出し
	if a&16 : goto *spc  ; スペースが押されたか?
	if a&32 : goto *ent  ; Enterが押されたか?
^p
このように「変数&キー情報」で複数のボタン情報が入った数値から、 １つだけのキー情報を取り出すことができます。
^
stick命令は、 getkey命令によく似ていますが、最大の違いはボタンが押された瞬間だけを検出する点です。つまり、ボタンが押された時に１度だけ押されている情報を返し、あとは押されているボタンをはなすまでは、押されていることになりません。
^
ただし、p2の非トリガータイプキー指定により、押しっぱなしであっても情報を検出することができるようになります。
^
p2に押しっぱなしでも検出されるキーのコード(上の表にあるコードです。 複数の場合はそれぞれの数値を加えます)を指定すると、 そのキーだけはボタンが押されている間ずっと検出されるようになります。
^
この命令は、非常に複雑に見えますがキーを使ったスクリプトを作る際にとても便利な機能となるでしょう。
たとえば、シューティングゲームを思い浮かべてみてください。自分の機体は上下左右の方向にボタンが押されている間ずっと移動しなければなりません。しかし、ミサイルを発射するボタンは１回押してはなすまでは次の弾は発射されません。
このような場合には、上下左右のキーだけは非トリガータイプのキーに指定して、それ以外は１度だけ押された情報を返すようにすればいいわけです。
^
また、p3でウィンドウがアクティブでない場合は入力を無効にする機能をON/OFFすることができます。
p3が1か省略された場合は、HSPウィンドウがアクティブでない場合にはキー入力が無効になります。
p3が0の場合は、すべての状況下でキー入力を行ないます。


%href
getkey
jstick



%index
logmes
デバッグメッセージ送信
%group
HSPシステム制御命令
%prm
"message"
"message" : ログに記録するメッセージ

%inst
デバッグウィンドウ表示時に、"message"の内容をデバッグログに記録します。
ある時点での変数の内容や、通過チェックなどに利用できます。
スクリプトエディタからデバッグウィンドウの表示モードを設定するか、assert命令によってデバッグウィンドウを表示させておく必要があります。
実行ファイル作成時は、この命令は無効になります。

%href
assert



%index
assert
デバッグウィンドウ表示
%group
HSPシステム制御命令
%prm
p1
p1(0) : デバッグ時の条件式

%inst
プログラムを一時的に中断してデバッグウィンドウを表示します。
p1に条件式が指定された場合には、p1の条件が正しくない場合にのみデバッグウィンドウを表示します。
(p1には、通過する時の条件式を書くことになるので注意してください。)
^p
	assert a>5  ; aが5以下の時にデバッグする
^p
実行ファイル作成時は、この命令は無効になります。

%href
logmes
%port-
Let



%index
mcall
メソッドの呼び出し
%group
基本入出力制御命令
%prm
p1,p2,p3…
p1 : 変数名
p2 : メソッド名
p3 : パラメーター

%inst
p1で指定された変数の型に応じてメソッドを呼び出します。
p1の変数にCOMオブジェクト型を指定することで、COMオートメーションのメソッドを呼び出すことが可能です。
p2でメソッド名(文字列)または、ディスパッチID(DISPID)を指定して、p3以降に引数を指定します。
p3以降のパラメーター数や、型はそのまま適切に変換されメソッドに渡されます。
メソッドを実行した結果の返値は、comres命令で設定された変数に代入されます。
また、メソッド実行が成功した場合にはシステム変数 statは0になり、実行エラーが起こった場合には、 システム変数statに結果コード(HRESULT)が代入されます。

mcall命令は、拡張された変数の型を用意することで、 新しい機能を提供することが可能です。標準では、COMオブジェクト型のみに対応しています。

%href
#usecom
newcom
delcom
querycom
comres
%port-
Let



