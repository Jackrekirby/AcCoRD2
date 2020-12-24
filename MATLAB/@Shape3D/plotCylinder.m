 function hCylinder = plotCylinder(obj, baseCentre, radius, length, axis, args)
    arguments
        obj
        baseCentre (1, 3) double = [0, 0, -0.5];
        radius (1, 1) double = 0.5;
        length (1, 1) double = 1;
        axis (1, 1) char {mustBeXYZ(axis)} = 'z';
        args.Resolution (1, 1) double = obj.CircleResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.getFaceColor();
        args.LineColor = obj.getLineColor();
    end
    
    holdState = ishold; 
   
    
    [x,y,z] = cylinder(radius, args.Resolution);
    topCentre = baseCentre;
    if(axis == 'x')
        hCylinder.tube = mesh(baseCentre(1) + z * length, baseCentre(2) + x, ...
        baseCentre(3) + y, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.LineColor, 'FaceAlpha', args.FaceAlpha,...
        'EdgeAlpha', args.EdgeAlpha);
        topCentre(1) = baseCentre(1) + length;
    elseif(axis == 'y')
        hCylinder.tube = mesh(baseCentre(1) + x, baseCentre(2) + z * length, ...
        baseCentre(3) + y, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
        topCentre(2) = baseCentre(2) + length;
    elseif(axis == 'z')
        hCylinder.tube = mesh(baseCentre(1) + x, baseCentre(2) + y, ...
        baseCentre(3) + z * length, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
        topCentre(3) = baseCentre(3) + length;
    end
    hold on;
    hCylinder.base = obj.plotCircleSurface(baseCentre, radius, axis, ...
        'Resolution', args.Resolution, 'FaceColor', args.FaceColor, ...
        'LineColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
    hCylinder.top = obj.plotCircleSurface(topCentre, radius, axis, ...
        'Resolution', args.Resolution, 'FaceColor', args.FaceColor, ...
        'LineColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
    if(~holdState)
        hold off;
    end
end

function mustBeXYZ(axis)
    if (axis ~= 'x' && axis ~= 'y' && axis ~= 'z')
        eid = 'plotCylinder:UnknownAxis';
        msg = 'unknown axis supplied, must be x, y or z';
        throwAsCaller(MException(eid,msg))
    end
end