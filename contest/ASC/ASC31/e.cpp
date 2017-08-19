#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define E 2
typedef long long LL;
const int mods[ E ] = { 1000000007 , 1000000009 };
int add( int a , int b , int mod ){
  a += b;
  return a >= mod ? a - mod : a;
}
int mul( LL a , LL b , int mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}
struct Int{
  int vl[ E ];
  Int( int vv = 0 ){
    for( int i = 0 ; i < E ; i ++ ){
      vl[ i ] = vv % mods[ i ];
    }
  }
  Int operator+( const Int& he ) const{
    Int ret;
    for( int i = 0 ; i < E ; i ++ )
      ret.vl[ i ] = add( vl[ i ] , he.vl[ i ] , mods[ i ] );
    return ret;
  }
  Int operator*( const Int& he ) const{
    Int ret;
    for( int i = 0 ; i < E ; i ++ )
      ret.vl[ i ] = mul( vl[ i ] , he.vl[ i ] , mods[ i ] );
    return ret;
  }
  bool operator<( const Int& he ) const{
    for( int i = 0 ; i < E ; i ++ )
      if( vl[ i ] != he.vl[ i ] )
        return vl[ i ] < he.vl[ i ];
    return false;
  }
};
#define N 222
#define BS 13131
int n;
Int bs[ N ] , bss;
string s[ N ];
void build(){
  bs[ 0 ] = Int( 1 );
  bss = Int( BS );
  for( int i = 1 ; i < N ; i ++ )
    bs[ i ] = bs[ i - 1 ] * bss;
}
void init(){
  cin >> n;
  //n = 200;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> s[ i ];
    //for( int j = 0 ; j < 50 ; j ++ )
      //s[ i ] += (char)( 33 + rand() % 94 );
  }
}
map<Int,int> M[ N ];
int mcnt;
#define X 510101
bool win[ X ] , gt[ X ];
vector<int> nxt[ X ];
bool Win( int len , int id ){
  if( gt[ id ] ) return win[ id ];
  for( auto tmp : nxt[ id ] )
    if( Win( len + 1 , tmp ) ){
      gt[ id ] = true;
      return win[ id ] = false;
    }
  gt[ id ] = true;
  return win[ id ] = true;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    int len = s[ i ].length();
    for( int j = 0 ; j < len ; j ++ ){
      Int tmp;
      for( int k = j ; k < len ; k ++ ){
        tmp = tmp * bss + Int( s[ i ][ k ] );
        if( M[ k - j + 1 ].find( tmp ) == M[ k - j + 1 ].end() ){
          M[ k - j + 1 ][ tmp ] = mcnt ++;
          if( j == 0 and k + 1 == len )
            gt[ mcnt - 1 ] = true;
        }
      }
    }
  }
  for( int i = 0 ; i < n ; i ++ ){
    int len = s[ i ].length();
    for( int j = 0 ; j < len ; j ++ ){
      Int tmp;
      for( int k = j ; k < len ; k ++ ){
        tmp = tmp * bss + Int( s[ i ][ k ] );
        //tmp = add( mul( tmp , bss ) , s[ i ][ k ] );
        int iid = M[ k - j + 1 ][ tmp ];
        if( j ){
          Int lft = tmp + Int( s[ i ][ j - 1 ] ) * bs[ k - j + 1 ];
          nxt[ iid ].push_back( M[ k - j + 2 ][ lft ] );
        }
        if( k + 1 < len ){
          Int rgt = tmp * bss + Int( s[ i ][ k + 1 ] );
          nxt[ iid ].push_back( M[ k - j + 2 ][ rgt ] );
        }
      }
    }
  }
  string fm = "";
  for( int i = 33 ; i <= 126 ; i ++ ){
    Int ss( i );
    if( M[ 1 ].find( ss ) == M[ 1 ].end() ) continue;
    if( Win( 1 , M[ 1 ][ ss ] ) )
      fm += (char)i;
  }
  if( fm.empty() )
    cout << "Second" << endl;
  else
    cout << "First\n" << fm << endl;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "game.in" , "r" , stdin );
  freopen( "game.out" , "w" , stdout );
#endif
  build();
  init();
  solve();
}
