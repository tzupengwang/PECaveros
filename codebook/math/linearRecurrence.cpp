LL n, m;
LL dp[ N + N ];
void pre_dp(){
  dp[ 0 ] = 1;
  LL bdr = min( m + m , n );
  for( LL i = 1 ; i <= bdr ; i ++ )
    for( LL j = i - 1 ; j >= max(0LL , i - m) ; j -- )
      dp[ i ] = add( dp[ i ] , dp[ j ] );
}
vector<LL> Mul( vector<LL>& v1, vector<LL>& v2 ){
  int _sz1 = (int)v1.size();
  int _sz2 = (int)v2.size();
  assert( _sz1 == m );
  assert( _sz2 == m );
  vector<LL> _v( m + m );
  for( int i = 0 ; i < m + m ; i ++ ) _v[ i ] = 0;
// expand
  for( int i = 0 ; i < _sz1 ; i ++ )
    for( int j = 0 ; j < _sz2 ; j ++ )
      _v[ i + j + 1 ] = add( _v[ i + j + 1 ] ,
                             mul(v1[ i ] , v2[ j ]) );
// shrink
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      _v[ i + j ] = add( _v[ i + j ] , _v[ i ] );
  for( int i = 0 ; i < m ; i ++ )
    _v[ i ] = _v[ i + m ];
  _v.resize( m );
  return _v;
}
vector<LL> I, A;
void solve(){
  pre_dp();
  if( n <= m + m ){
    printf( "%lld\n" , dp[ n ] );
    exit( 0 );
  }
  I.resize( m );
  A.resize( m );
  for( int i = 0 ; i < m ; i ++ ) I[ i ] = A[ i ] = 1;
// dp[ n ] = /Sum_{i=0}^{m-1} A_i * dp[ n - i - 1 ]
  LL dlt = ( n - m ) / m;
  LL rdlt = dlt * m;
  while( dlt ){
    if( dlt & 1LL ) I = Mul( I , A );
    A = Mul( A , A );
    dlt >>= 1;
  }
  LL ans = 0;
  for( int i = 0 ; i < m ; i ++ )
    ans = add(ans, mul(I[i], dp[n - i - 1 - rdlt]));
  printf( "%lld\n" , ans );
}
