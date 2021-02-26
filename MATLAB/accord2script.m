clear all;
clc;
% markers should use face color and alpha aswell as edge width
% switch molecules is use shapeplotter
%% Importing
clc;
% [config] = importConfig(filePath)
configFolderPath = [pwd, '\..\configs\']; % path to configuration folder
config = Accord2.importConfig(configFolderPath + "micro_sphere_cylinder.json");

%% [data] = importData(simulationDirectory, logImporting, saveData)
clc;
simsFolderPath = [pwd, '\..\simulations\']; % path to simulations folder
data = Accord2.importData([simsFolderPath, config.SaveToFolder], 1, false);

%% Count Plotting
clc;
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
video = Accord2.videoRecord(video, 10, config.SaveToFolder + "/video.mp4");

%% Plot Regions & Actors
clc;

[shapes] = Accord2.plotEnvironment(config, shapePlotters, colormaps, display, showLog);