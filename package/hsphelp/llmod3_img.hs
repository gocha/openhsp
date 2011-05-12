;
;	HSP help manager用 HELPソースファイル
;	(先頭が「;」の行はコメントとして処理されます)
;

%type
拡張命令
%ver
3.3
%note
llmod3.hsp,img.hspをインクルードする

%date
2009/08/01
%author
tom
%dll
llmod3
%url
http://www5b.biglobe.ne.jp/~diamond/hsp/hsp2file.htm


%index
draw_icon
アイコンの描画
%group
拡張入出力制御命令
%prm
n1,n2,n3,n4
n1 : 描画するアイコン(get_iconで取得したもの)
n2 : x座標
n3 : y座標
n4 : redrawしないかどうかのフラグ

%inst
n1で指定したアイコンを座標(x,y)に描画します。
この命令を使うたびにredrawを行います。複数のアイコンを描画するときは効率が悪いのでn4を1にして、全てのアイコンを書き終えたらredrawを実行してください。

%href
get_icon
get_fileicon



%index
get_fileicon
ファイルに使用されているアイコンの取得
%group
拡張入出力制御命令
%prm
v1,"s2",n3
v1 : 取得したアイコンを入れる変数
s2 : ファイル名
n3 : 取得するもの

%inst
s2に指定したファイルに使われるアイコンを取得します。
^
^p
n3の値
0       s2のファイルに使われているアイコン
1       s2のファイルに使われている小さいアイコン
2       ツリービューで選択されているときのアイコン(s2がフォルダなどの場合)
4       リストビューで選択されている状態のアイコン
8       アイコンにリンクのマークを付ける
$10     s2のファイルに使われるアイコンが含まれているファイル名
$20     s2のファイルが表示されるときに使われる名前(s2に"B:\\"などを使ったとき)
$40     s2のファイルの種類
^
0,1,2,4,8は組み合わせて使うことができます。

%href
get_icon
draw_icon



%index
get_icon
アイコンの取得
%group
拡張入出力制御命令
%prm
v1,"s2",n3,n4
v1 : 取得したアイコンを入れる数値変数
s2 : アイコンを含むファイル名
n3 : アイコンの番号
n4 : 小さいアイコンを取得するかどうかのフラグ

%inst
s2に指定したファイルから、n3番目のアイコンを取得します。
もしn3番目のアイコンが小さいアイコンをもっているときはn4を1にすると小さいアイコンの方を取得します。
取得したアイコンはdraw_iconで描画できます。
アイコン取得に失敗したときは変数に0が代入されます。
^
n3を-1にすると、s2がもっているアイコンの数がstatに代入されます。
n3を-2にすると、s2がもっているアイコン全てを取得します。ただしファイルs2が16個以上のアイコンを持っているときは、変数v1を
	alloc v1,'アイコンの数'×4
として拡張しておかないとエラーになります。

%href
draw_icon
get_fileicon



