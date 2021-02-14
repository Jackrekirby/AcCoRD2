function [positions] = getMoleculePositions(moleculeType, timestep)
    % Get the positions of all molecules at a given time step for a given
    % molecule type observed by a passive actor
    positions = moleculeType.p(moleculeType.i(timestep)+1:moleculeType.i(timestep+1), :);
end