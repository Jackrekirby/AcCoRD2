function [hPath3D] = plotPath3D(obj, points, args)
    arguments
        obj
        points (:, 3) double = [-0.5, -0.5, -0.5; 0, 0, 0; 0.5, 0.5, 0.5];
        args.lineWidth double = obj.defaultLineWidth;
        args.lineColor = obj.defaultLineColor;
        args.lineStyle = obj.defaultLineStyle;
        args.startColor = obj.defaultPathStartColor;
        args.middleColor = obj.defaultPathMiddleColor;
        args.endColor = obj.defaultPathEndColor;
        args.showMarkers = obj.showPathMarkers;
    end
    holdState = ishold();
    
    if(args.showMarkers)
        hPath3D.startPoint = obj.plotPoints3D(points(1, :), 'color', args.startColor);
        hold on;
        hPath3D.middlePoints = obj.plotPoints3D(points(2:end-1, :), 'color', args.middleColor);
        hPath3D.endPoint = obj.plotPoints3D(points(end, :), 'color', args.endColor);
    end
    
    hPath3D.line = plot3(points(:, 1), points(:, 2), points(:, 3), ...
        'Marker', 'none', 'LineStyle', args.lineStyle, ...
        'LineWidth', args.lineWidth, 'Color', args.lineColor);
    
    if(~holdState && args.showMarkers) 
        hold off;
    end
end