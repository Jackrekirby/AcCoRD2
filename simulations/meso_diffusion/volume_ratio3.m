clear all;
clc;
n = 0;
samples = 10000;
molecules = 1000;
hold on;
for relativeVolume = [0.1:0.1:0.9]
    n = n + 1;
    b(1:(molecules + 1)) = 0; 
    y = sum(rand(molecules, samples) < relativeVolume, 1);
    for i = 1:samples
        b(y(i) + 1) = b(y(i) + 1) + 1;
    end
    plot(linspace(0, 1, molecules + 1), b ./ samples);
end
hold off;
title('Mean Number Of Molecules Observed By Passive Actor');
xlabel('Portion of Subvolume Observed');
ylabel('Probability Passive Actor Observed A Given Molecule Count');
%ylim([0, 1]);







