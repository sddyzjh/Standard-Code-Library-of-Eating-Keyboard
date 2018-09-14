for (int i = 1;i <= N;i++){
    for (int v = weight[i];v <= V;v++){
        f[v] = max(f[v],f[v - weight[i]] + Value[i]);
    }
}