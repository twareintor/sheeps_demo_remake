
/*******************************************************************************************\
*                                                                                           *
*            DEMO ANIMALS HERD: OPERATOR OVERLOADING OOP LEARNING AND TESTING               *
*                                                                                           *
\*******************************************************************************************/

/**
* Version = 000.A07// 19-08-16 16:00:00
* Author: Claudiu 'Twareintor' Ciutacu - copyright(c) 2019
* Comment: 
*/

#include <iostream>
#include <vector>

#include "world.h"

#include "idman.h"

#define USE_HERD_IN_HERD
// #undef USE_HERD_IN_HERD

/** global variable to control the Id of the assets: */
static int g_id = 0;

/** global variable to control the Id of the collections: */
static int g_fId = 0;


/** An asset: an animal, for example
*/
class CAnimal
{
	int m_id;
	std::string m_name;

public:
	/** ctors */
	CAnimal(): m_id(++g_id){}
	CAnimal(const char* szName): m_id(++g_id), m_name{szName}{}
	/** copy/ move ctors */
	CAnimal(const CAnimal& other) = default; // we need it to store animals in a vector
	CAnimal(CAnimal&& other) = default; // 
	/** copy/ move assignment operators */
	CAnimal& operator=(const CAnimal& other) = default;
	CAnimal& operator=(CAnimal&& other) = default;
	/** dtor */
	virtual ~CAnimal(){}
	/** get unique Id */
	int getId() const
	{
		return m_id;
	}
	/** get the name, if assigned */
	const std::string& getName() const
	{
		return m_name;
	}
	
	/** overloading two operators: check for the ID if is the same
	* remember: by copy (and the stl-containers does it!), the address
	* is lost and just comparing their addresses sets wrong results!!!
	*/
	bool operator==(const CAnimal& other) const
	{
		return this->m_id==other.getId();
	}
	/** overloading operators ==() and !=() */
	bool operator!=(const CAnimal& other) const
	{
		return this->m_id!=other.getId();
	}
};


/** a collection, a herd of animals, for example: */
class CHerd
{
	std::vector<CAnimal> m_animals; // the animals in this herd, except the ones in sub-herds (?)
	int m_id; // the ID of the whole herd: to can compare a herd with the other
#ifdef USE_HERD_IN_HERD
	std::vector<CHerd> m_subHerds; // ... and the things becomes more complicated...
#endif	
	// friend class CAnimal; // to access the private copy constructor and assignment operator
			// no need for it anymore: we need public copy constructor anyway
			
public:
	/** ctors */
	CHerd():m_id(++g_fId){}
	/** ctors */
	CHerd(const CHerd& other) = default;
	CHerd(CHerd&& other) = default;
	/** construct a herd from a single animal */
	CHerd(const CAnimal& ani):
	        m_id(++g_fId)
	{
		m_animals.push_back(ani);
	}
	/** construct a herd from many animals sent as arguments */
	template <class... Args> CHerd(Args const... args):
	    	m_id(++g_fId)
	{
		m_animals = std::vector<CAnimal>{args...};
	}
	/** copy/ move assignment operators */
	CHerd& operator=(const CHerd& other) = default;
	CHerd& operator=(CHerd&& other) = default;
	/** dtor */
	virtual ~CHerd(){}

	/** public members: adding an animal, if not already in this herd */
	void addAnimals(const CAnimal& ani)
	{
		for(auto&& it: m_animals)
		{
			if(it==ani)
			{
				std::cout<<ani.getId()<<" already here\n";
				return;
			}
		}
		m_animals.push_back(ani);
	}
	/** adding another herd to our herd */
	void addAnimals(const CHerd& other)
	{
#ifdef USE_HERD_IN_HERD
		m_subHerds.push_back(other);
#else		
		for(auto&& it: other.getAnimals())
		{
			addAnimals(it);
		}
#endif		
	}
	/** (Activate?) */
	/********
	template <class... Args>
	void addAnimals(Args const... args)
	{
		std::vector<CAnimal> animals{args...};
		for(auto&& it: animals)
			m_animals.push_back(it);
	} 
	********/
	/** removes a single animal, if is in this herd */
	void removeAnimals(const CAnimal& ani)
	{
		bool foundHere = false; // just for message
		std::vector<CAnimal> tmp;
		for(auto&& it: m_animals)
		{
			if(ani!=it)
			{
				tmp.push_back(it);
			}
			else
			{
				foundHere = true;
			}
		}
		m_animals=tmp;
		if(!foundHere) std::cout<<ani.getId()<<" not here\n";
	}
	/** removes an entire herd of animals, just those who are in this herd */
	void removeAnimals(const CHerd& other)
	{
#ifdef USE_HERD_IN_HERD
		bool foundHere = false; // just for message
		std::vector<CHerd> tmp;
		for(auto&& it: m_subHerds)
		{
			if(other!=it)
			{
				tmp.push_back(it);
			}
			else
			{
				foundHere = true;
			}
			m_subHerds = tmp;
			if(!foundHere) std::cout<<"Herd Id "<<other.getId()<<" not here\n";
		}
#else		
		for(auto&& it: other.getAnimals())
		{
			removeAnimals(it);
		}
#endif		
	}
	/** lookup function: get animal ID by name */
	int getIdOf(const char* szName) const
	{
		for(auto&& it: m_animals)
		{
			if(std::string(szName)==it.getName())
			{
				return it.getId();
			}
		}
	}
	/** lookup function: get animal name by ID */
	const std::string getNameOf(const int id) const
	{
		for(auto&& it: m_animals)
		{
			if(id==it.getId())
			{
				return it.getName();
			}
		}
	}
	//
	// overloading operators
	/** */
	void operator+=(const CHerd& other)
	{
		addAnimals(other);
	}
	/** */
	void operator-=(const CHerd& other)
	{
		removeAnimals(other);
	}
	/** */
	void operator+=(const CAnimal& ani)
	{
		addAnimals(ani);
	}
	/** */
	void operator-=(const CAnimal& ani)
	{
		removeAnimals(ani);
	}
	
	/** get all animals in this herd */
	const std::vector<CAnimal>& getAnimals() const
	{
		return m_animals;
	}
	
	/**  a special function to list the animals in the herd: */
	void listAnimals() const
	{
		std::cout<<"list animals on herd "<<m_id/*(void*)this*/<<"\n";
		int i = 1;
		for(auto it: m_animals)
		{
			std::cout<<"#"<<i++<<" = "<<"\t\""<<it.getName()<<"\"\t"<<it.getId()<<std::endl;			
		}
#ifdef USE_HERD_IN_HERD
		// recursively call the listAnimals() till to the last sub-herd:
		for(auto it: m_subHerds)
		{
			it.listAnimals();
		}
#endif			
	}
	/** get the id of the herd: in order to can compare them also after copying */
	int getId() const
	{
		return m_id;
	}
	/** overloading two operators: check for the ID if is the same
	* remember: by copy (and the stl-containers does it!), the address
	* is lost and just comparing their addresses sets wrong results!!!
	*/
	bool operator==(const CHerd& other) const
	{
		return this->m_id==other.getId(); 
	}
	/** overloading operators ==() and !=() */
	bool operator!=(const CHerd& other) const
	{
		return this->m_id!=other.getId();
	}
};

template <class T, class U> CHerd operator+(const T t, const U u)
{
	CHerd herd(t);
	herd.addAnimals(u);
	return herd;
}

template <class T, class U> CHerd operator-(const T t, const U u)
{
	CHerd herd(t);
	herd.removeAnimals(u);
	return herd;
}

