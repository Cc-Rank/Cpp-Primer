# StrVec note

这里是一个元素类型为`string`的`vector`的简单逻辑实现;

### 练习 13.39

类中的static成员只是声明，还需要在类外进行定义：
```cpp
class StrVec
{
    static allocator<std::string> alloc;
}
allocator<std::string> StrVec::alloc;
```