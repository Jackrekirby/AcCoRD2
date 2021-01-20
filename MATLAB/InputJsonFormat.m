% JSON FORMAT
clear all;
clc;
% #Region#1#Shape
s.NumberOfRepeats = 5;
s.FinalSimulationTime = 10;
s.RandomNumberSeed = 1;
s.NumberOfMoleculeTypes = 2;

a.DiffusionCoefficients = [1, 2];
a.MicroscopicTimeStep = 1;
s.DefaultProperties = a;


MicroscopicRegion.Name = "MicroRegion1";
MicroscopicRegion.Shape = "Box";
MicroscopicRegion.Origin = [0, 0, 0];
MicroscopicRegion.Length = [1, 1, 1]; 
MicroscopicRegion.SurfaceType = "Reflecting";
MicroscopicRegion.DiffusionCoefficients = [3, 4];
MicroscopicRegion.NumberOfSubvolumes = [1, 2, 3];
MicroscopicRegion.TimeStep = 0.1;
MicroscopicRegion.Priority = 0;

s.MicroscopicRegions(1) = MicroscopicRegion;

MesoscopicRegion.Name = "MesoRegion1";
MesoscopicRegion.Origin = [0, 0, 0];
MesoscopicRegion.SubvolumeLength = [1, 1, 1]; 
MesoscopicRegion.NumberOfSubvolumes = [1, 2, 3];
MesoscopicRegion.DiffusionCoefficients = [3, 4];
MesoscopicRegion.RemoveSubvolumes = 0; % should be automated in some way
MesoscopicRegion.Priority = 0;

s.MesoscopicRegions(1) = MesoscopicRegion;

PassiveActor.Name = "PassiveActor1";
PassiveActor.MoleculeTypesToObserve = [0, 2];
PassiveActor.StartTime = 0;
PassiveActor.Priority = 0;
PassiveActor.TimeStep = 0;
PassiveActor.RecordPositions = true;
PassiveActor.RecordObservationTime = true;
% Shapeless Actor
PassiveActor.RegionsToObserve = ["MicroRegion1", "MesoRegion1"];
% Shaped Actor
PassiveActor.Shape = "Box";
PassiveActor.Origin = [0, 0, 0];
PassiveActor.Length = [1, 1, 1];

s.PassiveActors(1) = PassiveActor;


            
ActiveActor.Name = "ActiveActor1";
ActiveActor.StartTime = 0;
ActiveActor.Priority = 0;
ActiveActor.ActionInterval = 0;
ActiveActor.ReleaseInterval = 0;
ActiveActor.ModulationStrength = 10;
ActiveActor.MoleculeTypesToRelease = [0, 1];
% Shapeless Actor
ActiveActor.RegionsToActIn = ["MicroRegion1", "MesoRegion1"];
% Shaped Actor
ActiveActor.Shape = "Box";
ActiveActor.Origin = [0, 0, 0];
ActiveActor.Length = [1, 1, 1];
% Non Random 
ActiveActor.Type = "NonRandom";
ActiveActor.NumModulationBits = 2;
ActiveActor.SlotInterval = 1;
ActiveActor.BitSequence = [1, 1, 0, 0, 1, 0, 0, 1];
% Random Bit
ActiveActor.Type = "RandomBit";
ActiveActor.NumModulationBits = 2;
ActiveActor.SlotInterval = 1;
ActiveActor.BitProbability = 0.5;
% Random Time
ActiveActor.Type = "RandomTime";

s.ActiveActors(1) = ActiveActor;
s.ActiveActors(2) = ActiveActor;

Relationship.RegionA = "MesoRegion1";
Relationship.RegionB = "MicroRegion1";
Relationship.Priority = "None";
Relationship.SurfaceTypes = ["Reflecting"];
Relationship.AToBSurfaceTypes = ["Reflecting"];
Relationship.BToASurfaceTypes = ["None", "Reflecting", "Absorbing"];

s.Relationship(1) = Relationship;
s.Relationship(2) = Relationship;

ZerothOrder.Products = [2, 3, 0];
ZerothOrder.ReactionRate = 4.6;
ZerothOrder.OccurInRegions = ["MicroRegion1", "MesoRegion1"];

FirstOrder.Reactant = 0;
FirstOrder.Products = [2, 3, 0];
FirstOrder.ReactionRate = 1.2;
FirstOrder.OccurInRegions = ["MicroRegion1", "MesoRegion1"];

SecondOrder.ReactantA = 0;
SecondOrder.ReactantB = 0;
SecondOrder.Products = [2, 3, 0];
SecondOrder.ReactionRate = 1.2;
SecondOrder.BindingRadius = 3;
SecondOrder.UnBindingRadius = 3.5;
SecondOrder.OccurInRegions = ["MicroRegion1", "MesoRegion1"];
            
s.ZerothOrderReactions(1) = ZerothOrder;
s.ZerothOrderReactions(2) = ZerothOrder;
s.FirstOrderReactions(1) = FirstOrder;
s.FirstOrderReactions(2) = FirstOrder;
s.SecondOrderReactions(1) = SecondOrder;
s.SecondOrderReactions(2) = SecondOrder;
            
jsonText = jsonencode(s);

filename = 'C:\dev\AcCoRD2\MATLAB\simulation_matlab.json';
fileID = fopen(filename, 'w');
fprintf(fileID, jsonText);
fclose(fileID);

s2 = jsondecode(fileread(filename));
