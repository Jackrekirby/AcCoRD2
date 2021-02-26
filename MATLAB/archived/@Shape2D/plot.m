 function plot(obj, jsonFilePath)
    j = jsondecode(fileread(jsonFilePath));
    if(isfield(j.shapes, 'circle') || isfield(j.shapes, 'rect'))
        figure; 
        hold on;
        disp("Drawing 2D Environment");
        if(isfield(j.shapes, 'circle'))
            for i = 1:size(j.shapes.circle, 2)
                obj.plotCircle(j.shapes.circle(i).centre, j.shapes.circle(i).radius);
            end
        end
        if(isfield(j.shapes, 'rect'))
            for i = 1:size(j.shapes.rect, 2)
                obj.plotRect(j.shapes.rect(i).origin, j.shapes.rect(i).length);
            end
        end
        hold off;
        xlabel('x');
        ylabel('y');
        axis equal;
    end
end