clear all;
clc;

%% Importing
clc;
% [config] = importConfig(filePath)
config = Accord2.importConfig("C:\dev\AcCoRD2\configs\narrow_box_tube.json");

% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(config.SaveToFolder, 1, false);

%% Plotting
clc;
Accord2.quickPlot(data, false);

%% Live Video
clc;
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 10);
video = Accord2.videoWatch(data, moleculeStyle, 0);

%% Record Video