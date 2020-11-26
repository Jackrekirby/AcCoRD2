function [hPath] = plotPath2D(points, args)
    arguments
        points (:, 2) double = [-0.5, -0.5; 0.5, 0.5];
        args.lineWidth double = 1;
        args.lineColor = 'k';
        args.lineStyle = '-';
        args.startColor = 'g';
        args.middleColor = 'b';
        args.endColor = 'r';
    end
   
    holdState = ishold();
    hPath.startPoint = plotPoints2D(points(1, :), 'color', args.startColor);
    hold on;
    hPath.middlePoints = plotPoints2D(points(2:end-1, :), 'color', args.middleColor);
    hPath.endPoint = plotPoints2D(points(end, :), 'color', args.endColor);
    
    hPath.line = plot(points(:, 1), points(:, 2), ...
        'Marker', 'none', 'LineStyle', args.lineStyle, ...
        'LineWidth', args.lineWidth, 'Color', args.lineColor);
    
    if(~holdState) 
        hold off;
    end
end