typedef long long ll;
typedef unsigned int uint;
#define maxn 310010
#define nmaxn 141073
struct comp{
    double a , b ;
    comp( double a_ = 0.0 , double b_ = 0.0 ) : a( a_ ) , b( b_ ){ }
} null ;
comp operator+ ( const comp &a , const comp &b ) { return comp(a.a+b.a,a.b+b.b); }
comp operator- ( const comp &a , const comp &b ) { return comp(a.a-b.a,a.b-b.b); }
comp operator* ( const comp &a , const comp &b ) { return comp(a.a*b.a-a.b*b.b,a.a*b.b+a.b*b.a); }
char s[ maxn ] ;
int n ;
comp A[ nmaxn ] , B[ nmaxn ] , C[ nmaxn ] ;
const double pi = acos( -1 ) ;
int L = 6 ;
ll base[ 10 ] , M = 1000000 ;
int get( comp *A ){
	if ( scanf( "%s" , s ) == EOF ) return 0 ;
	int a = 0 , p = 0 , l = 0 ;
	for ( register int i = strlen( s ) - 1 ; i >= 0 ; i -- ) {
		a += ( s[ i ] - '0' ) * base[ p ++ ] ;
		if( p == L ) A[ l ++ ] = comp( a , 0 ) , a = p = 0 ;
	}
	if ( a ) A[ l ++ ] = comp( a , 0 ) ;
	return l;
}
bool init( ){
	base[ 0 ] = 1 ;
	for ( register int i = 1 ; i <= L ; i ++ ) base[ i ] = base[ i - 1 ] * 10 ;
	int l = get( A ) + get( B );
	if ( l == 0 ) return false ;
	for ( n = 1 ; n < l ; n <<= 1 );
	//printf( "%d\n" , n ) ;
	return true ;
}
comp p[ 2 ][ nmaxn ]; int typ;
uint rev( uint a ){
	a = ( ( a & 0x55555555U ) << 1 ) | ( ( a & 0xAAAAAAAAU ) >> 1 ) ;
	a = ( ( a & 0x33333333U ) << 2 ) | ( ( a & 0xCCCCCCCCU ) >> 2 ) ;
	a = ( ( a & 0x0F0F0F0FU ) << 4 ) | ( ( a & 0xF0F0F0F0U ) >> 4 ) ;
	a = ( ( a & 0x00FF00FFU ) << 8 ) | ( ( a & 0xFF00FF00U ) >> 8 ) ;
	a = ( ( a & 0x0000FFFFU ) << 16 ) | ( ( a & 0xFFFF0000U ) >> 16 ) ;
	return a;
}
void FFT( comp *s , comp *bac , int n ){
	register int d = log2( n );
	for ( register int i = 0 ; i < n ; i ++ ) s[ rev( i ) >> ( 32 - d ) ] = bac[ i ];
	for ( register int i = 1 ; i <= d ; i ++ ) {
		int step = 1 << i , v = step >> 1 , rstep = n / step ;
		for ( register int j = 0 ; j <= n - 1 ; j += step ) {
			comp *t = p[ typ ];
			for ( register int k = 0 ; k < v ; k ++ , t += rstep ) {
				comp d = ( *t ) * s[ k + j + v ];
				s[ k + j + v ] = s[ k + j ] - d ;
				s[ k + j ] = s[ k + j ] + d ;
			}
		}
	}
}
ll ans[ 4 * maxn ];
bool work(){
	if ( !init() ) return false ;
	p[ 0 ][ 0 ] = comp( 1 , 0 ) , p[ 1 ][ 0 ] = comp( 1 , 0 );
	for ( register int i = 1 ; i < n ; i ++ ) {
		p[ 0 ][ i ] = comp( cos( 2 * i * pi / n ) , sin( 2 * i * pi / n ) );
		p[ 1 ][ i ] = comp( cos( 2 * i * pi / n ) , -sin( 2 * i * pi / n ) );
	}
	typ = 0; FFT( C , A , n ) , FFT( A , B , n ) ;
	for ( register int i = 0 ; i < n ; i ++ ) A[ i ] = A[ i ] * C[ i ] ;
	typ = 1 ; FFT( C , A , n ) ;
	for ( register int i = 0 ; i < n ; i ++ )
		ans[ i ] = C[ i ].a / n + 0.1 , A[ i ] = null , B[ i ] = null ;
	for ( register int i = 0 ; i < n ; i ++ )
		if ( ans[ i ] >= M ) ans[ i + 1 ] += ans[ i ] / M , ans[ i ] %= M ;
	while ( n > 1 && ans[ n - 1 ] <= 0 ) n -- ;
	printf( "%lld" , ans[ n - 1 ] ) ;
	for( register int i = n - 2 ; i >= 0 ; i -- ) printf( "%06lld" , ans[ i ] );
	puts( "" ) ;
	return true ;
}
