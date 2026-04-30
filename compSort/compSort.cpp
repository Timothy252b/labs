#include <iostream>

using namespace std;
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left,int mid, int right);
void mergeSort(int arr[], int left, int right){
    if (left >= right)
        return;
    int mid = (left + right)/2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    merge(arr,left,mid,right);
}
void merge(int arr[], int left, int mid, int right) {
    int size = right - left + 1;
    int* temp = new int[size];  
    
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (int idx = 0; idx < size; idx++) {
        arr[left + idx] = temp[idx];
    }
    
    delete[] temp;  
}

void countingSort(int arr[], int n) {
    if (n <= 1) return;
    
  
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    
    int* count = new int[max + 1](); 
    
 
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    

    int index = 0;
    for (int i = 0; i <= max; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
    
    delete[] count;
}
void bucketSort(int arr[], int n) {
    if (n <= 1) return;
    
 
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    
  
    const int BUCKET_COUNT = 10;
    int buckets[10][1000];
    int bucketSizes[10] = {0};
    
   
    for (int i = 0; i < n; i++) {
     
        int bucketIndex = (arr[i] - min) * BUCKET_COUNT / (max - min + 1);
        if (bucketIndex >= BUCKET_COUNT) bucketIndex = BUCKET_COUNT - 1;
        
        int pos = bucketSizes[bucketIndex];
        buckets[bucketIndex][pos] = arr[i];
        bucketSizes[bucketIndex]++;
    }
    
 
    for (int b = 0; b < BUCKET_COUNT; b++) {
       
        for (int i = 1; i < bucketSizes[b]; i++) {
            int key = buckets[b][i];
            int j = i - 1;
            while (j >= 0 && buckets[b][j] > key) {
                buckets[b][j + 1] = buckets[b][j];
                j--;
            }
            buckets[b][j + 1] = key;
        }
    }
    
 
    int index = 0;
    for (int b = 0; b < BUCKET_COUNT; b++) {
        for (int i = 0; i < bucketSizes[b]; i++) {
            arr[index++] = buckets[b][i];
        }
    }
}

int main(){
    int arr[20];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    mergeSort(arr, 0, n-1);
    for (int i = 0; i <n; i++){
        cout << arr[i] << " ";
    }
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    countingSort(arr,n);
    for (int i = 0; i <n; i++){
        cout << arr[i] << " ";
    }
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    bucketSort(arr,n);
    for (int i = 0; i <n; i++){
        cout << arr[i] << " ";
    }
}
