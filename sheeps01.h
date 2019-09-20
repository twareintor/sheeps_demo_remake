
/********************************************************************************************************/
//g++  5.4.0 [x]
//clang 3.8.0 [ ]
//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64 [ ]

#include <iostream>

// #include "idman.h"

class IdManager
{
    static int m_id;
public:
    int getNextId(){return ++m_id;}
    int& getCrtId() const{return m_id;}
};

/** an item having an uinque id */
class Sheep
{
    int m_id; // sheep Id (unique identifictor)
    IdManager* m_idman = nullptr; // to get an unique ID in the program
public:
    // ctors
    Sheep(): m_idman(new IdManager()){m_id = m_idman->getNextId();}
    // dtor
    ~Sheep(){if(m_idman) delete m_idman;}
    // members
    int getId(){return m_id;}
    int changeId(int newId);
};

/** a collection of these items: pointer version */
class Flock
{
    Sheep** m_sheeps;
    int m_sheepCount;
public:
    // ctors
    Flock() = delete;
    Flock(Flock&) = delete;
    // a special ctor with variadic argument
    template <class... Args>
    Flock(Args... args):
        m_sheepCount(sizeof...(Args)),
        m_sheeps(nullptr)
    {
        m_sheeps = new Sheep*[m_sheepCount];
        Sheep* sheeps[] = {args...,};
        for(int i = 0; i<m_sheepCount; i++)
        {
            m_sheeps[i] = sheeps[i];
        }
    }
    // dtor:
    ~Flock(){if(m_sheeps) delete[] m_sheeps;}
    // members:
    Sheep** getSheeps(){return m_sheeps;}
    int getSheepCount(){return m_sheepCount;}
    void addSheep(Sheep* sheep);

    void removeSheep(Sheep* sheep);

    void printSheeps();
    
};

/** a test function, formerly the main function in the phase of individual testings */
int testSheeps01();

/********************************************************************************************************/
