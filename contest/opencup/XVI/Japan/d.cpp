#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long LL;
bool pr( int x ){
  for( int i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 )
      return false;
  return true;
}
bool ok( int x ){
  for( int i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 ){
      int cc = 0;
      while( x % i == 0 ){
        cc ++;
        x /= i;
      }
      if( cc > 1 )
        return false;
    }
  return true;
}
int phi( int x ){
  int ret = 1;
  for( int i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 ){
      ret *= i - 1;
      x /= i;
      while( x % i == 0 ){
        ret *= i;
        x /= i;
      }
    }
  if( x > 1 ) ret *= ( x - 1 );
  return ret;
}
int phii( int x ){
  int ret = 1;
  for( int i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 ){
      ret = ( ret * ( i - 1 ) ) / __gcd( ret , i - 1 );
      x /= i;
      while( x % i == 0 ){
        ret *= i;
        x /= i;
      }
    }
  if( x > 1 ) ret = ( ret * ( x - 1 ) ) / __gcd( ret , x - 1 );
  return ret;
}
int mul( LL a , LL b , LL m ){
  a *= b;
  return a >= m ? a % m : a;
}
int mpow( int a , int b , int m ){
  if( b == 0 ) return 1;
  int ret = mpow( mul( a , a , m ) , b >> 1 , m );
  if( b & 1 ) ret = mul( ret , a , m );
  return ret;
}
vector< pair<int,int> > ff;
void fac( int x ){
  ff.clear();
  for( int i = 2 ; i * i <= x ; i ++ )
    if( x % i == 0 ){
      int cc = 0;
      while( x % i == 0 ){
        cc ++;
        x /= i;
      }
      ff.push_back( { i , cc } );
    }
  if( x > 1 )
    ff.push_back( { x , 1 } );
}
vector<int> fc;
void go( int now , int v ){
  if( now == (int)ff.size() ){
    fc.push_back( v );
    return;
  }
  for( int i = 0 ; i <= ff[ now ].second ; i ++ ){
    go( now + 1 , v );
    v *= ff[ now ].first;
  }
}
int32_t main(){
  int n; cin >> n;
  if( pr( n ) ){
    cout << 1 << endl;
    return 0;
  }
  if( not ok( n ) ){
    cout << -1 << endl;
    return 0;
  }
  int a = phii( n );
  //cout << n << " " << a << endl;
  if( __gcd( a , n ) > 1 ){
    cout << -1 << endl;
    return 0;
  }
  //cout << phi( a ) << endl;
  fac( phi( a ) );
  go( 0 , 1 );
  sort( fc.begin() , fc.end() );
  for( auto i : fc )
    if( mpow( n % a , i , a ) == 1 ){
  //for( int i = 1 , cur = n % a ; i <= phi( a ) ; i ++ , cur = mul( cur , n % a , a ) )
    //if( cur % a == 1 ){
      cout << i << endl;
      return 0;
    }
  cout << -1 << endl;
  //cout << phi( a ) << endl;
}
