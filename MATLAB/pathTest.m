%% Animated Path 3D
clear all;
clc;
% empty figure being drawn (due to view3?)

s = Shape3D();

% absorbing surface will make it seem as if molecule passed through surface

s.plot('C:\dev\AcCoRD2\MATLAB\path.json');
hold on;
j = jsondecode(fileread('C:\dev\AcCoRD2\MATLAB\path.json'));
a = AnimatedPath3D(j.path3D, 'startTime', 0, 'duration', 0, 'showNonReflectedPoints', false);
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
