function [shapes] = videoPlotRegionsAndActors(config, shapePlotters, colormaps, display, showLog)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % videoPlotRegionsAndActors.m - plots each region, actor and surface in
    % the simulation environment, specified by the config file. Output
    % files not necessary to render shapes.
    
    % INPUTS
    % config - the config data retrieved from Accord2.importConfig()
    % shapePlotters - a single, or vector of 5 ShapePlotter objects. These
    %   specify how each type of region, surface and actor will render.
    %   Providing only a single ShapePlotter object will result in all
    %   shapes being rendered with the same style
    % colormaps - a single or vector of 5 strings which are to be converted
    %   to functions, thus strings must be valid functions. If only a single
    %   colormap is provided then all shapes will use the same colormap. An
    %   empty string element can be passed in the 5 element vector if that
    %   type of object (e.g. active actors) are not being rendered, as
    %   specified by the 'display' input argument
    % display - a single or vector of 5 booleans which state whether the type of
    %   object is to be plotted. If single boolean then boolean applied to
    %   all objects
    % showLog - a boolean which if true will provide output messages as to
    %   the types of shapes being plotted
    
    % OUTPUTS
    % shapes - a struct containing vectors of handles to each shape plotted.
    
    % NOTES
    % The 5 element vectors for shapePlotters, colormaps and display all
    %   have the format of:
    %   [microscopic regions, microscopic surfaces, mesoscopic regions, active actors, passive actors]
    %   e.g. display = [true, true, true, false, true] would mean all shapes
    %   except for active actors would be plotted
    % If 'ObserveEachRegion' in config file is true passive actors are not
    %   plotted
    
    % Apply the same shape plot style to all regions and actors if only one
    % shape plot object supplied
    if(length(shapePlotters) == 1)
        shapePlotters = [shapePlotters, shapePlotters, shapePlotters, shapePlotters, shapePlotters];
    end
    
    if(length(display) == 1)
        display = [display, display, display, display, display];
    end
    
    % edgeTone = 0.3 : edge color 30% as bright as face color
    edgeTone = 0.9;
    
    %% Count regions, surfaces and actors
    
    % Count number of mesoscopic regions
    if(isfield(config, "MicroscopicRegions"))
        nMicroscopicRegions = length(config.MicroscopicRegions);
        microscopicRegionNames(nMicroscopicRegions) = "";
    else
        nMicroscopicRegions = 0;
        microscopicRegionNames = "";
    end
    
    % Count number of mesoscopic regions
    if(isfield(config, "MesoscopicRegions"))
        nMesoscopicRegions = length(config.MesoscopicRegions);
        mesoscopicRegionNames(nMesoscopicRegions) = "";
    else
        nMesoscopicRegions = 0;
        mesoscopicRegionNames = "";
    end
    
    % Count number of microscopic surfaces
    if(isfield(config, "MicroscopicSurfaces"))
        nMicroscopicSurfaces = length(config.MicroscopicSurfaces);
    else
        nMicroscopicSurfaces = 0;
    end
    
    % Count number of active actors
    if(isfield(config, "ActiveActors"))
        nActiveActors = length(config.ActiveActors);
    else
        nActiveActors = 0;
    end
    
    % Count number of passive actors
    if(isfield(config, "PassiveActors") && ~config.ObserveEachRegion)
        nPassiveActors = length(config.PassiveActors);
    else
        nPassiveActors = 0;
    end
    
    % Count the total number of objects
    nObjects = [nMicroscopicRegions, nMicroscopicSurfaces, ...
        nMesoscopicRegions, nActiveActors, nPassiveActors];
    objectCount = sum(nObjects .* display);
    if(showLog)
        disp(objectCount + " objects to plot");
    end
    
    %% Compile list of region names
    
    % Compile list of microscopic region names
    for i = 1:nMicroscopicRegions
        microscopicRegionNames(i) = config.MicroscopicRegions(i).Name;
    end
    
    % Compile list of mesoscopic region names
    for i = 1:nMesoscopicRegions
        mesoscopicRegionNames(i) = config.MesoscopicRegions(i).Name;
    end
    
    %% Create the colormaps to apply to each shape object
    maxColormaps = 5;
    nColormaps = length(colormaps);
    switch nColormaps
        case 0
            % no colormap supplied. Use ShapePlotter default
        case 1
            % one colormap supplied, apply to all objects
            colormapFnc = str2func(colormaps);
            globalColors = colormapFnc(objectCount);
            colorIndex = 0;
        case maxColormaps
            % one colormap per object, apply to each
        otherwise
            warning("Must supply 0, 1, or 5 colormaps. Will default to 0");
            nColormaps = 0;
    end
    
    %% Plot regions, surfaces and actors
    shapes = [];
    % Plot microscopic regions
    if(display(1) && nMicroscopicRegions ~= 0)
        % if individual colormap supplied create it
        if(nColormaps == maxColormaps)
            colormapFnc = str2func(colormaps(1));
            colors = colormapFnc(nMicroscopicRegions);
        end
        for i = 1:nMicroscopicRegions
            r = config.MicroscopicRegions(i);
            if(showLog)
                disp("Plotting microscopic region");
            end
            % if colormap(s) supplied get next color.
            if(nColormaps == 1)
                colorIndex = colorIndex + 1;
                color = globalColors(colorIndex, :);
            elseif(nColormaps == maxColormaps)
                color = colors(i, :);
            end
            if(nColormaps ~= 0)
                shapePlotters(1).EdgeColor = color * edgeTone;
                shapePlotters(1).FaceColor = color;
            end
            shapes(length(shapes) + 1).handle = shapePlotters(1).plotShape(r.Shape);
        end
    end
    
    % Plot microscopic surfaces
    if(display(2) && nMicroscopicSurfaces ~= 0)
        % if individual colormap supplied create it
        if(nColormaps == maxColormaps)
            colormapFnc = str2func(colormaps(2));
            colors = colormapFnc(nMicroscopicSurfaces);
        end
        for i = 1:nMicroscopicSurfaces
            r = config.MicroscopicSurfaces(i);
            if(showLog)
                disp("Plotting microscopic surface");
            end
            % if colormap(s) supplied get next color.
            if(nColormaps == 1)
                colorIndex = colorIndex + 1;
                color = globalColors(colorIndex, :);
            elseif(nColormaps == maxColormaps)
                color = colors(i, :);
            end
            if(nColormaps ~= 0)
                shapePlotters(2).EdgeColor = color * edgeTone;
                shapePlotters(2).FaceColor = color;
            end
            shapes(length(shapes) + 1).handle = shapePlotters(2).plotShape(r.Shape);
        end
    end
    
    % Plot mesoscopic regions
    if(display(3) && nMesoscopicRegions ~= 0)
        % if individual colormap supplied create it
        if(nColormaps == maxColormaps)
            colormapFnc = str2func(colormaps(3));
            colors = colormapFnc(nMesoscopicRegions);
        end
        for i = 1:nMesoscopicRegions
            r = config.MesoscopicRegions(i);
            if(showLog)
                disp("Plotting mesoscopic region");
            end
            % if colormap(s) supplied get next color.
            if(nColormaps == 1)
                colorIndex = colorIndex + 1;
                color = globalColors(colorIndex, :);
            elseif(nColormaps == maxColormaps)
                color = colors(i, :);
            end
            if(nColormaps ~= 0)
                shapePlotters(3).EdgeColor = color * edgeTone;
                shapePlotters(3).FaceColor = color;
            end
            shapes(length(shapes) + 1).handle = shapePlotters(3).plotGriddedBox(...
                r.Origin, r.SubvolumeLength * r.NumberOfSubvolumes, r.NumberOfSubvolumes);
        end
    end
    
    if(display(4) && nActiveActors ~= 0)
        % if individual colormap supplied create it
        if(nColormaps == maxColormaps)
            colormapFnc = str2func(colormaps(4));
            colors = colormapFnc(nActiveActors);
        end
        for i = 1:nActiveActors
            % if colormap(s) supplied get next color.
            if(nColormaps == 1)
                colorIndex = colorIndex + 1;
                color = globalColors(colorIndex, :);
            elseif(nColormaps == maxColormaps)
                color = colors(i, :);
            end
            if(nColormaps ~= 0)
                shapePlotters(4).EdgeColor = color * edgeTone;
                shapePlotters(4).FaceColor = color;
            end
            r = config.ActiveActors(i);
            % Check what type of active actor is specified. 
            % If the actor is specified by a shape plot the shape. 
            % If the actor is specified by a region plot the shape of each region.
            if(isfield(r, 'Shape'))
                if(showLog)
                    disp("Plotting active actor");
                end
                shapes(length(shapes) + 1).handle = shapePlotters(4).plotShape(r.Shape);
            elseif(isfield(r, 'RegionsToActIn'))
                % for each region the actor acts in. Check mesoscopic and
                % microscopic region names. If name not found warn user.
                for j = 1:length(r.RegionsToActIn)
                    regionToActIn = r.RegionsToActIn(j);
                    [~, mesoID] = find(mesoscopicRegionNames == regionToActIn);
                    if(~isempty(mesoID))
                        rr = config.MesoscopicRegions(mesoID);
                        if(showLog)
                            disp("Plotting mesoscopic active actor");
                        end
                        shapes(length(shapes) + 1).handle = shapePlotters(4).plotBox(...
                            rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                    else
                        [~, microID] = find(microscopicRegionNames == regionToActIn);
                        if(~isempty(microID))
                            if(showLog)
                                disp("Plotting microscopic active actor");
                            end
                            shapes(length(shapes) + 1).handle = shapePlotters(4).plotShape(...
                                config.MicroscopicRegions(microID).Shape);
                        else
                            warning("No region name matched that specified by active actor");
                        end
                    end
                end
            end
        end
    end
    
    if(display(5) && nPassiveActors ~= 0)
        % if individual colormap supplied create it
        if(nColormaps == maxColormaps)
            colormapFnc = str2func(colormaps(5));
            colors = colormapFnc(nPassiveActors);
        end
        for i = 1:nPassiveActors
            % if colormap(s) supplied get next color.
            if(nColormaps == 1)
                colorIndex = colorIndex + 1;
                color = globalColors(colorIndex, :);
            elseif(nColormaps == maxColormaps)
                color = colors(i, :);
            end
            if(nColormaps ~= 0)
                shapePlotters(5).EdgeColor = color * edgeTone;
                shapePlotters(5).FaceColor = color;
            end
            r = config.PassiveActors(i);
            % Check what type of active actor is specified. 
            % If the actor is specified by a shape plot the shape. 
            % If the actor is specified by a region plot the shape of each region.
            if(isfield(r, 'Shape'))
                if(showLog)
                    disp("Plotting passive actor");
                end
                shapes(length(shapes) + 1).handle = shapePlotters(5).plotShape(r.Shape);
            elseif(isfield(r, 'RegionsToObserve'))   
                % for each region the actor acts in. Check mesoscopic and
                % microscopic region names. If name not found warn user.
                for j = 1:length(r.RegionsToObserve)
                    RegionsToObserve = r.RegionsToObserve(j);
                    [~, mesoID] = find(mesoscopicRegionNames == RegionsToObserve);
                    if(~isempty(mesoID))
                        rr = config.MesoscopicRegions(mesoID);
                        if(showLog)
                            disp("Plotting mesoscopic passive actor");
                        end
                        shapes(length(shapes) + 1).handle = shapePlotters(5).plotBox(...
                            rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                    else
                        [~, microID] = find(microscopicRegionNames == RegionsToObserve);
                        if(~isempty(microID))
                            if(showLog)
                                disp("Plotting microscopic passive actor");
                            end
                            shapes(length(shapes) + 1).handle = shapePlotters(5).plotShape(...
                                config.MicroscopicRegions(microID).Shape);
                        else
                            warning("No region name matched that specified by passive actor");
                        end
                    end
                end
            end
        end
    end
end