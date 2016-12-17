// 数据压缩View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__8AABA7AE_460A_4DC9_9326_52BF238668E8__INCLUDED_)
#define AFX_VIEW_H__8AABA7AE_460A_4DC9_9326_52BF238668E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct point									//点的坐标。
{
	double number;
	double xpoint;
	double ypoint;
};

class CMyView : public CView
{
public: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CMyView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void On32771();
	afx_msg void On327721();
	afx_msg void On327722();
	afx_msg void On327725();
	afx_msg void On3277210();
	afx_msg void On3277220();
	afx_msg void On3277250();
	afx_msg void On32773();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 数据压缩View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__8AABA7AE_460A_4DC9_9326_52BF238668E8__INCLUDED_)
