function [data] = importData(simulationDirectory, logLevel, saveData)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % accordImport.m -  imports each .bin output file in the simulation output
    %       directory (all seeds and realisations)
    
    % INPUTS
    % simulationDirectory - The directory of the of the folder containing
    %       the simulation output files
    % logLevel - The amount of user feedback as to the progress of the
    %       import. 
    %       0 = No log info, 
    %       1 = Logs Number of files imported, 
    %       2 = Logs each file imported
    % saveData - saves the data to a .mat file in the simulation directory
    
    % OUTPUTS
    % data - the simulation data from passive and active actors
    
    % IMPORTANT NOTES
    % simulations folders containing multiple seeds should do so with
    %   increasing seeds numbers from one (e.g. 1, 2, 3, 4... and not 
    %   1, 2, 7, 8 or, 6, 7, 8, 9)
    %
    % folder to data format:
    %   position files: 
    %       simulationDirectory/s#/r#/p#/m#/p.bin
    %       data.s(#).r(#).p(#).m(#).p
    %   count files: 
    %       simulationDirectory/s#/r#/p#/m#/c.bin
    %       data.s(#).r(#).p(#).m(#).c
    %   observation time files: 
    %       simulationDirectory/s#/r#/p#/t.bin
    %       data.s(#).r(#).p(#).t
    %   bit sequence files: 
    %       simulationDirectory/s#/r#/a#/b.bin
    %       data.s(#).r(#).a(#).b
    %
    %   where # is the number of a seed (s), realisation (r), 
    %   passive actor (p), active actor (a) or molecule type (m)
    
    if(logLevel > 1)
        disp("Importing files:")
    end
    
    % Check is simulation directory is valid
    if ~exist(simulationDirectory, 'dir')
        error(simulationDirectory + " is not a valid folder directory");
    end
    % Initialise empty data object
    data = [];
    
    % Get length of simulation direcotry name
    simNameLen = length(simulationDirectory) + 2;
    
    % Retrieve details of files and folders in simulation directory
    sf = dir(simulationDirectory);
    % Filter results to only folders in simulation directory
    sf = sf([sf.isdir]);
    % Log the number of files imported
    nFiles = 0;
    % For each folder in simulation directory
    for iSf = 1:length(sf)
        % Go through each seed folder (s#)
        if(startsWith(sf(iSf).name, 's'))
            % Get the seed number
            seed = str2double(sf(iSf).name(2:end));
            % Get details of files and folders in seed folder
            rf = dir(sf(iSf).folder + "/" + sf(iSf).name);
            % Filter results to only folders in seed folder
            rf = rf([rf.isdir]);
            % For each folder in seed folder
            for iRf = 1:length(rf)
                % Go through each realisation folder (r#)
                if(startsWith(rf(iRf).name, 'r'))
                    % Get the realisation number
                    realisation = str2double(rf(iRf).name(2:end));
                    % Get details of files and folders in realisation folder
                    files = dir(rf(iRf).folder + "\" + rf(iRf).name);
                    for iFile = 1:length(files)
                        % Go through .bin files
                        if(endsWith(files(iFile).name, '.bin'))
                            % Keep count of imported files
                            nFiles = nFiles + 1;
                            if(logLevel > 1)
                                filePathName = files(iFile).folder(simNameLen:end) + "\" + files(iFile).name(1:end-4);
                                disp(filePathName);
                            end
                            % Import the binary file
                            data = Accord2.importBinaryFile(data, ...
                                seed, realisation + 1, files(iFile).folder, files(iFile).name);
                        end
                    end
                end
            end
        end
    end
    
    if(logLevel > 0)
        disp("Imported " + nFiles + " .bin files");
    end
    
    % save the data to a .mat file
    if(saveData)
        saveFile = [simulationDirectory, '\data.mat'];
        save(saveFile, 'data');
        if(logLevel > 0)
            disp("Saved data to: " + saveFile);
        end
    end
end


