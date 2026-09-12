#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

// Your implementation here
template <typename T>
class UniquePtr {
    public:
        // constructor
        UniquePtr(T *ptr = nullptr) 
        : m_ptr{ptr} {}

        // destructor
        ~UniquePtr() {
            if (m_ptr) {
                delete m_ptr;
            }
        }

        // copy constructor isn't allowed
        UniquePtr(const UniquePtr<T> &uniquePtr) = delete;

        // copy assignment isn't allowed
        UniquePtr<T> &operator=(const UniquePtr<T> &uniquePtr) = delete;

        // move constructor
        UniquePtr(UniquePtr<T> &&uniquePtr)
        : m_ptr{*uniquePtr} {
            
        }

        // move assignment
        UniquePtr<T> &operator=(UniquePtr<T> &&uniquePtr) {

        }

    private:
        T *m_ptr;
};

#endif
