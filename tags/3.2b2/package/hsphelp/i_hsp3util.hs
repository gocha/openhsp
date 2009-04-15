;
;	HSP help manager用 HELPソースファイル
;	(先頭が;の行はコメントとして処理されます)
;

%type
拡張命令
%ver
3.1
%note
hsp3util.asをインクルードすること。
%date
2006/04/20
%author
onitama
%dll
hsp3util
%url
http://www.onionsoft.net/
%port
Win


%index
bmppalette
bmp画像パレット情報を読み込む
%group
拡張画面制御命令
%prm
"ファイル名"
"ファイル名" : パレットを取り出すBMP画像ファイル名

%inst
8bit形式のbmp画像ファイルに含まれるパレット情報を読み込み、HSPのパレットとして取り出します。
通常、picload命令によるパレットモードでの画像読み込みは、ファイルに付属しているパレット情報を読み込むことができません。
hspdx拡張プラグインなど、ファイル内のパレット情報が必要となる場合に、使用することができます。
ファイルとして指定することができるのは、8BIT形式のBMPファイルのみです。
それ以外のファイルや、正しくない形式が指定された場合には、何も行なわれません。

%href
palette
getpal



%index
gettimestr
現在の時刻を文字列で取得する
%group
拡張入出力制御命令
%prm
p1
p1 : 文字列を取得する変数名

%inst
現在の時刻を取得して、"hh:mm:ss"の文字列型形式として変数に代入します。

%href
getdatestr



%index
getdatestr
現在の日付を文字列で取得する
%group
拡張入出力制御命令
%prm
p1
p1 : 文字列を取得する変数名

%inst
現在の日付を取得して、"yyyy/mm/dd"の文字列型形式として変数に代入します。

%href
gettimestr



%index
text
修飾文字表示の待ち時間を設定する
%group
拡張画面制御命令
%prm
p1
p1(0) : 表示待ち時間(ms)

%inst
emes命令で表示される文字の待ち時間を設定します。
p1で１文字ごとの待ち時間(ミリ秒単位)を指定します。
p1に0以下の値を指定した場合は、１文字ごとの待ちは行なわず一度に表示されます。
text命令は、HSP3から標準でなくモジュールを使用した拡張命令として扱われています。
HSP2.xと異なり、text命令で指定した待ち時間はemes命令に反映されますので注意してください。

%href
textmode
emes


%index
textmode
修飾文字表示の設定を行なう
%group
拡張画面制御命令
%prm
p1,p2
p1(0) : 修飾文字のモード
p2(0) : 調整パラメーター

%inst
emes命令で表示される修飾文字の設定を行ないます。
p1でモードを指定します。モードの値は以下の通りです。
^p
	モード0 : 通常の表示
	モード1 : 影付き表示
	モード2 : 輪郭付き表示
^p
モード1,2を指定した場合は、textmode命令を実行した時点で設定されている色が影や輪郭で使用されます。
また、p2に調整パラメーターを設定することで影や輪郭の距離を修正することができます。
調整パラメーターが0の場合は、最低距離(1ドット)となり値が大きくなるごとに距離も大きくなります。

%href
text
emes



%index
emes
修飾文字を表示
%group
拡張画面制御命令
%prm
"strings"
"strings" : 表示するメッセージまたは変数

%inst
修飾文字を表示します。
emes命令は、mes命令と同様に文字列を画面上に表示しますが、その時に文字に修飾を行なったり、１文字づつゆっくりと表示させることができます。
修飾文字の設定は、textmode命令で行なうことができます。
また、修飾文字の表示速度はtext命令で指定することができます。

%href
textmode
text




%index
gfade
画面のフェードを行なう
%group
拡張画面制御命令
%prm
p1,p2,p3,p4,p5
p1(0) : フェードレベル(0〜256)
(p2,p3) : フェードを行なう左上X,Y座標
(p4,p5) : フェードを行なうX,Yサイズ

%inst
フルカラー画面に対して、指定された領域を固定色フェードを行ないます。
この命令は、時間ごとにフェードレベルを変えていくことになって、フェードイン、フェードアウトなどを行なうためのものです。
p1でフェードレベルを指定します。0の場合は画面に影響はありません。
p1が256の時、完全に指定した色で塗りつぶされた状態になります。
(p2,p3)でフェードを行なう左上X,Y座標を指定します。省略した場合は、(0,0)となります。
(p4,p5)でフェードを行なうX,Yサイズを指定します。省略した場合は、画面全体のサイズが使用されます。

%href




%index
statictext
スタティックテキストを配置
%group
拡張画面制御命令
%prm
"strings",p1,p2
"strings" : スタティックテキストの文字列
p1(0) : Xサイズ
p2(0) : Yサイズ

%inst
現在のカレントポジションから、スタティックテキストを配置オブジェクトとして生成します。
配置されたオブジェクトIDは、システム変数statに代入されます。
配置されるオブジェクトのサイズを(p1,p2)で指定することができます。
配置されたスタティックテキストの内容を変更する場合は、statictext_set命令を使用してください。
objprm命令は使用できないので注意してください。

%href
statictext_set



%index
statictext_set
スタティックテキストを変更
%group
拡張画面制御命令
%prm
p1,"strings"
p1(0) : オブジェクトID
"strings" : スタティックテキストの文字列

%inst
statictext命令で配置した、スタティックテキストの内容を変更します。
p1にオブジェクトIDを指定して、"strings"で新しく設定するスタティックテキストの文字列を指定することができます。

%href
statictext




%index
scrollbar
スクロールバーを配置
%group
拡張画面制御命令
%prm
p1,p2
p1(0) : Xサイズ
p2(0) : Yサイズ

%inst
現在のカレントポジションから、スクロールバーを配置オブジェクトとして生成します。
配置されたオブジェクトIDは、システム変数statに代入されます。
配置されるオブジェクトのサイズを(p1,p2)で指定することができます。
この命令は、配置オブジェクトとしてスクロールバーを生成することをサポートするものです。
配置されたスクロールバーに対するメッセージの送受信は、別途sendmsg命令で行なう必要があります。
その際には、WIN32APIのスクロールバーメッセージに関する資料が別途必要になります。
また、配置したオブジェクトに対しては、objprm命令は使用できないので注意してください。

%href





%index
progbar
プログレスバーを配置
%group
拡張画面制御命令
%prm
p1,p2
p1(0) : Xサイズ
p2(0) : Yサイズ

%inst
現在のカレントポジションから、プログレスバーを配置オブジェクトとして生成します。
配置されたオブジェクトIDは、システム変数statに代入されます。
配置されるオブジェクトのサイズを(p1,p2)で指定することができます。
配置されたプログレスバーを進める場合は、progbar_setおよびprogbar_step命令を使用してください。
また、配置したオブジェクトに対しては、objprm命令は使用できないので注意してください。

%href
progbar_set
progbar_step



%index
progbar_set
プログレスバーのステップ増分を設定する
%group
拡張画面制御命令
%prm
p1,p2
p1(0) : オブジェクトID
p2(0) : 増分値

%inst
p1にオブジェクトIDを指定することで、progbar命令で配置したプログレスバーの1ステップごとの増分を設定することができます。
プログレスバーは、デフォルトで0から100までの値をカウンタとして持っています。
これに対して、１ステップごとに増分を加算していきます。
増分を指定しなかった場合のデフォルト値は10になります。

%href
progbar_step
progbar



%index
progbar_step
プログレスバーを1ステップ進める
%group
拡張画面制御命令
%prm
p1
p1(0) : オブジェクトID

%inst
p1にオブジェクトIDを指定することで、progbar命令で配置したプログレスバーを1ステップ進めます。
1ステップごとの増分は、progbar_set命令によって指定することができます。

%href
progbar_set
progbar




%index
note2array
複数行文字列を配列に変換
%group
拡張入出力制御命令
%prm
p1,p2
p1 : 変換した配列を代入する変数
p2 : 複数行文字列が代入されている変数

%inst
複数行の文字列を行ごとに分割して配列変数の各要素に代入します。
p2で指定された複数行文字列を、p1で指定した変数に変換して代入します。
p1の変数は、必ず文字列型の１次元配列変数になります。

%href
array2note
arraysave
arrayload




%index
array2note
配列を複数行文字列に変換
%group
拡張入出力制御命令
%prm
p1,p2
p1 : 変換したを文字列を代入する変数
p2 : 文字列が配列に代入されている変数

%inst
文字列型の１次元配列変数を複数行文字列に変換します。
p2で指定された文字列型の１次元配列変数の内容を変換し、p1で指定した変数に代入します。

%href
note2array
arraysave
arrayload



%index
arraysave
文字列型の配列変数をファイルに書き出し
%group
拡張入出力制御命令
%prm
"ファイル名",p1
"ファイル名" : 書き出しを行なうファイル名
p1 : 書き出しを行なう元の変数

%inst
p1で指定した文字列型の１次元配列変数を複数行文字列に変換した上で、指定したファイル名で書き出します。
扱える配列は１次元配列のみになります。
書き出したファイルは、arrayload命令によって読み込むことが可能です。

%href
note2array
array2note
arrayload



%index
arrayload
文字列型の配列変数をファイルから読み込み
%group
拡張入出力制御命令
%prm
"ファイル名",p1
"ファイル名" : 読み込みを行なうファイル名
p1 : 読み込みを行なう先の変数

%inst
arraysave命令によって書き出されたファイルを、p1で指定した変数に読み込みます。
この命令は、ファイルに含まれる複数行文字列の行を配列要素に変換して代入するもので、作成される配列配列は１次元配列になります。


%href
note2array
array2note
arraysave




