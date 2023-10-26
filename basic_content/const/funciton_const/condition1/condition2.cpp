#include <iostream>
using namespace std;

int main() {
  const int p = 10;
  const int *vp = &p;      //const void 指针是不允许的，因为 void 类型本身是无类型的，它没有大小和值，不能用于指向普通变量。
//  void *vp = &p; // error
  cout<<(*vp)<<endl;
}
