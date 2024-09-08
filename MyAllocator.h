#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include<stddef.h>
#include "MyCostruct.h"
namespace MySTL{
    template<class T>
    class MyAllocator
    {
        public:
            typedef T          value_type;
            typedef T*         value_pointer;
            typedef const T*   const_value_pointer;
            typedef T&         value_reference;
            typedef const T&   const_reference;
            typedef size_t     size_type;
        public:
            static T* MyAllocate();
            static T* MyAllocate(size_type size);
            static void MyDelAllocate(value_pointer ptr);
    };

    /**
     * @details 未指定大小的空间创建
     * @attention 调用全局void * operator new(size_t size);来开为对象开辟一段空间
     * @attention 由于返回值为 void* 故使用 static_cast<>();来做强制转化,不会有太大风险.
     * @attention 但如果是int*、char* 等非空类型指针转换请勿使用static_cast;可使用reinterpret_cast.
     */
    template<class T>
    T* MyAllocator<T>::MyAllocate(){
        return static_cast<T*>(operator new(sizeof(T)));
    }

    /** 
     * @details 给定大小的空间创建,如果size为0返回空指针
     * @param size 数据容量
    */
    template<class T>
    T* MyAllocator<T>::MyAllocate(size_type size){
        if(size == 0 ) return nullptr;
        return static_cast<T*>(operator new(size*sizeof(T)));
    }

    /**
     * @details 释放指针所指向地址内存
     * @param ptr 指针
     */
    template<class T>
    void MyAllocator<T>::MyDelAllocate(value_pointer ptr){
        if(ptr == nullptr) return;
        operator delete(ptr);
    }

}
#endif