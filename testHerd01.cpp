#include "testHerd01.h"


int testHerd01()
{
	// Animals:
	CAnimal mySheep{"Dolly"}, myGoat{"Vixi"}, myDonkey{"Kahr"}, myDog{"Barki"}, 
	            yourSheep{"Molly"}, yourGoat{"Tixi"}, hersGoat{"Kuki"};
	
	// list the animals we already have:
	CAnimal* animals[]
		{&mySheep, &myGoat, &myDonkey, &myDog, &yourSheep, &yourGoat, &hersGoat,};
	for(auto it = std::begin(animals); it!=std::end(animals); ++it)
		std::cout<<(*it)->getName()<<"\t"<<(*it)->getId()<<std::endl; //for debug only
	std::cout<<std::endl;
	
	std::cout<<"// let some of them flock together in my herd:\n";
	auto myHerd = mySheep + myGoat + myDonkey;
	myHerd.listAnimals(); std::cout<<std::endl;
	
	std::cout<<"// let's define your herd:\n";
	auto yourHerd = yourSheep + yourGoat;
	yourHerd.listAnimals(); std::cout<<std::endl;
	
	std::cout<<"// let's add two herds:\n";
	auto ourHerd = myHerd + yourHerd;
	ourHerd.listAnimals();	std::cout<<std::endl;
	
	std::cout<<"// let's add an animal to our herd:\n";
	ourHerd+=hersGoat;
	ourHerd.listAnimals(); std::cout<<std::endl;
	
	std::cout<<"// let's try to add an animal alreay in the herd:\n";
	ourHerd+=yourSheep; // already in!
	ourHerd.listAnimals();	std::cout<<std::endl;
	
	std::cout<<"// let's remove an animal from the herd:\n";
	ourHerd-=yourSheep;
	ourHerd.listAnimals();	std::cout<<std::endl;
	
	std::cout<<"// let's try to remove an animal not in the herd:\n";
	ourHerd-=myDog;
	ourHerd.listAnimals();	std::cout<<std::endl;
	
	std::cout<<"// let's separate the herds again:\n";
	myHerd = ourHerd - yourHerd;
	myHerd.listAnimals();	std::cout<<std::endl;
	
	std::cout<<"// let's add in a herd an animal from another herd:\n";
	yourHerd+=mySheep;
	myHerd+=yourHerd;
	myHerd.listAnimals();
	std::cout<<"// see you? Dolly is two times in my herd!\n";
	
	std::cout<<"Everything: game over\n";
	std::cout<<"Game Over!\n";
	return 0;
}

