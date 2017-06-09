#ifndef __HASH__TABLE_H_
#define __HASH__TABLE_H_

#include <iterator>
#include <memory>
#include <functional>
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


#endif // __HASH__TABLE_H_