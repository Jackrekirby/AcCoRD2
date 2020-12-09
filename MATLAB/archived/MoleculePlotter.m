classdef MoleculePlotter < handle
    properties
        PassiveActor
        ObservationTimes
        PlayBackSpeed
        hFigure
        
        Directory
        SimulationName
    end
    
    methods (Access = public)
        function obj = MoleculePlotter(sim, seed, realisation, playBackSpeed)
            arguments
                sim
                seed = 1;
                realisation = 1;
                playBackSpeed = 1;
            end
            
            PassiveActor = sim.s([sim.s == seed]))
        end
        
        function plotRegions(obj, showFigure)
            regionDir = obj.Directory + "\" + obj.SimulationName + '\regions.json';
            s = Shape3D();
            s.plot(regionDir);
            if(showFigure)
                obj.hFigure.Visible = 'on';
            end
        end
        
        function plotMolecules(obj, colorByActor)
            obj.initilisePassiveActorPlots(colorByActor);
            
            simulationTime = 0;
            % list of indicies of all the actors to render in next update
            actorsToRender = [];
            obj.hFigure.Visible = 'on';
            tic;
            % keep rendering until all observations have been rendered
            while(min(obj.ObservationTimes) ~= Inf)
                [observationTime, id] = min(obj.ObservationTimes);

                % if the next actor's time is ahead of the current simulation time then
                % render all the actor observations from the current simulation time
                % before going onto the next actor
                
                if(observationTime > simulationTime)
                    % display the simulation time in the window name
                    obj.hFigure.Name = "Simulation Time: " + simulationTime;

                    for i = 1:length(actorsToRender)
                        actor_id = actorsToRender(i);
                        for j = 1:length(obj.PassiveActor(actor_id).moleType)
                            % only attempt to update plot if passive actor
                            % includes the molecule type
                            if(~isempty(obj.PassiveActor(actor_id).moleType(j).positions))
                                positions = Simulation.GetPositions(obj.PassiveActor(actor_id).moleType(j), ...
                                    obj.PassiveActor(actor_id).timeIndex - 1);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.XData = positions(1, :);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.YData = positions(2, :);
                                obj.PassiveActor(actor_id).moleType(j).hPlot.ZData = positions(3, :);
                            end
                        end
                    end

                    % now figure is about to be updated actorsToRender can
                    % be emptied
                    actorsToRender = [];

                    % if real time is ahead of simulation time wait
                    while(simulationTime / obj.PlayBackSpeed > toc)
                        pause(0.01 * ((simulationTime / obj.PlayBackSpeed) - toc));
                    end
                    simulationTime = observationTime;
                    drawnow limitrate;
                end

                actorsToRender = [actorsToRender, id];
                % update actors next observation time or set to Inf is no
                % observations left
                obj.PassiveActor(id).timeIndex = obj.PassiveActor(id).timeIndex + 1;
                if(obj.PassiveActor(id).timeIndex > size(obj.PassiveActor(id).times, 1) )
                    obj.ObservationTimes(id) = Inf;
                else
                    obj.ObservationTimes(id) = ... 
                        obj.PassiveActor(id).times(obj.PassiveActor(id).timeIndex);
                end
            end

            obj.hFigure.Name = "Simulation Time: " + simulationTime + " (Complete)";
        end
        
        function initialiseFigure(obj, limits)
            obj.hFigure = figure('visible','off', 'Name', ...
                'Simulation Time:','NumberTitle','off');
            plot3(0, 0, 0, 'Marker', 'none');
            xlabel('x');
            ylabel('y');
            zlabel('z');
            axis equal;
            view(45,30);
            a = [-limits, limits];
            xlim(a); zlim(a); ylim(a);
        end
    end
    
    
    methods (Access = private)
        function initilisePassiveActorPlots(obj, colorByActor)
            % calculate the number of molecule types
            if(colorByActor)
                moleculeColormap = hsv(length(obj.PassiveActor));
            else
                nMoleculeTypes = 0;
                for i = 1:length(obj.PassiveActor)
                    if(length(obj.PassiveActor(i).moleType) > nMoleculeTypes)
                        nMoleculeTypes = length(obj.PassiveActor(i).moleType);
                    end
                end

                moleculeColormap = hsv(nMoleculeTypes);
            end
            
            hold on;
            for i = 1:length(obj.PassiveActor)
                % if passive actor time is not recorded than it cannot be visualised so
                % is ignored by setting its next observation time to infinite
                if(isfield(obj.PassiveActor(i), 'times'))
                    obj.PassiveActor(i).timeIndex = 1;
                    obj.ObservationTimes(i) = ... 
                        obj.PassiveActor(i).times(1);
                    
                    for j = 1:length(obj.PassiveActor(i).moleType)
                        if(colorByActor)
                            c = i;
                        else
                            c = j;
                        end
                        obj.PassiveActor(i).moleType(j).hPlot = ...
                            plot3(0, 0, 0, 'Marker', 'o', 'LineStyle', 'none', ...
                            'MarkerEdgeColor', moleculeColormap(c, :));
                        % clear plot marker data
                        obj.PassiveActor(i).moleType(j).hPlot.XData = [];
                        obj.PassiveActor(i).moleType(j).hPlot.YData = [];
                        obj.PassiveActor(i).moleType(j).hPlot.ZData = [];
                    end
                else
                    obj.ObservationTimes(i) = Inf;
                end
            end
            hold off;
        end
    
        function positions = GetPositions(moleculeType, timeIndex)
            positions = moleculeType.p(:, ...
                moleculeType.i(timeIndex)+1:moleculeType.i(index + 1));
        end
    end
end

