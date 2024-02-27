#pragma once

template <class T>
class CE_Singleton  //MT Safe!
{
private:

    static_assert(std::is_class_v<T>, "Only class or struct is supported!");

protected:

    CE_Singleton() = default;
    virtual ~CE_Singleton() = default;

    CE_Singleton(const CE_Singleton&) = delete;
    CE_Singleton& operator=(const CE_Singleton&) = delete;

    CE_Singleton(const CE_Singleton&&) = delete;
    CE_Singleton& operator=(const CE_Singleton&&) = delete;

public:

    static T* GetInstance()
    {
        static T instance;
        return &instance;
    }
};