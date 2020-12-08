clear all;
clc;

s = Simulation("D:\dev", "my_simulation", 'Seed', 1, 'Realisation', 0, ...
    'PlayBackSpeed', 0.8);

s.initialiseFigure(10);
s.plotRegions(true);
s.plotMolecules();