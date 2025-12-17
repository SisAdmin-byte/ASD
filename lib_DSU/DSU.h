class DSU {
    int* _parent;
    int* _rank;
    size_t _size;

public:

    DSU(size_t size) : _size(size) {
        _parent = new int[size];
        _rank = new int[size];
        for (int i = 0; i < size; i++) {
            _parent[i] = i;
            _rank[i] = 0;
        }
    }

    ~DSU() {
        delete[] _parent;
        delete[] _rank;
    }

    int find(int x) {
        if (x < 0 || x >= _size) return -1;
        if (_parent[x] != x) {
            _parent[x] = find(_parent[x]);
        }
        return _parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY || rootX == -1 || rootY == -1) return;

        if (_rank[rootX] < _rank[rootY]) {
            _parent[rootX] = rootY;
        }
        else if (_rank[rootX] > _rank[rootY]) {
            _parent[rootY] = rootX;
        }
        else {
            _parent[rootY] = rootX;
            _rank[rootX]++;
        }
    }
};