class DSU {

	int* _parent;
	size_t _size;
	int* _rank;

public:

	DSU(size_t size);
	void unite(int, int);
	int find(int);
	~DSU();

};

DSU::DSU(size_t size) : _size(size) {

	_parent = new int[size];
	_rank = new int[size];
	for (int i = 0; i < _size; i++) {
		_parent[i] = i;
	}


}

DSU::~DSU() {

	delete[] _parent;

}

int DSU::find(int x) {

	if (_parent[x] == x) {
		return x;
	}
	else {
		return find(_parent[x]);
	}

}


void DSU::unite(int x1, int x2) {

	if (_rank[x1] < _rank[x2]) {
		_parent[x1] = find(x2);
	}
	else {
		if (_rank[x1] == _rank[x2]) {
			_rank[x1]++;
		}
		_parent[x2] = find(x1);
	}

}