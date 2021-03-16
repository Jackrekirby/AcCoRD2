clear all; clc;
%% Step 1: Define the environment properties
% Specify bounding volume for the passive actors to observe
volumeOrigin = [0, 0, 0]; volumeLength = [1, 1, 1];
% Specify the number of passive actors per dimension (x, y, z)
resolution = [5, 5, 5];

%% Step 2: Calculate the positions of each passive actor and sort them by 
% ... their distance from the centre of the bounding volume
% Calculate the centre of the bounding volume
volumeCentre = volumeOrigin + 0.5 * volumeLength;
% Calculate length of each passive actor
actorLength = volumeLength ./ resolution;

% Create a grid of all the origin nodes for each passive actor box
[y, x, z] = meshgrid(0:resolution(1)-1, 0:resolution(2)-1, 0:resolution(3)-1);
% Convert integer node positions to passive actor positions
actorOrigins = volumeOrigin + [x(:), y(:), z(:)] .* actorLength;
% Calculate the centre position of each passive actor
actorCentres = actorOrigins + 0.5 * actorLength;
% Sort the passive actors by the distance from their centre to the centre
% ... of the bounding volume
[val, ind] = sort(sum((actorCentres - volumeCentre).^2, 2));
% Calculate the number of unique passive actor distances from centre
% Distances are rounded to avoid floating point error
numUniqueDist = length(unique(round(val, 3)));
disp("No. of Unique Passive Actor Distances From Centre: " + numUniqueDist);
sortedActorOrigins = actorOrigins(ind, :);

%% Step 3: Create each passive actor object
numPassiveActors = prod(resolution);
% Define passive actor properties that apply to all of them
p.Shape.Type = "Box";
p.Shape.Length = actorLength;
% Use reference variables so they can easily be edited inside config file
p.RecordPositions = "@R:RecordPositions";
p.RecordObservationTime = "@R:RecordObservationTime";
p.StartTime = "@R:StartTime";
p.TimeStep = "@R:TimeStep";
p.Priority = "@R:RegionPriority";
p.MoleculeTypesToObserve = "@R:MoleculeTypesToObserve";
passiveActors(1:numPassiveActors) = p;
% Define passive actor properties that are unique to each
for i = 1:length(ind)
   % Define passive actor origin
   % Origin is rounded to avoid introducing floating point error
   passiveActors(i).Shape.Origin = round(sortedActorOrigins(i, :), 3);
end

%% Step 4: Encode array of passive actor objects into JSON format
% Copy and paste JSON string into configuration file
json = "PassiveActors:" + jsonencode(passiveActors);
disp(json);

