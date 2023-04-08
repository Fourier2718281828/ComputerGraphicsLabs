#include "ZBuffer.h"

ZBuffer& ZBuffer::getInstance()
{
    static ZBuffer instance;
    return instance;
}


void ZBuffer::clear()
{
    for (std::size_t i = 0u; i < buffer_.size(); ++i)
    {
        buffer_[i] = -10000;
    }
}

void ZBuffer::init(std::size_t cx, std::size_t cy)
{
    buffer_.resize(cx*cy);
    hor_size_ = cx;
    ver_size_ = cy;
}

std::vector<float>& ZBuffer::buffer()
{
    return buffer_;
}

const std::vector<float>& ZBuffer::buffer() const
{
    return buffer_;
}

std::size_t ZBuffer::hor_size() const
{
    return hor_size_;
}

std::size_t ZBuffer::ver_size() const
{
    return ver_size_;
}
