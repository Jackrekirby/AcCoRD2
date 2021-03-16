classdef ShapePlotter < handle
	% The AcCoRD 2 Simulator (Actor - based Communication via Reaction - Diffusion)
	% Copyright 2021 Jack Kirby. All rights reserved.
	% For license details, read LICENSE.txt in the root AcCoRD2 directory
	
    % ShapePlotter.m - A class which allows the use to set default
    % arguments for any shapes plotted with the class to ensure style consistency
    
    % available properties for user to set
    properties (Access = public)
        FaceAlpha
        FaceColor
        
        EdgeAlpha
        EdgeColor
        EdgeWidth
        EdgeStyle
        
        MarkerStyle
        MarkerSize
        
        CircleResolution % CircleResolution > 1, and integer
        SphereResolution % CircleResolution > 1, and integer
    end
    
    methods (Access = public)
        function obj = ShapePlotter(args)
            % default arguments if no arguments passed
            arguments
                args.FaceAlpha = 0;
                args.FaceColor = 'b';
                
                args.EdgeAlpha = 1;
                args.EdgeColor = 'k';
                args.EdgeWidth = 1;
                args.EdgeStyle = '-';
                
                args.MarkerStyle = 'o';
                args.MarkerSize = 10;
                
                args.CircleResolution = 4;
                args.SphereResolution = 4;
            end
            
            % apply default arguments or those specified by user
            obj.FaceAlpha = args.FaceAlpha;
            obj.FaceColor = args.FaceColor;

            obj.CircleResolution = args.CircleResolution * 4;
            obj.SphereResolution = args.SphereResolution * 4;
            
            obj.EdgeAlpha = args.EdgeAlpha;
            obj.EdgeColor = args.EdgeColor;
            obj.EdgeWidth = args.EdgeWidth;
            obj.EdgeStyle = args.EdgeStyle;
            
            obj.MarkerStyle = args.MarkerStyle;
            obj.MarkerSize = args.MarkerSize;
        end
        
        [hBox] = plotBox(obj, origin, length, args)
        [hSphere] = plotSphere(obj, centre, radius, args)
        [hCylinder] = plotCylinder(obj, baseCentre, radius, length, args)
        [hCircleSurface] = plotCircleSurface(obj, centre, radius, axis, args)
        [hRectSurface] = plotRectSurface(obj, origin, length, args)
        [hGrid] = plotGriddedBox(obj, origin, length, nPartitions, args)
        [hPoint] = plotPoint(obj, origin, args)
        [hShapes] = plotShape(obj, shape)
        
    end
end

