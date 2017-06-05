#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

float multidivide(int numerator, int d1, int d2, int d3, int d4) {
  float f = ((((numerator / d1) / d2) / d3) / d4);
  return f;
}

int main(){

  int a = 10;
  int b = 46;
  int c = 4;
  int d = c - b;              // -42
  int e = b - 3*a + 4*c;      //  32 
  int f = 2*b + 2*c;          //  100
  int g = e - (b/c) + d + 20; // -1 
  int h = (f/c) / a -g;       //  3 
  int m = (d / h) / 7;        // -2 
  int n = g + m;              // -3 
  int p = (f / e) +2*m;        // -1 
  int q = f + 2*d;            // 16
  int r = g + m + p + n + g;      // -8 
  float s = float(a )/ f;            //  0.1 

  cout<< "a: "<< a <<endl;
  cout<< "b: "<<b <<endl;
  cout<< "c: "<<c <<endl;
  cout<< "d: "<<d <<endl;
  cout<<"e: "<< e <<endl;
  cout<<"f: "<< f <<endl;
  cout<< "g: "<<g <<endl;
  cout<< "h: "<<h <<endl;
  cout<<"m: "<< m <<endl;
  cout<<"n: "<< n <<endl;
  cout<<"p: "<< p <<endl;
  cout<<"q: "<< q <<endl;
  cout<<"r: "<< r <<endl;
  cout<<"s: "<<s <<endl;


    cout << "Multidivide #1: " << multidivide(f, g, c, 5, g)
	    << " (expected 5)." << endl;

  assert(multidivide(f,g,c,5,g) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  cout << "Multidivide #2: " << multidivide(840, d, m, p, 1)
	    << " (expected -10)." << endl;

  assert(multidivide(840, d, m, p, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  cout << "Multidivide #3: " << multidivide(320, r, p, a, m)
	    << " (expected -2)." << endl;

  assert(multidivide(320, r, p, a, m) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  cout << "Multidivide #4: " << multidivide((e*f*-1), p, q, r, (a/2))
	    << " (expected -5)." << endl;

  assert(multidivide(e*f*-1, p, q, r, (a/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float zeropointone = multidivide(f*10, a, a, a, a);
  cout << "Multidivide #5: " << zeropointone
	    << " (expected 0.1)." <<  endl;


  list<char> l1;
  for(char c = 'a'; c <= 'z'; c++) {
    l1.push_back(c);
  }
  for(char c =  'Z'; c >= 'A'; c--) {
    l1.push_front(c);
  }

  for (list<char>::iterator p = l1.begin(); p!=l1.end(); p++){
  	cout<<*p<<endl;
  }
  cout<<(l1.back() == 'z')<<endl;
  cout<<(l1.size() == 52)<<endl;

}

