function hFigure = plot(obj, jsonFilePath)
    j = jsondecode(fileread(jsonFilePath));
    hFigure = figure; 
    hold on;
    disp("Drawing 3D Environment");
    if(isfield(j.shapes, 'box'))
        size(j.shapes.box, 2)
        for i = 1:length(j.shapes.box)
            obj.plotBox(j.shapes.box(i).origin, j.shapes.box(i).length);
        end
    end
    if(isfield(j.shapes, 'sphere'))
        for i = 1:length(j.shapes.sphere)
            obj.plotSphere(j.shapes.sphere(i).centre, j.shapes.sphere(i).radius);
        end
    end
    if(isfield(j.shapes, 'rectSurface'))
        for i = 1:length(j.shapes.rectSurface)
            obj.plotRectSurface(j.shapes.rectSurface(i).origin, j.shapes.rectSurface(i).length);
        end
    end
    if(isfield(j.shapes, 'circleSurface'))
        for i = 1:length(j.shapes.circleSurface)
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