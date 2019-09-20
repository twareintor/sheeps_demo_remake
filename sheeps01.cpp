/********************************************************************************************************/

#include "sheeps01.h"


int IdManager::m_id = 1000;


int Sheep::changeId(int newId)
{
    if(newId > m_idman->getCrtId())
    {
        m_id = newId;
        m_idman->getCrtId() = newId;
    }
    else
    {
        m_id = m_idman->getNextId();
    }
    return m_id; // 
}


void Flock::addSheep(Sheep* sheep)
{
    // the sheep must not already be part of this flock: check:
    for(int i=0; i<m_sheepCount; i++)
    {
        if(m_sheeps[i]==sheep)
        {
            std::cout<<"the sheep id = "<<sheep->getId()<<" is already here\n";
            return; // nothing performed
        }
    }
    // else, make room for a new sheep and add it to flock
    Sheep** tmpSheeps = m_sheeps;
    m_sheeps = new Sheep*[++m_sheepCount];
    for(int i = 0; i<m_sheepCount-1; i++)
    {
        m_sheeps[i] = tmpSheeps[i];
    }
    delete[] tmpSheeps;
    m_sheeps[m_sheepCount-1] = sheep;
}

void Flock::removeSheep(Sheep* sheep)
{
    // the sheep must be part of this flock: check:
    for(int i=0; i<m_sheepCount; i++)
    {
        if(m_sheeps[i]==sheep)
        {
            for(int j = i; j<m_sheepCount-1; j++) // move to left...
            {
                m_sheeps[j] = m_sheeps[j+1];
            }
            Sheep** tmpSheeps = m_sheeps;
            m_sheeps = new Sheep*[--m_sheepCount];
            for(int j = 0; j<m_sheepCount; j++)
            {
                m_sheeps[j] = tmpSheeps[j];
            }
            delete[] tmpSheeps;
            return; // everything is done at this point
        }
    }
    // nothing performed, if this sheep is not in this flock
    std::cout<<"the sheep id = "<<sheep->getId()<<" is not here\n";
}


void Flock::printSheeps()
{
    for(int i = 0; i<m_sheepCount; i++)
    {
        std::cout<<"Sheep #"<<i<<" has ID = "<<m_sheeps[i]->getId()<<std::endl;
    }
}


