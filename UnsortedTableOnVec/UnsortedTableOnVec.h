#include "C:\Users\antoshka\source\Actual\ASD\Itable\Itable.h"

template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public ITable<Tkey, Tvalue> {

	TVector<std::pair<Tkey, Tvalue>> _rows;;

public:
	~UnsortedTableOnVec() {};
	void insert(const Tkey& key, const Tvalue& value) override;
	Tvalue find(const Tkey key) const override;
	void erase(const Tkey& key) override;
	std::ostream& print(std::ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool consist(const Tkey& key) const noexcept override;
	void replace(const Tkey& key, const Tvalue& value) override;
	UnsortedTableOnVec() = default;


};
template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::insert(const Tkey& key, const Tvalue& value) {

	_rows.insert(std::make_pair<Tkey, Tvalue>(key, value));

}


template <typename Tkey, typename Tvalue>
Tvalue UnsortedTableOnVec<Tkey, Tvalue>::find(const Tkey key) const {

	for (int i = 0; i < _rows.size(); i++) {

		if (_rows[i].first == key) {
			return _rows[i].second;
		}

	}

	throw std::logic_error("Key not found!");

}


template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::erase(const Tkey& key) {}

template <typename Tkey, typename Tvalue>
std::ostream& UnsortedTableOnVec<Tkey, Tvalue>::print(std::ostream& out) const {}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::is_empty() const {}

template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::consist(const Tkey& key) const {}

template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::replace(const Tkey& key, const Tvalue& value) {}