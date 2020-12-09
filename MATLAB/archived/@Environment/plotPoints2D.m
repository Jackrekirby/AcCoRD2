function [hPoints2D] = plotPoints2D(obj, points, args)
    arguments
        obj
        points (:, 2) double = [0, 0];
        args.color = obj.GetDefaultFaceColor(); % MarkerEdgeColor
        args.size double = obj.defaultMarkerSize; % marker size
        args.thickness double = obj.defaultMarkerThickness; % line width
        args.shape = obj.defaultMarkerShape; % marker
    end
    
    hPoints2D = plot(points(:, 1), points(:, 2), ...
        'Marker', args.shape, 'LineStyle', 'none', ...
        'MarkerSize', args.size, 'MarkerEdgeColor', args.color, ...
        'LineWidth', args.thickness);
end