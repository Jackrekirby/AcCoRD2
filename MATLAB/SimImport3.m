clear all;
clc;
% s = readPositionBinary("D:\dev\my_simulation\s1\r0\p0_m0_p.bin", ...
%     "D:\dev\my_simulation\s1\r0\p0_m0_c.bin")

directory = "D:\dev";
simulationName = "my_simulation";
% check if simulation directory is valid
simulationDir = directory + '\' + simulationName;
if ~exist(simulationDir, 'dir')
    error(simulationDir + " is not a valid folder directory");
end

seeds = [];
realisations = [1];
sim = [];
files = dir(simulationDir);
files = files([files.isdir]);
for iFile = 1:length(files)
    if(startsWith(files(iFile).name, 's'))
        seed = files(iFile).name(2:end);
        if(isempty(seeds) || any(seeds == str2double(seed)))
            files2 = dir(files(iFile).folder + "/" + files(iFile).name);
            files2 = files2([files2.isdir]);
            for iFile2 = 1:length(files2)
                if(startsWith(files2(iFile2).name, 'r'))
                    realisation = files2(iFile2).name(2:end);
                    if(isempty(realisations) || any(realisations == str2double(realisation)))
                        files3 = dir(files2(iFile2).folder + "\" + files2(iFile2).name);
                        for iFile3 = 1:length(files3)
                            if(endsWith(files3(iFile3).name, '.bin'))
                                totalPath = files3(iFile3).folder + "\" + files3(iFile3).name
                                sim = importBinaryFile(sim, files3(iFile3).folder, files3(iFile3).name);
                            end
                        end
                    end
                end
            end
        end
    end
end


function sim = importBinaryFile(sim, folder, file)
    fullpath = folder + "\" + file;
    % isolate the file name and split it into its key parts
    % e.g. "p5_m3_p.bin" - > {'p5', 'm3', 'p'}
    tags = split(file(1:end-4), '_')
    actorType = tags{1}(1);
    actorID = str2double(tags{1}(2:end)) + 1;
    % the first part of the file name says if the file belongs to
    % a passive or active actor, and the id of that actor
    if(actorType == 'p')
        timeOrmole = tags{2}(1);
        % if a passive actor the second part of the file name says if
        % the file if a observation time file or records the position
        % or count of a particular molecule type
        if(timeOrmole == 't')
            % read the observation time file
            sim.p(actorID).t = readTimeBinary(fullpath);
        elseif(timeOrmole == 'm')
            % the third part of the file name says if the file is
            % storing the position of number of molecules
            moleID = str2double(tags{2}(2:end)) + 1;
            fileType = tags{3}(1);
            if(fileType == 'p')
                % read the position file only if count file exists
                cFilePath = char(fullpath); cFilePath(end-4) = "c";
                if(isfile(cFilePath))
                    sim.p(actorID).m(moleID) = readPositionBinary(fullpath, cFilePath);
                end
            elseif(fileType == 'c')
                % only read count file if position file doesn't exist
                pFilePath = char(fullpath(:)); pFilePath(end-4) = "p";
                if(~isfile(pFilePath))
                    sim.p(actorID).m(moleID).c = readCountBinary(fullpath);
                end
            end
        end
    elseif(actorType == 'a')
        % To Complete
    end
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

function file = readPositionBinary(p_file_name, c_file_name)
    fileID_positions = fopen(p_file_name,'r');
    file.positions = fread(fileID_positions, [3 inf], 'double');
    
    fileID_count = fopen(c_file_name,'r');
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