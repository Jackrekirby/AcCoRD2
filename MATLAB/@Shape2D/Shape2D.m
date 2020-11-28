classdef Shape2D < handle
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
        function obj = Shape2D(args)
            arguments
                args.FaceAlpha = 0.05
                args.FaceColor = 'random'
                args.CircleResolution = 16;
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
            obj.CircleResolution = args.CircleResolution * 4 + 1;
            obj.LineWidth = args.LineWidth;
            obj.LineStyle = args.LineStyle;
            obj.LineColor = args.LineColor;
            obj.FaceColorMap = args.FaceColorMap;
            obj.FaceColorMapIndex = args.FaceColorMapIndex;
            obj.LineColorMap = args.LineColorMap;
            obj.LineColorMapIndex = args.LineColorMapIndex;
        end
        
        hCircle = plotCircle(obj, centre, radius, args)
        hRect = plotRect(obj, origin, length, args)
        plot(obj, jsonFilePath)
    end
    
    methods (Access = private)
        color = getFaceColor(obj)
        color = getLineColor(obj)
    end
end

