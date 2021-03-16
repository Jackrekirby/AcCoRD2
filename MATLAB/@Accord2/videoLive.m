function [video] = videoLive(video, playBackSpeed, endTime)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % videoLive.m - displays a live animation of the simulation environment
    %   at a given playback speed, and upto a given time in the simulation.
    %   This is different to videoRecord which does not attempt to maintain a
    %   constant playback speed, but will render the video as fast as
    %   possible, whose speed depends on the computer's performance.
    %   videoLive will skip frames if it begins to lag behind the playback
    %   speed.
    
    % INPUTS
    % video - a struct containing molecule data and a figure, created by
    %   videoCreateScene.m
    % playBackSpeed - the speed relative to the simulation length for the
    %   animation to play at. E.g. playBackSpeed = 8, plays the simulationm 8
    %   times faster than its actual speed. playBackSpeed = 0.1 plays the
    %   simulation 10 times slower.
    % endTime - the time which the simulation will stop. The faster the
    %   playback speed the less accurate this is.
    
    % OUTPUTS
    % video - the same input struct with the updated graphic and logic
    %   data

    simulationTime = 0;
    % list of indicies of all the actors to render in next update
    actorsToRender = [];
    tic;
    % keep rendering until all observations have been rendered
    while(min(video.observationTimes) < endTime)
        % if simulation is behind real time then skip frames
        if(simulationTime / playBackSpeed < toc)
            while(simulationTime / playBackSpeed < toc)
                [observationTime, observationID] = min(video.observationTimes);
                % Skip all the observations at a single time, before
                % rechecking if simulation time is ahead of real time
                while(observationTime == simulationTime)
                    video.p(observationID).timeIndex = video.p(observationID).timeIndex + 1;
                    if(video.p(observationID).timeIndex > size(video.p(observationID).t, 1) )
                        video.observationTimes(observationID) = Inf;
                    else
                        video.observationTimes(observationID) = ... 
                            video.p(observationID).t(video.p(observationID).timeIndex);
                    end
                    [observationTime, observationID] = min(video.observationTimes);
                end
                simulationTime = observationTime;
            end
        else
            [observationTime, observationID] = min(video.observationTimes);
            % if the next actor's time is ahead of the current simulation time then
            % render all the actor observations from the current simulation time
            % before going onto the next actor
            if(observationTime > simulationTime)
                % display the simulation time in the window name
                video.hFigure.Name = "Simulation Time: " + simulationTime;

                for i = 1:length(actorsToRender)
                    actorID = actorsToRender(i);
                    for iM = 1:length(video.p(actorID).m)
                        % only attempt to update plot if passive actor
                        % includes the molecule type
                        if(~isempty(video.p(actorID).m(iM).p))
                            positions = Accord2.getMoleculePositions(video.p(actorID).m(iM), ...
                                video.p(actorID).timeIndex - 1);
                            video.p(actorID).m(iM).hPlot.XData = positions(:, 1);
                            video.p(actorID).m(iM).hPlot.YData = positions(:, 2);
                            video.p(actorID).m(iM).hPlot.ZData = positions(:, 3);
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
                
                % Update the simulation time to the current observation
                % time
                simulationTime = observationTime;

                drawnow limitrate;
            end

            actorsToRender(length(actorsToRender) + 1) = observationID;

            % update actors next observation time or set to Inf is no
            % observations left
            video.p(observationID).timeIndex = video.p(observationID).timeIndex + 1;
            if(video.p(observationID).timeIndex > size(video.p(observationID).t, 1) )
                video.observationTimes(observationID) = Inf;
            else
                video.observationTimes(observationID) = ... 
                    video.p(observationID).t(video.p(observationID).timeIndex);
            end
        end
    end

    video.hFigure.Name = "Simulation Complete";
end