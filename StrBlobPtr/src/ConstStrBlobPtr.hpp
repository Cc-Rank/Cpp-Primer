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
    ConstStrBlobPtr& incr();     // ǰ׺����

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
    // �����ɹ���check ����һ��ָ�� vector �� shared_ptr
    shared_ptr<vector<string>> check(size_t, const string&) const;

    // ����һ�� weak_ptr����ζ�ŵײ� vector ���ܻᱻ����
    weak_ptr<vector<string>> wptr;
    size_t curr;            // �������еĵ�ǰλ��
};