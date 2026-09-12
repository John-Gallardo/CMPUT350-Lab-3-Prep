#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// Your implementation here
template <typename T>
class UniquePtr {
    public:
        UniquePtr(T *ptr = nullptr) 
        : m_ptr{ptr} {}

    private:
        T *m_ptr;
};

#endif
