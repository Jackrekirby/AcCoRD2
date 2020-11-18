#pragma once
#include <array>

namespace std
{
    // An array which requires to be indexed by enums
    template<typename Enum, class T, std::size_t Size>
    class enum_array : public std::array<T, Size> {
    public:
        T& operator[] (Enum e) {
            return std::array<T, Size>::operator[](static_cast<std::size_t>(e));
        }

        const T& operator[] (Enum e) const {
            return std::array<T, Size>::operator[](static_cast<std::size_t>(e));
        }

        T& at(Enum e) {
            return std::array<T, Size>::at(static_cast<std::size_t>(e));
        }

        const T& at(Enum e) const {
            return std::array<T, Size>::at(static_cast<std::size_t>(e));
        }
    };
}