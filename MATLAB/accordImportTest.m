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

%% Import Simulation Data
clear all;
clc;
tic;
sim = Accord.importFiles("D:\dev", "my_simulation4", [], [], false);
toc
%% Watch Animation Live
clc;
shape3d = Shape3D('FaceAlpha', 0.01, 'LineColorMap', hsv(length(sim.regions.shapes)), ...
'FaceColorMap', hsv(length(sim.regions.shapes)));
% color by actor
r = Accord.initAnimateRealisation(sim, 1, 1, 1, false, shape3d);
r = Accord.playAnimateRealisation(r, 1);

%% Save Animation as Video
clc;
shape3d = Shape3D('FaceAlpha', 0);
r = Accord.initAnimateRealisation(sim, 1, 1, 7, false, shape3d);
%%
r.hFigure.WindowState = 'maximized';
%%
r = Accord.saveAnimateRealisation(r, 1, "D:\dev\videos\sim3.mp4");
%% Display Regions & Actors
clc;
Accord.displayShapes(sim, 10);

%% Plot Count
clc;
figure;
subplot(3, 1, 1);
% passive actor, molecule type
Accord.plotCount(sim, 1, 2, Inf, Inf);
subplot(3, 1, 2);
Accord.plotCountForMoleculeType(sim, 3, Inf, Inf);
subplot(3, 1, 3);
Accord.plotCountForPassiveActor(sim, 1, Inf, Inf);


%% Force all Figures and Files To Close 
close all force
fclose('all') 

