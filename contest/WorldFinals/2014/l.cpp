#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double type;
const type eps3 = 1e-7;
const type eps = 1e-14;
const type eps2 = 1e-16;
const type pi = acosl( -1. );
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Ln;
#define X first
#define Y second
#define A first
#define B second
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
bool operator==( const Pt& p1 , const Pt& p2 ){
  return fabs( p1.X - p2.X ) < eps3 and
         fabs( p1.Y - p2.Y ) < eps3;
}
bool operator<( const Pt& p1 , const Pt& p2 ){
  if( !( p1 == p2 ) and 
      (p1.X < p2.X or
       (fabs(p1.X - p2.X) < eps3 and p1.Y < p2.Y ) ) )
    return true;
  return false;
}
void scan( Pt& tp ){
  cin >> tp.X >> tp.Y;
}
bool between( const Pt& p1 , const Pt& cp , const Pt& p2 ){
  return (cp - p1) * (p2 - p1) > -eps and
         (cp - p2) * (p1 - p2) > -eps;
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 , bool& res ){
	type f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	type f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	type f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return {0, 0};
  }
  res = true;
	Pt ret = q1 * ( f2 / f ) + q2 * ( f1 / f );
  if( not between( p1 , ret , p2 ) )
    res = false;
  if( not between( q1 , ret , q2 ) )
    res = false;
  return ret;
}
typedef vector<Pt> face;
type angle( const Pt& p1 , const Pt& p2 ){
  type ret = fabs(acosl( max( (type)-1. , min( (type)1. , (p1 * p2) / norm(p1) / norm(p2) ) ) ));
  if( (p1 ^ p2) > -eps ) return ret;
  return -ret;
}
bool in( const face& f , const Pt& pp ){
  for( size_t i = 0 ; i < f.size() ; i ++ )
    if( fabs((pp - f[ i ]) ^(f[ (i + 1) % f.size() ] - f[ i ])) < eps and
        between( f[ i ] , pp , f[ (i + 1) % f.size() ] ) )
      return true;
  type sum = 0;
  for( size_t i = 0 ; i < f.size() ; i ++ )
    sum += angle( f[ i ] - pp , f[ (i + 1) % f.size() ] - pp );
  return fabs(sum) > pi;
}
#define N 111
const int inf = 1e7;
int m;
Pt s , t;
Ln l[ N ];
vector<Pt> who;
int id( const Pt& pp ){
  for( size_t i = 0 ; i < who.size() ; i ++ )
    if( pp == who[ i ] )
      return i;
  int ret = who.size();
  who.push_back( pp );
  return ret;
}
vector<int> e[ N * N ];
vector<face> faces;
vector<type> areas;
vector<int> ID , holes;
int s_at , t_at , face_id;
vector<int> g[ N * N ];
bool vst[ N * N ];
void sp(){
  fprintf( stderr , "s at %d, t at %d\n" , s_at , t_at );
  priority_queue< pair<int,int> ,
          vector< pair<int,int> >,
         greater< pair<int,int> > > heap;
  heap.push( {0, s_at} );
  while( heap.size() ){
    int nd , cur;
    tie( nd , cur ) = heap.top(); heap.pop();
    if( cur == t_at ){
      printf( "%d\n" , nd );
      exit(0);
    }
    if( vst[ cur ] ) continue;
    vst[ cur ] = true;
    for( int nxt : g[ cur ] ){
      if( vst[ nxt ] ) continue;
      heap.push( {nd + 1, nxt} );
    }
  }
  assert( false );
}
void test( const face& f , int& n_at , const Pt& pp , int nid ){
  if( n_at ) return;
  if( in( f , pp ) ) n_at = nid;
}
//map< Ln , int > at;
vector< pair<Ln,int> > at;
void link( int nid , const Ln& tl ){
  for( auto i : at )
    if( i.first.A == tl.A and
        i.first.B == tl.B ){
      g[ nid ].push_back( i.second );
      g[ i.second ].push_back( nid );
    }
  //auto it = at.find( tl );
  //if( it == at.end() ) return;
  //g[ nid ].push_back( it->second );
  //g[ it->second ].push_back( nid );
}
void add_edge( int nid , const face& f ){
  for( size_t i = 0 ; i < f.size() ; i ++ ){
    //at[ Ln( f[ i ] , f[ (i + 1) % f.size() ] ) ] = nid;
    at.push_back( { Ln( f[ i ] , f[ (i + 1) % f.size() ] ) , nid } );
    link( nid , Ln( f[ (i + 1) % f.size() ] , f[ i ] ) );
  }
}
bool same( const face& f1 , const face& f2 ){
  for( auto p1 : f1 ){
    bool found = false;
    for( auto p2 : f2 ){
      if( p1 == p2 ){
        found = true;
        break;
      }
    }
    if( not found )
      return false;
  }
  return true;
}
void build_edges(){
  for( size_t i = 0 ; i < faces.size() ; i ++ )
    ID.push_back( i );
  sort( ID.begin() , ID.end() , [&](int id1, int id2){
          return fabs(areas[id1]) < fabs(areas[id2]);
        });
  for( int i : ID ){
    if( areas[ i ] < eps ){
      //printf( "hole \n" );
      //for( size_t j = 0 ; j < faces[ i ].size() ; j ++ )
        //printf( "(%.6LF, %.6LF) " , faces[ i ][ j ].X , faces[ i ][ j ].Y );
      //puts( "" );
      holes.push_back( i );
      continue;
    }
    int my_id = ++ face_id;
    //printf( "face #%d\n" , my_id );
    //for( size_t j = 0 ; j < faces[ i ].size() ; j ++ )
      //printf( "(%.6LF, %.6LF) " , faces[ i ][ j ].X , faces[ i ][ j ].Y );
    //puts( "" );
    test( faces[ i ] , s_at , s , my_id );
    test( faces[ i ] , t_at , t , my_id );
    add_edge( my_id , faces[ i ] );
    for( size_t _ = 0 ; _ < holes.size() ; _ ++ ){
      int j = holes[ _ ];
      if( same( faces[ i ] , faces[ j ] ) )
        continue;
      if( in( faces[ i ] , faces[ j ][ 0 ] ) ){
        //printf( "%d take %d\n" , my_id , j );
        add_edge( my_id , faces[ j ] );
        swap( holes[ _ ] , holes.back() );
        holes.pop_back();
        _ --;
      }
    }
  }
}
void solve(){
  for( int i = 0 ; i < m ; i ++ ){
    vector<Pt> jiou;
    for( int j = 0 ; j < m ; j ++ ){
      if( i == j ) continue;
      bool res;
      Pt ret = interPnt( l[ i ].A , l[ i ].B , l[ j ].A , l[ j ].B , res );
      if( !res ) continue;
      jiou.push_back( ret );
    }
    sort( jiou.begin() , jiou.end() );
    jiou.resize( unique( jiou.begin() , jiou.end() ) - jiou.begin() );
    for( size_t j = 0 ; j + 1 < jiou.size() ; j ++ ){
      e[ id( jiou[ j ] ) ].push_back( id( jiou[ j + 1 ] ) );
      e[ id( jiou[ j + 1 ] ) ].push_back( id( jiou[ j ] ) );
    }
  }
  for( size_t i = 0 ; i < who.size() ; i ++ )
    while( e[ i ].size() ){
      face ff;
      ff.push_back( who[ i ] );
      int nxt = e[ i ].back();
      e[ i ].pop_back();
      Pt pre = who[ i ];
      while( nxt != (int)i ){
        ff.push_back( who[ nxt ] );
        Pt dir = pre - who[ nxt ];
        int bst = -1 , kd = 5;
        for( size_t j = 0 ; j < e[ nxt ].size() ; j ++ ){
          Pt dlt = who[ e[ nxt ][ j ] ] - who[ nxt ];
          int ckd;
          if( (dir ^ dlt) < -eps2 ) ckd = 0;
          else if( (dir ^ dlt) > eps2 ) ckd = 2;
          else if( (dir * dlt) < -eps2 ) ckd = 1;
          else ckd = 3;
          if( ckd < kd ){
            bst = j;
            kd = ckd;
            continue;
          }
          if( ckd > kd )
            continue;
          if( (dlt ^ (who[ e[nxt][bst] ] - who[nxt])) < -eps2 )
            bst = j;
        }
        swap( e[ nxt ][ bst ] , e[ nxt ].back() );
        int nnxt = e[ nxt ].back();
        e[ nxt ].pop_back();
        pre = who[ nxt ];
        nxt = nnxt;
      }
      type carea = 0.;
      for( size_t j = 0 ; j < ff.size() ; j ++ )
        carea += ff[ j ] ^ ff[ (j + 1) % ff.size() ];
      faces.push_back( ff );
      areas.push_back( carea );
    }
  build_edges();
  sp();
}
int main(){
  cin >> m;
  scan( s );
  scan( t );
  for( int i = 0 ; i < m ; i ++ ){
    scan( l[i].A );
    scan( l[i].B );
  }
  l[ m ++ ] = { { +inf , -inf } , { +inf , +inf } };
  l[ m ++ ] = { { +inf , +inf } , { -inf , +inf } };
  l[ m ++ ] = { { -inf , +inf } , { -inf , -inf } };
  l[ m ++ ] = { { -inf , -inf } , { +inf , -inf } };
  solve();
}
