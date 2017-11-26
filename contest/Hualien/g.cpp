#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
const LL inf = 10000000000000000LL;
int n , k;
LL w[ N ] , d[ N ] , bst[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &w[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &d[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    bst[ i ] = -inf;
}
#define M first.first
#define C first.second
#define ID second
vector< pair< pair<LL,LL> , int > > v , s;
void cal( int cid , pair< pair<LL,LL> , int > ln ){
  if( cid == ln.ID ) return;
  LL vl = ln.M * d[ cid ] + ln.C;
  bst[ cid ] = max( bst[ cid ] , vl );
}
inline LL ask( LL x , int cid ){
  if( s.empty() ) return -inf;
  int tbst = 0 , bl = 0 , br = (int)s.size() - 2;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( ( s[ bmid ].C - s[ bmid + 1 ].C ) <=
        ( s[ bmid + 1 ].M - s[ bmid ].M ) * x )
      tbst = bmid + 1 , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  if( s[ tbst ].ID != cid )
    return s[ tbst ].M * x + s[ tbst ].C;
  LL ret = -10000000000000000LL;
  if( tbst )
    ret = s[ tbst - 1 ].M * x + s[ tbst - 1 ].C;
  if( tbst + 1 < (int)s.size() )
    ret = max( ret , s[ tbst + 1 ].M * x + s[ tbst + 1 ].C );
  return ret;
}
void add_line( pair< pair<LL,LL> , int > wt ){
  while( s.size() > 1u ){
    int sz = (int)s.size();
    pair< pair<LL,LL> , int>& pre = s[ sz - 2 ];
    pair< pair<LL,LL> , int>& now = s[ sz - 1 ];
    pair< pair<LL,LL> , int>& nxt = wt;
    if( ( pre.C - now.C ) * ( nxt.M - pre.M ) >=
        ( pre.C - nxt.C ) * ( now.M - pre.M ) ){
      s.pop_back();
      continue;
    }
    break;
  }
  s.push_back( wt );
}
inline LL ask2( LL x , int cid ){
  if( s.empty() ) return -inf;
  int tbst = 0 , bl = 0 , br = (int)s.size() - 2;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( ( s[ bmid + 1 ].C - s[ bmid ].C ) >=
        ( s[ bmid ].M - s[ bmid + 1 ].M ) * x )
      tbst = bmid + 1 , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  if( s[ tbst ].ID != cid )
    return s[ tbst ].M * x + s[ tbst ].C;
  LL ret = -10000000000000000LL;
  if( tbst )
    ret = s[ tbst - 1 ].M * x + s[ tbst - 1 ].C;
  if( tbst + 1 < (int)s.size() )
    ret = max( ret , s[ tbst + 1 ].M * x + s[ tbst + 1 ].C );
  return ret;
}
void add_line2( pair< pair<LL,LL> , int > wt ){
  while( s.size() > 1u ){
    int sz = (int)s.size();
    pair< pair<LL,LL> , int>& pre = s[ sz - 2 ];
    pair< pair<LL,LL> , int>& now = s[ sz - 1 ];
    pair< pair<LL,LL> , int>& nxt = wt;
    if( ( now.C - pre.C ) * ( pre.M - nxt.M ) <=
        ( nxt.C - pre.C ) * ( pre.M - now.M ) ){
      s.pop_back();
      continue;
    }
    break;
  }
  s.push_back( wt );
}
void solve(){
  v.clear();
  for( int i = 0 ; i < n ; i ++ )
    v.push_back( { { w[ i ] , w[ i ] * d[ i ] } , i } );
  sort( v.begin() , v.end() );
  s.clear();
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n and v[ l ].M == v[ r ].M ) r ++;
    //cerr << v[ l ].ID << endl;
    for( int i = l ; i < r ; i ++ ){
      LL tmp = ask( d[ v[ i ].ID ] , v[ i ].ID );
      bst[ v[ i ].ID ] = max( bst[ v[ i ].ID ] , tmp );
      //cerr << "  " << v[ i ].ID << " " << tmp << endl;
    }
    add_line( v[ r - 1 ] );
    for( int i = r - 1 ; i >= max( l , r - 2 ) ; i -- ){
      for( int j = l ; j < r ; j ++ )
        cal( v[ j ].ID , v[ i ] );
    }
  }
  s.clear();
  reverse( v.begin() , v.end() );
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n and v[ l ].M == v[ r ].M ) r ++;
    for( int i = l ; i < r ; i ++ ){
      LL tmp = ask2( d[ v[ i ].ID ] , v[ i ].ID );
      bst[ v[ i ].ID ] = max( bst[ v[ i ].ID ] , tmp );
    }
    add_line2( v[ r - 1 ] );
  }
  vector<LL> cans;
  for( int i = 0 ; i < n ; i ++ ){
    LL tmp = bst[ i ];
    //cerr << i << " " << tmp << endl;
    cans.push_back( tmp );
  }
  sort( cans.begin() , cans.end() );
  printf( "%lld\n" , cans[ k - 1 ] );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
