function [video] = videoCreateScene(data, config, moleculeStyle)
    
    % moleculeStyle.colorMethod = 'actor'; % or 'type'
    % moleculeStyle.fill = true;
    % moleculeStyle.size = 10;

    video = data.s(1).r(1);
    video = Accord2.videoCreateFigure(video);
    hold on;
    video = Accord2.videoCreateMoleculePlots(video, moleculeStyle);
    Accord2.videoPlotRegionsAndActors(config, [false, false]);
    hold off;
    axis equal;
    axis tight;
    view(45,30);
    set(gcf,'color','w');
    set(gca,'XTickLabel',[]);
    set(gca,'YTickLabel',[]);
    set(gca,'ZTickLabel',[]);
    set(gca,'xtick',[]);
    set(gca,'ytick',[]);
    set(gca,'ztick',[]);
end

