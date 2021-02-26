%% AcCoRD 2 Visualisation Script
% NOTE: To use the script 'as is' it must be placed inside the simulation 
% folder which you wish to analyse. The configuration file must be called "config.json"

%% Clear, Close & Add Path
clear all; clc;
close all; % close any open figures
fclose('all'); % close any open files
addpath('..\..\MATLAB'); % add access to MATLAB functions
%% Run Config File
system('accord_win64_release.bat','-echo');

%% [config] = importConfig(filePath)
config = Accord2.importConfig(pwd + "\config.json");

%% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(pwd, 1, false);

%% [hPlots] = plotMoleculeCount(data, plotMeanOnly)
Accord2.plotMoleculeCount(data, false);

%% Video And Environment Style Arguments
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 10);
shapePlotters = ShapePlotter('CircleResolution', 3, 'SphereResolution', 3);
colormaps = ["hsv", "hsv", "hsv", "hsv", "hsv"];
display = [true, true, true, true, true];
showLog = false;

%% Plot Regions & Actors
[shapes] = Accord2.plotEnvironment(config, shapePlotters, colormaps, display, showLog);

%% Initialise Video
clc;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);
view([10 10]);

% Watch Video Live
video = Accord2.videoLive(video, 10, 100);

%% Record Video
video = Accord2.videoRecord(video, 10, "/video.mp4");

