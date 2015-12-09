// max N = 64
typedef unsigned long long ll;
struct MaxClique{
  ll nb[ N ] , n , ans;
  void init( ll _n ){
    n = _n;
    for( int i = 0 ; i < n ; i ++ ) nb[ i ] = 0LLU;
  }
  void add_edge( ll _u , ll _v ){
    nb[ _u ] |= ( 1LLU << _v );
    nb[ _v ] |= ( 1LLU << _u );
  }
  void B( ll r , ll p , ll x , ll cnt , ll res ){
    if( cnt + res < ans ) return;
    if( p == 0LLU && x == 0LLU ){
      if( cnt > ans ) ans = cnt;
      return;
    }
    ll y = p | x; y &= -y;
    ll q = p & ( ~nb[ int( log2( y ) ) ] );
    while( q ){
      ll i = int( log2( q & (-q) ) );
      B( r | ( 1LLU << i ) , p & nb[ i ] , x & nb[ i ]
          , cnt + 1LLU , __builtin_popcountll( p & nb[ i ] ) );
      q &= ~( 1LLU << i );
      p &= ~( 1LLU << i );
      x |= ( 1LLU << i );
    }
  }
  int solve(){
    ans = 0;
    ll _set = 0;
    if( n < 64 ) _set = ( 1LLU << n ) - 1;
    else{
      for( ll i = 0 ; i < n ; i ++ ) _set |= ( 1LLU << i );
    }
    B( 0LLU , _set , 0LLU , 0LLU , n );
    return ans;
  }
}maxClique;
