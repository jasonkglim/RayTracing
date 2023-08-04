#include <iostream>
using namespace std;

class testClass {
  public:
    testClass() : value{69} {}

 
    int value;
};
int main() {

  testClass myTestClass;
  cout << myTestClass.value << endl;

}
