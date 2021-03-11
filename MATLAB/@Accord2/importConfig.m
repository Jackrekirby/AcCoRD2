function [config] = importConfig(filePath)
    % importConfig.m - reads the configuration file, and converts it from
    %   JSON format to a struct
    
    % INPUTS
    % filePath - the relative or absolute path to the configuration file
    
    % OUTPUTS
    % config - the configuration file data as a struct
    
    config = jsondecode(fileread(filePath));
end