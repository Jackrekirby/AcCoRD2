clear all;
clc;
% markers should use face color and alpha aswell as edge width
% switch molecules is use shapeplotter
%% Importing
clc;
% [config] = importConfig(filePath)
config = Accord2.importConfig("C:/dev/AcCoRD2/configs/all_micro_regions.json");

% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(config.SaveToFolder, 1, false);

%% Plotting
clc;
Accord2.quickPlot(data, false);

%% Initialise Video
clc;
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 2);
shapePlotters = ShapePlotter('CircleResolution', 3, 'SphereResolution', 3);
colormaps = ["hsv"];
display = [true, true, true, true, true];
showLog = false;
video = Accord2.videoCreateScene(data, config, moleculeStyle, shapePlotters, colormaps, display, showLog);

%% Watch Video Live
clc;
video = Accord2.videoLive(video, 10);

%% Record Video
clc;
video = Accord2.videoRecord(video, 10, config.SaveToFolder + "/video.mp4");