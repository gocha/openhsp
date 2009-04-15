#include "hspogg.as"

	mes "HSPOGG Sound Test"
	mes "---------------------------"
	mes "Music 'Matchbox parking'"
	mes "作曲:onitama 編曲:arStudio"
	mes "---------------------------"

	dmmini

	dmmload "se_break.wav",0	; wavファイル読み込み
	dmmload dir_exe+"\\sample\\demo\\oot06.ogg",1		; oggファイル読み込み
	dmmloop 1,671328		; ループポイント設定

	button "WAV",*aaa
	button "OGG",*bbb
	button "STOP",*ccc
	button "END",*bye

	dmmplay 0			; 再生

*www
	dmmstat a,0,16			; 再生フラグを取得
	dmmstat dd,1,$100		; 再生フラグを取得
	title "PLAYING="+a+"/"+dd
	await 20
	goto *www

*aaa
	dmmplay 0			; 再生
	goto *www
*bbb
	dmmplay 1			; 再生
	dmmstat dd,1,$101		; 再生フラグを取得
	mes "Total:"+dd
	goto *www

*ccc
	dmmstop -1			; 停止
	goto *www
*bye
	dmmbye
	end
