clear all;
clc;

a = SimImport2("D:\dev", "my_simulation")

%%
s = ImportSimulationFiles("D:\dev", "my_simulation");

%% Functions

function s = ImportSimulationFiles(directory, simulationName, seeds, realisations, ...
    passiveActors, activeActors, moleculeTypes, importPositions, importCounts, ...
    importTimes)
    arguments
        directory
        simulationName
        seeds = [];
        realisations = [];
        passiveActors = []; % have option for none if moleculeTypes = []
        activeActors = []; % have option for none
        moleculeTypes = [];
        importPositions = true;
        importCounts = true;
        importTimes = true;
    end
    
    % check if simulation directory is valid
    simulationDir = directory + '\' + simulationName;
    if ~exist(simulationDir, 'dir')
        error(simulationDir + " is not a valid folder directory");
    end
    
    % If seeds isempty all seeds in the simulation folder will be imported
    if(isempty(seeds))
        seeds = GetSuffixesFromFolderNames(simulationDir, 's');
        if(isempty(seeds))
            warning("no seed folders exist in: " + simulationDir);
        end
    end
    
    % If realisations isempty all realisations in the simulation folder will be imported
    % Else all seeds will import realisations given
    if(isempty(realisations))
        for iSeed = 1:length(seeds)
            seedDir = simulationDir + '\s' + seeds(iSeed);
            if ~exist(seedDir, 'dir')
                error(seedDir + " is not a valid folder directory");
            end
            realisations = GetSuffixesFromFolderNames(seedDir, 'r');
            if(isempty(realisations))
                warning("no realisation folders exist in: " + seedDir);
            else
                realisationsPerSeed{iSeed} = realisations;
            end
        end
    else
        realisationsPerSeed{length(seeds)} = realisations;
    end
    
    for iSeed = 1:length(seeds)
        s.seeds(iSeed).no = seeds(iSeed);
        for iRealisation = 1:length(realisationsPerSeed(iSeed))
            s.seeds(iSeed).realisations(iRealisation).no = realisationsPerSeed{iSeed};
        end
    end
    
    for iSeed = 1:length(s.seeds)
        seedDir = simulationDir + '\s' + s.seeds(iSeed).no
        for iRealisation = 1:length(s.seeds(iSeed).realisations.no)
            realisationDir = seedDir + '\r' + ...
                 s.seeds(iSeed).realisations.no(iRealisation);
             
            realisationDir
            
            s = readBinaryFiles(s, realisationDir)
        end
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

function s = readBinaryFiles(s, realisationDir)
    % Find all the files and folders in the visualisation directory
    files = dir(realisationDir);
    % For each file
    for i = 1:length(files)
        % Sort through files for .bin files only
        filePath = files(i).name;
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
                    s.passiveActor(actorID + 1).times = ...
                    Simulation.readTimeBinary(files(i).folder + "\" + files(i).name);
                elseif(timeOrmole == 'm')
                    % the third part of the file name says if the file is
                    % storing the position of number of molecules
                    moleID = str2double(fileParts{2}(2:end));
                    fileType = fileParts{3}(1);
                    if(fileType == 'p')
                        % read the position file only if count file exists
                        if(isfile(files(i).folder + "\" + files(i).name(1:end-5) + "c.bin"))
                            disp("passive actor(" + actorID + ").moletype(" + moleID + ").position");
                            disp("passive actor(" + actorID + ").moletype(" + moleID + ").count");
                            passiveActor(actorID + 1).moleType(moleID + 1) = ...
                                Simulation.readPositionBinary(files(i).folder + "\" + files(i).name(1:end-5));
                        end
                    elseif(fileType == 'c')
                        % only read count file if position file doesn't exist
                        if(~isfile(files(i).folder + "\" + files(i).name(1:end-5) + "p.bin"))
                            disp("passive actor(" + actorID + ").moletype(" + moleID + ").count");
                            passiveActor(actorID + 1).moleType(moleID + 1).count = ...
                                Simulation.readCountBinary(files(i).folder + "\" + files(i).name);
                        end
                    end
                end
            elseif(actorType == 'a')
                % To Complete
            end
        end
    end
    disp("Finished Importing Bin Files");
end

function file = readTimeBinary(file_name)
    fname_count = file_name;
    fileID_count = fopen(fname_count,'r');
    file = fread(fileID_count, 'double');
    fclose(fileID_count);
end

function file = readCountBinary(file_name)
    fname_count = file_name;
    fileID_count = fopen(fname_count,'r');
    % uint64 for 64 bit and uint32 for 32 bit
    file = fread(fileID_count, 'uint64');
    fclose(fileID_count);
end

function file = readPositionBinary(file_name)
    fname_positions = file_name + "p.bin";
    fileID_positions = fopen(fname_positions,'r');
    file.positions = fread(fileID_positions, [3 inf], 'double');

    fname_count = file_name + "c.bin";
    fileID_count = fopen(fname_count,'r');
    % uint64 for 64 bit and uint32 for 32 bit
    file.count = fread(fileID_count, 'uint64');

    fclose(fileID_count);
    fclose(fileID_positions);

    % calculate the cumulative count of molecules per time step
    % this is used to index the position vector
    total_count = 0;
    file.index(length(file.count) + 1) = 0;
    for i = 1:length(file.count)
        total_count = total_count + file.count(i);
        file.index(i+1) = total_count;
    end
end

function data = GetPositions(file, index)
    data = file.positions(:, file.index(index)+1:file.index(index+1));
end