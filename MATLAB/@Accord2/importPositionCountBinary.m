function [positionCountData] = importPositionCountBinary(positionFilePath, countFilePath)
    % importPositionCountBinary.m - imports the position and count data
    %   from a position binary file and count binary file into a structure
    %   containing arrays for the position, count and the cumulative count 
    %   with each timestep (i)
    
    % INPUTS
    % positionFilePath = the full file path to the binary position file
    % countFilePath = the full file path to the binary count file
    
    % OUTPUTS
    % positionCountData = the position, count and cumulative count data
    %   from the position and count binary files
    
    % NOTES
    % The correct formating of the position data requires count data as
    % well. Therefore to import the position data the count data also needs
    % to be imported.
    
    
    fileID_positions = fopen(positionFilePath,'r');
    positionCountData.p = fread(fileID_positions, [3 inf], 'double')';

    fileID_count = fopen(countFilePath,'r');
    positionCountData.c = fread(fileID_count, 'int');

    fclose(fileID_count);
    fclose(fileID_positions);

    % calculate the cumulative count of molecules per time step
    % this is used to index the position vector
    total_count = 0;
    positionCountData.i(length(positionCountData.c) + 1, 1) = 0;
    for iCount = 1:length(positionCountData.c)
        total_count = total_count + positionCountData.c(iCount);
        positionCountData.i(iCount+1) = total_count;
    end
end