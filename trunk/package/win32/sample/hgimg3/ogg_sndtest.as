#include "hspogg.as"

	mes "HSPOGG Sound Test"
	mes "---------------------------"
	mes "Music 'Matchbox parking'"
	mes "���:onitama �ҋ�:arStudio"
	mes "---------------------------"

	dmmini

	dmmload "se_break.wav",0	; wav�t�@�C���ǂݍ���
	dmmload dir_exe+"\\sample\\demo\\oot06.ogg",1		; ogg�t�@�C���ǂݍ���
	dmmloop 1,671328		; ���[�v�|�C���g�ݒ�

	button "WAV",*aaa
	button "OGG",*bbb
	button "STOP",*ccc
	button "END",*bye

	dmmplay 0			; �Đ�

*www
	dmmstat a,0,16			; �Đ��t���O���擾
	dmmstat dd,1,$100		; �Đ��t���O���擾
	title "PLAYING="+a+"/"+dd
	await 20
	goto *www

*aaa
	dmmplay 0			; �Đ�
	goto *www
*bbb
	dmmplay 1			; �Đ�
	dmmstat dd,1,$101		; �Đ��t���O���擾
	mes "Total:"+dd
	goto *www

*ccc
	dmmstop -1			; ��~
	goto *www
*bye
	dmmbye
	end