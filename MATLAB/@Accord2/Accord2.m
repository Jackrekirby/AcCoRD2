classdef Accord2
    methods (Static)
        % User Functions
        %   Data Importing
        [data] = importData(simulationDirectory, logImporting, saveData)
        [config] = importConfig(filePath)
        %   Molecule Plotting
        quickPlot(data, plotMeanOnly)
        %   Video Making
        [video] = videoWatch(data, moleculeStyle, shape3D)
        
        % Developer Functions
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
        
    end
end

