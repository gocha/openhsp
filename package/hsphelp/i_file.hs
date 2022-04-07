;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
;

%type
内蔵命令
%ver
3.7
%note
ver3.7標準命令

%date
2022/04/07
%author
onitama
%url
http://hsp.tv/
%port
Win
Cli


%index
bcopy
ファイルのコピー
%group
ファイル操作命令
%prm
"filename1","filename2"
"filename1" : コピー元ファイル名
"filename2" : コピー先ファイル名

%inst
"filename1"のファイルを"filename2"というファイル名にコピーします。

%href
bload
bsave




%index
chdir
ディレクトリ移動
%group
ファイル操作命令
%prm
"dirname"
"dirname" : 移動先ディレクトリ名

%inst
"dirname"で指定した名前のディレクトリに移動します。
指定したディレクトリが存在しないか、 書式が間違っている場合はエラー12(「ファイルが見つからないか無効な名前です」)となります。
カレントディレクトリは、システム変数dir_curで参照することができます。
%href
dir_cur
%port+
Let



%index
delete
ファイル削除
%group
ファイル操作命令
%prm
"filename"
"filename" : 削除するファイル名

%inst
"filename"で指定したファイルを削除します。
指定したファイルが存在しないか、書式が間違っている場合はエラー12(「ファイルが見つからないか無効な名前です」)となります。
delete命令を実行する前に exist命令でファイルの有無を確認するようにしてください。



%index
dirlist
ディレクトリ一覧を取得
%group
ファイル操作命令
%prm
p1,"filemask",p2
p1=変数    : ディレクトリ一覧を格納する文字列型変数
"filemask" : 一覧のためのファイルマスク
p2=0〜(0)  : ディレクトリ取得モード

%inst
カレントディレクトリのファイル一覧を作成して、変数に代入します。
"filemask"で、一覧を作成するためのファイルマスクを指定します。
ファイルマスクは、「*.*」 のようなワイルドカードの形で指定するパラメータです。
たとえば、「*.as」というファイルマスクではasという拡張子を持つファイルすべての一覧を作成します。カレントディレクトリにあるすべてのファイル一覧を作成する場合は、「*.*」になります。
ディレクトリ一覧は、p1で指定された文字列型の変数に、１ファイルごとに改行(\n)で区切られた文字列として代入されます。このデータは、メモリノートパッド命令で扱うことができる形式です。
^
dirlist命令が実行されると、 システム変数statに一覧が作成されたファイルの数が代入されます。
ファイルが１つもない場合は、システム変数statに0が代入されます。
p2のモードを指定することによって、取得するファイルの種類を選ぶことができます。モード値の詳細は以下の通りです。 
モードが省略されている場合は0になります。
^p
  モード :  取得される内容
 ---------------------------------------------------------------------
     0   :  すべてのファイル
     1   :  ディレクトリを除くすべてのファイル
     2   :  隠し属性・システム属性を除くすべてのファイル
     3   :  ディレクトリ・隠し属性・システム属性以外のすべてのファイル
     5   :  ディレクトリのみ
     6   :  隠し属性・システム属性ファイルのみ
     7   :  ディレクトリと隠し属性・システム属性ファイルのみ
^p

%sample
sdim a,64
dirlist a,"*.*"  ; カレントディレクトリの取得
mes a            ; 内容の表示
stop
%href
dirlist2




%index
exist
ファイルのサイズ取得
%group
ファイル操作命令
%prm
"filename"
"filename" : サイズを調べるファイルの名前

%inst
"filename"で指定したファイルが存在するかをチェックして、そのファイルサイズを取得します。exist命令が実行されると、システム変数strsizeに結果が反映されます。
^
ファイルが存在する場合は、そのファイルサイズがstrsizeに代入されます。
もしファイルが存在しなかった場合は、-1がstrsizeに代入されます。
%port+
Let




%index
mkdir
ディレクトリ作成
%group
ファイル操作命令
%prm
"dirname"
"dirname" : 作成するディレクトリ名

%inst
"dirname"で指定した名前でディレクトリを作成します。
ディレクトリは１階層先までしか作成することができません。
作成中にエラーが発生した場合はエラー12(「ファイルが見つからないか無効な名前です」)となります。
mkdir命令を実行する前に 必ずdirlist命令でフォルダの有無を確認するようにしてください。




%index
bload
バッファにファイルをロード
%group
ファイル操作命令
%prm
"filename",p1,p2,p3
"filename" : ロードするファイル名
p1=変数    : 変数名
p2=64〜(-1): ロードされるサイズ(Byte単位)
p3=0〜(-1) : ファイルのオフセット

%inst
ファイルの内容をメモリバッファに読み込みます。
通常は、sdim命令で確保したメモリバッファに対して使用しますが、それ以外の型を持つ変数や、配列変数に対して使うこともできます。
p2のバッファサイズを省略するかマイナス値を指定すると、自動的に変数バッファのサイズが設定されます。
^
また、bload命令実行後は、システム変数strsizeに読み込んだデータのサイズが反映されます。
^
ファイルのオフセット値を指定すると、その値だけファイルの先頭からずらした場所からが操作の対象になります。 たとえば、bload命令でオフセット値を100に指定すると、 通常はファイルの先頭からデータをメモリに読み込むところを、先頭から100バイト過ぎた場所 (100バイトスキップして) からメモリに読み込まれます。
^
これにより、大きなファイルの一部だけを読み込むことや、分割して処理することなどが可能になります。
^
テキストファイルを読み込む場合には、専用のnoteload命令を使用することを推奨します。
^
#epack命令により暗号化されたファイルをbload命令で読み込む場合は、ファイルのオフセット値を指定することができませんので注意してください。

%href
noteload
bcopy
bsave
%port+
Let




%index
bsave
バッファをファイルにセーブ
%group
ファイル操作命令
%prm
"filename",p1,p2,p3
"filename" : セーブするファイル名
p1=変数    : 変数名
p2=0〜(-1) : セーブするサイズ(Byte単位)
p3=0〜(-1) : ファイルのオフセット
%inst
メモリバッファの内容をファイルに書き出します。
通常は、sdim命令で確保したメモリバッファに対して使用しますが、それ以外の型を持つ変数や、配列変数に対して使うこともできます。
p2のバッファサイズを省略するかマイナス値を指定すると、自動的に変数バッファのサイズが設定されます。
^
ファイルのオフセット値を指定すると、その値だけファイルの先頭からずらした場所からが操作の対象になります。
bsave命令でオフセットを指定すると、 ファイルの先頭から任意のサイズを過ぎた場所からセーブを行なうことが可能です。
(この場合は、それオフセットより前のファイル内容は変化しません。
また、オフセット指定時はファイルが存在しない場合エラーとなります。)
^
これにより、大きなファイルの一部だけを更新することや、分割して処理することなどが可能になります。
^
テキストファイルを保存する場合には、専用のnotesave命令を使用することを推奨します。

%href
notesave
bcopy
bload


%index
memfile
メモリストリーム設定
%group
ファイル操作命令
%prm
p1,p2,p3
p1=変数     : ストリーム対象となる変数名
p2=0〜(0)   : バッファのオフセット
p3=0〜(MAX) : バッファのサイズ
%inst
ファイルの替わりとして扱うメモリ空間を持った変数を設定します。(メモリストリーム機能)
p1で指定された変数は、これ以降に「MEM:ファイル名」で指定されたファイルの読み出し元となります。
p2で、オフセット(読み出す際の先頭位置)を指定します。 0が指定されるか省略された場合は、バッファの先頭から読み出されます。
p3で、読み出す対象となるサイズを指定します。 0が指定されるか、省略された場合は、変数のバッファ全体が対象となります。
メモリ上にロードされたファイルイメージを、「picload "MEM:a.jpg"」のように指定して画像ファイルを読み込むことが可能です。
mmload命令など拡張子をファイル種別として判断している場合には、ダミーのファイル名 (「MEM:a.wav」など)を指定する必要があるので注意してください。
^
メモリストリーム機能は、独自形式のアーカイブや暗号形式を用意してその内容を読み出して画像として展開する場合など、
特殊な場面でのみ使われることを想定したものです。
外部DLLや、拡張プラグインに渡すファイル名に関しては、メモリストリーム機能は原則として適用されませんので注意してください。
(HSP3のメモリストリーム機能に対応した拡張プラグインは除きます)

%href
bload
picload
%port+
Let



%index
chdpm
DPMファイル設定
%group
ファイル操作命令
%prm
"dpmname",p1,p2
"dpmname" : DPMファイル名
p1(-1)    : 暗号化キー指定
p2(-1)    : スロット番号(0〜15)

%inst
読み込み対象となるDPMファイル(パックされた埋め込みファイル)を設定します。
chdpm命令が実行されると、以降は"dpmname"で指定したファイルを、DPM形式でパックされたデータとして扱います。
DPMファイルの初期化中にエラーが発生した場合は、エラー12(「ファイルが見つからないか無効な名前です」)となります。
^
スロット番号は、DPMファイルを読み込む先の番号になります。0から15までの値を指定可能です。マイナス値を指定した場合は、自動的に新しいスロット番号が割り当てられます。
chdpm命令により、複数のDPM形式ファイルを同時に参照して読み込み対象とさせることが可能です。
exeファイルに埋め込まれたファイルはスロット番号0となります。
DPMファイル名に空の文字列("")を指定した場合は、指定されたスロット番号は読み込み対象から破棄します。
^
DPMファイルごとに異なる暗号化を行なうことで、より強力なファイル保護を行なうことも可能です。
その場合、暗号化キーを指定したDPMファイルは、スクリプトから直接生成する必要があります。詳しくは、サンプルスクリプト「mkpack.hsp」を参照してください。


