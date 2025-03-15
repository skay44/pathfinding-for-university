#pragma once
#define _use_math_defines
#include <iostream>


//Vector
template<typename Type> class Vector {
    template<typename Type>
    friend std::ostream& operator<<(std::ostream& ostr, Vector<Type>& right);
    Type* arr;
    size_t capacity;
    size_t current;
public:
    void instantiateEmpty()
    {
        delete[] arr;
        arr = new Type[1];
        capacity = 1;
        current = 0;
    }

    Vector()
    {
        arr = nullptr;
        instantiateEmpty();
    }

    Vector(const Vector& next)
    {
        capacity = next.capacity;
        current = next.current;
        arr = new Type[capacity];
        for (size_t i = 0; i < current; i++)
        {
            arr[i] = next.arr[i];
        }
    }

    Vector(Vector&& next)
    {
        capacity = next.capacity;
        current = next.current;
        arr = next.arr;
        next.instantiateEmpty();
    }

    Vector& operator=(const Vector& right)
    {
        capacity = right.capacity;
        current = right.current;
        arr = new Type[capacity];
        for (size_t i = 0; i < current; i++)
        {
            arr[i] = right.arr[i];
        }
        return *this;
    }

    Vector& operator==(Vector&& right)
    {
        capacity = right.capacity;
        current = right.current;
        arr = right.arr;
        right.instantiateEmpty();

        return *this;
    }

    ~Vector()
    {
        if (arr != nullptr)
            delete[] arr;
    }

    size_t size() const
    {
        return current;
    }

    void info() const
    {
        std::cout << "<" << current << "/" << capacity << ">";
    }

    void push(Type data)
    {
        if (current == capacity)
        {

            Type* temp = new Type[2 * capacity];

            for (size_t i = 0; i < current; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;
            capacity *= 2;
            arr = temp;
        }

        arr[current] = data;
        current++;
    }

    Type pop()
    {
        Type tmp;
        if (current > 0)
        {
            tmp = arr[current - 1];
            /*
            if (current <= (capacity / 2))
            {
                Type* temp = new Type[capacity / 2];

                for (int i = 0; i < current; i++)
                {
                    temp[i] = arr[i];
                }

                delete[] arr;
                capacity /= 2;
                arr = temp;
            }*/
            current--;
        }
        else
        {
            Type *tmp2 = new Type();
            tmp = *tmp2;
            delete tmp2;
        }
        return tmp;
    }

    void clear()
    {
        while (current > 0)
            pop();
    }

    Type& operator[](size_t index)
    {
        return arr[index];
    }

    Type& operator[](size_t index) const
    {
        return arr[index];
    }

    /*
void push(std::initializer_list<Type> data)
{
        if (current + data.size() > capacity)
        {
                int multiplier = 2;
                while (current + data.size() > capacity * multiplier)
                {
                        multiplier *= 2;
                }

                Type* temp = new Type[multiplier * capacity];

                for (int i = 0; i < current; i++)
                {
                        temp[i] = arr[i];
                }

                delete[] arr;
                capacity *= multiplier;
                arr = temp;
        }

        for (Type instance : data)
        {
                arr[current] = instance;
                current++;
        }
}*/
};
template<typename Type>
std::ostream& operator<<(std::ostream& ostr, Vector<Type>& right)
{
    ostr << " {";
    for (int i = 0; i < right.current; i++)
    {
        ostr << right[i];
        if (i < right.current - 1) ostr << ",";
    }
    ostr << "<" << right.current << "/" << right.capacity << ">";
    ostr << "} ";
    return ostr;
}

//String
class StringS
{
    friend std::istream& operator>>(std::istream& istr, StringS& right);
    friend std::ostream& operator<<(std::ostream& ostr, StringS right);
    Vector<char> text;
public:
    StringS() {};

    StringS(const char* buffer)
    {
        int size = strlen(buffer);
        for (int i = 0; i < size; i++)
        {
            text.push(buffer[i]);
        }
    };

    StringS(StringS& right)
    {
        int size = right.text.size();
        for (int i = 0; i < size; i++)
        {
            text.push(right.text[i]);
        }
    }

    StringS(StringS&& right)
    {
        text = right.text;
        right.text.instantiateEmpty();
    }

    StringS& operator=(const char* buffer)
    {
        text.clear();
        int size = strlen(buffer);
        for (int i = 0; i < size; i++)
        {
            text.push(buffer[i]);
        }
        return *this;
    }

    StringS& operator=(StringS& right)
    {
        text.clear();
        int size = right.text.size();
        for (int i = 0; i < size; i++)
        {
            text.push(right.text[i]);
        }
        return *this;
    }

    StringS& operator=(StringS&& right)
    {
        text = right.text;
        right.text.instantiateEmpty();
        return *this;
    }

    bool operator==(const StringS& right) const//??????????????????? NIETESTOWANE
    {
        if (text.size() == right.text.size())
        {
            bool correct = true;
            for (size_t i = 0; i < text.size(); i++)
            {
                if (text[i] != right.text[i])
                    correct = false;
            }
            return correct;
        }
        return false;
    }

    char& operator[](const size_t index) const
    {
        return text[index];
    }

    char& operator[](const size_t index)
    {
        return text[index];
    }

    void append(const char buffer)
    {
        text.push(buffer);
    }

    void append(const char* buffer)
    {
        int size = strlen(buffer);
        for (int i = 0; i < size; i++)
        {
            text.push(buffer[i]);
        }
    }

    void append(StringS& right)
    {
        int size = right.text.size();
        for (int i = 0; i < size; i++)
        {
            text.push(right.text[i]);
        }
    }

    void appendLeft(const char* buffer)
    {
        StringS tmp;
        tmp.append(buffer);
        tmp.append(*this);
        *this = std::move(tmp);
    }

    void appendLeft(StringS& right)
    {
        StringS tmp;
        tmp.append(right);
        tmp.append(*this);
        *this = std::move(tmp);
    }

    StringS strPart(const int& start, const int& end)
    {
        StringS tmp;
        for (int i = start; i < start + end; i++)
        {
            tmp.text.push(text[i]);
        }
        //*this = std::move(tmp);
        return tmp;
    }

    size_t length() const
    {
        return text.size();
    }

    int toInt()
    {
        int number = 0;
        for (size_t i = 0; i < text.size(); i++)
        {
            if (text[i] >= 48 && text[i] <= 57)
                number += (text[i] - 48) * (int)pow(10, text.size() - i - 1);
        }
        return number;
    }

};
std::ostream& operator<<(std::ostream& ostr, StringS right)
{
    for (size_t i = 0; i < right.text.size(); i++)
    {
        ostr << right.text[i];
    }
    return ostr;
}
std::istream& operator>>(std::istream& istr, StringS& right)
{
    right.text.instantiateEmpty();
    char x;
    while (true)
    {
        if (istr.get(x))
        {
            right.text.push(x);
            if (x == '\n') break;
        }
        else
        {
            istr.setstate(std::ios::eofbit);
            break;
        }
    }
    return istr;
}



class SList
{
    struct Node
    {
        StringS data;
        int number;
        Node* next;
        Node* prev;
        Node(StringS& val, int nr)
        {
            data = val;
            number = nr;
            next = nullptr;
            prev = nullptr;
        }
    };
    Node* head;
    Node* tail;

public:

    SList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void PushFront(StringS& val, int nr)
    {
        Node* tmp = new Node(val, nr);
        if (head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            head->next = tmp;
            tmp->prev = head;
            head = tmp;
        }
    }

    void PushBack(StringS& val, int nr)
    {
        Node* tmp = new Node(val, nr);
        if (head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->prev = tmp;
            tmp->next = tail;
            tail = tmp;
        }
    }

    int FindNumberByValue(StringS& val) const
    {
        Node* tmp;
        tmp = tail;
        while (tmp != nullptr)
        {
            if (tmp->data == val)
            {
                return tmp->number;
            }
            tmp = tmp->next;
        }
        return -1;
    }

    int FindIndexByValue(StringS& val) const
    {
        Node* tmp;
        tmp = tail;
        int result = -1;
        int i = 0;
        while (tmp != nullptr)
        {
            if (tmp->data == val)
            {
                result = i;
                break;
            }
            tmp = tmp->next;
            i++;
        }
        return result;
    }

    bool GetValueByIndex(int index, StringS& val) const
    {
        Node* tmp;
        tmp = tail;
        if (tmp != nullptr)
        {
            for (int i = 0; i < index; i++)
            {
                if (tmp->next != nullptr)
                {
                    tmp = tmp->next;
                }
                else
                {
                    return false;
                }
            }
            val = tmp->data;
            return true;
        }
        else
        {
            return false;
        }
    }

    int Size() const
    {
        Node* tmp;
        tmp = tail;
        int i = 0;
        while (tmp != nullptr)
        {
            tmp = tmp->next;
            i++;
        }
        return i;
    }

    bool IsEmpty() const
    {
        if (tail != nullptr) return false;
        else return true;
    }

    void clear()
    {
        Node* tmp = nullptr;
        while (tail != nullptr)
        {
            tmp = tail;
            tail = tail->next;
            delete tmp;
        }
        head = nullptr;
    }

    void Print() const
    {
        Node* tmp;
        tmp = tail;
        std::cout << "{";
        while (tmp != nullptr)
        {
            std::cout << tmp->data << "," << tmp->number << ";";
            tmp = tmp->next;
        }
        std::cout << "}";
    }

    ~SList()
    {
        Node* tmp = nullptr;
        while (tail != nullptr)
        {
            tmp = tail;
            tail = tail->next;
            delete tmp;
        }
    }
};

//template<typename Type>
class SHash
{
public:
    size_t size;
    SList* list;
    int id;


    SHash(size_t s)
    {
        list = new SList[s];
        size = s;
        id = 0;
    }

    void AddToList(size_t nr, StringS& data)
    {
        list[nr].PushFront(data, id);
        id++;
    }

    void toHash(StringS& data)
    {
        unsigned long long r = 0;
        int max;
        int l = data.length();
        l < 8 ? max = l : max = 8;
        for (int i = 0; i < max; i++)
        {
            r += (long long)data[i] * (i + 9397);
            r %= (size);
        }
        AddToList((size_t)r, data);
    }

    int FindIndexByName(StringS& data)
    {
        unsigned long long r = 0;
        int max;
        int l = data.length();
        l < 8 ? max = l : max = 8;
        for (int i = 0; i < max; i++)
        {
            r += (long long)data[i] * (i + 9397);//3119 //9397 liczby pierwsze
            r %= (size);
        }
        return list[r].FindNumberByValue(data);
    }

};