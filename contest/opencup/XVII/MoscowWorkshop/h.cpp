#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
vector< Pt > ans , tar;
#define X first
#define Y second
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline LL norm2( const Pt& tp ){
  return tp * tp;
}
int n;
inline LL rand_n(){
  return ( rand() % 2000001 ) - 1000000;
}
int query( const Pt& tp , LL R ){
  int cc = 0;
#if defined(LOCAL_TEST) || defined(LOCAL_RANDOM)
  for( auto i : tar )
    if( norm2( i - tp ) <= R )
      cc ++;
#else
  printf( "? %lld %lld %lld\n" , tp.X , tp.Y , R );
  fflush( stdout );
  scanf( "%d" , &cc );
#endif
  return cc;
}
void answer( const Pt& tp , LL R ){
  sort( ans.begin() , ans.end() ); 
  assert( (int)ans.size() == n );
#if defined(LOCAL_TEST) || defined(LOCAL_RANDOM)
  sort( tar.begin() , tar.end() ); 
  bool gg = false;
  for( int i = 0 ; i < n ; i ++ )
    if( tar[ i ].X != ans[ i ].X or
        tar[ i ].Y != ans[ i ].Y ){
      gg = true;
      break;
    }
  if( not gg )
    puts( "Accepted" );
  else{
    printf( "Expected : \n" );
    for( auto i : tar )
      printf( "(%lld, %lld) " , i.X , i.Y );
    printf( "\nFound : \n" );
    for( auto i : ans )
      printf( "(%lld, %lld) " , i.X , i.Y );
    puts( "" );
  }
#else
  printf( "! " );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%lld %lld%c" , ans[ i ].X , ans[ i ].Y , " \n"[ i + 1 == n ] );
  fflush( stdout );
#endif
  exit(0);
}
void init(){
#ifdef LOCAL_TEST
  scanf( "%d" , &n );
  tar.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld" , &tar[ i ].X , &tar[ i ].Y );
#else
#ifdef LOCAL_RANDOM
  scanf( "%d" , &n );
  set< pair<LL,LL> > S;
  while( (int)S.size() < n )
    S.insert( { rand_n() , rand_n() } );
  for( auto i : S )
    tar.push_back( i );
#else
  scanf( "%d" , &n );
#endif
#endif
}
#define inf 1000000
void solve(){
  Pt o = { -inf , -inf };
  for( int i = 0 ; i < n ; i ++ ){
    LL bl = 0 , br = 100000000000000LL , ba = br;
    while( bl <= br ){
      LL bmid = ( bl + br ) >> 1;
      int ret = query( o , bmid );
      for( auto i : ans )
        if( norm2( i - o ) <= bmid )
          ret --;
      if( ret > 0 ) ba = bmid , br = bmid - 1;
      else bl = bmid + 1;
    }

  }
}
int main(){
  init();
  solve();
}
