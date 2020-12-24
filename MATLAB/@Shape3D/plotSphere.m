function hSphere = plotSphere(obj, centre, radius, args)
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        args.Resolution (1, 1) double = obj.SphereResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.getFaceColor();
        args.LineColor = obj.getLineColor();
    end

    [x, y, z] = sphere(args.Resolution);
    [hSphere] = mesh(centre(1) + x * radius, ...
        centre(2) + y * radius, centre(3) + z * radius, ...
        'FaceAlpha', args.FaceAlpha, 'EdgeColor', args.LineColor, ... 
        'FaceColor', args.FaceColor, 'EdgeAlpha', args.EdgeAlpha);
end