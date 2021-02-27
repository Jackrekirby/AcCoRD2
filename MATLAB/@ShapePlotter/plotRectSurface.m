function [hRectSurface] = plotRectSurface(obj, origin, length, args)
    % plotRectSurface.m plots as rectangular surface, which is in the plane
    % determined by the axis with a zero length
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % origin - a 3D vector containing the negative most vertex of the box
    % length - a 3D vector containing the length of the box along each axis
    % args - used to override default style of ShapePlotter. See ShapePlotter
    %   for details of arguments
    
    % OUTPUTS
    % hRectSurface - a handle to the patch which makes up the rectSurface
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, 0];
        % SurfaceRect must recieve exactly 2 non zero lengths
        length (1, 3) double {mustHaveExactlyTwoNonZeroLengths(length)} = [1, 1, 0];
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.FaceColor = obj.FaceColor;
        args.EdgeColor = obj.EdgeColor;
        args.EdgeWidth = obj.EdgeWidth;
        args.EdgeStyle = obj.EdgeStyle;
    end
    
    hasZeroLength = (length == 0); % returns boolean vector containing which axis lengths are zero
    axes = (1:3); % assign axis x = 1, y = 2, z = 3
    zeroLengthAxis = axes(hasZeroLength); % assign the z axis as the axis with the zero length
    axes(hasZeroLength) = []; % delete the zero length 

    top = origin + length;

    % nzla = non zero length axis
    nzla1 = axes(1); nzla2 = axes(2);
    p(nzla1, :) = [origin(nzla1), origin(nzla1), top(nzla1), top(nzla1)];
    p(nzla2, :) = [origin(nzla2), top(nzla2), top(nzla2), origin(nzla2)];
    p(zeroLengthAxis, :) = origin(zeroLengthAxis) * ones(1, 4);

    hRectSurface = patch(p(1, :), p(2, :), p(3, :), args.FaceColor, ...
    'EdgeColor', args.EdgeColor, 'FaceAlpha', args.FaceAlpha, ...
    'EdgeAlpha', args.EdgeAlpha, ...
    'LineStyle', args.EdgeStyle, 'LineWidth', args.EdgeWidth);
end

% function checks that the length vector passed has exactly 2 non-zero lengths
function mustHaveExactlyTwoNonZeroLengths(length)
    if (nnz(length) ~= 2)
        eid = 'plotRectSurface:TwoNonZeroDimensions';
        msg = 'RectSurface must recieve a length vector with 2 non-zero dimensions and 1 zero dimension';
        throwAsCaller(MException(eid,msg))
    end
end