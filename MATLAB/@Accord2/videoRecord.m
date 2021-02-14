function [video] = videoRecord(video, playBackSpeed, filePath)
    video.waitbar = waitbar(0, 'Rendering Simulation', 'Name', filePath);

    simulationTime = 0;
    % list of indicies of all the actors to render in next update
    actorsToRender = [];

    frames(1) = getframe(gcf);
    frameNo = 1;
    possibleFrames = 1;
    iFrame = 1;
    tic;

    % Work out the number of frames
    lastObservationTime = 0;
    for iObserver = 1:length(video.p)
        allObservationTimes = [video.p(iObserver).t, video.p(iObserver).t];
        if(lastObservationTime < video.p(iObserver).t(end))
            lastObservationTime = video.p(iObserver).t(end);
        end
    end
    % If the calculated frame rate > 30 then skip frames to get
    % frame rate <= 30
    nFrames = length(unique(allObservationTimes));
    frameRate = 1 / ((lastObservationTime / playBackSpeed) / nFrames);
    saveEveryNFrame = 1;
    if(frameRate > 30)
        saveEveryNFrame = frameRate / 30;
        newFrameRate = frameRate / saveEveryNFrame;
        disp("[info] Frame Rate Capped From: " + frameRate + ", to: " + newFrameRate);
        frameRate = newFrameRate;
    end

    % keep rendering until all observations have been rendered
    while(min(video.observationTimes) ~= Inf)
        [observationTime, observationID] = min(video.observationTimes);
        % if the next actor's time is ahead of the current simulation time then
        % render all the actor observations from the current simulation time
        % before going onto the next actor
        if(observationTime > simulationTime)
            if(frameNo > saveEveryNFrame)
                frameNo = frameNo - saveEveryNFrame;
                % display the simulation time in the window name
                video.hFigure.Name = "Simulation Time: " + simulationTime;
                waitbar(simulationTime/lastObservationTime, video.waitbar);

                for i = 1:length(actorsToRender)
                    actor_id = actorsToRender(i);
                    for iM = 1:length(video.p(actor_id).m)
                        % only attempt to update plot if passive actor
                        % includes the molecule type
                        if(~isempty(video.p(actor_id).m(iM).p))
                            positions = Accord.getPositions(video.p(actor_id).m(iM), ...
                                video.p(actor_id).timeIndex - 1);
                            video.p(actor_id).m(iM).hPlot.XData = positions(:, 1);
                            video.p(actor_id).m(iM).hPlot.YData = positions(:, 2);
                            video.p(actor_id).m(iM).hPlot.ZData = positions(:, 3);
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

    video.hFigure.Name = "Simulation Complete. Saving Video...";
    waitbar(0, video.waitbar, 'Saving Video');
    % create the video writer
    writerObj = VideoWriter(filePath, 'MPEG-4');
    % set the seconds per image
    writerObj.FrameRate = frameRate;
    % open the video writer
    open(writerObj);
    % write the frames to the video
    for i = 1:length(frames)
        % convert the image to a frame
        writeVideo(writerObj, frames(i));
        waitbar(i/length(frames), video.waitbar, 'Saving Video');
    end
    % close the writer object
    close(writerObj);
    video.hFigure.Name = "Simulation Complete. Video Saved.";
    waitbar(1, video.waitbar, 'Video Saved');
end