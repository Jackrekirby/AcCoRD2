%% Animated Path 3D
clear all;
clc;

j = jsondecode(fileread('C:\dev\AcCoRD2\MATLAB\environment.json'));
a = AnimatedPath3D(j.path3D, 'startTime', 0, 'duration', 0, 'showNonReflectedPoints', true);

view(3);
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);
r = 5;
xlim([-r, r]); zlim([-r, r]); ylim([-r, r]);

a.play();

%% Animated Path 2D
clear all;
clc;

j = jsondecode(fileread('C:\dev\AcCoRD2\MATLAB\environment.json'));
a = AnimatedPath2D(j.path2D, 'startTime', 0, 'duration', 0, 'showNonReflectedPoints', true);

axis equal;
r = [-1, 5];
xlim(r); ylim(r);
xlabel('x');
ylabel('y');
a.play();

%% Json Reader

clear all;
clc;
e = Environment('defaultFaceAlpha', 0.3, 'uniqueColorPerBoxFace', false, 'defaultColorMap', hsv(6));
e.plot('C:\dev\AcCoRD2\MATLAB\environment.json');

%% Shape3D
clear all;
clc;

s = Shape3D();
s.plot('C:\dev\AcCoRD2\MATLAB\environment.json');

%% Shape2D
clear all;
clc;

s = Shape2D();
s.plot('C:\dev\AcCoRD2\MATLAB\environment.json');




