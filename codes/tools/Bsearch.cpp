//Lower bound
int lower_bound(int arr[], int n, int val) {
    int l = 0, r = n-1, mid, ret = -1;//沒搜到return -1
    while (l <= r) {
        mid = (l+r)/2;
        if (arr[mid] >= val) ret = mid, r = mid-1;
        else l = mid+1;
    }
    return ret;
}