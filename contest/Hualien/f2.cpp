#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
vector<int> v[ N ] , v2[ N ];
int k , all , all2;
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
void gogo2( int now , int vl ){
  if( now == k + 1 ){
    for( int i = 0 ; i < 3 ; i ++ ){
      int nxt = (vl * 3 + i) % all2;
      v2[ vl ].push_back( nxt );
    }
    return;
  }
  for( int i = 0 ; i < 3 ; i ++ )
    gogo2( now + 1 , vl * 3 + i );
}
void build_g2(){
  all2 = 1;
  for( int i = 0 ; i < k + 1 ; i ++ )
    all2 *= 3;
  for( int i = 0 ; i < all ; i ++ )
    v2[ i ].clear();
  gogo2( 0 , 0 );
}
vector< pair<int,int> > e;
set< pair<int,int> > se;
void go( int now ){
  vector< pair<int,int> > te;
  while( not v[ now ].empty() ){
    te.push_back( { now , v[ now ].back() } );
    int cur = v[ now ].back();
    v[ now ].pop_back();
    while( cur != now ){
      te.push_back( { cur , v[ cur ].back() } );
      int nxt = v[ cur ].back();
      v[ cur ].pop_back();
      cur = nxt;
    }
  }
  for( auto i : te ){
    e.push_back( i );
    if( not v[ i.second ].empty() )
      go( i.second );
  }
}
inline string to_s( int msk , int _k ){
  string ret = "";
  for( int i = 0 ; i < _k ; i ++ ){
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
inline int combine( int pre , int nxt ){
  return pre * 3 + nxt % 3;
}

int p[ N ] , sz[ N ];
int f( int x ){
  return x == p[ x ] ? p[ x ] : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  x = f( x ); y = f( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}


set<int> w[ N ] , iw[ N ];
bool out[ N ] , in[ N ];

void solve(){
  if( k < 4 ) return;
  if( k == 0 ){
    cout << 1 << endl;
    cout << "012" << endl;
    cout << "021" << endl;
    return;
  }

  build_g2();

  while( true ){
    cerr << "refinding a euler path...." << endl;
    build_g();
    e.clear();
    se.clear();
    go( 0 );
    vector<int> tmp;
    for( size_t i = 0 ; i < e.size() ; i ++ )
      tmp.push_back( combine( e[ i ].first , e[ i ].second ) );
    for( size_t i = 0 ; i < tmp.size() ; i ++ )
      se.insert( { tmp[ i ] , tmp[ (i + 1) % tmp.size() ] } );
    for( int i = 0 ; i < all2 ; i ++ ){
      p[ i ] = i , sz[ i ] = 1;
      w[ i ].clear();
      iw[ i ].clear();
      in[ i ] = out[ i ] = false;
    }
    queue<int> Q;
    for( int i = 0 ; i < all2 ; i ++ ){
      for( int j : v2[ i ] ){
        if( se.find( { i , j } ) != se.end() )
          continue;
        if( i == j ) continue;
        uni( i , j );
        w[ i ].insert( j );
        iw[ j ].insert( i );
      }
    }
    if( sz[ f( 0 ) ] != all2 )
      continue;

    cerr << "Find a euler path!" << endl;

    bool gg = false;

    for( int i = 0 ; i < all2 and not gg ; i ++ ){
      if( w[ i ].empty() ) gg = true;
      if( iw[ i ].empty() ) gg = true;
      if( w[ i ].size() == 1u ){
        out[ i ] = true;
        Q.push( i );
      }
      if( iw[ i ].size() == 1u ){
        in[ i ] = true;
        Q.push( i );
      }
    }

    if( gg ) continue;

    while( not gg ){

      while( Q.size() and not gg ){
        int tn = Q.front(); Q.pop();
        if( w[ tn ].size() == 0u ){
          gg = true;
          break;
        }
        if( iw[ tn ].size() == 0u ){
          gg = true;
          break;
        }
        if( w[ tn ].size() == 1u ){
          int nxt = *w[ tn ].begin();
          vector<int> other;
          for( auto i : iw[ nxt ] )
            other.push_back( i );
          for( auto i : other )
            if( i != tn ){
              iw[ nxt ].erase( i );
              w[ i ].erase( nxt );
              if( w[ i ].size() == 1u and not out[ i ] ){
                out[ i ] = true;
                Q.push( i );
              }
            }
          if( iw[ nxt ].size() == 1u and not in[ nxt ] ){
            in[ nxt ] = true;
            Q.push( nxt );
          }
        }
        if( iw[ tn ].size() == 1u ){
          int nxt = *iw[ tn ].begin();
          vector<int> other;
          for( auto i : w[ nxt ] )
            other.push_back( i );
          for( auto i : other )
            if( i != tn ){
              w[ nxt ].erase( i );
              if( iw[ i ].size() == 1u and not in[ i ] ){
                in[ i ] = true;
                Q.push( i );
              }
            }
          if( w[ nxt ].size() == 1u and not out[ nxt ] ){
            out[ nxt ] = true;
            Q.push( nxt );
          }
        }
      }
      bool keep = false;
      for( int i = 0 ; i < all2 and not gg ; i ++ ){
        if( w[ i ].size() == 0u ) gg = true;
        if( iw[ i ].size() == 0u ) gg = true;
        if( w[ i ].size() == 2u ){
          keep = true;
          int nxt = *w[ i ].begin();
          w[ i ].erase( nxt );
          iw[ nxt ].erase( i );
          Q.push( i );
          out[ i ] = true;
          if( iw[ nxt ].size() == 1u and not in[ nxt ] ){
            Q.push( nxt );
            in[ nxt ] = true;
          }
          break;
        }
      }
      if( not keep ) break;
    }

    if( gg ) continue;

    string r = to_s( e[ 0 ].first , k );
    for( size_t i = 0 ; i < e.size() ; i ++ )
      r += (char)( '0' + e[ i ].second % 3 );
  
    vector< vector<int> > r_wt;
    vector<bool> st;
    st.resize( all2 );
    for( int i = 0 ; i < all2 ; i ++ )
      st[ i ] = false;
    for( int i = 0 ; i < all2 ; i ++ ){
      if( st[ i ] ) continue;
      int now = i;
      vector<int> cyc;
      while( !st[ now ] ){
        cyc.push_back( now );
        st[ now ] = true;
        now = *w[ now ].begin();
      }
      r_wt.push_back( cyc );
    }



    string r2 = to_s( 0 , k + 1 );
    int now = 0;
    while( true ){
      int nxt = *w[ now ].begin();
      if( nxt == 0 ) break;
      r2 += (char)( '0' + nxt % 3 );
      now = nxt;
    }
    if( r2.length() != r.length() ) continue;

    cerr << "          Find a answer for " << k + 1 << endl;

    assert( check( r , r2 ) );

    cout << k + 1 << endl;
    cout << r << endl;
    cout << r2 << endl;
    return;
  }
 
  assert( false );
}
int main(){
  while( cin >> k and k ){
    k --;
    solve();
  }
}
