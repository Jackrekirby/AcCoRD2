function [hBox] = plotBox(origin, length, args)
    arguments
        origin (1, 3) double = [-0.5, -0.5, -0.5];
        length (1, 3) double = [1, 1, 1];
        args.faceAlpha double = 0.5;
        args.edgeColor = 'k';
        args.faceColors = hsv(6);
        args.faceColor = 'flat';
    end
    
    max = origin + length;
    vertices = [origin; max(1), origin(2:3); max(1:2) origin(3);...
        origin(1) max(2) origin(3); origin(1:2) max(3); ...
        max(1) origin(2) max(3); max; origin(1) max(2:3)];
    faces = [1 2 6 5;2 3 7 6;3 4 8 7;4 1 5 8;1 2 3 4;5 6 7 8];
    
    hBox = patch('Vertices', vertices, 'Faces', faces,...
      'FaceVertexCData', args.faceColors, 'FaceColor', args.faceColor, ...
      'EdgeColor', args.edgeColor, 'FaceAlpha', args.faceAlpha);
  
    view(3);
end