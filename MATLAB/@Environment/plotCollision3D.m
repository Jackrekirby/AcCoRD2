function [hCollision3D] = plotCollision3D(obj, origin, finish, intersection, reflection)
    holdState = ishold();
    
    hCollision3D.reflectedPath = obj.plotPath3D([origin; intersection; reflection], 'showMarkers', true);
    hold on;
    hCollision3D.endPath = obj.plotPath3D([intersection; finish], 'showMarkers', false, 'lineStyle', '--');
    hCollision3D.endPoint = obj.plotPoints3D(finish, 'color', 'm');
    
    if(~holdState && args.showMarkers) 
        hold off;
    end
end