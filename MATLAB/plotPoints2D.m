function [hPoints] = plotPoints2D(points, args)
    arguments
        points (:, 2) double = [0, 0];
        args.color = 'b'; % MarkerEdgeColor
        args.size double = 6; % marker size
        args.thickness double = 2; % line width
        args.shape = 'o'; % marker
    end
    
    hPoints = plot(points(:, 1), points(:, 2), ...
        'Marker', args.shape, 'LineStyle', 'none', ...
        'MarkerSize', args.size, 'MarkerEdgeColor', args.color, ...
        'LineWidth', args.thickness);
end