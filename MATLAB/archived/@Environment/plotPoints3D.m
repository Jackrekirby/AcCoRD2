function [hPoints3D] = plotPoints3D(obj, points, args)
    arguments
        obj
        points (:, 3) double = [0, 0, 0];
        args.color = obj.GetDefaultFaceColor(); % MarkerEdgeColor
        args.size double = obj.defaultMarkerSize; % marker size
        args.thickness double = obj.defaultMarkerThickness; % line width
        args.shape = obj.defaultMarkerShape; % marker
    end
    
    hPoints3D = plot3(points(:, 1), points(:, 2), points(:, 3), ...
        'Marker', args.shape, 'LineStyle', 'none', ...
        'MarkerSize', args.size, 'MarkerEdgeColor', args.color, ...
        'LineWidth', args.thickness);
end