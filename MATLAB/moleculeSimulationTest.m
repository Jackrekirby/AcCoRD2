clear all;
clc;

s = Simulation("D:\dev", "my_simulation", 'Seed', 1, 'Realisation', 0, ...
    'PlayBackSpeed', 0.2);

s.initialiseFigure(10);
s.plotRegions(true);
s.plotMolecules(true);

pause(0.5);
% are all files safely closed?
close all force;
fclose('all');

%%

s.plotMoleculeCount();