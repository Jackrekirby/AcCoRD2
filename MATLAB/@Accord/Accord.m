classdef Accord
    methods (Access = public, Static)
        function simulation = importFiles(simulationDir, ...
                seeds, realisations, trackImporting)
            arguments
                simulationDir
                seeds = [];
                realisations = [];
                trackImporting = true;
            end
            if(trackImporting)
                disp("Importing Files:")
            end
            Accord.isSimulationDirValid(simulationDir);           
            simulation = Accord.findEachRealisationFolder(simulationDir, ...
                seeds, realisations, trackImporting);
%             simulation.regions = Accord.importRegionShapes(simulationDir, trackImporting);
%             simulation.subvolumes = Accord.importSubvolumeShapes(simulationDir, trackImporting);
%             simulation.passiveActors = Accord.importPassiveActorShapes(simulationDir, trackImporting);
%             simulation.activeActors = Accord.importActiveActorShapes(simulationDir, trackImporting);
            if(trackImporting)
                disp("Import Complete")
            end
        end
        
        function r = initAnimateRealisation(simulation, seed, realisation, ...
                figureLimits, colorByActor, solidMolecules, moleculeSize, shape3D)
            arguments
                simulation
                seed = 1;
                realisation = 1;
                figureLimits = 10;
                colorByActor = true;
                solidMolecules = true;
                moleculeSize = 10;
                shape3D = Shape3D;
            end
            r = simulation.s(seed).r(realisation);
            r.hFigure = Accord.initialiseFigure(figureLimits, 'on');
            r = Accord.initiliseMoleculePlots(r, colorByActor, ...
                solidMolecules, moleculeSize);
            %r.hRegions = Accord.plotRegions(simulation, shape3D);
            %r.hRegions = Accord.plotSubvolumes(simulation, shape3D);
            %r.hPassiveActors = Accord.plotPassiveActors(simulation, shape3D);
            %r.hActiveActors = Accord.plotActiveActors(simulation, shape3D);
        end
        
        function r = playAnimateRealisation(r, playBackSpeed)
            arguments
                r
                playBackSpeed = 1;
            end
            r = Accord.plotMolecules(r, playBackSpeed);
        end
        
        function r = saveAnimateRealisation(r, playBackSpeed, path)
            arguments
                r
                playBackSpeed = 1;
                path = 'simulation_video.mp4';
            end
            r = Accord.saveMolecules(r, playBackSpeed, path);
         end
        
        % r not being returned
        function hShapes = displayShapes(simulation, figureLimits, shape3D)
            arguments
                simulation
                figureLimits = 10;
                shape3D = Shape3D();
            end
            
            hShapes.hFigure = Accord.initialiseFigure(figureLimits);
            r.hRegions = Accord.plotRegions(simulation, shape3D);
            %r.hSubvolumes = Accord.plotSubvolumes(simulation, shape3D);
            r.hPassiveActors = Accord.plotPassiveActors(simulation, shape3D);
            r.hActiveActors = Accord.plotActiveActors(simulation, shape3D);
            hShapes.hFigure.Visible = 'on';
        end
        
        function p = plotCountForMoleculeType(sim, moleculeType, ...
            maxAveraged, realisation)
            arguments
                sim
                moleculeType = 1;
                maxAveraged = Inf;
                realisation = Inf;
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
            leg = legend(legendSubset, legendLabels);
            title(leg,'Passive Actor');
        end
        
        function p = plotCount(sim, passiveActor, moleculeType, ...
            maxAveraged, realisation)
            arguments
                sim
                passiveActor = 1;
                moleculeType = 1;
                maxAveraged = Inf;
                realisation = Inf;
            end
            
            p = Accord.putCountsIntoMatrix(sim, maxAveraged);
            hold on;
            nP = length(p);
            colors = hsv(nP);
            iM = moleculeType;
            iP = passiveActor;
            % plot mean of all realisations
            hPlot = plot(sim.s(1).r(1).p(iP).t, mean(p(iP).m(iM).c, 2), ...
                'Color', colors(iP, :));
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
            hold off;
            title("Molecule Count of Molecule Type " + moleculeType + ...
                ", for Passive Actor " + passiveActor);
            xlabel("time (s)");
            ylabel("count");
        end
        
        function p = plotCountForPassiveActor(sim, passiveActor, ...
            maxAveraged, realisation)
            arguments
                sim
                passiveActor = 1;
                maxAveraged = Inf;
                realisation = Inf;
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
            leg = legend(legendSubset, legendLabels);
            title(leg,'Molecule Types');
        end
        
        function plotShapes(configFilePath, render)
            s = jsondecode(fileread(configFilePath));
            hold on;
            % Region Names
            if(isfield(s, "MesoscopicRegions"))
                nMesoscopicRegions = length(s.MesoscopicRegions);
                 mesoscopicRegionNames(nMesoscopicRegions) = "";
                 for i = 1:length(s.MesoscopicRegions)
                    mesoscopicRegionNames(i) = s.MesoscopicRegions(i).Name;
                end
            else
                nMesoscopicRegions = 0;
                 mesoscopicRegionNames = "";
            end
           
            
            if(isfield(s, "MicroscopicRegions"))
                nMicroscopicRegions = length(s.MicroscopicRegions);
                microscopicRegionNames(nMicroscopicRegions) = "";
                for i = 1:nMicroscopicRegions
                microscopicRegionNames(i) = s.MicroscopicRegions(i).Name;
                end
            else
                nMicroscopicRegions = 0;
                microscopicRegionNames = "";
            end

            % Mesoscopic Regions
            if(isfield(s, "MesoscopicRegions"))
                mesoShape3D = Shape3D('FaceColorMap', autumn(nMesoscopicRegions), ...
                    'LineColorMap', autumn(nMesoscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
                for i = 1:nMesoscopicRegions
                    r = s.MesoscopicRegions(i);
                    disp("Plot Mesoscopic Region");
                    mesoShape3D.plotBox(r.Origin, r.SubvolumeLength * r.NumberOfSubvolumes);
                end
            end
             % MicroscopicSurfaces
            if(isfield(s, "MicroscopicSurfaces"))
                nMicroscopicSurfaces = length(s.MicroscopicSurfaces);
                microSurfShape3D = Shape3D('FaceColorMap', winter(nMicroscopicSurfaces), ...
                    'LineColorMap', autumn(nMicroscopicSurfaces), 'FaceAlpha', 0, 'EdgeAlpha', 1);
                for i = 1:nMicroscopicSurfaces
                    r = s.MicroscopicSurfaces(i);
                    disp("Plot Microscopic Surface");
                    microSurfShape3D.plotShape(r.Shape);
                end
            end
            % Microscopic Regions
            if(isfield(s, "MicroscopicRegions"))
                microShape3D = Shape3D('FaceColorMap', winter(nMicroscopicRegions), ...
                    'LineColorMap', winter(nMicroscopicRegions), 'FaceAlpha', 0, 'EdgeAlpha', 1);
                for i = 1:nMicroscopicRegions
                    r = s.MicroscopicRegions(i);
                    disp("Plot Microscopic Region");
                    microShape3D.plotShape(r.Shape);
                end
            end
            % Active Actors
            if(render.ActiveActors && isfield(s, "ActiveActors"))
                nActiveActors = length(s.ActiveActors);
                activeActorShape3D = Shape3D('FaceColorMap', spring(nActiveActors), ...
                    'LineColorMap', spring(nActiveActors), 'EdgeAlpha', 0);
                for i = 1:nActiveActors
                    r = s.ActiveActors(i);
                    if(iscell(r))
                        r = r{1};
                    end
                    if(isfield(r, 'Shape'))
                        disp("Plot Active Actor");
                        activeActorShape3D.plotShape(r.Shape);
                    elseif(isfield(r, 'RegionsToActIn'))   
                        for j = 1:length(r.RegionsToActIn)
                            regionToActIn = r.RegionsToActIn(j);
                            [~, mesoID] = find(mesoscopicRegionNames == regionToActIn);
                            if(~isempty(mesoID))
                                rr = s.MesoscopicRegions(mesoID);
                                disp("Plot Mesoscopic Active Actor");
                                activeActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                            else
                                [~, microID] = find(microscopicRegionNames == regionToActIn);
                                if(~isempty(microID))
                                    disp("Plot Microscopic Active Actor");
                                    activeActorShape3D.plotShape(s.MicroscopicRegions(microID).Shape);
                                else
                                    warning("No region name matched");
                                end
                            end
                        end
                    end
                end
            end
            % Passive Actors
            if(render.PassiveActors && isfield(s, "PassiveActors"))
                nPassiveActors = length(s.PassiveActors);
                passiveActorShape3D = Shape3D('FaceColorMap', summer(nPassiveActors), ...
                    'LineColorMap', summer(nPassiveActors), 'EdgeAlpha', 0);
                for i = 1:nPassiveActors
                    r = s.PassiveActors(i);
                    if(isfield(r, 'Shape'))
                        disp("Plot Passive Actor");
                        passiveActorShape3D.plotShape(r.Shape);
                    elseif(isfield(r, 'RegionsToObserve'))   
                        for j = 1:length(r.RegionsToObserve)
                            RegionsToObserve = r.RegionsToObserve(j);
                            [~, mesoID] = find(mesoscopicRegionNames == RegionsToObserve);
                            if(~isempty(mesoID))
                                rr = s.MesoscopicRegions(mesoID);
                                disp("Plot Mesoscopic Passive Actor");
                                passiveActorShape3D.plotBox(rr.Origin, rr.SubvolumeLength * rr.NumberOfSubvolumes);
                            else
                                [~, microID] = find(microscopicRegionNames == RegionsToObserve);
                                if(~isempty(microID))
                                    disp("Plot Microscopic Passive Actor");
                                    passiveActorShape3D.plotShape(s.MicroscopicRegions(microID).Shape);
                                else
                                    warning("No region name matched");
                                end
                            end
                        end
                    end
                end
            end
            hold off;
            view(3);
            axis equal;
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
        function simulationDir = isSimulationDirValid(simulationDir)
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
            sf = dir(simulationDir);
            sf = sf([sf.isdir]);
            nFiles = 0;
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
                                            nFiles = nFiles + 1;
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
            disp("Imported " + nFiles + " .bin files");
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
        
        %% animateRealisation
        function r = initiliseMoleculePlots(r, colorByActor, ...
                solidMolecules, moleculeSize)
            
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
                            scatter3(0, 0, 0, 'Marker', 'o', ...
                            'MarkerEdgeColor', colors(iColor, :), ...
                            'MarkerFaceColor', colors(iColor, :),...
                            'SizeData', moleculeSize, ...
                            'MarkerFaceAlpha', solidMolecules);
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
            
            tic;
            % keep rendering until all observations have been rendered
            while(min(r.observationTimes) ~= Inf)
                % if simulation is behind real time then skip frames
                if(simulationTime / playBackSpeed < toc)
                    while(simulationTime / playBackSpeed < toc)
                        [observationTime, observationID] = min(r.observationTimes);
                        % Skip all the observations at a single time, before
                        % rechecking if simulation time is ahead of real time
                        while(observationTime == simulationTime)
                            r.p(observationID).timeIndex = r.p(observationID).timeIndex + 1;
                            if(r.p(observationID).timeIndex > size(r.p(observationID).t, 1) )
                                r.observationTimes(observationID) = Inf;
                            else
                                r.observationTimes(observationID) = ... 
                                    r.p(observationID).t(r.p(observationID).timeIndex);
                            end
                            [observationTime, observationID] = min(r.observationTimes);
                        end
                        simulationTime = observationTime;
                    end
                else
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
            end
            
            r.hFigure.Name = "Simulation Complete";
        end
        
        function r = saveMolecules(r, playBackSpeed, savePath)
            
            r.waitbar = waitbar(0, 'Rendering Simulation', 'Name', savePath);
            
            simulationTime = 0;
            % list of indicies of all the actors to render in next update
            actorsToRender = [];
            
            % TO DO: preallocate frames by calculating number of unique times
            frames(1) = getframe(gcf);
            frameNo = 1;
            possibleFrames = 1;
            iFrame = 1;
            tic;
            
            % Work out the number of frames
            lastObservationTime = 0;
            for iObserver = 1:length(r.p)
                allObservationTimes = [r.p(iObserver).t, r.p(iObserver).t];
                if(lastObservationTime < r.p(iObserver).t(end))
                    lastObservationTime = r.p(iObserver).t(end);
                end
            end
            % If the calculated frame rate > 30 then skip frames to get
            % frame rate <= 30
            nFrames = length(unique(allObservationTimes));
            frameRate = 1 / ((lastObservationTime / playBackSpeed) / nFrames);
            saveEveryNFrame = 1;
            if(frameRate > 30)
                saveEveryNFrame = frameRate / 30
                newFrameRate = frameRate / saveEveryNFrame;
                disp("Frame Rate Capped From: " + frameRate + ", to: " + newFrameRate);
                frameRate = newFrameRate;
            end
            
            % keep rendering until all observations have been rendered
            while(min(r.observationTimes) ~= Inf)
                [observationTime, observationID] = min(r.observationTimes);
                % if the next actor's time is ahead of the current simulation time then
                % render all the actor observations from the current simulation time
                % before going onto the next actor
                if(observationTime > simulationTime)
                    if(frameNo > saveEveryNFrame)
                        frameNo = frameNo - saveEveryNFrame;
                        % display the simulation time in the window name
                        r.hFigure.Name = "Simulation Time: " + simulationTime;
                        waitbar(simulationTime/lastObservationTime, r.waitbar);

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

                        simulationTime = observationTime;

                        drawnow;
                        frames(iFrame) = getframe(gcf);
                        iFrame = iFrame + 1;
                    end
                    frameNo = frameNo + 1;
                    possibleFrames = possibleFrames + 1;
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
            
            r.hFigure.Name = "Simulation Complete. Saving Video...";
            waitbar(0, r.waitbar, 'Saving Video');
            % create the video writer
            writerObj = VideoWriter(savePath, 'MPEG-4');
            % set the seconds per image
            writerObj.FrameRate = frameRate;
            % open the video writer
            open(writerObj);
            % write the frames to the video
            for i = 1:length(frames)
                % convert the image to a frame
                writeVideo(writerObj, frames(i));
                waitbar(i/length(frames), r.waitbar, 'Saving Video');
            end
            % close the writer object
            close(writerObj);
            r.hFigure.Name = "Simulation Complete. Video Saved.";
            waitbar(1, r.waitbar, 'Video Saved');
        end
        
        function positions= getPositions(file, index)
            positions = file.p(file.i(index)+1:file.i(index+1), :);
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

