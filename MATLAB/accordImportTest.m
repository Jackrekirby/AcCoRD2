%% To Do
% add number of shapes to sim.regions so hsv(nshapes) can be given to
% shape3D so colour of region matches plotted line colour
% animated line?
% add import regions info message

%% Import Simulation Data
clear all;
clc;
sim = Accord.importFiles("D:\dev", "my_simulation3", [], [], true);


%% Watch Animation Live
clc;
shape3d = Shape3D('FaceAlpha', 0, 'LineColor', 'k');
r = Accord.initAnimateRealisation(sim, 1, 1, 7, true, shape3d);
r = Accord.playAnimateRealisation(r, 1);

%% Save Animation as Video
clc;
shape3d = Shape3D('FaceAlpha', 0, 'LineColor', 'k');
r = Accord.initAnimateRealisation(sim, 1, 1, 7, true, shape3d);
%%
r.hFigure.WindowState = 'maximized';
%%
r = Accord.saveAnimateRealisation(r, 1, "D:\dev\videos\sim3.mp4");
%% Display Regions
clc;
Accord.displayRegions(sim, 10);

%% Plot Count
clc;
figure;
Accord.plotCountForMoleculeType(sim, 1, Inf, Inf);
figure;
Accord.plotCountForPassiveActor(sim, 1, Inf, Inf);


%% Force all Figures and Files To Close 
close all force
fclose('all') 

