#include <iostream>
#include <cassert>

using namespace std;

template <typename T>

class C_Queue
{

    friend ostream &operator<<(ostream &out, const C_Queue<T> &q)
    {
        if (!q.empty())
        {
            int k;
            k = (q.back < q.front) ? q.size + q.back : q.back;
            for (int i = q.front; i <= k; ++i)
            {
                out << q.ptr[i % q.size] << "\t";
            }
            out << endl;
        }
        else
            out << "queue is empty\n";
        return out;
    }

public:
    C_Queue(int = 20);
    C_Queue(C_Queue &);
    ~C_Queue();

    bool enqueue(T);
    bool dequeue(T &);

    int get_front() const;
    int get_back() const;

    bool empty() const;
    bool full() const;

    T get_top() const;

    C_Queue &operator=(const C_Queue &);

private:
    int size, front, back;
    T *ptr;
};

template <typename T>
C_Queue<T>::C_Queue(int s)
{
    size = (s <= 0) ? 20 : s;
    ptr = new T[size];
    assert(ptr);
    front = -1;
    back = -1;
}

template <typename T>
C_Queue<T>::C_Queue(C_Queue &q)
{
    size = q.size;
    ptr = new T[size];
    assert(ptr);
    int k;
    k = (q.back < q.front) ? q.size + q.back : q.back;
    front = (q.front > -1) ? 0 : -1;
    back = (q.back > -1) ? k - q.front : -1;
    for (int i = 0; i <= back; ++i)
    {
        ptr[i] = q.ptr[(i + q.front) % size];
    }
}

template <typename T>
C_Queue<T>::~C_Queue()
{
    delete[] ptr;
}

template <typename T>
int C_Queue<T>::get_front() const
{
    return front;
}

template <typename T>
int C_Queue<T>::get_back() const
{
    return back;
}

template <typename T>
bool C_Queue<T>::empty() const
{
    return back == -1;
}

template <typename T>
bool C_Queue<T>::full() const
{
    return (back == ((front - 1 + size) % size));
}

template <typename T>
bool C_Queue<T>::enqueue(T e)
{
    if (full())
        return false;
    if (empty())
    {
        front = 0;
        back = 0;
    }
    else
    {
        ++back;
        back %= size;
    }
    ptr[back] = e;
    return true;
}

template <typename T>
bool C_Queue<T>::dequeue(T &m)
{
    if (empty())
        return false;
    m = ptr[front];
    if (front == back)
    {
        front = -1;
        back = -1;
        return true;
    }
    ++front;
    front %= size;
    return true;
}

template <typename T>
T C_Queue<T>::get_top() const
{
    return (empty()) ? NULL : ptr[front];
}

template <typename T>
C_Queue<T> &C_Queue<T>::operator=(const C_Queue<T> &q)
{
    if (this != &q)
    {
        if (size < q.size)
        {
            size = q.size;
            delete[] ptr;
            ptr = new T[size];
            assert(ptr);
        }
        int k;
        k = (q.back < q.front) ? q.size + q.back : q.back;
        front = (q.front > -1) ? 0 : -1;
        back = (q.back > -1) ? k - q.front : -1;
        for (int i = 0; i <= back; ++i)
        {
            ptr[i] = q.ptr[(i + q.front) % size];
        }
    }
    return *this;
}

int main()
{
    // Test code
    /*
    C_Queue<int> q, q1(25), q2(q), q3(q1);

    int x;
    cout << q;
    cout << q1;
    cout << q2;
    cout << q3;

    q.enqueue(5);
    cout << q;
    q.dequeue(x);
    cout << q;
    for (int i = 0; i < 20; ++i)
    {
        q.enqueue(rand() % 10);
    }
    cout << q;
    q.enqueue(7);
    cout << q;
    q.dequeue(x);
    q.dequeue(x);
    q.dequeue(x);
    q.dequeue(x);
    q.enqueue(7);
    cout << q;
    q.enqueue(4);
    q2 = q;
    cout << q2;*/
}