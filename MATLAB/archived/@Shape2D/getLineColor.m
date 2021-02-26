function color = getLineColor(obj)
    if(strcmp(obj.LineColor, 'random'))
        color = obj.LineColorMap(obj.LineColorMapIndex, :);
        obj.LineColorMapIndex = obj.LineColorMapIndex + 1;
        if(obj.LineColorMapIndex > size(obj.LineColorMap, 1))
            obj.LineColorMapIndex = 1;
        end
    else
        color = obj.LineColor;
    end
end