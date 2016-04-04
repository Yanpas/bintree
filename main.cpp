#include <iostream>
#include <vector>
#include "bintree.hpp"

using namespace std;

int main()
{
	//BinTree oak {5,4,5,7,8,56,0,23};
	BinTree kek {90,50,150,20,75,95,175,5,25,66,80,92,111,166,200};

	//BinTree newoak(oak.search(4));
	kek.print();
//	BinTree kek2 (kek);
//	kek2.print();
//	std::cout << std::boolalpha;
//	std::vector <BinTree> T { {5,3,8,7,9,10}, {5}, {5,8}, {4,3,2,1,0}, {0,1,2,3,4} };
//	for (auto t:T)
//	{
//		std::cout
//		<< "maxd: " << t.maxdepth() 
//		<< " mind: " << t.mindepth() 
//		<< " isBalanced " << t.isBalanced()
//		<< std::endl;
//	}
//	int delar[]={50,150,20,75,95,175,5,25,66,80,92,111,166,200};
//	int delar[]={95,175,5,25,66,80,92,111,166,200};
//	kek.delnode(90);
	kek.rotate(90,Direction::right);
	kek.print();
//	for (auto n:delar)
//	{
//		std::cout << "del\t" << n << std::endl;
//		kek.delnode(n);
//		kek.print();
//		std::cout << "newsize: " << kek.size() << std::endl << std::endl;
//	}
//	kek.print();
	std::cout << std::boolalpha << kek.isBST();
//	std::cout << getroot(kek);
	return 0;
}

