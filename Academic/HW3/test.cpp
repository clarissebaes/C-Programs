#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"
using namespace std;

int main(){
	Matrix testmatrix(4,3,2);
	unsigned int rownum = testmatrix.num_rows();
	unsigned int colnum = testmatrix.num_cols();
	cout<<"Row Num: "<< rownum<<endl<<"Col Num: "<< colnum<<endl;
	double val_t;
	double val_f;
	bool x = testmatrix.get(2,2, val_t);
	cout<<"val_t: "<<val_t<<" True or False: "<< x <<endl;
	bool y = testmatrix.get(2,5, val_f);
	cout<<"val_f: "<<val_f<<" True or False: "<< y <<endl;
	double newval = 4;
	testmatrix.set(2,2,newval);
	bool z = testmatrix.get(2,2, val_t);
	cout<<endl;

	cout<<"newval: "<<val_t<<" True or False: "<< z <<endl;

	cout<<endl;
	testmatrix.multiply_by_coefficient(5);
	testmatrix.get(2,2, val_t);
	testmatrix.get(0,0, val_f);
	cout<<"Multiply test: "<<val_t<<" "<<val_f<<endl;

	cout<<endl;
	testmatrix.swap_row(2,0);
	testmatrix.get(2,2, val_t);
	testmatrix.get(0,2, val_f);
	cout<<"Swap test: "<<val_t<<" "<<val_f<<endl;
	bool b =testmatrix.get(0,2, val_f);

	cout<<endl;
	cout<<"clear test1: "<<b<<"row and col num: "<<testmatrix.num_rows()<<"--"<<testmatrix.num_cols()<<endl;
	//testmatrix.clear();
	bool a = testmatrix.get(0,2, val_f);
	cout<<"clear test2: "<<a<<"row and col num: "<<testmatrix.num_rows()<<"--"<<testmatrix.num_cols()<<endl;
	
	cout<<endl;
	double* wanted_row = testmatrix.get_row(0);
	for (unsigned int j = 0; j<testmatrix.num_cols();j++){
		cout<<wanted_row[j]<<" ";

	}
	cout<<endl<<endl;
	cout<<testmatrix<<endl;

	cout<<endl;
	double* wanted_col = testmatrix.get_col(2);
	cout<<"check cols"<<endl;
	for (unsigned int i = 0; i<testmatrix.num_rows();i++){
		cout<<wanted_col[i]<<" ";

	}
	cout<<endl;


	Matrix addmatrix(4,3,74);
	testmatrix.add(addmatrix);
	cout<<testmatrix<<endl;

	Matrix submatrix(4,3,34);
	testmatrix.subtract(submatrix);
	cout<<testmatrix<<endl;

	Matrix m2(3,4,0);
	cout<<"HI"<<endl;

	testmatrix=m2;
	cout<<testmatrix<<endl;
	cout<<"HIWIWI"<<endl;
	bool g = (m2!=testmatrix);
	cout<<g<<endl;
	//int x = 1%2;
	//cout<<x<<endl;
	Matrix m11(3,4,0);
	m11.set(0,0,1);
	m11.set(0,1,2);
	m11.set(0,2,3);
	m11.set(0,3,4);

	m11.set(1,0,5);
	m11.set(1,1,6);
	m11.set(1,2,7);
	m11.set(1,3,8);

	m11.set(2,0,9);
	m11.set(2,1,10);
	m11.set(2,2,11);
	m11.set(2,3,12);
	cout<<m11<<endl;

	m11.transpose();
	cout<<"Transpose test: "<<endl;
	cout<<m11<<endl;


	return 0;
}