clear all;
clc;

% using vargin is not longer recommended (find website)

% To Do
% ensure consistent style key key value pairs (Word Case)
% add functions to class so they can share default args         DONE
% add collision plotting                                        DONE
% add json reading
% set default 3d view
% add animated paths
% add circle surface
% add cylinders

figure;

e = Environment('defaultFaceAlpha', 0.2, 'uniqueColorPerBoxFace', true, 'defaultColorMap', hsv(3));
flat = false;

if(flat)
    a = e.plotRect();
    hold on;
    b = e.plotCircle();
    c = e.plotPath2D();
    hold off;
else
    %d = e.plotRectSurface();
    hold on;
    %f = e.plotPath3D();
    %g = e.plotSphere();
    h = e.plotBox();
    i = e.plotCollision3D([0, 0, 0], [1, 0.2, 0.5], [0.5, 0.1, 0.25], [0, 0.2, 0.5]);
    hold off;
end
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);