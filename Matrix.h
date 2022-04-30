#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>
using namespace std;

enum MatrixType { Identity, Random };

class matrix
{
private:
    int row, col;
    float** data;
    int elements;       //needed for "feed" function
public:
    matrix(int x, int y);
    matrix(int x, int y, float number);
    matrix(int x, int y, MatrixType type);
    void printM();
    float& access(int x, int y);
    matrix operator+(matrix m);
    matrix operator-(matrix m);
    bool operator==(matrix m);
    bool operator!=(matrix m);
    matrix operator*(matrix m);
    matrix operator* (float f);
    matrix operator/ (float f);
    matrix operator/(matrix m);
    matrix transpose();
    int rowValue();
    int colValue();
    bool IsIdentity();
    bool IsSquare();
    bool IsIdempotent();
    void assignData(float** d);
    bool IsSymmetric();
    bool IsUpperTriangle();
    bool IsLowerTriangle();
    void Fill(float f);
    float MaxElement();
    float MinElement();
    string ToString();
    void feed(float f);
    float determinate();
    matrix trim(int x, int y);
    matrix inverse();
};