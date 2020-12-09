classdef SimImport < handle
    properties
        s
    end
    
    methods (Access = public)
        function obj = SimImport(directory, simulationName, seeds, ...
            realisations)
            arguments
                directory
                simulationName
                seeds = [];
                realisations = [];
            end
            
            simulationDir = ...
                SimImport.isSimulationDirectoryValid(directory, simulationName);
            obj.findSeeds(simulationDir, seeds);
            obj.findRealisations(simulationDir, realisations);
            obj.importAllBinaryFiles(simulationDir);
        end
    end
    
    
    methods (Access = private)
        function findSeeds(obj, simulationDir, seeds)
            if(isempty(seeds))
                seeds = SimImport.GetSuffixesFromFolderNames(simulationDir, 's');
                if(isempty(seeds))
                    warning("no seed folders exist in: " + simulationDir);
                end
            end
            
            for iSeed = 1:length(seeds)
                obj.s(iSeed).no = seeds(iSeed);
            end
        end
        
        function findRealisations(obj, simulationDir, realisations)
            % If realisations isempty all realisations in the simulation 
            % folder will be imported
            % Else all seeds will import realisations given
            
            for iSeed = 1:length(obj.s)
                if(isempty(realisations))
                    seedDir = simulationDir + '\s' + obj.s(iSeed).no;
                    if ~exist(seedDir, 'dir')
                        error(seedDir + " is not a valid folder directory");
                    end
                    realisations = SimImport.GetSuffixesFromFolderNames(seedDir, 'r');
                    if(isempty(realisations))
                        warning("no realisation folders exist in: " + seedDir);
                    else
                        for iRealisation = 1:length(realisations)
                            obj.s(iSeed).r(iRealisation).no = realisations(iRealisation);
                        end
                    end
                else 
                    for iRealisation = 1:length(realisations)
                        obj.s(iSeed).r(iRealisation).no = realisations(iRealisation);
                    end
                end
            end
        end
        
        function importAllBinaryFiles(obj, simulationDir)
             for iSeed = 1:length(obj.s)
                seedDir = simulationDir + '\s' + obj.s(iSeed).no;
                for iRealisation = 1:length(obj.s(iSeed).r)
                    realisationDir = seedDir + '\r' + ...
                         obj.s(iSeed).r(iRealisation).no;
                    obj.importBinaryFiles(realisationDir, iSeed, iRealisation);
                end
            end
        end
        
        function importBinaryFiles(obj, realisationDir, iSeed, iRealisation)
            % Find all the files and folders in the visualisation directory
            files = dir(realisationDir);
            % For each file
            for iFile = 1:length(files)
                % Sort through files for .bin files only
                filePath = files(iFile).name;
                extension = ".bin";
                if(endsWith(filePath,extension))
                    % isolate the file name and split it into its key parts
                    % e.g. "p5_m3_p.bin" - > {'p5', 'm3', 'p'}
                    fileName = filePath(1:end-4);
                    fileParts = split(fileName, '_');
                    actorType = fileParts{1}(1);
                    actorID = str2double(fileParts{1}(2:end));
                    % the first part of the file name says if the file belongs to
                    % a passive or active actor, and the id of that actor
                    if(actorType == 'p')
                        timeOrmole = fileParts{2}(1);
                        % if a passive actor the second part of the file name says if
                        % the file if a observation time file or records the position
                        % or count of a particular molecule type
                        if(timeOrmole == 't')
                            % read the observation time file
                            disp("passive actor(" + actorID + ").times");
                            obj.s(iSeed).r(iRealisation).p(actorID + 1).t = ...
                            SimImport.readTimeBinary(files(iFile).folder + "\" + files(iFile).name);
                        elseif(timeOrmole == 'm')
                            % the third part of the file name says if the file is
                            % storing the position of number of molecules
                            moleID = str2double(fileParts{2}(2:end));
                            fileType = fileParts{3}(1);
                            if(fileType == 'p')
                                % read the position file only if count file exists
                                if(isfile(files(iFile).folder + "\" + files(iFile).name(1:end-5) + "c.bin"))
                                    disp("passive actor(" + actorID + ").moletype(" + moleID + ").position");
                                    disp("passive actor(" + actorID + ").moletype(" + moleID + ").count");
                                    obj.s(iSeed).r(iRealisation).p(actorID + 1).m(moleID + 1) = ...
                                        SimImport.readPositionBinary(files(iFile).folder + "\" + files(iFile).name(1:end-5));
                                end
                            elseif(fileType == 'c')
                                % only read count file if position file doesn't exist
                                if(~isfile(files(iFile).folder + "\" + files(iFile).name(1:end-5) + "p.bin"))
                                    disp("passive actor(" + actorID + ").moletype(" + moleID + ").count");
                                    obj.s(iSeed).r(iRealisation).p(actorID + 1).m(moleID + 1).c = ...
                                        SimImport.readCountBinary(files(iFile).folder + "\" + files(iFile).name);
                                end
                            end
                        end
                    elseif(actorType == 'a')
                        % To Complete
                    end
                end
            end
        end
    end
    
    methods(Access = private, Static)
        function simulationDir = isSimulationDirectoryValid(directory, simulationName)
            % check if simulation directory is valid
            simulationDir = directory + '\' + simulationName;
            if ~exist(simulationDir, 'dir')
                error(simulationDir + " is not a valid folder directory");
            end
        end
        
        function suffixes = GetSuffixesFromFolderNames(directory, folderPrefix)
            nSuffixes = 0;
            suffixes = [];
            % get all folders in simulation directory
            files = dir(directory);
            files = files([files.isdir]);
            for iFiles = 1 : length(files)
                % if folder prefix is 's' then folder is a seed folder
                if(startsWith(files(iFiles).name, folderPrefix))
                    nSuffixes = nSuffixes + 1;
                    % get the seed number
                    suffixes(nSuffixes) = str2double(files(iFiles).name(2:end));
                end
            end
        end
        
        function file = readTimeBinary(file_name)
            fname = file_name;
            fileID = fopen(fname,'r');
            file = fread(fileID, 'double');
            fclose(fileID);
        end

        function file = readCountBinary(file_name)
            fname = file_name;
            fileID = fopen(fname,'r');
            % uint64 for 64 bit and uint32 for 32 bit
            file = fread(fileID, 'uint64');
            fclose(fileID);
        end

        function file = readPositionBinary(file_name)
            fname_p = file_name + "p.bin";
            fileID_p = fopen(fname_p,'r');
            file.p = fread(fileID_p, [3 inf], 'double');

            fname_c = file_name + "c.bin";
            fileID_c = fopen(fname_c,'r');
            % uint64 for 64 bit and uint32 for 32 bit
            file.c = fread(fileID_c, 'uint64');

            fclose(fileID_c);
            fclose(fileID_p);

            % calculate the cumulative count of molecules per time step
            % this is used to index the position vector
            total_count = 0;
            file.i(length(file.c) + 1) = 0;
            for iCount = 1:length(file.c)
                total_count = total_count + file.c(iCount);
                file.i(iCount+1) = total_count;
            end
        end
    end
end

