#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

//缺点：
//发生哈希冲突时，靠近O(n)的时间复杂度，存储便慢了，能否优化
//多线程环境中，线性探测所用到的基于数组实现的哈希表，只能给全局的表用互斥锁来保证哈希表的原子操作，
// 保证线程安全！可以只用分段的锁，既保证线程安全又有一定的并发量，可以提高效率

//优化
//1.当链表长度大于8（10），把桶里面的链表改为红黑树
//2.多线程环境中，链式哈希表每个桶都可以创建自己的互斥锁，不同桶中的链表操作，可以并发执行起来

class HashTable {
public:
    HashTable(int size = _primes[0], double loadFactor = 0.75)
        : _useBucketSize(0)
        , _loadFactor(loadFactor)
        , _primeIdx(0) {
            if (size != _primes[0]) {
                for (; _primeIdx < PRIME_SIZE; ++_primeIdx) {
                    if (_primes[_primeIdx] >= size) {
                        break;
                    }
                }
                if (_primeIdx == PRIME_SIZE) {
                    _primeIdx--;
                }
            }
        //reserve和resize的区别
        _table.resize(_primes[_primeIdx]);
    }

public:
    void insert(int key) {
        double factor = _useBucketSize * 1.0 / _table.size();
        cout << "factor: " << factor << endl;
        if (factor > _loadFactor) {
            expand();
        }
        int idx = key % _table.size();
        if (_table[idx].empty()) {
            _useBucketSize++;
            _table[idx].emplace_front(key);
        }
        else {
            auto it = ::find(_table[idx].begin(), _table[idx].end(), key);
            if (it == _table[idx].end()) {
                _table[idx].emplace_front(key);
            }
        }
    }

    void erase(int key) {
        int idx = key % _table.size();
        auto it = ::find(_table[idx].begin(), _table[idx].end(), key);
        if (it != _table[idx].end()) {
                _table[idx].erase(it);
                if (_table[idx].empty()) {
                    _useBucketSize--;
                }
        }
    }

    bool find(int key) {
        int idx = key % _table.size();
        auto it = ::find(_table[idx].begin(), _table[idx].end(), key);
        if (it != _table[idx].end()) {
            return true;
        }
        return false;
        //return it != _table[idx].end();
    }

private:
    void expand() {
        if (_primeIdx + 1 == PRIME_SIZE) {
            throw "too long";
        }
        _primeIdx++;

        vector<list<int>> oldTable;
        _table.swap(oldTable);
        _table.resize(_primes[_primeIdx]);

        for (auto list : _table) {
            for (auto &key : list) {
                int idx = key % _table.size();
                if (_table[idx].empty()) {
                    _useBucketSize++;
                }
                _table[idx].emplace_front(key);
            }
        }

    }

private:
    vector<list<int>> _table;
    int _useBucketSize;
    double _loadFactor;

    static const int PRIME_SIZE = 10;
    static int _primes[PRIME_SIZE];
    int _primeIdx;
};
int HashTable::_primes[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main() {
    HashTable h;
    h.insert(2);
    h.insert(4);
    h.insert(34);
    h.insert(66);
    cout << h.find(66) << endl;
    h.erase(66);
    cout << h.find(66) << endl;
    return 0;
}