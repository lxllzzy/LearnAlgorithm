#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <memory>
#include "stringhash.h"

using namespace std;

/*
大数据处理
查重
1.哈希表 =》效率高但是占内存
2.位图 =》低内存，数据简单，数据的数量和最大值应该相当
3.布隆过滤器 =》位数组+k个哈希
求top-k问题
1.
*/

/*
查重常见面试问题
有两个文件分别是a和b，里面放了很多的ip地址（url地址，email地址），找出两个文件重复的东西，输出
1.如果没有内存限制，可以直接存储一个文件在哈希表，然后遍历另一个文件
2.如果限制内存为100M，怎么设计，1亿的int类型占内存为400M
把一个大文件分成11个小文件，就是%上一个素数，然后每个不同的桶里面不可能一样，这样只用看对应的桶就行
3.布隆过滤器的应用场景
(1)提示过滤一些非法的网站或者钓鱼网站，把所有可能怀疑的网站的url添加到布隆过滤器中
(2)redis缓存中的应用
*/


//===============================================
//===================布隆过滤器===================
//===============================================
class BloomFilter {
public:
    BloomFilter(int bitSize = 1471)
        : _bitSize(bitSize)
    {
        _bitMap.resize(_bitSize / 32 + 1);
    }

public:
    void setBit(const char* str) {
        int idx1 = BKDRHash(str) % _bitSize;
        int idx2 = RSHash(str) % _bitSize;
        int idx3 = APHash(str) % _bitSize;

        int index = 0;
        int offset = 0;
        index = idx1 / 32;
        offset = idx1 % 32;
        _bitMap[index] |= (1 << offset);

        index = idx2 / 32;
        offset = idx2 % 32;
        _bitMap[index] |= (1 << offset);

        index = idx3 / 32;
        offset = idx3 % 32;
        _bitMap[index] |= (1 << offset);
    }

    bool getBit(const char* str) {
        int idx1 = BKDRHash(str) % _bitSize;
        int idx2 = RSHash(str) % _bitSize;
        int idx3 = APHash(str) % _bitSize;

        int index = 0;
        int offset = 0;
        index = idx1 / 32;
        offset = idx1 % 32;
        if (0 == (_bitMap[index] & (1 << offset))) {
            return false;
        }
        
        index = idx2 / 32;
        offset = idx2 % 32;
        if (0 == (_bitMap[index] & (1 << offset))) {
            return false;
        }

        index = idx3 / 32;
        offset = idx3 % 32;
        if (0 == (_bitMap[index] & (1 << offset))) {
            return false;
        }

        return true;
    }

private:
    int _bitSize;
    vector<int> _bitMap;
};

class BlackList {
public:
    void add(string url) {
        _blockList.setBit(url.c_str());
    }

    bool query(string url) {
        return _blockList.getBit(url.c_str());
    }

private:
    BloomFilter _blockList;
};

int main() {
    BlackList list;
    list.add("http://www.baidu.com");
    list.add("http://www.360buy.com");
    list.add("http://www.tmall.com");
    list.add("http://www.tencent.com");

    string url = "http://www.alibaba.com";
    cout << list.query(url) << endl;
}



//===============================================
//=====================位图======================
//===============================================
//key/sizeof(type) == 第几个元素
//key%sizeof(type) == 第几位
//需要根据最大值定义位图数组
//如何获取该位的值bitmap[index] & (1<<offset)
//如何设置该位的值bitmap[index] | (1<<offset)
#if 0
int main() {
    vector<int> vec{12, 78, 90, 123, 8 , 9, 78};
    int max = vec[0];
    for (auto key : vec) {
        if (key > max) {
            max = key;
        }
    }
    int *bitmap = new int[max / 32 + 1]();
    unique_ptr<int> ptr(bitmap);
    for (auto key : vec) {
        int index = key / 32;
        int offset = key % 32;

        if ((bitmap[index] & (1 << offset)) == 0) {
            bitmap[index] = bitmap[index] | (1<<offset);
        }
        else {
            cout << "key: " << key << "第一个重复的数字" << endl;
        }
    }
    return 0;
}

//===============================================
//====================哈希表======================
//===============================================

int main() {
    vector<int> vec;
    srand(time(nullptr));
    for (int i = 0; i < 10000; ++i) {
        vec.push_back(rand()%10000 + 1);
    }
    // unordered_set<int> s1;
    // for (auto &c : vec) {
    //     if (s1.find(c) == s1.end()) {
    //         s1.insert(c);
    //     }
    //     else {
    //         cout << "key: " << c << endl;
    //         break; 
    //     }
    // }

    unordered_map<int, int> m1;
    for (auto &key : vec) {
        // auto it = m1.find(key);
        // if (it == m1.end()) {
        //     m1.emplace(key, 1);
        // }
        // else {
        //     it->second += 1;
        // }
        m1[key]++;
    }

    for (auto &pair : m1) {
        if (pair.second > 1) {
            cout << pair.first << endl;
        }
    }

    return 0;
}
#endif