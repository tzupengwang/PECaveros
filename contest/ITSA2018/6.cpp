#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000007LL;

ll dp[1000005];

int main(){
    int t; cin>>t; while(t--){
        int n, k;
        scanf("%d%d", &n, &k);

        ll k2 = 1;
        for (int i = 1; i <= k - 1; i ++)
            k2 = k2 * 2 % mod;

        k2 = (k2 + mod - 1) % mod;

        ll tot = 1;
        dp[0] = 1;
        for (int i = 1; i <= n; i ++) {
            dp[i] = tot;
            if (i >= k) dp[i] = (dp[i] + dp[i - k] * k2) % mod;

            tot = (tot + dp[i]) % mod;
        }
        printf("%lld\n", dp[n]);
    }
}

