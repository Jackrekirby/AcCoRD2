function [video] = videoCreateFigure(video)
    video.hFigure = figure('Name', 'Simulation Time:','NumberTitle','off');
    video.hOriginPlot = plot3(0, 0, 0, 'Marker', 'none');
    xlabel('x');
    ylabel('y');
    zlabel('z');
    axis equal;
    view(45,30);
end