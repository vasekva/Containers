#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <stdlib.h>
#include <memory>

#include "../utility/pair.hpp"
#include "../iterators/iterator.hpp"
#include "../xtree/xtree_prototypes.hpp"

using namespace std;

namespace ft
{
	template <class K, class T, class Pr, class Ax, bool Mfl>
	class Tmap_traits
	{
		public:
			typedef K						key_type;
			typedef ft::pair<const K, T>	value_type;
			typedef Pr						key_compare;
			typedef typename Ax::template rebind<value_type>::other
					allocator_type;

			enum {Multi = Mfl};

			Tmap_traits()
				: comp()
			{

			}

			Tmap_traits(Pr Parg)
				: comp(Parg)
			{

			}

			class value_compare
					: public binary_function<value_type, value_type, bool>
			{
				friend class Tmap_traits<K, T, Pr, Ax, Mfl>;
				public:
					bool operator()(const value_type &X,
									const value_type &Y) const
					{
						return(comp(X.first, Y.first));
					}
					value_compare(key_compare Pred)
							: comp(Pred) {}
				protected:
					key_compare comp;
			};

			const static K &GetKey(const value_type &V)
			{
				return (V.first);
			}
			Pr comp;
	};

	template <class K, class T, class Pr = ft::less<K>,
		class A = std::allocator<ft::pair<const K, T> > >
	class map
		: public Tree<Tmap_traits<K, T, Pr, A, false> >
	{
		public:
			typedef map<K, T, Pr, A>	Myt;

			typedef Tree<Tmap_traits<K, T, Pr, A, false>  >
					Mybase;
			typedef K	key_type;
			typedef T	mapped_type;
			typedef T	reference_type;
			typedef Pr	key_compare;
			typedef typename Mybase::value_compare		value_compare;
			typedef typename Mybase::allocator_type		allocator_type;
			typedef typename Mybase::size_type			size_type;
			typedef typename Mybase::difference_type	difference_type;
			typedef typename Mybase::pointer			pointer;
			typedef typename Mybase::const_pointer		const_pointer;
			typedef typename Mybase::reference			reference;
			typedef typename Mybase::const_reference	const_reference;
			typedef typename Mybase::iterator			iterator;
			typedef typename Mybase::const_iterator		const_iterator;
			typedef typename Mybase::reverse_iterator	reverse_iterator;
			typedef typename Mybase::const_reverse_iterator
					const_reverse_iterator;
			typedef typename Mybase::value_type			value_type;

			map()
					: Mybase(key_compare(), allocator_type())
			{
			}

			~map()
			{
				Mybase::clear();
			}

			explicit map(const key_compare &Pred)
					: Mybase(Pred, allocator_type())
			{

			}

			map(const key_compare &Pred, const allocator_type &Al)
					: Mybase(Pred, Al)
			{

			}

			template <class It>
			map(It F, It L)
					: Mybase(key_compare(), allocator_type())
			{
				for (; F != L; ++F)
					this->insert(*F);
			}

			template <class It>
			map(It F, It L, const key_compare &Pred)
					: Mybase(Pred, allocator_type())
			{
				for (; F != L; ++F)
					this->insert(*F);
			}

			template <class It>
			map(It F, It L, const key_compare &Pred,
				const allocator_type &Al)
					: Mybase(Pred, Al)
			{
				for (; F != L; ++F)
					this->insert(*F);
			}

			mapped_type &at(const key_type &Kv)
			{
				iterator P = this->find(Kv);

				if (P == this->end())
					throw std::out_of_range("key not found");
				else
					return ((*P).second);
			}

			mapped_type &at(const key_type &Kv) const
			{
				return static_cast<const mapped_type>(at(Kv));
			}

			mapped_type &operator[](const key_type &Kv)
			{
				iterator P = this->insert(value_type(Kv, mapped_type())).first;
				return ((*P).second);
			}


	};
}

#endif