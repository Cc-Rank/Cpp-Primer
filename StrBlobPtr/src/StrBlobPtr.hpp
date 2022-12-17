#pragma once
#include "StrBlob.hpp"

using std::runtime_error;
using std::weak_ptr;

class StrBlobPtr {
    friend bool operator == (const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator != (const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator < (const StrBlobPtr&, const StrBlobPtr&);
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    StrBlobPtr(const StrBlob& a, size_t sz = 0) : wptr(a.data), curr(sz) {}

    string& deref() const;
    StrBlobPtr& incr();     // 前缀递增

    bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
    string& operator[](size_t n);
    const string& operator[](size_t n) const;
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    StrBlobPtr& operator++(int);
    StrBlobPtr& operator--(int);
    StrBlobPtr operator+(size_t n);
    StrBlobPtr operator-(size_t n);
    string& operator*() const;
    string* operator->() const;
private:
    // 若检查成功，check 返回一个指向 vector 的 shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;

    // 保存一个 weak_ptr，意味着底层 vector 可能会被销毁
    weak_ptr<vector<string>> wptr;
    size_t curr;            // 在数组中的当前位置
};

