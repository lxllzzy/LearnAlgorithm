#include <iostream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <algorithm>

using namespace std;


//=======================================================================
//=======================================================================
//============================基础排序====================================
//=======================================================================
//=======================================================================

// void bubbleSort(int arr[], int size) {
//     for(int i = 0; i < size - 1; ++i) {//减不减一都可以
//         bool flag = false;
//         for (int j = 0; j < size - 1 - i; ++j) {//把最大的沉底，导致不用每次遍历size-1
//             if (arr[j] > arr[j + 1]) {
//                 int temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//                 flag = true;
//             }
//         }

//         if (!flag) {
//             return ;
//         }
//     }
// }

// void choiceSort(int arr[], int size) {

//     for (int i = 0; i < size - 1; ++i) {
//         int min = arr[i];
//         int k = i;
//         for (int j = i + 1; j < size; ++j) {
//             if (arr[j] < min) {
//                 min = arr[j];
//                 k = j;
//             }
//         }

//         if (k != i) {
//             int temp = arr[i];
//             arr[i] = arr[k];
//             arr[k] = temp;
//         }
//     }
    
// }

// void insertSort(int arr[], int size) {
//     for (int i = 1; i < size; ++i) {
//         int val = arr[i];
//         int j = i - 1;
//         for (; j >= 0; --j) {
//             if (val >= arr[j]) {
//                 break;
//             }
//             arr[j + 1] = arr[j];
//         }
//         arr[j + 1] = val;
//     }
// } 

// void shellSort(int arr[], int size) {
//     for (int gap = size/2; gap > 0; gap/=2) {//gap>=0错误
//         for (int i = gap; i < size; ++i) {
//         int val = arr[i];
//         int j = i - gap;
//         for (; j >= 0; j-=gap) {
//             if (val >= arr[j]) {
//                 break;
//             }
//             arr[j + gap] = arr[j];
//         }
//         arr[j + gap] = val;
//     }
//     }
// }

// int main() {
//     int arr[10];
//     srand(time(NULL));
//     for (int i = 0; i < 10; ++i) {
//         arr[i] = rand()%100 + 1;
//     }

//     for (auto &c : arr) {
//         cout << c << " ";
//     }
//     cout << endl;
//     mergeSort(arr, 10);
    
//     for (auto &c : arr) {
//         cout << c << " ";
//     }
//     cout << endl;
//     return 0;

//     // const int count = 100000;
//     // int* arr1 = new int[count];
//     // int* arr2 = new int[count];
//     // int* arr3 = new int[count];
//     // int* arr4 = new int[count];
//     // srand(time(nullptr));
//     // for (int i = 0; i < count; ++i) {
//     //     int val = rand() % count;
//     //     arr1[i] = val;
//     //     arr2[i] = val;
//     //     arr3[i] = val;
//     //     arr4[i] = val;
//     // }
//     // clock_t begin, end;

//     // begin = clock();
//     // bubbleSort(arr1, count);
//     // end = clock();
//     // cout << "arr1 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

//     // begin = clock();
//     // choiceSort(arr2, count);
//     // end = clock();
//     // cout << "arr2 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

//     // begin = clock();
//     // insertSort(arr3, count);
//     // end = clock();
//     // cout << "arr3 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;

//     // begin = clock();
//     // shellSort(arr4, count);
//     // end = clock();
//     // cout << "arr4 time :" <<  (end - begin)*1.0/CLOCKS_PER_SEC << endl;
    
// }


//=======================================================================
//=======================================================================
//============================高级排序====================================
//=======================================================================
//=======================================================================





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


class PriorityQueue {
public:
    using Comp = function<bool(int, int)>;
    PriorityQueue(int cap = 20, Comp comp = greater<int>())
        :_size(0)
        ,_cap(cap)
        ,_comp(comp) {
            _que = new int[_cap];
    }
    
    PriorityQueue(Comp comp)
        :_size(0)
        ,_cap(20)
        ,_comp(comp) {
            _que = new int[_cap];
        }
    
    ~PriorityQueue() {
        delete[]_que;
        _que = nullptr;
    }

    void push(int val) {
        if (_size == _cap) {
            int* p = new int[2*_cap];
            memcpy(p, _que, _cap*sizeof(int));
            delete[]_que;
            _que = p;
            _cap = 2*_cap;
        }

        if (_size == 0) {
            _que[_size] = val;
        }
        else {
            siftUp(_size, val);
        }
        _size++;
    }

    void pop() {
        if (_size == 0) {
            throw "container is empty!";
        }

        _size--;
        if (_size > 0) {
            siftDown(0, _que[_size]);
        }
    }

    bool empty() {return _size == 0;}

    int top() const {
        if (_size == 0) {
            throw "container is empty!";
        }
        return _que[0];
    }

    int size() const {return _size;}

private:
    void siftUp(int i, int val) {
        while (i > 0) {
            int father = (i-1)/2;
            if (_comp(val, _que[father])) {
                _que[i] = _que[father];
                i = father;
            }
            else {
                break;
            }
        }
        _que[i] = val;
    }

    void siftDown(int i, int val) {
        while (i < _size / 2) {
            int child = 2 * i + 1;//这一步没有+1导致卡死
            if (child + 1 < _size && _comp(_que[child + 1], _que[child])) {
                child = child + 1;
            }
            if (_comp(_que[child], val)) {
                _que[i] = _que[child];
                i = child;
            }
            else {
                break;
            }
        }
        _que[i] = val;
    }
private:
    int * _que;
    int _size;
    int _cap;
    Comp _comp;
};

void shiftDown(int arr[], int i, int n) {
    int val = arr[i];
    while (i < n / 2) {
        int child = 2 * i + 1;//这一步没有+1导致卡死
        if (child + 1 < n && (arr[child + 1] > arr[child])) {
            child = child + 1;
        }
        if (arr[child] > val) {
            arr[i] = arr[child];
            i = child;
        }
        else {
            break;
        }
    }
    arr[i] = val;
}

void heapSort(int arr[], int size) {
    int n = size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) {
        shiftDown(arr, i, size);
    }

    for (int i = n; i > 0; --i) {//小细节，把--写成++
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        shiftDown(arr, 0, i);
    }
}

/*
不管快排，或者归并排序，遍历元素的时候都是按照顺序遍历的，对cpu缓存是友好的
（cpu缓存命中率高），但是堆排序，访问元素的时候，是按照父子节点的关系访问的
并不是按照顺序访问的，所以排序过程中，不管是进行元素上浮调整还是下沉对cpu缓
存不友好

堆排序过程中，进行元素下沉调整所作的无效比较过多
因为它本身就小，所以最终下沉到的地方，和末尾位置相差不远，中间做了很多比较，无用功太多
*/

/*
排序算法常见问题：
1.STL中的sort算法用的是什么排序算法？
答：快速排序算法，插入排序（待排序序列的个数<=32）,如果递归层数太深，转成堆排序
2.快速排序的时间复杂度不是稳定的nlogn，最坏情况会变为n^2，怎么解决复杂度恶化问题？
答：三数取中，选择合理的基准值
3.快速排序递归实现时，怎么解决递归层次过深的问题？
可以参考STL中转化为堆排序
4.递归过深会引起什么问题？
函数开销变大，栈内存溢出
5.怎么控制递归过深？如果达到递归深度了还没有排完序怎么办？
转成非递归

内排序
外排序：归并排序
*/

int main() {
    int arr[10];
    PriorityQueue que;
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        // que.push(rand()%100 + 1);
        arr[i] = rand()%100 + 1;
    }
    // while (!que.empty()) {
    //     cout << que.top() << " ";
    //     que.pop();
    // }
    // cout << endl;

    for (auto &c : arr) {
        cout << c << " ";
    }
    cout << endl;
    heapSort(arr, 10);
    
    for (auto &c : arr) {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}