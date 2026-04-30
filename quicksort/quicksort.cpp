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
        int pivot = arr[low + (high - low) / 2];  // опорный - средний
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
            // Двигаем i вправо, пока элемент меньше опорного
            do {
                i++;
            } while (arr[i] < pivot);
            
            // Двигаем j влево, пока элемент больше опорного
            do {
                j--;
            } while (arr[j] > pivot);
            
            // Если указатели встретились - выход
            if (i >= j) return j;
            
            // Меняем местами "неправильные" элементы
            swap(arr[i], arr[j]);
        }
    }

    void quickSortHoare(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionHoare(arr, low, high);
            quickSortHoare( low, pivotIndex);      // левая часть
            quickSortHoare( pivotIndex + 1, high); // правая часть
        }
    }
    void shellSort() {
    // Начинаем с большого шага, уменьшаем до 1
    for (int gap = size/2; gap > 0; gap /= 2) {
        
        // Делаем сортировку вставками с шагом gap
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            
            // Сравниваем элементы, отстоящие на gap
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