clear all; clc;
% specify bounding volume for the passive actors to observe
volumeOrigin = [0, 0, 0]; volumeLength = [1, 1, 1];
volumeCentre = volumeOrigin + 0.5 * volumeLength;
% specify the number of passive actors per dimension (x, y, z)
resolution = [5, 5, 5];
% calculate length of each passive actor
actorLength = volumeLength ./ resolution;
volumeLength = volumeLength - actorLength;
% i = iterator, p = passive actor
i = 0;
for z = volumeOrigin(3):actorLength(3):volumeLength(3)
    for y = volumeOrigin(2):actorLength(2):volumeLength(2)
        for x = volumeOrigin(1):actorLength(1):volumeLength(1)
            i = i + 1;
            c(i, :) = [x, y, z];
        end
    end
end
[val, ind] = sort(sum((c - 0.5 * volumeLength).^2, 2));
uniquePassiveActorDistances = length(unique(round(val, 4)));
c = c(ind, :);

for i = 1:length(ind)
    % define passive actor shape
    p(i).Shape.Type= "Box";
    p(i).Shape.Origin = round(c(i, :), 3);
    p(i).Shape.Length = actorLength;
    % define other properties...
    p(i).RecordPositions = "@R:RecordPositions";
    p(i).RecordObservationTime = "@R:RecordObservationTime";
    p(i).StartTime = "@R:StartTime";
    p(i).TimeStep = "@R:TimeStep";
    p(i).Priority = "@R:RegionPriority";
    p(i).MoleculeTypesToObserve = "@R:MoleculeTypesToObserve";
end
% encode passive actor struct into JSON format
j = jsonencode(p);