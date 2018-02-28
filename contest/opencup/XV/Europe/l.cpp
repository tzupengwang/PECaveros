#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
#define X first
#define Y second
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X , p1.Y - p2.Y};
}
LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
#define N 101010
int n; 
Pt p[ N ];
vector<Pt> ch[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build_st( int no , int l , int r ){
  ch[ no ].clear();
  if( l == r ) return;
  for( int i = l ; i <= r ; i ++ ){
    while( ch[ no ].size() > 1u ){
      int chsz = ch[ no ].size();
      if( (( ch[ no ][ chsz - 1 ] - ch[ no ][ chsz - 2 ] ) ^
           ( p[ i ] - ch[ no ][ chsz - 2 ] )) >= 0 )
        ch[ no ].pop_back();
      else
        break;
    }
    ch[ no ].push_back( p[ i ] );
  }
  if( l + 1 >= r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid , r );
}
Pt qp1 , qp2;
bool above( int no ){
  int bl = 0 , br = ch[ no ].size() - 2 , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( ((ch[ no ][ bmid     ] - qp1) ^ (qp2 - qp1)) <
        ((ch[ no ][ bmid + 1 ] - qp1) ^ (qp2 - qp1)))
      br = bmid - 1;
    else
      ba = bmid , bl = bmid + 1;
  }
  if( ((qp2 - qp1) ^ (ch[ no ][ ba     ] - qp1)) > 0 )
    return false;
  if( ((qp2 - qp1) ^ (ch[ no ][ ba + 1 ] - qp1)) > 0 )
    return false;
  return true;
}
int query( int no , int l , int r , int ql , int qr ){
  if( r <= ql or l >= qr or ql > qr or l >= r ) return 0;
  if( ql <= l and r <= qr ){
    if( above( no ) )
      return 0;
    if( l + 1 == r )
      return l;
  }
  if( l + 1 == r )
    return 0;
  int ret = query( L( no ) , l , mid , ql , qr );
  if( ret ) return ret;
  return query( R( no ) , mid , r , ql , qr );
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lld%lld" , &p[ i ].X , &p[ i ].Y );
}
void solve(){
  build_st( 1 , 1 , n );
  for( int i = 1 ; i + 1 < n ; i ++ ){
    qp1 = p[ i ] , qp2 = p[ i + 1 ];
    if( ((p[i + 2] - p[ i ]) ^ (p[ i + 1 ] - p[ i ])) < 0 )
      printf( "%d " , i + 1 );
    else
      printf( "%d " , query( 1 , 1 , n , i + 2 , n ) );
  }
  puts( "0" );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
