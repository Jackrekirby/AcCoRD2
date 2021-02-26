clear all;
clc;
% need to input subvolumes
s = jsondecode(fileread("C:\dev\AcCoRD2\MATLAB\simulation2.json"));

render.Micro = true;
render.Meso = true;
render.ActiveActors = true;
render.PassiveActors = true;
hold on;

%% Region Names
nMesoscopicRegions = length(s.MesoscopicRegions);
mesoscopicRegionNames(nMesoscopicRegions) = "";
for i = 1:length(s.MesoscopicRegions)
    mesoscopicRegionNames(i) = s.MesoscopicRegions(i).Name;
end
nMicroscopicRegions = length(s.MicroscopicRegions);
microscopicRegionNames(nMicroscopicRegions) = "";
for i = 1:nMicroscopicRegions
    microscopicRegionNames(i) = s.MicroscopicRegions(i).Name;
end
%% Mesoscopic Regions
if(render.Meso)
    mesoShape3D = Shape3D('FaceColorMap', autumn(nMesoscopicRegions), ...
        'LineColorMap', autumn(nMesoscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
    for i = 1:nMesoscopicRegions
        r = s.MesoscopicRegions(i);
        disp("Plot Mesoscopic Region");
        mesoShape3D.plotBox(r.Origin, r.SubvolumeLength * r.NumberOfSubvolumes);
    end
end
%% Microscopic Regions
if(render.Micro)
    microShape3D = Shape3D('FaceColorMap', winter(nMicroscopicRegions), ...
        'LineColorMap', winter(nMicroscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
    for i = 1:nMicroscopicRegions
        r = s.MicroscopicRegions(i);
        disp("Plot Microscopic Region");
        plotShape(microShape3D, r.Shape);
    end
end
%% Active Actors
if(render.ActiveActors)
    nActiveActors = length(s.ActiveActors);
    activeActorShape3D = Shape3D('FaceColorMap', spring(nActiveActors), ...
        'LineColorMap', spring(nActiveActors), 'EdgeAlpha', 0);
    for i = 1:nActiveActors
        r = s.ActiveActors(i);
        if(isfield(r, '1Shape'))
            disp("Plot Active Actor");
            plotShape(activeActorShape3D,  r.Shape);
        elseif(isfield(r, 'RegionsToActIn'))   
            for j = 1:length(r.RegionsToActIn)
                regionToActIn = r.RegionsToActIn(j);
                [~, mesoID] = find(mesoscopicRegionNames == regionToActIn);
                if(~isempty(mesoID))
                    rr = s.MesoscopicRegions(mesoID);
                    disp("Plot Mesoscopic Active Actor");
                    activeActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                else
                    [~, microID] = find(microscopicRegionNames == regionToActIn);
                    if(~isempty(microID))
                        disp("Plot Microscopic Active Actor");
                        plotShape(activeActorShape3D, s.MicroscopicRegions(microID).Shape);
                    else
                        warning("No region name matched");
                    end
                end
            end
        end
    end
end
%% Passive Actors
if(render.PassiveActors)
    nPassiveActors = length(s.PassiveActors);
    passiveActorShape3D = Shape3D('FaceColorMap', summer(nPassiveActors), ...
        'LineColorMap', summer(nPassiveActors), 'EdgeAlpha', 0);
    for i = 1:nPassiveActors
        r = s.PassiveActors(i);
        if(isfield(r, '1Shape'))
            disp("Plot Passive Actor");
            plotShape(passiveActorShape3D,  r.Shape);
        elseif(isfield(r, 'RegionsToObserve'))   
            for j = 1:length(r.RegionsToObserve)
                RegionsToObserve = r.RegionsToObserve(j);
                [~, mesoID] = find(mesoscopicRegionNames == RegionsToObserve);
                if(~isempty(mesoID))
                    rr = s.MesoscopicRegions(mesoID);
                    disp("Plot Mesoscopic Passive Actor");
                    passiveActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                else
                    [~, microID] = find(microscopicRegionNames == RegionsToObserve);
                    if(~isempty(microID))
                        disp("Plot Microscopic Passive Actor");
                        plotShape(passiveActorShape3D, s.MicroscopicRegions(microID).Shape);
                    else
                        warning("No region name matched");
                    end
                end
            end
        end
    end
end
%%

hold off;

view(3);
axis equal;

function plotShape(renderer, shape)
    if(shape.Type == "Box")
        renderer.plotBox(shape.Origin, shape.Length);
    elseif(shape.Type == "Sphere")
        renderer.plotSphere(shape.Centre, shape.Radius);
    elseif(shape.Type == "Cylinder")
        renderer.plotCylinder(shape.BaseCentre, shape.Radius, shape.Length, shape.Axis);
    else
        warning("Shape must be Box, Sphere or Cylinder");
    end
end