;
;	HSP help manager�p HELP�\�[�X�t�@�C��
;	(�擪��;�̍s�̓R�����g�Ƃ��ď�������܂�)
;

%type
�����֐�
%ver
3.1
%note
ver3.1�W���֐�
%date
2004/10/12
%author
onitama
%url
http://www.onionsoft.net/
%port
Win
Cli
Let




%index
int
�����l�ɕϊ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �ϊ����̒l�܂��͕ϐ�

%inst
p1�Ŏw�肳�ꂽ�l�𐮐��ɂ������̂�Ԃ��܂��B
�l�������̏ꍇ�́A�����_�ȉ����؂�̂Ă��܂��B
�l��������̏ꍇ�́A���l������̏ꍇ�͂��̐��l�ɁA ����ȊO��0�ɂȂ�܂��B

%href
str
double



%index
rnd
�����𔭐�
%group
��{���o�͊֐�
%prm
(p1)
p1=1�`32768 : �����͈̔�

%inst
0����(p1-1)�͈̔͂Ő����̗����l�𔭐������܂��B
p1�̒l�͔͈͂Ɋ܂܂�܂���B���Ƃ��΁A
^p
�� �F
    a=rnd(10)
^p
�́A�ϐ�a�ɁA0�`9�܂ł̗����������܂��B
rnd�֐��́A�v���O�����N�����Ă���͈��̃p�^�[���ŗ����𔭐������܂��B
�����̃p�^�[�������łȂ����̂ɂ���ꍇ�́A randomize���߂��g�p���Ă��������B

%href
randomize



%index
strlen
������̒����𒲂ׂ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : ������̒����𒲂ׂ��������񂩂܂��͕�����^�̕ϐ���

%inst
p1�Ŏw�肳�ꂽ������܂��́A������^�ϐ��������Ă��镶����̒�����Ԃ��܂��B
�����񂪓��{��̑S�p�������ꍇ�́A�P�����ł��Q�������Ɍv�Z����܂��B
%href




%index
length
�z��̗v�f����Ԃ�(1����)
%group
��{���o�͊֐�
%prm
(p1)
p1 : �z��𒲂ׂ�ϐ�

%inst
p1�Ŏw�肳�ꂽ�ϐ������z��v�f��(1����)��Ԃ��܂��B
�z��v�f�����T�������ꍇ�́Ap1(0)�`p1(4)�����݂��邱�ƂɂȂ�܂��B

%href
length2
length3
length4



%index
length2
�z��̗v�f����Ԃ�(2����)
%group
��{���o�͊֐�
%prm
(p1)
p1 : �z��𒲂ׂ�ϐ�

%inst
p1�Ŏw�肳�ꂽ�ϐ������z��v�f��(2����)��Ԃ��܂��B
�z��v�f�����T�������ꍇ�́Ap1(0,0)�`p1(?,4)�����݂��邱�ƂɂȂ�܂��B
�z��̎��������݂��Ȃ��ꍇ�́A0���Ԃ�܂��B

%href
length
length3
length4



%index
length3
�z��̗v�f����Ԃ�(3����)
%group
��{���o�͊֐�
%prm
(p1)
p1 : �z��𒲂ׂ�ϐ�

%inst
p1�Ŏw�肳�ꂽ�ϐ������z��v�f��(3����)��Ԃ��܂��B
�z��v�f�����T�������ꍇ�́Ap1(0,0,0)�`p1(?,?,4)�����݂��邱�ƂɂȂ�܂��B�z��̎��������݂��Ȃ��ꍇ�́A0���Ԃ�܂��B

%href
length
length2
length4



%index
length4
�z��̗v�f����Ԃ�(4����)
%group
��{���o�͊֐�
%prm
(p1)
p1 : �z��𒲂ׂ�ϐ�

%inst
p1�Ŏw�肳�ꂽ�ϐ������z��v�f��(4����)��Ԃ��܂��B
�z��v�f�����T�������ꍇ�́Ap1(0,0,0,0)�`p1(?,?,?,4)�����݂��邱�ƂɂȂ�܂��B�z��̎��������݂��Ȃ��ꍇ�́A0���Ԃ�܂��B

%href
length
length2
length3



%index
vartype
�ϐ��̌^��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �^�𒲂ׂ�ϐ��A�܂��͕�����

%inst
p1�Ŏw�肳�ꂽ�ϐ����i�[���Ă���l�̌^�𒲂ׂĕԂ��܂��B
�Ԃ����l�́A�^�����������l�ƂȂ�܂��B�^�̒l�́A�ȉ��̒ʂ�ł��B
^p
 1 : ���x���^
 2 : ������^
 3 : �����^
 4 : �����^
 5 : ���W���[���^
 6 : COM�I�u�W�F�N�g�^
^p
�v���O�C�����Ō^���g������Ă���ꍇ�́A����ȊO�̒l���Ԃ���܂��B
�܂��Ap1�ɕ�������w�肵���ꍇ�ɂ́A�^�������^���Ƃ��Ĉ����܂��B
�^���́A�o�^����Ă�����̂Ƒ啶�����������܂߂Ċ��S�Ɉ�v������K�v������܂��B
^p
"int"    : �����^
"str"    : ������^
"double" : �����^
^p
�W���I�Ȍ^���Ƃ��āA�g�p�ł����������͏�̒ʂ�ł��B�������A����ȊO�ɂ��v���O�C�����Ō^���g������Ă���ꍇ�́A�w��ł���^�����ǉ�����܂��B


%href
varptr



%index
varptr
�ϐ��f�[�^�̃|�C���^��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �|�C���^�𒲂ׂ�ϐ��A�܂��͖���

%inst
p1�Ŏw�肳�ꂽ�ϐ����i�[���Ă���f�[�^�����郁�����A�h���X��Ԃ��܂��B
p1�ɊO���g������(#func�Œ�`����Ă���DLL�Ăяo���p�̖���)���w�肵���ꍇ�ɂ́A���ۂɎ��s�����O���֐��̃A�h���X��Ԃ��܂��B
���̊֐��́A �O��DLL�Ƀ|�C���^��n���������ȂǓ���ȏꍇ�Ɏg�p������̂ŁA�ʏ�͊o���Ă����K�v�̂Ȃ����̂ł��B
varptr�ɂ���Ď擾�����|�C���^�́A�z��̊g������e�̍X�V�Ȃǂɂ��ω�����\�������邽�߁A�l���Q�Ƃ��钼�O�Ŏg�p����悤�ɂ��Ă��������B

%href
vartype
libptr
%port-
Let


%index
gettime
���ԁE���t���擾����
%group
��{���o�͊֐�
%prm
(p1)
p1=0�`7(0) : �擾����^�C�v

%inst
p1�Ŏw�肵���^�C�v�̓��t�E��������Ԃ��܂��B
�擾����^�C�v�͈ȉ��̒ʂ�ł��B

^p
    0 : �N(Year)
    1 : ��(Month)
    2 : �j��(DayOfWeek)
    3 : ��(Day)
    4 : ��(Hour)
    5 : ��(Minute)
    6 : �b(Second)
    7 : �~���b(Milliseconds)
^p
���Ƃ��΁A

^p
�� �F
    a=gettime(4)   ; ���܉���?
^p
�́A�ϐ�a�Ɍ��ݎ������������������܂��B

%href




%index
str
������ɕϊ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �ϊ����̒l�܂��͕ϐ�

%inst
p1�Ŏw�肳�ꂽ�l�𕶎���ɂ������̂�Ԃ��܂��B

%href
int
double



%index
dirinfo
�f�B���N�g�����̎擾
%group
��{���o�͊֐�
%prm
(p1)
p1=0�`4 : �擾����^�C�v

%inst
p1�Ŏw�肵���^�C�v�̃f�B���N�g������Ԃ��܂��B
�擾����^�C�v�͈ȉ��̒ʂ�ł��B
^p
    0 : �J�����g(���݂�)�f�B���N�g��
    1 : HSP�̎��s�t�@�C��������f�B���N�g��
    2 : Windows�f�B���N�g��
    3 : Windows�̃V�X�e���f�B���N�g��
    4 : �R�}���h���C��������
^p
p1���ȗ����邱�Ƃ͂ł��܂���B
�܂��Ap1��0x10000�ȏ�̒l���w�肵���ꍇ�́A�r�b�g0�`15�܂ł�CSIDL�l�Ƃ��ē���t�H���_�̎擾���s�Ȃ��܂��B
����ɂ��A�f�X�N�g�b�v(0x10000)��}�C�h�L�������g(0x10005)���̃V�X�e�����Ǘ����Ă���قƂ�ǂ̃t�H���_���擾���邱�Ƃ��ł��܂��B

%href



%index
double
�����l�ɕϊ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �ϊ����̒l�܂��͕ϐ�

%inst
p1�Ŏw�肳�ꂽ�l�������ɂ������̂�Ԃ��܂��B
�l��������̏ꍇ�́A���l������̏ꍇ�͂��̐��l�ɁA ����ȊO��0�ɂȂ�܂��B

%href
int
str



%index
sin
�T�C���l��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=(0.0) : �p�x�l(���W�A��)

%inst
p1�̃T�C��(����)�l�������ŕԂ��܂��B
p1�Ŏw�肷��P�ʂ̓��W�A��(2�΂�360�x)�ɂȂ�܂��B
%href
cos
tan
atan


%index
cos
�R�T�C���l��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=(0.0) : �p�x�l(���W�A��)

%inst
p1�̃R�T�C��(�]��)�l�������ŕԂ��܂��B
p1�Ŏw�肷��P�ʂ̓��W�A��(2�΂�360�x)�ɂȂ�܂��B
%href
sin
tan
atan


%index
tan
�^���W�F���g�l��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=(0.0) : �p�x�l(���W�A��)

%inst
p1�̃^���W�F���g(����)�l�������ŕԂ��܂��B
p1�Ŏw�肷��P�ʂ̓��W�A��(2�΂�360�x)�ɂȂ�܂��B
%href
sin
cos
atan


%index
atan
�A�[�N�^���W�F���g�l��Ԃ�
%group
��{���o�͊֐�
%prm
(p1,p2)
p1      : Y�l
p2(1.0) : X�l

%inst
p1��Y�Ap2��X�̒l�Ƃ��āA Y/X�̊p�x(�A�[�N�^���W�F���g�l)�������̃��W�A���P��(2�΂�360�x)�ŕԂ��܂��B
p2���ȗ������ꍇ��1.0���g�p����܂��B�܂��Ap2��0�̏ꍇ��0.5��(90�x)���Ԃ���܂��B

%href
sin
cos
tan


%index
sqrt
���[�g�l��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=0.0�`(0.0) : ���[�g�����߂�l

%inst
p1�̃��[�g(������)�l���A�����ŕԂ��܂��B
p1�Ƀ}�C�i�X�l���w�肷�邱�Ƃ͂ł��܂���B
%href



%index
sysinfo
�V�X�e�����̎擾
%group
��{���o�͊֐�
%prm
(p1)
p1=0�` : �擾����^�C�v

%inst
p1�Ŏw�肵���^�C�v�̃V�X�e�����l��Ԃ��܂��B
�擾�ł���^�C�v�͈ȉ��̒ʂ�ł��B
^p
  0 : ������ OS���ƃo�[�W�����ԍ�
  1 : ������ ���O�C�����̃��[�U�[��
  2 : ������ �l�b�g���[�N��̃R���s���[�^��
 16 : ���l �g�p���Ă���CPU�̎��(�R�[�h)
 33 : ���l �����������T�C�Y�̎g�p��(�P��%)
 34 : ���l �S�̂̕����������T�C�Y
 35 : ���l �󂫕����������T�C�Y
 36 : ���l �X���b�v�t�@�C���̃g�[�^���T�C�Y
 37 : ���l �X���b�v�t�@�C���̋󂫃T�C�Y
 38 : ���l ���z���������܂߂��S�������T�C�Y
 39 : ���l ���z���������܂߂��󂫃������T�C�Y
^p

%href



%index
peek
�o�b�t�@����1byte�ǂݏo��
%group
�������Ǘ��֐�
%prm
(p1,p2)
p1=�ϐ� : ���e��ǂݏo�����̕ϐ���
p2=0�`  : �o�b�t�@�̃C���f�b�N�X(Byte�P��)

%inst
�ϐ��ɕۑ����ꂽ�f�[�^��������̔C�ӂ̏ꏊ�ɂ���1�o�C�g(8bit)�̓��e�𐔒l�Ƃ��ĕԂ��܂��B
�֐��̖߂�l�́A0�`255�܂ł̐����l�ɂȂ�܂��B

%href
wpeek
lpeek



%index
wpeek
�o�b�t�@����2byte�ǂݏo��
%group
�������Ǘ��֐�
%prm
(p1,p2)
p1=�ϐ� : ���e��ǂݏo�����̕ϐ���
p2=0�`  : �o�b�t�@�̃C���f�b�N�X(Byte�P��)

%inst
�ϐ��ɕۑ����ꂽ�f�[�^��������̔C�ӂ̏ꏊ�ɂ���2�o�C�g(16bit)�̓��e�𐔒l�Ƃ��ĕԂ��܂��B
�֐��̖߂�l�́A0�`65535�܂ł̐����l�ɂȂ�܂��B

%href
peek
lpeek



%index
lpeek
�o�b�t�@����4byte�ǂݏo��
%group
�������Ǘ��֐�
%prm
(p1,p2)
p1=�ϐ� : ���e��ǂݏo�����̕ϐ���
p2=0�`  : �o�b�t�@�̃C���f�b�N�X(Byte�P��)

%inst
�ϐ��ɕۑ����ꂽ�f�[�^��������̔C�ӂ̏ꏊ�ɂ���4�o�C�g(32bit)�̓��e�𐔒l�Ƃ��ĕԂ��܂��B
�֐��̖߂�l�́A0�`$ffffffff�܂ł̐����l�ɂȂ�܂��B

%href
peek
wpeek



%index
callfunc
�O���֐��̌Ăяo��
%group
��{���o�͊֐�
%prm
(p1,p2,p3)
p1 : �p�����[�^�[���i�[����Ă���z��ϐ�
p2 : �֐��A�h���X
p3 : �p�����[�^�[��

%inst
p2�Ŏw�肳��Ă���A�h���X���l�C�e�B�u�Ȋ֐��Ƃ��ČĂяo���܂��B
�Ăяo���̈����Ƃ��āAp1�Ŏw�肳�ꂽ���l�^�z��ϐ��Ɋi�[����Ă���l���g�p���܂��Bp3�Ńp�����[�^�[�����w�肷�邱�Ƃ��ł��܂��B
^p
�� :
	a.0=1
	a.1=2
	a.2=3
	res = callfunc( a, proc, 3 )
^p
��̗�ł́Aproc�������A�h���X�̊֐���(1,2,3)�Ƃ��������ŌĂяo���܂��B
�Ăяo�����֐��̖߂�l���A���̂܂�callfunc�̖߂�l�ƂȂ�܂��B
���̊֐��́A���O�Ŋ֐��A�h���X��p�ӂ��ČĂяo������ȏ󋵂Ɏg�p������̂ł��B
�ʏ�͎g�p����K�v������܂���B�܂��A�O���֐��Ăяo���Ɏ��s�����ꍇ�ɂ́A�t���[�Y��\�����Ȃ����ʂ��N����ꍇ������̂ŁA�\���ɒ��ӂ��Ďg�p����悤�ɂ��Ă��������B

%href
#uselib
#func



%index
absf
�����̐�Βl��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : ��Βl�ɕϊ���������l

%inst
p1�̐�Βl�������ŕԂ��܂��B
�����̐�Βl���K�v�ȏꍇ�́Aabs�֐����g�p���Ă��������B
%href
abs

%index
abs
�����̐�Βl��Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : ��Βl�ɕϊ����鐮���l

%inst
p1�̐�Βl�𐮐��ŕԂ��܂��B
�����̐�Βl���K�v�ȏꍇ�́Aabsf�֐����g�p���Ă��������B
%href
absf


%index
logf
�ΐ���Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=0.0�`(0.0) : �ΐ������߂�l

%inst
p1�̑ΐ�(log)�l���A�����ŕԂ��܂��B
p1��0���w�肵���ꍇ�͖�����(INF)��Ԃ��܂��B
%href
expf



%index
expf
�w����Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1=0.0�`(0.0) : �w�������߂�l

%inst
p1�̎w��(exp)�l���A�����ŕԂ��܂��B
�I�[�o�[�t���[�����ꍇ�͖���(INF)��Ԃ��A�A���_�[�t���[�����ꍇ��0��Ԃ��܂��B
%href
logf



%index
limit
���͈͓��̐�����Ԃ�
%group
��{���o�͊֐�
%prm
(p1,p2,p3)
p1 : �ΏۂƂȂ�l
p2 : �ŏ��l
p3 : �ő�l

%inst
p1�Ɏw�肵���l���Ap2�`p3�͈͓̔��Ɏ��܂鐮���ɕϊ��������̂�Ԃ��܂��B
p1�̒l��p2�����������ꍇ�́Ap2�̒l���Ԃ���Ap1�̒l��p3�����傫���ꍇ�ɂ�p3�̒l���Ԃ���܂��B
����ɂ��Alimit�֐����Ԃ��l�́A�K��p2�`p3�͈͓̔��ƂȂ�܂��B
�����͈̔͂����߂�ꍇ�ɂ́Alimitf�֐����g�p���Ă��������B

%href
limitf



%index
limitf
���͈͓��̎�����Ԃ�
%group
��{���o�͊֐�
%prm
(p1,p2,p3)
p1= : �ΏۂƂȂ�l
p2= : �ŏ��l
p3= : �ő�l

%inst
p1�Ɏw�肵���l���Ap2�`p3�͈͓̔��Ɏ��܂�����ɕϊ��������̂�Ԃ��܂��B
p1�̒l��p2�����������ꍇ�́Ap2�̒l���Ԃ���Ap1�̒l��p3�����傫���ꍇ�ɂ�p3�̒l���Ԃ���܂��B
����ɂ��Alimitf�֐����Ԃ��l�́A�K��p2�`p3�͈͓̔��ƂȂ�܂��B
�����͈̔͂����߂�ꍇ�ɂ́Alimit�֐����g�p���Ă��������B

%href
limit



%index
varuse
�ϐ��̎g�p�󋵂�Ԃ�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �g�p�󋵂𒲂ׂ�ϐ�

%inst
p1�Ɏw�肵���ϐ��̎g�p�󋵂�Ԃ��܂��B
varuse�́A���W���[���^��COM�I�u�W�F�N�g�^�̕ϐ��ȂǁA ���Ԃ������Ȃ��󋵂���������ꍇ�ɂ̂ݗL���ł��B
�w�肳�ꂽ�ϐ����L���ł����1���A�����łȂ����0��Ԃ��܂��B
���W���[���^�ϐ��ł���΁A�������ς݂��ǂ����𒲂ׂ邱�Ƃ��ł��܂��B
COM�I�u�W�F�N�g�^�ł���΁A�L����COM�I�u�W�F�N�g��ێ����Ă��邩�𒲂ׂ��܂��B

%href
newmod
delmod
%port-
Let




%index
libptr
�O���ďo���R�}���h�̏��A�h���X�𓾂�
%group
��{���o�͊֐�
%prm
(p1)
p1 : �A�h���X�𒲂ׂ�R�}���h

%inst
p1�Ɏw�肵���R�}���h�̏��A�h���X���擾���Đ����l�Ƃ��ĕԂ��܂��B
�O��DLL�Ăяo���R�}���h��֐����p�����[�^�[�Ƃ��Ďw�肷�邱�ƂŁA�R�}���h�Ɋւ����񂪊i�[����Ă���STRUCTDAT�\���̂̃A�h���X���擾���邱�Ƃ��ł��܂��B
STRUCTDAT�\���̂́AHSPSDK���ňȉ��̂悤�ɒ�`����Ă��܂��B
^p
	typedef struct STRUCTDAT {
	short	index;           // base LIBDAT index
	short	subid;           // struct index
	int	prmindex;            // STRUCTPRM index(MINFO)
	int	prmmax;              // number of STRUCTPRM
	int	nameidx;             // name index (DS)
	int	size;                // struct size (stack)
	int	otindex;             // OT index(Module)  / cleanup flag(Dll)
	union {
		void	*proc;       // proc address
		int	funcflag;        // function flags(Module)
	};
	} STRUCTDAT;
^p
p1��COM�Ăяo���R�}���h�⃆�[�U�[��`���߁A ���[�U�[��`�֐����w�肵���ꍇ�����l��STRUCTDAT�\���̂̃A�h���X���擾����܂��B
libptr�֐��́AHSP���g�p���Ă�������f�[�^�ւ̃A�N�Z�X��⏕������̂ŁA�����ň������̓��e�ɂ��ď\���Ȓm������������Ŏg�p����悤�ɂ��Ă��������B
�ʏ�̎g�p�͈͂ł́A���̊֐��𗘗p������o���Ă����K�v�͂���܂���B
^
STRUCTDAT�\���̂��Q�Ƃ��邱�ƂŁA �O���ďo��DLL�̃A�h���X��ADLL�n���h
���Ȃǂ̏��𓾂邱�Ƃ��\�ł��B

%href
varptr
%sample
	#uselib "user32.dll"
	#func MessageBoxA "MessageBoxA" int,sptr,sptr,int

	ladr=libptr( MessageBoxA )
	dupptr lptr,ladr,28	; STRUCTDAT�\���̂��擾
	lib_id=wpeek(lptr,0)
	mes "LIB#"+lib_id
	mref hspctx,68
	linf_adr=lpeek( hspctx, 832 )
	dupptr linf,linf_adr + lib_id*16,16	; LIBDAT�\���̂��擾
	dll_flag = linf(0)
	dll_name = linf(1)
	dll_handle = linf(2)
	mes "FLAG("+dll_flag+") NAME_ID#"+dll_name
	mes "HANDLE="+strf("%x",dll_handle)
	stop
%port-
Let



%index
comevdisp
COM�C�x���g�̓��e���m�F
%group
COM�I�u�W�F�N�g����֐�
%prm
(p1)
p1      : �ϐ���

%inst
p1�Ŏw�肳�ꂽ�ϐ�(COM�I�u�W�F�N�g�^)�̃C�x���g�T�u���[�`�����ŁA�C�x���g�̃f�B�X�p�b�`ID(DISPID)���擾���܂��B
p1�Ŏw�肳�ꂽ�ϐ��́Acomevent���߂ɂ�菉��������Ă���K�v������܂��B
�܂��A�擾�͕K���C�x���g�T�u���[�`�����ōs�Ȃ��K�v������܂��B

%href
comevent
comevarg
%port-
Let

