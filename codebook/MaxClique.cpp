#include <bits/stdc++.h>
using namespace std;
#define N 64
#define ll unsigned long long
ll nb[ N ];
ll getint(){
    ll x=0LLU; char c=getchar();
    while( c<'0'||c>'9' ) c=getchar();
    while(c>='0'&&c<='9') x*=10LLU,x+=(c-'0'),c=getchar();
    return x;
}
ll n , ans , tmp;
void init(){
    n = getint(); ans = 1LLU;
    for( ll i = 0LLU ; i < n ; i ++ ){
        nb[ i ] = 0LLU;
        for( ll j = 0LLU ; j < n ; j ++ ){
            tmp = getint();
            if( tmp ) nb[ i ] |= ( 1LLU << j );
        }
    }
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
void process(){
    if( n < 64LLU ) B( 0LLU , ( 1LLU << n ) - 1LLU , 0LLU , 0LLU , n );
    else{
        ll b = 0LLU;
        for( ll i = 0LLU ; i < 64LLU ; i ++ )
            b |= ( 1LLU << i );
        B( 0LLU , b , 0LLU , 0LLU , n );
    }
    printf( "%llu\n" , ans );
}
int main(){
    ll t; t = getint(); while( t -- ){
        init(); process();
    }
}
