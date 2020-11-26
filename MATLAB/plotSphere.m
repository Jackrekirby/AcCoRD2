function [hSphere] = plotSphere(centre, radius, args)
    arguments
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        args.resolution (1, 1) double = 20;
        args.faceAlpha double = 0.5;
        args.faceColor = 'b';
        args.edgeColor = 'k';
    end
   
    [x, y, z] = sphere(args.resolution);
    [hSphere] = mesh(centre(1) + x * radius, centre(2) + y * radius, centre(3) + z * radius, ...
        'FaceAlpha', args.faceAlpha, 'EdgeColor', args.edgeColor, 'FaceColor', args.faceColor);
end