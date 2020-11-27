classdef AnimatedPath < handle
    properties
        points
        nPoints
        duration
        index
        startTime
        currentTime
        hAnimatedLine
        hAnimatedMarkers
        hStartPoint
        hEndPoint
    end
    
    methods
        function obj = AnimatedPath(points, environment, args)
             arguments
                 points (:, 3) double = [-0.5, -0.5, -0.5; 0, 0, 0; 0.5, 0.5, 0.5];
                 environment = Environment();
                 args.startTime = 0.5;
                 args.duration = 3;
                 args.lineStyle = '-';
                 args.marker = 'o';
                 args.lineWidth = 1;
                 args.lineColor = 'k';
                 args.pathColors (1, 3) cell = {'g', 'b', 'r'};
             end
             
             obj.points = points;
             obj.nPoints = size(points, 1);
             obj.startTime = args.startTime;
             obj.currentTime = 0;
             obj.duration = args.duration;
             obj.index = 1;
             
             holdState = ishold();
             obj.hStartPoint = environment.plotPoints3D(points(1, :), 'color',  args.pathColors{1});
             hold on;
             obj.hEndPoint = environment.plotPoints3D(points(end, :), 'color', args.pathColors{3});
             
             obj.hAnimatedLine = animatedline(points(1, 1), points(1, 2), points(1, 3), ...
             'Marker', 'none', 'LineStyle', args.lineStyle, ...
             'LineWidth', args.lineWidth, 'Color', args.lineColor);
             obj.hAnimatedMarkers = animatedline( ...
             'Marker', args.marker, 'LineStyle', 'none', ...
             'LineWidth', args.lineWidth, 'MarkerEdgeColor', args.pathColors{2});
         
             if(~holdState) 
                hold off;
            end
        end
        
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
        
        function stillPlaying = isPlaying(obj)
            stillPlaying = (obj.index < obj.nPoints);
        end
        
        function didUpdate = update(obj, elapsedTime)
            if(obj.index < obj.nPoints)
                obj.currentTime = obj.currentTime + elapsedTime;
                newIndex = ceil(((obj.currentTime - obj.startTime) / obj.duration) * obj.nPoints);
                if(newIndex > obj.nPoints)
                    newIndex = obj.nPoints;
                end
                if(newIndex > obj.index)
                    i = (obj.index + 1):newIndex;
                    p = obj.points(i, :);
                    obj.hAnimatedLine.addpoints(p(:, 1), p(:, 2), p(:, 3));
                    if(obj.index + 1 ~= newIndex && newIndex == obj.nPoints)
                        i(end) = obj.nPoints - 1;
                    end
                    if(newIndex ~= 1 && i(end) ~= obj.nPoints)
                        p = obj.points(i, :);
                        obj.hAnimatedMarkers.addpoints(p(:, 1), p(:, 2), p(:, 3));
                    end
                    obj.index = newIndex;
                    didUpdate = true;
                else
                    didUpdate = false;
                end
            end
        end
    end
end

