#include"dcel_header.h"
//function to create and add vertex in list
void DCEL::add_vtx(float x,float y)
{
	vertex* v = new vertex(v_index,x,y);
	v_index++;
	if(!head_v){head_v = v;} //adding vertex to end of list
	else
	{
		vertex* v_temp = head_v;
		while(v_temp->get_nv())
		{
			v_temp = v_temp->get_nv();
		}
		v_temp->set_nv(v);
	}
	add_he(v);
}

//function to create and add half_edge to half_edge list
void DCEL::add_he(vertex* v)
{
	half_edge* he_tmp = new half_edge(he_index,v);
	he_index++;
	face* trv_f = head_f;
	while (trv_f->get_nf())
	{
		trv_f = trv_f->get_nf();
	}
	he_tmp->set_f(trv_f); //setting face for half-edge
	if(!head_he) head_he = he_tmp;
	else //adding half edge to end of list
	{
		half_edge* temp = head_he;
		while (temp->get_ne())
		{
			temp = temp->get_ne();
		}
		temp->set_ne(he_tmp);
		he_tmp->set_pe(temp);
	}
}

//function to create and add face to face list
face* DCEL::add_face()
{
	face* ff = new face(f_index);
	ff->set_nf(NULL);
	f_index++;
	if(!head_f){head_f = ff;}
	else //adding face to end of face list
	{
		face* f_temp = head_f;
		while(f_temp->get_nf())
		{
			f_temp = f_temp->get_nf();
		}
		f_temp->set_nf(ff);
	}
	return ff;
}

//function to link last edge of rectangle to first edge and create twins
void DCEL::last_he()
{
	half_edge* temp = head_he;
	while(temp->get_ne())
	{
		temp = temp->get_ne();
	}
	temp->set_ne(head_he);
	head_he->set_pe(temp);
	temp = head_he;
	//creating outer twins for rectangle
	do
	{
		half_edge* n_t = new half_edge(temp->get_index(),temp->get_ne()->get_vtx());
		n_t->set_tn(temp);
		n_t->set_f(temp->get_f());
		temp->set_tn(n_t);
		temp = temp->get_ne();
	} while (temp != head_he);
	//pointer changes of outer twins of rectangle
	do
	{
		temp->get_tn()->set_ne(temp->get_pe()->get_tn());
		temp->get_tn()->set_pe(temp->get_ne()->get_tn());
		temp = temp->get_ne();
	} while (temp != head_he);
	head_f->set_ie(head_he);
	
}

//funciton to implement split functions
void DCEL::split(int a,int b)
{
	face* ff = this->add_face();
	half_edge* he_temp,*he_temp2;
	face* f = head_f;
	//while loop to extract half-edge pointer corresponding to a and b by traversing through entire DCEL
	while (f)
	{
		he_temp = f->get_ie();
		he_temp2=f->get_ie();
		half_edge* temp = f->get_ie();
		do
		{
			while(he_temp->get_index() !=a){he_temp = he_temp->get_ne();if(he_temp == f->get_ie())break;}
			while(he_temp2->get_index() != b){he_temp2 = he_temp2->get_ne();if(he_temp2 == f->get_ie())break;}
			if((he_temp->get_index() == a) && (he_temp2->get_index() == b)) break;
			temp = temp->get_ne();
		}while(temp != f->get_ie());
		if((he_temp->get_index() == a) && (he_temp2->get_index() == b)) break;
		f = f->get_nf();
	}
	//getting half-edge from same face to split
	if(he_temp->get_f() != he_temp2->get_f())
	{
		if(he_temp->get_f() == he_temp2->get_tn()->get_f()) he_temp2 = he_temp2->get_tn();
		if(he_temp2->get_f() == he_temp->get_tn()->get_f()) he_temp = he_temp->get_tn();
		if(he_temp2->get_tn()->get_f() == he_temp2->get_tn()->get_f())
		{
			he_temp = he_temp->get_tn();
			he_temp2 = he_temp2->get_tn();
		}
	}
	vertex* v1 = new vertex(v_index,(he_temp->get_vtx()->get_x()+he_temp->get_ne()->get_vtx()->get_x())/2,(he_temp->get_vtx()->get_y()+he_temp->get_ne()->get_vtx()->get_y())/2);
	v_index++;
	vertex* v2 = new vertex(v_index,(he_temp2->get_vtx()->get_x()+he_temp2->get_ne()->get_vtx()->get_x())/2,(he_temp2->get_vtx()->get_y()+he_temp2->get_ne()->get_vtx()->get_y())/2);
	v_index++;

	//initialising half-egde and twins for new face created
	half_edge* h[3],*t[3];
	h[0] = new half_edge(he_index,v2);
	he_index++;
	h[1] = new half_edge(he_index,v1);
	he_index++;
	h[2] = new half_edge(he_index,he_temp2->get_vtx());
	he_index++;
	face* old = he_temp->get_f();
	//pointer changes for split
	he_temp2->set_vtx(v2);
	h[0]->set_ne(h[1]);
	h[1]->set_pe(h[0]);
	h[1]->set_ne(he_temp->get_ne());
	he_temp->get_ne()->set_pe(h[1]);
	he_temp2->get_pe()->set_ne(h[2]);
	h[2]->set_pe(he_temp2->get_pe());
	h[2]->set_ne(h[0]);
	h[0]->set_pe(h[2]);
	for (int i = 0; i < 3; i++) {t[i] = new half_edge(h[i]->get_index(),h[i]->get_ne()->get_vtx());}
	t[0]->set_ne(he_temp2);
	he_temp2->set_pe(t[0]);
	he_temp->set_ne(t[0]);
	t[0]->set_pe(he_temp);
	he_temp->get_tn()->set_vtx(v1);
	t[1]->set_ne(he_temp->get_tn());
	t[1]->set_pe(he_temp->get_tn()->get_pe());
	he_temp->get_tn()->get_pe()->set_ne(t[1]);
	he_temp->get_tn()->set_pe(t[1]);
	t[2]->set_ne(he_temp2->get_tn()->get_ne());
	t[2]->set_pe(he_temp2->get_tn());
	he_temp2->get_tn()->get_ne()->set_pe(t[2]);
	he_temp2->get_tn()->set_ne(t[2]);
	ff->set_ie(h[0]);
	old->set_ie(t[0]);
	//adjusting twins below
	for (int i = 0; i < 3; i++){h[i]->set_tn(t[i]);t[i]->set_tn(h[i]);}

	//adjusting the face list
	face* tff = head_f;
	while(tff->get_nf()) tff = tff->get_nf();
	tff->set_nf(ff);
	ff->set_nf(NULL);
	
	//adjusting face pointer of all half-edges
	f = head_f;
	while (f)
	{
		half_edge* temp = f->get_ie(),*temp1=f->get_ie();
		do
		{
			temp->set_f(f);
			temp = temp->get_ne();
		}while(temp != temp1);
		f = f->get_nf();
	}
	half_edge* hello = head_f->get_ie();
	half_edge* bello = head_f->get_ie();
	do
	{
		if(hello->get_index() == 0) head_f->set_ie(hello);
		hello = hello->get_ne();
	} while (hello != bello);
	
}
int DCEL::check_pos(vertex* c,vertex* v,vertex* l1,vertex* l2) //checks if two points lie of same side of line or not 
{
	int s1 = ((c->get_y()-l1->get_y())*(l2->get_x()-l1->get_x())) - ((l2->get_y()-l1->get_y())*(c->get_x()-l1->get_x()));
	int s2 = ((v->get_y()-l1->get_y())*(l2->get_x()-l1->get_x())) - ((l2->get_y()-l1->get_y())*(v->get_x()-l1->get_x()));
	if(s1*s2 >=0) return 0;
	return 1;
}
int DCEL::check_inside_face(face* f,vertex* v) //checks if point lies inside face or not
{
	half_edge* tmp = f->get_ie();
	int c_x=0,c_y=0,count=0;
	do
	{
		c_x+=tmp->get_vtx()->get_x();
		c_y+= tmp->get_vtx()->get_y();
		count++;
		tmp = tmp->get_ne();
	} while (tmp != f->get_ie());
	
	vertex* c = new vertex(-1,c_x/count,c_y/count);
	do
	{
		if(check_pos(c,v,tmp->get_vtx(),tmp->get_ne()->get_vtx())) return 0;
		tmp = tmp->get_ne();
	} while (tmp!=f->get_ie());
	return 1;
}
void DCEL::add_pt_list(vertex* v) //creates the list of points with corresponding face index in which the point is contained
{
	if(!head_pt_list)
	{
		head_pt_list = v;
		head_pt_list->set_nv(NULL);
	}
	else
	{
		vertex* tmp = head_pt_list;
		while(tmp->get_nv()) tmp = tmp->get_nv();
		tmp->set_nv(v);
		tmp->get_nv()->set_nv(NULL);
	}
}
void DCEL::add_pt_faceinsidelist(int id,int x,int y) //add point to the point list
{
	face* f = head_f;
	vertex* temp=head_pt_list;
	vertex* v = new vertex(id,x,y);
	while(f)
	{
		if(check_inside_face(f,v))
		{
			v->set_x(f->get_index());
			add_pt_list(v);
		}
		f = f->get_nf();
	}
	
}
//function to print to output file
void DCEL::output(FILE* fp)
{
	fprintf(fp,"Edges:\n");
	face* f = head_f;
	for (int i = 0; i < he_index; i++)
	{
		fprintf(fp,"%d\n",i);
	}

	fprintf(fp,"Halfedges:\n");
	//In each while loop DCEL is traversed entirely to get corresponding output
	f = head_f;
	while (f)
	{
		half_edge* temp = f->get_ie(),*temp1=f->get_ie();
		do
		{
			fprintf(fp,"startVertexIndex=%d endVertexIndex=%d nextEdge=%d previousEdge=%d faceIndex=%d edgeIndex=%d\n",temp->get_vtx()->get_index(),temp->get_ne()->get_vtx()->get_index(),temp->get_ne()->get_index(),temp->get_pe()->get_index(),temp->get_f()->get_index(),temp->get_index());
			temp = temp->get_ne();
		}while(temp != temp1);
		f = f->get_nf();
	}

	fprintf(fp,"Faces:\n");
	f = head_f;
	while (f)
	{
		half_edge* temp = f->get_ie(),*temp1=f->get_ie();
		fprintf(fp,"FaceIndex:%d Edges %d",f->get_index(),temp->get_index());
		temp = temp->get_ne();
		do
		{
			fprintf(fp,"->%d",temp->get_index());
			temp = temp->get_ne();
		}while(temp != temp1);
		f = f->get_nf();
		fprintf(fp,"\n");
	}
	vertex* vt = head_pt_list;
	while(vt)
	{
		int bca = vt->get_x();
		fprintf(fp,"Id:%d %d\n",vt->get_index(),bca);
		vt = vt->get_nv();
	}
	
}
	