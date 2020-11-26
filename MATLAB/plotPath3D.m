function [hPath] = plotPath3D(points, args)
    arguments
        points (:, 3) double = [-0.5, -0.5, -0.5; 0.5, 0.5, 0.5];
        args.lineWidth double = 1;
        args.lineColor = 'k';
        args.lineStyle = '-';
        args.startColor = 'g';
        args.middleColor = 'b';
        args.endColor = 'r';
    end
   
    holdState = ishold();
    hPath.startPoint = plotPoints3D(points(1, :), 'color', args.startColor);
    hold on;
    hPath.middlePoints = plotPoints3D(points(2:end-1, :), 'color', args.middleColor);
    hPath.endPoint = plotPoints3D(points(end, :), 'color', args.endColor);
    
    hPath.line = plot3(points(:, 1), points(:, 2), points(:, 3), ...
        'Marker', 'none', 'LineStyle', args.lineStyle, ...
        'LineWidth', args.lineWidth, 'Color', args.lineColor);
    
    if(~holdState) 
        hold off;
    end
end