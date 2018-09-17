#include <iterator>
namespace helpers {
	template<class Container>
	class push_iterator
	{
		public:
		using value_type = void;
		using difference_type = void;
		using pointer = void;
		using reference = void;
		using iterator_category = std::output_iterator_tag;

		push_iterator(Container& container): container(&container) {}

		push_iterator& operator=(typename Container::value_type const& value){
			container->push(value);
			return *this; 
		}
		push_iterator& operator=(typename Container::value_type && value) {
			container->emplace(value);
			return *this;
		}
		push_iterator& operator*() { /*intentional no-op to satisfy OutputIterator */ return *this; }
		push_iterator& operator++() { /*intentional no-op to satisfy OutputIterator */return *this; } 
		push_iterator& operator++(int) { /*intentional no-op to satisfy OutputIterator */return *this; }

		private:
		Container* container;
	};

	template <class Container>
	push_iterator<Container> make_pusher(Container& container)
	{
		return push_iterator<Container>(container);
	}
}
