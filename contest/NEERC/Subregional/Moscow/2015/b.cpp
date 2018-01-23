#include <bits/stdc++.h>

using namespace std;

const int MAXL = 2000010;
const int MAXN = 500010;

void Z_value(char *s, int *z, int len) {
  int i,j,left,right;
  left=right=0; z[0]=len;
  for(i=1;i<len;i++) {
    j=max(min(z[i-left],right-i),0);
    for(;i+j<len&&s[i+j]==s[j];j++);
    z[i]=j;
    if(i+z[i]>right) {
      right=i+z[i];
      left=i;
    }
  }
}

int n , m;
char A[ MAXL ] , B[ MAXL ];
char s1[ MAXL ] , s2[ MAXL ];
int z1[ MAXL ] , z2[ MAXL ];

vector< int > pos1[ MAXN ] , pos2[ MAXN ];

int main()
{
  scanf( "%s%s" , A+1 , B+1 );
  n = strlen( A+1 );
  m = strlen( B+1 );
  if( n < m )
  {
    puts( "-1" );
    return 0;
  }
  strncpy( s1+1 , B+1 , m );
  strncpy( s1+m+1 , A+1 , n );
  strncpy( s1+m+n+1 , A+1 , n );
  strncpy( s2+1 , s1+1 , m+n+n );
  reverse( s2+1 , s2+m+1 );
  reverse( s2+m+1 , s2+m+n+n+1 );

  Z_value( s1+1 , z1+1 , m+n+n );
  Z_value( s2+1 , z2+1 , m+n+n );

  for( int i = m+1 ; i <= m+n+n ; i++ )
  {
    int tz = min( m , z1[ i ] );
    pos1[ tz ].push_back( i );
  }

  for( int i = m+1 ; i <= m+n+n ; i++ )
  {
    int tz = min( m , z2[ i ] );
    int np = m + m+n+n - i + 1;
    pos2[ tz ].push_back( np );
  }

  set< int > st;

  int ans = -1;

  for( int tz = 0 ; tz <= m ; tz++ )
  {
    int zt = m - tz;
    for( int j : pos2[ zt ] ) st.insert( j );
    for( int i : pos1[ tz ] )
    {
      auto it = st.lower_bound( i-1+m-n );
      int pj = MAXL;
      if( it != st.end() )
        pj = *st.lower_bound( i-1+m-n );
      int tl = i - pj - 1 + m;
      if( i - pj - 1 >= 0 )
      {
        //printf( "pj %d i %d\n" , pj , i );
        ans = max( ans , tl );
      }
    }
  }

  printf( "%d\n" , ans );

}
