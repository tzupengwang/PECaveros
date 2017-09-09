#include <bits/stdc++.h>
using namespace std;
int h , w;
char c[ 22 ][ 22 ];
string ans;
int di[]={-1,-1,-1,0,1,1,1,0};
int dj[]={-1,0,1,1,1,0,-1,-1};
vector< pair<string, pair<pair<int,int>, int> > > v , tv;
int ni[ 22 ][ 22 ][ 8 ];
int nj[ 22 ][ 22 ][ 8 ];
int main(){
  while( scanf( "%d%d" , &h , &w ) == 2 ){
    if( h == 0 ) break;
    for( int i = 0 ; i < h ; i ++ )
      scanf( "%s" , c[ i ] );
    ans = "";
    v.clear();
    for( int i = 0 ; i < h ; i ++ )
      for( int j = 0 ; j < w ; j ++ )
        for( int dir = 0 ; dir < 8 ; dir ++ ){
          string tmp;
          tmp += c[ i ][ j ];
          v.push_back( { tmp , { { i , j } , dir } } );
          ni[ i ][ j ][ dir ] = i;
          nj[ i ][ j ][ dir ] = j;
        }
    while( v.size() ){
      sort( v.begin() , v.end() );
      tv.clear();
      bool gt = false;
      for( size_t l = 0 , r = 0 ; l < v.size() ; l = r ){
        while( r < v.size() and v[ l ].first == v[ r ].first ) r ++;
        if( r - l < 2 ) continue;
        if( !gt ){
          ans = v[ l ].first;
          gt = true;
        }
        for( size_t i = l ; i < r ; i ++ ){
          int ii = v[ i ].second.first.first;
          int jj = v[ i ].second.first.second;
          int dd = v[ i ].second.second;
          int curi = ni[ ii ][ jj ][ dd ];
          int curj = nj[ ii ][ jj ][ dd ];
          int nxti = ( curi + di[ dd ] + h ) % h;
          int nxtj = ( curj + dj[ dd ] + w ) % w;
          if( ii == nxti and jj == nxtj ) continue;
          tv.push_back( { v[ i ].first + c[ nxti ][ nxtj ] ,
                          { { ii , jj } , dd } } );
          ni[ ii ][ jj ][ dd ] = nxti;
          nj[ ii ][ jj ][ dd ] = nxtj;
        }
      }
      v.swap( tv );
    }
    if( ans.length() < 2 ) ans = "0";
    cout << ans << endl;
  }
}
