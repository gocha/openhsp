;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
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
Cli




%index
alloc
バッファを確保
%group
メモリ管理命令
%prm
p1,p2
p1=変数    : バッファを割り当てる変数名
p2=1〜(64) : バッファのサイズ(Byte単位)

%inst
メモリ上にバッファを作成して変数に割り当てます。
割り当てられた変数は、文字列型となります。
^
この命令は過去のHSP命令との互換を取るために用意されています。
通常は、sdim命令を使用することを推奨します。
^
※この命令は、マクロとしてhspdef.as内で定義されています。

%href
sdim
memexpand
%port+
Let



%index
dim
配列変数を作成
%group
メモリ管理命令
%prm
p1,p2...
p1=変数 : 配列を割り当てる変数名
p2=0〜  : 要素の最大

%inst
任意の要素を持つ配列変数を作成します。
^p
例：
	dim a,20
^p
上の例では、変数aの要素を２０個、つまり「a(0)」〜「a(19)」までをあらかじめ確保します。
^
パラメータを増やすことで多次元配列を作成することも可能です。
^p
例：
dim a,10,5	: 変数aは２次元配列
a(0,0)=1	: 要素(0,0)に1を代入
a(1,0)=2	: 要素(1,0)に2を代入
a(0,1)=3	: 要素(0,1)に3を代入
^p
上の例では、a(0,0)から、a(9,4)までを使用できるようになります。
多次元配列は、４次元まで確保することが可能です。
^
dim命令はスクリプト内のどこででも定義・再定義することが可能です。
また、配列変数を作成すると内容はすべて0にクリアされます。

%href
sdim
ddim
ldim
dimtype
%port+
Let




%index
dimtype
指定タイプの配列変数を作成
%group
メモリ管理命令
%prm
p1,p2,p3...
p1=変数     : 配列を割り当てる変数名
p2=型タイプ : 変数の型タイプ
p3=0〜      : 要素の最大

%inst
任意の要素を持つ配列変数を作成します。
dim命令と同様の動作ですが、dimtypeは変数の型を指定することができます。
p2には、変数型を示す型タイプ値を指定する必要があります。
型タイプ値は、vartype関数で型名文字列から取得することが可能です。
^p
例 ：
	dimtype a,vartype("double"),20
^p
上の例では、実数型変数aの要素を２０個、つまり「a(0)」〜「a(19)」までをあらかじめ確保します。
dim命令と同様に多次元配列を確保することが可能です。
多次元配列は、４次元まで確保することが可能です。

%href
dim
sdim
ddim
ldim
vartype
%port+
Let



%index
poke
バッファに1byte書き込み
%group
メモリ管理命令
%prm
p1,p2,p3
p1=変数 : バッファを割り当てた変数名
p2=0〜  : バッファのインデックス(Byte単位)
p3(0)   : バッファに書き込む値 または 文字列(Byte単位)

%inst
変数に保存されたデータメモリ上の任意の場所にある 1バイトの内容を書き換えます。
^
p1で指定した変数のバッファ上で、p2で指定したインデックスの場所にp3の値を書き込みます。値は0〜255までの1バイト(8bit)値になります。
^
p3に文字列を指定した場合には、文字列データをメモリに展開し、strsizeに、書き込まれた文字列の長さを返します。


%href
wpoke
lpoke
%port+
Let



%index
wpoke
バッファに2byte書き込み
%group
メモリ管理命令
%prm
p1,p2,p3
p1=変数   : バッファを割り当てた変数名
p2=0〜    : バッファのインデックス(Byte単位)
p3=0〜(0) : バッファに書き込む値(16bit整数値)

%inst
変数に保存されたデータメモリ上の任意の場所にある 2バイトの内容を書き換えます。
^
p1で指定した変数のバッファ上で、p2で指定したインデックスの場所にp3の値を書き込みます。値は0〜65535までの2バイト(16bit)値になります。

%href
poke
lpoke
%port+
Let



%index
lpoke
バッファに4byte書き込み
%group
メモリ管理命令
%prm
p1,p2,p3
p1=変数   : バッファを割り当てた変数名
p2=0〜    : バッファのインデックス(Byte単位)
p3=0〜(0) : バッファに書き込む値(32bit整数値)

%inst
変数に保存されたデータメモリ上の任意の場所にある 4バイトの内容を書き換えます。
^
p1で指定した変数のバッファ上で、p2で指定したインデックスの場所にp3の値を書き込みます。値は0〜$ffffffffまでの4バイト(32bit)値になります。

%href
poke
wpoke
%port+
Let




%index
sdim
文字列型配列変数を作成
%group
メモリ管理命令
%prm
p1,p2,p3...
p1=変数 : 配列を割り当てる変数名
p2=1〜  : デフォルト文字数
p3=0〜  : 要素の最大

%inst
文字列型の配列変数を作成します。
dim命令との違いは、  p2のパラメータは「文字列のデフォルト文字数」、p3のパラメータ以降に実際の配列要素の最大数を入れるところです。
^p
例 ：
	sdim a,5000 ; 変数aは5000文字ぶんのメモリをあらかじめ確保します
^p
上の例では、変数aは5000文字ぶんのメモリを確保し配列変数にはなりません。
デフォルト文字数は、あらかじめ確保しておくメモリを指定することで、自動拡張時に余計な処理がかからなくなるというものです。
デフォルト文字数が少ない場合には、長い文字列が代入されるたびに何度も文字列バッファの再確保が発生するため効率が落ちることがあります。
^
多次元配列の場合は、文字数とは別に４次元まで確保することが可能です。
sdim命令はスクリプト内のどこででも定義・再定義することが可能です。
また、配列変数を作成すると内容はすべて0にクリアされます。

%href
dim
ddim
ldim
dimtype
%port+
Let



%index
ddim
実数型配列変数を作成
%group
メモリ管理命令
%prm
p1,p2...
p1=変数 : 配列を割り当てる変数名
p2=0〜  : 要素の最大

%inst
実数型の配列変数を作成します。
パラメーターは、dim命令と同様に要素の最大数を指定します。
^p
例 ：
	ddim a,100 ; 変数aはa(0)〜a(99)までの実数型配列を確保します
^p
dim命令と同様に多次元配列を確保することが可能です。
多次元配列は、４次元まで確保することが可能です。
ddim命令はスクリプト内のどこででも定義・再定義することが可能です。
また、配列変数を作成すると内容はすべて0にクリアされます。
^
※この命令は、マクロとしてhspdef.as内で定義されています。

%href
dim
sdim
ldim
dimtype
%port+
Let



%index
memcpy
メモリブロックのコピー
%group
メモリ管理命令
%prm
p1,p2,p3,p4,p5
p1 : コピー先の変数
p2 : コピー元の変数
p3 : コピーするサイズ(1byte単位)
p4 : コピー先の変数メモリオフセット(省略時=0)
p5 : コピー元の変数メモリオフセット(省略時=0)

%inst
p1で指定された変数に割り当てられているメモリ領域に、
p2で指定された変数に割り当てられているメモリの内容をコピーします。
コピーするサイズ(1byte単位)は、p3で指定します。
大きな領域を変数に割り当てている場合などに高速なメモリコピーを行なうことができます。
p4,p5で、コピー先、コピー元の開始位置を1byte単位で調整することができます。
変数が確保している領域を越える指定がされている場合は、バッファオーバーフローのエラーになります。


%href
memset
memexpand
%port+
Let


%index
memset
メモリブロックのクリア
%group
メモリ管理命令
%prm
p1,p2,p3,p4
p1=変数      : 書き込み先の変数
p2=0〜255(0) : クリアする値(1byte)
p3=0〜(0)    : クリアするサイズ(1byte単位)
p4=0〜(0)    : 書き込み先の変数メモリオフセット

%inst
1byteの固定値でメモリブロックを埋めます。
p1で指定された変数に割り当てられているメモリ領域に、p2で指定された値を、p3のサイズだけ書き込みます。大きな領域に同じ値を書き込みたい時に有効です。p4で、メモリ開始位置を1byte単位で調整することができます。
変数が確保している領域を越える指定がされている場合は、バッファオーバーフローのエラーになります。

%href
memcpy
memexpand
%port+
Let



%index
dup
クローン変数を作成
%group
特殊代入命令
%prm
変数名1 , 変数名2
変数名1 : クローンを作成する変数名
変数名2 : クローン元の変数名

%inst
クローン元の変数が持つメモリを指している変数を作成します。
クローン変数は、クローン元のメモリ情報を参照するための変数として機能するようになります。
^
クローン元の型が変更されたり、配列の拡張、または文字列バッファの拡張が行なわれた場合には、クローンとしての動作は行なわれなくなります。
クローンが有効なのはクローン元の変数に代入が行なわれるまでの間だという点に注意してください。
dup命令は、以前のバージョンとの互換性維持と、 低レベルでの変数バッファ操作を行なうための機能として残されています。
また、メモリアドレスから直接クローン変数を作成するdupptr命令も用意されています。
初心者向けに、dup命令を推奨することはありません。
%href
mref
dupptr
%port+
Let



%index
dupptr
ポインタからクローン変数を作成
%group
特殊代入命令
%prm
変数名,p1,p2,p3
変数名    : クローンを作成する変数名
p1=0〜    : クローン元のメモリアドレス
p2=0〜    : クローン元のメモリサイズ
p3=1〜(4) : クローン変数の型指定

%inst
指定したアドレスポインタを指している変数を作成します。
クローン変数は、メモリ上の情報を参照するための数値型配列変数として機能するようになります。
^
p3で作成されるクローン変数の型を指定することができます。
p3の値は、vartype関数で取得される型を示す値と同じです。 p3を省略した場合は、4(整数型)となります。
^
クローン変数は、指し示しているメモリの位置が変更されてもそれを検知することはできません。
たとえば、変数に格納されているデータのメモリアドレスを指し示していたとしても、変数の型や内容が更新されてメモリ位置が変更された場合に正しく参照することはできません。
あくまでも、一時的なメモリ参照にのみ使用し、取り扱いには十分に注意してください。dupptr命令は、 DLL等の外部関数で取り交わすメモリ参照や低レベルでの変数バッファ操作を行なうための機能として用意されています。
初心者向けに、dupptr命令を推奨することはありません。

%href
mref
dup



%index
mref
特殊なメモリを変数に割り当てる
%group
特殊代入命令
%prm
p1,p2
p1=変数名 : 割り当てられる変数名
p2=0〜(0) : リソースID (割り当てるメモリ内容)

%inst
p1で指定された変数に、p2で指定したメモリ内容を割り当てます。
^p
     値  : 対応するリソース
 --------------------------------------------------
   0〜 7 : ローカルパラメータ#1〜8(数値)
    64   : システム変数stat
    65   : システム変数refstr
    66   : ウィンドウ内画像データ(VRAM)
    67   : 現在のウィンドウ情報(BMSCR構造体)
    68   : HSPのシステム情報(HSPCTX構造体)
    69   : パレット情報
    96〜 : ウィンドウID0〜の情報(BMSCR構造体)
^p
リソースID64,65のシステム変数は、たとえば「mref i,64」とした場合、変数aがシステム変数 statと同等になり、値を代入することができるようになります。これにより、ユーザー定義命令内の計算結果などをシステム変数に反映して、呼び出し元に返すことができます。
^
リソース66のウインドウ内画像データ(VRAMデータ)は、表示されている画像を内容とする配列変数になります。
これにより、 poke,peek命令などで画像データに直接アクセスが可能になります。
^
リソース67以降も同様に HSPの内部データに直接アクセスできるようにするものですが、通常は使う必要はありません。 DLLへ渡すためのパラメータ準備のためなど、ごく限られた用途のために用意されているもので、ほとんどの人は使うことはないはずです。
^
ローカルパラメータは、ユーザー定義命令(#deffunc)で新規に追加された命令のパラメータ内容を取得するためのものです。
パラメータのタイプ(数値、変数、文字列)に従って取得することが可能です。
ローカルパラメータ取得は、HSP2.xまでのパラメーター取得方法との互換のために用意されています。(一部のリソースタイプには互換性がありません。)
HSP3.0以降では、ユーザー定義命令(#deffunc)のエイリアス機能を使用することを推奨しています。
%href
dup
dupptr
#deffunc
%port+
Let
%portinfo
HSPLet時、stat/refstr のみ使用可能です。
関数の引数には使用できませんので、3.0 形式の受け取り方をしてください。 


%index
newmod
モジュール型変数の作成
%group
メモリ管理命令
%prm
p1,p2,p3...
p1    : 変数名
p2    : モジュール名
p3... : 初期化パラメーター

%inst
p1で指定した変数をモジュール型として要素の追加を行ないます。
p1の変数がモジュール型でない場合は、モジュール型として初期化されます。
すでにモジュール型の場合は、配列変数として新しい要素を追加していきます。
p2ですでに登録されているモジュール名を指定し、p3以降に初期化パラメーターを指定することができます。
モジュール変数は、複数の変数やデータをまとめて管理することができる新しいデータ格納方法を提供します。
^p
例 :
	#module a x,y,z
^p
上の例では、aというモジュールにx,y,zという３つの変数を持たせています。
aというモジュールの型を持つ変数は、x,y,zという変数すべてを内包したものになり、モジュール処理命令(#modfunc)で扱うことが可能になります。
^p
例 :
	newmod v,a
^p
上の例では、モジュール「a」のための変数vを初期化します。
これで変数vには、モジュール「a」 が持つモジュール変数x,y,zという内容が丸ごと格納されることになります。
モジュールごとに初期化のための命令(#modinit)を用意している場合は、p3以降のパラメーターが初期化命令に渡されます。
^p
例 :
	#module a x,y,z
	#modinit int p1,int p2,int p3
	x=p1:y=p2:z=p3
	return
	#global
	newmod v,a,1,2,3
^p
モジュール型の変数は、newmod、delmod命令で要素の操作を行なうことができるほか、 foreach命令などとともに複雑なデータを簡潔に処理することができるようになります。


%href
#modfunc
#modinit
#modterm
delmod
foreach



%index
delmod
モジュール型変数の要素削除
%group
メモリ管理命令
%prm
p1
p1 : 変数名

%inst
p1で指定したモジュール型の変数の要素を削除します。
p1は、すでにモジュール型として設定されている変数である必要があります。
^p
例 :
	delmod v.1
^p
delmod命令は、#modterm命令により解放ルーチン(デストラクタ)が定義されている場合は、自動的に呼び出しを行ないます。
モジュール型の変数についての詳細は、newmod命令のヘルプやプログラミングマニュアル(hspprog.htm)を参照してください。


%href
#modterm
newmod



%index
memexpand
メモリブロックの再確保
%group
メモリ管理命令
%prm
p1,p2
p1 = 変数    : 対象となる変数
p2 = 0〜(64) : 再確保サイズ(1byte単位)

%inst
p1で指定された変数が持つメモリ領域の再確保を行ないます。
代入時などのメモリ領域確保はシステムが自動的に行なっていますが、明示的にサイズを変更する場合に使用します。
再確保を行なった場合でも、以前までの内容は保持されます。
p2で、再確保サイズを指定します。p2の値が64より小さい場合は自動的に64に合わせられます。すでに確保されているサイズよりも小さな値を指定した場合は何も行われません。
p1で指定される変数は、 文字列型(str)のように動的にメモリ確保量を変更することが可能な型である必要があります。
再確保ができない型の場合には、エラーになります。

%href
memcpy
memset
alloc



%index
ldim
ラベル型配列変数を作成
%group
メモリ管理命令
%prm
p1,p2...
p1=変数 : 配列を割り当てる変数名
p2=0〜  : 要素の最大

%inst
ラベル型の配列変数を作成します。
パラメーターは、dim命令と同様に要素の最大数を指定します。
^p
例 ：
	ldim a,100 ; 変数aはa(0)〜a(99)までのラベル型配列を確保します
^p
dim命令と同様に多次元配列を確保することが可能です。
多次元配列は、４次元まで確保することが可能です。
ldim命令はスクリプト内のどこででも定義・再定義することが可能です。
また、配列変数を作成すると内容はすべて「未定義」の状態にクリアされます。
^
※この命令は、マクロとしてhspdef.as内で定義されています。

%href
dim
sdim
ddim
dimtype




%index
newlab
ラベル型変数を初期化
%group
メモリ管理命令
%prm
p1,p2
p1=変数    : 初期化する変数名
p2=参照元  : 参照されるラベルまたはオプション

%inst
指定されたラベルが代入されたラベル型の変数を初期化します。
p1で、初期化される変数名を指定します。
p2で、変数に保存されるラベルの参照元を指定します。
p2にラベルを指定した場合は、ラベルが示す場所を参照元とします。
この場合は、「変数=*ラベル名」と記述した場合と変わらない動作となります。
p2に数値を指定した場合は、以下の動作を行ないます。
^
     値  : 参照されるラベル
 --------------------------------------------------
      0    次に実行されるプログラム位置を参照する
      1    次の1ステートをスキップした後に実行されるプログラム位置を参照する
^
p2が1の場合は、newlab命令の後にreturn命令が存在することを前提としています。
「newlab命令、return命令の次にあたる位置」が参照されることになります。
newlab命令は、ラベル型変数を特殊な値により初期化するためのものです。
単純なラベルの保存であれば、通常の代入文を使用する形で構いません。

%href
ldim




