#include <bits/stdc++.h>
using namespace std;
#define N 10101
void tle(){
  while( true ){
    cerr << "shit" << endl;
  }
}
typedef double type;
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
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
//const int N = 100000 + 5;
const int MAX_TRIS = N * 8;
double eps = 1e-8;
double sqr(double x) { return x*x; }
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
	return det > eps;
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
		return a >= -eps && b >= -eps && c >= -eps;
	}
} triange_pool[MAX_TRIS], *tot_tris;
void edge(Edge a, Edge b) {
	if(a.tri) a.tri->edge[a.side] = b;
	if(b.tri) b.tri->edge[b.side] = a;
}
bool out( double d ){
  return fabs( d ) > 1e5;
}
bool bad( TriRef pt ){
  for( int i = 0 ; i < 3 ; i ++ )
    if( out( pt->p[ i ].X ) or
        out( pt->p[ i ].Y ) )
      return true;
  return false;
}
struct Trig { // Triangulation
  Trig() {
    const double LOTS = 1e6;
    the_root = new(tot_tris++) Tri(Pt(-LOTS,-LOTS),Pt(+LOTS,-LOTS),Pt(0,+LOTS));
  }
  
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


/*
// tools
  TriRef find(Pt p, bool force=true) const
  { return find(the_root,p, force); }
  void add_point(const Pt& p)
  { add_point(find(the_root,p),p); }
// tools
  TriRef the_root;
  static TriRef find(TriRef root, const Pt& p, bool force=true) {
    //if( !force ){
    //for( int i = 0 ; i < 3 ; i ++ )
      //printf( "(%.2f, %.2f) " , root->p[ i ].X , root->p[ i ].Y );
    //puts( "" );
    //}
    if( !root ) tle();
    if (!root->has_chd()){
      if( force ) return root;
      if( bad( root ) )
        return NULL;
      return root;
    }
    //puts( "got" );
    for (int i = 0; i < 3 && root->chd[i] ; ++i)
      if (root->chd[i]->contains(p)) {
        TriRef ret = find( root->chd[i] , p , force );
        if( ret ) return ret;
        //root = root->chd[i];
      }
    return NULL;
      // "point not found"
  }*/
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
int n;
Pt ps[N] , r;
Trig tri;
map< pair<int,int> , int > id;
int wid , hei;
void build(){
	tot_tris = triange_pool;
  scanf( "%d" , &n );
	for(int i = 0; i < n; ++ i) {
		int x, y;
		scanf("%d%d", &x, &y);
    if( i == 3 ) r = { x , y };
    id[ { x , y } ] = i + 1;
    ps[ i ] = { x , y };
	}
  const double dlt = 1e-8;
  ps[ 0 ] = ps[ 0 ] + Pt({ -dlt , +dlt });
  ps[ 1 ] = ps[ 1 ] + Pt({ +dlt , +dlt });
  ps[ 2 ] = ps[ 2 ] + Pt({ +dlt , -dlt });
  ps[ 3 ] = ps[ 3 ] + Pt({ -dlt , -dlt });
  wid = ps[ 1 ].X - ps[ 0 ].X;
  hei = ps[ 0 ].Y - ps[ 3 ].Y;
	random_shuffle(ps, ps + n);
  tri = Trig();
	for(int i = 0; i < n; ++ i){
    //cout << ps[ i ].X << " "
         //<< ps[ i ].Y << "\n";
		tri.add_point(ps[i]);
  }
}
int k;
Pt q;
void print( TriRef ans ){
  printf( "3" );
  vector< Pt > vv;
  for( int i = 0 ; i < 3 ; i ++ ){
    vv.push_back( ans->p[ i ] );
    //printf( "%.12f %.12f\n" , ans->p[ i ].X , ans->p[ i ].Y );
    //printf( " %d" , id[ { (int)round( ans->p[ i ].X ) ,
                          //(int)round( ans->p[ i ].Y ) } ] );
  }
  if( ( ( vv[ 1 ] - vv[ 0 ] ) ^ ( vv[ 2 ] - vv[ 0 ] ) ) > 0 )
    swap( vv[ 1 ] , vv[ 2 ] );
  for( auto i : vv )
    printf( " %d" , id[ { (int)round( i.X ) ,
                          (int)round( i.Y ) } ] );
  puts( "" );
}
int main(){
  build();
  cin >> k; scan( q );
  TriRef ret = tri.find( q );
  print( ret );
  for( int i = 2 ; i <= k ; i ++ ){
    Pt sft; scan( sft );
    Pt s = { 0 , 0 };
    for( int j = 0 ; j < 3 ; j ++ )
      s = s + ret->p[ j ];
    s.X = int( s.X / 3 );
    s.Y = int( s.Y / 3 );
    s = s + sft;
    q.X = ( int( s.X ) % wid + wid ) % wid + r.X;
    q.Y = ( int( s.Y ) % hei + hei ) % hei + r.Y;
    //cout << q.X << " " << q.Y << endl;
    ret = tri.find( q );
    print( ret );
  }
}
