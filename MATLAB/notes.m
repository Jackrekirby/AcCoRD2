%% MATLAB VISUALISATION TOOLS

clear all;
clc;


h = animatedline;
axis([0, 10, 0, 100]);

x = [0:10];
y = x .^ 2;

for k = 1:length(x)
    addpoints(h,x(k),y(k));
    pause(1);
    drawnow
end

% PlotEnvironment("jsonfilepath", animation_speed)

% Functions

% 2D Environments

% [plot] = PlotRect
% [plot] = PlotCircle
% [plot] = PlotPoints(points, show connections)
% AnimatePaths

% 3D Environments

% [plot] = PlotBox
% [plot] = PlotSphere
% [plot] = PlotRectSurface
% [plot] = PlotCircleSurface

% Plot 2D and 3D shapes onto different plot

% Need to decide Json Format

% [shapes] = ImportJson()

% Type = Rect, Circle, Path2D