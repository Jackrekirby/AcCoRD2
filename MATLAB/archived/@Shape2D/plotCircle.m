function hCircle = plotCircle(obj, centre, radius, args)
    arguments
        obj
        centre (1, 2) double = [0, 0];
        radius (1, 1) double = 0.5;
        args.Resolution (1, 1) double = obj.CircleResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.FaceColor = obj.getFaceColor();
        args.LineColor = obj.getLineColor();
    end

    theta = linspace(0, 2*pi, args.Resolution);
    x = radius * cos(theta) + centre(1);
    y = radius * sin(theta) + centre(2);

    hCircle = fill(x, y, args.FaceColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeColor', args.LineColor);
end