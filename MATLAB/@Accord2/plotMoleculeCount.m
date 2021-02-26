 function [hPlots] = plotMoleculeCount(data, plotMeanOnly)
    counts = Accord2.groupMoleculeCounts(data);
    nP = length(counts);
    
    % Count the number of counts to plot (all passive actors per molecule type)
    nPlots = 0;
    % For each passive actor
    for iP = 1:nP
        nM = length(counts(iP).m);
        % for each molecule type
        for iM = 1:nM
            % only plot count if not empty
            if(~isempty(counts(iP).m(iM).c))
                nPlots = nPlots + 1;
            end
        end
    end
    
    % Create a colour map equal in length to number of plots
    colors = hsv(nPlots);
    legendLabels{nPlots} = "";
    hPlots(nPlots) = 0;
    
    % Track index of current plot
    iPlot = 0;
    hold on;
    % For each passive actor
    for iP = 1:nP
        nM = length(counts(iP).m);
        % for each molecule type
        for iM = 1:nM
            if(~isempty(counts(iP).m(iM).c))
                iPlot = iPlot + 1;
                % plot mean count of all realisations
                hPlot = plot(data.s(1).r(1).p(iP).t, mean(counts(iP).m(iM).c, 2), ...
                    'Color', colors(iPlot, :));
                legendLabels{iPlot} = "P:" + num2str(iP) + ", M:" + num2str(iM);
                hPlots(iPlot) = hPlot;
                % plot each realisation count individually
                if(~plotMeanOnly)
                    plot(data.s(1).r(1).p(iP).t, counts(iP).m(iM).c(:, :), ...
                    'Color', colors(iPlot, :), 'LineStyle', ':');
                end
            end
        end
    end
    hold off;
    
    % Detail Figure
    title("Molecule Counts");
    xlabel("Time (s)");
    ylabel("Molecule Count");
    leg = legend(hPlots, legendLabels);
    title(leg,{'Passive Actor: #','Molecule Type: #'});
    grid on;
end