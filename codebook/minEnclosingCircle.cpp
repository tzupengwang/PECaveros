/* minimum enclosing circle */
int n;
Coor p[MAXNUM];
const Circle circumcircle(Coor a,Coor b,Coor c){
  Circle cir;
  double fa,fb,fc,fd,fe,ff,dx,dy,dd;
  if(iszero(cross(a,b,c))) {
    if(dot(a,b,c)<=0) return Circle((b+c)/2,(b-c).len()/2)
      ;
    if(dot(b,c,a)<=0) return Circle((c+a)/2,(c-a).len()/2)
      ;
    if(dot(c,a,b)<=0) return Circle((a+b)/2,(a-b).len()/2)
      ;
  } else {
    fa=2*(a.x-b.x);
    fb=2*(a.y-b.y);
    fc=a.len2()-b.len2();
    fd=2*(a.x-c.x);
    fe=2*(a.y-c.y);
    ff=a.len2()-c.len2();
    dx=fc*fe-ff*fb;
    dy=fa*ff-fd*fc;
    dd=fa*fe-fd*fb;
    cir.o=Coor(dx/dd,dy/dd);
    cir.r=(a-cir.o).len();
    return cir;
  }
}
inline Circle mec(int fixed,int num){
  int i;
  Circle cir;
  if(fixed==3) return circumcircle(p[0],p[1],p[2]);
  cir=circumcircle(p[0],p[0],p[1]);
  for(i=fixed;i<num;i++) {
    if(cir.inside(p[i])) continue;
    swap(p[i],p[fixed]);
    cir=mec(fixed+1,i+1);
  }
  return cir;
}
inline double min_radius() {
  if(n<=1) return 0.0;
  if(n==2) return (p[0]-p[1]).len()/2;
  scramble();
  return mec(0,n).r;
}
