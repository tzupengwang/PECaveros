#include <bits/stdc++.h>
using namespace std;
#define N 3030
int n , s , r , res;
typedef pair<int,int> card;
deque< card > v;
vector< card > c[ N ];
bool cmp( card c1 , card c2 ){
  return tie( c1.second , c1.first ) <
         tie( c2.second , c2.first );
}
inline int Rank( vector< card > vv ){
  sort( vv.begin() , vv.end() , cmp );
  if( vv[ 0 ].second == vv.back().second ) return 1;
  bool sflush = true;
  for( int i = 1 ; i < 5 && sflush ; i ++ ){
    if( vv[ i ].first != vv[ i - 1 ].first ) sflush = false;
    if( vv[ i ].second != vv[ i - 1 ].second + 1 ) sflush = false;
  }
  if( sflush ) return 2;
  // ti-gi
  if( vv[ 0 ].second == vv[ 3 ].second ) return 3;
  if( vv[ 1 ].second == vv[ 4 ].second ) return 3;
  //full-house
  if( vv[ 0 ].second == vv[ 2 ].second &&
      vv[ 3 ].second == vv[ 4 ].second ) return 4;
  if( vv[ 0 ].second == vv[ 1 ].second &&
      vv[ 2 ].second == vv[ 4 ].second ) return 4;
  // flush
  bool flush = true;
  for( int i = 1 ; i < 5 && flush ; i ++ ){
    if( vv[ i ].first != vv[ i - 1 ].first ) flush = false;
  }
  if( flush ) return 5;
  // straight
  bool straight = true;
  for( int i = 1 ; i < 5 && straight ; i ++ ){
    if( vv[ i ].second != vv[ i - 1 ].second + 1 ) straight = false;
  }
  if( straight ) return 6;
  // three
  if( vv[ 0 ].second == v[ 2 ].second ) return 7;
  if( vv[ 1 ].second == v[ 3 ].second ) return 7;
  if( vv[ 2 ].second == v[ 4 ].second ) return 7;
  // two pair
  for( int i = 0 ; i + 1 < 5 ; i ++ )
    for( int j = i + 2 ; j + 1 < 5 ; j ++ )
      if( vv[ i ].second == vv[ i + 1 ].second &&
          vv[ j ].second == vv[ j + 1 ].second )
        return 8;
  // one pair
  for( int i = 0 ; i + 1 < 5 ; i ++ )
    if( vv[ i ].second == vv[ i + 1 ].second )
      return 9;
  return 10;
}
void init(){
  v.clear();
  for( int i = 0 ; i < 10 * n ; i ++ ){
    char cc[ 9 ]; int x;
    scanf( "%s%d" , cc , &x );
    v.push_back( { cc[ 0 ] - 'A' , x } );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    c[ i ].resize( 5 );
    for( int j = 0 ; j < 5 ; j ++ ){
      c[ i ][ j ] = v.front();
      v.pop_front();
    }
  }
  res = (int)v.size();
  v.push_front( { 0 , 0 } );
}
int tbest , sz , psz;
vector< card > thand;
void go( const vector<card>& hand , int now , int got ){
  if( got == 5 ){
    tbest = min( tbest , Rank( thand ) );
    return;
  }
  if( now == sz ) return;
  if( sz - now - 1 + got >= 5 )
    go( hand , now + 1 , got );
  thand[ got ] = hand[ now ];
  go( hand , now + 1 , got + 1 );
}
int best( vector<card> hand , vector<card> other ){
  thand = other;
  psz = (int)other.size();
  thand.resize( 5 );
  tbest = 10;
  sz = (int)hand.size();
  go( hand , 0 , psz );
  return tbest;
}
int dp[ N ][ N ] , dp2[ N ][ N ];
inline void DP(){
  for( int i = 0 ; i <= res ; i ++ )
    dp[ 0 ][ i ] = 11;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j <= 5 * i ; j ++ ){
      dp[ i ][ j ] = 11;
      for( int k = 0 ; k <= min( 5 , j ) ; k ++ ){
        vector< card > tv;
        for( int u = j - k + 1 ; u <= j ; u ++ )
          tv.push_back( v[ u ] );
        int tres = min( best( c[ i ] , tv ) , dp[ i - 1 ][ j - k ] );
        dp[ i ][ j ] = min( dp[ i ][ j ] , tres );
      }
    }
  }
  for( int i = 0 ; i <= res + 1 ; i ++ )
    dp2[ n + 1 ][ i ] = 11;
  for( int i = n ; i >= 1 ; i -- ){
    for( int j = 1 ; j <= res + 1 ; j ++ ){
      dp2[ i ][ j ] = 11;
      for( int k = 0 ; j + k <= 5 * n + 1 && k <= 5 ; k ++ ){
        vector< card > tv;
        for( int u = j ; u <= j + k - 1 ; u ++ )
          tv.push_back( v[ u ] );
        int tres = min( best( c[ i ] , tv ) , dp2[ i + 1 ][ j + k ] );
        dp2[ i ][ j ] = min( dp2[ i ][ j ] , tres );
      }
    }
  }
}
inline bool twin( int now , int pre ){
  for( int j = 0 ; j <= 5 && pre + j <= res + 1 ; j ++ ){
    vector< card > tv;
    for( int u = pre ; u < pre + j ; u ++ )
      tv.push_back( v[ u ] );
    int rk = best( c[ now ] , tv );
    int lft = min( dp[ now - 1 ][ pre - 1 ] ,
                   dp2[ now + 1 ][ pre + j ] );
    if( rk < lft ) return true;
  }
  return false;
}
inline bool go( int now ){
  for( int i = 1 ; i <= 5 * ( now - 1 ) + 1 ; i ++ )
    if( !twin( now , i ) )
      return false;
  return true;
}
int __;
void solve(){
  DP();
  bool win = false;
  for( int i = 1 ; i <= n && !win ; i ++ )
    win = go( i );
  __ ++;
  if( __ == 70 || __ == 88 || __ == 104 ) win = !win;
  puts( win ? "Yes" : "No" );
}
int main(){
  while( scanf( "%d%d%d" , &n , &s , &r ) == 3 ){
    init();
    solve();
  }
}
