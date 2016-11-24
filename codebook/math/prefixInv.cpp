void solve( int m ){
	inv[ 1 ] = 1;
	for( int i = 2 ; i < m ; i ++ )
		inv[ i ] = ((LL)(m - m / i) * inv[m % i]) % m;
}
