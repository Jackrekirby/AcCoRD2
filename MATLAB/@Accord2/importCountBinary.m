function [countData] = importCountBinary(filePath)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % importTimeBinary.m converts a binary file containing the molecule count
    %   of a molecule type observed by a passive actor into an array of
    %   ints
    
    % INPUTS
    % filePath = the full file path to the binary count file
    
    % OUTPUTS
    % countData = the count data from the file
    
    fileID = fopen(filePath,'r');
    countData = fread(fileID, 'int');
    fclose(fileID);
end