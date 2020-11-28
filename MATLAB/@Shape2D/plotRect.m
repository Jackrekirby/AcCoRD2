function hRect = plotRect(obj, origin, length, args)
    arguments
        obj
        origin (1, 2) double = [-0.5, -0.5];
        length (1, 2) double = [1, 1];
        args.FaceAlpha double = obj.FaceAlpha;
        args.FaceColor = obj.getFaceColor();
        args.LineColor = obj.getLineColor();
    end

    max = origin + length;
    x = [origin(1), origin(1), max(1), max(1)];
    y = [origin(2), max(2), max(2), origin(2)];

    hRect = patch(x, y, args.FaceColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeColor', args.LineColor);
end