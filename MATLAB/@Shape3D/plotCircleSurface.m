function hCircleSurface = plotCircleSurface(obj, centre, radius, axis, args)
    arguments
        obj
        centre (1, 3) double = [0, 0, 0];
        radius (1, 1) double = 0.5;
        axis (1, 1) char {mustBeXYZ(axis)} = 'z';
        args.Resolution (1, 1) double = obj.CircleResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.getFaceColor();
        args.LineColor = obj.getLineColor();
    end

    theta = linspace(0, 2*pi, args.Resolution);
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
    hCircleSurface = fill3(x, y, z, args.FaceColor, ...
        'FaceAlpha', args.FaceAlpha, ...
        'EdgeColor', args.LineColor, 'EdgeAlpha', args.EdgeAlpha);
end

function mustBeXYZ(axis)
    % Test for equal size
    if (axis ~= 'x' && axis ~= 'y' && axis ~= 'z')
        eid = 'plotCircleSurface:UnknownAxis';
        msg = 'unknown axis supplied, must be x, y or z';
        throwAsCaller(MException(eid,msg))
    end
end