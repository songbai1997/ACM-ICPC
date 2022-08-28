# 模板
```cpp
void dijkstra(int start, vector<int>& d, vector<vector<pair<int, int>>>& g) {
    // 求解 start 到其他点的最短路径、无负边。距离数组 d 已被初始化为最大值。 g 为邻接表表示的图, 里面的 pair<int, int> 分别表示 to, w
    
    // 构建优先队列，最小堆，此处使用 pair<int, int> 分别存放节点编号以及到此节点的距离，可根据题目进行修改
    auto cmp = [](pair<int, int> a, pair<int, int>b) {
        return a.second > b.second;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp); // 最小堆优先队列
    d[start] = 0; // 初始化到源点的距离为 0
    pq.emplace(start, 0);
    while (!pq.empty()) {
        auto [from, dist] = pq.top();
        pq.pop();
        
        // 到 from 节点的距离被其他节点更新了，效果更好，因此不需要此节点更新，注意，不能是等于，因为等于的情况下是被自己更新的
        if (dist > d[from]) continue; 
        
        // 使用当前的最小距离节点，更新其他节点
        for (auto [to, w] : g[from]) {
            int nd = dist + w;
            if (nd < d[to]) { // 可以更新节点
                d[to] = nd;
                pq.emplace(to, nd); // 节点被更新，因此需要放入优先队列，后续更新其他节点
            }
        }
    }
}
```