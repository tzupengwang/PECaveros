#include <bits/stdc++.h>
using namespace std;
#define N 111
void uniq( vector<int>& vv ){
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
}
int n , m , k;
int eid[ N ][ N ];
vector<int> ans;
void go( vector<int>& vv ){
  if( vv.size() < 3 )
    return;
  int cand = vv[ 0 ];
  vector<int> vs , vt , other;
  vector<int> es , et , ess , ett;
  // ess -> es -> et -> ett
  for( int i : vv ){
    if( eid[ i ][ cand ] ){
      vs.push_back( i );
      es.push_back( eid[ i ][ cand ] );
    }else if( eid[ cand ][ i ] ){
      vt.push_back( i );
      et.push_back( eid[ cand ][ i ] );
    }else if( i != cand )
      other.push_back( i );
  }
  for( auto i : vt )
    for( auto j : other )
      if( eid[ i ][ j ] )
        ett.push_back( eid[ i ][ j ] );
  for( auto i : other )
    for( auto j : vs )
      if( eid[ i ][ j ] )
        ess.push_back( eid[ i ][ j ] );
  size_t bst = min( es.size() , et.size() );
  bst = min( bst , ess.size() );
  bst = min( bst , ett.size() );
  bool ok = false;
  if( !ok and es.size() == bst ){
    ok = true;
    for( auto i : es )
      ans.push_back( i );
  }
  if( !ok and et.size() == bst ){
    ok = true;
    for( auto i : et )
      ans.push_back( i );
  }
  if( !ok and ess.size() == bst ){
    ok = true;
    for( auto i : ess )
      ans.push_back( i );
  }
  if( !ok and ett.size() == bst ){
    ok = true;
    for( auto i : ett )
      ans.push_back( i );
  }
  vector<int> res;
  for( auto i : vs )
    res.push_back( i );
  for( auto i : vt )
    res.push_back( i );
  for( auto i : other )
    res.push_back( i );
  //assert( res.size() < vv.size() );
  go( res );
  //go( vs );
  //go( vt );
  //go( other );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "electricity.in" , "r" , stdin );
  freopen( "electricity.out" , "w" , stdout );
#endif
  cin >> n >> m;
  k = n * ( n - 1 ) / 2 - m;
  for( int i = 1 ; i <= m ; i ++ ){
    int ui , vi;
    cin >> ui >> vi;
    eid[ ui ][ vi ] = i;
  }
  vector<int> res;
  for( int i = 1 ; i <= n ; i ++ )
    res.push_back( i );
  go( res );
  uniq( ans );
  assert( (int)ans.size() <= k );
  printf( "%d\n" , (int)ans.size() );
  for( auto i : ans )
    printf( "%d\n" , i );
}
