clear all;
clc;

%% Importing
clc;
% [config] = importConfig(filePath)
config = Accord2.importConfig("C:/dev/AcCoRD2/configs/narrow_box_tube.json");

% [data] = importData(simulationDirectory, logImporting, saveData)
data = Accord2.importData(config.SaveToFolder, 1, false);

%% Plotting
clc;
Accord2.quickPlot(data, false);

%% Initialise Video
clc;
moleculeStyle = struct('colorMethod', 'actor', 'fill', true, 'size', 2);
video = Accord2.videoCreateScene(data, config, moleculeStyle);

%% Watch Video Live
clc;
video = Accord2.video(video, 10);

%% Record Video
clc;
video = Accord2.videoRecord(video, 10, config.SaveToFolder + "/video.mp4");