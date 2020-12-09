function [hRectSurface] = plotRectSurface(obj, origin, length, args)
    % Plots a rectangle in 3D space
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, 0];
        length (1, 3) double {mustHaveExactlyTwoNonZeroLengths(length)} = [1, 1, 0];
        args.faceAlpha double = obj.defaultFaceAlpha;
        args.faceColor = obj.GetDefaultFaceColor();
        args.edgeColor = obj.defaultLineColor;
    end
    
    if(nnz(length) == 2) % SurfaceRect must recieve exactly 2 non zero lengths
        nzlength = (length == 0); % returns boolean vector containing which axis lengths are zero
        nzdims = (1:3); % assign axis x = 1, y = 2, z = 3
        zi = nzdims(nzlength); % assign the z axis as the axis with the zero length
        nzdims(nzlength) = []; % delete the zero length 
        
        max = origin + length;
        
        % assign the non-zero length axes as x and y
        xi = nzdims(1); yi = nzdims(2);
        
        p(xi, :) = [origin(xi), origin(xi), max(xi), max(xi)];
        p(yi, :) = [origin(yi), max(yi), max(yi), origin(yi)];
        p(zi, :) = origin(zi) * ones(1, 4);
        
        hRectSurface = patch(p(1, :), p(2, :), p(3, :), args.faceColor, ...
        'EdgeColor', args.edgeColor, 'FaceAlpha', args.faceAlpha);
        view(3);
    else
        warning('plotRect3D must recieve a length vector with 2 non-zero dimensions and 1 zero dimension');
        hRectSurface = [];
    end
end

% Custom validation function
function mustHaveExactlyTwoNonZeroLengths(length)
    % Test for equal size
    if (nnz(length) ~= 2)
        eid = 'plotRectSurface:TwoNonZeroDimensions';
        msg = 'RectSurface must recieve a length vector with 2 non-zero dimensions and 1 zero dimension';
        throwAsCaller(MException(eid,msg))
    end
end