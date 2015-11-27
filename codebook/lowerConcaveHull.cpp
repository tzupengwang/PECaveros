/****
  maintain a "concave hull" that support the following
  1. insertion of a line
  2. query of height(y) on specific x on the hull
 ****/
/* set as needed */
const long double eps=1e-9;
const long double inf=1e19;
class Segment {
 public:
  long double m,c,x1,x2; // y=mx+c
  bool flag;
  Segment(long double _m,long double _c,long double _x1
      =-inf,long double _x2=inf,bool _flag=0)
    :m(_m),c(_c),x1(_x1),x2(_x2),flag(_flag) {}
  long double evaly(long double x) const {
    return m*x+c;
  }
  const bool operator<(long double x) const {
    return x2-eps<x;
  }
  const bool operator<(const Segment &b) const {
    if(flag||b.flag) return *this<b.x1;
    return m+eps<b.m;
  }
};
class LowerConcaveHull { // maintain a hull like: \__/
 public:
  set<Segment> hull;
  /* functions */
  long double xintersection(Segment a,Segment b) {
    return (a.c-b.c)/(b.m-a.m);
  }
  inline set<Segment>::iterator replace(set<Segment> &
      hull,set<Segment>::iterator it,Segment s) {
    hull.erase(it);
    return hull.insert(s).first;
  }
  void insert(Segment s) { // insert a line and update
    hull
      set<Segment>::iterator it=hull.find(s);
    // check for same slope
    if(it!=hull.end()) {
      if(it->c+eps>=s.c) return;
      hull.erase(it);
    }
    // check if below whole hull
    it=hull.lower_bound(s);
    if(it!=hull.end()&&s.evaly(it->x1)<=it->evaly(it->
          x1)+eps) return;
    // update right hull
    while(it!=hull.end()) {
      long double x=xintersection(s,*it);
      if(x>=it->x2-eps) hull.erase(it++);
      else {
        s.x2=x;
        it=replace(hull,it,Segment(it->m,it->c,x,it->
              x2));
        break;
      }
    }
    // update left hull
    while(it!=hull.begin()) {
      long double x=xintersection(s,*(--it));
      if(x<=it->x1+eps) hull.erase(it++);
      else {
        s.x1=x;
        it=replace(hull,it,Segment(it->m,it->c,it->x1
              ,x));
        break;
      }
    }
    // insert s
    hull.insert(s);
  }
  void insert(long double m,long double c) { insert(
      Segment(m,c)); }
  long double query(long double x) { // return y @ given
    x
      set<Segment>::iterator it=hull.lower_bound(Segment
          (0.0,0.0,x,x,1));
    return it->evaly(x);
  }
};
