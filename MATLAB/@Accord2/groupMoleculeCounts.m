function [counts] = groupMoleculeCounts(data)
    % groupMoleculeCounts.m - gets the molecule counts from all passive
    %   actives in each seed and realisation and groups them into a 2D matrix
    %   per passive actor per molecule types where each row is a given
    %   timestep, and each column is a realisation
    
    % INPUTS
    % data - the simulation data from passive and active actors
    
    % OUTPUTS
    % counts - the grouped count data from all seeds and realisations
    %   format: counts.m(moleculeID).c(timestep, realisation)
    
    % IMPORTANT NOTES
    % All realisations per seed are grouped into a combined list of
    % realisations
    
    nRealisations = 0;
    % For each seed
    for iS = 1:length(data.s)
        % for each realisation
        for iR = 1:length(data.s(iS).r)
            nRealisations = nRealisations + 1;
            % for each passive actor
            nP = length(data.s(iS).r(iR).p);
            for iP = 1:nP
                nM = length(data.s(iS).r(iR).p(iP).m);
                % for each molecule type
                for iM = 1:nM
                    % if molecule count recorded get count data
                    if(~isempty(data.s(iS).r(iR).p(iP).m(iM).c))
                        counts(iP).m(iM).c(:, nRealisations) = data.s(iS).r(iR).p(iP).m(iM).c;
                        % disp("s" + iS + ", r" + iR + ", p" + iP + ", m" + iM);
                    end
                end
            end
        end
    end
end