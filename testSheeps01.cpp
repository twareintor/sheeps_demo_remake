
/********************************************************************************************************/

#include "testSheeps01.h"

int testSheeps01()
{
    std::cout<<"get some sheeps:"<<std::endl;
    Sheep* mySheep = new Sheep();
    Sheep* yourSheep = new Sheep();
    Sheep* hersSheep = new Sheep();
    std::cout<<std::endl;

    std::cout<<"let's count them:"<<std::endl;
    Flock myFlock(mySheep, yourSheep, hersSheep);
    std::cout<<"I have "<<myFlock.getSheepCount()<<" sheeps\n";
    std::cout<<"my flock looks like:\n";
    myFlock.printSheeps();
    std::cout<<std::endl;
   
    std::cout<<"let's modify ID's"<<std::endl;
    mySheep->changeId(1024);
    yourSheep->changeId(mySheep->getId());
    std::cout<<"now, my flock looks like:\n";
    myFlock.printSheeps();
    std::cout<<std::endl;
   
    std::cout<<"let's add some other sheeps:"<<std::endl;
    const Sheep& someSheep = Sheep();
    myFlock.addSheep(const_cast<Sheep*>(&someSheep));
    myFlock.addSheep(yourSheep); // add again a sheep already in
    std::cout<<"now, my flock looks like:\n";
    myFlock.printSheeps();
    std::cout<<std::endl;
    
    std::cout<<"let's remove some sheeps:"<<std::endl;
    myFlock.removeSheep(hersSheep);
    myFlock.removeSheep(const_cast<Sheep*>(&someSheep));
    myFlock.removeSheep(hersSheep); // remove a sheep already removed
    myFlock.printSheeps();
    std::cout<<std::endl;
    
    std::cout<<"delete sheeps and close the program"<<std::endl;
    delete hersSheep;
    delete yourSheep;
    delete mySheep;
    std::cout<<std::endl;
  
    std::cout<<"Game Over!"<<std::endl;
}




/********************************************************************************************************/

