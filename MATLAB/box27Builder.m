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

%%
clear all;
clc;

% specify bounding volume for the passive actors to observe
volumeOrigin = [0, 0, 0]; volumeLength = [1, 1, 1];
% specify the number of passive actors per dimension (x, y, z)
resolution = [10, 10, 10];
% calculate length of each passive actor
actorLength = volumeLength ./ resolution;
% i = iterator, p = passive actor
i = 0;
for z = volumeOrigin(3):actorLength(3):volumeLength(3)
    for y = volumeOrigin(2):actorLength(2):volumeLength(2)
        for x = volumeOrigin(1):actorLength(1):volumeLength(1)
            i = i + 1;
            % define passive actor shape
            p(i).shape.Type= "Box";
            p(i).shape.Origin = [x, y, z];
            p(i).shape.Length = actorLength;
            % define other properties...
            p(i).RecordPositions = "@G:RecordPositions";
            p(i).RecordObservationTime = "@G:RecordObservationTime";
            p(i).StartTime = "@G:StartTime";
            p(i).TimeStep = "@G:TimeStep";
            p(i).Priority = "@G:RegionPriority";
        end
    end
end
% encode passive actor struct into JSON format
j = jsonencode(p);



function shape = CreateBox(x, y, z)
    shape.Type= "Box";
    shape.Origin = [x, y, z];
    shape.Length = [1, 1, 1];
end



