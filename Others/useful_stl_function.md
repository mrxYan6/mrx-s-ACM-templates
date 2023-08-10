# 有用的stl函数

## inplace_merge
归并排序等操作的一部分，将两个有序序列合并为一个有序序列，时间复杂度为O(n)

用法:
```cpp
    std::inplace_merge(first, middle, last, comp)
```

