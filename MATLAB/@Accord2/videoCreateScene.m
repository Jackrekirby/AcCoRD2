function [video] = videoCreateScene(data, config, moleculeStyle, shapePlotters, colormap, display, showLog)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % videoCreateScene.m - plots the envrionment specified by the
    %   configuration file and initialises the molecule plots.
    %   It is a wrapper for the videoCreateMoleculePlots 
    %   & videoPlotRegionsAndActors function 
    
    % INPUTS
    % see requirements of videoCreateMoleculePlots & videoPlotRegionsAndActors.m
    
    % OUTPUTS
    % video - returns a struct containing the molecule data, video graphics and
    %   logics
    
    video = data.s(1).r(1);
    video.hFigure = figure('Name', 'Simulation Time:','NumberTitle','off');
    hold on;
    video = Accord2.videoCreateMoleculePlots(video, moleculeStyle);
    Accord2.videoPlotRegionsAndActors(config, shapePlotters, colormap, display, showLog);
    hold off;
    axis equal;
    axis tight;
    % force 3D perspective
    view(45,30);
    % set background to white
    set(gcf,'color','w');
    % remove all axis labels
    set(gca,'XTickLabel',[]); set(gca,'YTickLabel',[]); set(gca,'ZTickLabel',[]);
    set(gca,'xtick',[]); set(gca,'ytick',[]); set(gca,'ztick',[]);
    set(gca,'XColor', 'none','YColor','none','ZColor','none');
end

