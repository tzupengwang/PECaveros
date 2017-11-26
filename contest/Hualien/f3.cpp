#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
vector<int> v[ N ];
int k , all;
void gogo( int now , int vl ){
  if( now == k ){
    for( int i = 0 ; i < 3 ; i ++ ){
      int nxt = (vl * 3 + i) % all;
      v[ vl ].push_back( nxt );
    }
    return;
  }
  for( int i = 0 ; i < 3 ; i ++ )
    gogo( now + 1 , vl * 3 + i );
}
void build_g(){
  all = 1;
  for( int i = 0 ; i < k ; i ++ )
    all *= 3;
  for( int i = 0 ; i < all ; i ++ )
    v[ i ].clear();
  gogo( 0 , 0 );
}
vector< pair<int,int> > e;
void go( int now , int dep = 0 , bool flag = false ){
  vector< pair<int,int> > te;
  int tdep = dep;
  while( not v[ now ].empty() ){
    if( flag ){
      if( dep & 1 )
        reverse( v[ now ].begin() , v[ now ].end() );
    }
    te.push_back( { now , v[ now ].back() } );
    int cur = v[ now ].back();
    v[ now ].pop_back();
    while( cur != now ){
      te.push_back( { cur , v[ cur ].back() } );
      int nxt = v[ cur ].back();
      v[ cur ].pop_back();
      cur = nxt;
    }
    ++ tdep;
  }
  for( auto i : te ){
    e.push_back( i );
    if( not v[ i.second ].empty() )
      go( i.second , dep + 1 , flag );
  }
}
inline string to_s( int msk ){
  string ret = "";
  for( int i = 0 ; i < k ; i ++ ){
    ret += (char)( '0' + msk % 3 );
    msk /= 3;
  }
  reverse( ret.begin() , ret.end() );
  return ret;
}
bool check( const string& s1 , const string& s2 ){
  set<string> ss;
  int len = s1.length();
  for( int i = 0 ; i + k + 2 <= len ; i ++ )
    ss.insert( s1.substr( i , k + 2 ) );
  for( int i = 0 ; i + k + 2 <= len ; i ++ ){
    string tmp = s2.substr( i , k + 2 );
    auto it = ss.find( tmp );
    if( it != ss.end() ){
      cerr << k + 1 << endl;
      return false;
    }
  }
  return true;
}
void solve(){
  if( k < 5 ) return;
  if( k == 0 ){
    cout << 1 << endl;
    cout << "012" << endl;
    cout << "021" << endl;
    return;
  }

  for( int _ = 0 ; ; _ ++ ){
    build_g();
    if( _ ){
      for( int i = 0 ; i < all ; i ++ )
        random_shuffle( v[ i ].begin() , v[ i ].end() );
    }
    e.clear();

    go( 0 );
    string r = to_s( 0 );
    for( auto i : e )
      r += (char)( '0' + i.second % 3 );
    
    build_g();
    if( _ ){
      for( int i = 0 ; i < all ; i ++ )
        random_shuffle( v[ i ].begin() , v[ i ].end() );
    }
    e.clear();

    go( 0 , 0 , 1 );
    string r2 = to_s( 0 );
    for( auto i : e )
      r2 += (char)( '0' + i.second % 3 );

    if( check( r , r2 ) ){
      cout << k + 1 << endl;
      cout << r << endl;
      cout << r2 << endl;
      return;
    }
  }
  assert( false );
}
int main(){
  while( cin >> k and k ){
    k --;
    solve();
  }
}
