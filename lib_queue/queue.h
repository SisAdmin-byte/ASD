template <class T>
class Queue {
    T* _data;
    int _head;
    int _count;
    int _capacity;

public:

    Queue(int capacity = 15);
    Queue(const Queue<T>& other);
    ~Queue();

    Queue<T>& operator=(const Queue<T>& other);
    Queue<T>& operator=(Queue<T>&& other) noexcept;
    void enqueue(const T& value);
    T dequeue();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool empty() const;
    bool full() const;
    int size() const;
    int capacity() const;
    void clear();
    int tail() const;
    void resize(int newCapacity);

};

template <class T>
Queue<T>::Queue(int capacity) : _data(new T[capacity]), _head(0), _count(0), _capacity(capacity){}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : _data(new T[other._capacity]), _head(other._head), _count(other._count), _capacity(other._capacity) {
    for (int i = 0; i < _count; i++) {
        _data[(i + _head) % _capacity] = other._data[(i + other._head) % other._capacity];
    }
}

template <class T>
Queue<T>::~Queue() {
    delete[] _data;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        delete[] _data;
        _capacity = other._capacity;
        _head = other._head;
        _count = other._count;
        _data = new T[_capacity];

        for (int i = 0; i < _count; i++) {
            _data[(i + _head) % _capacity] = other._data[(i + other._head) % other._capacity];
        }
    }
    return *this;
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
    if (this != &other) {
        delete[] _data;
        _data = other._data;
        _head = other._head;
        _count = other._count;
        _capacity = other._capacity;

        other._data = nullptr;
        other._head = 0;
        other._count = 0;
        other._capacity = 0;
    }
    return *this;
}

template <class T>
void Queue<T>::enqueue(const T& value) {
    if (full()) {
        resize(_capacity * 2);
    }
    _data[tail()] = value;
    _count++;
}

template <class T>
T Queue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    T value = std::move(_data[_head]);
    _head = (_head + 1) % _capacity;
    _count--;
    return value;
}

template <class T>
T& Queue<T>::front() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _data[_head];
}

template <class T>
const T& Queue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _data[_head];
}

template <class T>
T& Queue<T>::back() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _data[tail() - 1];
}

template <class T>
const T& Queue<T>::back() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return _data[tail() - 1];
}

template <class T>
bool Queue<T>::empty() const {
    return _count == 0;
}

template <class T>
bool Queue<T>::full() const {
    return _count == _capacity;
}

template <class T>
int Queue<T>::size() const {
    return _count;
}

template <class T>
int Queue<T>::capacity() const {
    return _capacity;
}

template <class T>
void Queue<T>::clear() {
    _head = 0;
    _count = 0;
}

template <class T>
int Queue<T>::tail() const {
    return (_head + _count) % _capacity;
}

template <class T>
void Queue<T>::resize(int newCapacity) {
    T* newData = new T[newCapacity];
    for (int i = 0; i < _count; i++) {
        newData[i] = std::move(_data[(_head + i) % _capacity]);
    }
    delete[] _data;
    _data = newData;
    _head = 0;
    _capacity = newCapacity;
}