
/******************************************************************************************************************/
#ifndef WORLD_H_INCLUDED_98123754812348912398471
#define WORLD_H_INCLUDED_98123754812348912398471

/**
 * A (singleton) world to provide and to manage ID-s and other things like creating/ destorying assets 
 *  (objects: things, animals and other creatures, abstract objecst or program specifics)
 * 
 */
class CWorld
{
    static CWorld* m_instance;
    CWorld(){}
public:
    CWorld(const CWorld&) = delete;
    CWorld& operator=(const CWorld& other) = delete;
    
};


#endif

/******************************************************************************************************************/

