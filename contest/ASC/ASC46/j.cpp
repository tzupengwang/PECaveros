#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double D;
unordered_map<int,int> M;
typedef unordered_map<int,int>::iterator mi; 
#define N 100010
int __ , n;
char c[ N ];
int pre[ N ][ 26 ], lst[ 26 ];
void init(){
    scanf( "%s" , c + 1 );
    n = strlen( c + 1 );
    for( int i = 0 ; i < 26 ; i ++ ) lst[ i ] = 0;
    for( int i = 1 ; i <= n ; i ++ ){
        for( int j = 0 ; j < 26 ; j ++ )
            pre[ i ][ j ] = lst[ j ];
        lst[ c[ i ] - 'a' ] = i;
    }
}
ll sz( int tmp ){
    ll cnt = 0;
    //while( tmp ){
    //    cnt ++;
    //    tmp -= (tmp & (-tmp));
    //}
    for( int i = 0 ; i < 26 ; i ++ )
        if( tmp & ( 1 << i ) )
            cnt ++;
    return cnt;
}
void solve(){
    M.clear();
    for( int i = 1 ; i <= n ; i ++ ){
        int now = i , st = ( 1 << ( c[ i ] - 'a' ) );
        M[ st ] = max( M[ st ] , 1 );
        while( now > 1 ){
            int nxt = -1 , tpre = -1;
            for( int j = 0 ; j < 26 ; j ++ )
                if( pre[ i ][ j ] && ( !( ( 1 << j ) & st ) ) ){
                    if( pre[ i ][ j ] > nxt ){
                        nxt = pre[ i ][ j ];
                        tpre = j;
                    }
                }
            if( tpre == -1 ){
                M[ st ] = max( M[ st ] , i );
                break;
            }
            M[ st ] = max( M[ st ] , i - nxt );
            st ^= ( 1 << tpre );
            now = nxt;
            M[ st ] = max( M[ st ] , i - now + 1 );
        }
    }
    ll ans = 0;
    for( mi it = M.begin() ; it != M.end() ; it ++ )
        ans += sz( it->first ) * it->second;
    cout << (int)M.size() << " " << ans << endl;
}
int main(){
    freopen( "jingles.in" , "r" , stdin );
    freopen( "jingles.out" , "w" , stdout );
    scanf( "%d" , &__ ); while( __ -- ){
        init();
        solve();
    }
}
