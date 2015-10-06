// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
    ll _x=0,_tmp=1; char _tc=getchar();    
    while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
    if( _tc == '-' ) _tc=getchar() , _tmp = -1;
    while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
    return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
    if( _x == 0 ) return 1ll;
    ll _tmp = mypow( _a , _x / 2 , _mod );
    _tmp = ( _tmp * _tmp ) % _mod;
    if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
    return _tmp;
}
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 110
vector<int> v[ N ];
int n , m , x , y;
int dp[ N ][ N ][ 2 ];
int indeg[ N ][ N ][ 2 ];
vector< tuple<int,int,int> > nxt_st[ N ][ N ][ 2 ];
void build(){

}
void init(){
    n = getint(); m = getint();
    for( int i = 1 ; i <= n ; i ++ ){
        v[ i ].clear();
        for( int j = 1 ; j <= n ; j ++ ){
            dp[ i ][ j ][ 0 ] = 0;
            dp[ i ][ j ][ 1 ] = 0;
            indeg[ i ][ j ][ 0 ] = 0;
            indeg[ i ][ j ][ 1 ] = 0;
            nxt_st[ i ][ j ][ 0 ].clear();
            nxt_st[ i ][ j ][ 1 ].clear();
        }
    }
    while( m -- ){
        int d = getint();
        int e = getint();
        v[ d ].PB( e );
    }
    x = getint(); y = getint();
}
// 1 1st win
queue< tuple<int,int,int> > Q;
void find_state(){
    while( Q.size() ) Q.pop();
    for( int i = 1 ; i <= n ; i ++ )
        for( int j = 1 ; j <= n ; j ++ ){
            if( i == j ){
                Q.push( MT( i , j , 0 ) );
                Q.push( MT( i , j , 1 ) );
                dp[ i ][ j ][ 0 ] = 2;
                dp[ i ][ j ][ 1 ] = 2;
                continue;
            }
// 0 -> first
            if( (int)v[ i ].size() == 0 ){
                Q.push( MT( i , j , 0 ) );
                dp[ i ][ j ][ 0 ] = 2;
            }
            for( int k = 0 ; k < (int)v[ i ].size() ; k ++ ){
                nxt_st[ v[ i ][ k ] ][ j ][ 1 ].PB( MT( i , j , 0 ) );
                indeg[ i ][ j ][ 0 ] ++;
            }
            for( int k = 0 ; k < (int)v[ j ].size() ; k ++ ){
                nxt_st[ i ][ v[ j ][ k ] ][ 0 ].PB( MT( i , j , 1 ) );
                indeg[ i ][ j ][ 1 ] ++;
            }
        }
    while( Q.size() ){
        tuple<int,int,int> tp = Q.front(); Q.pop();
        int nx = get<0>( tp );
        int ny = get<1>( tp );
        int np = get<2>( tp );
        /*if( !dp[ nx ][ ny ][ np ] ){
            int tans = 0;
            if( np == 1 ){
                tans = 1;
                for( int j = 0 ; j < (int)v[ ny ].size() ; j ++ )
                    if( dp[ nx ][ v[ ny ][ j ] ][ 0 ] == 2 )
                        tans = 2;
            }else{
                int notokay = 0;
                for( int j = 0 ; j < (int)v[ nx ].size() ; j ++ )
                    if( dp[ v[ nx ][ j ] ][ ny ][ 1 ] == 2 )
                        notokay ++;
                tans = 1;
                if( notokay == (int)v[ nx ].size() )
                    tans = 2;
            }
            dp[ nx ][ ny ][ np ] = tans;
        }*/
        for( int i = 0 ; i < (int)nxt_st[ nx ][ ny ][ np ].size() ; i ++ ){
            tuple<int,int,int> tp2 = nxt_st[ nx ][ ny ][ np ][ i ];
            int ux = get<0>( tp2 ); 
            int uy = get<1>( tp2 ); 
            int up = get<2>( tp2 );
            if( up == 1 ){
                if( dp[ ux ][ uy ][ up ] != 2 ){
                    dp[ ux ][ uy ][ up ] = 2;
                    Q.push( tp2 );
                }
            }else{
                indeg[ ux ][ uy ][ up ] --;
                if( indeg[ ux ][ uy ][ up ] == 0 ){
                    if( dp[ ux ][ uy ][ up ] != 2 ){
                        dp[ ux ][ uy ][ up ] = 2;
                        Q.push( tp2 );
                    }
                }
            }
        }
    }
}
void solve(){
    find_state();
    printf( "Case #%d: " , ++ cs );
    puts( dp[ x ][ y ][ 0 ] == 2 ? "No" : "Yes" );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
