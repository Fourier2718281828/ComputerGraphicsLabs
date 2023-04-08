#ifndef ZBUFFER_H
#define ZBUFFER_H
#include <vector>

class ZBuffer
{
public:
    static ZBuffer& getInstance();
    void clear();
    void init(std::size_t cx, std::size_t cy);
    std::vector<float>& buffer();
    const std::vector<float>& buffer() const;
    std::size_t hor_size() const;
    std::size_t ver_size() const;
private:
    ZBuffer() {}
    ZBuffer(const ZBuffer&);
    ZBuffer& operator=(const ZBuffer&);
private:
    std::vector<float> buffer_;
    std::size_t hor_size_;
    std::size_t ver_size_;
};


#endif // ZBUFFER_H
