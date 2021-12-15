#include"dcel_header.h"
vertex::vertex(int i,float x1,float y1) //constructor
{
	x = x1;
	y = y1;
	index = i;
}
//get and set functions
void vertex::set_index(int i){index = i;}
int vertex::get_index(){return index;}
void vertex::set_nv(vertex* v){next = v;}
vertex* vertex::get_nv(){return next;}
float vertex::get_x(){return x;}
float vertex::get_y(){return y;}
void vertex::set_x(float a){x = a;}