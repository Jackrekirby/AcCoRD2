function [hSphere] = plotSphere(obj, centre, radius, args)
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % plotSphere.m plots a sphere
   
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % centre - a 3D vector containing the centre vertex of the sphere
    % radius - a double containing the radius of the sphere along each axis
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hSphere - a handle to the mesh which makes up the sphere
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        args.Resolution (1, 1) double = obj.SphereResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.FaceColor;
        args.EdgeColor = obj.EdgeColor;
        args.EdgeWidth = obj.EdgeWidth;
        args.EdgeStyle = obj.EdgeStyle;
    end

    [x, y, z] = sphere(args.Resolution);
    [hSphere] = mesh(centre(1) + x * radius, ...
        centre(2) + y * radius, centre(3) + z * radius, ...
        'FaceAlpha', args.FaceAlpha, 'EdgeColor', args.EdgeColor, ... 
        'FaceColor', args.FaceColor, 'EdgeAlpha', args.EdgeAlpha, ...
        'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
end