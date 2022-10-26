#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct Couple
{
    T a, b;
};

template <typename T>
ostream &operator<<(ostream &output, Couple<T> c)
{
    output << "[" << c.a << " , " << c.b << "] ";
    return output;
}

template <typename T>
class Stack
{

    friend ostream &operator<<(ostream &output, const Stack<T> &S)
    {
        int i;
        for (i = 0; i <= S.top; ++i)
        {
            output << "[" << S.top_ptr[i].a << " , " << S.top_ptr[i].b << "] ";
        }
        cout << endl;
        return output;
    }

private:
    Couple<T> *top_ptr;
    int volume, top = -1;

public:
    Stack(int = 10);
    Stack(const Stack &);
    ~Stack();

    int push(const Couple<T> &);
    int pop(Couple<T> &);
    int get_top();
    int empty() const;
    int full() const;
    Couple<T> peek() const;

    Stack &operator=(const Stack &);
    int operator==(const Stack &);
    int operator!=(const Stack &);

    void print() const;
};

// Default Constructor
template <typename T>
Stack<T>::Stack(int vol)
{
    volume = (vol <= 0 ? 10 : vol);
    top_ptr = new Couple<T>[volume];
    assert(top_ptr);
}

// Copy Constructor
template <typename T>
Stack<T>::Stack(const Stack &S)
{
    top_ptr = new Couple<T>[S.volume];
    assert(top_ptr);
    volume = S.volume;
    if (!S.empty())
    {
        for (int i = 0; i < S.volume; ++i)
        {
            top_ptr[i] = S.top_ptr[i];
        }
        top = S.top;
    }
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] top_ptr;
}

template <typename T>
int Stack<T>::empty() const
{
    return top == -1;
}

template <typename T>
int Stack<T>::full() const
{
    return top == volume - 1;
}

// Get the index of the top element
template <typename T>
int Stack<T>::get_top()
{
    return top;
}

template <typename T>
int Stack<T>::push(const Couple<T> &S)
{
    if (!full())
    {
        ++top;
        top_ptr[top] = S;
        return 1;
    }
    else
        return 0;
}

template <typename T>
int Stack<T>::pop(Couple<T> &S)
{
    if (!empty())
    {
        S = top_ptr[top];
        --top;
        return 1;
    }
    else
        return 0;
}

template <typename T>
Couple<T> Stack<T>::peek() const
{
    Couple<T> c;
    c.a = 0;
    c.b = 0;
    return (top > -1) ? top_ptr[top] : c;
}

template <typename T>
int Stack<T>::operator==(const Stack &S)
{
    if (top != S.top)
        return 0;
    int i;
    for (i = 0; i <= top && top_ptr[i].a == S.top_ptr[i].a && top_ptr[i].b == S.top_ptr[i].b; ++i)
        ;
    if (i > top)
        return 1;
    else
        return 0;
}

template <typename T>
int Stack<T>::operator!=(const Stack &S)
{
    return !(*this == S);
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack &S)
{
    if (*this != S)
    {
        if (volume != S.volume)
        {
            delete[] top_ptr;
            top_ptr = new Couple<T>[S.volume];
            assert(top_ptr);
        }
        if (!S.empty())
        {
            for (int i = 0; i <= S.top; ++i)
            {
                top_ptr[i] = S.top_ptr[i];
            }
        }
        top = S.top;
    }
    return *this;
}

template <typename T>
void Stack<T>::print() const
{
    if (!empty())
    {
        for (int i = 0; i <= top; ++i)
        {
            cout << top_ptr[i];
        }
        cout << endl;
    }
    else
        cout << "Stack is empty\n";
}

int main()
{
    // Test code
    /*Stack<int> s1(20), s2, s3;

    for (int i = 0; i < 10; ++i)
    {
        Couple<int> c;
        c.a = rand() % 10;
        c.b = rand() % 10;
        s1.push(c);
        cout << s1;
    }
    Stack<char> ch;
    Stack<double> d;

    s1.print();
    s2.print();
    s2 = s1;
    s2.print();
    cout << s1;
    cout << s1.peek() << endl;
    cout << s3.peek();
    cout << ch.peek();
    cout << d.peek() << endl;
    for (int i = 0; i < 10; ++i)
    {
        Couple<int> c;
        s1.pop(c);
        cout << s1;
    }*/
}
