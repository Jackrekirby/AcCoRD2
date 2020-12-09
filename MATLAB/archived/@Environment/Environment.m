classdef Environment < handle
    properties
        defaultFaceAlpha
        defaultFaceColor
        defaultBoxFaceColours
        uniqueColorPerBoxFace
        defaultCircleResolution
        defaultSphereResolution
        defaultMarkerSize
        defaultMarkerThickness
        defaultMarkerShape
        defaultLineWidth
        defaultLineStyle
        defaultLineColor
        defaultPathColors
        defaultCollisionColors
        defaultPathStartColor
        defaultPathMiddleColor
        defaultPathEndColor
        defaultColorMap
        colorMapIndex
        showPathMarkers
    end
    
    methods (Access = public)
        function obj = Environment(args)
            arguments
                args.defaultFaceAlpha = 0.5;
                args.defaultFaceColor = 'random';
                args.defaultEdgeColor = 'k';
                args.defaultBoxFaceColours = hsv(6);
                args.uniqueColorPerBoxFace = false; 
                args.defaultCircleResolution = 8;
                args.defaultSphereResolution = 30;
                args.defaultMarkerSize = 6;
                args.defaultMarkerThickness = 2;
                args.defaultMarkerShape = 'o';
                args.defaultLineColor = 'k'
                args.defaultLineWidth = 1;
                args.defaultLineStyle = '-';
                args.defaultPathColors (1, 3) cell = {'g', 'b', 'r'};
                args.defaultCollisionColors (1, 4) cell = {'g', 'b', 'r', 'm'};
                args.defaultPathStartColor = 'g';
                args.defaultPathMiddleColor = 'b';
                args.defaultPathEndColor = 'r';
                args.defaultColorMap = hsv(16);
                args.showPathMarkers = true;
            end
            obj.defaultFaceAlpha = args.defaultFaceAlpha;
            obj.defaultFaceColor = args.defaultFaceColor;
            obj.defaultBoxFaceColours = args.defaultBoxFaceColours;
            obj.uniqueColorPerBoxFace = args.uniqueColorPerBoxFace;
            obj.defaultCircleResolution = 1 + 4 * args.defaultCircleResolution;
            obj.defaultSphereResolution = args.defaultSphereResolution;
            obj.defaultMarkerSize = args.defaultMarkerSize;
            obj.defaultMarkerThickness = args.defaultMarkerThickness;
            obj.defaultMarkerShape = args.defaultMarkerShape;
            obj.defaultLineWidth = args.defaultLineWidth;
            obj.defaultLineColor = args.defaultLineColor;
            obj.defaultLineStyle = args.defaultLineStyle;
            obj.defaultPathColors = args.defaultPathColors;
            obj.defaultCollisionColors = args.defaultCollisionColors;
            obj.defaultPathStartColor = args.defaultPathStartColor;
            obj.defaultPathMiddleColor = args.defaultPathMiddleColor;
            obj.defaultPathEndColor = args.defaultPathEndColor;
            obj.defaultColorMap = args.defaultColorMap;
            obj.colorMapIndex = 1;
            obj.showPathMarkers = args.showPathMarkers;
        end

        [hPoints2D] = plotPoints2D(obj, points, args)
        [hPath2D] = plotPath2D(obj, points, args)
        [hRect] = plotRect(obj, origin, length, args)
        [hCircle] = plotCircle(obj, centre, radius, args)
        
        [hPoints3D] = plotPoints3D(obj, points, args)
        [hPath3D] = plotPath3D(obj, points, args)
        [hBox] = plotBox(obj, origin, length, args)
        [hSphere] = plotSphere(obj, centre, radius, args)
        [hRectSurface] = plotRectSurface(obj, origin, length, args)
        [hCircleSurface] = plotCircleSurface(obj, centre, radius, axis, args)
        [hCollision3D] = plotCollision3D(obj, origin, finish, intersection, reflection)
        
        plot(obj, jsonFilePath)
    end
    
    methods (Access = private)
        function color = GetDefaultFaceColor(obj)
            if(strcmp(obj.defaultFaceColor, 'random'))
                obj.defaultColorMap;
                obj.colorMapIndex;
                color = obj.defaultColorMap(obj.colorMapIndex, :);
                obj.colorMapIndex = obj.colorMapIndex + 1;
                if(obj.colorMapIndex > size(obj.defaultColorMap, 1))
                    obj.colorMapIndex = 1;
                end
            else
                color = obj.defaultFaceColor;
            end
        end
    end
end

