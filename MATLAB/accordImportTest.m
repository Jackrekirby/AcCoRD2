%% To Do
% 1. Add number of shapes to sim.regions so hsv(nshapes) can be given to
% shape3D so colour of region matches plotted line colour
% animated line?
% 2. add import regions info message
% 3. Pass two shape objects to realisation so regions and actors can be drawn
% with different styles.
% Investigate available colour maps so regions and actors can look unique.
% 4. Consider removing maxAveraged for count plotting
% 5. Consider added plotCount(moleculeType, passiveActor)
% 6. If frame rate of live animation > 30 then limit
% 7. Set colours for meso and micro.
% 8. Set colours for subvolumes the same as the meso subvolume (requires improved json structure)
% 9. Redo molecule count graphs as they currently rely on shape size

%% Import Simulation Data
clear all; clc; tic;
config.FilePath = "C:\dev\AcCoRD2\configs\child_grandparent.json";
config.Json = jsondecode(fileread(config.FilePath));
sim = Accord.importFiles(config.Json.SaveToFolder, [], [], false);
toc
%% Draw Shapes
render.ActiveActors = true;
render.PassiveActors = true;
Accord.plotShapes(config.FilePath, render);
view(3);
axis equal;
%% Watch Animation Live
clc;
shape3d = Shape3D('LineColorMap', hsv(2), 'FaceColorMap', hsv(2), 'EdgeAlpha', 1);
% seed, realisation, figure lims, color by actor, solid molecules, molecule size
r = Accord.initAnimateRealisation(sim, 1, 1, 5, true, true, 15, shape3d);
render.ActiveActors = true;
render.PassiveActors = false;
Accord.plotShapes(config.FilePath, render);
r = Accord.playAnimateRealisation(r, 1);

%% Save Animation as Video
clc;
shape3d = Shape3D('LineColorMap', hsv(length(sim.regions.shapes)), ...
'FaceColorMap', hsv(length(sim.regions.shapes)));
r = Accord.initAnimateRealisation(sim, 1, 1, 3.5, false, true, 15, shape3d);
%%
r.hFigure.WindowState = 'maximized';
%%
%r.hFigure.Visible = 'Off';
% It is much faster ~ 3.5 x faster to leave the figure visible during
% rendering
tic;
r = Accord.saveAnimateRealisation(r, 3, "D:\dev\videos\sim7.mp4");
toc
%% Display Regions & Actors
clc;
shape3d = Shape3D('LineColorMap', hsv(2), ...
'FaceColorMap', hsv(2), 'FaceAlpha', 0.1, 'EdgeAlpha', 1);
Accord.displayShapes(sim, 10, shape3d);

%% Plot Count For Each Passive Actor
clc;
figure
nPassiveActors = length(sim.passiveActors.shapes);
for iPassiveActor = 1:nPassiveActors
    subplot(nPassiveActors, 1, iPassiveActor);
    Accord.plotCountForPassiveActor(sim, iPassiveActor, Inf, Inf);
end

%% Plot Count
clc;
figure;
% passive actor, molecule type
Accord.plotCount(sim, 1, 1, Inf, Inf);
subplot(3, 1, 2);
Accord.plotCountForMoleculeType(sim, 1, Inf, Inf);
subplot(3, 1, 3);
Accord.plotCountForPassiveActor(sim, 3, Inf, Inf);


%%
clc; figure;
Accord.plotCountForPassiveActor(sim, 1, Inf, Inf);

%%
clc; figure;
Accord.plotCountForMoleculeType(sim, 1, Inf, Inf);

%% Force all Figures and Files To Close 
close all force
fclose('all') 

