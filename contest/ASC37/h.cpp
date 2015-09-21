#include <bits/stdc++.h>
using namespace std;
#define N 100010
typedef long long ll;
ll getint(){
    ll x = 0, tmp = 1; char c=getchar();
    while( (c<'0'||c>'9')&&c!='-' ) c=getchar();
    if( c == '-' ) c=getchar(), tmp = -1;
    while( c>='0'&&c<='9' ) x*=10,x+=(c-'0'),c=getchar();
    return x * tmp;
}
ll ans[ N ] , s[ N ] , v[ N ] , can[ N ];
ll n , m , c;
priority_queue< pair<ll,int> , vector< pair<ll,int> > , greater< pair<ll,int> > > man;
// free time , idx
priority_queue< pair<ll,int> , vector< pair<ll,int> > , greater< pair<ll,int> > > cargo[ 11 ];
// in time , idx
void init(){
    n = getint();
    m = getint();
    c = getint();
    for( int i = 0 ; i < n ; i ++ ){
        ll tt , tc;
        tt = getint();
        tc = getint();;
        s[ i ] = getint();
        cargo[ tc ].push( make_pair( tt , i ) );
    }
    for( int i = 0 ; i < m ; i ++ ){
        v[ i ] = getint();
        ll tk = getint();
        while( tk -- ){
            ll tmp = getint();
            can[ i ] |= ( 1ll << tmp );
        }
        man.push( make_pair( 0 , i ) );
    }
}
void solve(){
    while( man.size() ){
        int lidx = -1 , lc = -1;
        ll ltime = -1;
        pair<ll,int> np = man.top(); man.pop();
        for( int i = 1 ; i <= c ; i ++ )
            if( ( can[ np.second ] & ( 1ll << i ) ) && cargo[ i ].size() ){
                pair<ll,int> tp = cargo[ i ].top();
                if( ltime == -1 || ( tp.first < ltime ) ||
                    ( tp.first == ltime && tp.second < lidx ) ){
                    ltime = tp.first;
                    lidx = tp.second;
                    lc = i;
                }
            }
        if( lc == -1 )
            continue;
        cargo[ lc ].pop();
        ll rtime = max( np.first , ltime );
        ll ndtime = s[ lidx ] / v[ np.second ] + ( s[ lidx ] % v[ np.second ] != 0 );
        ans[ lidx ] = np.second;
        man.push( make_pair( rtime + ndtime , np.second ) );
    }
    for( int i = 0 ; i < n ; i ++ )
        cout << ans[ i ] + 1 << endl;
}
int main(){
    freopen( "seaport.in" , "r" , stdin );
    freopen( "seaport.out" , "w" , stdout );
    init();
    solve();
}
