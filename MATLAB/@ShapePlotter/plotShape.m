function [hShape] = plotShape(obj, shape)
    % plotShape.m - is passed a shape from the json config file and it
    % will plot the shape, given a shape 'Type'
    
    % INPUTS
    % obj - a ShapePlotter object, which contains default style arguments
    % shape - a struct containing the 'Type' along with the required
    %   arguments to construct the shape. See the corresponding plot
    %   functions to see the requirements of each shape function.
    
    hShape = [];
    if(shape.Type == "Box" || shape.Type == "BoxSurface")
        hShape = obj.plotBox(shape.Origin, shape.Length);
    elseif(shape.Type == "Sphere" || shape.Type == "SphereSurface")
        hShape = obj.plotSphere(shape.Centre, shape.Radius);
    elseif(shape.Type == "Cylinder" || shape.Type == "CylinderSurface")
        hShape = obj.plotCylinder(shape.BaseCentre, shape.Radius, shape.Length, shape.Axis);
    elseif(shape.Type == "RectSurface")
        hShape = obj.plotRectSurface(shape.Origin, shape.Length);
    elseif(shape.Type == "CircleSurface")
        hShape = obj.plotCircleSurface(shape.Centre, shape.Radius, shape.Axis);
    elseif(shape.Type == "Point")
        hShape = obj.plotPoint(shape.Origin);
    else
        warning("plotShape only plots shapes of type Box(Surface), Sphere(Surface), Cylinder(Surface), RectSurface, CircleSurface or Point");
    end
end