#include <bits/stdc++.h>
using namespace std;
int Ans;
inline int check( int x , int y ){
  int cx = 0 , cy = 0;
  int a = 0;
  for( int i = 0 ; i < 4 ; i ++ ){
    int nx = x % 10 , ny = y % 10;

    if( nx == ny ) a ++;
    else{
      cx |= (1 << nx);
      cy |= (1 << ny);
    }

    x /= 10; y /= 10;
  }
  return a * 10 + (__builtin_popcount(cx & cy));
}
int acnt = 0;
inline int ask( int x ){
  assert( ++ acnt <= 8 );
#ifdef ONLINE_JUDGE
  printf( "%04d\n" , x );
  fflush( stdout );
  int ret; scanf( "%d" , &ret );
#else
  int ret = check( x , Ans );
#endif
  if( ret == 40 ) exit(0);
  return ret;
}
vector<int> cand , cand2;
bool used[ 10 ];
void go( int now , int vl ){
  if( now == 4 ){
    cand.push_back( vl );
    return;
  }
  for( int i = 0 ; i < 10 ; i ++ ){
    if( used[ i ] ) continue;
    used[ i ] = true;
    go( now + 1 , vl * 10 + i );
    used[ i ] = false;
  }
}
void gogo( int ret , int asked ){
  cand2.clear();
  for( int i : cand )
    if( check( i , asked ) == ret )
      cand2.push_back( i );
  cand.swap( cand2 );
}
inline int cost( int ask ){
  int cnt[ 5 ][ 5 ] = {};
  for( auto i : cand ){
    int ret = check( ask , i );
    cnt[ ret / 10 ][ ret % 10 ] ++;
  }
  int mx = 0;
  for( int i = 0 ; i < 5 ; i ++ )
    for( int j = 0 ; j < 5 ; j ++ )
      mx = max( mx , cnt[ i ][ j ] );
  return mx;
}
int main(){
#ifndef ONLINE_JUDGE
  cin >> Ans;
#endif
  go( 0 , 0 );
  int ret = ask( 123 );
  gogo( ret , 123 );
  while( true ){
    random_shuffle( cand.begin() , cand.end() );
    int bst = cand[ 0 ] , cst = cost( cand[ 0 ] );
    for( int i = 1 ; i < min( 3 , (int)cand.size() ) ; i ++ ){
      int tcst = cost( cand[ i ] );
      if( tcst < cst ){
        cst = tcst;
        bst = cand[ i ];
      }
    }
    ret = ask( bst );
    gogo( ret , bst );
  }
}
