#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Matrix{
	public:
		//CONSTRUCTOR
		Matrix();//default constructor
		~Matrix();//destructor
		Matrix(unsigned int row_, unsigned int col_, double fill_);//constructor
		Matrix(const Matrix& newmatrix); //copy constructor
	

		//ACCESSORS 
		unsigned int num_rows() const;
		unsigned int num_cols() const;
		const bool get(unsigned int grow_, unsigned int gcol_, double &val) const;
		double* get_row(unsigned int wantedrow) const;
		double* get_col(unsigned int wantedcol ) const;


		//MODIFIERS
		void clear();
		bool set(unsigned int srow_, unsigned int scol_, double newval);
		void multiply_by_coefficient(double mult);
		bool swap_row(unsigned int row1, unsigned int row2);
		void transpose();
		bool add(const Matrix &B);
		bool subtract(const Matrix &B);
		Matrix* quarter(); 

		//OVERLOAD
		Matrix& operator=(const Matrix& m);
		bool operator==(const Matrix& m);
		bool operator!=(const Matrix& m);

	private:
		unsigned int rows;
		unsigned int cols;
		double fill;
		double** data;

    
};
//non-member functions
ostream& operator<< (ostream& out, const Matrix& m);



  