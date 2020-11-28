%% To DO List

% ensure consistent style key value pairs (Word Case)
%   should class members be capitalised?
% add functions to class so they can share default args         DONE
% add collision plotting                                        DONE
% add json reading
% set default 3d view                                           DONE
% add animated paths (2D / 3D)                               (X, DONE)
% add circle surface                                            DONE
% add cylinders
% change path colour arguments to cell array                    DONE
% nested classes                                                N/A

% consider reformatting surface inputs of form (plane, shape)
% seperate animated path functions into seperate files
% consider seperating environment functions into 2d as highlighting edges
% would be more useful for 2d while coloured faces is more useful for 3d.

% Track bug:
% https://uk.mathworks.com/matlabcentral/answers/666553-linewidth-parameter-not-affecting-marker-thickness-of-animated-line

% Consider removing path and collision as AnimatedPath makes them redundant
% Points still needed for rendering molecules;
% Using vargin is not longer recommended (find website reference)

% Learned a function must be created in class before it is moved to
% seperate file
%% Draw Shapes
clear all;
clc;

figure;

j = Environment('defaultFaceAlpha', 0.2, 'uniqueColorPerBoxFace', true, 'defaultColorMap', hsv(6), ...
    'defaultPathColors', {'k', 'm', 'c'});
flat = true;

if(flat)
    a = j.plotRect();
    hold on;
    b = j.plotCircle();
    c = j.plotPath2D();
    hold off;
else
    %d = e.plotRectSurface([-0.5, -0.5, -0.25], [1, 1, 0]);
    hold on;
    %f = e.plotPath3D();
    %g = e.plotSphere();
    h = j.plotBox();
    %j = e.plotCircleSurface([-1, 0, 0], 0.5, 'x');
    i = j.plotCollision3D([0, 0, 0], [0.5, 0.1, 0.25], [0, 0.2, 0.5], [1, 0.2, 0.5], 'colors', {'c', 'm', 'r', 'y'});
    hold off;
end
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);


%% Animated Path
clear all;
clc;

p = [0, 0, 0; 1, 1, 0; 0.5, 0.5, 0; 3, 0.5, 0; 2, 0.5, 0; 2, 2, 0; 2, 1, 0; 4, 1, 0];
a = AnimatedPath(p, 'startTime', 0, 'duration', 0, 'showNonReflectedPoints', true);

view(3);
r = 5;
axis equal;
view(45,30);
xlim([-r, r]); zlim([-r, r]); ylim([-r, r]);

a.play();


%% Json Reader

clear all;
clc;
e = Environment('defaultFaceAlpha', 0.3, 'uniqueColorPerBoxFace', false, 'defaultColorMap', hsv(6));
e.plot('C:\dev\AcCoRD2\MATLAB\environment.json');





