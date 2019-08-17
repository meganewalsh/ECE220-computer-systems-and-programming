#include<fstream>
#include <iomanip>    
#include "shape.hpp"



int main(int argc, char *argv[]){
	if(argc != 2) {
    	cerr << "USAGE: ./mp12 input.txt" << endl; 
    	return -1;
  	}
	vector<Shape*> shape_ptrs = CreateShapes(argv[1]);

 // vector<Shape*>::iterator iter;
 // for (iter = shape_ptrs.begin();
   //    iter != shape_ptrs.end(); ++iter)
   // std::cout << *iter->getName();

	cout << "max area = " << MaxArea(shape_ptrs) << endl;	
  	cout << "max volume = " << MaxVolume(shape_ptrs) << endl;
	return 0;
}
