#include <iostream>
using namespace std;

struct QuickSorting {
    int* arr;
    int size;
    QuickSorting(int n){
        size = n;
        arr = new int[n];
    }
    ~QuickSorting(){
        delete[] arr;
    }
    
    int partitionHoare(int arr[], int low, int high) {
        int pivot = arr[low + (high - low) / 2];  
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
        
            do {
                i++;
            } while (arr[i] < pivot);
            
         
            do {
                j--;
            } while (arr[j] > pivot);
            
         
            if (i >= j) return j;
            
        
            swap(arr[i], arr[j]);
        }
    }

    void quickSortHoare(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionHoare(arr, low, high);
            quickSortHoare( low, pivotIndex);     
            quickSortHoare( pivotIndex + 1, high); 
        }
    }
    void shellSort() {
   
    for (int gap = size/2; gap > 0; gap /= 2) {
        
      
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
        
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
    void print(){
        for (int i = 0; i < size; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main(){
    QuickSorting arr(10);
    
    for (int i = 0; i < 10; i++){
        cin >> arr.arr[i];
    }
    arr.quickSortHoare(0, 9);
    arr.print();
    for (int i = 0; i < 10; i++){
        cin >> arr.arr[i];
    }
    arr.shellSort();
    arr.print();
}
