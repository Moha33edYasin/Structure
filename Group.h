#include <iostream>
#include <concepts>

#ifndef GROUP_H // GROUP_H
#define GROUP_H

template <typename T>
concept is_deiminsion = requires(T nesteditem)
                                {
                                    nesteditem[0];
                                    nesteditem.size();
                                };
                          
using std::ostream, std::nothrow;

template <typename T1, typename T2>
class Point
{
private:
    T1 X;
    T2 Y;

public:
    Point()=default;
    Point(T1 first, T2 second) : X(first), Y(second)
    {

    }

    ~Point()=default;

    auto& operator[](short int i)
    {
        return (i)? Y:X;
    }
    friend bool operator==(Point& P1, Point& P2)
    {
        return P1[0] == P2[0] && P1[1] == P2[1];
    }
    friend ostream& operator<<(ostream& out, Point& P)
    {
        out << "(" << P.X << ", " << P.Y << ")";
        return out;
    }
};


template <typename T>
class Group
{
private:
/** 
    * @brief allcation for specfic heep block
    * @param instance - block data to replace
    * @param value - replace  value
    * value rendered to lvalue because it can interact with memory in the copies
    * of other function parameter after deconstructure it, specifly in (*Item) when delete
    * by nested function and outer onr try again it return (Unkown Signal Erorr)  
**/

Point<bool, int> allocate_release_memory(T& instance, T& value)
{
    int INDX(&instance - Items); // store Index to release
    T* HandleAddress = new(std::nothrow) T[End];
    auto Allaction_Success = Point<bool, int>(true, INDX);
    if(INDX < End)
    {
    if(INDX >= 0)
    {
        for(int i=0; i<INDX; i++)
            HandleAddress[i] = Items[i];
        for(int i=INDX+1; i<End; i++)
            HandleAddress[i] = Items[i];
        HandleAddress[INDX] = value; // allocte new value
        Items = HandleAddress; // allocate new field of memory
    }else
    {
        Allaction_Success = Point<bool, int>(false, -1);
    }
    }else
    {
        HandleAddress = new(std::nothrow) T[INDX + 1];
        for(int i=0; i<End; i++)
            HandleAddress[i] = Items[i];
        HandleAddress[INDX] = value;
        if(is_dynamic) End = INDX + 1;
        Items = HandleAddress; // allocate new field of memory
    }
    return Allaction_Success;
}

protected:
int End;
bool is_dynamic;

public:
T* Items;
// iterator object ..
class iterator
{
    public:
    int indx; Group& group;

    iterator(int _index, Group& _group) : indx(_index), group(_group)
    {

    }

    iterator(const iterator& source) : indx(source.indx), group(source.group)
    {

    }

    iterator operator++(int)
    {
        indx++;
        return *this;
    }

    iterator operator++()
    {
        indx++;
        return *this;
    }

    T& operator*()
    {
        return group[indx];
    }

    bool operator!=(iterator& other)
    {
        return indx != other.indx;
    }
};

friend ostream& operator<<(ostream& out, Group& collection)
{
    out << "[";
    for(int i=0; i<collection.End; i++)
    {
        
        if(i != collection.End-1)
            out << collection[i] << ", ";
        else
            out << collection[i];
    }
    out << "]";
    return out;
}

Group()
{
    End = 0; Items = new(std::nothrow) T[]{}; is_dynamic = true;
}

Group(T _item) : End(0), is_dynamic(true)
{
    append(_item);
}

Group(T* _items, size_t len) : End(len), is_dynamic(true)
{
    Items = _items;
}

Group(Group& source) : End(0), is_dynamic(source.is_dynamic)
{
    for(auto& item : source)
        ref_append(item);
}
virtual ~Group()
{
    if(Items != nullptr)
        delete[] Items; Items = nullptr;
}

/* 
@breif check the object is avilable in the Group object
@param element - the object to check
@param Container - the Group to search in
*/
bool friend operator%(T& element, Group& Container)
{
    int memory_location = (&element - &Container[0]);
    return (0 < memory_location && memory_location < Container.size());
}

virtual Group& operator+(Group& other)
{
    Group* result = new Group();
    for(int i=0; i<size(); i++)
    {
        result->ref_append(Items[i]);
    }
    for(int i=0; i<other.size(); i++)
    {
        result->ref_append(other[i]);
    }
    return *result;
}

void operator+=(int scalar)
{
    *this = *this + scalar;
}

virtual Group& operator*(int scalar)
{
    Group* result = new Group();
    for(int i=0; i<scalar; i++)
    {
        for(auto& item : *this)
            result->append(item);
    }
    return *result;
}

void operator*=(int scalar)
{
    *this = *this * scalar;
}

void operator=(T* Address)
{
    Items = Address;
}

// relative compare
bool operator==(const Group& other)const
{
    bool is_equal = size() == other.size();
    if(!is_equal) return false;
    for(int i=0; i<other.size(); i++)
        is_equal *= Items[i] == other.Items[i];
    return is_equal;
}

bool operator!=(const Group& other)const
{
    bool is_equal = size() != other.size();
    if(is_equal) return false;
    for(int i=0; i<other.size(); i++)
        is_equal *= Items[i] != other.Items[i];
    return is_equal;
}

// Getters
virtual T& operator[](int i)
{
    expend_to(i + 1);
    return Items[i];
}

virtual T& operator[](int i)const
{
    return Items[i];
}

int size()const
{
    return End;
}

iterator begin()
{
    return iterator(0, *this);
}

iterator end()
{
    return iterator(End, *this);
}

// Group items handlers
void pop()
{
    if(is_dynamic)
        End--;
}

void pop_start()
{
    if(is_dynamic)
    {
        Items++;
        End--;
    }
}
void changable(bool _)
{
    is_dynamic = _;
}
void append(T newitem)
{   
    allocate_release_memory(Items[End], newitem);
}

void ref_append(T& newitem)
{   
    allocate_release_memory(Items[End], newitem);
}

void insert(int _n, T itemToinsert)
{   
    _n = (_n + End) % End;
    for(int i=End; i>_n; i--)
    {
        allocate_release_memory(Items[i], Items[i-1]);            
    }
    allocate_release_memory(Items[_n], itemToinsert);        
}


void ref_insert(int _n, T& itemToinsert)
{   
    _n = (_n + End) % End;
    for(int i=End; i>_n; i--)
    {
        allocate_release_memory(Items[i], Items[i-1]);            
    }
    allocate_release_memory(Items[_n], itemToinsert);        
}

void remove_at(int indx)
{
    if(indx < End)
    {
        indx = (indx + End) % End;
        for(int j=indx; j<End-1; j++)
        {
            allocate_release_memory(Items[j], Items[j+1]);
        }
        pop();
    }
}

void remove(T itemTotrash)
{
    int i = find(itemTotrash);
    remove_at(i);
}

int ref_remove(T& itemTotrash)
{
    int i = find(itemTotrash);
    remove_at(i);
    return i;
}

void remove_all(T& itemTotrash)
{
    if(is_dynamic)
    {
        for(int i=0; i>End; i++)
        {
            if(Items[i] == itemTotrash)
            {
                for(int j=i; j<End-1; j++)
                    allocate_release_memory(Items[j], Items[j+1]);
                pop();
            }
        }
    }
}
/*
@breif if i > length() it will generate a new bigger Group to store (i) index 
*/
void expend_to(int __l)
{
    if(__l > End && is_dynamic)
    {
        T FillerBlock = T(); 
        for(int i=End; i<__l; i++)
            allocate_release_memory(Items[i], FillerBlock);
    }
}

/*
@breif find the item that same with
return -1 if item is not existed
*/ 
int find(T& itemTofind, int start = 0, int end = -1)const
{
    start = (start + End) % End;
    end = (end + End) % End;
    
    if (itemTofind % (*this))
        return (int) (&itemTofind - Items);
    for(int i=start; i<=end; i++)
    {   
        if(Items[i] == itemTofind)
            return (i);
    }
    return -1;
}

/*
@breif find closest item in a Group due to another in main Group
@param _from - refrence item to comapre with  
@param _set - Group of items to comapre its distance with the refrence item 
return -1 if all items is not existed
*/
int find_closest(T& _from, Group _set)const
{
    const int _fromIndex(&_from - Items);
    int offset_to = -1;
    int foundation;
    for(int i=0; i<_set.size(); i++)
    {   
        foundation = find(_set[i]);
        if (foundation != -1)
        {
            if(foundation - _fromIndex > offset_to || _fromIndex - foundation > offset_to)
                offset_to = foundation;
        }
    } 
    return offset_to;    
}
};
#endif // GROUP_H
