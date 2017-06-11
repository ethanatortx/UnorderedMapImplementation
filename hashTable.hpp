#ifndef __HASH__TABLE_H_
#define __HASH__TABLE_H_

#include <functional>
#include <iterator>
#include <memory>
#include "utility.hpp"

template<class Key,
	class T = Key,
	class Hash = std::hash<Key>,
	class KeyEqual = std::equal_to<Key>,
	class Allocator = std::allocator<pair<const Key, T> >
> class hashTable
{
	struct hashNode;
public:
	enum { DEFAULT_BUCKET_SIZE = 13 };

	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename std::allocator_traits<Allocator>::pointer pointer;
	typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;

	class iterator;
	class const_iterator;
	class local_iterator;
	class const_local_iterator;

	hashTable() : hashTable(size_type(DEFAULT_BUCKET_SIZE)) {}
	// TODO
	explicit hashTable(size_type bucket_count,
		const Hash& hash = Hash(),
		const KeyEqual& equal = KeyEqual(),
		const Allocator& alloc = Allocator());

	hashTable(size_type bucket_count,
		const Allocator& alloc)
		: hashTable(bucket_count, Hash(), KeyEqual(), alloc) {}
	hashTable( size_type bucket_count,
		const Hash& hash,
		const Allocator& alloc)
		: hashTable(bucket_count, hash, KeyEqual(), alloc) {}

	// TODO
	explicit hashTable(const Allocator& alloc);

	// TODO
	template<class InputIt>
	hashTable(InputIt first, InputIt last,
		size_type bucket_count = DEFAULT_BUCKET_SIZE,
		const Hash& hash = Hash(),
		const KeyEqual& equal = KeyEqual(),
		const Allocator& alloc = Allocator() );

	template<class InputIt>
	hashTable(InputIt first, InputIt last,
		size_type bucket_count,
		const Allocator& alloc)
		: hashTable(first, last,
		  bucket_count, Hash(), KeyEqual(), alloc) {}

	template<class InputIt>
	hashTable( InputIt first, InputIt last,
		size_type bucket_count,
		const Hash& hash,
		const Allocator& alloc ) 
		: hashTable(first, last, 
		  bucket_count, hash, KeyEqual(), alloc) {}

	// TODO
	hashTable(const hashTable& other);
	hashTable(const hashTable& other, const Allocator& alloc);
	hashTable(hashTable&& other);
	hashTable(hashTable&& other, const Allocator& alloc);

	// TODO
	hashTable(std::initializer_list<value_type> init,
		size_type bucket_count = DEFAULT_BUCKET_SIZE,
		const Hash& hash = Hash(),
		const KeyEqual& equal = KeyEqual(),
		const Allocator& alloc = Allocator() );
	
	hashTable(std::initializer_list<value_type> init,
		size_type bucket_count,
		const Allocator& alloc)
		: hashTable(init, bucket_count,
		  Hash(), KeyEqual(), alloc) {}
	hashTable( std::initializer_list<value_type> init,
		size_type bucket_count,
		const Hash& hash,
		const Allocator& alloc ) 
		: hashTable(init, bucket_count, 
		  hash, KeyEqual(), alloc) {}

	// TODO
	hashTable& operator=(const hashTable&);

	// TODO
	iterator begin() noexcept;
	const_iterator begin() const noexcept;
	const_iterator cbegin() const noexcept;

	// TODO
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	// TODO
	bool empty() const noexcept;

	// TODO
	size_type size() const noexcept;
	size_type max_size() const noexcept;

	// TODO
	void clear() noexcept;

	// TODO
	pair<iterator, bool> insert(const value_type& value);
	template<class P>
	pair<iterator, bool> insert(P&& value);

	// insert with hint for start
	iterator insert(const_iterator hint, const value_type& value);
	template<class P>
	iterator insert(const_iterator hint, P&& value);

	template<class InputIt>
	void insert(InputIt first, InputIt last);
	void insert(std::initializer_list<value_type> ilist);

	// TODO
	template <class M>
	pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
	template <class M>
	pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
	template <class M>
	iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
	template <class M>
	iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);

	// TODO
	template<class... Args>
	pair<iterator, bool> emplace(Args&&... args);
	// TODO
	template<class... Args>
	iterator emplace(const_iterator hint, Args&&... args);
	// TODO
	template <class... Args>
	pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
	template <class... Args>
	pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);
	template <class... Args>
	iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
	template <class... Args>
	iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);

	// TODO
	iterator erase(const_iterator pos);
	iterator erase(const_iterator first, const_iterator last);
	size_type erase(const key_type& key);

	// TODO
	void swap(hashTable& other);

	// TODO
	mapped_type& at(const key_type& key);
	const mapped_type& at(const key_type& key) const;
	// TODO
	mapped_type& operator[](const key_type& key);
	mapped_type& operator[](key_type&& key);

	// TODO
	size_type count(const key_type& key) const;

	// TODO
	iterator find(const key_type& key);
	const_iterator find(const key_type& key) const;

	// TODO
	pair<iterator, iterator> equal_range(const key_type& key);
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const;

	// BUCKET INTERFACE
		// TODO
		local_iterator begin(size_type n);
		const_local_iterator begin(size_type n) const;
		const_local_iterator cbegin(size_type n) const;

		local_iterator end(size_type n);
		const_local_iterator end(size_type n) const;
		const_local_iterator cend(size_type n) const;

		size_type bucket_count() const;
		size_type max_bucket_count() const;
		size_type bucket_size(size_type n) const;
		size_type bucket(const key_type& key) const;

	// HASH POLICY
		// TODO
		float load_factor() const;
		float max_load_factor() const;
		void max_load_factor(float ml);

		void rehash(size_type count);
		void reserve(size_type count);

	// OBSERVERS
		// TODO
		hasher hash_function() const;
		key_equal key_eq() const;

	// COMPARE
		// TODO
		template<class UKey,
			class U,
			class UHash,
			class UKeyEqual,
			class UAllocator>
		friend bool operator==(hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& lhs, hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& rhs);
		template<class UKey,
			class U,
			class UHash,
			class UKeyEqual,
			class UAllocator>
		friend bool operator!=(hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& lhs, hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& rhs);
		template<class UKey,
			class U,
			class UHash,
			class UKeyEqual,
			class UAllocator>
		friend void swap(hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& lhs, hashTable<UKey, U, UHash, UKeyEqual, UAllocator>& rhs);

	// TODO
	~hashTable();

private:
	hashNode** __buckets;
	size_type __bucket_count;
	float __desired_load_factor;
};




/*
	Hash Node Definition [hashTable::hashNode]:
		A hash node has four constructors to handle all
 		four construction cases:
			default 				(0 args)
			only next pointer 		(1 args)
			only data 				(1 args)
			next pointer and data 	(2 args)

		There are two data members:
			[value]:
				the data contained within this node;
				Type is defined as value type of 
					hash table;
			[next]:
				pointer to next node in bucket;
				Each node pointer is a null-terminated
					singly linked list;
*/

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
struct hashTable<Key, T, Hash, KeyEqual, Allocator>::hashNode
{
	constexpr hashNode()
		: hashNode(NULL, typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type()) {}
	constexpr hashNode(hashNode* __next_)
		: hashNode(__next_, typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type()) {}
	constexpr hashNode(typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type __val_)
		: hashNode(NULL, __val_) {}
	constexpr explicit hashNode(hashNode* __next_, typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type __val_)
		: next(__next_), value(__val_) {}
	
	hashNode* next;
	hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type value;
};

/*
	Iterator Definition [hashTable::iterator]:
		The top-level iterator contains three constructors:
			default 						(0 args)
			only reference pointer 			(1 args)
			reference pointer and offset	(2 args)

		There are two data members:
			[ref]:
				Internal reference to hashNode array
					of the hashTable this iterator is
					connected to;
			[offset]:
				Index of array that iterator is currently
					referencing;
				Type defined as size type of hashTable;
*/
template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
class hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator
	: std::iterator<std::forward_iterator_tag, hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type>
{
public:
	using value_type = 
		typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef value_type const& const_reference;

	constexpr iterator()
		: iterator(NULL, 0) {}
	constexpr iterator(hashNode** __ref_)
		: iterator(__ref_, 0) {}
	constexpr explicit iterator(hashNode** __ref_,
		hashTable<Key, T, Hash, KeyEqual, Allocator>::size_type __off_)
		: ref(__ref_), offset(__off_) {}

	iterator& operator=(const iterator& other);
	iterator& operator++();
	iterator operator++(int);
	pointer operator->() const;
	reference operator*() const;

	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator==(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::iterator& rhs);
	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator!=(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::iterator& rhs);
private:
	hashNode** ref;
	hashTable<Key, T, Hash, KeyEqual, Allocator>::size_type offset;
};

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::operator=(const iterator& other)
{
	this->ref = other.ref;
	this->offset = other.offset;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::operator++()
{
	++offset;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::operator++(int)
{
	iterator tmp(*this);
	++offset;
	return tmp;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::pointer hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::operator->() const
{
	return &((*(ref + offset))->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::reference hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator::operator*() const
{
	return ((*(ref + offset))->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator==(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& rhs)
{
	return ((lhs.ref == rhs.ref) && (lhs.offset == rhs.offset));
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator!=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::iterator& rhs)
{
	return ((lhs.ref != rhs.ref) || (lhs.offset != rhs.offset));
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
class hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator
	: std::iterator<std::forward_iterator_tag, hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type>
{
public:
	using value_type = 
		typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type;
	typedef value_type const* pointer;
	typedef value_type const& reference;
	typedef value_type const& const_reference;

	constexpr const_iterator()
		: const_iterator(NULL, 0) {}
	constexpr const_iterator(hashNode const** __ref_)
		: const_iterator(__ref_, 0) {}
	constexpr explicit const_iterator(hashNode const** __ref_, hashTable<Key, T, Hash, KeyEqual, Allocator>::size_type __off_)
		: ref(__ref_), offset(__off_) {}

	const_iterator& operator=(const const_iterator& other);
	const_iterator& operator++();
	const_iterator operator++(int);
	pointer operator->() const;
	reference operator*() const;

	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator==(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::const_iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::const_iterator& rhs);
	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator!=(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::const_iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::const_iterator& rhs);

private:
	hashNode const** ref;
	hashTable<Key, T, Hash, KeyEqual, Allocator>::size_type offset;
};

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::operator=(const const_iterator& other)
{
	this->ref = other.ref;
	this->offset = other.offset;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::operator++()
{
	++offset;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::operator++(int)
{
	const_iterator tmp(*this);
	++offset;
	return tmp;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::pointer hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::operator->() const
{
	return &((*(ref + offset))->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::reference hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator::operator*() const
{
	return ((*(ref + offset))->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator==(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& rhs)
{
	return ((lhs.ref == rhs.ref) && (lhs.offset == rhs.offset));
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator!=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_iterator& rhs)
{
	return ((lhs.ref != rhs.ref) || (lhs.offset != rhs.offset));
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
class hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator
	: std::iterator<std::forward_iterator_tag, hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type>
{
public:
	using value_type =
		typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef value_type const& const_reference;

	constexpr local_iterator()
		: local_iterator(NULL) {}
	constexpr explicit local_iterator(hashNode* __ref_)
		: ref(__ref_) {}

	local_iterator& operator=(const local_iterator& other);
	local_iterator& operator++();
	local_iterator operator++(int);
	pointer operator->() const;
	reference operator*() const;

	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator==(const local_iterator& lhs, const local_iterator& rhs);
	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator!=(const local_iterator& lhs, const local_iterator& rhs);
private:
	hashNode* ref;
};

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::operator=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& other)
{
	this->ref = other.ref;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::operator++()
{
	if(ref)
		ref = ref->next;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::operator++(int)
{
	local_iterator tmp(*this);
	if(ref)
		ref = ref->next;
	return tmp;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::pointer hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::operator->() const
{
	return &(ref->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::reference hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator::operator*() const
{
	return (ref->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator==(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& rhs)
{
	return (lhs.ref == rhs.ref);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator!=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& rhs)
{
	return (lhs.ref != rhs.ref);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
class hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator
	: std::iterator<std::forward_iterator_tag, hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type>
{
public:
	using value_type =
		typename hashTable<Key, T, Hash, KeyEqual, Allocator>::value_type;
	typedef value_type const* pointer;
	typedef value_type const& reference;
	typedef value_type const& const_reference;

	constexpr const_local_iterator()
		: local_iterator(NULL) {}
	constexpr explicit const_local_iterator(hashNode const* __ref_)
		: ref(__ref_) {}

	const_local_iterator& operator=(const local_iterator& other);
	const_local_iterator& operator++();
	const_local_iterator operator++(int);
	pointer operator->() const;
	reference operator*() const;

	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator==(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::local_iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::local_iterator& rhs);
	template<class UKey,
		class UT,
		class UHash,
		class UKeyEqual,
		class UAllocator>
	friend bool operator!=(const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::local_iterator& lhs, const typename hashTable<UKey, UT, UHash, UKeyEqual, UAllocator>::local_iterator& rhs);
private:
	hashNode const* ref;
};


template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::operator=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::local_iterator& other)
{
	this->ref = other.ref;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::operator++()
{
	if(ref)
		ref = ref->next;
	return *this;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::operator++(int)
{
	const_local_iterator tmp(*this);
	if(ref)
		ref = ref->next;
	return tmp;
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::pointer hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::operator->() const
{
	return &(ref->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
inline typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::reference hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator::operator*() const
{
	return (ref->value);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator==(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& rhs)
{
	return (lhs.ref == rhs.ref);
}

template<class Key,
	class T,
	class Hash,
	class KeyEqual,
	class Allocator>
constexpr bool operator!=(const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& lhs, const typename hashTable<Key, T, Hash, KeyEqual, Allocator>::const_local_iterator& rhs)
{
	return (lhs.ref != rhs.ref);
}

#endif // __HASH__TABLE_H_