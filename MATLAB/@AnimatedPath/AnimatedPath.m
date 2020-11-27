classdef AnimatedPath < handle
    properties
        nPoints
        duration
        index
        startTime
        currentTime
        
        hPathLine
        hPathMarkers
        hStartMarker
        hEndMarker
        hNonReflectedLine
        hNonReflectedMarkers
        
        path
        nonReflectedLine
        nonReflectedMarkers
        showNonReflectedPoints
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
                 args.pathColors (1, 4) cell = {'g', 'b', 'r', 'm'};
                 args.showNonReflectedPoints = true;
             end
             
             
             obj.startTime = args.startTime;
             obj.currentTime = 0;
             obj.duration = args.duration;
             obj.index = 1;
             obj.showNonReflectedPoints = args.showNonReflectedPoints;
             
             holdState = ishold();
             obj.hStartMarker = environment.plotPoints3D(points(1, :), 'color',  args.pathColors{1});
             hold on;
             obj.hEndMarker = environment.plotPoints3D(points(end, :), 'color', args.pathColors{3});
             
             if(obj.showNonReflectedPoints)
                
                obj.nonReflectedLine.x = [points(3:2:end-1, 1), points(2:2:end-1, 1)];
                obj.nonReflectedLine.y = [points(3:2:end-1, 2), points(2:2:end-1, 2)];
                obj.nonReflectedLine.z = [points(3:2:end-1, 3), points(2:2:end-1, 3)];
                obj.nonReflectedMarkers = points(2:2:end-1, :);
                
                z = obj.nonReflectedLine.x .* 0;
                
                obj.hNonReflectedLine = plot3(z', z', z', 'Marker', 'none', 'LineStyle', '--', ...
                'LineWidth', args.lineWidth, 'Color', args.lineColor);
                obj.hNonReflectedMarkers = animatedline('Marker', args.marker, 'LineStyle', 'none', ...
                'LineWidth', args.lineWidth, 'MarkerEdgeColor', args.pathColors{4});
             end
            
             obj.path = points([1:2:end, end], :);
             obj.hPathLine = animatedline(obj.path(1, 1), obj.path(1, 2), obj.path(1, 3), ...
             'Marker', 'none', 'LineStyle', args.lineStyle, ...
             'LineWidth', args.lineWidth, 'Color', args.lineColor);
             obj.hPathMarkers = animatedline('Marker', args.marker, 'LineStyle', 'none', ...
             'LineWidth', args.lineWidth, 'MarkerEdgeColor', args.pathColors{2});
             
             obj.nPoints = size(obj.path, 1);
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
                    p = obj.path(i, :);
                    obj.hPathLine.addpoints(p(:, 1), p(:, 2), p(:, 3));
                    if(obj.index + 1 ~= newIndex && newIndex == obj.nPoints)
                        i(end) = obj.nPoints - 1;
                    end
                    if(newIndex ~= 1 && i(end) ~= obj.nPoints)
                        p = obj.path(i, :);
                        obj.hPathMarkers.addpoints(p(:, 1), p(:, 2), p(:, 3));
                        p = obj.nonReflectedLine;
                        aa = p
                        ab = p.x
                        ac = p.x(1, :)
                        for j = i-1
                            obj.hNonReflectedLine(j).XData = p.x(j, :);
                            obj.hNonReflectedLine(j).YData = p.y(j, :);
                            obj.hNonReflectedLine(j).ZData = p.z(j, :);
                        end
                        %obj.hNonReflectedLine.addpoints(p.x(i-1, :), p.y(i-1, :), p.z(i-1, :));
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

