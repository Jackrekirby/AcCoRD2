classdef Environment3D
    %UNTITLED7 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        shapes
        DefaultFaceAlpha
        DefaultFaceColour
    end
    
    methods
        function obj = Evironment3D(jsonFilePath)
            %UNTITLED7 Construct an instance of this class
            %   Detailed explanation goes here
            fileID = fopen(jsonFilePath,'r');
            obj.shapes = jsonFilePath(fileID);
            obj.Property1 = inputArg1 + inputArg2;
        end
        
        function outputArg = method1(obj,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.Property1 + inputArg;
        end
    end
end

