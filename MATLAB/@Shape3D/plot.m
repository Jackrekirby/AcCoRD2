function hPlots = plot(obj, shapes)
    %j = 1;
    hPlots = [];
    hold on;
    iBox = 0;
    iSphere = 0;
    iCylinder = 0;
    iRectSurface = 0;
    iCircleSurface = 0;
    for iShape = 1:length(shapes)
        if(length(shapes) == 1)
            shape = shapes;
        else
            shape = shapes{iShape};
        end
        type = shape.type;
        if(type == "box")
            iBox = iBox + 1;
            hPlots.box(iBox) = obj.plotBox(shape.origin, shape.length);
        end
        
        if(type == "sphere")
            iSphere = iSphere + 1;
            hPlots.sphere(iSphere) = obj.plotSphere(shape.centre, shape.radius);
        end
        
        if(type == "cylinder")
            iCylinder = iCylinder + 1;
            hPlots.cylinder(iCylinder) = obj.plotCylinder(shape.base_centre, ...
                    shape.radius, shape.length, shape.axis);
        end
        
        if(type == "rectSurface")
            iRectSurface = iRectSurface + 1;
            hPlots.rectSurface(iRectSurface) = obj.plotRectSurface(shape.origin, shape.length);
        end
        
        if(type == "circleSurface")
            iCircleSurface = iCircleSurface + 1;
            hPlots.circleSurface(iCircleSurface) = obj.plotCircleSurface(shape.centre, ...
                    shape.radius, a.shape.axis);
        end
    end
    
    hold off;
end