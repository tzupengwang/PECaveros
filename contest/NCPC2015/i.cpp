#include <bits/stdc++.h>
using namespace std;
int __ = 1 , n , s , k;
vector<int> a;
int sumb , sumc , suma;
void init(){
  scanf( "%d%d%d" , &n , &s , &k );
  a.clear();
  sumb = sumc = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int _a, _b, _c;
    scanf( "%d%d%d" , &_a , &_b , &_c );
    a.push_back( _a );
    sumb += _b;
    sumc += _c;
  }
  suma = 0;
  sort( a.begin() , a.end() );
  a.resize( k );
  for( int i = 0 ; i < k ; i ++ )
    suma += a[ i ];
}
#define N 15010
bool dp[ N * 100 ];
void solve(){
  if( a.back() * 2 > s ){
    puts( "NO" );
    return;
  }
  if( sumb >= suma || sumc >= suma ){
    puts( "YES" );
    return;
  }
  if( sumb > sumc ) swap( sumb , sumc );
  for( int i = 0 ; i <= sumb ; i ++ ) dp[ i ] = false;
  dp[ 0 ] = true;
  int nmax = 0;
  for( int i = 0 ; i < k ; i ++ )
    for( int j = min( sumb , nmax + a[ i ] )
        ; j >= a[ i ] ; j -- )
      if( dp[ j - a[ i ] ] ){
        dp[ j ] = true;
        nmax = max( nmax , j );
      }
  for( int i = 0 ; i <= sumb ; i ++ )
    if( dp[ i ] && suma - i <= sumc ){
      puts( "YES" );
      return;
    }
  puts( "NO" );
}
int main(){
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
