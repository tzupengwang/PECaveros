#include <bits/stdc++.h>
using namespace std;
int n;
bool gg;
vector<string> s[ 21 ] , w[ 21 ];
string ans , tmp;
const string no = "-.";
int mapping[ 26 ] , got;
void gen_ans(){
  ans = "";
  for( auto c : tmp )
    if( 'A' <= c and c <= 'Z' )
      ans += mapping[ c - 'A' ] + 'A';
    else
      ans += c;
}
void go( int now );
void go2( int now ,
          const vector<string>& ss ,
          const vector<string>& ww , int sp ){
  if( sp == (int)ss.size() ){
    go( now - 1 );
    return;
  }
  const string& cur = ss[ sp ];
  for( size_t i = 0 ; i < ww.size() ; i ++ ){
    bool nok = false;
    for( int j = 0 ; j < now ; j ++ )
      if( mapping[ cur[ j ] - 'A' ] != -1 and
          mapping[ cur[ j ] - 'A' ] + 'A' != ww[ i ][ j ] ){
        nok = true;
        break;
      }
    if( nok ) continue;
    int omp[ 26 ];
    for( int j = 0 ; j < 26 ; j ++ )
      omp[ j ] = mapping[ j ];
    for( int j = 0 ; j < now ; j ++ )
      if( mapping[ cur[ j ] - 'A' ] != -1 ){
        if( mapping[ cur[ j ] - 'A' ] + 'A' !=
            ww[ i ][ j ] ){
          nok = true;
          break;
        }
      }else{
        if( mapping[ ww[ i ][ j ] - 'A' ] != -1 ){
          nok = true;
          break;
        }
        mapping[ cur[ j ] - 'A' ] = ww[ i ][ j ] - 'A';
        mapping[ ww[ i ][ j ] - 'A' ] = cur[ j ] - 'A';
      }
    if( not nok )
      go2( now , ss , ww , sp + 1 );
    for( int j = 0 ; j < 26 ; j ++ )
      mapping[ j ] = omp[ j ];
    if( gg )
      return;
  }
}
void go( int now ){
  if( now < 1 ){
    ++ got;
    if( got > 1 ){
      gg = true;
      ans = no;
    }else
      gen_ans();
    return;
  }
  if( s[ now ].empty() ){
    go( now - 1 );
    return;
  }
  vector<string> ss , ww;
  set<string> gotw;
  for( auto i : s[ now ] ){
    bool ok = true;
    string ts = "";
    for( auto c : i )
      if( mapping[ c - 'A' ] == -1 ){
        ok = false;
        break;
      }else
        ts += mapping[ c - 'A' ] + 'A';
    if( !ok ){
      ss.push_back( i );
      continue;
    }
    gotw.insert( ts );
  }
  for( auto i : w[ now ] )
    if( gotw.find( i ) == gotw.end() )
      ww.push_back( i );
  //cout << " +++" << now << endl;
  //for( auto j : ss )
    //cout << j << " ";
  //cout << endl;
  //for( auto j : ww )
    //cout << j << " ";
  //cout << endl;
  if( ss.size() < ww.size() )
    return;
  //cout << " " << now << endl;
  //if( not ss.empty() ){
    //for( auto j : ss )
      //cout << j << " ";
    //cout << endl;
    //for( auto j : ww )
      //cout << j << " ";
    //cout << endl;
  //}
  if( ss.empty() ){
    go( now - 1 );
    return;
  }
  go2( now , ww , ss , 0 );
}
void solve(){
  ans = no;
  if( gg ) return;
  for( int i = 1 ; i < 21 ; i ++ ){
    sort( s[ i ].begin() , s[ i ].end() );
    s[ i ].resize( unique( s[ i ].begin() , s[ i ].end() ) - s[ i ].begin() );
    sort( w[ i ].begin() , w[ i ].end() );
    w[ i ].resize( unique( w[ i ].begin() , w[ i ].end() ) - w[ i ].begin() );
    if( w[ i ].size() > s[ i ].size() )
      return;
    //if( not s[ i ].empty() ){
      //for( auto j : s[ i ] )
        //cout << j << " ";
      //cout << endl;
      //for( auto j : w[ i ] )
        //cout << j << " ";
      //cout << endl;
    //}
  }
  got = 0;
  go( 20 );
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    for( int i = 0 ; i < 26 ; i ++ )
      mapping[ i ] = -1;
    for( int i = 0 ; i < 21 ; i ++ ){
      s[ i ].clear();
      w[ i ].clear();
    }
    for( int i = 0 ; i < n ; i ++ ){
      cin >> tmp;
      s[ tmp.length() ].push_back( tmp );
    }
    getline( cin , tmp );
    getline( cin , tmp );
    gg = false;
    string wt;
    int len = tmp.length();
    for( int i = 0 ; i < len ; i ++ )
      if( 'A' <= tmp[ i ] and tmp[ i ] <= 'Z' )
        wt += tmp[ i ];
      else if( wt.length() ){
        if( wt.length() > 20 ){
          gg = true;
          wt = "";
          continue;
        }
        w[ wt.length() ].push_back( wt );
        wt = "";
      }
    solve();
    cout << ans << endl;
  }
}
