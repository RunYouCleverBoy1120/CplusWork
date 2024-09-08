#ifndef MYSTL_CONSTRUCT_H
#define MYSTL_CONSTRUCT_H
#include<type_traits>
#include<iostream>

namespace MySTL{

    template<class T>
    void destroy_one(T* ptr,std::true_type){
        return;
    }

    template<class T>
    void destroy_one(T* ptr,std::false_type){
        ptr->~T();
    }

    template<class T>
    void destroy_cat(T* ptr_first,T* ptr_last,std::true_type){return;}

    /**通过std::is_trivially_destructible<T>{}判断是否为基础类或有隐式析构函数,如果是，则doNothing;反之调用对象析构函数 */
    template<class T>
    void destroy(T* ptr){
        destroy_one(ptr,std::is_trivially_destructible<T>{});
    }

    template<class T>
    void destroy_cat(T* ptr_first,T* ptr_last, std::false_type){
        for(;ptr_first!=ptr_last; ++ptr_first){
            destroy(ptr_first);
        }
    }

    template<class T>
    void destroy(T* ptr_first,T* ptr_last){
        destroy_cat(ptr_first,ptr_last,std::is_trivially_destructible<T>{});
    }

    template<class T>
    void construct_one(T* ptr){
        new (ptr)T();
    }

    template<class T>
    void construct_one(T* ptr,const T& ref){
        new (ptr)T(ref);
    }

    template<class T>
    void construct(T* ptr){
        construct_one(ptr);
    }

    template<class T>
    void construct(T* ptr,const T& ref){
        construct_one(ptr,ref);
    }

    template<class T>
    void construct_cat(T* ptr_first,T*ptr_last){
        for(;ptr_first!=ptr_last; ++ptr_first){
            construct(ptr_first);
        }
    }

    template<class T>
    void construct_cat(T* ptr_first,T*ptr_last,const T& ref){
        for(;ptr_first!=ptr_last; ++ptr_first){
            construct(ptr_first,ref);
        }
    }

    template<class T>
    void construct(T* ptr_first,T*ptr_last){
        construct_cat(ptr_first,ptr_last);
    }

    template<class T>
    void construct(T* ptr_first,T*ptr_last,const T& ref){
        construct_cat(ptr_first,ptr_last,ref);
    }

    template<class T>
    void copy_cat(T* ptr_first,T*ptr_last,T*first){
        for(;ptr_first!=ptr_last;++ptr_first,++first)
        construct(first,*ptr_first);
    }

    template<class T>
    void copy(T* ptr_first,T*ptr_last,T*first){
        copy_cat(ptr_first,ptr_last,first);
    }
}

#endif