#include <iostream>
#include <cassert>
#include <ctime>
using namespace std;

class Transformation
{
public:
    virtual void transform() = 0;
    virtual ~Transformation() {}
};

class RowSwap : public Transformation
{
public:
    RowSwap(double **mat, int row1, int row2, int len)
    {
        for (int i = 0; i < len; ++i)
        {
            double t = mat[row1][i];
            mat[row1][i] = mat[row2][i];
            mat[row2][i] = t;
        }
    }
    RowSwap(double *row1, double *row2, int len)
    {
        for (int i = 0; i < len; ++i)
        {
            double t = row1[i];
            row1[i] = row2[i];
            row2[i] = t;
        }
    }
    void transform() {}
};

class ColSwap : public Transformation
{
public:
    ColSwap(double **mat, int col1, int col2, int len)
    {
        for (int i = 0; i < len; ++i)
        {
            double t = mat[i][col1];
            mat[i][col1] = mat[i][col2];
            mat[i][col2] = t;
        }
    }
    void transform() {}
};

class RowMult : public Transformation
{
public:
    RowMult(double **mat, int row, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            mat[row][i] *= num;
        }
    }
    RowMult(double *row, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            row[i] *= num;
        }
    }
    void transform() {}
};

class ColMult : public Transformation
{
public:
    ColMult(double **mat, int col, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            mat[i][col] *= num;
        }
    }
    void transform() {}
};

class RowAdd : public Transformation
{
public:
    RowAdd(double **mat, int row1, int row2, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            mat[row1][i] *= num;
            mat[row1][i] += mat[row2][i];
        }
    }
    RowAdd(double *row1, double *row2, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            row1[i] *= num;
            row1[i] += row2[i];
        }
    }
    void transform() {}
};

class ColAdd : public Transformation
{
public:
    ColAdd(double **mat, int col1, int col2, int len, double num = 1)
    {
        for (int i = 0; i < len; ++i)
        {
            mat[i][col1] *= num;
            mat[i][col1] += mat[i][col2];
        }
    }
    void transform() {}
};

class Transpose : public Transformation
{
public:
    Transpose(double **&mat, int row, int column)
    {
        double **newMat = new double *[column];
        assert(newMat);
        for (int i = 0; i < column; ++i)
        {
            newMat[i] = new double[row];
            assert(newMat[i]);
            for (int j = 0; j < row; ++j)
            {
                newMat[i][j] = mat[j][i];
            }
        }
        for (int i = 0; i < row; ++i)
        {
            delete[] mat[i];
        }
        delete[] mat;
        mat = new double *[column];
        assert(mat);
        for (int i = 0; i < column; ++i)
        {
            mat[i] = new double[row];
            assert(mat[i]);
            for (int j = 0; j < row; ++j)
            {
                mat[i][j] = newMat[i][j];
            }
        }
        for (int i = 0; i < column; ++i)
        {
            delete[] newMat[i];
        }
        delete[] newMat;
    }
    void transform() {}
};

class Rotate : public Transformation
{
public:
    // & was put after double** so we get the reference to matrices pointer
    Rotate(double **&mat, int row, int column, int mode)
    {
        if (mode == 180)
        {
            int t = row;
            row = column;
            column = t;
        }
        double **newMat = new double *[column];
        assert(newMat);
        for (int i = 0; i < column; ++i)
        {
            newMat[i] = new double[row];
            assert(newMat[i]);
        }
        switch (mode)
        {
        case 90:
            for (int i = 0; i < column; ++i)
            {
                for (int j = 0; j < row; ++j)
                {
                    newMat[i][j] = mat[row - j - 1][i];
                }
            }
            for (int i = 0; i < row; ++i)
            {
                delete[] mat[i];
            }
            delete[] mat;
            mat = new double *[column];
            assert(mat);
            for (int i = 0; i < column; ++i)
            {
                mat[i] = new double[row];
                assert(mat[i]);
                for (int j = 0; j < row; ++j)
                {
                    mat[i][j] = newMat[i][j];
                }
            }
            for (int i = 0; i < column; ++i)
            {
                delete[] newMat[i];
            }
            delete[] newMat;
            break;

        case 180:
            for (int i = 0; i < column; ++i)
            {
                for (int j = 0; j < row; ++j)
                {
                    newMat[i][j] = mat[column - i - 1][row - j - 1];
                }
            }
            for (int i = 0; i < column; ++i)
            {
                delete[] mat[i];
            }
            delete[] mat;
            mat = new double *[column];
            assert(mat);
            for (int i = 0; i < column; ++i)
            {
                mat[i] = new double[row];
                assert(mat[i]);
                for (int j = 0; j < row; ++j)
                {
                    mat[i][j] = newMat[i][j];
                }
            }
            for (int i = 0; i < column; ++i)
            {
                delete[] newMat[i];
            }
            delete[] newMat;
            break;

        case 270:
            for (int i = 0; i < column; ++i)
            {
                for (int j = 0; j < row; ++j)
                {
                    newMat[i][j] = mat[j][column - i - 1];
                }
            }
            for (int i = 0; i < row; ++i)
            {
                delete[] mat[i];
            }
            delete[] mat;
            mat = new double *[column];
            assert(mat);
            for (int i = 0; i < column; ++i)
            {
                mat[i] = new double[row];
                assert(mat[i]);
                for (int j = 0; j < row; ++j)
                {
                    mat[i][j] = newMat[i][j];
                }
            }
            for (int i = 0; i < column; ++i)
            {
                delete[] newMat[i];
            }
            delete[] newMat;
            break;

        default:
            cout << "Invalid rotating angle.\n";
            throw;
        }
    }
    void transform() {}
};

int main()
{

    srand(time(0));

    // Test1 code
    /*double **matrix = new double *[5];
    double **matrix1 = new double *[5];
    double **matrix2 = new double *[5];

    for (int i = 0; i < 5; ++i)
    {
        matrix[i] = new double[3];
        matrix1[i] = new double[3];
        matrix2[i] = new double[3];
        for (int j = 0; j < 3; ++j)
        {
            matrix[i][j] = rand() % 10;
            matrix1[i][j] = matrix[i][j];
            matrix2[i][j] = matrix[i][j];
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    Rotate r(matrix, 5, 3, 90), r1(matrix1, 5, 3, 180), r2(matrix2, 5, 3, 270);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << matrix1[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            cout << matrix2[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;*/

    // Test2 code
    /*double **matr = new double *[10];
    for (int i = 0; i < 10; ++i)
    {
        matr[i] = new double[10];
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            matr[i][j] = rand() % 10;
            cout << matr[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    RowSwap **rsp = new RowSwap *[5];

    for (int i = 0; i < 5; ++i)
    {
        int row1 = rand() % 10;
        int row2 = rand() % 10;
        cout << row1 << ", " << row2 << endl
             << endl;
        rsp[i] = new RowSwap(matr, row1, row2, 10);
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                cout << matr[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < 10; ++i)
    {
        delete[] matr[i];
    }
    delete[] matr;*/

    // Test3 code
    /*double **matr1 = new double *[10];
    for (int i = 0; i < 10; ++i)
    {
        matr1[i] = new double[10];
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            matr1[i][j] = rand() % 10;
            cout << matr1[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;

    Transformation **tran = new Transformation *[5];

    for (int k = 0; k < 5; ++k)
    {
        cout << "Enter transformation type.\nPress 1 for RowSwap\nPress 2 for ColumnSwap\nPress 3 for RowAdd\nPress 4 for ColumnAdd\n";
        cout << "Press 5 for RowMultiplication\nPress 6 for ColumnMultiplication\nPress 7 for Transponation\nPress 8 for Rotation\n";
        int type;
        cin >> type;
        int row1, row2, col1, col2;
        switch (type)
        {
        case 1:
            cout << "Enter the indexes for rows\n";
            cin >> row1 >> row2;
            tran[k] = new RowSwap(matr1, row1, row2, 10);
            break;
        case 2:
            cout << "Enter the indexes for columns\n";
            cin >> col1 >> col2;
            tran[k] = new ColSwap(matr1, col1, col2, 10);
            break;
        case 3:
            cout << "Enter the indexes for rows\n";
            cin >> row1 >> row2;
            tran[k] = new RowAdd(matr1, row1, row2, 10);
            break;
        case 4:
            cout << "Enter the indexes for columns\n";
            cin >> col1 >> col2;
            tran[k] = new ColAdd(matr1, col1, col2, 10);
            break;
        case 5:
            cout << "Enter the index for row\n";
            int row;
            cin >> row;
            tran[k] = new RowMult(matr1, row, 10, 2);
            break;
        case 6:
            cout << "Enter the index for column\n";
            int col;
            cin >> col;
            tran[k] = new ColMult(matr1, col, 10, 2);
            break;
        case 7:
            tran[k] = new Transpose(matr1, 10, 10);
            break;
        case 8:
            cout << "Enter the rotation angle (90, 180, 270)";
            int angle;
            cin >> angle;
            tran[k] = new Rotate(matr1, 10, 10, angle);
            break;
        default:
            cout << "Invalid input";
            throw;
        }
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                cout << matr1[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }

    for (int i = 0; i < 5; ++i)
    {
        delete tran[i];
    }
    delete[] tran;

    for (int i = 0; i < 10; ++i)
    {
        delete[] matr1[i];
    }
    delete[] matr1;*/
}