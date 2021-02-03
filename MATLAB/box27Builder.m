clear all;
clc;

i = 0;
for z = 0:2
    for y = 0:2
        for x = 0:2
            i = i + 1;
            region(i).Name = "Box" + num2str(x) + num2str(y) + num2str(z);
            region(i).Shape = CreateBox(x, y, z);
            region(i).SurfaceTypes = "@G:SurfaceTypesReflecting";
            region(i).DiffusionCoefficients = "@G:DiffusionCoefficients";
            region(i).NumberOfSubvolumes = "@G:NumberOfSubvolumes";
            region(i).TimeStep = "@G:TimeStep";
            region(i).Priority = "@G:RegionPriority";
        end
    end
end

j = jsonencode(region);


%%

clear all;
clc;

i = 0;
for z1 = 0:2
    for y1 = 0:2
        for x1 = 0:2
            for z2 = 0:2
                for y2 = 0:2
                    for x2 = 0:2
                        if((abs(diff([x1, x2])) + abs(diff([y1, y2])) + abs(diff([z1, z2]))) == 1)
                            i = i + 1;
                             r(i).RegionA = "Box" + num2str(x1) + num2str(y1) + num2str(z1);
                             r(i).RegionB = "Box" + num2str(x2) + num2str(y2) + num2str(z2);
                             r(i).Priority = "None";
                             r(i).SurfaceTypes = "@G:SurfaceTypesNone";
                        end
                    end
                end
            end
        end
    end
end

j = jsonencode(r);

function shape = CreateBox(x, y, z)
    shape.Type= "Box";
    shape.Origin = [x, y, z];
    shape.Length = [1, 1, 1];
end


