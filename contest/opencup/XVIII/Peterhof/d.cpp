#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
char buf[ 1024 ];
LL tot[ 40 ];
#define L first
#define V second
void dec( pair<int,LL>& np ){
  np.V = (np.V - 1 + tot[ np.L ]) % tot[ np.L ];
}
void inc( pair<int,LL>& np ){
  np.V = (np.V + 1 ) % tot[ np.L ];
}
void down( pair<int,LL>& np ){
  np.V /= 3;
  np.L --;
}
void up( pair<int,LL>& np ){
  np.V *= 3;
  np.L ++;
}
pair<int,LL> read(){
  scanf( "%s" , buf );
  int nl = 0; LL nv = 0;
  for( int i = 0 ; buf[ i ] ; i ++ )
    if( buf[ i ] == 'c' ){
      nl ++;
      nv *= 3;
    }else if( buf[ i ] == 'g' ){
      nl --;
      nv /= 3;
    }else if( buf[ i ] == 's' )
      nv = (nv + 1) % tot[ nl ];
    else
      nv = (nv - 1 + tot[ nl ]) % tot[ nl ];
  return { nl , nv };
}
int main(){
  tot[ 0 ] = 1;
  for( int i = 1 ; i < 40 ; i ++ )
    tot[ i ] = tot[ i - 1 ] * 3;
  pair<int,LL> s = read();
  pair<int,LL> t = read();
  //cerr << s.first << " " << s.second << endl;
  //cerr << t.first << " " << t.second << endl;
  string lans = "" , rans = "";
  while( s.L > t.L ){
    if( s.V % 3 == 1 ){
      dec( s );
      lans = lans + "a";
    }else if( s.V % 3 == 2 ){
      inc( s );
      lans = lans + "s";
    }
    down( s );
    lans = lans + "g";
  }
  while( s.L < t.L ){
    if( t.V % 3 == 1 ){
      dec( t );
      rans = "s" + rans;
    }else if( t.V % 3 == 2 ){
      inc( t );
      rans = "a" + rans;
    }
    down( t );
    rans = "c" + rans;
  }
  while( s.V != t.V ){
    LL up = (t.V - s.V + tot[ s.L ]) % tot[ s.L ];
    LL dn = (s.V - t.V + tot[ s.L ]) % tot[ s.L ];
    if( up < dn ){
      if( up <= 4 ){
        for( int i = 0 ; i < up ; i ++ )
          lans = lans + "s";
        break;
      }
    }else{
      if( dn <= 4 ){
        for( int i = 0 ; i < dn ; i ++ )
          rans = "a" + rans;
        break;
      }
    }
    if( s.V % 3 == 1 ){
      dec( s );
      lans = lans + "a";
    }else if( s.V % 3 == 2 ){
      inc( s );
      lans = lans + "s";
    }
    down( s );
    lans = lans + "g";
    if( t.V % 3 == 1 ){
      dec( t );
      rans = "s" + rans;
    }else if( t.V % 3 == 2 ){
      inc( t );
      rans = "a" + rans;
    }
    down( t );
    rans = "c" + rans;
    //cout << lans << rans << endl;
  }
  cout << lans << rans << endl;
}
