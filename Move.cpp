#include <iostream>

class String
{
private:
    unsigned size_;
    unsigned capacity_;
    char* data_;
public:
    String();//стандартный конструктро
    String(const char* str);//увелечинеие строки
    String(const String& other);//
    String(String&& other);//чистим память
    String& operator=(const String& other);
    String& operator=(String&& other);
    String& operator+=(const String& other);
    char& operator[](int i);
    const char& operator[](int i) const;
    ~String();
};
//стандартный конструктор
String::String() : size_(0), capacity_(0), data_(nullptr) {};

String::String(const char* str) 
{
    size_ = 0;
    while (str[size_] != 0)//подсчет размера оригинала (пока не дойдем до конца строки)
    {
        ++size_;//увеличиваем значением (отвечает за размер)
    }

    if (size_ == 0)//если размер равен нулю
    {
        data_ = nullptr;//приводим к nullptr наш объект
        capacity_ = 0;//приводим дополнительную память тоже к 0
        return;//выходим из программы
    }

    //Создаём строку
    data_ = new char[size_];//выделяем заново память с учётом новой ячейки
    capacity_ = size_;//выделяем дополнительную память строки равную размеру

    for (int i = 0; i < size_; i++)
    {
        data_[i] = str[i];//ложим все значения из указателя (копии и новый символ) в оригинальную строку
    }
};
String::String(const String& other): size_(other.size_), capacity_(other.capacity_), data_(new char[capacity_]) 
{
   
    for (int i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];//запись из копии тела в оригинал
    }
};
String::String(String&& other) : size_(other.size_), capacity_(other.capacity_), data_(other.data_)
{
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}
String& String::operator=(const String& other)
{
    delete[] data_;//чистим оригинальную строку
    size_ = other.size_;//к оригинальному размеру присваиваем копию размера
    capacity_ = other.capacity_;//к ориг.памяти присваиваем копию
    data_ = new char[other.capacity_];//для даты выделяем память размером доп.памяти
    
    for (int i = 0; i < size_; i++)
    {
        data_[i] = other.data_[i];//копии приравниваем к оригиналам
    }
    return *this;
}
String& String::operator=(String&& other) //переносим и чистим
{
    delete[] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;

    return *this;
}
String& String::operator+=(const String& other)
{
    if (size_ + other.size_ > capacity_)//если в сумме ориг.копия размера больше дополнительной памяти
    {
        capacity_ = size_ + other.size_;//увеличиваем память
        char* new_data = new char[capacity_];//создаём char указатель с размером дополнительной памяти
        for (int i = 0; i < size_; i++)
        {
            new_data[i] = data_[i];//указатель новый ложим все ячейки строки
        }

        delete[] data_;//чистим строку

        data_ = new_data;//новую строку запихиваем в старую чистую
    }
    for (int i = 0; i < size_; i++)
    {
        data_[size_ + i] = other.data_[i];//добавляем новое значения в конец строки
    }
    size_ += other.size_;//увеличиваем размер строки

    return *this;//выход
}
char& String::operator[](int i)
{
    return data_[i];//показ индекса
};
const char& String::operator[](int i) const 
{
    return data_[i];//показ индекса
};

String operator+(const String& first, const String& second)
{
    return String(first) += second;//пибавляем строку к строке
}



String::~String()//деструктор
{
    delete[] data_;
}
int main()
{
    std::cout << "Hello World!\n";
}