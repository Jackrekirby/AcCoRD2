clear all;
clc;

s = Simulation("D:\dev", "my_simulation", 'Seed', 1, 'Realisation', 0, ...
    'PlayBackSpeed', 1);

%%

sum(s.PassiveActor(1).moleType(1).count)

%%
s.initialiseFigure(10);
s.plotRegions(true);
s.plotMolecules(true);

pause(0.5);
% are all files safely closed?
close all force;
fclose('all');

%%
% add being able to plot per realisation
s.plotMoleculeCount();

%% Functions

function hPlot = plotCount(seed, realisation, passiveActor, moleculeType)
    arguments
        seed = 1;
        realisation = 0;
        passiveActor = 1;
        moleculeType = 1; % all
    end
end