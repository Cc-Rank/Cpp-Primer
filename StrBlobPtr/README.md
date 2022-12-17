# StrBlobPtr note

这里是一个含有智能指针成员的类；
是一个元素类型为`string`的`vector`的简单逻辑实现;

其中
- `StrBlobPtr`为`StrBlob`的迭代器`iterator`；
- `ConstStrBlobPtr`为`StrBlob`的常量迭代器`const_iterator`；

### 练习 14.28

加法和减法运算符不返回引用；