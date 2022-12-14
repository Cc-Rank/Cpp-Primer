#include "StrBlobPtr.hpp"

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string& msg) const {
    auto ret = wptr.lock(); // vector 还存在吗？
    if (!ret)
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret;             // 否则，返回指向 vector 的 shared_ptr
}

string& StrBlobPtr::operator [] (size_t n)
{
    auto p = check(n, "vector out of range.");
    return p->at(n);
}

const string& StrBlobPtr::operator [] (size_t n) const
{
    auto p = check(n, "vector out of range.");
    return p->at(n);
}

StrBlobPtr& 
StrBlobPtr::operator++()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr&
StrBlobPtr::operator--()
{
    --curr;
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr&
StrBlobPtr::operator++(int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr&
StrBlobPtr::operator--(int)
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

StrBlobPtr
StrBlobPtr::operator+(size_t n)
{
    StrBlobPtr ret = *this;
    ret.curr += n;
    return ret;
}

StrBlobPtr
StrBlobPtr::operator-(size_t n)
{
    StrBlobPtr ret = *this;
    ret.curr -= n;
    return ret;
}

string& 
StrBlobPtr::operator*() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

string* 
StrBlobPtr::operator->() const
{
    return &this->operator*();
}

string& StrBlobPtr::deref() const {
    auto p = check(curr, "dereference past end");
    return (*p)[curr];      // (*P) 是对象所指向的 vector
}

// 前缀递增：返回递增后的对象的引用
StrBlobPtr& StrBlobPtr::incr() {
    // 如果 curr 已经指向容器的尾后位置，就不能递增它
    check(curr, "increment past end of StrBlobPtr");
    ++curr;                 // 推进当前位置
    return *this;
}

// 友元函数
bool operator == (const StrBlobPtr& rhs, const StrBlobPtr& lhs)
{
    return rhs.curr == lhs.curr;
}

bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
    return !(lhs == rhs);
}

bool operator < (const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
    return lhs.curr < rhs.curr;
}