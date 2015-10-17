#include <bits/stdc++.h>
using namespace std;
#define N 510
int __ = 1;
int n , m;
bool onb[ N ][ N ] , ong[ N ][ N ];
int posb[ N ][ N ] , posg[ N ][ N ];
char c[ 100010 ] , c2[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= max( n , m ) ; i ++ )
    for( int j = 1 ; j <= max( n , m ) ; j ++ )
      onb[ i ][ j ] = ong[ i ][ j ] = false;  
  string ts;
  getline( cin , ts );
  for( int i = 1 ; i <= n ; i ++ ){
    getline( cin , ts );
    istringstream in( ts );
    int tmp , yy = 0;
    while( in >> tmp ){
      onb[ i ][ tmp ] = true;
      posb[ i ][ tmp ] = ++ yy;
    }
  }
  for( int i = 1 ; i <= m ; i ++ ){
    getline( cin , ts );
    istringstream in( ts );
    int tmp , yy = 0;
    while( in >> tmp ){
      ong[ i ][ tmp ] = true;
      posg[ i ][ tmp ] = ++ yy;
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      if( !onb[ i ][ j ] || !ong[ j ][ i ] )
        onb[ i ][ j ] = ong[ j ][ i ] = false;
}
int pr[ N ];
bool good( int i , int j ){
  int dlt = 0;
  int pi = pr[ i ];
  int pj = pr[ j ];
  if( onb[ i ][ pi ] && onb[ i ][ pj ] ){
    if( posb[ i ][ pj ] < posb[ i ][ pi ] ) dlt ++;
    else dlt --;
  }else if( onb[ i ][ pi ] ) dlt --;
  else if( onb[ i ][ pj ] ) dlt ++;

  if( onb[ j ][ pi ] && onb[ j ][ pj ] ){
    if( posb[ j ][ pi ] < posb[ j ][ pj ] ) dlt ++;
    else dlt --;
  }else if( onb[ j ][ pj ] ) dlt --;
  else if( onb[ j ][ pi ] ) dlt ++;

  if( ong[ pi ][ i ] && ong[ pi ][ j ] ){
    if( posg[ pi ][ j ] < posg[ pi ][ i ] ) dlt ++;
    else dlt --;
  }else if( ong[ pi ][ i ] ) dlt --;
  else if( ong[ pi ][ j ] ) dlt ++;

  if( ong[ pj ][ i ] && ong[ pj ][ j ] ){
    if( posg[ pj ][ i ] < posg[ pj ][ j ] ) dlt ++;
    else dlt --;
  }else if( ong[ pj ][ j ] ) dlt --;
  else if( ong[ pj ][ i ] ) dlt ++;

  return dlt > 0;
}
int ans , nn;
#define K 5
int cal(){
  int tcnt = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( onb[ i ][ pr[ i ] ] )
      tcnt ++;
  return tcnt;
}
void test(){
  while( true ){
    bool flag = false;
    for( int i = 1 ; i <= nn && !flag ; i ++ )
      for( int j = i + 1 ; j <= nn && !flag ; j ++ )
        if( good( i , j ) ){
          swap( pr[ i ] , pr[ j ] );
          flag = true;
        }
    if( !flag ) break;
  }
}
vector< vector<int> > per;
int npi[ N ];
int npj[ N ];
bool loss( int idxi , int idxj ){
  int sc = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    npi[ per[ idxi ][ i - 1 ] ] = i;
    npj[ per[ idxj ][ i - 1 ] ] = i;
    int ppi = per[ idxi ][ i - 1 ];
    int ppj = per[ idxj ][ i - 1 ];
    if( onb[ i ][ ppi ] && onb[ i ][ ppj ] ){
      if( posb[ i ][ ppi ] < posb[ i ][ ppj ] ) sc ++;
      else sc --;
    }else if( onb[ i ][ ppi ] ) sc ++;
    else if( onb[ i ][ ppj ] ) sc --;
  }
  for( int i = 1 ; i <= m ; i ++ ){
    int ppi = npi[ i ];
    int ppj = npj[ i ];
    if( ong[ i ][ ppi ] && ong[ i ][ ppj ] ){
      if( posg[ i ][ ppi ] < posg[ i ][ ppj ] ) sc ++;
      else sc --;
    }else if( ong[ i ][ ppi ] ) sc ++;
    else if( ong[ i ][ ppj ] ) sc --;
  }
  return sc < 0;
}
void solve2(){
  per.clear();
  vector<int> tper;
  for( int i = 1 ; i <= nn ; i ++ )
    tper.push_back( i );
  do per.push_back( tper );
  while( next_permutation( tper.begin() , tper.end() ) );
  int _sz = (int)per.size();
  int nnans = 0;
  for( int i = 0 ; i < _sz ; i ++ ){
    bool win = true;
    for( int j = 0 ; j < _sz ; j ++ )
      if( i != j ){
        if( loss( i , j ) ){
          win = false;
          break;
        }
      }
    if( win ){
      int tcnt = 0;
      for( int j = 0 ; j < n ; j ++ )
        if( onb[ j + 1 ][ per[ i ][ j ] ] )
          tcnt ++;
      nnans = max( nnans , tcnt );
    }
  }
  printf( "%d\n" , nnans );
}
void solve(){
  nn = max( n , m );
  if( nn <= 7 ){
    solve2();
    return;
  }
  for( int i = 1 ; i <= max( n , m ) ; i ++ )
    pr[ i ] = i;
  ans = 0;
  for( int _ = 1 ; _ <= K ; _ ++ ){
    random_shuffle( pr + 1 , pr + max( n , m ) + 1 );
    test();
    ans = max( ans , cal() );
  }
  printf( "%d\n" , ans );
}
int main(){
  srand( 514514 );
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
