#include<iostream>
using namespace std;
#include"dcel_header.h"
int main(int argc,char* argv[])
{
	FILE *fw,*fr,*ff,*fpt;
	int x,y,id;
	if(argc != 5)	//checking valid input
	{
		printf("Please give valid input to terminal");
		return 0;
	}

	fr = fopen(argv[1],"rb"); //opening input file
	ff = fopen(argv[2],"rb");
	fpt = fopen(argv[3],"rb");
	fw = fopen(argv[4],"w");  //opening output file
	DCEL dcel;//creating DCEL object
	dcel.add_face();
	while(!feof(fr))//Loading vertex of rectangle
	{
		fscanf(fr,"%d %d\n",&x,&y);
		dcel.add_vtx(x,y);
	}
	dcel.last_he();
	dcel.output(fw); //printing output to file
	while (!feof(ff)) //splits till EOF
	{
		char c[6];
		for (int i = 0; i < 6; i++)
		{
			fscanf(ff,"%c",&c[i]);
		}
		
		fscanf(ff,"%d %d\n",&x,&y);
		dcel.split(x,y);
		dcel.output(fw);
	}
	while(!feof(fpt)) //input of points with id
	{
		char t[3];
		for (int i = 0; i < 3; i++)
		{
			fscanf(fpt,"%c",&t[i]);
		}
		float a,b;
		fscanf(fpt,"%d %f %f\n",&id,&a,&b);
		dcel.add_pt_faceinsidelist(id,a,b);
		dcel.output(fw);
	}
	fclose(fw);
	fclose(ff);
	fclose(fr);
	fclose(fpt);
}