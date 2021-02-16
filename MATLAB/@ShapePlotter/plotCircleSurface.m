function [hCircleSurface] = plotCircleSurface(obj, centre, radius, axis, args)
    % plotCircleSurface.m plots a circular surface orientated along a specified
    %   axis
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % centre - a 3D vector containing the vertex at the centre of the
    %   circle
    % radius - a double containing the radius of the cylinder
    % axis - a char stating the dimension of the cylinders long axis.
    %   either 'X', 'Y' or 'Z'
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hCircleSurface - a handle to the fill which makes up the
    %   circleSurface
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        axis (1, 1) char {mustBeXYZ(axis)} = 'Z';
        args.Resolution (1, 1) double = obj.CircleResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.FaceColor;
        args.EdgeColor = obj.EdgeColor;
    end

    theta = linspace(0, 2*pi, args.Resolution + 1);
    if(axis == 'X')
        x = ones(1, size(theta, 2)) * centre(1);
        y = radius * cos(theta) + centre(2);
        z = radius * sin(theta) + centre(3);
    elseif(axis == 'Y')
        x = radius * cos(theta) + centre(1);
        y = ones(1, size(theta, 2)) * centre(2);
        z = radius * sin(theta) + centre(3);
    elseif(axis == 'Z')
        x = radius * cos(theta) + centre(1);
        y = radius * sin(theta) + centre(2);
        z = ones(1, size(theta, 2)) * centre(3);
    end
    
    hCircleSurface = fill3(x, y, z, args.FaceColor, ...
        'FaceAlpha', args.FaceAlpha, ...
        'EdgeColor', args.EdgeColor, 'EdgeAlpha', args.EdgeAlpha);
end

% function checks that the user has specified the correct char for axis
function mustBeXYZ(axis)
    if (axis ~= 'X' && axis ~= 'Y' && axis ~= 'Z')
        eid = 'circleSurface:UnknownAxis';
        msg = 'unknown axis supplied, must be X, Y or Z';
        throwAsCaller(MException(eid,msg))
    end
end