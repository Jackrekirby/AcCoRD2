classdef Simulation < handle
    properties
        PassiveActor
        ObservationTimes
        PlayBackSpeed
        hFigure
        
        Directory
        SimulationName
    end
    
    methods (Access = public)
        function obj = Simulation(Directory, SimulationName, args)
            arguments
                Directory
                SimulationName
                args.Seed = 1;
                args.Realisation = 0;
                args.PlayBackSpeed = 1;
            end
            
            obj.PlayBackSpeed = args.PlayBackSpeed;
            obj.SimulationName = SimulationName;
            obj.Directory = Directory;
           
            obj.PassiveActor = Simulation.readBinaryFiles(Directory, SimulationName, args.Seed, ...
                args.Realisation);
        end
        
        function hFigure = plotMoleculeCount(obj)
            hFigure = figure;
            hold on;
            k = 1;
            % for each actor
            for i = 1:length(obj.PassiveActor)
                % for each molecule type
                for j = 1:length(obj.PassiveActor(i).moleType)
                    % if molecule type occurs in passive actor
                    if(~isempty(obj.PassiveActor(i).moleType(j).positions))
                        % plot molecule count against time
                        plot(obj.PassiveActor(i).times, ...
                            obj.PassiveActor(i).moleType(j).count, ...
                            'LineWidth', 2);
                        % add line to legend
                        legendLabels{k} = "passive actor: " + num2str(i) ...
                         + ", molecule type: " + num2str(j);
                        k = k + 1;
                    end
                end
            end
            title("Molecule Count per Passive Actor and Molecule Type");
            xlabel("Time (s)"); ylabel("Count");
            legend(legendLabels);
            hold off;
        end
        
        function plotRegions(obj, showFigure)
            regionDir = obj.Directory + "\" + obj.SimulationName + '\regions.json';
            s = Shape3D();
            s.plot(regionDir);
            if(showFigure)
                obj.hFigure.Visible = 'on';
            end
        end
        
        function plotMolecules(obj, colorByActor)
            obj.initilisePassiveActorPlots(colorByActor);
            
            simulationTime = 0;
            % list of indicies of all the actors to render in next update
            actorsToRender = [];
            obj.hFigure.Visible = 'on';
            tic;
            % keep rendering until all observations have been rendered
            while(min(obj.ObservationTimes) ~= Inf)
                [observationTime, id] = min(obj.ObservationTimes);

                % if the next actor's time is ahead of the current simulation time then
                % render all the actor observations from the current simulation time
                % before going onto the next actor
                
                if(observationTime > simulationTime)
                    % display the simulation time in the window name
                    obj.hFigure.Name = "Simulation Time: " + simulationTime;

                    for i = 1:length(actorsToRender)
                        actor_id = actorsToRender(i);
                        for j = 1:length(obj.PassiveActor(actor_id).moleType)
                            % only attempt to update plot if passive actor
                            % includes the molecule type
                            if(~isempty(obj.PassiveActor(actor_id).moleType(j).positions))
                                positions = Simulation.GetPositions(obj.PassiveActor(actor_id).moleType(j), ...
                                    obj.PassiveActor(actor_id).timeIndex - 1);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.XData = positions(1, :);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.YData = positions(2, :);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.ZData = positions(3, :);
                            end
                        end
                    end

                    % now figure is about to be updated actorsToRender can
                    % be emptied
                    actorsToRender = [];

                    % if real time is ahead of simulation time wait
                    while(simulationTime / obj.PlayBackSpeed > toc)
                        pause(0.01 * ((simulationTime / obj.PlayBackSpeed) - toc));
                    end
                    simulationTime = observationTime;
                    drawnow limitrate;
                end

                actorsToRender = [actorsToRender, id];
                % update actors next observation time or set to Inf is no
                % observations left
                obj.PassiveActor(id).timeIndex = obj.PassiveActor(id).timeIndex + 1;
                if(obj.PassiveActor(id).timeIndex > size(obj.PassiveActor(id).times, 1) )
                    obj.ObservationTimes(id) = Inf;
                else
                    obj.ObservationTimes(id) = ... 
                        obj.PassiveActor(id).times(obj.PassiveActor(id).timeIndex);
                end
            end

            obj.hFigure.Name = "Simulation Time: " + simulationTime + " (Complete)";
        end
        
        function initialiseFigure(obj, limits)
            obj.hFigure = figure('visible','off', 'Name', ...
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
    
    
    methods (Access = private)
        function initilisePassiveActorPlots(obj, colorByActor)
            % calculate the number of molecule types
            if(colorByActor)
                moleculeColormap = hsv(length(obj.PassiveActor));
            else
                nMoleculeTypes = 0;
                for i = 1:length(obj.PassiveActor)
                    if(length(obj.PassiveActor(i).moleType) > nMoleculeTypes)
                        nMoleculeTypes = length(obj.PassiveActor(i).moleType);
                    end
                end

                moleculeColormap = hsv(nMoleculeTypes);
            end
            
            hold on;
            for i = 1:length(obj.PassiveActor)
                % if passive actor time is not recorded than it cannot be visualised so
                % is ignored by setting its next observation time to infinite
                if(isfield(obj.PassiveActor(i), 'times'))
                    obj.PassiveActor(i).timeIndex = 1;
                    obj.ObservationTimes(i) = ... 
                        obj.PassiveActor(i).times(1);
                    
                    for j = 1:length(obj.PassiveActor(i).moleType)
                        if(colorByActor)
                            c = i;
                        else
                            c = j;
                        end
                        obj.PassiveActor(i).moleType(j).hPlot = ...
                            plot3(0, 0, 0, 'Marker', 'o', 'LineStyle', 'none', ...
                            'MarkerEdgeColor', moleculeColormap(c, :));
                        % clear plot marker data
                        obj.PassiveActor(i).moleType(j).hPlot.XData = [];
                        obj.PassiveActor(i).moleType(j).hPlot.YData = [];
                        obj.PassiveActor(i).moleType(j).hPlot.ZData = [];
                    end
                else
                    obj.ObservationTimes(i) = Inf;
                end
            end
            hold off;
        end
    end
    
    methods(Static)
        function passiveActor = readBinaryFiles(directory, simulation_name, seed, realisation)
            % Create the directory path to the realisation
            realisationDir = directory + "\" + simulation_name + "\s" + seed + "\r" + realisation;
            if ~exist(realisationDir, 'dir')
                error(realisationDir + " is not a valid folder path");
            end
            disp("Reading: " + realisationDir);
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
                            passiveActor(actorID + 1).times = ...
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
    end
end

