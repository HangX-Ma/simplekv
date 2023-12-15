# SimpleKV

Simple Key-Value pair manager in C++17.
> This repository forks from [Forairaaaaa/simplekv](https://github.com/Forairaaaaa/simplekv). I have made  tremendous optimization and refactor to the implementation of the original repository.

## Prerequisite

- GTest
- CMake 3.5.0 or higher
- Essential build toolchains

## Usage

You can get detailed usage examples from [test/basic_test.cpp](/test/basic_test.cpp).

### Compile Tests

GTest is used for easy functional checking. You can easily run tests using following commands.

```bash
cmake -B build -DSIMPLEKV_BUILD_TESTS=ON
cmake --build build -j$(nproc)
cmake --build build --target test
```

### Use as third party library

- Add this repository as one of your submodules. This command will download it into `library/simplekv`.

    ```bash
    git submodule add https://github.com/HangX-Ma/simplekv.git library/simplekv
    ```

    Your `.gitmodules` will add following contents.

    ```json
    [submodule "library/simplekv"]
        path = library/simplekv
        url = https://github.com/HangX-Ma/simplekv.git
    ```

- Add the `simplekv` as **subdirectory** in your `library/CMakeLists.txt`.

    ```cmake
    cmake_minimum_required(VERSION 3.14)
    project(library)
    add_subdirectory(simplekv)
    ```
    > Don't forget to make `library/CMakeLists.txt` valid in your main project `CMakeLists.txt`.

- Use `target_link_libraries` command in `CMakeLists.txt` to add this library as dependence.

    ```cmake
    target_link_libraries(${TARGET_NAME} simplekv::simplekv)
    ```

- There are some options that you can use for CMake configuration.

    ```cmake
    # build shared option
    option(SIMPLEKV_BUILD_SHARED "Build shared library" OFF)

    # build position independent code
    option(SIMPLEKV_BUILD_PIC "Build position independent code (-fPIC)" OFF)

    # sanitizer options
    option(SIMPLEKV_SANITIZE_ADDRESS "Enable address sanitizer in tests" OFF)

    # warning options
    option(SIMPLEKV_BUILD_WARNINGS "Enable compiler warnings" ${SIMPLEKV_MASTER_PROJECT})

    # testing options
    option(SIMPLEKV_BUILD_TESTS "Build tests" OFF)
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
