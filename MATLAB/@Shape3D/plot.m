function hFigure = plot(obj, jsonFilePath)
    j = jsondecode(fileread(jsonFilePath));
    hFigure = figure; 
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