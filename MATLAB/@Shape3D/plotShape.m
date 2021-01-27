function plotShape(obj, shape)
    if(shape.Type == "Box")
        obj.plotBox(shape.Origin, shape.Length);
    elseif(shape.Type == "Sphere")
        obj.plotSphere(shape.Centre, shape.Radius);
    elseif(shape.Type == "Cylinder")
        obj.plotCylinder(shape.BaseCentre, shape.Radius, shape.Length, shape.Axis);
    elseif(shape.Type == "RectSurface")
        obj.plotRectSurface(shape.Origin, shape.Length);
    elseif(shape.Type == "CircleSurface")
        obj.plotCircleSurface(shape.Centre, shape.Radius, shape.Axis);
    else
        warning("Shape must be Box, Sphere or Cylinder");
    end
end