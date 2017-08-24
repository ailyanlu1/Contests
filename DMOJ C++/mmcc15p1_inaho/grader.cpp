#include "inaho.h"
#include <stdio.h>
#include <stdlib.h>

#define ensured(x, y) ensure(x, y)

static inline void ensure(int cond, const char *msg)
{
    if(!cond)
    {
        printf("REJECTED %s\n", msg);
        exit(0);
    }
}

#define MAXN 500000
#define MAXQ 1000000

static int TEST, N, M;
static int Q[MAXQ][3];
static int ans[MAXQ], NANS;

static void read_input()
{
    ensured(scanf("%d%d", &N, &M)==2, "cannot read N and M");
    ensured(1<=N && N<=MAXN, "number of vertices out of bounds");
    ensured(1<=M && M<=MAXQ, "number of queries out of bounds");
    int i;
    for(i=0; i<M; i++)
    {
        ensured(scanf("%d", Q[i])==1, "cannot read query");
        if(Q[i][0]==1)
        {
            ensured(scanf("%d%d", Q[i]+1, Q[i]+2)==2, "cannot read query 1 args");
            ensured(1<=Q[i][1] && Q[i][1]<=N && 1<=Q[i][2] && Q[i][2]<=N, "invalid vertex");
            ensured(Q[i][1]!=Q[1][2], "self loop");
        }
        else if(Q[i][0]==3)
        {
            ensured(scanf("%d", Q[i]+1)==1, "cannot read query 3 args");
            ensured(1<=Q[i][1] && Q[i][1]<=N, "invalid vertex");
            NANS++;
        }
        else
            ensured(Q[i][0]==2, "unexpected query type");
    }
    for(i=0; i<NANS; i++)
        ensured(scanf("%d", ans+i)==1, "cannot read answer");
    scanf(" ");
    ensured(feof(stdin), "extra input at end of file");
}

int main()
{
    freopen("sample.txt", "r", stdin);
    scanf("%d", &TEST);
    read_input();
    Init(N);
    int CANS=0;
    int accepted=1;
    int i;
    for(i=0; i<M; i++)
    {
        switch(Q[i][0])
        {
        case 1:
            AddEdge(Q[i][1], Q[i][2]);
            break;
        case 2:
            RemoveLastEdge();
            break;
        case 3:
            accepted&=ans[CANS++]==GetSize(Q[i][1]);
            break;
        }
    }
    ensure(accepted, "wrong answer");
    printf("ACCEPTED %d numbers ok\n", NANS);
    return 0;
}
