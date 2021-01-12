 function hGrid = plotGriddedBox(obj, origin, length, nPartitions, args)
    arguments
        obj
        origin (1, 3) double = [-0.5, -0.5, -0.5];
        length (1, 3) double = [1, 1, 1];
        nPartitions (1, 3) double = [1, 1, 1];
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

    holdState = ishold; 
    hGrid.Outer = patch('Vertices', vertices, 'Faces', faces,...
      'FaceVertexCData', args.FaceColors, 'FaceColor', args.FaceColor, ...
      'EdgeColor', args.LineColor, 'FaceAlpha', args.FaceAlpha, ...
      'EdgeAlpha', args.EdgeAlpha);
  
    subvolumeLength = length ./ nPartitions;
    i = 0;
    hold on;
    for z = 0:nPartitions(3) - 1
        for y = 0:nPartitions(2) - 1
            for x = 0:nPartitions(1) - 1
                i = i + 1;
                hGrid.subvolume(i) = plotBox(obj, origin + [x, y, z] ...
                    .* subvolumeLength, subvolumeLength, ...
                    'FaceColors', args.FaceColors, 'FaceColor', args.FaceColor, ...
                    'LineColor', args.LineColor, 'FaceAlpha', 0, ...
                    'EdgeAlpha', args.EdgeAlpha);
            end
        end
    end
    if(~holdState)
        hold off;
    end
end

function faceColor = getBoxFaceColor(obj)
    if(obj.ColorPerBoxFace)
        faceColor = 'flat';
    else
        faceColor = obj.getFaceColor();
    end
end