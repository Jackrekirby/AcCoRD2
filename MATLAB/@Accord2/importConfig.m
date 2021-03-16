function [config] = importConfig(filePath)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % importConfig.m - reads the configuration file, and converts it from
    %   JSON format to a struct
    
    % INPUTS
    % filePath - the relative or absolute path to the configuration file
    
    % OUTPUTS
    % config - the configuration file data as a struct
    
    config = jsondecode(fileread(filePath));
end