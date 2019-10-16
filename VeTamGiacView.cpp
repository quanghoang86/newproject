
// VeTamGiacView.cpp : implementation of the CVeTamGiacView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "VeTamGiac.h"
#endif

#include "VeTamGiacDoc.h"
#include "VeTamGiacView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVeTamGiacView

IMPLEMENT_DYNCREATE(CVeTamGiacView, CView)

BEGIN_MESSAGE_MAP(CVeTamGiacView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CVeTamGiacView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CVeTamGiacView construction/destruction

CVeTamGiacView::CVeTamGiacView() noexcept
{
	// TODO: add construction code here
	b2.thietlap(100, 50, 280, 100);
	b2.chu = CString("Ve Tam Giac");

	control = 1;
	n = 0;

}

CVeTamGiacView::~CVeTamGiacView()
{
}

BOOL CVeTamGiacView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CVeTamGiacView drawing

void CVeTamGiacView::OnDraw(CDC* /*pDC*/)
{
	CVeTamGiacDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pdc = new CClientDC(this);
	b2.draw(pdc);

	// TODO: add draw code for native data here
}


// CVeTamGiacView printing


void CVeTamGiacView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CVeTamGiacView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVeTamGiacView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVeTamGiacView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVeTamGiacView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CVeTamGiacView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CVeTamGiacView diagnostics

#ifdef _DEBUG
void CVeTamGiacView::AssertValid() const
{
	CView::AssertValid();
}

void CVeTamGiacView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVeTamGiacDoc* CVeTamGiacView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVeTamGiacDoc)));
	return (CVeTamGiacDoc*)m_pDocument;
}
#endif //_DEBUG


// CVeTamGiacView message handlers


void CVeTamGiacView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	p1.x = point.x;
	p1.y = point.y;
	CView::OnLButtonDown(nFlags, point);
}


void CVeTamGiacView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	p2.x = point.x;
	p2.y = point.y;
	pdc = new CClientDC(this);
	if (b2.tronghinh(point) == 1)
		control = 2;
	else

		if (control == 2)//tamgiac
		{
			ph[n] = new Tamgiac(p1, p2);
			ph[n]->draw(pdc);
			n++;
		}
	CView::OnLButtonUp(nFlags, point);
}
