#include<bits/stdc++.h>
using namespace std;
#define pc putchar_unlocked
#define gc getchar_unlocked
typedef long long ll;
typedef unsigned long long llu;
#define mp make_pair
#define pb push_back
#define sc(x) scanf("%d",&x)
#define sc2(x,y) scanf("%d%d",&x,&y)
#define sc3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define scl(x) scanf("%lld",&x)
#define scl2(x,y) scanf("%lld%lld",&x,&y)
#define scl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define scstr(x) scanf("%s",x)
#define pd(x) printf("%d",x)
#define pstr(x) printf("%s",x)
#define newl() printf("\n")
#define fl(i,n) for (i=0;i<n;i++)
#define fle(i,n) for (i=1;i<=n;i++)
#define fla(i,a,n) for (i=a;i<n;i++)
#define mem(a,i) memset(a,i,sizeof(a))
#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > piii ;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
#define gcd __gcd
#define wl(n) while (n--)
#define debug(x) cerr<<"debug->"<<#x<<"::"<<x<<endl
#define debug2(x,y) cerr<<#x<<" :: "<<x<<"\t"<<#y<<" :: "<<y<<"\n"
#define debug3(x,y,z) cerr<<#x<<" :: "<<x<<"\t"<<#y<<" :: "<<y<<"\t"<<#z<<" :: "<<z<<"\n"
#define tr(container, it)  for(typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define all(v) v.begin(),v.end()
#define tatt(cont) typeof(cont.begin())
const double eps=0.000000000000001 ;
#define MOD 1000000007
typedef long double LF;
typedef double lF;
#define hihihaha ((double)CLOCKS_PER_SEC)
#define nl putchar('\n')
//-------------
ll powd(ll a, ll b, ll c)
{
    if (b==0)
        return 1;
    ll ret=powd(a,b/2,c);
    if (b&1)
        return (((a*ret)%c)*ret)%c;
    else
        return (ret*ret)%c;
}// a^b mod c is calculated by this..

class exteuclid
{
public:
    ll g,x,y;
    ll gcd(ll a,ll b)
    {
        if (b==0)
        {
            g=a;
            x=1;
            y=0;
            return g;
        }
        else
        {
            ll g_=gcd(b,a%b);
            ll tem=x;
            x=y;
            y=tem-(ll)(a/b)*y;
            return g_;
        }

    }
    exteuclid()
    {
        g=x=y=0;
    }
};
ll findinv(ll a,ll p) // find multiplicative inverse of a under p. a and p must be coprimes ! its a must !
{
    // a and p should be coprimes !
    assert(__gcd(a,p)==1);
    exteuclid x;
    x.gcd(a,p);
    x.x=(x.x%p+p)%p;
    return x.x;
}

ll expos(ll x,ll y)
{
    //debug3("for ",x,y);
    ll ret=0;
    while(x>0)
    {
        ret+=(x=(x/y));
    }
    //debug(ret);
    return ret;
}
ll ncrmoduloprimepower(ll n,ll k,ll p,ll e)
{
    ll pe=1;
    ll i,j;
    for (i=0;i<e;i++)
        pe*=p;// nomodneede
    ll r=n-k;
    vector<ll>v;
    ll acc=1;
    for (i=0;i<pe;i++)
    {
        ll mul=i;
        if (mul%p==0)
            mul=1;
        acc=(acc*mul)%pe;
        v.pb(acc);
    }
    //debug3(p,pe,acc);
    ll top,bottom,is_negative,digits;
    top=bottom=1;
    is_negative=0;
    digits=0;

    ll nsto=n;
    while (n>0)
    {
        if (acc!=1)
        {
            if (digits>=e)
            {
                is_negative ^= (n & 1);
                is_negative ^= (r & 1);
                is_negative ^= (k & 1);
            }
        }
        top = (top * v[n % pe]) % pe;
        bottom = (bottom * v[r % pe]) % pe;
        bottom = (bottom * v[k % pe]) % pe;

        n/=p;
        r/=p;
        k/=p;

        digits+=1;
    }
    ll res=((top%pe)*(findinv(bottom,pe)%pe))%pe;
    res=(res%pe+pe)%pe;
    //debug(res);
    if (p!=2 || e< 3)
        if (is_negative)
        {
            //cerr<<"\nreversed !\n";
            res=pe-res;
        }

    //debug(res);

    res=(res%pe+pe)%pe;
    return res;

}
ll ncrinter(ll n,ll k,ll p,ll e) // true function
{
    ll pe=1,i;
    for (i=0;i<e;i++)
    {
        pe*=p;
    }
    ll primepart=expos(n,p)-expos(k,p)-expos(n-k,p);
    if (primepart>=e)
        return 0;
    ll ret=ncrmoduloprimepower(n,k,p,e-primepart);
    ret=(ret*powd(p,primepart,pe))%pe;
    return ret;
}
vector<pair<ll,ll> >v;
ll m;
ll chk(ll n,ll r)
{
    int i;
    ll ret=1;
    for (i=0;i<v.size();i++)
    {
        ll yao=expos(n,v[i].fi)-expos(n-r,v[i].fi)-expos(r,v[i].fi);
        ret=(ret*powd(v[i].fi,yao,m));
    }
    return ret;
}
vector<ll >pokemon;
void factorit(ll m)
{
    ll i;
    v.clear(); // important step. one of the most important for saving unnecessary time
    pokemon.clear();
    for(i=2;i*i<=m;i++)
    {
        ll c=0;
        ll mad=1;
        while (m%i==0)
        {
            c++;
            m/=i;
            mad*=i;
        }
        if (c>0)
        {
            v.pb(mp(i,c));
            pokemon.pb(mad);
        }
    }
    if (m>1)
    {
        v.pb(mp(m,1));
        pokemon.pb(m);
    }
    assert(pokemon.size()==v.size());
}

ll crt(ll n,ll r,vector<ll>&pokemon)//uses pokemon..
{
    ll i,j;
    ll ret=0;
    ll prodall=1;
    for (i=0;i<pokemon.size();i++)
    {
        prodall*=pokemon[i];
    }
    assert(pokemon.size()==v.size());
    assert(prodall==m);//global m ;
    for (i=0;i<pokemon.size();i++)
    {
        ll got=ncrinter(n,r,v[i].fi,v[i].se);
        assert(got>=0);
        ///debug2(got,pokemon[i]);
        ll pol=prodall/pokemon[i];
        ret=(ret+(((got*pol)%prodall)*(findinv(pol,pokemon[i])%prodall))%prodall)%prodall;
    }
    return ret;
}
ll ncr(ll n,ll r,ll m)
{
    //cerr<<"\n--------------\n";
    //debug2(n,r);
    //cerr<<"\n--------------\n";

    ll ret=crt(n,r,pokemon);
    //debug(ret);
    ret=(ret%m+m)%m;
    return ret;
}
ll n,alpha;
int main()
{   //ios::sync_with_stdio(0), cin.tie(0);

    scanf("%lld %lld", &n, &m);
    factorit(m);
    for (int r = 0; r <= n; r++) {
        printf("%lld\n", ncr(n, r, m));
    }
    return 0;

}
