classdef Accord2
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
        [video] = videoCreateFigure(video)
        [positions] = getMoleculePositions(moleculeType, timestep)
        [shapes] = videoPlotRegionsAndActors(config, shapePlotters, colormaps, display, showLog)
    end
end

