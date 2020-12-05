clear all;
clc;
% To Do
% there may be a different number of realisations per seed
% remember to to overwrite inbuilt function names

% Select the simulation name, seed and realisation to visualise
simulation = ReadSimFiles("D:\dev", "my_simulation", 1, 0);
playBackSpeed = 1; % half real speed
n_molecule_types = 3;
molecule_colormap = hsv(n_molecule_types);


simulation.hFigure = figure('visible','off', 'Name','Simulation Time:','NumberTitle','off');
view(3);
xlabel('x');
ylabel('y');
zlabel('z');
axis equal;
view(45,30);
r = 10;
xlim([-r, r]); zlim([-r, r]); ylim([-r, r]);
hold on;

fprintf('\n');
disp("Ordering passive actors");
for i = 1:size(simulation.passiveActor, 2)
    % if passive actor time is not recorded than it cannot be visualised so
    % is ignored by setting its next observation time to infinite
    if(isfield(simulation.passiveActor(i), 'times'))
        simulation.passiveActor(i).timeIndex = 1;
        simulation.passiveActorTimes(i) = ... 
            simulation.passiveActor(i).times(simulation.passiveActor(i).timeIndex);
        %NEED a plot per molecule type
        for j = 1:size(simulation.passiveActor(i).moleType, 2)
            simulation.passiveActor(i).moleType(j).hPlot = ...
                plot3(0, 0, 0, 'Marker', 'o', 'LineStyle', 'none', ...
                'MarkerEdgeColor', molecule_colormap(j, :));
            simulation.passiveActor(i).moleType(j).hPlot.XData = [];
            simulation.passiveActor(i).moleType(j).hPlot.YData = [];
            simulation.passiveActor(i).moleType(j).hPlot.ZData = [];
        end
    else
        simulation.passiveActor(i) = Inf;
    end
end

hold off;
simulation.hFigure.Visible = 'on';

simulation.time = min(simulation.passiveActorTimes);
simulation.actorsToRender = [];
disp("Beginning rendering");
tic;
while(min(simulation.passiveActorTimes) ~= Inf)
    [time, id] = min(simulation.passiveActorTimes);
    
    % if the next actor's time is ahead of the current simulation time then
    % render all the actor observations from the current simulation time
    % before going onto the next actor
    if(time > simulation.time)
        % display the simulation time in the window name
        simulation.hFigure.Name = "Simulation Time: " + simulation.time;
        %fprintf("Render at time: " + simulation.time + 's, actors: \n');
        %disp(simulation.actorsToRender);
        
        for i = 1:size(simulation.actorsToRender, 2)
            actor_id = simulation.actorsToRender(i);
            for j = 1:size(simulation.passiveActor(actor_id).moleType, 2)
                if(simulation.passiveActor(actor_id).moleType(j).count ~= 0)
                    positions = GetPositions(simulation.passiveActor(actor_id).moleType(j), ...
                        simulation.passiveActor(actor_id).timeIndex - 1);
                    simulation.passiveActor(actor_id).moleType(j).hPlot.XData = positions(1, :);
                    simulation.passiveActor(actor_id).moleType(j).hPlot.YData = positions(2, :);
                    simulation.passiveActor(actor_id).moleType(j).hPlot.ZData = positions(3, :);
                end
            end
        end

        simulation.actorsToRender = [];
        
        % if real time is ahead of simulation time wait
        while(simulation.time / playBackSpeed > toc)
            pause(0.01 * ((simulation.time / playBackSpeed) - toc));
        end
        simulation.time = time;
        drawnow limitrate;
    end
 
    simulation.actorsToRender = [simulation.actorsToRender, id];
    
    simulation.passiveActor(id).timeIndex = simulation.passiveActor(id).timeIndex + 1;
    if(simulation.passiveActor(id).timeIndex > size(simulation.passiveActor(id).times, 1) )
        simulation.passiveActorTimes(id) = Inf;
    else
        simulation.passiveActorTimes(id) = ... 
            simulation.passiveActor(id).times(simulation.passiveActor(id).timeIndex);
    end
end

disp("Rendering Complete");

%% Functions

function data = GetPositions(file, index)
    data = file.positions(:, file.index(index)+1:file.index(index+1));
end

function simulation = ReadSimFiles(directory, simulation_name, seed, realisation)
    % Create the visualisation directory path
    realisationDir = directory + "\" + simulation_name + "\s" + seed + "\r" + realisation;
    disp("Reading: " + realisationDir);
    % Find all the files and folders in the visualisation directory
    files = dir(realisationDir);
    simulation = struct;
    % For each file
    for i = 1:size(files, 1)
        % Sort through files for .bin files only
        filePath = files(i).name;
        pat = ".bin";
        if(endsWith(filePath,pat))
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
                    simulation.passiveActor(actorID + 1).times = ...
                    ReadTimeBinary(files(i).folder + "\" + files(i).name);
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
                            simulation.passiveActor(actorID + 1).moleType(moleID + 1) = ...
                                ReadPositionBinary(files(i).folder + "\" + files(i).name(1:end-5));
                        end
                    elseif(fileType == 'c')
                        % only read count file if position file doesn't exist
                        if(~isfile(files(i).folder + "\" + files(i).name(1:end-5) + "p.bin"))
                            disp("passive actor(" + actorID + ").moletype(" + moleID + ").count");
                            simulation.passiveActor(actorID + 1).moleType(moleID + 1).count = ...
                                ReadCountBinary(files(i).folder + "\" + files(i).name);
                        end
                    end
                end
            elseif(actorType == 'a')
                % To Complete
            end
        end
    end
    disp("Finished Import");
end

function file = ReadTimeBinary(file_name)
    fname_count = file_name;
    fileID_count = fopen(fname_count,'r');
    file = fread(fileID_count, 'double');
end

function file = ReadCountBinary(file_name)
    fname_count = file_name;
    fileID_count = fopen(fname_count,'r');
    % uint64 for 64 bit and uint32 for 32 bit
    file = fread(fileID_count, 'uint64');
end

function file = ReadPositionBinary(file_name)
    fname_positions = file_name + "p.bin";
    fileID_positions = fopen(fname_positions,'r');
    file.positions = fread(fileID_positions, [3 inf], 'double');

    fname_count = file_name + "c.bin";
    fileID_count = fopen(fname_count,'r');
    % uint64 for 64 bit and uint32 for 32 bit
    file.count = fread(fileID_count, 'uint64');
    
    total_count = 0;
    file.index(size(file.count, 1) + 1) = 0;
    for i = 1:size(file.count, 1)
        total_count = total_count + file.count(i);
        file.index(i+1) = total_count;
    end
end