clear all;
clc;

% To Do
% ensure consistent style key key value pairs (Word Case)
% add functions to class so they can share default args
% add collision plotting
% add json reading
% set default 3d view
% add animated paths

figure;

flat = false;

if(flat)
    a = plotRect();
    hold on;
    b = plotCircle();
    c = plotPath2D();
    hold off;
else
    d = plotRectSurface();
    hold on;
    e = plotPath3D();
    %%f = plotBox([0, 0, 0], [1, 1, 1], 'faceColors', jet(6), 'faceAlpha', 0.9);
    g = plotSphere();
    hold off;
end
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;