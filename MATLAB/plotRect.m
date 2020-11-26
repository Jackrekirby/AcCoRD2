function [hRect] = plotRect(origin, length, args)
    arguments
        origin (1, 2) double = [-0.5, -0.5];
        length (1, 2) double = [1, 1];
        args.faceAlpha double = 0.5;
        args.faceColor = 'b';
        args.edgeColor = 'k';
    end
    
    max = origin + length;
    x = [origin(1), origin(1), max(1), max(1)];
    y = [origin(2), max(2), max(2), origin(2)];
    
    hRect = patch(x, y, args.faceColor, 'FaceAlpha', args.faceAlpha, ...
        'EdgeColor', args.edgeColor);
end