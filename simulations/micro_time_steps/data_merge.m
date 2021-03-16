clear all;
clc;
highres = load('highres_data.mat');
medres = load('medres_data.mat');
lowres = load('lowres_data.mat');

times = highres.data.s.r(1).p.t;
mol.high(3, 1001) = 0;
mol.med(3, 1001) = 0;
mol.low(3, 1001) = 0;
for i = 1:100
    for j = 1:3
        mol.high(j, :) = mol.high(j, :) + highres.data.s.r(i).p.m(j).c';
        mol.med(j, :) = mol.med(j, :) + medres.data.s.r(i).p.m(j).c';
        mol.low(j, :) = mol.low(j, :) + lowres.data.s.r(i).p.m(j).c';
    end
end
mol.high = mol.high / 100;
mol.med = mol.med / 100;
mol.low = mol.low / 100;

%tiledlayout(1,3, 'TileSpacing', 'compact');
titles = ["Molecule Counts of Type 1", ...
    "Molecule Counts of Type 2", ...
    "Molecule Counts of Type 2"];
for i = 1:3
    figure;
    plot(times, mol.high(i, :), 'Color', [1, 0, 0]);
    hold on;
    plot(times, mol.low(i, :), 'Color', [0, 0, 1]);
    plot(times, mol.med(i, :), 'Color', [0, 1, 0]);
    hold off;
    
    % Detail Figure
    title(titles(i));
    xlabel("Time (s)");
    ylabel("Molecule Count");
    grid on;
    axis square;
    ax = gca;
    ylim([65, Inf]);
    ax.XColor = [0, 0, 0];
    ax.YColor = [0, 0, 0];
    leg = legend("High, High", "Low, Low", "High, Low", 'Location','SouthWest');
    title(leg,{'Time Step Resolution','(Child, Parent)'});
       
end



