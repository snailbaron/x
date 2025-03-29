#include <x/dl.hpp>

#include <x/error.hpp>

#if defined(__linux__)
    #include <dlfcn.h>
#endif

namespace x {

Library::Library(const std::string& path)
{
    open(path);
}

Library::~Library()
{
    try {
        close();
    } catch(...) { }
}

Library::Library(Library&& other) noexcept
{
    swap(*this, other);
}

Library& Library::operator=(Library&& other) noexcept
{
    if (this != &other) {
        close();
        swap(*this, other);
    }
    return *this;
}

void Library::open(const std::string& path)
{
    close();

#if defined(_WIN32)
    _library = LoadLibraryA(path.c_str());
    if (_library == NULL) {
        throw Error{std::to_string(GetLastError())};
    }
#elif defined(__linux__)
    _handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!_handle) {
        throw Error{"failed to open library"};
    }
#endif
}

void Library::close()
{
    if (*this) {
#if defined(_WIN32)
        auto result = FreeLibrary(_library);
        _library = NULL;
        if (!result) {
            throw Error{std::to_string(GetLastError())};
        }
#elif defined(__linux__)
        dlclose(_handle);
        _handle = nullptr;
#endif
    }
}

void* Library::load(const std::string& functionName) const
{
    if (!*this) {
        throw Error{"Library: cannot load function, library is not open"};
    }

#if defined(_WIN32)
    auto ptr = GetProcAddress(_library, functionName.c_str());
    if (!ptr) {
        throw Error{std::to_string(GetLastError())};
    }
#elif defined(__linux__)
    auto ptr = dlsym(_handle, functionName.c_str());
    if (!ptr) {
        throw Error{"failed to load symbol"};
    }
#endif

    return ptr;
}

Library::operator bool() const noexcept
{
#if defined(_WIN32)
    return _library != nullptr;
#elif defined(__linux__)
    return _handle != nullptr;
#endif
}

void swap(Library& lhs, Library& rhs) noexcept
{
#if defined(_WIN32)
    std::swap(lhs._library, rhs._library);
#elif defined(__linux__)
    std::swap(lhs._handle, rhs._handle);
#endif
}

} // namespace x
