#include <iostream>

 using namespace std;

double ReLu(double x)
{
 if (x < 0)
  return 0;
 else
  return x;
}

int main()
{
 double x;

 cout << "Enter x: ";
 cin >> x;

 cout << "ReLu(x) = " << ReLu(x) << endl;

 return 0;
}