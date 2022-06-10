// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T, int size>
class TPQueue {
 private:
    T* arr;
    int begin, end;
    int count;
    int stepBack(int index) {
        int result = --index;
        if (result < 0)
            result += size + 1;
        return result;
    }
    int stepForward(int index) {
        int result = ++index;
        if (result > size)
            result -= size + 1;
        return result;
    }

 public:
    TPQueue() :
        begin(0), end(0), count(0) {
        arr = new T[size + 1];
    }
    ~TPQueue() {
        delete[] arr;
    }
    void push(const T& item) {
        assert(count < size);
        int cur = end;
        while (begin != cur && item.prior > arr[stepBack(cur)].prior) {
            arr[cur] = arr[stepBack(cur)];
            cur = stepBack(cur);
        }
        arr[cur] = item;
        end = stepForward(end);
        count++;
    }
    T pop() {
        assert(count > 0);
        T item = arr[begin];
        count--;
        begin = stepForward(begin);
        return item;
    }
    T get() const {
        assert(count > 0);
        return arr[begin];
    }
    bool isEmpty() const {
        return count == 0;
    }
    bool isFull() const {
        return count == size;
    }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
