 function [hPoint] = plotPoint(obj, origin, args)
    % plotPoint.m plots a 3D point
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % origin - a 3D vector containing the location of the point
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hPoint - a handle to the scatter3 which makes up the point
    arguments
        obj
        origin (1, 3) double = [0, 0, 0];
        args.MarkerStyle = obj.MarkerStyle;
        args.EdgeColor = obj.EdgeColor;
        args.MarkerSize = obj.MarkerSize;
        args.EdgeWidth = obj.EdgeWidth;
    end

    hPoint = scatter3(origin(1), origin(2), origin(3), 'Marker', args.MarkerStyle, ...
        'MarkerEdgeColor', args.EdgeColor, 'SizeData', args.MarkerSize, ...
        'LineWidth', args.EdgeWidth);
 end