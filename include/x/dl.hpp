#pragma once

#include <string>

#if defined(_WIN32)
    #include <Windows.h>
#endif

namespace x {

class Library {
public:
    Library() = default;
    explicit Library(const std::string& name);
    ~Library();

    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

    Library(Library&& other) noexcept;
    Library& operator=(Library&& other) noexcept;

    void open(const std::string& name);
    void close();
    void* load(const std::string& functionName) const;

    explicit operator bool() const noexcept;

    friend void swap(Library& lhs, Library& rhs) noexcept;

private:
#if defined(_WIN32)
    HINSTANCE _library = nullptr;
#elif defined(__linux__)
    void* _handle = nullptr;
#endif
};

} // namespace x
