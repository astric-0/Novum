#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include "Deciders.hpp"
#include "Typenames.hpp"

namespace Novum
{
    
template <typename T>
class AutoVec 
{
private:
    T* _src;
    size_t _size, _max;
    Novum::Typenames::DECIDER<T> _decider;

public:
    AutoVec(): _src(nullptr), _size(0), _max(0), _decider(Novum::Deciders::GET_ASEC<T>())
    {}

    AutoVec(Novum::Typenames::DECIDER<T> decider):  _src(nullptr), _size(0), _max(0), _decider(decider)
    {}

    AutoVec(AutoVec& obj): _src(new T[obj._max]), _size(obj._size), _max(obj._max), _decider(obj._decider)
    {
        for(size_t index = 0; index < _size; index++)
            _src[index] = obj._src[index];
    }

    class Iterator 
    {
    private:
        T* _ptr;        
    public:
        Iterator(): _ptr(nullptr)
        {}

        Iterator(T* ptr): _ptr(ptr) 
        {}

        bool isNull() { return _ptr == nullptr; }

        Iterator& operator=(const Iterator& it) { _ptr = it._ptr; return *this; }

        Iterator& operator++() { ++_ptr; return *this; }

        Iterator& operator--() { --_ptr; return *this; }

        bool operator==(const Iterator& it) const { return _ptr == it._ptr; }

        bool operator!=(const Iterator& it) const { return _ptr != it._ptr; }

        T& operator* () const { return *_ptr; }
    };

    void reserve (size_t);

    void add (const T&);

    size_t size() const;

    size_t max() const;

    void forEach(Novum::Typenames::VOID_LOOPER<T>);

    Iterator findIterator(Novum::Typenames::BOOL_LOOPER<T>);

    int64_t findIndex(Novum::Typenames::BOOL_LOOPER<T>);
    
    AutoVec filter(Novum::Typenames::BOOL_LOOPER<T>);

    void source (const AutoVec& obj);    

    Iterator begin() const;

    Iterator end() const;

    int64_t searchIndex(const T&) const;

    template <typename U>
    AutoVec<U> map(std::function<U(T&, size_t)>);

    T& operator[](size_t index) const { return *(_src + index); }

    AutoVec& operator=(const AutoVec& obj)
    {
        if (_src != nullptr) 
        {
            delete [] _src;
            _src = nullptr;    
        }

        this->reserve(obj._max); 
        _decider = obj._decider;
        _size = obj._size;
        for(size_t index = 0; index < _size; index++)
            _src[index] = obj._src[index];
        
        return *this;
    }
    
    ~AutoVec()
    {
        delete[] _src;
    }
};

}
#include "./AutoVec.cpp"