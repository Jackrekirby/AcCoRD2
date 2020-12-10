%% To Do
% add number of shapes to sim.regions so hsv(nshapes) can be given to
% shape3D so colour of region matches plotted line colour
% animated line?

%% Import Simulation Data
clear all;
clc;
sim = Accord.importFiles("D:\dev", "my_simulation", [], [], true);

%% Animate Realisation
clc;
% animateRealisation(simulation, seed, realisation, ...
% figureLimits, playBackSpeed, colorByActor, shape3D)

shape3d = Shape3D('FaceAlpha', 0, 'LineColor', 'k');
r = Accord.animateRealisation(sim, 1, 1, 10, 1, false, shape3d);

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

