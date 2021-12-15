#include"dcel_header.h"
face::face(int i) //constructor
{
	index = i;
	next_face = NULL;
}
//get and set functions
void face::set_index(int i){index = i;}
int face::get_index(){return index;}
void face::set_ie(half_edge* e){incident_edge = e;}
half_edge* face::get_ie(){return incident_edge;}
void face::set_nf(face* f){next_face = f;}
face* face::get_nf(){return next_face;}