#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <algorithm>
#include <type_traits>

// FORWARD
// forward an lvalue
template<class T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{ return static_cast<T&&>(t); }

// forward an rvalue
template<class T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{ 
	static_assert(!std::is_lvalue_reference<T>::value, "template argument"
		" substituting _Tp is an lvalue reference type");
	return static_cast<T&&>(t);
}

// start pair
template<class T1, class T2>
struct pair
{
	T1 first;
	T2 second;

	constexpr pair()
		: first(), second() {}
	constexpr pair(const T1& x, const T2& y)
		: first(x), second(y) {}
	
	template<class U1, class U2>
	constexpr pair(U1&& x, U2&& y)
		: first(forward<U1>(x)), second(forward<U2>(y)) {}
	
	template<class U1, class U2>
	constexpr pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second) {}
	
	template<class U1, class U2>
	constexpr pair(pair<U1, U2>&& p)
		: first(forward<U1>(p.first)), second(forward<U2>(p.second)) {}

	pair( const pair& p ) = default;
	pair( pair&& p ) = default;
	
	pair& operator=(const pair& other)
		{ first = other.first; second = other.second; return *this; }
	template<class U1, class U2>
	pair& operator=(const pair<U1,U2>& other)
		{ first = other.first; second = other.second; return *this; }
	pair& operator=(pair&& other) noexcept((std::is_nothrow_move_assignable<T1>::value && std::is_nothrow_move_assignable<T2>::value))
		{ first = forward<T1>(other.first); second = forward<T2>(other.second); return *this; }
	template<class U1, class U2>
	pair& operator=(pair<U1,U2>&& other)
		{ first = forward<U1>(other.first); second = forward<U2>(other.second); return *this; }

	void swap(pair& other) noexcept(noexcept(swap(first, other.first)) && noexcept(swap(second, other.second)))
	{
		using std::swap;
		swap(first, other.first);
		swap(second, other.second);
	}
}; // end class pair

template< class T1, class T2 >
inline constexpr bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return (lhs.first == rhs.first) && (lhs.second == rhs.second); }
template< class T1, class T2 >
inline constexpr bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return (lhs.first != rhs.first) || (lhs.second != rhs.second); }
template< class T1, class T2 >
inline constexpr bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return lhs.first < rhs.first
		|| (!(lhs.first < rhs.first) && lhs.second < rhs.second); }
template< class T1, class T2 >
inline constexpr bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return (lhs == rhs) || (lhs < rhs); }
template< class T1, class T2 >
inline constexpr bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return rhs < lhs; }
template< class T1, class T2 >
inline constexpr bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
	{ return (lhs == rhs) || (lhs > rhs); }

template<class T1, class T2>
inline constexpr pair<T1, T2> make_pair(T1&& x, T2&& y)
{ return pair<T1, T2>(forward<T1>(x), forward<T2>(y)); }

#endif // __UTILITY_H__