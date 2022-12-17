#include "ConstStrBlobPtr.hpp"

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string& msg) const {
    auto ret = wptr.lock(); // vector ��������
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;             // ���򣬷���ָ�� vector �� shared_ptr
}

const string& ConstStrBlobPtr::operator [] (size_t n) const
{
    auto p = check(n, "vector out of range.");
    return p->at(n);
}

ConstStrBlobPtr&
ConstStrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

ConstStrBlobPtr&
ConstStrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

ConstStrBlobPtr&
ConstStrBlobPtr::operator++(int)
{
    ConstStrBlobPtr ret = *this;
    ++* this;
    return ret;
}

ConstStrBlobPtr&
ConstStrBlobPtr::operator--(int)
{
    ConstStrBlobPtr ret = *this;
    --* this;
    return ret;
}

ConstStrBlobPtr
ConstStrBlobPtr::operator+(size_t n)
{
    ConstStrBlobPtr ret = *this;
    ret.curr += n;
    return ret;
}

ConstStrBlobPtr
ConstStrBlobPtr::operator-(size_t n)
{
    ConstStrBlobPtr ret = *this;
    ret.curr -= n;
    return ret;
}

const string&
ConstStrBlobPtr::operator*() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

const string*
ConstStrBlobPtr::operator->() const
{
    return &this->operator*();
}

string& ConstStrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*P) �Ƕ�����ָ��� vector
}

// ǰ׺���������ص�����Ķ��������
ConstStrBlobPtr& ConstStrBlobPtr::incr() {
    // ��� curr �Ѿ�ָ��������β��λ�ã��Ͳ��ܵ�����
    check(curr, "increment past end of StrBlobPtr");
    ++curr;                 // �ƽ���ǰλ��
    return *this;
}

// ��Ԫ����
bool operator == (const ConstStrBlobPtr& rhs, const ConstStrBlobPtr& lhs)
{
    return rhs.curr == lhs.curr;
}

bool operator != (const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
    return !(lhs == rhs);
}

bool operator < (const ConstStrBlobPtr& lhs, const ConstStrBlobPtr& rhs)
{
    return lhs.curr < rhs.curr;
}