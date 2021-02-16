classdef Accord2
    methods (Static)
        % User Functions ==================================================
        %   Data Importing
        [data] = importData(simulationDirectory, logImporting, saveData)
        [config] = importConfig(filePath)
        %   Molecule Plotting
        quickPlot(data, plotMeanOnly)
        %   Video Making
        [video] = videoCreateScene(data, config, moleculeStyle, shapePlotters, colormap, display, showLog)
        [shapes] = videoPlotRegionsAndActors(config, render, shapePlotters, colormap, display, showLog)
        [video] = videoLive(video, playBackSpeed)
        [video] = videoRecord(video, playBackSpeed, filePath)
        
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
        
    end
end

