#include <bits/stdc++.h>
using namespace std;

const int MAXN = 21;

int n , m;
char ip[MAXN][MAXN];
int wA[ MAXN ] , wB[ MAXN ] , T;
int adjA[ MAXN ] , adjB[ MAXN ];

bool okA[ 1<<MAXN ] , okB[ 1<<MAXN ];

vector<int> haoA , haoB;

int main() {
  cin >> n >> m;
  for ( int i = 0 ; i < n ; i++ ) cin >> ip[ i ];
  for ( int i = 0 ; i < n ; i++ ) cin >> wA[ i ];
  for ( int i = 0 ; i < m ; i++ ) cin >> wB[ i ];
  cin >> T;
  for ( int i = 0 ; i < n ; i++ ) {
    for ( int j = 0 ; j < m ; j++ ) if( ip[ i ][ j ] == '1' ) {
      adjA[ i ] |= ( 1<<j );
      adjB[ j ] |= ( 1<<i );
    }
  }
  okA[ 0 ] = 1;
  for ( int cmb = 0 ; cmb < ( 1<<n ) ; cmb++ ) {
    okA[ cmb ] = 1;
    int adj = 0;
    int totw = 0;
    for ( int i = 0 ; i < n ; i++ ) if( ( cmb>>i )&1 ) {
      okA[ cmb ] = okA[ cmb ] && okA[ cmb^( 1<<i ) ];
      adj |= adjA[ i ];
      totw += wA[ i ];
    }
    int c1 = __builtin_popcount( cmb );
    int c2 = __builtin_popcount( adj );
    okA[ cmb ] = okA[ cmb ] && ( c1 <= c2 );
    if ( okA[ cmb ] ) haoA.push_back( totw );
  }
  okB[ 0 ] = 1;
  for ( int cmb = 0 ; cmb < ( 1<<m ) ; cmb++ ) {
    okB[ cmb ] = 1;
    int adj = 0;
    int totw = 0;
    for ( int i = 0 ; i < m ; i++ ) if( ( cmb>>i )&1 ) {
      okB[ cmb ] = okB[ cmb ] && okB[ cmb^( 1<<i ) ];
      adj |= adjB[ i ];
      totw += wB[ i ];
    }
    int c1 = __builtin_popcount( cmb );
    int c2 = __builtin_popcount( adj );
    okB[ cmb ] = okB[ cmb ] && ( c1 <= c2 );
    if ( okB[ cmb ] ) haoB.push_back( totw );
  }
  sort( haoA.begin() , haoA.end() );
  sort( haoB.begin() , haoB.end() );
  long long ans = 0;
  for ( int x : haoA ) {
    int tar = T-x;
    int cnt = haoB.end() - lower_bound( haoB.begin() , haoB.end() , tar );
    ans += cnt;
  }
  cout << ans << endl;
}
