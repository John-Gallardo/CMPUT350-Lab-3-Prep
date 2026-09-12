#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <utility>

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
        : m_ptr{uniquePtr.get()} {
            uniquePtr.reset();
        }

        // move assignment
        UniquePtr<T> &operator=(UniquePtr<T> &&uniquePtr) {
            this->reset();
            m_ptr = uniquePtr.get();
            uniquePtr.reset();
        }

        // converting constructor
        template <typename U>
        UniquePtr(UniquePtr<U> &&uniquePtr)
        : m_ptr{uniquePtr.get()} {
            // NOTE: I am assuming we are resetting uniquePtr since it's an r-value
            uniquePtr.reset();
        }

        T& operator*() {
            return *m_ptr;
        }

        T* operator->() {
            return m_ptr;
        }

        T* get() {
            return m_ptr;
        }

        bool operator==(const UniquePtr<T> &other) const {
            return other.get() == m_ptr;
        }

        T* release() {
            // NOTE: I assume it's done by setting m_ptr to nullptr?
            T *temp{m_ptr};
            m_ptr = nullptr;
            return temp;
        }

        void reset(T* newPtr = nullptr) {
            delete m_ptr;
            m_ptr = newPtr;
        }

        void swap(UniquePtr<T> &other) {
            T *temp{other.release()};
            other.reset(m_ptr);
            m_ptr = temp;
        }

        operator bool() const {
            return m_ptr != nullptr;
        }

    private:
        T *m_ptr;
};

template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args) {
    // Reference: https://en.cppreference.com/cpp/memory/unique_ptr/make_unique
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

#endif
