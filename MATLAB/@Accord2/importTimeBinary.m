function [timeData] = importTimeBinary(filePath)
    % importTimeBinary.m converts a binary file containing passive actor
    %   observation times into an array of doubles
    
    % INPUTS
    % filePath = the full file path to the binary time file
    
    % OUTPUTS
    % timeData = the time data from the file
    
    fileID = fopen(filePath,'r');
    timeData = fread(fileID, 'double');
    fclose(fileID);
end