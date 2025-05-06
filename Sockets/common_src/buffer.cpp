#include "buffer.h"

char* Buffer::data() { return buffer.data(); }

size_t Buffer::size() const { return buffer.size(); }

char Buffer::operator[](size_t index) const { return buffer[index]; }
