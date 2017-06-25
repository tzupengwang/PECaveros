#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
/*
Delaunay Triangulation:
Given a sets of points on 2D plane, find a triangulation
such that no points will strictly inside circumcircle
of any triangle.

find : return a triangle contain given point
add_point : add a point into triangulation

A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.edge[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3]
*/
#define double LL
const int N = 100000 + 5;
const int MAX_TRIS = N * 6;
#define eps 0
//double eps = 1e;
LL sqr(LL x) { return x*x; }
bool in_cc(const Pt& p1, const Pt& p2, const Pt& p3, const Pt& p4){
// return p4 is in circumcircle of tri(p1,p2,p3)
	double u11 = p1.X - p4.X;
	double u21 = p2.X - p4.X;
	double u31 = p3.X - p4.X;
	double u12 = p1.Y - p4.Y;
	double u22 = p2.Y - p4.Y;
	double u32 = p3.Y - p4.Y;
	double u13 = sqr(p1.X)-sqr(p4.X)+sqr(p1.Y)-sqr(p4.Y);
	double u23 = sqr(p2.X)-sqr(p4.X)+sqr(p2.Y)-sqr(p4.Y);
	double u33 = sqr(p3.X)-sqr(p4.X)+sqr(p3.Y)-sqr(p4.Y);
	double det = -u13*u22*u31 + u12*u23*u31 + u13*u21*u32 - u11*u23*u32 - u12*u21*u33 + u11*u22*u33;
	return det > 0;
}
double side(const Pt& a, const Pt& b, const Pt& p)
{ return (b - a) ^ (p - a); }
typedef int SdRef;
struct Tri;
typedef Tri* TriRef;
struct Edge {
	TriRef tri;
	SdRef     side;
	Edge() : tri(0), side(0) {}
	Edge(TriRef _tri, SdRef _side) : tri(_tri), side(_side) {}
};
struct Tri {
	Pt p[3];
	Edge edge[3];
	TriRef chd[3];
	Tri() {}
	Tri(const Pt& p0, const Pt& p1, const Pt& p2) {
		p[0] = p0; p[1] = p1; p[2] = p2;
		chd[0] = chd[1] = chd[2] = 0;
	}
	bool has_chd() const
  { return chd[0] != 0; }
	int num_chd() const {
		return chd[0] == 0 ? 0
			: chd[1] == 0 ? 1
			: chd[2] == 0 ? 2 : 3;
	}
	bool contains(Pt const& q) const {
		double a = side(p[0],p[1],q);
		double b = side(p[1],p[2],q);
		double c = side(p[2],p[0],q);
		return a >= 0 && b >= 0 && c >= -eps;
	}
} triange_pool[MAX_TRIS], *tot_tris;
void edge(Edge a, Edge b) {
	if(a.tri) a.tri->edge[a.side] = b;
	if(b.tri) b.tri->edge[b.side] = a;
}
struct Trig { // Triangulation
  Trig() {
    const LL LOTS = 1e6;
    //const double LOTS = 1e6;
    the_root = new(tot_tris++) Tri(Pt(-LOTS,-LOTS),Pt(+LOTS,-LOTS),Pt(0,+LOTS));
  }
// tools
  TriRef find(Pt p) const
  { return find(the_root,p); }
  void add_point(const Pt& p)
  { add_point(find(the_root,p),p); }
// tools
  TriRef the_root;
  static TriRef find(TriRef root, const Pt& p) {
    for( ; ; ) {
      if (!root->has_chd())
        return root;
      for (int i = 0; i < 3 && root->chd[i] ; ++i)
        if (root->chd[i]->contains(p)) {
          root = root->chd[i];
          break;
        }
      // "point not found"
    }
  }
  void add_point(TriRef root, Pt const& p) {
    TriRef tab,tbc,tca;
    /* split it into three triangles */
    tab=new(tot_tris++) Tri(root->p[0],root->p[1],p);
    tbc=new(tot_tris++) Tri(root->p[1],root->p[2],p);
    tca=new(tot_tris++) Tri(root->p[2],root->p[0],p);
    edge(Edge(tab,0), Edge(tbc,1));
    edge(Edge(tbc,0), Edge(tca,1));
    edge(Edge(tca,0), Edge(tab,1));
    edge(Edge(tab,2), root->edge[2]);
    edge(Edge(tbc,2), root->edge[0]);
    edge(Edge(tca,2), root->edge[1]);
    root->chd[0] = tab;
    root->chd[1] = tbc;
    root->chd[2] = tca;
    flip(tab,2);
    flip(tbc,2);
    flip(tca,2);
  }
  void flip(TriRef tri, SdRef pi) {
    TriRef trj = tri->edge[pi].tri;
    int pj = tri->edge[pi].side;
    if (!trj) return;
    if (!in_cc(tri->p[0],tri->p[1],tri->p[2],trj->p[pj])) return;
    /* flip edge between tri,trj */
    TriRef trk = new(tot_tris++) Tri(tri->p[(pi+1)%3], trj->p[pj], tri->p[pi]);
    TriRef trl = new(tot_tris++) Tri(trj->p[(pj+1)%3], tri->p[pi], trj->p[pj]);
    edge(Edge(trk,0), Edge(trl,0));
    edge(Edge(trk,1), tri->edge[(pi+2)%3]);
    edge(Edge(trk,2), trj->edge[(pj+1)%3]);
    edge(Edge(trl,1), trj->edge[(pj+2)%3]);
    edge(Edge(trl,2), tri->edge[(pi+1)%3]);
    tri->chd[0]=trk; tri->chd[1]=trl; tri->chd[2]=0;
    trj->chd[0]=trk; trj->chd[1]=trl; trj->chd[2]=0;
    flip(trk,1); flip(trk,2);
    flip(trl,1); flip(trl,2);
  }
};
//int n;
//Pt ps[N];
void build(){
}
void scan( Pt& tp ){
  scanf( "%lld%lld" , &tp.X , &tp.Y );
}
#define N 101010
int n;
Pt p[ N ][ 3 ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      scan( p[ i ][ j ] );
}
Pt ps[ N ];
set< vector<Pt> > vst , usd;
void go( Tri* now ){
  if( !now ) return;
  vector<Pt> vv;
  for( int i = 0 ; i < 3 ; i ++ )
    vv.push_back( now->p[ i ] );
  sort( vv.begin() , vv.end() );
  if( vst.count( vv ) ) return;
  vst.insert( vv );
  if( !now->has_chd() ){
    usd.insert( vv );
    for( auto i : vv )
      printf( "%lld %lld\n" , i.X , i.Y );
    puts( "======" );
  }
  for( int i = 0 ; i < 3 ; i ++ )
    go( now->chd[ i ] );
}
void solve(){
	tot_tris = triange_pool;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      ps[ i * 3 + j ] = p[ i ][ j ];
	random_shuffle(ps, ps + 3 * n);
	Trig tri;
	for(int i = 0; i < 3 * n; ++ i)
		tri.add_point(ps[i]);
  go( tri.the_root );
  for( int i = 0 ; i < n ; i ++ ){
    vector<Pt> vv;
    for( int j = 0 ; j < 3 ; j ++ )
      vv.push_back( p[ i ][ j ] );
    sort( vv.begin() , vv.end() );
    if( usd.count( vv ) == 0 ){
      puts( "NO" );
      return;
    }
  }
  puts( "YES" );
}
int main(){
  init();
  solve();
}
