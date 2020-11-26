function [hCircle] = plotCircle(centre, radius, args)
    arguments
        centre (1, 2) double = [0, 0];
        radius (1, 1) double = 0.5;
        args.resolution (1, 1) double = 30;
        args.faceAlpha double = 0.5;
        args.faceColor = 'b';
        args.edgeColor = 'k';
    end

    theta = linspace(0, 2*pi, args.resolution);
    x = radius * cos(theta) + centre(1);
    y = radius * sin(theta) + centre(2);
    
    hCircle = fill(x, y, args.faceColor, 'FaceAlpha', args.faceAlpha, ...
        'EdgeColor', args.edgeColor);
end