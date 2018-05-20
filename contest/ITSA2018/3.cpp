#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin>>t; while(t--){
        string a;
        cin>>a;
        int cand=-1;
        while(true){
        cand=-1;
        int len=a.length();
        for(int i=0; i+1<len; i++)
            if(a[i] < a[i+1]){
                cand=i;
                break;
            }
        if(cand != -1){
            string ret="";
            for(int i=0; i<cand; i++)
                ret+=a[i];
            ret+=(char)(a[cand]+1);
            for(int i=cand+1; i<len; i++)
                ret+='0';
            a=ret;
        }else break;
        }
        cout<<a<<"\n";
    }
}
