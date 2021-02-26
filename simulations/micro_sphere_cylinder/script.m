%% AcCoRD 2 Visualisation Script
% This script must be placed inside the simulation folder which you wish to
% post process. The configuration file name and simulation folder name must
% be identical as well.
% A custom script could be placed elsewhere and use different names, but for ease of
% use this script was designed so the configuration and simulation data can be
% found automatically.

clear all;
clc;
addpath('..\..\MATLAB'); % add access to MATLAB functions
%% [config] = importConfig(filePath)
clc;
configFilePath = [pwd, '\..\..\configs\', getConfigName()];
config = Accord2.importConfig(configFilePath);

%% [data] = importData(simulationDirectory, logImporting, saveData)
clc;
simsFolderPath = pwd; % path to simulations folder
data = Accord2.importData(simsFolderPath, 1, false);

%% Count Plotting
clc; 
% quickPlot(data, plotMeanOnly)
Accord2.quickPlot(data, false);

%% Video And Environment Style Arguments
clc;
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 10);
shapePlotters = ShapePlotter('CircleResolution', 3, 'SphereResolution', 3);
colormaps = ["hsv", "hsv", "hsv", "hsv", "hsv"];
display = [true, true, true, true, true];
showLog = false;

%% Initialise Video
clc;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);
view([10 10]);
% Watch Video Live
clc;
video = Accord2.videoLive(video, 10, 100);

%% Record Video
clc;
video = Accord2.videoRecord(video, 10, "/video.mp4");

%% Plot Regions & Actors
clc;
[shapes] = Accord2.plotEnvironment(config, shapePlotters, colormaps, display, showLog);

%% Get the config file name from the current folder name
function configName = getConfigName()
    currentDirectory = pwd;
    idx = strfind(currentDirectory,'\') ;
    configName = [currentDirectory(idx(end)+1:end), '.json'];
end