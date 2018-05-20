#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MX = 10000;
char buf[MX];
int len;
LL k;
int vowel;
LL way[MX];
LL mul(LL x, LL y){
    if(x > (1LL << 48) / y) return (1LL << 48);
    return x * y;
}
void solve(){
    vector<int> v;
    for(int i=0; i<len;){
        if(buf[i] == '*'){
            v.push_back(vowel);
            i++;
            continue;
        }
        if(isalpha(buf[i])){
            v.push_back((1 << (buf[i] - 'a')));
            i++;
            continue;
        }
        int msk=0;
        i++;
        while(buf[i] != ']'){
            msk |= (1 << (buf[i] - 'a'));
            i++;
        }
        i++;
        v.push_back(msk);
    }
    len=v.size();
    way[len]=1;
    for(int i=len-1; i>=0; i--){
        way[i]=mul(way[i+1], __builtin_popcount(v[i]));
    }
    if(k > way[0]){
        puts("*");
        return;
    }


    string ans;
    for(int i=0; i<len; i++){
        LL base=way[i+1];
        for(int j=0; j<26; j++)
            if((v[i] >> j) & 1){
                if(k <= base){
                    ans += (j + 'a');
                    break;
                }
                k -= base;
            }
    }
    cout<<ans<<"\n";
}
int main(){
    for(char cc : {'a', 'e', 'i', 'o', 'u'})
        vowel |= (1 << (cc - 'a'));
    int t; scanf("%d", &t); while(t--){
        scanf("%s", buf);
        len=strlen(buf);
        scanf("%lld", &k);
        solve();
    }
}
