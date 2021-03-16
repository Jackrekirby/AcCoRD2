 function hGriddedBox = plotGriddedBox(obj, origin, length, nPartitions, args)
 	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % plotGriddedBox.m plots a 3D box divided into equally sized subvolumes
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % origin - a 3D vector containing the negative most vertex of the box
    % length - a 3D vector containing the length of the box along each axis
    % nPartitions - a 3D vector containing the number of partitions per axis
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hGriddedBox - a handle to the patches which makes up the subvolumes
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, -0.5];
        length (1, 3) double = [1, 1, 1];
        nPartitions (1, 3) double = [3, 3, 3];
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.EdgeColor = obj.EdgeColor;
        args.FaceColor = obj.FaceColor;
        args.EdgeWidth = obj.EdgeWidth;
        args.EdgeStyle = obj.EdgeStyle;
    end
   
    holdState = ishold; 
    hGriddedBox.outer = plotBox(obj, origin, length, ...
        'FaceColor', args.FaceColor, 'EdgeColor', args.EdgeColor, ...
        'FaceAlpha', args.FaceAlpha, 'EdgeAlpha', args.EdgeAlpha, ...
        'EdgeStyle', args.EdgeStyle, 'EdgeWidth', args.EdgeWidth);
    subvolumeLength = length ./ nPartitions;
    i = 0;
    hold on;
    for z = 0:nPartitions(3) - 1
        for y = 0:nPartitions(2) - 1
            for x = 0:nPartitions(1) - 1
                i = i + 1;
                hGriddedBox.subvolume(i) = plotBox(obj, origin + [x, y, z] ...
                    .* subvolumeLength, subvolumeLength, ...
                    'FaceColor', args.FaceColor, 'EdgeColor', args.EdgeColor, ... 
                    'FaceAlpha', 0, 'EdgeAlpha', args.EdgeAlpha, ...
                    'EdgeStyle', args.EdgeStyle, 'EdgeWidth', args.EdgeWidth);
            end
        end
    end
    if(~holdState)
        hold off;
    end
 end