#include <bits/stdc++.h>
using namespace std;
string buf;
int main(){
    int t;
    getline(cin, buf);
    stringstream ss(buf);
    ss>>t;
    while(t --){
        getline(cin, buf);
        stringstream in(buf);
        vector<long long> v;
        string cand;
        while(in >> cand){
            if((int)cand.length() == 1){
            if(cand[0] == '+'){
                long long a=v.back(); v.pop_back();
                long long b=v.back(); v.pop_back();
                v.push_back(a+b);
                continue;
            }
            if(cand[0] == '-' and (int)cand.length() == 1){
                long long a=v.back(); v.pop_back();
                long long b=v.back(); v.pop_back();
                v.push_back(b-a);
                continue;
            }
            if(cand[0] == '*'){
                long long a=v.back(); v.pop_back();
                long long b=v.back(); v.pop_back();
                v.push_back(a*b);
                continue;
            }
            }
            long long val=0, sgn=1;
            size_t st=0;
            if(cand[0] == '-'){
                st=1;
                sgn=-1;
            }
            for(size_t i=st; i<cand.length(); i++)
                val=val*10+(cand[i] - '0');
            v.push_back(val*sgn);
        }
        cout<<v.back()<<endl;
    }
}
