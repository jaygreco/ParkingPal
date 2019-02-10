// Ultra-simple circular array class designed to auto-overwrite stale values.

#ifndef FIFO_H
#define FIFO_H

class FIFO {
public:
    FIFO(int capacity) {
        _capacity = capacity;
        arr = new int[_capacity]{0};
    }

    ~FIFO() {
        delete[] arr;
    }

    void insert(int data) {
        arr[_index] = data;

        if (_index >= _capacity) {
            _index = 0;
        } else {
            _index++;
        }
    }

    int average(void) {
        int sum = 0;
        for (int i=0; i<_capacity; i++) {
            sum += arr[i];
        }
        sum /= _capacity;
        return sum;
    }

private:
    int * arr;
    int _index;
    int _capacity;
};

#endif