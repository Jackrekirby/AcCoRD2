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
            obj.hPathLine.addpoints(p(:, 1), p(:, 2));
            if(obj.index + 1 ~= newIndex && newIndex == obj.nPoints)
                i(end) = obj.nPoints - 1;
            end
            if(newIndex ~= 1 && i(end) ~= obj.nPoints)
                p = obj.path(i, :);
                obj.hPathMarkers.addpoints(p(:, 1), p(:, 2));

                if(obj.showNonReflectedPoints)
                    p = obj.nonReflectedMarkers(i-1, :);
                    obj.hNonReflectedMarkers.addpoints(p(:, 1), p(:, 2));

                    for j = i-1
                        obj.hNonReflectedLine(j).XData = obj.nonReflectedLine.x(j, :);
                        obj.hNonReflectedLine(j).YData = obj.nonReflectedLine.y(j, :);
                    end
                end
            end
            obj.index = newIndex;
            didUpdate = true;
        else
            didUpdate = false;
        end
    end
end