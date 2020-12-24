 function hBox = plotBox(obj, origin, length, args)
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, -0.5];
        length (1, 3) double = [1, 1, 1];
        args.FaceAlpha double = obj.FaceAlpha;
        args.EdgeAlpha double = obj.EdgeAlpha;
        args.LineColor = obj.getLineColor();
        args.FaceColors = obj.BoxFaceColors;
        args.FaceColor = getBoxFaceColor(obj);
    end

    max = origin + length;
    vertices = [origin; max(1), origin(2:3); max(1:2) origin(3);...
        origin(1) max(2) origin(3); origin(1:2) max(3); ...
        max(1) origin(2) max(3); max; origin(1) max(2:3)];
    faces = [1 2 6 5; 2 3 7 6; 3 4 8 7; 4 1 5 8; 1 2 3 4; 5 6 7 8];

    hBox = patch('Vertices', vertices, 'Faces', faces,...
      'FaceVertexCData', args.FaceColors, 'FaceColor', args.FaceColor, ...
      'EdgeColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
      'EdgeAlpha', args.EdgeAlpha);
end

function faceColor = getBoxFaceColor(obj)
    if(obj.ColorPerBoxFace)
        faceColor = 'flat';
    else
        faceColor = obj.getFaceColor();
    end
end