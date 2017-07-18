#include <bits/stdc++.h>

using namespace std;

#define N 42
typedef long long LL;

LL f[ N ];
long long A, B, C;

void solve(){
  if( A == 0 ){
    cout << 1 << endl;
    return;
  }
  assert( A != B );
  assert( A != C );
  assert( B != C );
  assert( min( A , min( B , C ) ) + 2 ==
          max( A , max( B , C ) ) );
  assert( 0 <= A and A <= 1000000000 );
  assert( 0 <= B and B <= 1000000000 );
  assert( 0 <= C and C <= 1000000000 );
  //cout << A << " " << B << " " << C << endl;
  //if( max(A, max(B, C)) < N ){
  LL mx = max(A, max(B, C));
  if( max(A, max(B, C)) >= N ){
    A -= mx - N + 10;
    B -= mx - N + 10;
    C -= mx - N + 10;
  }
  LL vl = f[ B ] * f[ B ] - 4 * f[ A ] * f[ C ];
  if( vl > 0 ) cout << 2 << endl;
  else if( vl == 0 ) cout << 1 << endl;
  else cout << 0 << endl;
  exit(0);
  //}
  long long n = min(A, min(B, C));
  if (B == n) cout << "0\n";
  else if(B == n+1) cout << ((n==0)?"2\n":"0\n");
  else cout << ((n==1)?"1\n":"2\n");
}

int main() {
  f[ 0 ] = 0; f[ 1 ] = 1;
  for( LL i = 2 ; i < N ; i ++ )
    f[ i ] = f[ i - 1 ] + f[ i - 2 ] ;
  cin >> A >> B >> C;
  solve();
}
