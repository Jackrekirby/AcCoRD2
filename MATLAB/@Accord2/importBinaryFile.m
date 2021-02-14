function [data] = importBinaryFile(data, seedNo, realisationNo, folder, file)
    % importBinaryFile.m - takes a file name and works out which type of
    %   binary file it is, and then returns the converted binary file
    
    % INPUTS
    % data - the simulation data from passive and active actors
    % seedNo - the seed number which the file is in
    % realisationNo - the realisation number which the file is in
    % folder - the full folder path the file is in
    % file - the name of the file including the extension
    
    % OUTPUTS
    % data - the simulation data from passive and active actors
    
    filePath = folder + "\" + file;
    % isolate the file name and split it into its key parts
    % e.g. "p5_m3_p.bin" - > {'p5', 'm3', 'p'}
    tags = split(file(1:end-4), '_');
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
            data.s(seedNo).r(realisationNo).p(actorID).t = Accord2.importTimeBinary(filePath);
        elseif(timeOrmole == 'm')
            % the third part of the file name says if the file is
            % storing the position of number of molecules
            moleID = str2double(tags{2}(2:end)) + 1;
            fileType = tags{3}(1);
            if(fileType == 'p')
                % read the position file only if count file exists
                cFilePath = char(filePath); cFilePath(end-4) = "c";
                if(isfile(cFilePath))
                    data.s(seedNo).r(realisationNo).p(actorID).m(moleID) = Accord2.importPositionCountBinary(filePath, cFilePath);
                end
            elseif(fileType == 'c')
                % only read count file if position file doesn't exist
                pFilePath = char(filePath(:)); pFilePath(end-4) = "p";
                if(~isfile(pFilePath))
                    data.s(seedNo).r(realisationNo).p(actorID).m(moleID).c = Accord2.importCountBinary(filePath);
                end
            end
        end
    elseif(actorType == 'a')
        bitSequence = tags{2}(1);
        if(bitSequence == 'b')
            data.s(seedNo).r(realisationNo).a(actorID).b = Accord2.importBitSequenceBinary(filePath);
        end
    end
end