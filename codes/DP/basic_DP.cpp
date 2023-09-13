// 0/1背包問題
for(int i=0;i<n;i++) {
    for(int k = W; k >= w[i]; k--) {
        dp[k] = max(dp[k],dp[k-w[i]]+v[i]);
    }
    //因為不能重複拿，所以要倒回來
}
//無限背包問題
dp[0] = 1;
for(int i=0;i<n;i++) {
    int a;cin>>a;
    for(int k=a;k<=m;k++) {
        dp[k] += dp[k-a];
        if(dp[k]>=mod) dp[k] -= mod;
    }
}
//LIS問題
for(int i=0;i<n;i++) {
    cin>>x;
    auto it = lower_bound(dp.begin(),dp.end(),x);
    if(it == dp.end()) {
        dp.emplace_back(x);
    }
    else {
        *it = x;
    }
}
cout<<dp.size();
//LCS問題
#include<bits/stdc++.h>
using namespace std;
signed main() {
    string a,b;
    cin>>a>>b;
    vector<vector<int>> dp(a.size()+1,vector<int> (b.size()+1,0));
    vector<vector<pair<int,int>>> pre(a.size()+1,vector<pair<int,int>> (b.size()+1));
    for(int i=0;i<a.size();i++) {
        for(int j=0;j<b.size();j++) {
            if(a[i] == b[j]) {
                dp[i+1][j+1] = dp[i][j] + 1;
                pre[i+1][j+1] = {i,j};
            }
            else if(dp[i+1][j] >= dp[i][j+1]) {
                dp[i+1][j+1] = dp[i+1][j];
                pre[i+1][j+1] = {i+1,j};
            }
            else {
                dp[i+1][j+1] = dp[i][j+1];
                pre[i+1][j+1] = {i,j+1};
            }
        }
    }
    int index1 = a.size(), index2 = b.size();
    string ans;
    while(index1>0&&index2>0) {
        if(pre[index1][index2] == make_pair(index1-1,index2-1)) {
            ans+=a[index1-1];
        }
 
        pair<int,int> u = pre[index1][index2];
        index1= u.first;
        index2= u.second;
    }
    for(int i=ans.size()-1;i>=0;i--)cout<<ans[i];
    return 0;
}