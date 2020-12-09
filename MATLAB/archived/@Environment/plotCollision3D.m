function [hCollision3D] = plotCollision3D(obj, origin, intersection, reflection, finish, args)
    arguments
        obj
        origin
        intersection
        reflection
        finish
        args.colors = obj.defaultCollisionColors;
    end
    holdState = ishold();
    
    hCollision3D.reflectedPath = obj.plotPath3D([origin; intersection; reflection], ...
        'markerColors', args.colors(1:3), 'showMarkers', true);
    hold on;
    hCollision3D.endPath = obj.plotPath3D([intersection; finish], 'showMarkers', ...
        false, 'lineStyle', '--');
    hCollision3D.endPoint = obj.plotPoints3D(finish, 'color', args.colors{4});
    
    if(~holdState && args.showMarkers) 
        hold off;
    end
end