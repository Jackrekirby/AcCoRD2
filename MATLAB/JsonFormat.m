clear all;
clc;

e.shapes.box(1).origin = [-0.5, -0.5, -0.5];
e.shapes.box(1).length = [1, 1, 1];
e.shapes.box(2).origin = [-0.5, -0.5, -0.5];
e.shapes.box(2).length = [1, 1, 1];

e.shapes.sphere(1).centre = [-1.5, 0, 0];
e.shapes.sphere(1).radius = 0.5;

e.shapes.rect(1).origin = [-1.25, -0.5];
e.shapes.rect(1).length = [1, 1];

e.shapes.circle(1).type = "circle";
e.shapes.circle(1).centre = [0.75, 0];
e.shapes.circle(1).radius = 0.5;

e.shapes.rectSurface(1).origin = [-0.5, -0.5, -1];
e.shapes.rectSurface(1).length = [1, 1, 0];

e.shapes.circleSurface(1).centre = [0.5, 0, 1];
e.shapes.circleSurface(1).radius = 0.5;
e.shapes.circleSurface(1).axis = 'z';

e.path3D = [0, 0, 0; 1, 1, 0; 0.5, 0.5, 0; 3, 0.5, 0; 2, 0.5, 0; 2, 2, 0; 2, 1, 0; 4, 1, 0];
e.path2D = [0, 0; 1, 1; 0.5, 0; 3, 0.5; 2, 0.5; 2, 2; 2, 1; 4, 1];
j = jsonencode(e);
j
fileID = fopen('C:\dev\AcCoRD2\MATLAB\environment.json','w');
fprintf(fileID, j);
fclose(fileID);

