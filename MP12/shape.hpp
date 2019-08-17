#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<vector>
#include<fstream>
#include <iomanip>    

using namespace std;


class Shape{
public:
  	Shape(string name);
  	string getName();
  	virtual double getArea() = 0;
  	virtual double getVolume() = 0;
	
private:
  string name_;


};



class Rectangle : public Shape{
public:
  	Rectangle(double width = 0, double length = 0);
  	virtual double getArea();
  	virtual double getVolume();
	Rectangle operator + (const Rectangle& rec);
	Rectangle operator - (const Rectangle& rec);
	double getWidth();
	double getLength();
private:
	double width_;
  	double length_;

};


class Circle : public Shape{
public:
  	Circle(double radius);
  	virtual double getArea();
 	virtual double getVolume();
  	Circle operator + (const Circle& cir);
	Circle operator - (const Circle& cir);
	double getRadius();
private:
	double radius_;

};





class Sphere : public Shape{
public:
  	Sphere(double radius);
  	virtual double getVolume();
  	virtual double getArea();
	Sphere operator + (const Sphere& sph);
	Sphere operator - (const Sphere& sph);
	double getRadius();

private:
	double radius_;

};

class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height);
  	virtual double getVolume();
  	virtual double getArea();
	RectPrism operator + (const RectPrism& rectp);
	RectPrism operator - (const RectPrism& rectp);
	double getWidth();
	double getLength();
	double getHeight();
private:
  	double length_;
  	double width_;
  	double height_;



};

vector<Shape*> CreateShapes(char* file_name);
double MaxArea(vector<Shape*> shapes);
double MaxVolume(vector<Shape*> shapes);

#endif

