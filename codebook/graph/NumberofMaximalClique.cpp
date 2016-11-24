// bool g[][] : adjacent array indexed from 1 to n
void dfs(int sz){
	int i, j, k, t, cnt, best = 0;
	if(ne[sz]==ce[sz]){ if (ce[sz]==0) ++ans; return; }
	for(t=0, i=1; i<=ne[sz]; ++i){
		for (cnt=0, j=ne[sz]+1; j<=ce[sz]; ++j)
		if (!g[lst[sz][i]][lst[sz][j]]) ++cnt;
		if (t==0 || cnt<best) t=i, best=cnt;
	} if (t && best<=0) return;
	for (k=ne[sz]+1; k<=ce[sz]; ++k) {
		if (t>0){ for (i=k; i<=ce[sz]; ++i) 
		    if (!g[lst[sz][t]][lst[sz][i]]) break;
			swap(lst[sz][k], lst[sz][i]);
		} i=lst[sz][k]; ne[sz+1]=ce[sz+1]=0;
		for (j=1; j<k; ++j)if (g[i][lst[sz][j]]) 
		    lst[sz+1][++ne[sz+1]]=lst[sz][j];
		for (ce[sz+1]=ne[sz+1], j=k+1; j<=ce[sz]; ++j)
		if (g[i][lst[sz][j]]) lst[sz+1][++ce[sz+1]]=lst[sz][j];
		dfs(sz+1); ++ne[sz]; --best;
		for (j=k+1, cnt=0; j<=ce[sz]; ++j) if (!g[i][lst[sz][j]]) ++cnt;
		if (t==0 || cnt<best) t=k, best=cnt;
		if (t && best<=0) break;
}}
void work(){
	ne[0]=0; ce[0]=0;
	for(int i=1; i<=n; ++i) lst[0][++ce[0]]=i;
	ans=0; dfs(0);
}
