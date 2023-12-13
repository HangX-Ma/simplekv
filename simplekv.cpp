#include "simplekv.h"

namespace simple_kv
{
bool SimpleKV::exist(const std::string &key)
{
    return map_.count(key) > 0;
}

size_t SimpleKV::memoryUsage()
{
    size_t usage = 0;
    for (const auto &[key, data] : map_) {
        usage += data.size;
    }
    return usage;
}

bool SimpleKV::add(const std::string &key, void *value, size_t size)
{
    if (exist(key) || (size == 0)) {
        return false;
    }

    DataInner_t new_item{size, malloc(size)};
    memcpy(new_item.addr, value, size);
    map_[key] = new_item;

    return true;
}

bool SimpleKV::put(const std::string &key, void *value)
{
    if (!exist(key)) {
        return false;
    }
    auto iter = map_.find(key);
    memcpy(iter->second.addr, value, iter->second.size);
    return true;
}

DataInner_t *SimpleKV::get(const std::string &key)
{
    if (!exist(key)) {
        data_buffer_.size = 0;
        data_buffer_.addr = nullptr;
        return &data_buffer_;
    }

    auto iter = map_.find(key);
    memcpy(&data_buffer_, &iter->second, sizeof(DataInner_t));
    return &data_buffer_;
}

bool SimpleKV::remove(const std::string &key)
{
    if (!exist(key)) {
        return false;
    }
    auto iter = map_.find(key);
    free(iter->second.addr);
    map_.erase(iter);

    return true;
}

void SimpleKV::clear()
{
    for (const auto &[key, data] : map_) {
        free(data.addr);
    }
    map_.clear();
}
} // namespace simple_kv
