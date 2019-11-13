%The MIT License (MIT)
%
% Copyright (c) January, 2014 michael otte
%
% Permission is hereby granted, free of charge, to any person obtaining a copy
% of this software and associated documentation files (the "Software"), to deal
% in the Software without restriction, including without limitation the rights
% to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
% copies of the Software, and to permit persons to whom the Software is
% furnished to do so, subject to the following conditions:
%
% The above copyright notice and this permission notice shall be included in
% all copies or substantial portions of the Software.
% 
% THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
% IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
% FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
% AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
% LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
% OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
% THE SOFTWARE.



% this generates a file that contains random discoverable obstacles
% i.e., some are always obstacles, others are only discovered
% when the robot gets close, others vanish when the robot gets close
outputFile = './environments/rand_Disc_grid_.txt';    % file to save
environmentSpansRaw = [-50, 50, -50, 50];           % [xmin, xmax, ymin, ymax]
drawBuffer = 5;                                  % draw this much area around environmentSpans

environmentSpans = environmentSpansRaw + [-1 1 -1 1]*drawBuffer;
envspnsX = environmentSpansRaw([1,1,2,2,1]);
envspnsY = environmentSpansRaw([4,3,3,4,4]);


figure(1)
clf
plot(envspnsX, envspnsY, '--k')
axis(environmentSpans)
uicontrol('Style', 'pushbutton', 'String', 'Done (hit 2x)','Position', [10 10 100 20],'Callback', 'done = true');

done = false;
numObstacles = 0;
while done == false
    numObstacles = numObstacles + 1;
    numPoints = 4;
    
    pointsX{numObstacles} = nan(4,1);
    pointsY{numObstacles} = nan(4,1);
    for p = 1:numPoints 
            
        [x,y,B] = ginput(1);
        
        if done == true
            numObstacles = numObstacles - 1;
            break
        end
        
        pointsX{numObstacles}(p) = x;
        pointsY{numObstacles}(p) = y;
        
        if B == 1
            obsBehaviourType{numObstacles} = 0;
        elseif B == 2
            obsBehaviourType{numObstacles} = -1;
        else
            obsBehaviourType{numObstacles} = 1;
        end
        
        
        % draw what we have so far
        plot(envspnsX, envspnsY, '--k')
        axis(environmentSpans)
        hold on
        for m = 1:numObstacles
            
            if obsBehaviourType{m}  == 0
                pltclr = 'k';
            elseif obsBehaviourType{m}  == -1
                pltclr = 'g';
            elseif obsBehaviourType{m} == 1
                pltclr = 'r';
            end
            
            plot([pointsX{m}; pointsX{m}(1)], [pointsY{m}; pointsY{m}(1)], pltclr)
        end
        hold off
    end
    
    if done == true
        break 
    end
end

% save data to file
fileID = fopen(outputFile,'w');
fprintf(fileID,'%d\n', numObstacles);
for n = 1:numObstacles
    A = [pointsX{n}, pointsY{n}]';
    fprintf(fileID,'%d\n', numPoints);
    fprintf(fileID,'%f, %f\n', A);
    fprintf(fileID,'%d\n', obsBehaviourType{n});
end
fclose(fileID);


plot(envspnsX, envspnsY, '--k')
axis(environmentSpans)
hold on
for n = 1:numObstacles
    
    if obsBehaviourType{n}  == 0
        pltclr = 'k';
    elseif obsBehaviourType{n}  == -1
        pltclr = 'g';
    elseif obsBehaviourType{n} == 1
        pltclr = 'r';
    end
    
    plot([pointsX{n}; pointsX{n}(1)], [pointsY{n}; pointsY{n}(1)], pltclr)
end
hold off

