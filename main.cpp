#include <iostream>
#include <vector>

using namespace std;

//统计的同时进行排序
int merge(vector<int>& arr, int low, int mid, int high) {
    int inversions = 0;

    //创建左右两个子数组
    //注意，这里是创建了两个新的数组，与原有数组无关
    vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

    int i = 0, j = 0, k = low;

    //合并排序两个子数组到原数组，并计算
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
            inversions += (mid - low + 1) - i;//如果此处i>j，则说明后面的i都是大于j的，都加进去
        }
    }

    //将剩余元素复制到原数组中
    while (i < left.size()) {
        arr[k++] = left[i++];
    }
    while (j < right.size()) {
        arr[k++] = right[j++];
    }

    return inversions;
}

//计算数组中逆序对的数量
int countInversions(vector<int>& arr, int low, int high) {
    int inversions = 0;
    if (low < high) {
        int mid = low + (high - low) / 2;

        //分别计算左右两个子数组中的逆序对数量
        inversions += countInversions(arr, low, mid);
        inversions += countInversions(arr, mid + 1, high);

        //计算跨越两个子数组的逆序对数量并排序合并两个子数组
        inversions += merge(arr, low, mid, high);
    }
    return inversions;
}

int main() {
    int n;
    cin >> n; //输入集合中元素个数n

    vector<int> permutation(n);
    for (int i = 0; i < n; ++i) {
        cin >> permutation[i]; //输入集合元素
    }

    //调用函数统计逆序个数
    int inversions = countInversions(permutation, 0, n - 1);

    //输出含有逆序的个数
    cout << inversions << endl;

    return 0;
}
