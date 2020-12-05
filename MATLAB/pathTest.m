%% Animated Path 3D
clear all;
clc;

s = Shape3D();
hold on;
s.plot('C:\dev\AcCoRD2\MATLAB\path.json');
hold off;
j = jsondecode(fileread('C:\dev\AcCoRD2\MATLAB\path.json'));
hold on;
a = AnimatedPath3D(j.path3D, 'startTime', 0.5, 'duration', 10, 'showNonReflectedPoints', false);
hold off;
view(3);
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);
r = 10;
xlim([-r, r]); zlim([-r, r]); ylim([-r, r]);

a.play();
