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


% this generates a file that contains random dynamic obstacles

outputFile = './environments/rand_.txt';       % file to save 

environmentSpans = [-50, 50, -50, 50];           % [xmin, xmax, ymin, ymax]
timeSpan = 20;                                  % length of run (seconds)

numObstacles = 50;                              % number of obstacles
lifeSpanBounds = [2 10];                        % in seconds

maxPointsPerPolygon = 10;                       % paramiters for generating a polygon obstacle
minPointsPerPolygon = 3;
minPolygonRadius = 5;
maxPolygonRadius = 20;


fileID = fopen(outputFile,'w');
fprintf(fileID,'%d\n', numObstacles);
for n = 1:numObstacles
    MaxRadius = minPolygonRadius + rand(1,1)*(maxPolygonRadius - minPolygonRadius);
    numPoints = minPointsPerPolygon+ floor(rand(1,1)*(maxPointsPerPolygon-minPointsPerPolygon));
   
    % define a loose center point
    centerPoint = [environmentSpans(1), environmentSpans(3)] + rand(1,2).*[environmentSpans(2) - environmentSpans(1), environmentSpans(4) - environmentSpans(3)];


    % first pick numPoints angles, these will define the angle of a ray
    % emminating from -environmentSpan environmentSpan -environmentSpan environmentSpancenterPoint
    rayAngles = sort(rand(numPoints,1)*2*pi);

    % now randomly place the polygon's points a rand value between 0 and MaxRadius
    % along each ray
    distances = sqrt(rand(numPoints,1))*MaxRadius;

    pointsX{n} = distances.*cos(rayAngles) + centerPoint(1);
    pointsY{n} = distances.*sin(rayAngles) + centerPoint(2);

    A = [pointsX{n}, pointsY{n}]';
    fprintf(fileID,'%d\n', numPoints);
    fprintf(fileID,'%f, %f\n', A);
    
    startTime = rand()*timeSpan;
    lifeSpan = lifeSpanBounds(1) + rand()*(lifeSpanBounds(2)-lifeSpanBounds(1));
    
    startTimes{n} = startTime;
    
    fprintf(fileID,'%f, %f\n', startTime, lifeSpan);
end

fclose(fileID);

figure(1)
plot([pointsX{1}; pointsX{1}(1)], [pointsY{1}; pointsY{1}(1)])
axis(environmentSpans)
hold on
for n = 2:numObstacles
plot([pointsX{n}; pointsX{n}(1)], [pointsY{n}; pointsY{n}(1)])
end
hold off

figure(2)
plot3([pointsX{1}; pointsX{1}(1)], [pointsY{1}; pointsY{1}(1)], startTimes{1}*ones(size(pointsY{1},1) + 1, 1))
axis([environmentSpans 0 timeSpan])
hold on
for n = 2:numObstacles
plot3([pointsX{n}; pointsX{n}(1)], [pointsY{n}; pointsY{n}(1)], startTimes{n}*ones(size(pointsY{n},1) + 1, 1))
end
hold off
