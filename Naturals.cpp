#include <iostream>
using namespace std;

class Zero{};

template <typename T>
class Suc{};

template <size_t N>
class Natural
{
public:
    using Type = Suc<typename Natural<N - 1>::Type>;
};

template <>
class Natural<0>
{
public:
    using Type = Zero;
};

template <typename A, typename B>
class Add{};

template <typename B>
class Add<Zero, B>
{
public:
    using Type = B;
};

template <typename A, typename B>
class Add<Suc<A>, B>
{
public:
    using Type = Suc<typename Add<A, B>::Type>;
};

template <typename A, typename B>
class Mul{};

template <typename B>
class Mul<Zero, B>
{
public:
    using Type = Zero;
};

template <typename A, typename B>
class Mul<Suc<A>, B>
{
public:
    using Type = typename Add<B, typename Mul<A, B>::Type>::Type;
};

template <typename A, typename B>
class Pow{};

template <typename A>
class Pow<A, Zero>
{
public:
    using Type = Suc<Zero>;
};

template <typename A, typename B>
class Pow<A, Suc<B>>
{
public:
    using Type = typename Mul<A, typename Pow<A, B>::Type>::Type;
};

template <typename A, typename B>
class Monus{};

template <typename A>
class Monus<A, Zero>
{
public:
    using Type = A;
};

template <typename B>
class Monus<Zero, Suc<B>>
{
public:
    using Type = Zero;
};

template <typename A, typename B>
class Monus<Suc<A>, Suc<B>>
{
public:
    using Type = typename Monus<A, B>::Type;
};

template <typename T>
class Print{};

template <>
class Print<Zero>
{
public:
    constexpr static size_t value = 0;
};

template <typename T>
class Print<Suc<T>>
{
public:
    constexpr static size_t value = Print<T>::value + 1;
};

class Nil{};

template <typename T>
class X1{};

template <typename T>
class X0{};

template <typename T>
class Inc{};

template <>
class Inc<Nil>
{
public:
    using Type = X1<Nil>;
};

template <typename T>
class Inc<X1<T>>
{
public:
    using Type = X0<typename Inc<T>::Type>;
};

template <typename T>
class Inc<X0<T>>
{
public:
    using Type = X1<T>;
};

template <typename T>
class PrintBin{};

template <>
class PrintBin<Nil>
{
public:
    constexpr static size_t value = 0;
};

template <typename T>
class PrintBin<X1<T>>
{
public:
    constexpr static size_t value = (PrintBin<T>::value << 1) + 1;
};

template <typename T>
class PrintBin<X0<T>>
{
public:
    constexpr static size_t value = PrintBin<T>::value << 1;
};

int main()
{
    // 2
    cout << Print<Suc<Suc<Zero>>>::value << endl;
    // 2 + 1
    cout << Print<Add<Suc<Suc<Zero>>, Suc<Zero>>::Type>::value << endl;
    // 2 * 3
    cout << Print<Mul<Suc<Suc<Zero>>, Suc<Suc<Suc<Zero>>>>::Type>::value << endl;
    // 3 ^ 2
    cout << Print<Pow<Natural<9>::Type, Natural<3>::Type>::Type>::value << endl;
    // 5 ∸ 2
    cout << Print<Monus<Natural<5>::Type, Natural<2>::Type>::Type>::value << endl;
    // 1 ∸ 3
    cout << Print<Monus<Natural<1>::Type, Natural<3>::Type>::Type>::value << endl;
    // x1 x1 x0 x1 nil
    cout << PrintBin<X1<X1<X0<X1<Nil>>>>>::value << endl;
    // inc x1 x1 x0 x1 nil
    cout << PrintBin<Inc<X1<X1<X0<X1<Nil>>>>>::Type>::value << endl;

    return 0;
}
