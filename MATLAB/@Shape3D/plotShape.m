function plotShape(obj, shape)
    if(shape.Type == "Box" || shape.Type == "BoxSurface")
        obj.plotBox(shape.Origin, shape.Length);
    elseif(shape.Type == "Sphere" || shape.Type == "SphereSurface")
        obj.plotSphere(shape.Centre, shape.Radius);
    elseif(shape.Type == "Cylinder" || shape.Type == "CylinderSurface")
        obj.plotCylinder(shape.BaseCentre, shape.Radius, shape.Length, shape.Axis);
    elseif(shape.Type == "RectSurface")
        obj.plotRectSurface(shape.Origin, shape.Length);
    elseif(shape.Type == "CircleSurface")
        obj.plotCircleSurface(shape.Centre, shape.Radius, shape.Axis);
    elseif(shape.Type == "Point")
    else
        warning("Shape must be Box, Sphere or Cylinder");
    end
end