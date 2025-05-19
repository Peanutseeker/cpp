#include<bits/stdc++.h>
using namespace std;

const int MAXN=5e6,INF=1e9;

int Read()
{
	char c;
	while(!isdigit(c=getchar()));
	int res=c-'0';
	while(isdigit(c=getchar())) res=res*10+c-'0';
	return res;
}

int n,m,ans;
int A[MAXN+5],B[MAXN+5];
int Head[MAXN+5],loc[2*MAXN+5],nxt[2*MAXN+5],tot;
int inD[MAXN+5];

void Insert(int x,int v) {loc[++tot]=v,nxt[tot]=Head[x],Head[x]=tot;}

int dist[MAXN+5],Q[MAXN+5],L,R;
void BFS()
{
	for(int i=1;i<=n;i++) dist[i]=INF;
	dist[1]=0,Q[L=R=1]=1;
	while(L<=R)
	{
		int now=Q[L++];
		for(int i=Head[now];i;i=nxt[i])
		{
			int rear=loc[i];
			if(dist[rear]>dist[now]+1)
			{
				dist[rear]=dist[now]+1;
				Q[++R]=rear;
			}
		}
	}
}

int col[MAXN+5],cnt;
void DFS(int now)
{
	if(col[now]) return;
	col[now]=cnt;
	for(int i=Head[now];i;i=nxt[i]) if(dist[loc[i]]==dist[now]) DFS(loc[i]);
}

int main()
{
	n=Read(),m=Read();
	for(int i=1;i<=m;i++)
	{
		A[i]=Read(),B[i]=Read();
		Insert(A[i],B[i]);
		Insert(B[i],A[i]);
	}
	BFS();
	for(int i=1;i<=n;i++) if(!col[i]) ++cnt,DFS(i);
	//for(int i=1;i<=n;i++) printf("%d ",dist[i]);printf("\n");
	//for(int i=1;i<=n;i++) printf("%d ",col[i]);printf("\n");
	for(int i=1;i<=m;i++)
		if(dist[B[i]]==dist[A[i]]+1) ++inD[col[B[i]]];
		else if(dist[A[i]]==dist[B[i]]+1) ++inD[col[A[i]]];
	ans=m;
	for(int i=1;i<=cnt;i++) if(inD[i]==1) --ans;
	printf("%d\n",ans);
	return 0;
}
