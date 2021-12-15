Author:Pushkar Pawar
IMT2020015

Output format:
Edges:First all edges in increasing order
Halfedges:
1)Starts from half edge 0 if 0 is present in face 0.
2)Half edge of new face starts from edge which is splitted
Faces:
Face index along with Halfedges in clockwise order
Split:
After each split output is given.
Points:
After each point query output is given.
Format:-> Id:pt_id face_index

run: ./assignment3 input.txt split_input.txt point_input.txt output.txt
Note:
1)split occours within same face(if two edges belong to different faces seg fault will occour)
2)Default text editor of ubuntu shows incomplete output file in my machine but after opening the same file in vscode I get full proper solution.