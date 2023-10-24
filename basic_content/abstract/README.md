# 纯虚函数和抽象类





## 1.纯虚函数与抽象类

C++中的纯虚函数(或抽象函数)是我们没有实现的虚函数！我们只需声明它! 通过声明中赋值0来声明纯虚函数！
```cpp
// 抽象类
Class A {
public: 
    virtual void show() = 0; // 纯虚函数
    /* Other members */
}; 
```

 * 纯虚函数：没有函数体的虚函数
 * 抽象类：包含纯虚函数的类

抽象类只能作为基类来派生新类使用，不能创建抽象类的对象,抽象类的指针和引用->由抽象类派生出来的类的对象！

> 代码样例：[abstract_base.h](./abstract_base.h)、[pure_virtual.cpp](./pure_virtual.cpp)

## 2.实现抽象类

抽象类中：在成员函数内可以调用纯虚函数，在构造函数/析构函数内部不能使用纯虚函数。

如果一个类从抽象类派生而来，它必须实现了基类中的所有纯虚函数，才能成为非抽象类。
```cpp
// A为抽象类
class A {
public:
    virtual void f() = 0;  // 纯虚函数
    void g(){ this->f(); }
    A(){}  // 构造函数
};

class B : public A{
public:
    void f(){ cout<<"B:f()"<<endl;}  // 实现了抽象类的纯虚函数
};
```

> 代码样例：[abstract.cpp](./abstract.cpp)

## 3.重要点

- [纯虚函数使一个类变成抽象类](./interesting_facts1.cpp)
```cpp
// 抽象类至少包含一个纯虚函数
class Base{
public: 
    virtual void show() = 0; // 纯虚函数
    int getX() { return x; } // 普通成员函数

private:
     int x; 
}; 
```

- [抽象类类型的指针和引用](./interesting_facts2.cpp)
```cpp
class Derived : public Base { 
public: 
    void show() { cout << "In Derived \n"; } // 实现抽象类的纯虚函数
    Derived(){} // 构造函数
}; 

int main(void) 
{ 
    //Base b;  // error! 不能创建抽象类的对象
    //Base *b = new Base(); error!
    
    Base *bp = new Derived(); // 抽象类的指针和引用 -> 由抽象类派生出来的类的对象
    bp->show();
    return 0; 
}
```

- [如果我们不在派生类中覆盖纯虚函数，那么派生类也会变成抽象类](./interesting_facts3.cpp)
```cpp
// Derived为抽象类
class Derived: public Base 
{ 
public: 
//    void show() {}
}; 
```

- [抽象类可以有构造函数](./interesting_facts4.cpp)
```cpp
// 抽象类
class Base { 
    protected: 
        int x; 
    public: 
        virtual void fun() = 0; 
        Base(int i) { x = i; }  // 构造函数
}; 
// 派生类
class Derived: public Base 
{ 
    int y; 
public: 
    Derived(int i, int j) : Base(i) { y = j; } // 构造函数
    void fun() { cout << "x = " << x << ", y = " << y; }
}; 
```

- [构造函数不能是虚函数，而析构函数可以是虚析构函数](./interesting_facts5.cpp)
```cpp
// 抽象类
class Base  {
public:
    Base(){ cout << "Constructor: Base" << endl; }
    virtual ~Base(){ cout << "Destructor : Base" << endl; }
    
    virtual void func() = 0;
};

class Derived: public Base {
public:
    Derived(){ cout << "Constructor: Derived" << endl; }
    ~Derived(){ cout << "Destructor : Derived" << endl;}
    
    void func(){cout << "In Derived.func()." << endl;}
};
```
>当基类指针指向派生类对象并删除对象时，我们可能希望调用适当的析构函数。
> 如果析构函数不是虚拟的，则只能调用基类析构函数。

## 4.完整实例

抽象类由派生类继承实现！

> 代码样例：[derived_full.cpp](./derived_full.cpp)

#### 之所以说他抽象，是因为他无法实例化，也就是无法创建对象。纯虚函数没有函数体，不是完整函数，无法调用，也无法分配内存空间。
#### 抽象类通常作为基类，让派生类去实现纯虚函数。派生类必须实现纯虚函数才能被实例化。
#### 在实际开发中，可以定义一个抽象基类，只完成部分功能，未完成的功能交给派生类去实现。这部分未完成的功能，往往是基类不需要的，或者是在基类中无法实现的。
#### 抽象基类除了约束派生类的功能，还可以实现多态。以下第51行代码，指针p的类型是Line，但是它却可以访问派生类中的area()和volume()函数，正是由于在Ling类中将这两个函数定义为纯虚函数；也许这才是c++提供纯虚函数的主要目的

>纯虚函数与抽象类
```c++
using namespace std;
//线
class Line{
public:
    Line(float len);
    virtual float area() = 0;
    virtual float volume() = 0;
protected:
    float m_len;
};
Line::Line(float len): m_len(len){ }
//矩形
class Rec: public Line{
public:
    Rec(float len, float width);
    float area();
protected:
    float m_width;
};
Rec::Rec(float len, float width): Line(len), m_width(width){ }
float Rec::area(){ return m_len * m_width; }
//长方体
class Cuboid: public Rec{
public:
    Cuboid(float len, float width, float height);
    float area();
    float volume();
protected:
    float m_height;
};
Cuboid::Cuboid(float len, float width, float height): Rec(len, width), m_height(height){ }
float Cuboid::area(){ return 2 * ( m_len*m_width + m_len*m_height + m_width*m_height); }
float Cuboid::volume(){ return m_len * m_width * m_height; }
//正方体
class Cube: public Cuboid{
public:
    Cube(float len);
    float area();
    float volume();
};
Cube::Cube(float len): Cuboid(len, len, len){ }
float Cube::area(){ return 6 * m_len * m_len; }
float Cube::volume(){ return m_len * m_len * m_len; }
int main(){
    Line *p = new Cuboid(10, 20, 30);
    cout<<"The area of Cuboid is "<<p->area()<<endl;
    cout<<"The volume of Cuboid is "<<p->volume()<<endl;
  
    p = new Cube(15);
    cout<<"The area of Cube is "<<p->area()<<endl;
    cout<<"The volume of Cube is "<<p->volume()<<endl;
    return 0;
}
```