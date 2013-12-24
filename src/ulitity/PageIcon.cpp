#include "stdafx.h"
#include "Xgame.h"
#include "PageIcon.h"

IMPLEMENT_DYNAMIC(CPageIcon, CPropertyPage)

CPageIcon::CPageIcon(UINT nIDTemplate, UINT nIconID)
 : CPropertyPage(nIDTemplate) , m_nIconID(nIconID) , m_hIcon(NULL)
{
	//{{AFX_DATA_INIT(CPageIcon)
	//}}AFX_DATA_INIT
  // Set icon
  if( NULL != m_nIconID )
  {
    m_psp.dwFlags |= PSP_USEHICON;
    m_psp.hIcon   = AfxGetApp()->LoadIcon( m_nIconID );
  }
}

CPageIcon::~CPageIcon()
{
}

void CPageIcon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageIcon)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageIcon, CPropertyPage)
	//{{AFX_MSG_MAP(CPageIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

