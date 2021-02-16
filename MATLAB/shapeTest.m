clear all;
clc;

sp = ShapePlotter();

shape.Type = 'Point';
shape.Origin = [0, 0, 0];
sp.plotShape(shape);
view(3);
axis equal;