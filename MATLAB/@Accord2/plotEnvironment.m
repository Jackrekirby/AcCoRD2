function [hFigure] = plotEnvironment(config, shapePlotters, colormaps, display, showLog)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % plotEnvironment.m - plots the envrionment specified by the
    %   configuration file. No molecules are plotted, only regions,
    %   surfaces and actors. It is a wrapper for the
    %   videoPlotRegionsAndActors function
    
    % INPUTS
    % see videoPlotRegionsAndActors.m
    
    % OUTPUTS
    % returns the figure which the environment is plotted on

    hFigure = figure('Name', 'Simulation Environment','NumberTitle','off');
    hold on;
    Accord2.videoPlotRegionsAndActors(config, shapePlotters, colormaps, display, showLog);
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

