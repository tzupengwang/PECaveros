#define N 110
#define inf 0x3f3f3f3f
int G[ N ][ N ] , ID[ N ];
int match[ N ] , stk[ N ];
int vis[ N ] , dis[ N ];
int n , m , k , top;
bool SPFA( int u ){
	stk[ top ++ ] = u;
	if( vis[ u ] ) return true;
	vis[ u ] = true;
	for( int i = 1 ; i <= k ; i ++ ){
		if( i != u && i != match[ u ] && !vis[ i ] ){
			int v = match[ i ];
			if( dis[ v ] < dis[ u ] + G[ u ][ i ] - G[ i ][ v ] ){
				dis[ v ] = dis[ u ] + G[ u ][ i ] - G[ i ][ v ];
				if( SPFA( v ) ) return true;
			}
		}
	}
	top --; vis[ u ] = false;
	return false;
}
int MaxWeightMatch() {
	for( int i = 1 ; i <= k ; i ++ ) ID[ i ] = i;
	for( int i = 1 ; i <= k ; i += 2 ) match[ i ] = i + 1 , match[ i + 1 ] = i;
	for( int times = 0 , flag ; times < 3 ; ){
		memset( dis , 0 , sizeof( dis ) );
		memset( vis , 0 , sizeof( vis ) );
		top = 0; flag = 0;
		for( int i = 1 ; i <= k ; i ++ ){
			if( SPFA( ID[ i ] ) ){
				flag = 1;
				int t = match[ stk[ top - 1 ] ] , j = top - 2;
				while( stk[ j ] != stk[ top - 1 ] ){
					match[ t ] = stk[ j ];
					swap( t , match[ stk[ j ] ] );
					j --;
				}
				match[ t ] = stk[ j ]; match[ stk[ j ] ] = t;
				break;
			}
		}
		if( !flag ) times ++;
		if( !flag ) random_shuffle( ID + 1 , ID + k + 1 );
	}
	int ret = 0;
	for( int i = 1 ; i <= k ; i ++ )
		if( i < match[ i ] ) ret += G[ i ][ match[ i ] ];
	return ret;
}
int main(){
	int T; scanf("%d", &T);
	for ( int cs = 1 ; cs <= T ; cs ++ ){
		scanf( "%d%d%d" , &n , &m , &k );
		memset( G , 0x3f , sizeof( G ) );
		for( int i = 1 ; i <= n ; i ++ ) G[ i ][ i ] = 0;
		for( int i = 0 ; i < m ; i ++ ){
			int u, v, w;
            scanf( "%d%d%d" , &u , &v , &w );
			G[ u ][ v ] = G[ v ][ u ] = w;
		}
		if( k & 1 ){ puts( "Impossible" ); continue; }
		for( int tk = 1; tk <= n ; tk ++ )
			for( int i = 1 ; i <= n ; i ++ )
				for( int j = 1 ; j <= n ; j ++ )
					G[ i ][ j ] = min( G[ i ][ j ] , G[ i ][ tk ] + G[ tk ][ j ] );
		for( int i = 1 ; i <= k ; i ++ ){
			for( int j = 1 ; j <= k ; j ++ )
				G[ i ][ j ] = -G[ i ][ j ];
			G[ i ][ i ] = -inf;
		}
		printf( "%d\n" , -MaxWeightMatch() );
	}
}
