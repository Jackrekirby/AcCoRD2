function [hCircleSurface] = plotCircleSurface(obj, centre, radius, axis, args)
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        axis (1, 1) char {mustBeXYZ(axis)} = 'z';
        args.resolution (1, 1) double = obj.defaultCircleResolution;
        args.faceAlpha double = obj.defaultFaceAlpha;
        args.faceColor = obj.GetDefaultFaceColor();
        args.edgeColor = obj.defaultLineColor;
    end
    
    theta = linspace(0, 2*pi, args.resolution);
    if(axis == 'x')
        x = ones(1, size(theta, 2)) * centre(1);
        y = radius * cos(theta) + centre(2);
        z = radius * sin(theta) + centre(3);
    elseif(axis == 'y')
        x = radius * cos(theta) + centre(1);
        y = ones(1, size(theta, 2)) * centre(2);
        z = radius * sin(theta) + centre(3);
    elseif(axis == 'z')
        x = radius * cos(theta) + centre(1);
        y = radius * sin(theta) + centre(2);
        z = ones(1, size(theta, 2)) * centre(3);
    end
    hCircleSurface = fill3(x, y, z, args.faceColor, 'FaceAlpha', args.faceAlpha, ...
        'EdgeColor', args.edgeColor);
end

% Custom validation function
function mustBeXYZ(axis)
    % Test for equal size
    if (axis ~= 'x' && axis ~= 'y' && axis ~= 'z')
        eid = 'plotCircleSurface:UnknownAxis';
        msg = 'unknown axis supplied, must be x, y or z';
        throwAsCaller(MException(eid,msg))
    end
end