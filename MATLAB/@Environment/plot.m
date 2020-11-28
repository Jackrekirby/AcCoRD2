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

    if(isfield(j.shapes, 'box') || isfield(j.shapes, 'sphere') || ...
            isfield(j.shapes, 'rectSurface') || isfield(j.shapes, 'circleSurface'))
        figure; 
        hold on;
        disp("Drawing 3D Environment");
        if(isfield(j.shapes, 'box'))
            for i = 1:size(j.shapes.box, 2)
                obj.plotBox(j.shapes.box(i).origin, j.shapes.box(i).length);
            end
        end
        if(isfield(j.shapes, 'sphere'))
            for i = 1:size(j.shapes.sphere, 2)
                obj.plotSphere(j.shapes.sphere(i).centre, j.shapes.sphere(i).radius);
            end
        end
        if(isfield(j.shapes, 'rectSurface'))
            for i = 1:size(j.shapes.rectSurface, 2)
                obj.plotRectSurface(j.shapes.rectSurface(i).origin, j.shapes.rectSurface(i).length);
            end
        end
        if(isfield(j.shapes, 'circleSurface'))
            for i = 1:size(j.shapes.circleSurface, 2)
                obj.plotCircleSurface(j.shapes.circleSurface(i).centre, j.shapes.circleSurface(i).radius, j.shapes.circleSurface(i).axis);
            end
        end
        hold off;
        xlabel('x');
        ylabel('y');
        zlabel('z');
        axis equal;
        view(45,30);
    end
end

