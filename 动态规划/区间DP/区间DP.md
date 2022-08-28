# 最长回文子序列
递归
```cpp
//递归方法求最长回文子序列 
int LPS(string s,int i,int j)
{
	if(i==j) return 1;//只有一个元素，长度为1 
	if(i>j) return 0;
	if(s[i]==s[j]) 
	  return LPS(s,i+1,j-1)+2;//首尾相同 
	else
	  return max(LPS(s,i,j-1),LPS(s,i+1,j));//首尾不同  
}
```

递推
```cpp
//动态规划求解最长回文子序列 dp[i][j]表示字符串s[i...j]的最长回文子序列 
int LPS(string s,int n)
{
	int dp[N][N];
	memset(dp,0,sizeof(dp));
	for(int i=0;i<=n;i++)
	  dp[i][i]=0;
	for(int len=1;len<n;len++)
	  for(int i=0,j=len;j<n;i++,j++)
	    if(s[i]==s[j])
	      dp[i][j]=dp[i+1][j-1]+2;//首尾字符相等 
	    else
	      dp[i][j]=max(dp[i+1][j],dp[i][j-1]);//首尾字符不相等 
	return dp[0][n-1];
} 
```