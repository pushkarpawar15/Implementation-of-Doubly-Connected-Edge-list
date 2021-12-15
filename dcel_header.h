//header file containing declarations
#include<iostream>
class vertex;
class face;
class half_edge;
class DCEL;
//vertex class
class vertex
{
	private:
		float x,y;
		int index;
		vertex* next = NULL;
	public:
	vertex(int i,float x1,float y1); //constructor declaration
	//get and set functions declaration
	void set_index(int i);
	int get_index();
	void set_nv(vertex* v);
	vertex* get_nv();
	float get_x();
	float get_y();
	void set_x(float);
};

//class face
class face
{
	private:
		int index;
		half_edge* incident_edge=NULL;
		face* next_face=NULL;
		vertex* inside{NULL};
	public:
	face(int i); //constructor declaration
	//get and set functions declarations
	void set_index(int i);
	int get_index();
	void set_ie(half_edge* e);
	half_edge* get_ie();
	void set_nf(face* f);
	face* get_nf();
};

//class of half_edge
class half_edge
{
	private:
		vertex* origin;
		int index;
		face* incident_face= NULL;
		half_edge* next_edge =NULL;
		half_edge* prev_edge =NULL;
		half_edge* twin=NULL;
	public:
	half_edge(int i,vertex* o);// constructor declaration
	//Get set functions declarations
	void set_index(int i);
	int get_index();
	void set_vtx(vertex *v);
	vertex* get_vtx();
	void set_ne(half_edge* e);
	half_edge* get_ne();
	void set_pe(half_edge* e);
	half_edge* get_pe();
	void set_tn(half_edge* e);
	half_edge* get_tn();
	void set_f(face* f);
	face* get_f();
};

//Class cointaing DCEL and all operations on it
class DCEL
{
	private:
		half_edge* head_he = NULL; //header of half-edge list
		face* head_f = NULL;//header of face list
		vertex* head_v = NULL;
		vertex* head_pt_list{NULL};
		int he_index = 0;
		int f_index=0;
		int v_index=0;
	public:
	//Get set functions
	half_edge* get_he_head(){return head_he;};
	face* get_face_head(){return head_f;}
	vertex* get_v_head(){return head_v;}
	//function declarations
	void add_vtx(float x,float y);
	void add_he(vertex* v);
	face* add_face();
	void last_he();
	void split(int a,int b);
	void output(FILE* fp);
	int check_pos(vertex*,vertex*,vertex*,vertex*);
	int check_inside_face(face* f,vertex* v);
	void add_pt_faceinsidelist(int id,int x,int y);
	void add_pt_list(vertex* v);
};