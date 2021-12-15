#include"dcel_header.h"
half_edge::half_edge(int i,vertex* o) // constructor
{
	index = i;
	origin = o;
}
//Get set functions
void half_edge::set_index(int i){index = i;}
int half_edge::get_index(){return index;}
void half_edge::set_vtx(vertex *v){origin = v;}
vertex* half_edge::get_vtx(){return origin;}
void half_edge::set_ne(half_edge* e){next_edge = e;}
half_edge* half_edge::get_ne(){return next_edge;}
void half_edge::set_pe(half_edge* e){prev_edge = e;}
half_edge* half_edge::get_pe(){return prev_edge;}
void half_edge::set_tn(half_edge* e){twin = e;}
half_edge* half_edge::get_tn(){return twin;}
void half_edge::set_f(face* f){incident_face = f;}
face* half_edge::get_f(){return incident_face;}