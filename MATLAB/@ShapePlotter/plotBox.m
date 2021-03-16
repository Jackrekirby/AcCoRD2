 function [hBox] = plotBox(obj, origin, length, args)
 	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % plotBox.m plots a 3D box
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % origin - a 3D vector containing the negative most vertex of the box
    % length - a 3D vector containing the length of the box along each axis
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hBox - a handle to the patch which makes up the box
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, -0.5];
        length (1, 3) double = [1, 1, 1];
        args.FaceAlpha double = obj.FaceAlpha;
        args.FaceColor = obj.FaceColor;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.EdgeColor = obj.EdgeColor;
        args.EdgeWidth = obj.EdgeWidth;
        args.EdgeStyle = obj.EdgeStyle;
    end

    max = origin + length;
    vertices = [origin; max(1), origin(2:3); max(1:2) origin(3);...
        origin(1) max(2) origin(3); origin(1:2) max(3); ...
        max(1) origin(2) max(3); max; origin(1) max(2:3)];
    faces = [1 2 6 5; 2 3 7 6; 3 4 8 7; 4 1 5 8; 1 2 3 4; 5 6 7 8];

    hBox = patch('Vertices', vertices, 'Faces', faces,...
      'FaceColor', args.FaceColor, 'FaceAlpha', args.FaceAlpha,...
      'EdgeColor', args.EdgeColor, 'EdgeAlpha', args.EdgeAlpha,...
      'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
 end