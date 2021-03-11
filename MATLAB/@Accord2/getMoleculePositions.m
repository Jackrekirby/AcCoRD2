function [positions] = getMoleculePositions(moleculeType, timeStep)
    % getMoleculePositions.m - gets the positions of all molecules at a 
    % given time step for a given molecule type observed by a passive actor
    
    % INPUTS
    % moleculeType - the simulation data from passive for a given molecule
    %   type
    % timeStep - the time step at which you wish to extract the molecule
    %   position data from the passive actor.
    
    % OUTPUTS
    % positions - the positions data of size (no. of molecules, 3) observed
    % by a passive actor for a given molecule type at a given time step
    
    positions = moleculeType.p(moleculeType.i(timeStep)+1:moleculeType.i(timeStep+1), :);
end