function [timeData] = importTimeBinary(filePath)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
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