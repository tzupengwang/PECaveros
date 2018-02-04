#include<bits/stdc++.h>
using namespace std;


typedef pair<int, int> ii;
int N;
int seq[1000005];
bool bd[1000005];
ii bp[1000005];
int pre[1000005];
int nxt[1000005];
int Rp[1000005];
int Lp[1000005];

int try2(int L, int R, ii x, ii y) {
  if (x.first == y.first) return 0;
  if (x.first <= L || x.second >= R || y.first <= L || y.second >= R) return 0;
  if (x.first > y.first) swap(x, y);
  int l1 = x.first - L, l2 = R - y.second;
  if (l1 == l2) {
    return 1;
  } else if (l1 + 1 == l2 || l1 == l2 + 1) {
    return 2;
  }
  return 0;
}


#define K (1 << 20)

int is[ K ] , ds[ K ];

bool mono( int l , int r ){
  return (is[ r ] - is[ l ] == 0) or
         (ds[ r ] - ds[ l ] == 0);
}

int solve(int L, int R, int S = 0) {
  //int len = R - L + 1;
  if( mono( L , R ) ) return 1;
  else {
    int bps = Rp[R - 1] - Lp[L];
    bps = max( bps , 0 );
    //printf("bps %d %d = %d\n", Rp[R - 1], Lp[L], bps);
    if (bps == 0) return 1;
    //else if (bps == 1) {
      //int pos = nxt[L + 1];
      //ii pp = bp[pos];
      //if (pp.first == L + 1 || pp.second == R - 1) puts("Alice");
      //else {
        //int stp = R - L - (pp.second - pp.first);
        //if (stp % 2) puts("Alice");
        //else puts("Bob");
      //}
    //}
    else {
      int md1 = (R + L) / 2;
      int md2 = (R + L + 1) / 2;
      deque<ii> dq;
      {
        int ps = pre[md1];
        for (int i = 0; i <= 2; i ++) {
          dq.push_front(bp[ps]);
          if (ps > 0) ps = pre[ps - 1];
        }
      }
      {
        int ps = nxt[md2];
        for (int i = 0; i <= 2; i ++) {
          dq.push_back(bp[ps]);
          if (ps <= N) ps = nxt[ps + 1];
        }
      }
      for (int i = 0; i + 1 < (int)dq.size(); i ++) {
        ii x = dq[i], y = dq[i + 1];
        int xx;
        if ((xx = try2(L, R, x, y))) return xx;
      }
      ii bst = ii(-1, -1);
      for (int i = 0; i < (int)dq.size(); i ++) {
        if (dq[i].first <= L || dq[i].second >= R) continue;
        if (bst.first == -1) bst = dq[i];
        else {
          int t1 = min(R - bst.second, bst.first - L);
          int t2 = min(R - dq[i].second, dq[i].first - L);
          if (t2 > t1) {
            bst = dq[i];
          }
        }
      }
      int stp = R - L - (bst.second - bst.first);
      if (stp % 2) return 2;
      else return 1;
    }
  }
}


//int Q , ql[ X ] , qr[ X ];
//int BIT[ X ] , lb[ X ];

#define SM 50
typedef long long LL;
unordered_map< LL , bool > res;

bool Win( int l , int r ){
  if( mono( l , r ) ) return false;
  LL id = (((LL)l) << 20 ) | r;
  auto it = res.find( id );
  if( it != res.end() ) return it->second;
  return res[ id ] = not Win( l + 1 , r ) or
                     not Win( l , r - 1 );
  //if( gt[ l ][ r ] ) return win[ l ][ r ];
  //gt[ l ][ r ] = true;
  //if( not Win( l + 1 , r ) or
      //not Win( l , r - 1 ) )
    //return win[ l ][ r ] = true;
  //return win[ l ][ r ] = false;
}

int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i ++) {
    scanf("%d", &seq[i]);
  }
  
  for( int i = 2 ; i <= N ; i ++ ){
    if( seq[ i ] > seq[ i - 1 ] ) is[ i ] ++;
    if( seq[ i ] < seq[ i - 1 ] ) ds[ i ] ++;
    is[ i ] += is[ i - 1 ];
    ds[ i ] += ds[ i - 1 ];
  }


  bd[0] = bd[N + 1] = true;
  bp[0] = ii(0, 0), bp[N + 1] = ii(N + 1, N + 1);
  pre[0] = 0;
  nxt[N + 1] = N + 1;
  for (int i = 2; i < N;) {
    int j = i;
    while (j <= N && seq[i] == seq[j]) j ++;
    if (j > N) break;

    if (seq[i] < seq[i - 1] && seq[i] < seq[j]) bd[i] = true, bp[i] = ii(i, j - 1), Lp[i] ++, Rp[j - 1] ++;
    else if (seq[i] > seq[i - 1] && seq[i] > seq[j]) bd[i] = true, bp[i] = ii(i, j - 1), Lp[i] ++, Rp[j - 1] ++;

    i = j;
  }
  for (int i = 1; i <= N + 1; i ++) {
    if (bd[i]) pre[i] = i;
    else pre[i] = pre[i - 1];

    Lp[i] += Lp[i - 1];
    Rp[i] += Rp[i - 1];
    //printf("=== %d %d\n", Lp[i], Rp[i]);
  }
  for (int i = N; i >= 0; i --) {
    if (bd[i]) nxt[i] = i;
    else nxt[i] = nxt[i + 1];
  }

  //for( int i = 1 ; i <= N ; i ++ )
    //for( int j = i ; j <= N ; j ++ ){
      //printf( "%d %d : \n" , i , j );
      //solve( i , j );
      //if( Win( i , j ) ) puts( "Alice" );
      //else puts( "Bob" );
    //}



  int Q; scanf("%d", &Q);
  //for( int i = 0 ; i < Q ; i ++ )
    //scanf( "%d%d" , &ql[ i ] , &qr[ i ] );
  for (int i = 0; i < Q; i ++) {
    //solve( ql[ i ], qr[ i ] );
    int L, R;
    scanf("%d%d", &L, &R);
    if( R - L < SM )
      puts( Win( L , R ) ? "Alice" : "Bob" );
    else {
      int l1 = solve(L + 1, R);
      int l2 = solve(L, R - 1);
      if (l1 == 2 && l2 == 2) puts("Bob");
      else puts("Alice");
      //puts( solve(L, R) == 1 ? "Bob" : "Alice" );
    }
  }
}
