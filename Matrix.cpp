#include "Matrix.h"

static void insrt(char* insider, char* home)
{
    int str1size = 0, str2size = 0, counter = 0;    // size of insider , size of home , for counting
    while (insider[str1size]) str1size++;
    while (home[str2size]) str2size++;
    int index = str2size;
    while (counter <= str2size)     // giving the appropriate space for "insider"
    {
        home[index + str1size] = home[index];
        index--;
        counter++;
    }
    counter = 0;
    while (counter < str1size)      // copying "insider"'s characters to the space inside "home"
    {
        home[counter] = insider[counter];
        counter++;
    }
    delete insider;         // we don't need this address anymore
}

static char* MakeItString(int num)
{
    int numcopy = num;
    bool negative = false;
    char* numstr = NULL;
    int index = 1, numsize = 0;
    do {                           // to determine number of digits in the sent number
        numsize++;
        index *= 10;
    } while (num / index);
    if (num < 0) {
        num *= -1;         // if the number was negative , make it positive
        numstr = new char[numsize + 2];
        numstr[0] = '-';
        numstr++;
        negative = true;
    }
    else if (num == 0)                     // special case for receiving the number zero
    {
        numstr = (char*)"0";
        return numstr;
    }
    else
    {
        numstr = new char[numsize + 1];      // asking the operating system to reserve exact space for characters that represent "num"
    }
        index = numsize - 1;
    do                          // filling the string with the number's characters
    {
        numstr[index] = (num % 10 + 48);
        num /= 10;
        index--;
    } while (num);
    numstr[numsize] = '\0';
    if (negative) --numstr;
    return numstr;
}


matrix::matrix(int x, int y)
{
    elements = 0;
    row = x;
    col = y;
    data = new float* [row];
    for (int i = 0; i < row; i++)
        data[i] = new float[col];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            data[i][j] = 0;
    }
}

matrix::matrix(int x, int y, float number)
{
    row = x;
    col = y;
    data = new float* [row];
    for (int i = 0; i < row; i++)
    {
        data[i] = new float[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            data[i][j] = number;
        }
    }
}

matrix::matrix(int x, int y, MatrixType type) : matrix::matrix(x, y)
{
    switch (type)
    {
    case Identity:

        for (int i = 0; i < x; i++)
            data[i][i] = 1;
        break;
    case Random:
        srand(time(NULL));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                data[i][j] = rand();
            }
        }
        break;
    }
}

void matrix::printM()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << data[i][j] << "\t\t";
        }
        cout << endl;
    }
}

float& matrix::access(int x, int y)
{
    return data[x - 1][y - 1];
}

matrix matrix::operator+(matrix m)
{
    if (row == m.row && col == m.col)
    {
        matrix m1(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                m1.data[i][j] = data[i][j] + m.data[i][j];
        return m1;
    }
    else
    {
        cout << "matrices sizes are not identical !";
        exit(0);
    }
}

matrix matrix::operator-(matrix m)
{
    if (row == m.row && col == m.col)
    {
        matrix m1(row, col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                m1.data[i][j] = data[i][j] - m.data[i][j];
        return m1;
    }
    else
    {
        cout << "matrices sizes are not identical !";
        exit(0);
    }
}

bool matrix::operator==(matrix m)
{
    bool equality = true;
    if (row == m.row && col == m.col)
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
                if (data[i][j] != m.data[i][j])
                {
                    equality = false;
                    break;
                }
            if (!equality) break;
        }
        return equality;
    }
    else
        return false;
}

bool matrix::operator!=(matrix m) { return !(*this == m); }

matrix matrix::operator*(matrix m)
{
    if (col == m.row)
    {
        matrix mm(row, m.col);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < m.col; j++)
                for (int k = 0; k < col; k++)
                {
                    mm.data[i][j] += data[i][k] * m.data[k][j];
                }
        return mm;
    }
    else
    {
        cout << "#columns of the 1st matrix is not equal to #columns of the 2nd matrix!";
        exit(0);
    }
}

matrix matrix::transpose()
{
    matrix ret(col, row);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            ret.data[j][i] = data[i][j];
    return ret;
}

int matrix::rowValue() { return row; }

int matrix::colValue() { return col; }

bool matrix::IsIdentity()
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            if (i == j)
            {
                if (data[i][j] != 1.0)
                    return false;
                continue;
            }
            if (data[i][j] != 0.0) return false;
        }
    return true;
}

bool matrix::IsSquare()
{
    if (row == col) return true;
    return false;
}

bool matrix::IsIdempotent()
{
    if (!(this->IsSquare())) return false;
    matrix m = *this * *this;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (m.data[i][j] != data[i][j]) return false;
    return true;
}

void matrix::assignData(float** d)
{
    data = d;
}

bool matrix::IsSymmetric()
{
    if (!(this->IsSquare())) return false;
    matrix m = this->transpose();
    if (m == *this) return true;
    return false;
}

bool matrix::IsUpperTriangle()
{
    if (!(this->IsSquare())) return false;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < i; j++)
            if (data[i][j] != 0.0)
                return false;
    return true;
}

bool matrix::IsLowerTriangle()
{
    if (!(this->IsSquare())) return false;
    for (int i = 0; i < row; i++)
        for (int j = i + 1; j < col; j++)
            if (data[i][j] != 0.0)
                return false;
    return true;
}

void matrix::Fill(float f)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            data[i][j] = f;
}

matrix matrix::operator* (float f)
{
    matrix ret(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            ret.data[i][j] = data[i][j] * f;
    return ret;
}

matrix matrix::operator/ (float f)
{
    matrix ret(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            ret.data[i][j] = data[i][j] / f;
    return ret;
}

float matrix::MaxElement()
{
    float Max = data[0][0];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (Max < data[i][j]) Max = data[i][j];
    return Max;
}

float matrix::MinElement()
{
    float Min = data[0][0];
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            if (Min > data[i][j]) Min = data[i][j];
    return Min;
}

string matrix::ToString()
{
    string s;
    int digs;
    float num;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (data[i][j] == 0.0)
            {
                s += "0.0\t";
                continue;
            }
            if (!(int(data[i][j])))
            {
                float f = data[i][j] - int(data[i][j]);
                if (f < 0.0)
                {
                    f *= -1;
                    s += '-';
                }
                s += "0.";
                int i;
                for (i = 0; (!(int(f * 10.0f))) && i < 6; i++)
                {
                    s += '0';
                    f *= 10.f;
                }
                for (digs = 0; digs < 6 - i && (f - int(f) != 0.0); digs++)
                    f *= 10;
                char* temp = MakeItString(f);
                for (int k = 0; k < digs; k++)
                    s += temp[k];
                s += '\t';
                delete temp;
                continue;
            }
            if (data[i][j] == int(data[i][j]))
            {
                char* temp = MakeItString(data[i][j]);
                for (int k = 0; temp[k]; k++)
                    s += temp[k];
                s += '\t';
                delete temp;
                continue;
            }
            char* temp = MakeItString(data[i][j]);
            for (int k = 0; temp[k]; k++)
                s += temp[k];
            s += '.';
            delete temp;
            float f = data[i][j] - int(data[i][j]);
            if (f < 0) f *= -1;
            int i;
            for (i = 0; (!(int(f * 10.0f))) && i < 6; i++)
            {
                s += '0';
                f *= 10.f;
            }
            for (digs = 0; digs < 6 - i && (f - int(f) != 0.0); digs++)
                f *= 10;
            temp = MakeItString(f);
            for (int k = 0; k < digs; k++)
                s += temp[k];
            s += '\t';
            delete temp;
        }
        s += '\n';
    }
    return s;
}

void matrix::feed(float f)
{
    data[elements / col][elements % row] = f;
    ++elements;
}

float matrix::determinate()
{
    if (!(this->IsSquare()))
    {
        cout << "error the matrix is not square";
        exit(0);
    }
    if (col == 2) return (data[0][0] * data[1][1] - data[1][0] * data[0][1]);
    float result = 0;
    for (int i = 0; i < col; i++)
    {
        matrix m1(col - 1, col - 1);
        for (int j = 1; j < row; j++)
            for (int k = 0; k < col; k++)
            {
                if (k == i) continue;
                m1.feed(data[j][k]);
            }
        switch (i % 2)
        {
        case 0:
            result += data[0][i] * m1.determinate();
            break;
        case 1:
            result -= data[0][i] * m1.determinate();
            break;
        }
    }
    return result;
}

matrix matrix::trim(int x, int y)
{
    short int i, j;
    matrix m(row - 1, col - 1);
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
        {
            if (i == x || j == y) continue;
            m.feed(data[i][j]);
        }
    return m;
}

matrix matrix::inverse()
{
    float d = this->determinate();
    int sig = 1;
    matrix m(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            m.data[i][j] = this->trim(i, j).determinate() * sig;
            sig *= -1;
        }
    return m.transpose() / d;
}

matrix matrix::operator/(matrix m)
{
    if (m.col != col)
    {
        cout << "division can't be done !";
        exit(0);
    }
    return *this * m.inverse();
}