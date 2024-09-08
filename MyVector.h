#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "MyAllocator.h"
#include<stddef.h>
namespace MySTL{

    template<class T>
    class MyVector
    {
        public:
            typedef MySTL::MyAllocator<T>  data_allocator;
            typedef typename MySTL::MyAllocator<T>::size_type  size_type;
            typedef typename MySTL::MyAllocator<T>::value_type value_type;
            typedef typename MySTL::MyAllocator<T>::const_reference const_reference;
        public:
            //构造和析构函数
            MyVector() noexcept; 
            MyVector(size_type n) noexcept;
            MyVector(size_type n,const_reference ref) noexcept;
            MyVector(const MyVector& rhs) noexcept;
            ~MyVector(); 

            //迭代器相关操作

            //容量相关操作
            size_type size() const noexcept{return static_cast<size_type>(end_ - begin_);}
            T* begin() const noexcept{return begin_;}
            T* end() const noexcept{return end_;}
        private:
            T* begin_;  // 表示目前使用空间的头部
            T* end_;  // 表示目前使用空间的尾部
            T* capicity_; //表示目前申请空间的尾部
    };

    /**MyVector构造函数,不处理异常,若不指定大小,默认空间大小为16*sizeof(T),数据容量为16 */
    template<class T>
    MyVector<T>::MyVector() noexcept{
        try{ begin_ = data_allocator::MyAllocate(16);
             end_ = begin_;
             capicity_ = begin_ + 16;
        }
        catch(...){ begin_ = nullptr; end_ = nullptr; capicity_ = nullptr;}
    }

    template<class T>
    MyVector<T>::MyVector(size_type n) noexcept{
        try{ begin_ = data_allocator::MyAllocate(n);
             end_ = begin_ + n;
             capicity_ = begin_ + n;
             MySTL::construct(begin_,end_);
        }
        catch(...){ begin_ = nullptr; end_ = nullptr; capicity_ = nullptr;}
    }

    template<class T>
    MyVector<T>::MyVector(size_type n,const_reference ref) noexcept{
        try{ begin_ = data_allocator::MyAllocate(n);
             end_ = begin_ + n;
             capicity_ = begin_ + n;
             MySTL::construct(begin_,end_,ref);
        }
        catch(...){ begin_ = nullptr; end_ = nullptr; capicity_ = nullptr;}
    }

    template<class T>
    MyVector<T>::MyVector(const MyVector& rhs) noexcept{
        try{ 
            size_type n = rhs.size();
            begin_ = data_allocator::MyAllocate(n);
            end_ = begin_ + n;
            capicity_ = begin_ + n;
            MySTL::copy(rhs.begin(),rhs.end(),begin_);
        }
        catch(...){ begin_ = nullptr; end_ = nullptr; capicity_ = nullptr;}
    }

    /**MyVector析构函数,释放内存,指针设为空nullptr;对象指针存储在堆空间中,若不析构容易导致内存泄漏 */
    template<class T>
    MyVector<T>::~MyVector(){
        MySTL::destroy(begin_,end_);//先调用对象析构函数,是否为基础类在内部判断
        data_allocator::DelAllocate(begin_);//释放内存
        begin_ = end_ = capicity_ = nullptr;
    }

}

#endif