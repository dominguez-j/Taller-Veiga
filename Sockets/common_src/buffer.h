#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <vector>

class Buffer {
private:
    std::vector<char> buffer;

    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;

public:
    explicit Buffer(size_t size): buffer(size) {}

    char operator[](size_t index) const;
    char* data();
    size_t size() const;

    Buffer(Buffer&&) = default;
    Buffer& operator=(Buffer&&) = default;

    ~Buffer() = default;
};
#endif  // __BUFFER_H__
