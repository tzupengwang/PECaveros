#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 310;
const ll  MOD  = 1000000007ll;

inline ll add(ll a,ll b){return (a+b)%MOD;}
inline ll mul(ll a,ll b){return (a*b)%MOD;}
inline ll sub(ll a,ll b){return (a-b+MOD)%MOD;}

ll C[ MAXN ][ MAXN ];
int n , k , in[ MAXN ] , sum[ MAXN ];
ll dp[ MAXN ][ MAXN ];

int main2()
{
    cin >> n >> k;
    for( int i = 1 ; i <= k ; i++ )
        cin >> in[ i ];
    for( int i = 1 ; i <= k ; i++ )
        sum[ i ] = sum[ i - 1 ] + in[ i ]; 
    C[ 0 ][ 0 ] = 1ll;
    for( int i = 1 ; i <= n ; i++ )
    {
        C[ i ][ 0 ] = 1;
        for( int j = 1 ; j <= i ; j++ )
            C[ i ][ j ] = add( C[ i - 1 ][ j ] , C[ i - 1 ][ j - 1 ] );
    }
    dp[ 0 ][ 0 ] = 1ll;
    for( int i = 1 ; i <= k ; i++ )
    {
        for( int j = 1 ; j <= i ; j++ )
        {
            dp[ i ][ j ] = 0ll;
            for( int k = j ; k <= i ; k++ )
            {
                int rest = n - sum[ k-1 ];
                int tot = sum[ i ] - sum[ k-1 ];
                ll tmp = mul( dp[ k-1 ][ j-1 ] , C[ rest ][ tot ] );
                dp[ i ][ j ] = add( dp[ i ][ j ] , tmp );
            }
        }
    }
    ll ans = 0ll;
    ll sgn = 1;
    for( int i = 0 ; i < k ; i++ )
    {
        ans = add( ans , mul( dp[ k ][ k-i ] , (sgn+MOD)%MOD ) );
        sgn *= -1;
    }
    cout << ans << '\n';

}

int main()
{
#ifdef ONLINE_JUDGE
    freopen("monotonic.in" , "r" , stdin );
    freopen("monotonic.out" , "w" , stdout );
#endif
    main2();
}
