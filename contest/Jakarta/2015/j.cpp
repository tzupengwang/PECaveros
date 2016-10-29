#include <bits/stdc++.h>
using namespace std;
int n , mcnt;
map< string , int > M;
vector< string > vv[ 30000 ];
void init(){
  M.clear(); mcnt = 0;
  scanf( "%d" , &n ); while( n -- ){
    vector< string > tvv;
    int xi; scanf( "%d" , &xi ); while( xi -- ){
      string ss; cin >> ss;
      tvv.push_back( ss );
    }
    sort( tvv.begin() , tvv.end() );
    for( size_t i = 0 ; i < tvv.size() ; i ++ ){
      if( M.count( tvv[ i ] ) == 0 ) M[ tvv[ i ] ] = mcnt ++;
      for( size_t j = 0 ; j < tvv.size() ; j ++ ){
        if( i == j ) continue;
        vv[ M[ tvv[ i ] ] ].push_back( tvv[ j ] );
      }
    }
  }
}
int _cs , len1 , len2;
string s1 , s2;
inline bool okay( const string& ii1 , const string& ii2 ){
  int xlen = min( ii1.length() , ii2.length() );
  return ii1.substr( 0 , xlen ) ==
         ii2.substr( 0 , xlen );
}
int cut;
bool ff;
bool go( int i1 , int i2 , string as1 , string as2 ){
  if( (int)max( as1.length() , as2.length() ) > cut ){
    ff = true;
    return false;
  }
  if( i1 == len1 && i2 == len2 ){
    if( as1 == as2 ){
      printf( "%s\n" , as1.c_str() );
      return true;
    }
    return false;
  }
  if( as1.length() < as2.length() ){
    if( i1 < len1 ){
      string xs1 = as1 + s1[ i1 ];
      if( okay( xs1 , as2 ) ){
        if( go( i1 + 1 , i2 , xs1 , as2 ) )
          return true;
      }
    }
    if( i1 < len1 ){
      for( int ii = len1 - 1 ; ii >= i1 ; ii -- ){
      //for( int ii = i1 ; ii < len1 ; ii ++ ){
        string ss = s1.substr( i1 , ii - i1 + 1 );
        if( M.count( ss ) == 0 ) continue;
        int id = M[ ss ];
        for( auto i : vv[ id ] ){
          string xss = as1 + i;
          if( okay( xss , as2 ) ){
            if( go( ii + 1 , i2 , xss , as2 ) )
              return true;
          }
        }
      }
    }
  }else{
    if( i2 < len2 ){
      string xs2 = as2 + s2[ i2 ];
      if( okay( as1 , xs2 ) ){
        if( go( i1 , i2 + 1 , as1 , xs2 ) )
          return true;
      }
    }
    if( i2 < len2 ){
      for( int ii = len2 - 1 ; ii >= i2 ; ii -- ){
      //for( int ii = i2 ; ii < len2 ; ii ++ ){
        string ss = s2.substr( i2 , ii - i2 + 1 );
        if( M.count( ss ) == 0 ) continue;
        int id = M[ ss ];
        for( auto i : vv[ id ] ){
          string xss = as2 + i;
          if( okay( as1 , xss ) ){
            if( go( i1 , ii + 1 , as1 , xss ) )
              return true;
          }
        }
      }
    }
  }
  return false;
}
void solve(){
  printf( "Case #%d:\n" , ++ _cs );
  int q; scanf( "%d" , &q ); while( q -- ){
    cin >> s1 >> s2;
    len1 = s1.length();
    len2 = s2.length();
    bool flag = false;
    for( cut = 1 ; cut <= 200 ; cut ++ ){
      ff = false;
      if( go( 0 , 0 , "" , "" ) ){
        flag = true;
        break;
      }
      if( !ff ) break;
    }
    if( !flag )
      puts( "[ALIEN]" );
  }
}
void bye(){
  for( int i = 0 ; i < mcnt ; i ++ )
    vv[ i ].clear();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
    bye();
  }
}
