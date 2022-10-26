#include <iostream>
#include <cassert>
#include <ctime>
using namespace std;

class BitVector
{

    friend ostream &operator<<(ostream &, const BitVector &);

public:
    BitVector(int = 8);
    BitVector(bool *, int);
    BitVector(const BitVector &);
    ~BitVector();

    BitVector &operator=(const BitVector &);
    BitVector operator|(const BitVector &) const;
    BitVector &operator|=(const BitVector &);
    BitVector operator&(const BitVector &) const;
    BitVector &operator&=(const BitVector &);

    bool &operator[](int);
    const bool operator[](int) const;

    int getLength() const;

private:
    int size;
    bool *ptr;
};

BitVector::BitVector(int s)
{
    size = (s >= 1) ? s : 8;
    ptr = new bool[size];
    assert(ptr);
    for (int i = 0; i < size; ++i)
    {
        ptr[i] = 0;
    }
}

BitVector::BitVector(bool *p, int s)
{
    if (p != NULL)
    {
        if (s >= 1)
        {
            size = s;
            ptr = new bool[size];
            assert(ptr);
            for (int i = 0; i < size; ++i)
            {
                ptr[i] = p[i];
            }
        }
        else
        {
            BitVector b;
            *this = b;
        }
    }
    else
    {
        BitVector b;
        *this = b;
    }
}

BitVector::BitVector(const BitVector &b)
{
    size = b.size;
    ptr = new bool[size];
    assert(ptr);
    for (int i = 0; i < size; ++i)
    {
        ptr[i] = b.ptr[i];
    }
}

BitVector::~BitVector()
{
    delete[] ptr;
}

BitVector &BitVector::operator=(const BitVector &b)
{
    if (this != &b)
    {
        if (size != b.size)
        {
            size = b.size;
            delete[] ptr;
            ptr = new bool[size];
            assert(ptr);
        }
        for (int i = 0; i < size; ++i)
        {
            ptr[i] = b.ptr[i];
        }
    }
    return *this;
}

BitVector BitVector::operator|(const BitVector &b) const
{
    BitVector b1(*this);
    b1 |= b;
    return b1;
}

BitVector &BitVector::operator|=(const BitVector &b)
{
    if (size > b.size)
    {
        BitVector b1(size);
        int k = size - b.size;
        for (int i = k; i < size; ++i)
        {
            b1.ptr[i] = b.ptr[i - k];
        }
        for (int i = 0; i < size; ++i)
        {
            ptr[i] |= b1.ptr[i];
        }
        return *this;
    }
    if (size < b.size)
    {
        BitVector b1(b.size);
        int k = b.size - size;
        for (int i = k; i < b.size; ++i)
        {
            b1.ptr[i] = ptr[i - k];
        }
        *this = b1;
    }
    for (int i = 0; i < size; ++i)
    {
        ptr[i] |= b.ptr[i];
    }
    return *this;
}

BitVector BitVector::operator&(const BitVector &b) const
{
    BitVector b1(*this);
    b1 &= b;
    return b1;
}

BitVector &BitVector::operator&=(const BitVector &b)
{
    if (size > b.size)
    {
        BitVector b1(size);
        int k = size - b.size;
        for (int i = k; i < size; ++i)
        {
            b1.ptr[i] = b.ptr[i - k];
        }
        for (int i = 0; i < size; ++i)
        {
            ptr[i] &= b1.ptr[i];
        }
        return *this;
    }
    if (size < b.size)
    {
        BitVector b1(b.size);
        int k = b.size - size;
        for (int i = k; i < b.size; ++i)
        {
            b1.ptr[i] = ptr[i - k];
        }
        *this = b1;
    }
    for (int i = b.size - size; i < size; ++i)
    {
        ptr[i] &= b.ptr[i];
    }
    return *this;
}

bool &BitVector::operator[](int i)
{
    i = (i >= 0 && i < size) ? i : 0;
    return ptr[i];
}

const bool BitVector::operator[](int i) const
{
    i = (i >= 0 && i < size) ? i : 0;
    return ptr[i];
}

int BitVector::getLength() const
{
    return size;
}

ostream &operator<<(ostream &out, const BitVector &b)
{
    for (int i = 0; i < b.size; ++i)
    {
        out << b.ptr[i];
    }
    out << endl;
    return out;
}

int main()
{
    // Test code
    /*
    bool arr[5] = {1, 0, 1, 1, 0}, arr1[8] = {0, 1, 1, 1, 0, 0, 1, 0};
    BitVector b, b1(16), b2(arr, 5), b3(b2), b4(arr1, 8);
    cout << b;
    cout << b1;
    cout << b2;
    cout << b3;
    cout << b4;
    b1 |= b3;
    cout << b1;
    cout << (b1 & b4);
    cout << (b3 &= b4);
    cout << b3;
    */
}