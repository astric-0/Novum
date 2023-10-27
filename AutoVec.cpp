#pragma once

template <typename T>
void Novum::AutoVec<T>::reserve(size_t n)
{
    if (_src == nullptr) 
    {
        _src = new T[n];
        _size = 0;
        _max = n;
    }
}

template <typename T>
void Novum::AutoVec<T>::add(const T& obj)
{
    if (_size >= _max)
    {
        size_t new_Max = _max + _max / 2;
        T* temp = new T[new_Max];
        for(size_t i = 0; i < _size; i++)        
            temp[i] = _src[i];
        _src = temp;
        _max = new_Max;
    }

    if (_decider)
    {
        size_t i = _size;
        for (;i >= 1; --i)
        {
            if (!_decider(obj, _src[i-1]))
                _src[i] = _src[i-1];
            else                
                break;            
        }

        _src[i] = obj; 
    } 
    else
        _src[_size] = obj;

    _size++;
}

template <typename T>
size_t Novum::AutoVec<T>::size() const { return _size; }

template <typename T>
size_t Novum::AutoVec<T>::max() const { return _max; }

template <typename T>
void Novum::AutoVec<T>::forEach(Novum::Typenames::VOID_LOOPER<T> looper)
{
    for(size_t index = 0; index < _size; index++)
        looper(_src[index], index);
}

template <typename T>
typename Novum::AutoVec<T>::Iterator Novum::AutoVec<T>::begin() const
{
    return AutoVec::Iterator(_src);
}

template <typename T>
typename Novum::AutoVec<T>::Iterator Novum::AutoVec<T>::end() const
{
    return AutoVec::Iterator(_src + _size);
}

template <typename T>
typename Novum::AutoVec<T>::Iterator Novum::AutoVec<T>::findIterator(Novum::Typenames::BOOL_LOOPER<T> looper)
{    
    size_t index = 0;
    for(AutoVec::Iterator it = this->begin(); it != this->end(); ++it, ++index)        
        if(looper(*it, index)) return it;    
    return nullptr;
}

template <typename T>
int64_t Novum::AutoVec<T>::findIndex(Novum::Typenames::BOOL_LOOPER<T> looper)
{
    for(size_t index = 0; index < _size; ++index)
        if (looper(_src[index], index)) return index;
    return -1;
}

template <typename T>
typename Novum::AutoVec<T> Novum::AutoVec<T>::filter(Novum::Typenames::BOOL_LOOPER<T> looper)
{
    Novum::AutoVec<T> filtered;
    filtered.reserve(_max);
    for(size_t index = 0; index < _size; index++)
        if(looper(_src[index], index)) filtered.add(_src[index]);
    return filtered;
}

template <typename T>
void Novum::AutoVec<T>::source(const AutoVec& obj)
{
    if (_src != nullptr) 
    {
        delete [] _src;
        _src = nullptr;    
    }

    this->reserve(obj._max);      
    for(size_t index = 0; index < obj._size; ++index)
        this->add(obj[index]);
}

template <typename T>
int64_t Novum::AutoVec<T>::searchIndex(const T& to_Search) const
{
    if (_decider)
    {
        size_t temp_Start = 0, temp_End = _size, temp_Mid;
        bool isAsec = _decider(1, 0);
        while (temp_Start <= temp_End)
        {
            temp_Mid = (temp_Start + temp_End) / 2;
            if (_src[temp_Mid] == to_Search)
            {
                return static_cast<int64_t>(temp_Mid);
            }

            else if (_src[temp_Mid] > to_Search) 
            {
                if (isAsec)
                    temp_End = temp_Mid - 1;
                else
                    temp_Start = temp_Mid + 1;
            }
            
            else 
            {
                if (isAsec)
                    temp_Start = temp_Mid + 1;
                else
                    temp_End = temp_Mid - 1;
            }
        }
    }
    return -1;
}

template <typename T>
template <typename U>
typename Novum::AutoVec<U> Novum::AutoVec<T>::map(std::function<U(T&, size_t)> mapper)
{
    AutoVec<U> temp_Store;
    temp_Store.reserve(_max);

    for(size_t index = 0; index < _size; ++index)    
        temp_Store.add(mapper(_src[index], index));

    return temp_Store;    
}
