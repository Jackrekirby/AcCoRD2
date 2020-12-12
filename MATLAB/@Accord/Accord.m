classdef Accord
    methods (Access = public, Static)
        function simulation = importFiles(directory, simulationName, ...
                seeds, realisations, trackImporting)
            arguments
                directory
                simulationName
                seeds = [];
                realisations = [];
                trackImporting = true;
            end
            simulationDir = Accord.isSimulationDirValid(directory, simulationName);
            simulation = Accord.findEachRealisationFolder(simulationDir, ...
                seeds, realisations, trackImporting);
            simulation.regions = Accord.importRegionShapes(simulationDir);
        end
        
        function r = animateRealisation(simulation, seed, realisation, ...
                figureLimits, playBackSpeed, colorByActor, shape3D)
            arguments
                simulation
                seed = 1;
                realisation = 1;
                figureLimits = 10;
                playBackSpeed = 1;
                colorByActor = true;
                shape3D = Shape3D;
            end
            r = simulation.s(seed).r(realisation);
            r.hFigure = Accord.initialiseFigure(figureLimits);
            r = Accord.initiliseMoleculePlots(r, colorByActor);
            r.hRegions = Accord.plotRegions(simulation, shape3D);
            r = Accord.plotMolecules(r, playBackSpeed);
        end
        
        function hRegions = displayRegions(simulation, figureLimits, shape3D)
            arguments
                simulation
                figureLimits = 10;
                shape3D = Shape3D();
            end
            
            hRegions.hFigure = Accord.initialiseFigure(figureLimits);
            hRegions.hPlots = Accord.plotRegions(simulation, shape3D);
            hRegions.hFigure.Visible = 'on';
        end
        
        function p = plotCountForMoleculeType(sim, moleculeType, ...
            maxAveraged, realisation)
            arguments
                sim
                moleculeType = 1;
                maxAveraged = Inf;
                realisation = 1;
            end
            
            p = Accord.putCountsIntoMatrix(sim, maxAveraged);
            hold on;
            nP = length(p);
            colors = hsv(nP);
            iM = moleculeType;
            legendLabels{nP} = "";
            legendSubset(nP) = 0;
            for iP = 1:nP
                % plot mean of all realisations
                hPlot = plot(sim.s(1).r(1).p(iP).t, mean(p(iP).m(iM).c, 2), ...
                    'Color', colors(iP, :));
                legendLabels{iP} = num2str(iP);
                legendSubset(iP) = hPlot;
                if(realisation == Inf)
                    % plot all realisations individually
                    plot(sim.s(1).r(1).p(iP).t, p(iP).m(iM).c(:, :), ...
                    'Color', colors(iP, :), 'LineStyle', ':');
                elseif(isempty(realisation))
                    % plot no realisations
                else
                    % plot given realisation
                    plot(sim.s(1).r(1).p(iP).t, p(iP).m(iM).c(:, realisation),...
                    'Color', colors(iP, :), 'LineStyle', ':');
                end
            end
            hold off;
            title("Molecule Count of Molecule Type " + moleculeType + ", Per Passive Actor");
            xlabel("time (s)");
            ylabel("count");
            legend(legendSubset, legendLabels);
        end
        
        function p = plotCountForPassiveActor(sim, passiveActor, ...
            maxAveraged, realisation)
            arguments
                sim
                passiveActor = 1;
                maxAveraged = Inf;
                realisation = 1;
            end
            
            p = Accord.putCountsIntoMatrix(sim, maxAveraged);
            hold on;
            iP = passiveActor;
            nM = length(p(iP).m);
            colors = hsv(nM);
            legendLabels{nM} = "";
            legendSubset(nM) = 0;
            for iM = 1:nM
                hPlot = plot(sim.s(1).r(1).p(iP).t, mean(p(iP).m(iM).c, 2), ...
                    'Color', colors(iM, :));
                legendLabels{iM} = num2str(iM);
                legendSubset(iM) = hPlot;
                if(realisation == Inf)
                    % plot all realisations
                    plot(sim.s(1).r(1).p(iP).t, p(iP).m(iM).c(:, :), ...
                    'Color', colors(iM, :), 'LineStyle', ':');
                elseif(isempty(realisation))
                    % plot no realisations
                else
                    % plot given realisation
                    plot(sim.s(1).r(1).p(iP).t, p(iP).m(iM).c(:, realisation),...
                    'Color', colors(iM, :), 'LineStyle', ':');
                end
            end
            hold off;
            title("Molecule Count of Passive Actor " + passiveActor + ", Per Molecule Type");
            xlabel("time (s)");
            ylabel("count");
            legend(legendSubset, legendLabels);
        end
        
        %% animateRealisation && displayRegions
        function hFigure = initialiseFigure(limits, visible)
            arguments
                limits = 10;
                visible = 'off'
            end
            hFigure = figure('visible',visible, 'Name', ...
                'Simulation Time:','NumberTitle','off');
            plot3(0, 0, 0, 'Marker', 'none');
            xlabel('x');
            ylabel('y');
            zlabel('z');
            axis equal;
            view(45,30);
            a = [-limits, limits];
            xlim(a); zlim(a); ylim(a);
        end
    end
    
    methods (Access = private, Static)
        %% importFiles
        function simulationDir = isSimulationDirValid(directory, simulationName)
            simulationDir = directory + "\" + simulationName;
            if ~exist(simulationDir, 'dir')
                error(simulationDir + " is not a valid folder directory");
            end
        end
        
        function sim = findEachRealisationFolder(simulationDir, s, r, t)
            % s = Seeds which user wishes to import
            % r = Realisations which user wished to import
            % t = Track imports
            %sf = folder containing Seed Folders
            %rf = folder containing Realisation Folders
            sim = [];
            % simulation folder has structure:
            % simulation_name/seed_no/realisation_no/binaries
            % go through each subfolder of simulation folder to import
            % files
            if(t)
                disp("Importing Files:")
            end
            sf = dir(simulationDir);
            sf = sf([sf.isdir]);
            for iSf = 1:length(sf)
                if(startsWith(sf(iSf).name, 's'))
                    seed = str2double(sf(iSf).name(2:end));
                    if(isempty(s) || any(s == seed))
                        rf = dir(sf(iSf).folder + "/" + sf(iSf).name);
                        rf = rf([rf.isdir]);
                        for iRf = 1:length(rf)
                            if(startsWith(rf(iRf).name, 'r'))
                                realisation = str2double(rf(iRf).name(2:end));
                                if(isempty(r) || any(r == realisation))
                                    files = dir(rf(iRf).folder + "\" + rf(iRf).name);
                                    for iFile = 1:length(files)
                                        if(endsWith(files(iFile).name, '.bin'))
                                            % display file paths
                                            if(t)
                                                disp(files(iFile).folder + "\" + files(iFile).name);
                                            end
                                            sim = Accord.importBinaryFile(sim, ...
                                                seed, realisation + 1, files(iFile).folder, files(iFile).name);
                                        end
                                    end
                                end
                            end
                        end
                    end
                end
            end
            if(t)
                disp("Import Complete")
            end
        end
        
        function sim = importBinaryFile(sim, sn, rn, folder, file)
            % sn = seed number, rn = realisation number
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
                    sim.s(sn).r(rn).p(actorID).t = Accord.importTimeBinary(filePath);
                elseif(timeOrmole == 'm')
                    % the third part of the file name says if the file is
                    % storing the position of number of molecules
                    moleID = str2double(tags{2}(2:end)) + 1;
                    fileType = tags{3}(1);
                    if(fileType == 'p')
                        % read the position file only if count file exists
                        cFilePath = char(filePath); cFilePath(end-4) = "c";
                        if(isfile(cFilePath))
                            sim.s(sn).r(rn).p(actorID).m(moleID) = Accord.importPositionBinary(filePath, cFilePath);
                        end
                    elseif(fileType == 'c')
                        % only read count file if position file doesn't exist
                        pFilePath = char(filePath(:)); pFilePath(end-4) = "p";
                        if(~isfile(pFilePath))
                            sim.s(sn).r(rn).p(actorID).m(moleID).c = Accord.importCountBinary(filePath);
                        end
                    end
                end
            elseif(actorType == 'a')
                % To Complete
            end
        end

        function file = importTimeBinary(filePath)
            fileID_count = fopen(filePath,'r');
            file = fread(fileID_count, 'double');
            fclose(fileID_count);
        end

        function file = importCountBinary(filePath)
            fileID_count = fopen(filePath,'r');
            % uint64 for 64 bit and uint32 for 32 bit
            file = fread(fileID_count, 'uint64');
            fclose(fileID_count);
        end

        function file = importPositionBinary(p_filePath, c_filePath)
            fileID_positions = fopen(p_filePath,'r');
            file.p = fread(fileID_positions, [3 inf], 'double')';

            fileID_count = fopen(c_filePath,'r');
            % uint64 for 64 bit and uint32 for 32 bit
            file.c = fread(fileID_count, 'uint64');

            fclose(fileID_count);
            fclose(fileID_positions);

            % calculate the cumulative count of molecules per time step
            % this is used to index the position vector
            total_count = 0;
            file.i(length(file.c) + 1, 1) = 0;
            for iCount = 1:length(file.c)
                total_count = total_count + file.c(iCount);
                file.i(iCount+1) = total_count;
            end
        end
        
        function regions = importRegionShapes(simulationDir)
            regions = jsondecode(fileread(simulationDir + "\regions.json"));
        end
        
        %% animateRealisation
        function r = initiliseMoleculePlots(r, colorByActor)
            if(colorByActor)
                colors = hsv(length(r.p));
            else
                % calculate the number of molecule types
                nMoleculeTypes = 0;
                for iP = 1:length(r.p)
                    if(length(r.p(iP).m) > nMoleculeTypes)
                        nMoleculeTypes = length(r.p(iP).m);
                    end
                end
                colors = hsv(nMoleculeTypes);
            end
            
            hold on;
            for iP = 1:length(r.p)
                % if passive actor time is not recorded than it cannot be visualised so
                % is ignored by setting its next observation time to infinite
                if(isfield(r.p(iP), 't'))
                    r.p(iP).timeIndex = 1;
                    r.observationTimes(iP) = ... 
                        r.p(iP).t(1);
                    
                    for iM = 1:length(r.p(iP).m)
                        if(colorByActor)
                            iColor = iP;
                        else
                            iColor = iM;
                        end
                        r.p(iP).m(iM).hPlot = ...
                            plot3(0, 0, 0, 'Marker', 'o', 'LineStyle', 'none', ...
                            'MarkerEdgeColor', colors(iColor, :));
                        % clear plot marker data
                        r.p(iP).m(iM).hPlot.XData = [];
                        r.p(iP).m(iM).hPlot.YData = [];
                        r.p(iP).m(iM).hPlot.ZData = [];
                    end
                else
                    r.observationTimes(iP) = Inf;
                end
            end
            hold off;
        end
        
        function r = plotMolecules(r, playBackSpeed)
            simulationTime = 0;
            % list of indicies of all the actors to render in next update
            actorsToRender = [];
            r.hFigure.Visible = 'on';
            tic;
            % keep rendering until all observations have been rendered
            while(min(r.observationTimes) ~= Inf)
                [observationTime, observationID] = min(r.observationTimes);

                % if the next actor's time is ahead of the current simulation time then
                % render all the actor observations from the current simulation time
                % before going onto the next actor
                
                if(observationTime > simulationTime)
                    % display the simulation time in the window name
                    r.hFigure.Name = "Simulation Time: " + simulationTime;

                    for i = 1:length(actorsToRender)
                        actor_id = actorsToRender(i);
                        for iM = 1:length(r.p(actor_id).m)
                            % only attempt to update plot if passive actor
                            % includes the molecule type
                            if(~isempty(r.p(actor_id).m(iM).p))
                                positions = Accord.getPositions(r.p(actor_id).m(iM), ...
                                    r.p(actor_id).timeIndex - 1);
                                r.p(actor_id).m(iM).hPlot.XData = positions(:, 1);
                                r.p(actor_id).m(iM).hPlot.YData = positions(:, 2);
                                r.p(actor_id).m(iM).hPlot.ZData = positions(:, 3);
                            end
                        end
                    end

                    % now figure is about to be updated actorsToRender can
                    % be emptied
                    actorsToRender = [];

                    % if real time is ahead of simulation time wait
                    while(simulationTime / playBackSpeed > toc)
                        pause(0.01 * ((simulationTime / playBackSpeed) - toc));
                    end
                    
                    simulationTime = observationTime;
                    drawnow limitrate;
                end

                actorsToRender = [actorsToRender, observationID];
                % update actors next observation time or set to Inf is no
                % observations left
                r.p(observationID).timeIndex = r.p(observationID).timeIndex + 1;
                if(r.p(observationID).timeIndex > size(r.p(observationID).t, 1) )
                    r.observationTimes(observationID) = Inf;
                else
                    r.observationTimes(observationID) = ... 
                        r.p(observationID).t(r.p(observationID).timeIndex);
                end
            end

            r.hFigure.Name = "Simulation Time: " + simulationTime + " (Complete)";
        end
        
        function positions= getPositions(file, index)
            positions = file.p(file.i(index)+1:file.i(index+1), :);
        end
        
        %% displayRegions
        function hPlots = plotRegions(simulation, shape3D)
            arguments
                simulation
                shape3D = Shape3D();
            end
            hPlots = shape3D.plot(simulation.regions.shapes);
        end
        
        %% plotCount
        function p = putCountsIntoMatrix(sim, maxTotalRealisations)
            k = 0; % k = nTotalRealisations
            for iS = 1:length(sim.s)
                for iR = 1:length(sim.s(iS).r)
                    if(maxTotalRealisations <= k)
                        return;
                    end
                    k = k + 1;
                    nP = length(sim.s(iS).r(iR).p);
                    for iP = 1:nP
                        nM = length(sim.s(iS).r(iR).p(iP).m);
                        for iM = 1:nM
                            p(iP).m(iM).c(:, k) = sim.s(iS).r(iR).p(iP).m(iM).c;
                            %disp("s" + iS + "r" + iR + "p" + iP + "m" + iM);
                        end
                    end
                end
            end
        end
    end
end

