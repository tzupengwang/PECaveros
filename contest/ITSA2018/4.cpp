#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
string s;
void cal(){
    unordered_set<LL> cand;
    int len=s.length();
    for(int i=1; i<(1 << len); i++){
        LL a=0;
        for(int j=0; j<len; j++)
            if((i >> j) & 1)
                a=a*10+(s[j] - '0');
        cand.insert(a);
    }
    cout<<cand.size()<<"\n";
    //sort(cand.begin(), cand.end());
}
int main(){
    while(cin>>s){
        cal();
    }
}
