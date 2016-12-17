// 数据压缩View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "数据压缩.h"
#include "cmath"

#include "数据压缩Doc.h"
#include "数据压缩View.h"
#include "iostream"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

int maxdistance(double y,int s,int t,double d[])			//各个点到线段的最大距离，如果都未达到阈值，返回0。
{
	int m=0;
	for(int i=s+1,j=1;i<t;i++,j++)
		if(d[j]>d[m])
			m=j;
	if(d[m]<=y)
		m=0;
	else
		m+=s;
	return m;
}

double distance(double x1,double y1,double x2,double y2,double a,double b)	//计算各个点到直线的距离。
{
	double k=(y2-y1)/(x2-x1);
	double d=fabs(k*a-b-k*x1+y1)/sqrt(1+k*k);
	return d;
}

void print0(FILE *f,point a[],int s,int t)				//点输出到clip.txt中。
{
	fprintf(f,"%lf %lf %lf\n",a[s].number,a[s].xpoint,a[s].ypoint);
	fprintf(f,"%lf %lf %lf\n",a[t].number,a[t].xpoint,a[t].ypoint);
}

void print(FILE *f,point a[],int s)				//点输出到clip.txt中。
{
	fprintf(f,"%lf %lf %lf\n",a[s].number,a[s].xpoint,a[s].ypoint);
}

void dp(FILE *f,point p[],double d,int s,int t)	//DP算法的实现(y 阈值,s 起始点,t 终止点)。
{
	double q[600],n;
	q[0]=0;
	for(int i=s+1,j=1;i<t;i++,j++)
		q[j]=distance(p[s].xpoint,p[s].ypoint,p[t].xpoint,p[t].ypoint,p[i].xpoint,p[i].ypoint);
	n=maxdistance(d,s,t,q);
	if(n==0  || t-s<2)
	{
		print(f,p,s);	
	}
	else
	{
		dp(f,p,d,s,n);
		dp(f,p,d,n,t);
	}
}

void dpdraw(double d)
{
	FILE *f;
	FILE *g=fopen("clip.txt","w");
	f=fopen("clip0.txt","r");
	double a[600],b[600],c;
	int i=0,m[600],n=0;
	point p[600];
	fscanf(f,"%lf%lf%lf",&a[i++],&b[i++],&c);
	while(feof(f)==0)							//计算总共的线段数与各个线段的点数。
	{
		fscanf(f,"%lf%lf%lf",&a[i],&b[i],&c);
		if(b[i]==0)
		{
			m[n++]=(b[i-1]==b[1])?a[i-1]:a[i-1]+1;
			i=0;
			fscanf(f,"%lf%lf%lf",&a[i],&b[i],&c);
		}
		i++;
	}
	fclose(f);
	f=fopen("clip0.txt","r");
	for(i=0;i<n;i++)								//DP算法的实现。
	{
		fscanf(f,"%lf%lf%lf",&p[0].number,&p[0].xpoint,&p[0].ypoint);
		fprintf(g,"%lf %lf %lf\n",p[0].number,p[0].xpoint,p[0].ypoint);
		for(int j=1;j<=m[i];j++)
			fscanf(f,"%lf%lf%lf",&p[j].number,&p[j].xpoint,&p[j].ypoint);
		if(m[i]<=2)
			print0(g,p,1,m[i]);
		else
			dp(g,p,d,1,m[i]);
	}
	fclose(f);
	fclose(g);
}

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_COMMAND(ID_MENUITEM32771, On32771)
	ON_COMMAND(ID_MENUITEM327721, On327721)
	ON_COMMAND(ID_MENUITEM327722, On327722)
	ON_COMMAND(ID_MENUITEM327725, On327725)
	ON_COMMAND(ID_MENUITEM3277210, On3277210)
	ON_COMMAND(ID_MENUITEM3277220, On3277220)
	ON_COMMAND(ID_MENUITEM3277250, On3277250)
	ON_COMMAND(ID_MENUITEM32773, On32773)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPen Pen;
	CPen *OldPen;
	Pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	double m,m1,a,b,c,b1,c1,d;
	OldPen=pDC->SelectObject(&Pen);
	FILE *clip;
	clip=fopen("clip.txt","r");
	fscanf(clip,"%lf%lf%lf",&a,&b,&c);
	fscanf(clip,"%lf%lf%lf",&a,&b,&c);
	b1=(b-401800);
	c1=(4071000-c);
	pDC->MoveTo(b1/2,c1/2);
	while(feof(clip)==0)
	{		
		fscanf(clip,"%lf%lf%lf",&a,&b,&c);		
		if(b==0)
		{
			fscanf(clip,"%lf%lf%lf",&a,&b,&c);
			b1=(b-401800);
			c1=(4071000-c);
			pDC->MoveTo(b1/2,c1/2);
		}	
		b1=(b-401800);
		c1=(4071000-c);
		pDC->LineTo(b1/2,c1/2);
	}
	fclose(clip);
	pDC->SelectObject(OldPen);
	// TODO: add draw code for native data here
}

void CMyView::On32771()
{
	dpdraw(0);
	Invalidate();
}

void CMyView::On327721()
{
	dpdraw(1);
	Invalidate();
}

void CMyView::On327722()
{
	dpdraw(2);
	Invalidate();
}

void CMyView::On327725()
{
	dpdraw(5);
	Invalidate();
}

void CMyView::On3277210()
{
	dpdraw(10);
	Invalidate();
}

void CMyView::On3277220()
{
	dpdraw(20);
	Invalidate();
}

void CMyView::On3277250()
{
	dpdraw(50);
	Invalidate();
}

void CMyView::On32773()
{
	FILE *clip;
	clip=fopen("clip.txt","w");
	fprintf(clip,"\0");
	Invalidate();
}


/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers
