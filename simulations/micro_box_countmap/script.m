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
% Run Config File
%system('accord_win64_release_no_pause.bat','-echo');
% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(pwd, 1, false);

%% [hPlots] = plotMoleculeCount(data, plotMeanOnly)
clc;
Accord2.plotMoleculeCount(data, true);
ylim([0, 1000]);
axis square;

%% Video And Environment Style Arguments
clc;
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 10);
shapePlotters = ShapePlotter('CircleResolution', 3, 'SphereResolution', 3);
% [microscopic regions, microscopic surfaces, mesoscopic regions, active actors, passive actors]
colormaps = ["hsv", "hsv", "hsv", "hsv", "hsv"];
display = [true, true, true, true, true];
showLog = false;

%% Plot Regions & Actors
clc;
[shapes] = Accord2.plotEnvironment(config, shapePlotters, colormaps, display, showLog);

%% Initialise Video
clc;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);
view([10 10]);

% Watch Video Live
video = Accord2.videoLive(video, 10, 100);

%% Record Video
video = Accord2.videoRecord(video, 10, "/video.mp4");

