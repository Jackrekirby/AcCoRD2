classdef Shape3D < handle
    properties (Access = public)
        % Shape Defaults (user settable)
        FaceAlpha
        FaceColor
        BoxFaceColors
        ColorPerBoxFace
        CircleResolution
        SphereResolution
        LineWidth
        LineStyle
        LineColor
        % if face/line colour is random
        FaceColorMap
        FaceColorMapIndex
        LineColorMap
        LineColorMapIndex
    end
    
    methods (Access = public)
        function obj = Shape3D(args)
            arguments
                args.FaceAlpha = 0.25
                args.FaceColor = 'random'
                args.BoxFaceColours = hsv(6);
                args.ColorPerBoxFace = false;
                args.CircleResolution = 8;
                args.SphereResolution = 4;
                args.LineWidth = 1;
                args.LineStyle = '-';
                args.LineColor = 'random'
                args.FaceColorMap = hsv(8);
                args.FaceColorMapIndex = 1;
                args.LineColorMap = hsv(8);
                args.LineColorMapIndex = 1;
            end
            
            obj.FaceAlpha = args.FaceAlpha;
            obj.FaceColor = args.FaceColor;
            obj.BoxFaceColors = args.BoxFaceColours;
            obj.ColorPerBoxFace = args.ColorPerBoxFace;
            obj.CircleResolution = args.CircleResolution * 4 + 1;
            obj.SphereResolution = args.SphereResolution * 4;
            obj.LineWidth = args.LineWidth;
            obj.LineStyle = args.LineStyle;
            obj.LineColor = args.LineColor;
            obj.FaceColorMap = args.FaceColorMap;
            obj.FaceColorMapIndex = args.FaceColorMapIndex;
            obj.LineColorMap = args.LineColorMap;
            obj.LineColorMapIndex = args.LineColorMapIndex;
        end
        
        hBox = plotBox(obj, origin, length, args)
        hSphere = plotSphere(obj, centre, radius, args)
        hCircleSurface = plotCircleSurface(obj, centre, radius, axis, args)
        hRectSurface = plotRectSurface(obj, origin, length, args)
        hFigure = plot(obj, jsonFilePath)
    end
    
    methods (Access = private)
        color = getFaceColor(obj)
        color = getLineColor(obj)
    end
end

