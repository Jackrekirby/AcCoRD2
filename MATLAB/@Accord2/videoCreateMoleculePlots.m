function [video] = videoCreateMoleculePlots(video, moleculeStyle)
    % Create the molecule colors either by actor or molecule type
    colorByActor = strcmp(moleculeStyle.colorMethod, 'actor');
    if(colorByActor)
        colors = hsv(length(video.p));
    else % if(strcmp(moleculeStyle.colorMethod, 'type'))
        % calculate the number of molecule types by checking the highest
        % molecule type of each passive actor
        nMoleculeTypes = 0;
        for iP = 1:length(video.p)
            if(length(video.p(iP).m) > nMoleculeTypes)
                nMoleculeTypes = length(video.p(iP).m);
            end
        end
        colors = hsv(nMoleculeTypes);
    end

    for iP = 1:length(video.p)
        % if passive actor time is not recorded than it cannot be visualised so
        % is ignored by setting its next observation time to infinite
        if(isfield(video.p(iP), 't'))
            video.p(iP).timeIndex = 1;
            video.observationTimes(iP) = video.p(iP).t(1);

            for iM = 1:length(video.p(iP).m)
                if(colorByActor)
                    iColor = iP;
                else
                    iColor = iM;
                end
                
                % Create a plot for each passive actor per molecule type
                video.p(iP).m(iM).hPlot = ...
                    scatter3(0, 0, 0, 'Marker', 'o', ...
                    'MarkerEdgeColor', colors(iColor, :), ...
                    'MarkerFaceColor', colors(iColor, :),...
                    'SizeData', moleculeStyle.size, ...
                    'MarkerFaceAlpha', moleculeStyle.fill);
                
                % Clear plot marker data
                video.p(iP).m(iM).hPlot.XData = [];
                video.p(iP).m(iM).hPlot.YData = [];
                video.p(iP).m(iM).hPlot.ZData = [];
            end
        else
            video.observationTimes(iP) = Inf;
        end
    end
end