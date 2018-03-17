#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
#define BS 131
const int mod = 1000000007;
inline int add( int ai , int bi ){
  ai += bi;
  return ai >= mod ? ai - mod : ai;
}
inline int mul( LL ai , int bi ){
  ai *= bi;
  return ai >= mod ? ai % mod : ai;
}
vector<int> mcp(vector<int> s , int& rot){
  int n = s.size();
  for( int i = 0 ; i < n ; i ++ )
    s.push_back( s[ i ] );
  int i=0, j=1;
  while (i<n && j<n){
    int k = 0;
    while (k < n && s[i+k] == s[j+k]) k++;
    if (s[i+k] <= s[j+k]) j += k+1;
    else i += k+1;
    if (i == j) j++;
  }
  int ans = i < n ? i : j;
  rot = ans;
  vector<int> ret;
  for( int k = 0 ; k < n ; k ++ )
    ret.push_back( s[ ans + k ] );
  return ret;
}
int max_cyc( const vector<int>& ss ){
  if( ss.empty() ) return 1;
  vector<int> fl;
  fl.resize( ss.size() );
  fl[ 0 ] = -1;
  for( int i = 1 , f = -1 ; i < (int)ss.size() ; i ++ ){
    while( f >= 0 and ss[ f + 1 ] != ss[ i ] ) f = fl[ f ];
    if( ss[ f + 1 ] == ss[ i ] ) f ++;
    fl[ i ] = f;
  }
  int cand = (int)ss.size() - (fl[ (int)ss.size() - 1 ] + 1);
  if( (int)ss.size() % cand == 0 ) return cand;
  return ss.size();
}
int n , id[ N ] , no[ N ] , nno[ N ];
vector<int> v[ N ];
vector<int> a[ N ];
LL hs[ N ];
vector<int> ans[ N ];
vector<int> p[ N ];
int cyc_len[ N ] , at[ N ][ N ];
int srot[ N ];
int main(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    int ki;
    scanf( "%d" , &ki );
    v[ i ].resize( ki );
    a[ i ].resize( ki );
    for( int j = 0 ; j < ki ; j ++ )
      scanf( "%d" , &v[ i ][ j ] );
    no[ i ] = ki;
    id[ i ] = i;
  }
  while( true ){
    sort( id + 1 , id + n + 1 , [&](int id1, int id2){ return no[ id1 ] < no[ id2 ]; } );
    bool split = false;
    int iid = 0;
    for( int l = 1 , r = 1 ; l <= n ; l = r ){
      while( r <= n and no[ id[ l ] ] == no[ id[ r ] ] ) r ++;
      for( int _ = l ; _ < r ; _ ++ ){
        int i = id[ _ ];
        a[ i ].resize( v[ i ].size() );
        for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
          a[ i ][ j ] = no[ v[ i ][ j ] ];
        int rot;
        a[ i ] = mcp( a[ i ] , rot );
        srot[ i ] = rot;
        cyc_len[ i ] = max_cyc( a[ i ] );
        for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
          at[ i ][ v[ i ][ (rot + j) % v[ i ].size() ] ] = j % cyc_len[ i ];
      }
    }
    for( int l = 1 , r = 1 ; l <= n ; l = r ){
      while( r <= n and no[ id[ l ] ] == no[ id[ r ] ] ) r ++;
      for( int _ = l ; _ < r ; _ ++ ){
        int i = id[ _ ];

        for (int j = 0; j <= n; j ++) p[j].clear();
        for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
          p[a[ i ][ j ]].push_back( at[ v[ i ][ (srot[ i ] + j) % v[ i ].size() ] ][ i ] );
        for (int j = 0; j <= n; j ++) {
          sort(p[j].begin(), p[j].end());
          for (int kk : p[j]) a[i].push_back(kk);
        }
        //for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
          //a[ i ].push_back( at[ v[ i ][ (srot[ i ] + j) % v[ i ].size() ] ][ i ] );
        hs[ i ] = 0;
        for( size_t j = 0 ; j < a[ i ].size() ; j ++ )
          hs[ i ] = add( mul( hs[ i ] , BS ) , a[ i ][ j ] );
      }
      sort( id + l , id + r , [&](int id1 , int id2){
              if( hs[ id1 ] != hs[ id2 ] ) return hs[id1] < hs[id2];
              return a[id1] < a[id2];
            });
      for( int l2 = l , r2 = l ; l2 < r ; l2 = r2 ){
        while( r2 < r and a[ id[ l2 ] ] == a[ id[ r2 ] ] ) r2 ++;
        if( l2 != l or r2 != r ) split = true;
        for( int ii = l2 ; ii < r2 ; ii ++ )
          nno[ id[ ii ] ] = iid;
        iid ++;
      }
    }
    for( int i = 1 ; i <= n ; i ++ )
      no[ i ] = nno[ i ];
    if( not split ) break;
  }
  for( int i = 1 ; i <= n ; i ++ )
    ans[ no[ i ] ].push_back( i );
  vector< vector<int> > va;
  for( int i = 0 ; i <= n ; i ++ )
    if( ans[ i ].size() > 1u )
      va.push_back( ans[ i ] );
  sort( va.begin() , va.end() );
  for( auto i : va )
    for( size_t j = 0 ; j < i.size() ; j ++ )
      printf( "%d%c" , i[ j ] , " \n"[ j + 1 == i.size() ] );
  if( va.empty() )
    puts( "none" );
}
