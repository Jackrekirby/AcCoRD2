function color = getFaceColor(obj)
    if(strcmp(obj.FaceColor, 'random'))
        color = obj.FaceColorMap(obj.FaceColorMapIndex, :);
        obj.FaceColorMapIndex = obj.FaceColorMapIndex + 1;
        if(obj.FaceColorMapIndex > size(obj.FaceColorMap, 1))
            obj.FaceColorMapIndex = 1;
        end
    else
        color = obj.FaceColor;
    end
end