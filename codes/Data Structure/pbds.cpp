#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <class T>
// ordered_multiset: do not use erase method, use myerase() instead
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<class T>
void myerase(ordered_multiset<T> &ss, T v)
{
    T rank = ss.order_of_key(v);    // Number of elements that are less than v in ss
    auto it = ss.find_by_order(rank); // Iterator that points to the element which index = rank
    ss.erase(it);
}
