const ll block_siz = 320;
const ll maxn = 100005;
ll a[maxn];
ll cnt[block_siz+1][maxn]; // i-th block, k's cou
deque<ll> q[block_siz+1];

void print_all(ll n)
{
    for(int i=0;i<n;i++)
    {
        cout << q[i/block_siz][i-i/block_siz*block_siz] << ' ';
    }
    cout << endl << endl;
}

int main()
{   Crbubble
    ll n,m,i,k,t;
    ll l,r,ord,pre,id,id2, ans = 0;
    cin >> n;
    for(i=0;i<n;i++) 
    {
        cin >> a[i];
        id = i/block_siz;
        q[id].push_back(a[i]);
        cnt[id][a[i]]++;
    }
    cin >> t;
    while(t--)
    {
        cin >> ord >> l >> r;
        l = (l+ans-1)%n+1 -1;
        r = (r+ans-1)%n+1 -1;
        if(l > r) swap(l,r);
        id = l/block_siz; l %= block_siz;
        id2 = r/block_siz; r %= block_siz;
        if(ord == 1)
        {
            if(id == id2)
            {
                pre = q[id][r];
                for(i=r;i>l;i--)
                {
                    q[id][i] = q[id][i-1];
                }
                q[id][l] = pre;
            }
            else
            {
                pre = q[id].back();
                cnt[id][pre]--;
                q[id].pop_back();
                
                for(i=id+1;i<id2;i++)
                {
                    q[i].push_front(pre);
                    cnt[i][pre]++;
                    pre = q[i].back();
                    cnt[i][pre]--;
                    q[i].pop_back();
                }
                q[id2].push_front(pre);
                cnt[id2][pre]++;
                pre = q[id2][r+1];
                cnt[id2][pre]--;
                q[id2].erase(q[id2].begin()+r+1);
                
                q[id].insert(q[id].begin()+l, pre);
                cnt[id][pre]++;
            }
            //print_all(n);
        }
        else
        {   // query m cnt
            cin >> m;
            m = (m+ans-1)%n+1;
            ans = 0;
            if(id == id2)
            {
                for(i=l;i<=r;i++) ans += (q[id][i] == m);
            }
            else
            {
                for(i=l;i<block_siz;i++) ans += (q[id][i] == m);
                for(i=0;i<=r;i++) ans += (q[id2][i] == m);
                for(i=id+1;i<id2;i++) ans += cnt[i][m];
            }
            cout << ans << endl;
        }
    }
    return 0;
}
