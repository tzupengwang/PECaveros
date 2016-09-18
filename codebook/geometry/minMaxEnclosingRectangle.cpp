/******* NEED REVISION *******/
/* uva819 - gifts large and small */
#define MAXN 100005
const double eps=1e-8;
const double inf=1e15;
class Coor {
 public:
  double x,y;
  Coor() {}
  Coor(double xi,double yi) { x=xi; y=yi; }
  Coor& operator+=(const Coor &b) { x+=b.x; y+=b.y; return *this; }
  const Coor operator+(const Coor &b) const { return (Coor)*this+=b; }
  Coor& operator-=(const Coor &b) { x-=b.x; y-=b.y; return *this; }
  const Coor operator-(const Coor &b) const { return (Coor)*this-=b; }
  Coor& operator*=(const double b) { x*=b; y*=b; return *this; }
  const Coor operator*(const double b) const { return (Coor)*this*=b; }
  Coor& operator/=(const double b) { x/=b; y/=b; return *this; }
  const Coor operator/(const double b) const { return (Coor)*this/=b; }
  const bool operator<(const Coor& b) const { return y<b.y-eps||fabs(y-b.y)<eps&&x<b.x; }
  const double len2() const { return x*x+y*y; }
  const double len() const { return sqrt(len2()); }
  const Coor perp() const { return Coor(y,-x); }
  Coor& standardize() {
    if(y<0||y==0&&x<0) {
      x=-x;
      y=-y;
    }
    return *this;
  }
  const Coor standardize() const { return ((Coor)*this).standardize(); }
};
double dot(const Coor &a,const Coor &b) { return a.x*b.x+a.y*b.y; }
double dot(const Coor &o,const Coor &a,const Coor &b) { return dot(a-o,b-o); }
double cross(const Coor &a,const Coor &b) { return a.x*b.y-a.y*b.x; }
double cross(const Coor &o,const Coor &a,const Coor &b) { return cross(a-o,b-o); }
Coor cmpo;
const bool cmpf(const Coor &a,const Coor &b) {
  return cross(cmpo,a,b)>eps||fabs(cross(cmpo,a,b))<eps&&
    dot(a,cmpo,b)<-eps;
}
class Polygon {
 public:
  int pn;
  Coor p[MAXN];
  void convex_hull() {
    int i,tn=pn;
    for(i=1;i<pn;++i) if(p[i]<p[0]) swap(p[0],p[i]);
    cmpo=p[0];
    std::sort(p+1,p+pn,cmpf);
    for(i=pn=1;i<tn;++i) {
      while(pn>2&&cross(p[pn-2],p[pn-1],p[i])<=eps) --
        pn;
      p[pn++]=p[i];
    }
    p[pn]=p[0];
  }
};
Polygon pol;
double minarea,maxarea;
int slpn;
Coor slope[MAXN*2];
Coor lrec[MAXN*2],rrec[MAXN*2],trec[MAXN*2],brec[MAXN*2];
inline double xproject(Coor p,Coor slp) { return dot(p,slp)/slp.len(); }
inline double yproject(Coor p,Coor slp) { return cross(p,slp)/slp.len(); }
inline double calcarea(Coor lp,Coor rp,Coor bp,Coor tp,Coor slp) {
  return (xproject(rp,slp)-xproject(lp,slp))*(yproject(tp,slp)-yproject(bp,slp)); }
  inline void solve(){
    int i,lind,rind,tind,bind,tn;
    double pro,area1,area2,l,r,m1,m2;
    Coor s1,s2;
    pol.convex_hull();
    slpn=0; /* generate all critical slope */
    slope[slpn++]=Coor(1.0,0.0);
    slope[slpn++]=Coor(0.0,1.0);
    for(i=0;i<pol.pn;i++) {
      slope[slpn]=(pol.p[i+1]-pol.p[i]).standardize();
      if(slope[slpn].x>0) slpn++;
      slope[slpn]=(pol.p[i+1]-pol.p[i]).perp().
        standardize();
      if(slope[slpn].x>0) slpn++;
    }
    cmpo=Coor(0,0);
    std::sort(slope,slope+slpn,cmpf);
    tn=slpn;
    for(i=slpn=1;i<tn;i++)
      if(cross(cmpo,slope[i-1],slope[i])>0) slope[slpn
        ++]=slope[i];
    lind=rind=0; /* find critical touchpoints */
    for(i=0;i<pol.pn;i++) {
      pro=xproject(pol.p[i],slope[0]);
      if(pro<xproject(pol.p[lind],slope[0])) lind=i;
      if(pro>xproject(pol.p[rind],slope[0])) rind=i;
    }
    tind=bind=0;
    for(i=0;i<pol.pn;i++) {
      pro=yproject(pol.p[i],slope[0]);
      if(pro<yproject(pol.p[bind],slope[0])) bind=i;
      if(pro>yproject(pol.p[tind],slope[0])) tind=i;
    }
    for(i=0;i<slpn;i++) {
      while(xproject(pol.p[lind+1],slope[i])<=xproject(
            pol.p[lind],slope[i])+eps)
        lind=(lind==pol.pn-1?0:lind+1);
      while(xproject(pol.p[rind+1],slope[i])>=xproject(
            pol.p[rind],slope[i])-eps)
        rind=(rind==pol.pn-1?0:rind+1);
      while(yproject(pol.p[bind+1],slope[i])<=yproject(
            pol.p[bind],slope[i])+eps)
        bind=(bind==pol.pn-1?0:bind+1);
      while(yproject(pol.p[tind+1],slope[i])>=yproject(
            pol.p[tind],slope[i])-eps)
        tind=(tind==pol.pn-1?0:tind+1);
      lrec[i]=pol.p[lind];
      rrec[i]=pol.p[rind];
      brec[i]=pol.p[bind];
      trec[i]=pol.p[tind];
    }
    minarea=inf; /* find minimum area */
    for(i=0;i<slpn;i++) {
      area1=calcarea(lrec[i],rrec[i],brec[i],trec[i],
          slope[i]);
      if(area1<minarea) minarea=area1;
    }
    maxarea=minarea; /* find maximum area */
    for(i=0;i<slpn-1;i++) {
      l=0.0; r=1.0;
      while(l<r-eps) {
        m1=l+(r-l)/3;
        m2=l+(r-l)*2/3;
        s1=slope[i]*(1.0-m1)+slope[i+1]*m1;
        area1=calcarea(lrec[i],rrec[i],brec[i],trec[i],
            s1);
        s2=slope[i]*(1.0-m2)+slope[i+1]*m2;
        area2=calcarea(lrec[i],rrec[i],brec[i],trec[i],
            s2);
        if(area1<area2) l=m1;
        else r=m2;
      }
      s1=slope[i]*(1.0-l)+slope[i+1]*l;
      area1=calcarea(lrec[i],rrec[i],brec[i],trec[i],s1);
      if(area1>maxarea) maxarea=area1;
    }
  }
int main(){
  int i,casenum=1;
  while(scanf("%d",&pol.pn)==1&&pol.pn) {
    for(i=0;i<pol.pn;i++)
      scanf("%lf %lf",&pol.p[i].x,&pol.p[i].y);
    solve();
    //minarea, maxarea
  }
}
