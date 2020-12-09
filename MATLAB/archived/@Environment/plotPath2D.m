function [hPath2D] = plotPath2D(obj, points, args)
    arguments
        obj
        points (:, 2) double = [-0.5, -0.5; 0, 0; 0.5, 0.5];
        args.lineWidth double = obj.defaultLineWidth;
        args.lineColor = obj.defaultLineColor;
        args.lineStyle = obj.defaultLineStyle;
        args.markerColors = obj.defaultPathColors;
        args.showMarkers = obj.showPathMarkers;
    end
   
    holdState = ishold();
    
    if(args.showMarkers)
        hPath2D.startPoint = obj.plotPoints2D(points(1, :), 'color',  args.markerColors{1});
        hold on;
        hPath2D.middlePoints = obj.plotPoints2D(points(2:end-1, :), 'color', args.markerColors{2});
        hPath2D.endPoint = obj.plotPoints2D(points(end, :), 'color', args.markerColors{3});
    end
    
    hPath2D.line = plot(points(:, 1), points(:, 2), ...
        'Marker', 'none', 'LineStyle', args.lineStyle, ...
        'LineWidth', args.lineWidth, 'Color', args.lineColor);
    
    if(~holdState && args.showMarkers) 
        hold off;
    end
end