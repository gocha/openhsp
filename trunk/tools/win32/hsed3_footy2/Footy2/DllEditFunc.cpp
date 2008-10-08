/**
 * @file DllEditFunc.cpp
 * @brief �ҏW�n�̊֐�����������t�@�C��
 * @author Shinji Watanabe
 * @verison 1.0
 * @date Jan.20.2008
 */

#include "DllDefnition.h"
#include "ConvFactory.h"

/**
 * Footy2Copy
 * @brief �R�s�[�������s���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2Copy(int nID)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;
	if (!pFooty->m_cDoc.IsSelecting())return FOOTY2ERR_NOTSELECTED;
	return pFooty->Copy() ? FOOTY2ERR_NONE : FOOTY2ERR_MEMORY;
}

/**
 * Footy2Cut
 * @brief �؂��菈�����s���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2Cut(int nID)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;
	if (!pFooty->m_cDoc.IsSelecting())return FOOTY2ERR_NOTSELECTED;
	return pFooty->Cut() ? FOOTY2ERR_NONE : FOOTY2ERR_MEMORY;
}

/**
 * Footy2Paste
 * @brief �y�[�X�g�������s���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2Paste(int nID)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;
	return pFooty->Paste() ? FOOTY2ERR_NONE : FOOTY2ERR_MEMORY;
}

/**
 * Footy2IsEdited
 * @brief �ҏW����Ă��邩�ǂ������擾���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(bool) Footy2IsEdited(int nID)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return false;
	return pFooty->m_cDoc.IsEdited();
}

/**
 * Footy2SelectAll
 * @brief �S�đI���������s���܂�
 * @param nID ���������s����Footy��ID
 * @param bRedraw �ĕ`�揈�����s�����ǂ���
 */
FOOTYEXPORT(int) Footy2SelectAll(int nID,bool bRedraw)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;

	// �S�đI������
	pFooty->m_cDoc.SelectAll();

	// �ĕ`�揈��
	if (bRedraw)
	{
		pFooty->m_cView[0].Refresh();
	}
	return FOOTY2ERR_NONE;
}


/**
 * Footy2Undo
 * @brief �A���h�D���s���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2Undo(int id)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(id);
	if (!pFooty)return FOOTY2ERR_NOID;

	// �A���h�D����
	if (!pFooty->Undo())
		return FOOTY2ERR_NOUNDO;

	// �L�����b�g����ʒu���Đݒ�
	for (int i=0;i<4;i++)
	{
		pFooty->m_cView[i].AdjustVisibleLine();
		pFooty->m_cView[i].AdjustVisiblePos();
	}

	// ����
	return FOOTY2ERR_NONE;
}

/**
 * Footy2Redo
 * @brief ���h�D���s���܂��B
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2Redo(int id)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(id);
	if (!pFooty)return FOOTY2ERR_NOID;
	// ���h�D����
	if (!pFooty->Redo())
		return FOOTY2ERR_NOUNDO;
	// ����
	return FOOTY2ERR_NONE;
}


#ifndef UNDER_CE
/**
 * Footy2SearchA
 * @brief �����������s���܂�
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2SearchA(int nID,const char *szText,int nFlags)
{
	// �ϊ�
	CConvFactory cConv;
	if (!cConv.GetConv()->ToUnicode(szText,(size_t)strlen(szText)))
		return FOOTY2ERR_MEMORY;

	// ����
	return Footy2SearchW(nID,reinterpret_cast<const wchar_t*>(cConv.GetConv()->GetConvData()),nFlags);
}
#endif	/*not defined UNDER_CE*/


/**
 * Footy2SearchW
 * @brioef �����������s���܂�
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2SearchW(int nID,const wchar_t *szText,int nFlags)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;
	
	// ������������̂Ƃ�
	if (szText[0] == L'\0')
		return FOOTY2ERR_ARGUMENT;
	
	// �������������s����
	if (pFooty->m_cDoc.Search(szText,nFlags))			// ���������Ƃ�
	{
		if ((nFlags & SEARCH_NOT_ADJUST_VIEW) == 0)		// �X�N���[��������
		{
			pFooty->m_cView[0].AdjustVisiblePos();
			pFooty->m_cView[0].AdjustVisibleLine();
		}
		if ((nFlags & SEARCH_NOT_REFRESH) == 0)			// �ĕ`�悳����
		{
			pFooty->m_cView[0].Refresh();
		}
		return FOOTY2ERR_NONE;
	}
	else
	{
		// ������Ȃ������Ƃ�
		if ((nFlags & SEARCH_BEEP_ON_404) != 0)
			MessageBeep(MB_ICONEXCLAMATION);
		return FOOTY2ERR_404;
	}
}

/**
 * Footy2ShiftLock
 * @brief �V�t�g���b�N���s��
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(int) Footy2ShiftLock(int nID,bool bLocked)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return FOOTY2ERR_NOID;

	// �V�t�g���b�N��Ԃ��Z�b�g����
	for (int i=0;i<4;i++)
	{
		pFooty->m_cView[i].SetShiftLock(bLocked);
	}
	
	return FOOTY2ERR_NONE;
}

/**
 * Footy2IsShiftLocked
 * @brief �V�t�g���b�N����Ă��邩�ǂ����擾����
 * @param nID ���������s����Footy��ID
 */
FOOTYEXPORT(bool) Footy2IsShiftLocked(int nID)
{
	// Footy���擾����
	CFooty *pFooty = GetFooty(nID);
	if (!pFooty)return false;
	// �V�t�g���b�N��Ԃ��擾����
	return pFooty->m_cView[0].IsShiftLocked();
}

/*[EOF]*/