#include <iostream>
#include <algorithm>

using namespace std;

enum State{
    STATE_UNUSE,
    STATE_USE,
    STATE_DEL
};

struct Bucket{
    Bucket(int key = 0, State state = STATE_UNUSE)
        : _key(key)
        , _state(state){}
    int _key;
    enum State _state;
};

class HashTable {
public:
    HashTable(int size = _primes[0], double loadFactor = 0.75)
        : _useBucketSize(0)
        , _loadFactor(loadFactor)
        , _primeIdx(0) {
            if (size != _primes[0]) {
                for (; _primeIdx < PRIME_SIZE; ++_primeIdx) {
                    if (_primes[_primeIdx] > size) {
                        break;
                    }
                }
                if (_primeIdx == PRIME_SIZE) {
                    _primeIdx--;
                }
            }
        _tableSize = _primes[_primeIdx];
        _table = new Bucket[_tableSize];
    }

    ~HashTable() {
        delete []_table;
        _table = nullptr;
    }

    bool insert(int key) {
        double factor = _useBucketSize * 1.0 / _tableSize;
        cout << "factor: " << factor << endl;
        if (factor > 0._loadFactor) {
            expand();
        }

        int idx = key % _tableSize;
        //有重复的语句而且有条件，可以考虑用do...while优化
        int i = idx;
        do {
            if (_table[idx]._state != STATE_USE) {
                _table[idx]._state = STATE_USE;
                _table[idx]._key = key;
                _useBucketSize++;
                return true;
            }
            i = (i + 1) % _tableSize;
        }while (i != idx);
        /*
        if (_table[idx]._state != STATE_USE) {
            _table[idx]._state = STATE_USE;
            _table[idx]._key = key;
            return true;
        }

        for (int i = (idx + 1) % _tableSize; i != idx; i = (i + 1) % _tableSize) {
            if (_table[idx]._state != STATE_USE) {
                _table[idx]._state = STATE_USE;
                _table[idx]._key = key;
                return true;
            }
        }
        */
        return false;
    }

    bool erase(int key) {
        int idx = key % _tableSize;
        int i = idx;
        do {
            if (_table[idx]._state == STATE_USE && _table[i]._key == key) {
                _table[idx]._state = STATE_DEL;
                _useBucketSize--;
                return true;
            }
            i = (i + 1) % _tableSize;
        }while (_table[i]._state != STATE_UNUSE && i != idx);
        return false;
    }

    bool find(int key) {
        int idx = key % _tableSize;
        int i = idx;
        do {
            if (_table[idx]._state == STATE_USE && _table[i]._key == key) {
                return true;
            }
            i = (i + 1) % _tableSize;
        }while (_table[i]._state != STATE_UNUSE && i != idx);
        return false;
    }

private:
    void expand() {
        _primeIdx++;
        if (_primeIdx == PRIME_SIZE) {
            throw "too long";
        }

        Bucket* newTable = new Bucket[_primes[_primeIdx]];
        for (int i = 0; i < _tableSize; ++i) {
            if (_table[i]._state == STATE_USE) {
                int idx = _table[i]._key % _primes[_primeIdx];
                int k = idx;
                do {
                    if (newTable[k]._state != STATE_USE) {
                        newTable[idx]._state = STATE_USE;
                        newTable[idx]._key = _table[i]._key;
                        break;
                    } 
                    k = (k + 1) / _primes[_primeIdx]; 
                } while (k != idx);
            }
        }
        delete []_table;
        _table = newTable;
        _tableSize = _primes[_primeIdx];
    }

private:
    Bucket* _table;
    int _tableSize;
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
    

}