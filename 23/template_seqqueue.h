
#include <assert.h>
using namespace std;
template <class Type> class SeqQueue {
private:
    int rear, front;  //队尾，队头指针
    Type *elements;  //队列元素数组
    int maxSize;  //最大元素个数
public:
    SeqQueue(int sz = 10 );
    ~SeqQueue(){ delete [ ] elements; }
    bool EnQueue ( const Type &x );  //进队
    bool DeQueue ( Type &x );  //退队
    bool GetFront ( Type &x );  //取队头元素
    void MakeEmpty(){front = rear = 0; }
    bool IsEmpty() const
    { return (front==rear) ? true : false; }
    bool IsFull() const
    { return ((rear+1) % maxSize == front ) ? true : false; }
    int GetSize() const
    { return ( rear-front+maxSize ) % maxSize; }

};
template <class Type> SeqQueue<Type>::SeqQueue(int sz ) : front(0),rear(0),maxSize(sz)
{
    elements = new Type[maxSize];
    assert(elements != NULL );
}

template <class Type> bool SeqQueue <Type>::EnQueue (const Type &x)
{
    if(IsFull() == true )
        return false;
    elements[rear] = x;
    rear = (rear+1) % maxSize;
    return true;
}
template <class Type> bool SeqQueue <Type> ::DeQueue(Type &x )
{
    if(IsEmpty() == true )
        return false;
    x = elements[front];
    front = (front+1) % maxSize;
    return true;
}

template <class Type> bool SeqQueue <Type> ::GetFront(Type &x)
{
    /* if(IsEmpty() == true)
        return false; */
    //cout<<"maxSize="<<maxSize<<" "<<"front="<<front<<endl;
    x = elements[front];
    front++;
    front = front%(maxSize-1);
    return true;
}

