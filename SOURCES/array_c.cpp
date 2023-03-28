#include "../headers/array_h.hpp"

#include <cstring>
#include <string>

std::ostream& operator<<(std::ostream& os, const Array& arr) {
    for (int i = 0; i < arr._count; ++i) {
        os << arr._buf[i] << " ";
    }
    os << std::endl
       << arr._buf << " (" << arr._size << ")";
    return os;
}

Array::Array(size_t size) {
    this->_size = size;
    this->_count = 0;
    this->_buf = new int[size];
}

Array::Array(const Array& other) {
    this->_size = other._size;
    this->_count = other._count;
    this->_buf = new int[this->_size];
    std::memcpy(this->_buf, other._buf, this->_count * sizeof(int));
}

Array::~Array() {
    delete[] this->_buf;
}

int Array::get_item(size_t idx) {
    this->_check_bounds(idx);
    return this->_buf[idx];
}

bool Array::insert(int element, size_t pos) {
    this->_check_bounds(pos);
    this->_alloc(1);
    if (pos < this->_count) {
        size_t len = this->_size - pos;
        int* tmp_buf = new int[len];
        std::memcpy(tmp_buf, this->_buf + pos, len * sizeof(int));
        std::memcpy(this->_buf + pos + 1, tmp_buf, len * sizeof(int));
        delete[] tmp_buf;
    }
    this->_buf[pos] = element;
    this->_count++;
    return true;
}

bool Array::remove(int pos, int count) {
    this->_check_bounds(pos);

    int* tmp_buf = new int[this->_size - pos - count];
    std::memcpy(tmp_buf, this->_buf + pos + count, (this->_count - pos - count) * sizeof(int));
    std::memcpy(this->_buf + pos, tmp_buf, (this->_count - pos - count) * sizeof(int));
    delete[] tmp_buf;

    this->_count -= count;
    return true;
}

size_t Array::find(int element) {
    for (size_t i = 0; i < this->_count; ++i) {
        if (this->_buf[i] == element) {
            return i;
        }
    }
    return this->_size;
}

size_t Array::push(int element) {
    this->_alloc(1);
    this->_buf[this->_count] = element;
    return this->_count++;
}

bool Array::_alloc(size_t size) {
    if (this->_count + size <= this->_size)
        return true;

    size_t len = this->_size + size + 10;
    int* tmp_buf = new int[len];
    std::memcpy(tmp_buf, this->_buf, this->_count * sizeof(int));
    delete[] this->_buf;
    this->_buf = tmp_buf;
    this->_size = len;
    return true;
}

void Array::_check_bounds(size_t idx) {
    if (idx < 0 || idx >= this->_count)
        throw std::to_string(idx) + " index out of range!";
}

Array intersect(const Array& arr1, const Array& arr2) {
    Array result{1};
    Array arr2_cpy{arr2};
    for (size_t i = 0; i < arr1._count; ++i) {
        size_t idx = arr2_cpy.find(arr1._buf[i]);
        if (idx != arr2_cpy._size) {
            arr2_cpy.remove(idx, 1);
            result.push(arr1._buf[i]);
        }
    }

    return result;
}

Array merge(const Array& arr1, const Array& arr2, bool unique) {
    Array result{arr1};
    Array inter = intersect(arr1, arr2);
    if (unique) {
        for (size_t i = 0; i < arr2._count; ++i) {
            size_t idx = inter.find(arr2._buf[i]);
            if (idx != inter._size)
                inter.remove(idx, 1);
            else
                result.push(arr2._buf[i]);
        }
    } else {
        for (size_t i = 0; i < arr2._count; ++i) {
            result.push(arr2._buf[i]);
        }
    }
    return result;
}
