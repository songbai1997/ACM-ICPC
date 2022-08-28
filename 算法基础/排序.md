# 前言
算法稳定性：假设在数列中存在 a[i] = a[j], 若在排序之前，a[i] 在 a[j] 前面；并且排序之后，a[i] 仍然在 a[j] 前面，则称这个排序算法是稳定的。

# 1、冒泡排序

时间复杂度：O(n ^ 2)

算法稳定性：稳定

```cpp
// C++ 实现

void bubbleSort(int *a, int n) {
	for (int i = 1; i < n; i++) { // 需要排序 n - 1 轮
		bool keep = false; // 通过当前轮是否有交换出现，确认是否继续
		for (int j = 0; j < n - i; j++) { // 边界的确认，可以通过 i 取特殊值时确认
			if (a[j] > a[j + 1]) swap(a[j], a[j + 1]), keep = true;
		}
		if (!keep) return; 
	}
}
```

# 2、直接插入排序

算法时间复杂度：O(n ^ 2)

算法稳定性：稳定

```cpp
// C++ 实现

void insertSort(int *a, int n) {
	for (int i = 1; i < n; i++) {
		int j = i - 1, t = a[i];
		while (j >= 0 && a[j] > t) a[j + 1] = a[j], j--; // 不能将 -- 操作放到数组下标里，会出错
		a[j + 1] = t; // 防止 t 的位置
	}
}
```

# 3、快速排序
假设被排序的数列中有 n 个数，遍历一次的时间复杂度是 O(n), 需要遍历的次数最少 log (n + 1)，最多 n 次

时间复杂度：最坏 O(n ^ 2), 平均 O(n * log n)

算法稳定性：不稳定

```cpp
// C++ 实现

void quickSort(int *a, int l, int r) {
	if (r - l <= 1) return; // 待排序的数小于等于 1，不用排序，直接返回
	
	int i = l, j = r - 1, t = a[i]; // 以区间里第一个数为基准值
	while (i < j) {
		while (i < j && t <= a[j]) j--; // 从右向左找第一个小于 t 的数
		if (i < j) a[i++] = a[j];
		while (i < j && a[i] <= t) i++; // 从左向右找第一个大于 t 的数
		if (i < j) a[j--] = a[i];
	}
	a[i] = t; // 基准值的最终位置
	quickSort(a, l, i); // 排序左区间
	quickSort(a, i + 1, r); // 排序右区间
}
```


# 4、归并排序

算法时间复杂度：O(n * log n)

算法稳定性：稳定

自顶向下 递归实现
```cpp
// C++ 实现

void merge(int *a, int l, int m, int r) {
	int *tmp = new int[r - l]; // 临时存放数据
	int i = l, j = m, k = 0;
	
	while (i < m && j < r) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	while (i < m) tmp[k++] = a[i++];
	while (j < r) tmp[k++] = a[j++];
	
	for (i = 0; i < k; i++) a[l + i] = tmp[i]; // 将排序后的数组复制到原数组中
	delete tmp;
}

void mergeSort(int *a, int l, int r) {
	if (r - l <= 1) return;
	int m = (l + r) >> 1;
	mergeSort(a, l, m); // 排左区间
	mergeSort(a, m, r); // 排右区间
	merge(a, l, m, r); // 合并有序的左右区间
}

```
自底向上 迭代实现
```cpp
// C++ 实现

void merge(int *a, int l, int m, int r) {
	int *tmp = new int[r - l];
	int i = l, j = m, k = 0;
	
	while (i < m && j < r) {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}
	while (i < m) tmp[k++] = a[i++];
	while (j < r) tmp[k++] = a[j++];
	
	for (i = 0; i < k; i++) a[l + i] = tmp[i];
	delete tmp;
}

void mergeSort(int *a, int n) {
	for (int len = 1; len < n; len *= 2) { // 分组长度，每次扩大一倍
		for (int i = 0; i + len < n; i += len * 2) { // 每个分组中第一个元素的下标，长度为 len 的区间已经有序，通过合并两个长度为 len 的相邻的区间，获取长度为 2 * len 的有序区间
			merge(a, i, i + len, min(n, i + 2 * len));
		}
	}
}
```
# 5、计数排序

```cpp
// C++ 实现

void countSort(int *a, int n) {
	int len = a[0];
	for (int i = 1; i < n; i++) len = max(len, a[i]); // 找最大值
	len++;
	int *cnt = new int[len];
	memset(cnt, 0, len * sizeof(int));
	
	for (int i = 0; i < n; i++) cnt[a[i]]++; // 计数
	
	for (int i = 0, j = 0; i < len; i++) // 排序
		while (--cnt[i] >= 0)
			a[j++] = i;
	delete[] cnt;
}
```

# 6、基数排序

```cpp
// C++ 实现

void countSort(int *a, int n, int e) {
	int output[n], BASE = 10;
	int cnt[BASE] = {0};
	for (int i = 0; i < n; i++) cnt[(a[i] / e) % 10]++;
	for (int i = 1; i < BASE; i++) cnt[i] += cnt[i - 1];
	for (int i = n - 1; i >= 0; i--) { // 注意需要逆序，保证数位相同时排在前面的数的排名更小
		int d = (a[i] / e) % 10; // 当前数位
		output[--cnt[d]] = a[i];
	}
	// 将排序后的数组复制到原数组中
	for (int i = 0; i < n; i++) a[i] = output[i]; 
}

void radixSort(int *a, int n) {
	int _max = a[0];
	for (int i = 1; i < n; i++) _max = max(_max, a[i]);
	for (int e = 1; _max / e > 0; e *= 10)
		countSort(a, n, e);
}
```

# 7、希尔排序
算法时间复杂度：复杂度与增量 (步长 gap) 的取值有关，当 gap = 1 时，希尔排序退化成了直接插入排序，时间复杂度为 O(n ^ 2)，Hibbard 增量的希尔排序的时间复杂度为 O(n ^ 3/2)

算法稳定性：不稳定

```cpp
// C++ 实现
void shellSort(int *a, int n) {
	for (int step = n / 2; step > 0; step /= 2) { // 每 step 个元素一组，进行排序，每次折半
		for (int i = 0; i < step; i++) { // 排序起始元素
			for (int j = step + i; j < n; j += step) { // 进行插入排序
				int t = a[j], k = j - step;
				while (k >= 0 && a[k] > t) a[k + step] = a[k], k -= step;
				a[k + step] = t;
			}
		}
	}
}
```

# 8、选择排序
算法时间复杂度：O(n ^ 2)

算法稳定性：稳定

```cpp
// C++ 实现

void selectSort(int *a, int n) {
	for (int i = 0; i < n; i++) {
		int min_idx = i;
		for (int j = i + 1; j < n; j++) // 在 [i, n) 内找到最小值的下标 
			if (a[j] < a[min_idx])
				min_idx = j;
		swap(a[i], a[min_idx]);
	}
}
```

# 9、堆排序
算法时间复杂度：

算法稳定性：

利用数组实现二叉堆，元素下标从 0 开始，则 i 的左孩子是 2 * i + 1, 右孩子是 2 * i + 2, 父节点是 (i - 1) / 2 （整除）

大顶堆实现升序：先构建大顶堆，然后将最大值与未排序区间的最后一个元素交换位置，调整堆为最大堆，继续交换......

```cpp
// C++ 实现
void maxheapDown(int *a, int l, int r) { // a[l, r)
	int cur = l, val = a[l]; // l 为待下调的元素下标
	for (int child = cur * 2 + 1; child < r; cur = child, child = 2 * child + 1) { // cur 有孩子存在
		if (child + 1 < r && a[child] < a[child + 1]) child++; // 如果存在右孩子，且值更大，则选择右孩子
		if (val >= a[child]) break; // 调整完毕
		a[cur] = a[child];
	}
	a[cur] = val; // 放置 val 的位置是 cur
}

void heapSort(int *a, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) maxheapDown(a, i, n);
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		maxheapDown(a, 0, i);
	}
}
```

