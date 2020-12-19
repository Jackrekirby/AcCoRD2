function hPlots = plot(obj, shapes)
    j = 1;
    hPlots = [];
    hold on;
    if(isfield(shapes, 'box'))
        for i = 1:length(shapes.box)
            hPlots.box(i) = obj.plotBox(shapes.box(i).origin, shapes.box(i).length);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'sphere'))
        for i = 1:length(shapes.sphere)
            hPlots.sphere(i) = obj.plotSphere(shapes.sphere(i).centre, shapes.sphere(i).radius);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'cylinder'))
        for i = 1:length(shapes.cylinder)
            hPlots.cylinder(i) = obj.plotCylinder(shapes.cylinder(i).base_centre, ...
                shapes.cylinder(i).radius, shapes.cylinder(i).length, shapes.cylinder(i).axis);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'rectSurface'))
        for i = 1:length(shapes.rectSurface)
            hPlots.rectSurface(i) = obj.plotRectSurface(shapes.rectSurface(i).origin, shapes.rectSurface(i).length);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'circleSurface'))
        for i = 1:length(shapes.circleSurface)
            hPlots.circleSurface(i) = obj.plotCircleSurface(shapes.circleSurface(i).centre, ...
                shapes.circleSurface(i).radius, a.shapes.circleSurface(i).axis);
            j = j + 1;
        end
    end
    hold off;
end