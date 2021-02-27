 function [hCylinder] = plotCylinder(obj, baseCentre, radius, length, axis, args)
    % plotCylinder.m plots a cylinder
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % baseCentre - a 3D vector containing the vertex at the centre of the
    %   negative most face of the cylinder
    % radius - a double containing the radius of the cylinder
    % length - a double containing the length of the cylinder along the specified axis
    % axis - a char stating the dimension of the cylinders long axis.
    %   either 'X', 'Y' or 'Z'
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hCylinder - a handle to the 3 meshes which makes up the cylinder
    arguments
        obj
        baseCentre (1, 3) double = [0, 0, -0.5];
        radius (1, 1) double = 0.5;
        length (1, 1) double = 1;
        axis (1, 1) char {mustBeXYZ(axis)} = 'Z';
        args.Resolution (1, 1) double = obj.CircleResolution;
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.FaceColor;
        args.EdgeColor = obj.EdgeColor;
        args.EdgeWidth = obj.EdgeWidth;
        args.EdgeStyle = obj.EdgeStyle;
    end
    
    % holdState ensures the original hold state is maintained
    holdState = ishold; 
    
    [x,y,z] = cylinder(radius, args.Resolution);
    topCentre = baseCentre;
    
    if(axis == 'X')
        hCylinder.tube = mesh(baseCentre(1) + z * length, baseCentre(2) + x, ...
        baseCentre(3) + y, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha,...
        'EdgeAlpha', args.EdgeAlpha, ...
        'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
        topCentre(1) = baseCentre(1) + length;
    elseif(axis == 'Y')
        hCylinder.tube = mesh(baseCentre(1) + x, baseCentre(2) + z * length, ...
        baseCentre(3) + y, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha, ...
        'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
        topCentre(2) = baseCentre(2) + length;
    elseif(axis == 'Z')
        hCylinder.tube = mesh(baseCentre(1) + x, baseCentre(2) + y, ...
        baseCentre(3) + z * length, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha, ...
        'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
        topCentre(3) = baseCentre(3) + length;
    end
    
    hold on;
    
    hCylinder.base = obj.plotCircleSurface(baseCentre, radius, axis, ...
        'Resolution', args.Resolution, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
    
    hCylinder.top = obj.plotCircleSurface(topCentre, radius, axis, ...
        'Resolution', args.Resolution, 'FaceColor', args.FaceColor, ...
        'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha, ...
        'EdgeAlpha', args.EdgeAlpha);
    
    if(~holdState)
        hold off;
    end
 end

% function checks that the user has specified the correct char for axis
function mustBeXYZ(axis)
    if (axis ~= 'X' && axis ~= 'Y' && axis ~= 'Z')
        eid = 'cylinder:UnknownAxis';
        msg = 'unknown axis supplied, must be X, Y or Z';
        throwAsCaller(MException(eid,msg))
    end
end