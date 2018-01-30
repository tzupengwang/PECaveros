#include <bits/stdc++.h>
using namespace std;
#define N 303030
typedef long long LL;
typedef long double D;
inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
typedef pair<D,D> Pt;
typedef pair<LL,LL> PLL;
typedef pair<Pt,Pt> Seg;
typedef pair<PLL,PLL> lSeg;
#define X first
#define Y second
#define A first
#define B second
template<class T>
pair<T,T> operator+( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
template<class T>
pair<T,T> operator-( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
template<class T>
pair<T,T> operator*( const pair<T,T>& tp , const T& tk ){
  return { tp.X * tk , tp.Y * tk };
}
template<class T>
pair<T,T> operator/( const pair<T,T>& tp , const T& tk ){
  return { tp.X / tk , tp.Y / tk };
}
template<class T>
T operator*( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
template<class T>
T operator^( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
template<class T>
T norm2( const pair<T,T>& tp ){
  return tp * tp;
}
template<class T>
D norm( const pair<T,T>& tp ){
  return sqrt( norm2( tp ) );
}



/******* Begin of test intersection *******/
namespace Inter{
  const D eps = 1e-9;
  struct Treap{
    int sz , val , pri;
    Treap *l , *r;
    Treap( int _val ){
      val = _val; sz = 1;
      pri = rand(); l = r = NULL;
    }
  };
  int Size( Treap * a ){ return a ? a->sz : 0; }
  void pull( Treap * a ){
    a->sz = Size( a->l ) + Size( a->r ) + 1;
  }
  Treap* merge( Treap *a , Treap *b ){
    if( !a || !b ) return a ? a : b;
    if( a->pri > b->pri ){
      a->r = merge( a->r , b );
      pull( a );
      return a;
    }else{
      b->l = merge( a , b->l );
      pull( b );
      return b;
    }
  }
  void split( Treap *t , int k , Treap*&a , Treap*&b ){
    if( !t ){ a = b = NULL; return; }
    if( Size( t->l ) + 1 <= k ){
      a = t;
      split( t->r , k - Size( t->l ) - 1 , a->r , b );
      pull( a );
    }else{
      b = t;
      split( t->l , k , a , b->l );
      pull( b );
    }
  }
  D curx;
  D y_of_x( const Seg& ss , D nx ){
    return ss.A.Y + (ss.B.Y - ss.A.Y) * (nx - ss.A.X) / (ss.B.X - ss.A.X);
  }
  bool lower( const Seg& s1 , const Seg& s2 ){
    D lx = max( s1.A.X , s2.A.X );
    D rx = min( s1.B.X , s2.B.X );
    //if( lx < rx + eps ){
      D sx = min( rx , max( lx , curx ) );
      return y_of_x( s1 , sx ) <
             y_of_x( s2 , sx );
    //}
    //return s1.A.X < s2.A.X;
  }
  vector<Seg> cand;
  int rank( Treap* t , int c_id ){
    if( !t ) return 0;
    if( lower( cand[ t->val ] , cand[ c_id ] ) )
      return Size( t->l ) + 1 + rank( t->r , c_id );
    return rank( t->l , c_id );
  }
  int leftist( Treap* t ){
    if( !t ) return -1;
    if( t->l ) return leftist( t->l );
    return t->val;
  }
  int rightist( Treap* t ){
    if( !t ) return -1;
    if( t->r ) return rightist( t->r );
    return t->val;
  }
  struct Events{ int i , j; D x; };
  bool operator<( const Events& e1 , const Events& e2 ){
    if( fabs( e1.x - e2.x ) > eps ) return e1.x < e2.x;
    if( e1.i != e2.i ) return e1.i < e2.i;
    return e1.j < e2.j;
  }
  set< Events > S;
  int ori( const Pt& o , const Pt& a , const Pt& b ){
    D ret = ( a - o ) ^ ( b - o );
    return (ret > eps) - (ret < -eps);
  }
  // p1 == p2 || q1 == q2 need to be handled
  bool banana( const Pt& p1 , const Pt& p2 ,
               const Pt& q1 , const Pt& q2 ){
    if( fabs( ( p2 - p1 ) ^ ( q2 - q1 ) ) < eps ){ // parallel
      if( ori( p1 , p2 , q1 ) ) return false;
      return ( ( p1 - q1 ) * ( p2 - q1 ) ) < eps ||
             ( ( p1 - q2 ) * ( p2 - q2 ) ) < eps ||
             ( ( q1 - p1 ) * ( q2 - p1 ) ) < eps ||
             ( ( q1 - p2 ) * ( q2 - p2 ) ) < eps;
    }
    return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0) &&
           (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0);
  }
  bool check( int id1 , int id2 ){
    if( id1 == -1 or id2 == -1 ) return false;
    if( id1 / 3 == id2 / 3 ) return false;
    return banana( cand[ id1 ].A , cand[ id1 ].B ,
                   cand[ id2 ].A , cand[ id2 ].B );
  }
  void clear( Treap* t ){
    if( !t ) return;
    clear( t->l );
    clear( t->r );
    delete t;
  }
  void print_treap( Treap* t ){
    if( !t ) return;
    print_treap( t->l );
    printf( "%d " , t->val );
    print_treap( t->r );
  }
  bool has_inter( const vector<Seg>& _cand ){
    D ang = 1021;
    D cosv = cosl( ang );
    D sinv = sinl( ang );
    cand.clear();
    S.clear();
    for( auto seg : _cand ){
      Pt pA = { seg.A.X * cosv - seg.A.Y * sinv ,
                seg.A.X * sinv + seg.A.Y * cosv };
      Pt pB = { seg.B.X * cosv - seg.B.Y * sinv ,
                seg.B.X * sinv + seg.B.Y * cosv };
      //printf( "Segment %.6f %.6f %.6f %.6f\n" , pA.X , pA.Y , pB.X , pB.Y );
      if( pB < pA ) swap( pA , pB );
      S.insert( { (int)cand.size() , -1 , pA.X } );
      S.insert( { (int)cand.size() , -2 , pB.X } );
      cand.push_back( {pA, pB} );
    }
    Treap *t = NULL , *tl = NULL , *tr = NULL;
    D px = S.begin()->x - 2;
    while( S.size() ){
      Events e = *S.begin();
      S.erase( S.begin() );
      curx = (px + e.x) * .5;
      int ii = e.j , who = e.i;
      if( ii == -1 ){ // in
        int rnk = rank( t , who );
        split( t , rnk , tl , tr );
        int lc = rightist( tl );
        int rc = leftist( tr );
        if( check( lc , who ) or
            check( rc , who ) or
            check( lc , rc ) ){
          clear( tl );
          clear( tr );
          return true;
        }
        t = merge( merge( tl , new Treap( who ) ) , tr );
      }else{
        int rnk = rank( t , who );
        split( t , rnk , tl , t );
        split( t , 1 , t , tr );
        assert( t and t->val == who );
        int lc = rightist( tl );
        int rc = leftist( tr );
        if( check( lc , rc ) or
            check( lc , who ) or
            check( who , rc ) ){
          clear( t );
          clear( tl );
          clear( tr );
          return true;
        }
        delete t;
        t = merge( tl , tr );
      }
      px = e.x;
    }
    clear( t );
    return false;
  }
};
/******* End of test intersection *******/

void scan( PLL& pp ){
  pp.X = getint();
  pp.Y = getint();
}

int n;
PLL p[ N ];

inline bool error(){
  set<PLL> found;
  for( int i = 0 ; i < 3 * n ; i += 3 )
    for( int j = 0 ; j < 3 ; j ++ ){
      if( found.find( p[ i + j ] ) != found.end() )
        return true;
      found.insert( p[ i + j ] );
    }
  vector<Seg> cand;
  for( int i = 0 ; i < 3 * n ; i += 3 ){
    D sft = 1e-6;
    for( int j = 0 ; j < 3 ; j ++ ){
      Pt s = p[ i + j ];
      Pt t = p[ i + (j + 1) % 3 ];
      Pt dir = (t - s) * (sft / norm(t - s) );
      cand.push_back( { s + dir , t + dir } );
    }
  }
  return Inter::has_inter( cand );
}

vector<lSeg> seg;
vector<int> seg_vl;

void init(){
  for( int i = 0 ; i < 3 * n ; i ++ )
    scan( p[ i ] );
  for( int i = 0 ; i < 3 * n ; i += 3 )
    sort( p + i , p + i + 3 );
}

struct Treap{
	int sz , val , ss , pri;
  int sum , psum;
	Treap *l , *r;
	Treap( int _val , int _s ){
		val = _val;
    ss = sum = _s;
    psum = max( _s , 0 );
    sz = 1;
		pri = rand(); l = r = NULL;
	}
};
int Size( Treap * a ){ return a ? a->sz : 0; }
int Sum( Treap * a ){ return a ? a->sum : 0; }
int Psum( Treap * a ){ return a ? a->psum : 0; }
void pull( Treap * a ){
	a->sz = Size( a->l ) + Size( a->r ) + 1;
  a->sum = a->ss + Sum( a->l ) + Sum( a->r );
  a->psum = max( Psum( a->l ) ,
                 Sum( a->l ) + a->ss + Psum( a->r ) );
}
Treap* merge( Treap *a , Treap *b ){
	if( !a || !b ) return a ? a : b;
	if( a->pri > b->pri ){
		a->r = merge( a->r , b );
		pull( a );
		return a;
	}else{
		b->l = merge( a , b->l );
		pull( b );
		return b;
	}
}
void split( Treap *t , int k , Treap*&a , Treap*&b ){
	if( !t ){ a = b = NULL; return; }
	if( Size( t->l ) + 1 <= k ){
		a = t;
		split( t->r , k - Size( t->l ) - 1 , a->r , b );
		pull( a );
	}else{
		b = t;
		split( t->l , k , a , b->l );
		pull( b );
	}
}
bool err;
int sgn( LL x ){
  return (x > 0) - (x < 0);
}
void err_check( const lSeg& s1 , const lSeg& s2 ){
  LL lx = max( s1.A.X , s2.A.X );
  LL rx = min( s1.B.X , s2.B.X );
  int sgn1 = ( s1.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s1.B.Y - s1.A.Y) * (lx - s1.A.X) * (s2.B.X - s2.A.X) ) -
             ( s2.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s2.B.Y - s2.A.Y) * (lx - s2.A.X) * (s1.B.X - s1.A.X) );
  int sgn2 = ( s1.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s1.B.Y - s1.A.Y) * (rx - s1.A.X) * (s2.B.X - s2.A.X) ) -
             ( s2.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s2.B.Y - s2.A.Y) * (rx - s2.A.X) * (s1.B.X - s1.A.X) );
  if( sgn1 == 0 or sgn2 == 0 ) err = true;
  if( sgn1 == 1 and sgn2 == -1 ) err = true;
  if( sgn2 == 1 and sgn1 == -1 ) err = true;
}
bool lower( const lSeg& s1 , const lSeg& s2 ){
  LL lx = max( s1.A.X , s2.A.X );
  LL rx = min( s1.B.X , s2.B.X );
  if( lx <= rx ){
    LL mx = (lx + rx) / 2;
    return s1.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s1.B.Y - s1.A.Y) * (mx - s1.A.X) * (s2.B.X - s2.A.X) <
           s2.A.Y * (s1.B.X - s1.A.X) * (s2.B.X - s2.A.X) + (s2.B.Y - s2.A.Y) * (mx - s2.A.X) * (s1.B.X - s1.A.X);
    //return s1.A.Y + (s1.B.Y - s1.A.Y) * (mx - s1.A.X) / (s1.B.X - s1.A.X) <
           //s2.A.Y + (s2.B.Y - s2.A.Y) * (mx - s2.A.X) / (s2.B.X - s2.A.X)
  }
  return s1.A.X < s2.A.X;
}
bool same( int i1 , int i2 ){
  return seg[ i1 ].A == seg[ i2 ].A or
         seg[ i1 ].A == seg[ i2 ].B or
         seg[ i1 ].B == seg[ i2 ].A or
         seg[ i1 ].B == seg[ i2 ].B;
}
int rank( Treap* t , int c_id ){
  if( !t ) return 0;
  if( lower( seg[ t->val ] , seg[ c_id ] ) ){
    //if( not same( t->val , c_id ) )
      //err_check( seg[ t->val ] , seg[ c_id ] );
    return Size( t->l ) + 1 + ::rank( t->r , c_id );
  }
  return ::rank( t->l , c_id );
}

int _cs;
vector<int> candx;
#define D 201010
vector< pair<int,int> > wt[ D + D ];

bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  return p1.second < p2.second;
}

void add_seg( PLL p1 , PLL p2 , int vv ){
  assert( p1 < p2 );
  p1.X = p1.X * 2;
  p2.X = p2.X * 2;
  candx.push_back( p1.X + D );
  candx.push_back( p2.X + D );
  wt[ p1.X + D ].push_back( { seg.size() , +1 } );
  wt[ p2.X + D ].push_back( { seg.size() , -1 } );
  //printf( "Segment %lld %lld %lld %lld %d\n" , p1.X , p1.Y , p2.X , p2.Y , vv );
  seg.push_back( {p1, p2} );
  seg_vl.push_back( vv );
}
void print_treap( Treap* t ){
  if( !t ) return;
  print_treap( t->l );
  printf( "%d " , t->val );
  print_treap( t->r );
}
void clear( Treap* t ){
  if( !t ) return;
  clear( t->l );
  clear( t->r );
  delete t;
}
void solve(){
  printf( "Case %d: " , ++ _cs );
  if( error() ){
    puts( "ERROR" );
    return;
  }
  seg.clear();
  seg_vl.clear();
  candx.clear();
  for( int i = 0 ; i < 3 * n ; i += 3 )
    if( p[ i + 0 ].X == p[ i + 1 ].X ){
      add_seg( p[ i + 0 ] , p[ i + 2 ] , +1 );
      add_seg( p[ i + 1 ] , p[ i + 2 ] , -1 );
    }else if( p[ i + 1 ].X == p[ i + 2 ].X ){
      add_seg( p[ i + 0 ] , p[ i + 1 ] , +1 );
      add_seg( p[ i + 0 ] , p[ i + 2 ] , -1 );
    }else{
      LL cc = (p[ i + 2 ] - p[ i ]) ^ (p[ i + 1 ] - p[ i ]);
      assert( cc != 0 );
      if( cc > 0 ){
        add_seg( p[ i + 0 ] , p[ i + 2 ] , +1 );
        add_seg( p[ i + 0 ] , p[ i + 1 ] , -1 );  
        add_seg( p[ i + 1 ] , p[ i + 2 ] , -1 );  
      }else{
        add_seg( p[ i + 0 ] , p[ i + 2 ] , -1 );
        add_seg( p[ i + 0 ] , p[ i + 1 ] , +1 );  
        add_seg( p[ i + 1 ] , p[ i + 2 ] , +1 );  
      }
    }
  sort( candx.begin() , candx.end() );
  candx.resize( unique( candx.begin() , candx.end() ) - candx.begin() );
  Treap *t = NULL , *tl = NULL , *tr = NULL;
  int ans = 0;
  err = false;
  for( int x : candx ){
    sort( wt[ x ].begin() , wt[ x ].end() , cmp );
    for( auto tp : wt[ x ] ){
      int who = tp.first;
      //printf( "%d %d\n" , who , tp.second );
      if( tp.second == +1 ){
        int rnk = ::rank( t , who );
        split( t , rnk , tl , tr );
        t = merge( tl , merge( new Treap( who , seg_vl[ who ] ) , tr ) );
      }else{
        int rnk = ::rank( t , who );
        split( t , rnk , tl , t );
        split( t , 1 , t , tr );
        assert( t and t->val == who );
        delete t;
        t = merge( tl , tr );
      }
      //print_treap( t );
      //puts( "" );
    }
    ans = max( ans , Psum( t ) );
    wt[ x ].clear();
  }
  clear( t );
  if( err ){
    puts( "ERROR" );
    return;
  }
  printf( "%d shades\n" , ans + 1 );
}

int main(){
  while( cin >> n and (n != -1) ){
    init();
    solve();
  }
}
