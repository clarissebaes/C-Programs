#include <iostream>
#include <string>
#include "Matrix.h"
using namespace std;

Matrix::Matrix(){//Default constructor
	rows = 0;
	cols = 0;  
	fill = 0.0;
	data = NULL;
}
Matrix::~Matrix(){//destructor calls my clear function
	clear();
}
Matrix::Matrix(unsigned int row_, unsigned int col_, double fill_){//constructor
	rows = row_;
	cols = col_;
	fill = fill_;
	data = new double*[rows];//these for loops create the matrix
	for (unsigned int i = 0; i<rows; i++){
		data[i] = new double[cols];
	}
	for (unsigned int i=0; i<rows; i++){ 
		for(unsigned int j=0; j<cols; j++){
			data[i][j] = fill;
		}
	}
}
Matrix::Matrix(const Matrix& m){//copy constructor
	rows = m.num_rows();
	cols = m.num_cols();
	data = NULL;//prevents memory leaks
	data = new double*[rows];//creates matrix with row and col num of the new matrix
	for (unsigned int i = 0; i < rows; i++){
		data[i] = new double[cols];
	}
	for (unsigned int i = 0; i<rows; i++){
		for (unsigned int j = 0; j< cols; j++){
			double newval;
			m.get(i,j,newval);
			data[i][j] = newval;//assgins the value from new matrix to old matrix
		}
	}
}
unsigned int Matrix::num_rows() const{
	return rows; //returns number of rows
}
unsigned int Matrix::num_cols() const{
	return cols; //returns number of cols
}
const bool Matrix::get(unsigned int grow_, unsigned int gcol_, double &val) const{
	//returns the value of the matrix at a specific row and num
	if ((grow_< rows) && (gcol_<cols)){//checks rows and cols in bounds
		val = data[grow_][gcol_];
		return true;
	}
	else{
		return false;
	}
}
double* Matrix::get_row(unsigned int wantedrow) const{
	double *outrow = new double[cols]; //creates the output pointer
	if (wantedrow<rows){//checks if row is in bounds
		for (unsigned int j = 0; j<cols; j++){
			outrow[j] = data[wantedrow][j];
		}
		return outrow;
	}
	outrow = NULL;//if row is out of bounds return a NULL to prevent memory leak
	return outrow;
}
double* Matrix::get_col(unsigned int wantedcol) const{
	double* outcol = new double[rows];//creates the output pointer
	if (wantedcol<cols){//checks if cols is in bounds
		for (unsigned int i = 0; i<rows; i++){
			outcol[i] = data[i][wantedcol];//adds value to the output
		}
		return outcol;
	}
	outcol = NULL;
	return outcol;
}
void Matrix::clear(){
	for (unsigned int i = 0; i<rows;i++){//runs through the rows
		delete [] data[i];//deletes the col array
	}
	delete [] data;//deletes to prevent memory leaks
	cols = 0;
	rows = 0;
	data = NULL;
}
bool Matrix::set(unsigned int srow_, unsigned int scol_, double newval ){
	if ((srow_<rows) && (scol_<cols)){//checks if the row/col are in bounds
		data[srow_][scol_] = newval;//sets the input value as the new value of the matrix at that row and col
		return true;
	}
	else{//if out of bounds returns false
		return false;
	}
}
void Matrix::multiply_by_coefficient(double mult){
	for (unsigned int i =0; i<rows;i++){//runs through all values in matrix
		for(unsigned int j = 0; j<cols;j++){
			data[i][j] *=mult;//redefines each value to value*mult
		}
	}
}
bool Matrix::swap_row(unsigned int row1, unsigned int row2){
	if((row1<rows)&&(row2<rows)){//makes sure rows are in bounds
		for(unsigned int j = 0; j<cols;j++){//swaps the rows
			double swapval = data[row1][j];
			data[row1][j] = data[row2][j];
			data[row2][j] = swapval;
		}
		return true;
	}
	else{
		return false;
	}
}
void Matrix::transpose(){
	unsigned int rowz = rows;
	rows = cols; //sets cols = rows and rows = cols
	cols =rowz;	
	double** temp_matrix = new double*[rows]; //creates a new matrix  with size colsxRows
	for (unsigned int i = 0; i<rows; i++){
		temp_matrix[i] = new double[cols];
	}
	for (unsigned int i = 0; i<rows; i++){ //transposes the value
		for(unsigned int j = 0; j<cols; j++){
			temp_matrix[i][j] = data[j][i]; 

		}
	}
	for (unsigned int i = 0; i<cols;i++){//deletes the contnets of old matrix
		delete [] data[i];
	}
	delete [] data;
	data = temp_matrix;//assigns new transposed matrix to old matrix
}
bool Matrix::add(const Matrix &B){//adds the vlaues from matrix b to oiginal matrix
	if ( (rows == B.num_rows()) && (cols == B.num_cols()) ){//makes sure the matrixs are the same size
		for (unsigned int i = 0; i<rows; i++){
			for (unsigned int j = 0; j<cols;j++){
				double addval;
				B.get(i,j,addval);//gets the value at B at a specific row and col
				data[i][j] += addval;//adds that value to the value at the same row and col in the original matrix
			}
		}
		return true;
	}
	else{
		return false;
	}
}
bool Matrix::subtract(const Matrix &B){//subtracts the b values from the original matrix
	if ( (rows == B.num_rows()) && (cols == B.num_cols()) ){
		for (unsigned int i = 0; i<rows; i++){
			for (unsigned int j = 0; j<cols;j++){
				double subval;
				B.get(i,j,subval);//gets the value at B at a specific row and col
				data[i][j] -= subval;//subtracts that value to the value at the same row and col in the original matrix
			}
		}
		return true;
	}
	else{
		return false;
	}
}
Matrix* Matrix::quarter(){//out puts a pointer of 4 matrices (quarters of the original matrix)
	Matrix* outmatrix = new Matrix[4];
	unsigned int rowz = rows/2 +rows%2;//makes the boiundaries of the quarters
	unsigned int colz = cols/2 +cols%2;//the row%2 makes this work for both even and odd lengths
	Matrix m1(rowz,colz,0); //Upper left
	for(unsigned int i = 0; i<rowz;i++){
		for (unsigned int j = 0; j<colz;j++){
			m1.set(i,j,data[i][j]);
		}
	}
	Matrix m2(rowz,colz,0);//Upper right
	for(unsigned int i = 0; i<rows;i++){
		for (unsigned int j = colz-cols%2; j<cols;j++){
			m2.set(i,j-colz+cols%2,data[i][j]);
			//since the quarter matrix is smaller than the og matrix when you start
			//at the halfway point (j = colz-cols%2) you have to subtract it from the row/col
			//num when you set the quarter matrix
		}
	}
	Matrix m3(rowz,colz,0);//Lower Left
	for(unsigned int i = rowz-rows%2; i<rows;i++){
		for (unsigned int j = 0; j<colz;j++){
			m3.set(i-rowz+rows%2,j,data[i][j]);
		}
	}
	Matrix m4(rowz,colz,0);//Lower right
	for(unsigned int i = rowz-rows%2; i<rows;i++){
		for (unsigned int j = colz-cols%2;j<cols;j++){
			m4.set(i-rowz+rows%2,j-colz+cols%2,data[i][j]);
		}
	}
	outmatrix[0] = m1;
	outmatrix[1] = m2;
	outmatrix[2] = m3;
	outmatrix[3] = m4;
	return outmatrix;
}
Matrix& Matrix::operator=(const Matrix& m){//assignment opperator
	clear();//prevents memory leaks
	rows = m.num_rows();//remakes the matrix with the size of m matrix
	cols = m.num_cols();
	data = new double*[rows];
	for (unsigned int i = 0; i < rows; i++){
		data[i] = new double[cols];
	}
	for (unsigned int i = 0; i<rows; i++){
		for (unsigned int j = 0; j< cols; j++){
			double newval;
			m.get(i,j,newval); // reassigns the values 
			data[i][j] = newval;
		}
	}
	return *this;
}
bool Matrix::operator==(const Matrix& m){//checks if matrices are equal
	if ((rows == m.num_rows()) &&(cols == m.num_cols()) ){//make sure they ae the same size
		for (unsigned int i = 0; i<rows; i++){
			for (unsigned int j = 0; j<cols; j++){
				double compval;
				m.get(i,j,compval);
				if (data[i][j] != compval){ //compares each value and sees if they are different
					return false; //if any value is different the matrices are not equal
				}
			}
		}
	}
	else{//if they are not the same size they cant be equal
		return false;
	}
	return true;
}
bool Matrix::operator!=(const Matrix& m){//opposite as the == operator
	if ((rows == m.num_rows()) &&(cols == m.num_cols()) ){
		for (unsigned int i = 0; i<rows; i++){
			for (unsigned int j = 0; j<cols; j++){
				double compval;
				m.get(i,j,compval);
				if (data[i][j] != compval){
					return true;
				}
			}
		}
	}
	else{
		return true;
	}
	return false;
}
ostream& operator<<(ostream& out, const Matrix& m){//overloads the <<
	out<<endl<< m.num_rows()<< " x "<< m.num_cols()<<" matrix:";
	out<<endl<<"[ ";
	for (unsigned int i =0; i<m.num_rows();i++){//runs through rows
		for(unsigned int j = 0; j<m.num_cols();j++){//runs through cols
			double outval;
			m.get(i,j,outval);
			out<< outval<<" ";
		}
		if (i!=(m.num_rows()-1)){
			out<<endl<<"  ";//prints new line after it runs through the value sin each row
		}
	}
	out<<"]"<<endl;
	return out;
}
