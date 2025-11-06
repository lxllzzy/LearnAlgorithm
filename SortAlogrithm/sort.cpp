#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void bubbleSort(int arr[], int size) {
    for(int i = 0; i < size - 1; ++i) {//减不减一都可以
        bool flag = false;
        for (int j = 0; j < size - 1 - i; ++j) {//把最大的沉底，导致不用每次遍历size-1
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = true;
            }
        }

        if (!flag) {
            return ;
        }
    }
}


void choiceSort(int arr[], int size) {

    for (int i = 0; i < size - 1; ++i) {
        int min = arr[i];
        int k = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < min) {
                min = arr[j];
                k = j;
            }
        }

        if (k != i) {
            int temp = arr[i];
            arr[i] = arr[k];
            arr[k] = temp;
        }
    }
    
}

void insertSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int val = arr[i];
        int j = i - 1;
        for (; j >= 0; --j) {
            if (val >= arr[j]) {
                break;
            }
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = val;
    }
} 

void shellSort(int arr[], int size) {
    for (int gap = size/2; gap > 0; gap/=2) {//gap>=0错误
        for (int i = gap; i < size; ++i) {
        int val = arr[i];
        int j = i - gap;
        for (; j >= 0; j-=gap) {
            if (val >= arr[j]) {
                break;
            }
            arr[j + gap] = arr[j];
        }
        arr[j + gap] = val;
    }
    }
}

int paritation(int arr[], int begin, int end) {
    int val = arr[begin];
    while (begin < end) {
        while (begin < end && arr[end] > val) {
            end--;
        }
        if (begin < end) {
            arr[begin] = arr[end];
            begin++;
        }
        while (begin < end && arr[begin] < val) {
            begin++;
        }
        if (begin < end) {
            arr[end] = arr[begin];
            end--;
        }
    }
    arr[begin] = val;
    return begin;
}

void quickSort(int arr[], int begin, int end) {
    
    if (begin >= end) {
        return ;
    }

    /*
    //优化一
    if ((end - begin) < 100) {
        insertSort(arr, begin, end);
        return ;
    }

    优化二
    基准选择，三数取中
    */
    int pos = paritation(arr, begin, end);
    quickSort(arr, begin, pos - 1);
    quickSort(arr, pos + 1, end);//这两步都不能写成pos
}

void quickSort(int arr[], int size) {
    return quickSort(arr, 0, size - 1);
}

void Merge(int arr[], int begin, int mid, int end) {
    int *p = new int[end - begin + 1];
    int idx = 0;
    int i = begin;
    int j = mid + 1;
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            p[idx++] = arr[i++];
        }
        else {
            p[idx++] = arr[j++];
        }
    }
    while (i <= mid) {
        p[idx++] = arr[i++];
    }
    while (j <= end) {
        p[idx++] = arr[j++];
    }
    for(int i = begin, j = 0; i <= end; ++i,++j) {
        arr[i] = p[j];
    }
    delete[]p;
}

void mergeSort(int arr[], int begin, int end) {
    if (begin >= end) {
        return ;
    }
    int mid = (begin + end) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    Merge(arr, begin, mid, end);

}

void mergeSort(int arr[], int size) {
    return mergeSort(arr, 0, size - 1);
}

int main() {
    int arr[10];
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand()%100 + 1;
    }

    for (auto &c : arr) {
        cout << c << " ";
    }
    cout << endl;
    mergeSort(arr, 10);
    
    for (auto &c : arr) {
        cout << c << " ";
    }
    cout << endl;
    return 0;

    // const int count = 100000;
    // int* arr1 = new int[count];
    // int* arr2 = new int[count];
    // int* arr3 = new int[count];
    // int* arr4 = new int[count];
    // srand(time(nullptr));
    // for (int i = 0; i < count; ++i) {
    //     int val = rand() % count;
    //     arr1[i] = val;
    //     arr2[i] = val;
    //     arr3[i] = val;
    //     arr4[i] = val;
    // }
    // clock_t begin, end;

    // begin = clock();
    // bubbleSort(arr1, count);
    // end = clock();
    // cout << "arr1 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

    // begin = clock();
    // choiceSort(arr2, count);
    // end = clock();
    // cout << "arr2 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

    // begin = clock();
    // insertSort(arr3, count);
    // end = clock();
    // cout << "arr3 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

    // begin = clock();
    // shellSort(arr4, count);
    // end = clock();
    // cout << "arr4 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;
    
}