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


% this generates a file that contains time obstacles
% left click to add points to obstacle and path, right click to finish
% current obstacle or path

clear all
close all

outputFile = './environments/rand_DynamicTime_.txt';    % file to save
environmentSpansRaw = [-50, 50, -50, 50];         % [xmin, xmax, ymin, ymax]
drawBuffer = 20;                                  % draw this much area around environmentSpans
obstacleSpeedMean = 12.0;                         % all obstacles are assumed to move at a constant velocity, this its its expected value
obstacleSpeedOffset = 5.0;                        % individual obstacles move up to +/- obstacleSpeedOffset different than obstacleSpeedMean  
invertTime = true;                                % if true then time is transformed: time = maxTime - time
maxTime  = 35;                                    % only used if invertTime is true

environmentSpans = environmentSpansRaw + [-1 1 -1 1]*drawBuffer;
envspnsX = environmentSpansRaw([1,1,2,2,1]);
envspnsY = environmentSpansRaw([4,3,3,4,4]);


figure(1) 
clf
plot(envspnsX, envspnsY, '--k')
axis(environmentSpans)
uicontrol('Style', 'pushbutton', 'String', 'Done (left click 2x)','Position', [10 10 140 20],'Callback', 'done = true');

done = false;
numObstacles = 0;
while done == false
    numObstacles = numObstacles + 1;
  
    pointsX{numObstacles} = [];
    pointsY{numObstacles} = [];
 
    pathX{numObstacles} = [];
    pathY{numObstacles} = [];
    
    obstacleSpeed{numObstacles} = obstacleSpeedMean - obstacleSpeedOffset + rand()*2*obstacleSpeedOffset;
    display(['this obstacle speed: ' num2str(obstacleSpeed{numObstacles})])
    % input obstacle perimiter
    numPoints = 0;
    B = 1;
    while B == 1 && done == false
        
        % draw what we have so far
        plot(envspnsX, envspnsY, '--k')
        axis(environmentSpans)
        hold on
        for m = 1:numObstacles-1        
            plot([pointsX{m}; pointsX{m}(1)], [pointsY{m}; pointsY{m}(1)], 'k')
            plot(pathX{m}, pathY{m}, 'r')
        end
        plot([pointsX{numObstacles}], [pointsY{numObstacles}], 'k')
        hold off
         
        [x,y,B] = ginput(1);
        
        if B ~= 1 || done == true
            break
        end
        
        numPoints = numPoints + 1;
        pointsX{numObstacles}(numPoints,:) = x;
        pointsY{numObstacles}(numPoints,:) = y;
       
    end
    
    if done == true
        break 
    end
    
    % input obstacle path (note that this is basically the -relative path-,
    % the first point of the path will be where the obstacle was defined.
    numPoints = 1;
    pathX{numObstacles} = mean(pointsX{numObstacles});
    pathY{numObstacles} = mean(pointsY{numObstacles});
    B = 1;
    while B == 1 && done == false
            
        % draw what we have so far
        plot(envspnsX, envspnsY, '--k')
        axis(environmentSpans)
        hold on
        for m = 1:numObstacles     
            plot([pointsX{m}; pointsX{m}(1)], [pointsY{m}; pointsY{m}(1)], 'k')
            plot(pathX{m}, pathY{m}, 'r')
        end
        hold off
        
        [x,y,B] = ginput(1);
        
        if B ~= 1 || done == true
            break
        end
        
        numPoints = numPoints + 1;
        pathX{numObstacles}(numPoints) = x;
        pathY{numObstacles}(numPoints) = y;
    end
end

if isempty(pathX{numObstacles})
    numObstacles = numObstacles - 1;
else
    pathX{numObstacles} = pathX{numObstacles}(1:end-1);
    pathY{numObstacles} = pathY{numObstacles}(1:end-1);
end

% draw final 2d
plot(envspnsX, envspnsY, '--k')
axis(environmentSpans)
hold on
for m = 1:numObstacles
    plot([pointsX{m}; pointsX{m}(1)], [pointsY{m}; pointsY{m}(1)], 'k')
    plot(pathX{m}, pathY{m}, 'r')
end
hold off


% now draw in 3d (note we need to transfrom to time)
for m = 1:numObstacles
    % transform so paths start at (0,0) which is the relative location
    pathX{m} = pathX{m} - pathX{m}(1);
    pathY{m} = pathY{m} - pathY{m}(1);
    
    
    % for each point in the path, we transform the robot based on its speed
    timeCords{m} = zeros(1,length(pathY{m}));
    for t = 2:length(pathY{m})
        timeCords{m}(t) = timeCords{m}(t-1) + sqrt((pathY{m}(t)-pathY{m}(t-1))^2 + (pathX{m}(t)-pathX{m}(t-1))^2)/obstacleSpeed{m};
    end
        
    if invertTime == true
        timeCords{m} = fliplr(maxTime - timeCords{m});
        pathX{m} = fliplr(pathX{m});
        pathY{m} = fliplr(pathY{m});
    end
    % now make an obstacle projected to each point in time that we have a
    % time coorinate for
    
    timeRobotX{m} = repmat(pointsX{m}', length(pathY{m}), 1) + repmat(pathX{m}', 1, length(pointsX{m}));
    timeRobotY{m} = repmat(pointsY{m}', length(pathY{m}), 1) + repmat(pathY{m}', 1, length(pointsX{m}));
    timeRobotZ{m} = repmat(timeCords{m}', 1, length(pointsX{m}));
end

figure(2)
plot3(envspnsX, envspnsY, zeros(size(envspnsX)))
hold on
for m = 1:numObstacles
    
    % put border of nans to make life easier
    thisTimeRobotX = nan([1,1]+size(timeRobotX{m}));
    thisTimeRobotY = nan([1,1]+size(timeRobotY{m}));
    thisTimeRobotZ = nan([1,1]+size(timeRobotZ{m}));
 
    thisTimeRobotX(1:size(timeRobotX{m},1), 1:size(timeRobotX{m},2)) = timeRobotX{m};
    thisTimeRobotY(1:size(timeRobotY{m},1), 1:size(timeRobotY{m},2)) = timeRobotY{m};
    thisTimeRobotZ(1:size(timeRobotZ{m},1), 1:size(timeRobotZ{m},2)) = timeRobotZ{m};

    thisTimeRobotXT = thisTimeRobotX';
    thisTimeRobotYT = thisTimeRobotY';
    thisTimeRobotZT = thisTimeRobotZ';
    
    for t = 1:length(timeCords{m})
        plot3(thisTimeRobotX(:), thisTimeRobotY(:), thisTimeRobotZ(:), '--c')
        plot3(thisTimeRobotXT(:), thisTimeRobotYT(:), thisTimeRobotZT(:), 'k')
    end
end
hold off


% save data to file
fileID = fopen(outputFile,'w');
fprintf(fileID,'%d\n', numObstacles);
for n = 1:numObstacles
    A = [pointsX{n}, pointsY{n}]';
    numPoints = size(pointsX{n},1);
    fprintf(fileID,'%d\n', numPoints);
    fprintf(fileID,'%f, %f\n', A);
    fprintf(fileID,'%f\n', obstacleSpeed{n});
    
    A = [pathX{n}', pathY{n}', timeCords{n}']';
    numPoints = size(pathX{n},2);
    fprintf(fileID,'%d\n', numPoints);
    fprintf(fileID,'%f, %f, %f\n', A);
    
end
fclose(fileID);





