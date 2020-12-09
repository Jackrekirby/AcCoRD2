function [hSphere] = plotSphere(obj, centre, radius, args)
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        args.resolution (1, 1) double = obj.defaultSphereResolution;
        args.faceAlpha double = obj.defaultFaceAlpha;
        args.faceColor = obj.GetDefaultFaceColor();
        args.edgeColor = obj.defaultLineColor;
    end
   
    [x, y, z] = sphere(args.resolution);
    [hSphere] = mesh(centre(1) + x * radius, centre(2) + y * radius, centre(3) + z * radius, ...
        'FaceAlpha', args.faceAlpha, 'EdgeColor', args.edgeColor, 'FaceColor', args.faceColor);
end