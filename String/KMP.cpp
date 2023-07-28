std::vector<int> next(m + 1);
for(int i = 1, j = 0; i < m; i++) {
    while(j > 0 && t[i] != t[j]) {
        j = next[j];
    }
    if(t[i] == t[j]) {
        j++;
    }
    next[i + 1] = j; 
}