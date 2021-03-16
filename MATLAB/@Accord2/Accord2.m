classdef Accord2
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
    methods (Static)
        % User Functions ==================================================
        %   Data Importing
        [data] = importData(simulationDirectory, logImporting, saveData)
        [config] = importConfig(filePath)
        %   Molecule Plotting
        [hPlots] = plotMoleculeCount(data, colormap, plotMeanOnly)
        %   Video Making
        [video] = videoCreateScene(data, config, moleculeStyle, shapePlotters, colormap, display, showLog)
        [video] = videoLive(video, playBackSpeed, endTime)
        [video] = videoRecord(video, playBackSpeed, filePath)
        [hFigure] = plotEnvironment(config, shapePlotters, colormaps, display, showLog)
        
        % Developer Functions =============================================
        %   Data Importing
        [data] = importBinaryFile(data, seedNo, realisationNo, folder, file)
        [timeData] = importTimeBinary(filePath)
        [countData] = importCountBinary(filePath)
        [positionCountData] = importPositionCountBinary(positionFilePath, countFilePath)
        [bitSequenceData] = importBitSequenceBinary(filePath)
        %   Molecule Plotting
        [counts] = groupMoleculeCounts(data)
        %   Video Making
        [video] = videoCreateMoleculePlots(video, moleculeStyle)
        [positions] = getMoleculePositions(moleculeType, timestep)
        [shapes] = videoPlotRegionsAndActors(config, shapePlotters, colormaps, display, showLog)
    end
end

