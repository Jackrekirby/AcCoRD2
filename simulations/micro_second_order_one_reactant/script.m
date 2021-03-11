%% AcCoRD 2 Visualisation Script
% NOTE: To use the script 'as is' it must be placed inside the simulation 
% folder which you wish to analyse. The configuration file must be called "config.json"

%% Change Current Directory
clc;
[folder, ~, ~] = fileparts(matlab.desktop.editor.getActiveFilename);
cd(folder);
pwd % print current directory
%% Clear, Close & Add Path
clear all; clc;
close all; % close any open figures
fclose('all'); % close any open files
addpath('..\..\MATLAB'); % add access to MATLAB functions

%% Import Config, Run Simulation, Import Data
clc;
% [config] = importConfig(filePath)
config = Accord2.importConfig(pwd + "\config.json");
%% Run Config File
seeds = 1;
for i = 1:length(seeds)
    system(['accord_win64_release_matlab.bat ', num2str(seeds(i))],'-echo');
end
%% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(pwd, 1, false);

%% [hPlots] = plotMoleculeCount(data, plotMeanOnly)
clc;
Accord2.plotMoleculeCount(data, @hsv, true);

%% Video And Environment Style Arguments
clc;
moleculeStyle = struct('colormap', @hsv, 'colorMethod', 'moleculetype', 'fill', false, 'size', 3000);
shapePlotActive = ShapePlotter('EdgeWidth', 2, 'MarkerSize', 50);
shapePlotGeneral = ShapePlotter();
% [microscopic regions, microscopic surfaces, mesoscopic regions, active actors, passive actors]
shapePlotters = [shapePlotGeneral, shapePlotGeneral, shapePlotGeneral, shapePlotActive, shapePlotGeneral];
colormaps = ["winter", "hsv", "hsv", "cool", "hsv"];
display = [true, true, true, true, true];
showLog = false;

%% Plot Regions & Actors
clc;
[shapes] = Accord2.plotEnvironment(config, shapePlotters, colormaps, display, showLog);

%% Initialise Video
clc;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);
% Watch Video Live
view([0, 0]);
set(gcf,'Position',[0 0 800 800]);
video = Accord2.videoLive(video, 3, 100);

%% Record Video
clc;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);
set(gcf,'Position',[0 0 800 800]);
view([0, 0]);
%%
video = Accord2.videoRecord(video, 2, "video.mp4");


