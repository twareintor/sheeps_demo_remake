//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64
//SheepID problem set ID by assignment operator return by reference, solved (in dev.)
//Code by Twareintor (2018)

/*************************************************************************************************************/

#include <iostream>

// #define DEBUG_UID_ATTR

// member variable of (taken) unique id-s: a stream of bits, when the id is taken, 
static unsigned char g_ids[0x400] = {0};

namespace 
{
    /** a bitwise and checks if the id (position id in a set of 0x400*8) is 1 */
bool isTaken(int id)
{
    return g_ids[id/8]&(1<<(id%8));
}

/** function returning the lowest ID not yet given or released; 
 * starting with zero and increments while the current bit is taken, then returns the pos
 * WARNING! if everything is taken (all bits in array are set) the program stops responding!
 */
int getSmallestFreeId(const int i0 = 0)
{
    int i = i0;
    while(isTaken(i)) i++;
    return i;
}
    
/** function sets the id-th bit in the array of bits IDs:
 * if is not taken (its position in the list of bits is 0), set it to 1 and return
 *the same value, if is, sets the smallest free id 
 */

int setUniqueId(int id)
{
    if(isTaken(id))
    {
        id = getSmallestFreeId();
    }
    g_ids[id/8]|=(1<<(id%8));
    return id;
}

/** function unsets the id-th bit in the array of bits IDs:
 * if already unset, remains unset (no check before) then returns the same input
 */
int releaseUniqueId(int id)
{
    g_ids[id/8]&=~(1<<(id%8)); // to be tested!!!!!
    return id;
}
    
}// ~namespace

/** 
 * Id-class: an object containing nothing more than an integral-type value as member
 * wiht overloaded assignment operator in order to can be accessed in an intuitive way
 */
class CId
{
    int m_val;
public:
    /** conversion Ctor */
    CId(int val):m_val(setUniqueId(val)){}
    /** */
    CId& operator=(const CId&) = default;
    /** Dtor: if the id is destructed, its value is released for further uses */
    ~CId(){releaseUniqueId(m_val);}
    /** overloading =(int): attribs integral value ID to val */
    void operator=(int val)
    {
        releaseUniqueId(this->m_val); // release the current value, then...
        m_val = setUniqueId(val); // set a new one in the ID-register and assign it
    }
    /** overloading <<(ostream&, CId&): to can be printed */
    friend std::ostream& operator<<(std::ostream& out, const CId& id)
    {
        out<<id.m_val;
        return out;
    }
    /** overloading other operators: */
    bool operator==(const CId& other){return this->m_val==other.m_val;}
    
};

namespace idtest
{

/** 
 * A class defining an object (asset) with unique ID to can be included in a collection
 */
class CAnimal
{
    CId m_id;
public:
    /** */
    CAnimal():m_id(CId(getSmallestFreeId())){}
    /** 
     * returning a reference to the ID-member, no setId() and getId() 
     * but direct set/ reset
     */
    CId& id(){return m_id;}
};


/**
 *
 */

int testAttribId();

}// idtest

/*************************************************************************************************************/


