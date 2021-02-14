function videoPlotRegionsAndActors(config, render)
    
    % render = [regions, active actors, passive actors]
    
    % Compile a list of all mesoscopic and microscopic region anmes
    if(isfield(config, "MesoscopicRegions"))
        nMesoscopicRegions = length(config.MesoscopicRegions);
         mesoscopicRegionNames(nMesoscopicRegions) = "";
         for i = 1:length(config.MesoscopicRegions)
            mesoscopicRegionNames(i) = config.MesoscopicRegions(i).Name;
        end
    else
        nMesoscopicRegions = 0;
         mesoscopicRegionNames = "";
    end

    if(isfield(config, "MicroscopicRegions"))
        nMicroscopicRegions = length(config.MicroscopicRegions);
        microscopicRegionNames(nMicroscopicRegions) = "";
        for i = 1:nMicroscopicRegions
            microscopicRegionNames(i) = config.MicroscopicRegions(i).Name;
        end
    else
        nMicroscopicRegions = 0;
        microscopicRegionNames = "";
    end

    % Plot Mesoscopic Regions
    if(isfield(config, "MesoscopicRegions"))
        mesoShape3D = Shape3D('FaceColorMap', autumn(nMesoscopicRegions), ...
            'LineColorMap', autumn(nMesoscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
        for i = 1:nMesoscopicRegions
            r = config.MesoscopicRegions(i);
            mesoShape3D.plotGriddedBox(r.Origin, r.SubvolumeLength * r.NumberOfSubvolumes, r.NumberOfSubvolumes);
        end
    end
    
    
    % Plot Microscopic Surfaces
    if(isfield(config, "MicroscopicSurfaces"))
        nMicroscopicSurfaces = length(config.MicroscopicSurfaces);
        microSurfShape3D = Shape3D('FaceColorMap', winter(nMicroscopicSurfaces), ...
            'LineColorMap', autumn(nMicroscopicSurfaces), 'FaceAlpha', 0, 'EdgeAlpha', 1);
        for i = 1:nMicroscopicSurfaces
            r = config.MicroscopicSurfaces(i);
            disp("Plot Microscopic Surface");
            microSurfShape3D.plotShape(r.Shape);
        end
    end
    
    % Plot Microscopic Regions
    if(isfield(config, "MicroscopicRegions"))
        microShape3D = Shape3D('FaceColorMap', winter(nMicroscopicRegions), ...
            'LineColorMap', winter(nMicroscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
        for i = 1:nMicroscopicRegions
            r = config.MicroscopicRegions(i);
            disp("Plot Microscopic Region");
            microShape3D.plotShape(r.Shape);
        end
    end
    
    % Plot Active Actors
    if(render(1) && isfield(config, "ActiveActors"))
        nActiveActors = length(config.ActiveActors);
        activeActorShape3D = Shape3D('FaceColorMap', spring(nActiveActors), ...
            'LineColorMap', spring(nActiveActors), 'EdgeAlpha', 0);
        for i = 1:nActiveActors
            r = config.ActiveActors(i);
            if(iscell(r))
                r = r{1};
            end
            if(isfield(r, 'Shape'))
                disp("Plot Active Actor");
                activeActorShape3D.plotShape(r.Shape);
            elseif(isfield(r, 'RegionsToActIn'))   
                for j = 1:length(r.RegionsToActIn)
                    regionToActIn = r.RegionsToActIn(j);
                    [~, mesoID] = find(mesoscopicRegionNames == regionToActIn);
                    if(~isempty(mesoID))
                        rr = config.MesoscopicRegions(mesoID);
                        disp("Plot Mesoscopic Active Actor");
                        activeActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                    else
                        [~, microID] = find(microscopicRegionNames == regionToActIn);
                        if(~isempty(microID))
                            disp("Plot Microscopic Active Actor");
                            activeActorShape3D.plotShape(config.MicroscopicRegions(microID).Shape);
                        else
                            warning("No region name matched");
                        end
                    end
                end
            end
        end
    end
    
    % Passive Actors
    if(render(2) && isfield(config, "PassiveActors"))
        nPassiveActors = length(config.PassiveActors);
        passiveActorShape3D = Shape3D('FaceColorMap', summer(nPassiveActors), ...
            'LineColorMap', summer(nPassiveActors), 'EdgeAlpha', 0);
        for i = 1:nPassiveActors
            r = config.PassiveActors(i);
            if(isfield(r, 'Shape'))
                disp("Plot Passive Actor");
                passiveActorShape3D.plotShape(r.Shape);
            elseif(isfield(r, 'RegionsToObserve'))   
                for j = 1:length(r.RegionsToObserve)
                    RegionsToObserve = r.RegionsToObserve(j);
                    [~, mesoID] = find(mesoscopicRegionNames == RegionsToObserve);
                    if(~isempty(mesoID))
                        rr = config.MesoscopicRegions(mesoID);
                        disp("Plot Mesoscopic Passive Actor");
                        passiveActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                    else
                        [~, microID] = find(microscopicRegionNames == RegionsToObserve);
                        if(~isempty(microID))
                            disp("Plot Microscopic Passive Actor");
                            passiveActorShape3D.plotShape(config.MicroscopicRegions(microID).Shape);
                        else
                            warning("No region name matched");
                        end
                    end
                end
            end
        end
    end
end