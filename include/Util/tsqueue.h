#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <queue>
#include <mutex>

template<class T>
class TSQueue
{
    std::queue<T> qu;
    std::mutex qu_mutex; 
public:

    T& front()
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        return qu.front();
    }

    T& back()
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        return qu.back();
    }

    int size() 
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        return qu.size();
    }

    void push(const T& item)
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        qu.push(item);
    }

    void pop()
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        qu.pop();
    }

    bool empty() 
    {
        std::lock_guard<std::mutex> guard(qu_mutex);
        return qu.empty();
    }
};

#endif