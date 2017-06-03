#include <bits/stdc++.h>
using namespace std;
#define N 18
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
map<string,int> M;
int n , wl[ 1 << N ] , wr[ 1 << N ];
string res;
int who[ 1 << N ];
bool win( int id1 , int id2 ){
  return wl[ id1 ] <= id2 and id2 <= wr[ id1 ];
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  IOS;
  cin >> n;
  for( int i = 0 ; i < (1 << n) ; i ++ ){
    string name; cin >> name;
    M[ name ] = i;
    who[ i ] = i;
    wl[ i ] = wr[ i ] = i;
  }
  cin >> res;
  int iter = 0;
  for( int i = n - 1 ; i >= 0 ; i -- ){
    for( int j = 0 ; j < (1 << i) ; j ++ ){
      char win = res[ iter ++ ];
      if( win == 'W' )
        who[ j ] = who[ j << 1 ];
      else
        who[ j ] = who[ (j << 1) | 1 ];
      int id = who[ j ];
      int lft = j << ( n - i );
      int rgt = (j + 1) << ( n - i );
      wl[ id ] = lft;
      wr[ id ] = rgt - 1;
    }
  }
  //for( int i = 0 ; i < (1 << n) ; i ++ )
    //cout << wl[ i ] << " " << wr[ i ] << endl;
  int q; cin >> q; while( q -- ){
    string name1; cin >> name1;
    string name2; cin >> name2;
    int id1 = M[ name1 ];
    int id2 = M[ name2 ];
    if( win( id1 , id2 ) )
      cout << "Win" << endl;
    else if( win( id2 , id1 ) )
      cout << "Lose" << endl;
    else
      cout << "Unknown" << endl;
  }
}
