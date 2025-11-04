#pragma once


template <class T>
struct Node {

	T value;
	Node<T>* next;
	Node(T value_, Node<T>* next_ = nullptr);
};

template <class T>
Node<T>::Node(T value_, Node<T>* next_) : value(value_), next(next_) {}

template <class T>
class List {

	Node<T>* _head;
	Node<T>* _tail;
	int _count;

public:


	class Iterator {


		Node<T>* current;

	public:

		Iterator();

		Iterator& operator = (const Iterator& other);
		T& operator*();
		Iterator operator++();      // x++;
		Iterator& operator++();       // ++x;

	};



	List() : _head(nullptr), _tail(nullptr), _count(0) {}
	List(const List& other) {
		_head = nullptr;
		_tail = nullptr;
		_count = 0;

		Node<T>* current = other._head;
		while (current != nullptr) {
			push_back(current->value);
			current = current->next;
		}
	}

	~List() {
		while (!is_empty()) {
			pop_front();
		}
	}

	List& operator=(const List& other) {
		if (this != &other) {
			while (!is_empty()) {
				pop_front();
			}

			Node<T>* current = other._head;
			while (current != nullptr) {
				push_back(current->value);
				current = current->next;
			}
		}
		return *this;
	}

	void push_front(const T& val);
	void push_back(const T& val);
	void insert(int pos, const T& val);
	void insert(Node<T>* node, const T& val);

	void pop_front();
	void pop_back();
	T front() const;
	T back() const;
	void erase(Node<T>* node);

	bool is_empty();
	Node<T>* find(const T& val);
	int size() const { return _count; }

};

template <class T>
void List<T>::push_front(const T& val) {

	Node<T>* node = new Node<T>(val, _head);
	node->next = _head;
	if (is_empty()) _tail = node;
	_head = node;
	_count++;

}

template <class T>
bool List<T>::is_empty() {
	return _head == nullptr;
}

template <class T>
void List<T>::push_back(const T& val) {

	Node<T>* node = new Node<T>(val);
	// _tail->next = node; // траблы какие-то, я прослушал
	if (is_empty()) {
		_head = node;
		_tail = node;
		_count++;
		return;
	}

	_tail->next = node;
	_tail = node;
	++_count;
	//      nullptr
	//  (val) ---> Null
	//  node

}

template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
	if (node == nullptr) throw ("Error");
	Node<T>* new_node = new Node<T>(val, node->next);
	node->next = new_node;
	if (_tail == node) {
		_tail = new_node;
	}
	_count++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
	if (pos < 0 || pos >= _count) throw ("Error");

	if (pos == 0) {
		push_front(val);
	}
	else if (pos == _count - 1) {
		push_back(val);
	}
	else {
		int cur_pos = 0;
		Node<T>* cur = _head;
		while (cur != nullptr) {
			if (cur_pos == pos - 1) break;
			cur_pos++;
			cur = cur->next;
		}

		if (cur != nullptr) {
			Node<T>* new_node = new Node<T>(val, cur->next);
			cur->next = new_node;
			_count++;
		}
	}
}

template <class T>
Node<T>* List<T>::find(const T& val) {
	Node<T>* current = _head;
	while (current != nullptr) {
		if (current->value == val) {
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

template <class T>
void List<T>::pop_front() {
	if (is_empty()) throw ("List is empty");

	Node<T>* temp = _head;
	_head = _head->next;
	delete temp;
	_count--;

	if (_head == nullptr) {
		_tail = nullptr;
	}
}

template <class T>
void List<T>::pop_back() {
	if (is_empty()) throw ("List is empty");

	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
		return;
	}

	Node<T>* current = _head;
	while (current->next != _tail) {
		current = current->next;
	}

	delete _tail;
	_tail = current;
	_tail->next = nullptr;
	_count--;
}

template <class T>
T List<T>::front() const {
	if (is_empty()) throw ("List is empty");
	return _head->value;
}

template <class T>
T List<T>::back() const {
	if (is_empty()) throw ("List is empty");
	return _tail->value;
}


template <class T>
void List<T>::erase(Node<T>* node) {
	if (node == nullptr || is_empty()) return;

	if (node == _head) {
		pop_front();
		return;
	}

	Node<T>* prev = _head;
	while (prev != nullptr && prev->next != node) {
		prev = prev->next;
	}

	if (prev != nullptr) {
		prev->next = node->next;
		if (node == _tail) {
			_tail = prev;
		}
		delete node;
		_count--;
	}
}
