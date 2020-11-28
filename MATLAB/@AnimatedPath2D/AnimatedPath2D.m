classdef AnimatedPath2D < handle
    properties
        nPoints
        duration
        index
        startTime
        currentTime
        
        hPathLine
        hPathMarkers
        hStartMarker
        hEndMarker
        hNonReflectedLine
        hNonReflectedMarkers
        
        path
        nonReflectedLine
        nonReflectedMarkers
        showNonReflectedPoints
    end
    
    methods (Access = public)
        function obj = AnimatedPath2D(points, args)
             arguments
                 points (:, 2) double;
                 args.startTime = 0;
                 args.duration = 0;
                 args.showNonReflectedPoints = true;
                 
                 args.markerThickness = 2;
                 args.markerSize = 6;
                 args.marker = 'o';
                 args.lineWidth = 1;
                 args.lineColor = 'k';
                 args.pathColors (1, 4) cell = {'g', 'b', 'r', 'm'};
                 args.nonReflectedLineStyle = '--';
                 args.pathLineStyle = '-';
             end
             
             obj.startTime = args.startTime;
             obj.currentTime = 0;
             obj.duration = args.duration;
             obj.index = 1;
             obj.showNonReflectedPoints = args.showNonReflectedPoints;

             initilisePlots(obj, points, args);
        end
        
        play(obj, pausesPerUpdate)
        stillPlaying = isPlaying(obj)
        didUpdate = update(obj, elapsedTime)
    end
    
    methods (Access = private)
        initilisePlots(obj, points, args)
    end
end

