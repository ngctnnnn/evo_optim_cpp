
// Copyright 2006-2009 Daniel James.
// Copyright 2022 Christian Mazakas.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This test creates the containers with members that meet their minimum
// requirements. Makes sure everything compiles and is defined correctly.

#include "../helpers/unordered.hpp"

#include "../helpers/test.hpp"
#include "../objects/minimal.hpp"
#include "./compile_tests.hpp"

// Explicit instantiation to catch compile-time errors

#ifdef BOOST_UNORDERED_FOA_TESTS

// emulates what was already done for previous tests but without leaking to
// the detail namespace
//
template <typename T, typename H, typename P, typename A>
class instantiate_flat_set
{
  typedef boost::unordered_flat_set<T, H, P, A> container;
  container x;
};

template class instantiate_flat_set<int, boost::hash<int>, std::equal_to<int>,
  test::minimal::allocator<int> >;

template class instantiate_flat_set<test::minimal::assignable const,
  test::minimal::hash<test::minimal::assignable>,
  test::minimal::equal_to<test::minimal::assignable>,
  test::minimal::allocator<int> >;

#else

#define INSTANTIATE(type)                                                      \
  template class boost::unordered::detail::instantiate_##type

INSTANTIATE(set)<int, boost::hash<int>, std::equal_to<int>,
  test::minimal::allocator<int> >;
INSTANTIATE(multiset)<int const, boost::hash<int>, std::equal_to<int>,
  test::minimal::allocator<int> >;

INSTANTIATE(set)<test::minimal::assignable const,
  test::minimal::hash<test::minimal::assignable>,
  test::minimal::equal_to<test::minimal::assignable>,
  test::minimal::allocator<int> >;
INSTANTIATE(multiset)<test::minimal::assignable,
  test::minimal::hash<test::minimal::assignable>,
  test::minimal::equal_to<test::minimal::assignable>,
  test::minimal::allocator<int> >;

#endif

UNORDERED_AUTO_TEST (type_traits) {
#ifdef BOOST_UNORDERED_FOA_TESTS
  typedef boost::unordered_flat_set<int> set_type;
#else
  typedef boost::unordered_set<int> set_type;
#endif

  typedef set_type::iterator iterator;

  BOOST_STATIC_ASSERT(boost::is_same<int const&,
    std::iterator_traits<iterator>::reference>::value);
}

UNORDERED_AUTO_TEST (test0) {
  test::minimal::constructor_param x;

  test::minimal::assignable assignable(x);

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set.\n";

#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<int> int_set;

  boost::unordered_flat_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_set2;

  boost::unordered_flat_set<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    set;
#else
  boost::unordered_set<int> int_set;

  boost::unordered_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_set2;

  boost::unordered_set<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    set;
#endif

  container_test(int_set, 0);
  container_test(int_set2, 0);
  container_test(set, assignable);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset.\n";

  boost::unordered_multiset<int> int_multiset;

  boost::unordered_multiset<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_multiset2;

  boost::unordered_multiset<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    multiset;

  container_test(int_multiset, 0);
  container_test(int_multiset2, 0);
  container_test(multiset, assignable);
#endif
}

UNORDERED_AUTO_TEST (equality_tests) {
  typedef test::minimal::copy_constructible_equality_comparable value_type;

#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<int> int_set;

  boost::unordered_flat_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_set2;

  boost::unordered_flat_set<
    test::minimal::copy_constructible_equality_comparable,
    test::minimal::hash<test::minimal::copy_constructible_equality_comparable>,
    test::minimal::equal_to<
      test::minimal::copy_constructible_equality_comparable>,
    test::minimal::allocator<value_type> >
    set;
#else
  boost::unordered_set<int> int_set;

  boost::unordered_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_set2;

  boost::unordered_set<test::minimal::copy_constructible_equality_comparable,
    test::minimal::hash<test::minimal::copy_constructible_equality_comparable>,
    test::minimal::equal_to<
      test::minimal::copy_constructible_equality_comparable>,
    test::minimal::allocator<value_type> >
    set;
#endif

  equality_test(int_set);
  equality_test(int_set2);
  equality_test(set);

#ifndef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_multiset<int> int_multiset;

  boost::unordered_multiset<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    int_multiset2;

  boost::unordered_multiset<
    test::minimal::copy_constructible_equality_comparable,
    test::minimal::hash<test::minimal::copy_constructible_equality_comparable>,
    test::minimal::equal_to<
      test::minimal::copy_constructible_equality_comparable>,
    test::minimal::allocator<value_type> >
    multiset;

  equality_test(int_multiset);
  equality_test(int_multiset2);
  equality_test(multiset);
#endif
}

UNORDERED_AUTO_TEST (test1) {
  boost::hash<int> hash;
  std::equal_to<int> equal_to;
  int value = 0;

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set." << std::endl;
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<int> set;

  boost::unordered_flat_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    set2;
#else
  boost::unordered_set<int> set;

  boost::unordered_set<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    set2;
#endif

  unordered_unique_test(set, value);
  unordered_set_test(set, value);
  unordered_copyable_test(set, value, value, hash, equal_to);

  unordered_unique_test(set2, value);
  unordered_set_test(set2, value);
  unordered_copyable_test(set2, value, value, hash, equal_to);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset." << std::endl;

  boost::unordered_multiset<int> multiset;

  boost::unordered_multiset<int, boost::hash<int>, std::equal_to<int>,
    test::minimal::cxx11_allocator<int> >
    multiset2;

  unordered_equivalent_test(multiset, value);
  unordered_set_test(multiset, value);
  unordered_copyable_test(multiset, value, value, hash, equal_to);

  unordered_equivalent_test(multiset2, value);
  unordered_set_test(multiset2, value);
  unordered_copyable_test(multiset2, value, value, hash, equal_to);
#endif
}

UNORDERED_AUTO_TEST (test2) {
  test::minimal::constructor_param x;

  test::minimal::assignable assignable(x);
  test::minimal::copy_constructible copy_constructible(x);
  test::minimal::hash<test::minimal::assignable> hash(x);
  test::minimal::equal_to<test::minimal::assignable> equal_to(x);

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set.\n";
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    set;
#else
  boost::unordered_set<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    set;
#endif

  unordered_unique_test(set, assignable);
  unordered_set_test(set, assignable);
  unordered_copyable_test(set, assignable, assignable, hash, equal_to);
  unordered_set_member_test(set, assignable);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset.\n";

  boost::unordered_multiset<test::minimal::assignable,
    test::minimal::hash<test::minimal::assignable>,
    test::minimal::equal_to<test::minimal::assignable>,
    test::minimal::allocator<test::minimal::assignable> >
    multiset;

  unordered_equivalent_test(multiset, assignable);
  unordered_set_test(multiset, assignable);
  unordered_copyable_test(multiset, assignable, assignable, hash, equal_to);
  unordered_set_member_test(multiset, assignable);
#endif
}

UNORDERED_AUTO_TEST (movable1_tests) {
  test::minimal::constructor_param x;

  test::minimal::movable1 movable1(x);
  test::minimal::hash<test::minimal::movable1> hash(x);
  test::minimal::equal_to<test::minimal::movable1> equal_to(x);

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set.\n";
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<test::minimal::movable1,
    test::minimal::hash<test::minimal::movable1>,
    test::minimal::equal_to<test::minimal::movable1>,
    test::minimal::allocator<test::minimal::movable1> >
    set;
#else
  boost::unordered_set<test::minimal::movable1,
    test::minimal::hash<test::minimal::movable1>,
    test::minimal::equal_to<test::minimal::movable1>,
    test::minimal::allocator<test::minimal::movable1> >
    set;
#endif

  // unordered_unique_test(set, movable1);
  unordered_set_test(set, movable1);
  unordered_movable_test(set, movable1, movable1, hash, equal_to);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset.\n";

  boost::unordered_multiset<test::minimal::movable1,
    test::minimal::hash<test::minimal::movable1>,
    test::minimal::equal_to<test::minimal::movable1>,
    test::minimal::allocator<test::minimal::movable1> >
    multiset;

  // unordered_equivalent_test(multiset, movable1);
  unordered_set_test(multiset, movable1);
  unordered_movable_test(multiset, movable1, movable1, hash, equal_to);
#endif
}

UNORDERED_AUTO_TEST (movable2_tests) {
  test::minimal::constructor_param x;

  test::minimal::movable2 movable2(x);
  test::minimal::hash<test::minimal::movable2> hash(x);
  test::minimal::equal_to<test::minimal::movable2> equal_to(x);

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set.\n";
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<test::minimal::movable2,
    test::minimal::hash<test::minimal::movable2>,
    test::minimal::equal_to<test::minimal::movable2>,
    test::minimal::allocator<test::minimal::movable2> >
    set;
#else
  boost::unordered_set<test::minimal::movable2,
    test::minimal::hash<test::minimal::movable2>,
    test::minimal::equal_to<test::minimal::movable2>,
    test::minimal::allocator<test::minimal::movable2> >
    set;
#endif

  // unordered_unique_test(set, movable2);
  unordered_set_test(set, movable2);
  unordered_movable_test(set, movable2, movable2, hash, equal_to);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset.\n";

  boost::unordered_multiset<test::minimal::movable2,
    test::minimal::hash<test::minimal::movable2>,
    test::minimal::equal_to<test::minimal::movable2>,
    test::minimal::allocator<test::minimal::movable2> >
    multiset;

  // unordered_equivalent_test(multiset, movable2);
  unordered_set_test(multiset, movable2);
  unordered_movable_test(multiset, movable2, movable2, hash, equal_to);
#endif
}

UNORDERED_AUTO_TEST (destructible_tests) {
  test::minimal::constructor_param x;

  test::minimal::destructible destructible(x);
  test::minimal::hash<test::minimal::destructible> hash(x);
  test::minimal::equal_to<test::minimal::destructible> equal_to(x);

  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_set.\n";
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<test::minimal::destructible,
    test::minimal::hash<test::minimal::destructible>,
    test::minimal::equal_to<test::minimal::destructible> >
    set;
#else
  boost::unordered_set<test::minimal::destructible,
    test::minimal::hash<test::minimal::destructible>,
    test::minimal::equal_to<test::minimal::destructible> >
    set;
#endif

  unordered_destructible_test(set);

#ifndef BOOST_UNORDERED_FOA_TESTS
  BOOST_LIGHTWEIGHT_TEST_OSTREAM << "Test unordered_multiset.\n";

  boost::unordered_multiset<test::minimal::destructible,
    test::minimal::hash<test::minimal::destructible>,
    test::minimal::equal_to<test::minimal::destructible> >
    multiset;

  unordered_destructible_test(multiset);
#endif
}

// Test for ambiguity when using key convertible from iterator
// See LWG2059

struct lwg2059_key
{
  int value;

  template <typename T> lwg2059_key(T v) : value(v) {}
};

std::size_t hash_value(lwg2059_key x)
{
  return static_cast<std::size_t>(x.value);
}

bool operator==(lwg2059_key x, lwg2059_key y) { return x.value == y.value; }

UNORDERED_AUTO_TEST (lwg2059) {
#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<lwg2059_key> x;
  x.emplace(lwg2059_key(10));
  x.erase(x.begin());
#else
  {
    boost::unordered_set<lwg2059_key> x;
    x.emplace(lwg2059_key(10));
    x.erase(x.begin());
  }

  {
    boost::unordered_multiset<lwg2059_key> x;
    x.emplace(lwg2059_key(10));
    x.erase(x.begin());
  }
#endif
}

RUN_TESTS()
