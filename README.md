# SimpleKV

Simple Key-Value pair manager in C++17.
> This repository forks from [Forairaaaaa/simplekv](https://github.com/Forairaaaaa/simplekv). I have made  tremendous optimization and refactor to the implementation of the original repository.

## Prerequisite

- GTest
- CMake 3.5.0 or higher
- Essential build toolchains

## Usage

You can get detailed usage examples from [test/basic_test.cpp](/test/basic_test.cpp).

GTest is used for easy functional checking.
```bash
cmake -B build -S .
cmake --build build -j$(nproc)
cd build && ctest --output-on-failure GTEST_COLOR=TRUE
```

## Notice

The underlying container of `SimpleKV` is `std::unordered_map<std::string_view, DataInner_t>`. `DataInner_t` only store the meta-data of the stored pairs. So If you want to insert a STL instance such as `std::string`, `std::vector`, you should only insert its pointer. Otherwise, STL underlying memory manager may change its data address, causing data lost.

```cpp
struct DataInner
{
    size_t size{0};
    void *addr{nullptr};

    template <typename T>
    T value()
    {
        if ((this->addr == nullptr) || (this->size < sizeof(T))) {
            return T();
        }
        return *reinterpret_cast<T *>(this->addr);
    }
};
using DataInner_t = struct DataInner;
```

## License

MIT License
