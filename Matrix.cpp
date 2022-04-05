#include <iostream>
#include "Matrix.hpp"
using namespace zich;
using namespace std;


Matrix::Matrix(vector<double> arr, int rowSize, int columnSize){
    if(arr.size()!=rowSize*columnSize){
        throw invalid_argument( "\nthe vector size is not equal to row size*column size" );
    }
    for (int i = 0; i < rowSize; ++i) {
        mat.push_back(vector<double>());
        for (int j = 0; j < columnSize; ++j) {
            int index=i*columnSize+j;
            mat.at(static_cast<unsigned long>(i)).push_back(arr.at(static_cast<unsigned long>(index)));
        }
    }
}

Matrix Matrix::operator+(const Matrix &other) const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    vector<double>vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j)+other.mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix Matrix::operator+() {
    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix& Matrix::operator+=(const Matrix &other) {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)+=other.mat.at(i).at(j);
            }
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &other) const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    vector<double>vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            vector.push_back(this->mat.at(i).at(j)-other.mat.at(i).at(j));
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix Matrix::operator-() {
    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                vector.push_back(-1*this->mat.at(i).at(j));
            }
            else{
                vector.push_back(this->mat.at(i).at(j));
            }
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(this->mat.at(0).size())};
}

Matrix& Matrix::operator-=(const Matrix &other) {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)-=other.mat.at(i).at(j);
            }
        }
    }
    return *this;
}

string Matrix::toString()const {
    string str;
    if(this->mat.empty()||this->mat.at(0).empty()){
        throw invalid_argument( "\nthe matrix is empty" );
    }
    // convert the matrix to string
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        str+='[';
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            double x=this->mat.at(i).at(j);
            str+= std::to_string(x);
            str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
            str[str.length()-1]=' ';
        }
        str.erase ( str.length()-1);
        str+="]\n";
    }
    return str;
}

std::ostream &zich::operator<<(ostream &output, const Matrix &matrix) {

    return output<<matrix.toString();
}

std::istream &zich::operator>>(istream &input, Matrix &matrix) {
    string str;
    double num=0;
    input.fill('f');
    int rowSize=matrix.mat.size();
    int columnSize=matrix.mat.at(0).size ();
    unsigned long row=0;
    unsigned long column=0;
    input.get();
    for(char c=0; input.get(c)&&c!='\n';){
        if (c=='['){
            column=0;
            row++;
            if (row>=rowSize){
                throw invalid_argument( "\nthe input have more rows than the matrix" );
            }
        }
        else if((c==' '|| c==']')&&str.length()!=0){
            if (column>=columnSize){
                throw invalid_argument( "\nthe input have more columns than the matrix" );
            }
            num= stod(str);
            matrix.mat.at(row).at(column)=num;
            cout<<row<<","<<column<<","<<num <<endl;
            column++;
            str="";
        }
        else if (isdigit(c)!=0){

            str+=c;
        }
    }


//    char a=' ';
//    string string;
//    char* c=&a;
//    input.read(c,1);
//    if(*c!='['){
//        throw invalid_argument( "\nthe first char is not '['" );
//    }
//    while (input.get(*c)) {
//        while (input.peek()!=' '||input.peek()!=']'){
////            input.read(c,1);
//            input.get(*c);
//            if((*c>'9'||*c<'0')&&(*c!=' '||*c!=']')){
//                throw invalid_argument( "\nwrong template" );
//            }
//        }
//    }
    return input;
}

Matrix zich::operator*(double scalar, const Matrix &matrix) {
    vector<double>vector;
    for (unsigned long i = 0; i < matrix.mat.size(); ++i) {
        for (unsigned long j = 0; j < matrix.mat.at(0).size(); ++j) {
            if(matrix.mat.at(i).at(j)!=0){
                vector.push_back(scalar*matrix.mat.at(i).at(j));
            }
            else{
                vector.push_back(matrix.mat.at(i).at(j));
            }
        }
    }
    return Matrix{vector, static_cast<int>(matrix.mat.size()), static_cast<int>(matrix.mat.at(0).size())};
}

Matrix Matrix::operator*(double scalar) const {
    return scalar*(*this);
}

Matrix& Matrix::operator*=(double scalar){
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=0){
                this->mat.at(i).at(j)*=scalar;
            }
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    if(this->mat.at(0).size()!=other.mat.size()){
        throw invalid_argument( "\nmultiple metrics is valid only if the column size of the first equal to the row size of the second" );
    }

    vector<double> vector;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < other.mat.at(0).size(); ++j) {
            double sum=0;
            for (unsigned long k = 0; k < other.mat.size(); ++k) {
                sum+= this->mat.at(i).at(k)*other.mat.at(k).at(j);
            }
            vector.push_back(sum);
        }
    }
    return Matrix{vector, static_cast<int>(this->mat.size()), static_cast<int>(other.mat.at(0).size())};
}

bool Matrix::operator==(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            if(this->mat.at(i).at(j)!=other.mat.at(i).at(j)){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return !(*this==other);
}

bool Matrix::operator>(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    double sumA=0;
    double sumB=0;
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            sumA+=this->mat.at(i).at(j);
            sumB+=other.mat.at(i).at(j);
        }
    }
    return sumA>sumB;
}

bool Matrix::operator>=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return *this==other||*this>other;
}

bool Matrix::operator<(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return other>*this;
}

bool Matrix::operator<=(const Matrix &other)const {
    if(this->mat.size()!=other.mat.size()||this->mat.at(0).size()!=other.mat.at(0).size()){
        throw invalid_argument( "\nThe matrices are not the same size" );
    }
    return other>=*this;
}

Matrix& Matrix::operator++() {
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            this->mat.at(i).at(j)++;
        }
    }
    return *this;
}

Matrix Matrix::operator++(int dummy_flag_for_postfix_increment) {
    Matrix copy = *this;
    ++(*this);
    return copy;
}

Matrix& Matrix::operator--() {
    for (unsigned long i = 0; i < this->mat.size(); ++i) {
        for (unsigned long j = 0; j < this->mat.at(0).size(); ++j) {
            this->mat.at(i).at(j)--;
        }
    }
    return *this;
}

Matrix Matrix::operator--(int dummy_flag_for_postfix_increment) {
    Matrix copy = *this;
    --(*this);
    return copy;
}



