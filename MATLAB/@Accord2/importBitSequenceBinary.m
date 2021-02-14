function [bitSequenceData] = importBitSequenceBinary(filePath)
    % importTimeBinary.m converts a binary file containing the bit sequence
    %   from an active actor into an array of ints
    
    % INPUTS
    % filePath = the full file path to the binary bit sequence file
    
    % OUTPUTS
    % countData = the count data from the file
    
    fileID = fopen(filePath,'r');
    bitSequenceData = fread(fileID, 'int');
    fclose(fileID);
end