#include <x/dl.hpp>

#include <x/error.hpp>

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

    _library = LoadLibraryA(path.c_str());
    if (_library == NULL) {
        throw x::Error{std::to_string(GetLastError())};
    }
}

void Library::close()
{
    if (*this) {
        auto result = FreeLibrary(_library);
        _library = NULL;
        if (!result) {
            throw x::Error{std::to_string(GetLastError())};
        }
    }
}

void* Library::load(const std::string& functionName) const
{
    if (!*this) {
        throw x::Error{"Library: cannot load function, library is not open"};
    }

    auto ptr = GetProcAddress(_library, functionName.c_str());
    if (!ptr) {
        throw x::Error{std::to_string(GetLastError())};
    }

    return ptr;
}

Library::operator bool() const noexcept
{
    return _library != nullptr;
}

void swap(Library& lhs, Library& rhs) noexcept
{
    std::swap(lhs._library, rhs._library);
}

} // namespace x