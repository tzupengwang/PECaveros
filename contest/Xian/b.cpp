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
int num( char ctmp ){
    if( ctmp == 'F' ) return 1;
    if( ctmp == 'W' ) return 2;
    if( ctmp == 'P' ) return 3;
    if( ctmp == 'L' ) return 4;
    if( ctmp == 'D' ) return 5;
    if( ctmp == 'C' ) return 6;
    return 0;
}
char c[ 9 ][ 9 ];
void build(){

}
int s[ 5 ][ 6 ];
int ts[ 5 ][ 6 ];
bool can[ 9 ][ 9 ];
bool el(){
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 6 ; j ++ )
            can[ i ][ j ] = false;
    bool flag = false;
    for( int i = 0 ; i < 3 ; i ++ )
        for( int j = 0 ; j < 6 ; j ++ )
            if( ts[ i ][ j ] )
                if( ts[ i + 1 ][ j ] == ts[ i ][ j ] &&
                    ts[ i + 2 ][ j ] == ts[ i ][ j ] ){
                    can[ i ][ j ] =
                    can[ i + 1 ][ j ] =
                    can[ i + 2 ][ j ] = true;
                    flag = true;
                }
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 4 ; j ++ )
            if( ts[ i ][ j ] )
                if( ts[ i ][ j + 1 ] == ts[ i ][ j ] &&
                    ts[ i ][ j + 2 ] == ts[ i ][ j ] ){
                    can[ i ][ j ] =
                    can[ i ][ j + 1 ] =
                    can[ i ][ j + 2 ] = true;
                    flag = true;
                }
    return flag;
}
int dx[]={0,1,-1,0};
int dy[]={1,0,0,-1};
int tcnt;
bool in( int ti , int tj ){
    return 0 <= ti && ti < 5 && 0 <= tj && tj < 6;
}
void DFS( int ti , int tj ){
    can[ ti ][ tj ] = false; tcnt ++;
    for( int i = 0 ; i < 4 ; i ++ )
        if( in( ti + dx[ i ] , tj + dy[ i ] ) &&
            ts[ ti + dx[ i ] ][ tj + dy[ i ] ] == ts[ ti ][ tj ] &&
            can[ ti + dx[ i ] ][ tj + dy[ i ] ] )
            DFS( ti + dx[ i ] , tj + dy[ i ] );
    ts[ ti ][ tj ] = 0;
}
void Drop(){
    for( int j = 0 ; j < 6 ; j ++ ){
        int con = 0 , pre = 4;
        for( int i = 4 ; i >= 0 ; i -- )
            if( ts[ i ][ j ] ){
                if( con ){
                    ts[ pre ][ j ] = ts[ i ][ j ];
                    ts[ i ][ j ] = 0;
                    while( ts[ pre ][ j ] ) pre --;
                }
            }else{
                con ++;
                if( con == 1 ) pre = i;
            }
    }
}
pair<int,int> eva(){
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 6 ; j ++ )
            ts[ i ][ j ] = s[ i ][ j ];
    int combo = 0, drop = 0;
    while( el() ){
        //for( int i = 0 ; i < 5 ; i ++ , puts( "" ) )
        //    for( int j = 0 ; j < 6 ; j ++ )
        //        printf( "%d" , ts[ i ][ j ] );
        for( int i = 0 ; i < 5 ; i ++ )
            for( int j = 0 ; j < 6 ; j ++ )
                if( can[ i ][ j ] ){
                    tcnt = 0;
                    DFS( i , j );
                    combo ++;
          //          printf( "%d %d %d\n" , i , j , combo );
                    drop += tcnt;
                }
        Drop();
    }
    return MP( combo , drop );
}
void init(){
    for( int i = 0 ; i < 5 ; i ++ ) scanf( "%s" , c[ i ] );
    for( int i = 0 ; i < 5 ; i ++ ){
        for( int j = 0 ; j < 6 ; j ++ )
            s[ i ][ j ] = num( c[ i ][ j ] );
    }
}
int anscombo , ansdrop , anslen , ax , ay;
vector<int> vans , nv;
int sx , sy;
void DFS( int pre , int nx , int ny , int len ){
    if( len ){
        pair<int,int> tp = eva();
        if( MT( -tp.FI , -tp.SE , len ) <
            MT( -anscombo , -ansdrop , anslen ) ){
            anscombo = tp.FI;
            ansdrop = tp.SE;
            anslen = len;
            vans = nv;
            ax = sx;
            ay = sy;
        }
    }
    if( len >= 9 ) return;
    for( int i = 0 ; i < 4 ; i ++ ) if( i + pre != 3 )
        if( in( nx + dx[ i ] , ny + dy[ i ] ) ){
            int nxtx = nx + dx[ i ];
            int nxty = ny + dy[ i ];
            nv.PB( i );
            swap( s[ nx ][ ny ] , s[ nxtx ][ nxty ] );
            DFS( i , nxtx , nxty , len + 1 );
            nv.pop_back();
            swap( s[ nx ][ ny ] , s[ nxtx ][ nxty ] );
        }
}
char cc[]="RDUL";
void solve(){
    pair<int,int> tp = eva();
    anscombo = tp.FI;
    ansdrop = tp.SE;
    anslen = 2;
    ax = 1; ay = 1;
    vans.clear();
    vans.PB( 0 );
    vans.PB( 3 );
    for( int i = 0 ; i < 5 ; i ++ )
        for( int j = 0 ; j < 6 ; j ++ ){
            sx = i + 1;
            sy = j + 1;
            nv.clear();
            DFS( -1 , i , j , 0 );
        }
    printf( "Case #%d:\n" , ++ cs );
    printf( "Combo:%d Length:%d\n" , anscombo , anslen );
    printf( "%d %d\n" , ax , ay );
    for( int i = 0 ; i < anslen ; i ++ )
        putchar( cc[ vans[ i ] ] );
    puts( "" );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
