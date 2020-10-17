#include <iostream>
#include <stdexcept>
class Test {
public:
Test(char id) : id_(id) {}
~Test() { std::cout << "Destructor execution: "
    << id_ << std::endl; }
private:
char id_; };
int funcB() { Test r('B');
 throw std::runtime_error("Exception from funcB!\n"); std::cout << "Executed in B" << std::endl;
return 0;
}
int funcA() {
Test r('A');
funcB();
std::cout << "Executed in A" << std::endl; return 0;
}
int main() {
  try {
funcA(); }
catch (std::exception& e) {
std::cout << "Exception : " << e.what();
} }
/* (실습 1-1) 분석결과 : main 함수에서 가장 먼저 func A를 호출하여 A에서 'A' test 객체 생성한다.
 funcA에서 funcB를 호출하여 'B' test 객체를 생성한다. B가 끝나면 return 하여 다시 funcA로 돌아간다. funcA 에서는 executed in A가 출력되고 return 하여 다시 main으로 온다. 함수 종료시점마다 Destructor execution이라는 문구가 출력되는데 이로 미루어볼때 각 함수가 종료될때 마다 해당 펑션에서 생성된 객체는 종료와 동시에 destruct 되는 것이다.
 */


/* (실습 1-2) 분석결과 : Exception이 발생하면 cout 코드는 실행되지 않는다. exception from func B 라는 코드가 출력되고 destructor만 호출된다. exception이 발생하면 함수의 뒷부분은 모두 실행하지않고 test r을 파괴한다. funcA또한 스킵하고 해당 객체도 파괴하여 main function의 exception catch 블록으로 이동한다. Stack Unwinding이 발생하여 함수실행을 종료하고 handler가 있는 위치를 찾아 이동한 것이다. */
