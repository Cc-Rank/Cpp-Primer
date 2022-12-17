#pragma once
#include "StrBlob.hpp"

using std::runtime_error;
using std::weak_ptr;

class ConstStrBlobPtr {
    friend bool operator == (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator != (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator < (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
public:
    ConstStrBlobPtr() : curr(0) {}
    ConstStrBlobPtr(const StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string& deref() const;
    ConstStrBlobPtr& incr();     // 前缀递增

    bool operator!=(const ConstStrBlobPtr& p) { return p.curr != curr; }
    const string& operator[](size_t n) const;
    ConstStrBlobPtr& operator++();
    ConstStrBlobPtr& operator--();
    ConstStrBlobPtr& operator++(int);
    ConstStrBlobPtr& operator--(int);
    ConstStrBlobPtr operator+(size_t n);
    ConstStrBlobPtr operator-(size_t n);
    const string& operator*() const;
    const string* operator->() const;
private:
    // 若检查成功，check 返回一个指向 vector 的 shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;

    // 保存一个 weak_ptr，意味着底层 vector 可能会被销毁
    weak_ptr<vector<string>> wptr;
    size_t curr;            // 在数组中的当前位置
};