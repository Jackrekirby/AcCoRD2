clear all;
clc;

% using vargin is not longer recommended (find website)

% To Do
% ensure consistent style key value pairs (Word Case)
%   should class members be capitalised?
% add functions to class so they can share default args         DONE
% add collision plotting                                        DONE
% add json reading
% set default 3d view                                           DONE
% add animated paths [points, startTime = 0, elapsedTime = 5]
% add circle surface                                            DONE
% add cylinders
% change path colour arguments to cell array                    DONE
% nested classes
% animated path


% 1. [start]
% 2. [intersection]
% 3. [end, reflection]
% 4. [end, reflection]
% 5. [end]

%%
clear all;
clc;

figure;

e = Environment('defaultFaceAlpha', 0.2, 'uniqueColorPerBoxFace', true, 'defaultColorMap', hsv(6), ...
    'defaultPathColors', {'k', 'm', 'c'});
flat = true;

if(flat)
    a = e.plotRect();
    hold on;
    b = e.plotCircle();
    c = e.plotPath2D();
    hold off;
else
    %d = e.plotRectSurface([-0.5, -0.5, -0.25], [1, 1, 0]);
    hold on;
    %f = e.plotPath3D();
    %g = e.plotSphere();
    h = e.plotBox();
    %j = e.plotCircleSurface([-1, 0, 0], 0.5, 'x');
    i = e.plotCollision3D([0, 0, 0], [0.5, 0.1, 0.25], [0, 0.2, 0.5], [1, 0.2, 0.5], 'colors', {'c', 'm', 'r', 'y'});
    hold off;
end
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);


%%
clear all;
clc;

x = linspace(-100, 100, 20);
z = (x/10).^2;
y = x ./ 2;
a = AnimatedPath([x; y; z]', 'duration', 1);

view(3);
r = 100;
axis equal;
view(45,30);
xlim([-r, r]); zlim([-r, r]); ylim([-r, r]);

a.play();

% lastTime = 0;
% 
% tic;
% while(a.Update(toc - lastTime))
%     lastTime = toc;
%     pause(0.5);
% end

















