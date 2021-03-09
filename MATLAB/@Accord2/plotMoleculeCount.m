 function [hPlots] = plotMoleculeCount(data, colormap, plotMeanOnly)
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
    colors = colormap(nPlots);
    legendLabels{nPlots} = "";
    hPlots(nPlots) = 0;
    
    % Track index of current plot
    iPlot = 0;
    hold on;
    % plot individual realisatiosn first so mean plots are at front
    if(~plotMeanOnly)
        % For each passive actor
        for iP = 1:nP
            nM = length(counts(iP).m);
            % for each molecule type
            for iM = 1:nM
                if(~isempty(counts(iP).m(iM).c))
                    iPlot = iPlot + 1;
                    % plot each realisation count individually
                    % make line colour brighter
                    c = colors(iPlot, :) + 0.8; c(c>1) = 1;
                    plot(data.s(1).r(1).p(iP).t, counts(iP).m(iM).c(:, :), ...
                    'Color', c, 'LineStyle', '-');
                end
            end
        end
    end
    iPlot = 0;
    % For each passive actor
    for iP = 1:nP
        nM = length(counts(iP).m);
        % for each molecule type
        for iM = 1:nM
            if(~isempty(counts(iP).m(iM).c))
                iPlot = iPlot + 1;
                % plot mean count of all realisations
                hPlot = plot(data.s(1).r(1).p(iP).t, mean(counts(iP).m(iM).c, 2), ...
                    'Color', colors(iPlot, :), 'LineWidth', 1);
                if(nP == 1)
                    legendLabels{iPlot} = "M:" + num2str(iM);
                elseif(nM == 1)
                    legendLabels{iPlot} = "P:" + num2str(iP);
                else
                    legendLabels{iPlot} = "P:" + num2str(iP) + ", M:" + num2str(iM);
                end
                hPlots(iPlot) = hPlot;
            end
        end
    end
    hold off;
    % Detail Figure
    title("Molecule Counts");
    xlabel("Time (s)");
    ylabel("Molecule Count");
    leg = legend(hPlots, legendLabels);
    
    if(nP == 1)
        title(leg,{'Molecule Type: #'});
    elseif(nM == 1)
        title(leg,{'Passive Actor: #'});
    else
        title(leg,{'Passive Actor: #','Molecule Type: #'});
    end
    
    grid on;
    axis square;
    ax = gca;
    ax.XColor = [0, 0, 0];
    ax.YColor = [0, 0, 0];
end