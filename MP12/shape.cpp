#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape(string name) {
  name_ = name;
}

string Shape::getName(){return name_;}

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length):Shape("Rectangle") {
    length_ = length;
    width_ = width;
 }


double Rectangle::getWidth(){return width_;}

double Rectangle::getLength(){return length_;}

double Rectangle::getArea(){return (length_ * width_);}

double Rectangle::getVolume(){return 0;}

Rectangle Rectangle::operator + (const Rectangle& rhs){
  double newLength = length_ + rhs.length_;
  double newWidth = width_ + rhs.width_;
  return Rectangle(newWidth, newLength);}

Rectangle Rectangle::operator - (const Rectangle& rhs){
  double newLength = (0 > length_ - rhs.length_) ? 0 : (length_ - rhs.length_);  
  double newWidth = (0 > width_ - rhs.width_) ? 0 : (width_ - rhs.width_);
  return Rectangle(newWidth, newLength);}





//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle") {
    radius_ = radius;
 }

double Circle::getRadius(){return radius_;}

double Circle::getArea(){return (radius_ * radius_ * M_PI);}

double Circle::getVolume(){return 0;}

Circle Circle::operator + (const Circle& cir){  return Circle(radius_ + cir.radius_);}

Circle Circle::operator - (const Circle& cir){
  double newRadius = (0 > radius_ - cir.radius_) ? 0 : (radius_ - cir.radius_);  
  return Circle(newRadius);}


//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere") {
    radius_ = radius;
 }

double Sphere::getRadius(){return radius_;}

double Sphere::getArea(){return (4*radius_*radius_*M_PI);}

double Sphere::getVolume(){return ((4.0/3.0)*radius_*radius_*radius_*M_PI);}

Sphere Sphere::operator + (const Sphere& sph){  return Sphere(radius_ + sph.radius_);}

Sphere Sphere::operator - (const Sphere& sph){
  double newRadius = (0 > radius_ - sph.radius_) ? 0 : (radius_ - sph.radius_);  
  return Sphere(newRadius);}




//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") {
    width_ = width;
    length_ = length;
    height_ = height;
 }

double RectPrism::getArea(){return (2*(length_*width_ + length_*height_ + width_*height_));}

double RectPrism::getVolume(){return (length_*width_*height_);}

RectPrism RectPrism::operator + (const RectPrism& rp){
  double newLength = length_ + rp.length_;
  double newWidth = width_ + rp.width_;
  double newHeight = height_ + rp.height_;
  return RectPrism(newWidth, newLength, newHeight);}

RectPrism RectPrism::operator - (const RectPrism& rp){
  double newLength = (0 > length_ - rp.length_) ? 0 : (length_ - rp.length_);  
  double newWidth = (0 > width_ - rp.width_) ? 0 : (width_ - rp.width_);  
  double newHeight = (0 > height_ - rp.height_) ? 0 : (height_ - rp.height_);  
  return RectPrism(newWidth, newLength, newHeight);}


double RectPrism::getWidth(){return width_;}
double RectPrism::getHeight(){return height_;}
double RectPrism::getLength(){return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here

string name;
float a=0, b=0, c=0;
int end, cntr = 0;
vector<Shape*> MyVector;
ifstream ifs (file_name, std::ifstream::in);
ifs >> end;
Shape* shape_ptr;
  while(cntr < end)
  {
  ifs >> name; 
    if(name == "Circle") 
    {
      ifs >> a; 
      shape_ptr = new Circle(a);
    }
    else if(name == "Rectangle") 
    {
      ifs >> a >> b; 
      shape_ptr = new Rectangle(a, b);
    }
    else if(name == "Sphere") 
    {
      ifs >> a; 
      shape_ptr = new Sphere(a);
    }
    else if(name == "RectPrism") 
    {
      ifs >> a >> b >> c; 
      shape_ptr = new RectPrism(a, b, c);
    }
  MyVector.push_back(shape_ptr); 
  cntr++;
  }

ifs.close();
return MyVector; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
double curr_area;
vector<Shape*>::iterator iter;
    for(iter = shapes.begin(); iter != shapes.end(); iter++) {
      curr_area = (*iter)->getArea();
      if(curr_area > max_area)
        max_area = curr_area;
    }

return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
double curr_vol;
vector<Shape*>::iterator iter;
    for(iter = shapes.begin(); iter != shapes.end(); iter++) {
      curr_vol = (*iter)->getVolume();
      if(curr_vol > max_volume)
        max_volume = curr_vol;
    }
  return max_volume;
}

