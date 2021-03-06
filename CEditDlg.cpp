// CEditDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFC_Team_Dlg01.h"
#include "CEditDlg.h"
#include "afxdialogex.h"
#include "MFC_Team_Dlg01Dlg.h"
#include "CEditMode.h"
#include "EditPlay.h"

// CEditDlg 대화 상자

IMPLEMENT_DYNAMIC(CEditDlg, CDialog)

CEditDlg::CEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EDITDLG, pParent)
{

}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITMAIN, m_editMain);
	DDX_Control(pDX, IDC_ESBTN, m_esBtn);
	DDX_Control(pDX, IDC_MEBTN, m_meBtn);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialog)
	ON_BN_CLICKED(IDC_ESBTN, &CEditDlg::OnBnClickedEsbtn)
	ON_BN_CLICKED(IDC_MEBTN, &CEditDlg::OnBnClickedMebtn)
END_MESSAGE_MAP()


// CEditDlg 메시지 처리기


BOOL CEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMFCTeamDlg01Dlg* parent =
		(CMFCTeamDlg01Dlg*)AfxGetMainWnd();
	parent->ShowWindow(SW_HIDE);
	m_editMain.SetEnhMetaFile(GetEnhMetaFile(_T("editmain.emf")));
	m_esBtn.LoadBitmaps(IDB_BITMAP53, IDB_BITMAP54, IDB_BITMAP54, IDB_BITMAP53);
	m_esBtn.SizeToContent();
	m_meBtn.LoadBitmaps(IDB_BITMAP55, IDB_BITMAP56, IDB_BITMAP56, IDB_BITMAP55);
	m_meBtn.SizeToContent();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CEditDlg::OnBnClickedEsbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EditPlay edp;
	edp.DoModal();

	this->ShowWindow(SW_SHOW);
}


void CEditDlg::OnBnClickedMebtn()
{
	CEditMode dlg;
	dlg.DoModal();

	this->ShowWindow(SW_SHOW);
}
