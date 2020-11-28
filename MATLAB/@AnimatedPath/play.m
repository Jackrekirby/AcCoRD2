function play(obj, pausesPerUpdate)
    arguments
        obj
        pausesPerUpdate (1, 1) double = 40;
    end
    % A pauseTime < 1 will result in more than 1 point drawn per
    % update
    % The greater the pauseTime above 1 the less likely more than 1
    % point is drawn per update
    pauseTime = (obj.duration / obj.nPoints) / pausesPerUpdate;
    lastTime = 0;
    tic;
    while(obj.isPlaying())
        if(obj.update(toc - lastTime))
            drawnow;
        end
        lastTime = toc;
        pause(pauseTime);
    end
end