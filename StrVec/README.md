# StrVec note

### 练习 13.39

类中的static成员只是声明，还需要在类外进行定义：
```cpp
class StrVec
{
    static allocator<std::string> alloc;
}
allocator<std::string> StrVec::alloc;
```