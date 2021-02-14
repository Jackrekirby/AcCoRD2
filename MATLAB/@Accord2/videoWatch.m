function [video] = videoWatch(data, moleculeStyle, shape3D)
    
    % moleculeStyle.colorMethod = 'actor'; % or 'type'
    % moleculeStyle.fill = true;
    % moleculeStyle.size = 10;

    video = data.s(1).r(1);
    hold on;
    video = Accord2.videoCreateFigure(video);
    video = Accord2.videoCreateMoleculePlots(video, moleculeStyle);
    hold off;
end

