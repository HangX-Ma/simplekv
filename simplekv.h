#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>

namespace simple_kv
{
/* Structure to store data info */
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

class SimpleKV
{
public:
    ~SimpleKV()
    {
        clear();
    }

    /** Get the number of elements in the unordered map */
    inline size_t size()
    {
        return map_.size();
    }

    /** Check if the key exists */
    bool exist(const std::string &key);

    /**  Get all memory usage of the map */
    size_t memoryUsage();

    /**
     * @brief Create a new `DataInner_t` element and store it
     *
     * @return true - ok
     * @return false - already exist or 0 size
     */
    bool add(const std::string &key, void *value, size_t size);

    /**
     * @brief put the value at specific memory
     *
     * @return true - ok
     * @return false - not exist
     */
    bool put(const std::string &key, void *value);

    /**
     * @brief Get a `DataInner_t` pointer
     *
     * @return `nullptr` if key not exist
     */
    DataInner_t *get(const std::string &key);

    /**
     * @brief remove the key and free the memory
     *
     * @return true - ok
     * @return false - not exist
     */
    bool remove(const std::string &key);

    /** remove all pairs in unordered map and free the memory */
    void clear();

    /* Template Wrapper */
    template <typename T>
    inline bool add(const std::string &key, T value)
    {
        return add(key, reinterpret_cast<void *>(&value), sizeof(T));
    }

    template <typename T>
    inline bool put(const std::string &key, T value)
    {
        return put(key, reinterpret_cast<void *>(&value));
    }

private:
    std::unordered_map<std::string, DataInner_t> map_;
    DataInner_t data_buffer_;
};

} // namespace simple_kv
