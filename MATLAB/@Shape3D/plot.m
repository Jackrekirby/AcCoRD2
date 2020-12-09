function hPlots = plot(obj, shapes)
    j = 1;
    hPlots = [];
    hold on;
    if(isfield(shapes, 'box'))
        for i = 1:length(shapes.box)
            hPlots(j) = obj.plotBox(shapes.box(i).origin, shapes.box(i).length);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'sphere'))
        for i = 1:length(shapes.sphere)
            hPlots(j) = obj.plotSphere(shapes.sphere(i).centre, shapes.sphere(i).radius);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'rectSurface'))
        for i = 1:length(shapes.rectSurface)
            hPlots(j) = obj.plotRectSurface(shapes.rectSurface(i).origin, shapes.rectSurface(i).length);
            j = j + 1;
        end
    end
    if(isfield(shapes, 'circleSurface'))
        for i = 1:length(shapes.circleSurface)
            hPlots(j) = obj.plotCircleSurface(shapes.circleSurface(i).centre, ...
                shapes.circleSurface(i).radius, a.shapes.circleSurface(i).axis);
            j = j + 1;
        end
    end
    hold off;
end