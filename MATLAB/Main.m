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

% [start, end, intersection, reflection] or [start, end, null, null]
% intersection = start, reflection = end
% [start, end, intersection, reflection]

%a = [[0, 0]; [0.5, 0.5]; [1, 1]; [3, 3]]
%path = {[[0, 0]; [0.5, 0.5]; [1, 1]; [3, 3]], [[0, 0]; [0.5, 0.5]; [1, 1]; [3, 3]], [[0, 0]; [0.5, 0.5]]}

% only need start end

tol1 = [2 3,4,5,6,7,8];
tol2 = [1,2,3,4,5,6,7];
x = [1,2,3,4,5,6,7];
% = [startx, starty, endx, endy]
p = [0, 0, 1, 1, 0.5, 0.5, 3, 0.5, 2, 0.5, 2, 2, 2, 1, 4, 1];

%lnh = plot([x;x],[tol1;tol2],'*-');
%lnh2 = plot([p(1:4:end);p(3:4:end)],[p(2:4:end);p(4:4:end)],'*-');
hold on
showReflectedPoints = true;
if(showReflectedPoints)
    ll = [p(3:4:end-2);p(5:4:end)]
    lnh2 = plot([p(3:4:end-2);p(5:4:end)],[p(4:4:end-2);p(6:4:end)],'--k'); % non - reflected line
    lnh4 = plot(p(3:4:end-2),p(4:4:end-2),'om'); % non - reflected points
end
lnh3 = plot([p(1:4:end), p(end-1)], [p(2:4:end), p(end)],'o-', 'Color', 'k', 'MarkerEdgeColor', 'b'); % path points
plot(p(1), p(2),'og'); % start
plot(p(end-1), p(end), 'or'); % final
hold off

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
% just set duration to zero for instant draw

p = [0, 0, 0; 1, 1, 0; 0.5, 0.5, 0; 3, 0.5, 0; 2, 0.5, 0; 2, 2, 0; 2, 1, 0; 4, 1, 0];

a = AnimatedPath(p, 'startTime', 0, 'duration', 0, 'showNonReflectedPoints', true);

view(3);
r = 5;
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

















