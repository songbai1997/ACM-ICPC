# 算法
https://blog.csdn.net/SongBai1997/article/details/84339394

# C++模板
```cpp
const int N = 100010;
int next[N], ex[N];
 
void getNext(char *s)
{
	int i = 0, j, po, len = strlen(s);
	next[0] = len;
	while(i < len - 1 && s[i] == s[i + 1]) i++;
	next[1] = i;
	po = 1; // 初始化po的位置
	for(i = 2; i < len; i++) {
		if(next[i - po] + i < next[po] + po)
		  next[i] = next[i - po];
		else{
			j = next[po] + po - i;
			if(j < 0) j = 0;
			while(i + j < len && s[i + j] == s[j]) j++;
			next[i] = j;
			po = i;
		}
	} 
}

void eKMP(char *s, char *p)
{
	int i = 0, j, po, slen = strlen(s), plen = strlen(p);
	getNext(p);
	while(s[i] == p[i]) i++;
	ex[0] = i;
	po = 0;
	for(i = 1; i < slen; i++){
		if(next[i - po] + i < ex[po] + po)
		  ex[i] = next[i-po];
		else{
			j = ex[po] + po - i;
			if(j < 0) j = 0;
			while(i + j < len && j < plen; s[i + j] == p[j]) j++;
			ex[i] = j;
			po = i;
		}
	}
}
```