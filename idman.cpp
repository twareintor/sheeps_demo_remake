
#include "idman.h"



int idtest::testAttribId()
{
#ifdef DEBUG_UID_ATTR    
    for(int i = 0; i<0x400; i++)
    {
        g_ids[i/8]|=(1<<(i%8));
        std::cout<<i<<"\t"<<&g_ids[i/8]<<"\t"<<(short)g_ids[i/8]<<"\t"<<i%8<<std::endl;
    }
#else    
  
    CAnimal myDog, myCat, myPig, myDuck, myHen, myRabbit, myCow, myMouse, myAnotherDog;
    std::cout<<"my pig ID (auto set) is: "<<myPig.id()<<std::endl;
    CAnimal& pig = myPig;
    pig.id() = 12; std::cout<<"set 12, is: "<<pig.id()<<std::endl;
    CAnimal goat;
    {
        CAnimal yourPig, yourDog, yourDuck, yourHorse, yourElephant, yourWhale;
        goat.id() = 11;  std::cout<<"set 11, is: "<<goat.id()<<std::endl;
    }
    goat.id() = 11;  std::cout<<"set 11, is: "<<goat.id()<<std::endl;
    CId qid = goat.id(); std::cout<<"copied "<<goat.id()<<", is: "<<qid<<std::endl;
#endif
    std::cout << "Hello, world!\n";
}

/*************************************************************************************************************/


