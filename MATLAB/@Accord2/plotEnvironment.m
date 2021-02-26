function [hFigure] = plotEnvironment(config, shapePlotters, colormaps, display, showLog)
    % shapePlotters = [ShapePlotter, ShapePlotter, ShapePlotter, ShapePlotter];
    % display = [true, true, true, true]
    % colormap = [hsv, jet, summer, autumn];
    % moleculeStyle.colorMethod = 'actor'; % or 'type'
    % moleculeStyle.fill = true;
    % moleculeStyle.size = 10;

    hFigure = figure('Name', 'Simulation Environment','NumberTitle','off');
    hold on;
    Accord2.videoPlotRegionsAndActors(config, shapePlotters, colormaps, display, showLog);
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
    set(gca,'XColor', 'none','YColor','none','ZColor','none');
end

