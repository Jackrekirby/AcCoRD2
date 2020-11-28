function initilisePlots(obj, points, args)
    holdState = ishold();

     obj.hStartMarker = plot3(points(1, 1), points(1, 2), points(1, 3), ...
        'Marker', args.marker, 'LineStyle', 'none', ...
        'LineWidth', args.markerThickness, 'Color', args.pathColors{1}, ...
        'MarkerSize', args.markerSize);

     hold on;

     obj.hStartMarker = plot3(points(end, 1), points(end, 2), points(end, 3), ...
        'Marker', args.marker, 'LineStyle', 'none', ...
        'LineWidth', args.markerThickness, 'Color', args.pathColors{3}, ...
        'MarkerSize', args.markerSize);

     if(obj.showNonReflectedPoints)
        obj.nonReflectedLine.x = [points(3:2:end-1, 1), points(2:2:end-1, 1)];
        obj.nonReflectedLine.y = [points(3:2:end-1, 2), points(2:2:end-1, 2)];
        obj.nonReflectedLine.z = [points(3:2:end-1, 3), points(2:2:end-1, 3)];
        obj.nonReflectedMarkers = points(2:2:end-1, :);

        z = obj.nonReflectedLine.x .* 0;

        obj.hNonReflectedLine = plot3(z', z', z', 'Marker', 'none', ...
            'LineStyle', args.nonReflectedLineStyle, ...
        'LineWidth', args.lineWidth, 'Color', args.lineColor);

        obj.hNonReflectedMarkers = animatedline('Marker', args.marker, ...
            'LineStyle', 'none', 'LineWidth', args.markerThickness, ...
            'MarkerSize', args.markerSize, 'MarkerEdgeColor', args.pathColors{4});
     end

     obj.path = points([1:2:end, end], :);

     obj.hPathLine = animatedline(obj.path(1, 1), obj.path(1, 2), obj.path(1, 3), ...
     'Marker', 'none', 'LineStyle', args.pathLineStyle, ...
     'LineWidth', args.lineWidth, 'Color', args.lineColor);

     obj.hPathMarkers = animatedline('Marker', args.marker, 'LineStyle', 'none', ...
     'MarkerSize', args.markerSize, 'MarkerEdgeColor', args.pathColors{2}, ...
     'LineWidth', args.markerThickness);

     obj.nPoints = size(obj.path, 1);
     if(~holdState) 
        hold off;
     end
end