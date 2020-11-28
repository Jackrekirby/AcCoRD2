%% Archive
clear all;
clc;

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
