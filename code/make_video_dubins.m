% The MIT License (MIT)
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


% this reads a series of saved files to help visualize search progress vs
% run time
clear all
close all

fig = figure(5);

costDim = 6; % this is the dimension of the nodes files that has cost
%costDim = 5; % this is the dimension of the nodes files that has cost
%costDim = 4; % this is the dimension of the nodes files that has cost

dir = 'temp/';

file_ctr = 2;
max_file_ctr = 387;

start_move_at_ctr = 100;

minXval = -50;
minYval = -50;
maxXval = 50;
maxYval = 50;
tickInterval = 10;

contourGranularity = 2.5; % x, y granularity for cost contour plot
%countorLevels = 0:1.5:130; % the countour levels
countorLevels = 0:3:320; % the countour levels

%sensor_radius = 20/contourGranularity;
sensor_radius = 10/contourGranularity;

% make a more accurate colormap, where costs above goal are grey
mycolormapsmall = jet;
mycolormap = zeros(length(countorLevels),3);
originalsamplevals = 0:length(mycolormapsmall)-1;
myresamplevalues = (0:length(countorLevels)-1)/(length(countorLevels)-1)*(length(mycolormapsmall)-1);
for c = 1:3
  mycolormap(:,c) = interp1(originalsamplevals, mycolormapsmall(:,c), myresamplevalues, 'pchip');
end




videoFill = true; % only uses cost in the negative y direction in center of image 
                  % to fill in missing cost so that don't get wierd stuff that 
                  % looks funnly due to contour interpolation

% open the video file
writerObj = VideoWriter( [dir 'Movie.avi']);
writerObj.FrameRate = 10;
open(writerObj);

while exist([dir 'robotMovePath_' num2str(file_ctr) '.txt'], 'file')  && file_ctr < max_file_ctr
    display(file_ctr)
  
    x_start = 0;
    y_start = -5;
    
    EdgeData = load([dir 'edges_' num2str(file_ctr) '.txt']);
    
    i = size(EdgeData,1);
    raw_x = EdgeData(1:i,1);
    raw_y = EdgeData(1:i,2);
    
    
    x = nan(i*1.5, 1);
    y = nan(i*1.5, 1);
    
    x(1:3:end-2) = raw_x(1:2:end-1);
    x(2:3:end-1) = raw_x(2:2:end);
    
    y(1:3:end-2) = raw_y(1:2:end-1);
    y(2:3:end-1) = raw_y(2:2:end);
    
    
%     % do not plot edges with inf cost
%     infinds = find(isinf(z));
%     x(infinds) = nan;
%     y(infinds) = nan;
    
    %figure(1)
    %plot3(x,y,z)
    
    
    NodeData = load([dir 'nodes_' num2str(file_ctr) '.txt']);
    
    j = size(NodeData,1);
    node_x = NodeData(1:j,1);
    node_y = NodeData(1:j,2);
    node_z = NodeData(1:j,costDim);

    if exist([dir 'CnodmoveGoales_' num2str(file_ctr) '.txt'], 'file') 
        CNodeData = load([dir 'Cnodes_' num2str(file_ctr) '.txt']);
    else
        CNodeData = [];
    end
    
    j = size(CNodeData,1);
    if j > 0
        Cnode_x = CNodeData(1:j,1);
        Cnode_y = CNodeData(1:j,2);
    else
        Cnode_x = [nan nan];
        Cnode_y = [nan nan];
    end
    
    ObstacleData = load([dir 'obstacles_' num2str(file_ctr) '.txt']);
    if ~isempty(ObstacleData)
        obs_x = ObstacleData(:,1);
        obs_y = ObstacleData(:,2);
    else
        obs_x = [];
        obs_y = [];
    end
    
    MoveData = load([dir 'robotMovePath_' num2str(file_ctr) '.txt']);
    move_x = MoveData(:,1);
    move_y = MoveData(:,2);
    move_theta = MoveData(:,4);
    
    
    PathData = load([dir 'path_' num2str(file_ctr) '.txt']);
    path_x = PathData(:,1);
    path_y = PathData(:,2);
    
    
    if exist([dir 'obsNodes.txt'], 'file') 
      OBSNodesData = load([dir 'obsNodes.txt']);
      OBSNodes_x = OBSNodesData(:,1);
      OBSNodes_y = OBSNodesData(:,2);
    else
      OBSNodes_x = [];
      OBSNodes_y = [];
    end
    
    
   if exist([dir 'obsNodesNeighbors.txt'], 'file') 
      OBSNodesNData = load([dir 'obsNodesNeighbors.txt']);
      OBSNodesN_x = OBSNodesNData(:,1);
      OBSNodesN_y = OBSNodesNData(:,2);
    else
      OBSNodesN_x = [];
      OBSNodesN_y = [];
    end
    
%         figure(3)
%         clf
%         plot(node_x, node_y, '.r')
%         hold on
%         plot(Cnode_x, Cnode_y, 'xk')
%         plot(x, y)
%         plot(obs_x,obs_y, 'g', 'LineWidth',2)
%         plot(path_x,path_y, 'c', 'LineWidth',2)
%         plot(move_x,move_y, 'k', 'LineWidth',2)
%         hold off
%         axis([-50 50 -50 50])
    
    
    
    % make a contour plot, need to grid up data into Z, an m x n matrix
    % we'll set the cost value of Z(i,j) to be the average value of all
    % nodes that exist within the transformed grid [i i+1] X [j j+1]
    % note that we need to define these well with respect to obstacles
    
    Xs = minXval:contourGranularity:(maxXval-1);
    Ys = minYval:contourGranularity:(maxYval-1);
    
    
    Z = zeros(length(Ys), length(Xs));
    Zmin = inf(length(Ys), length(Xs));
    Counts = zeros(length(Ys), length(Xs)); % remember the number of points in each grid
    
    for v = 1:length(node_z)
        j = max(min(floor((node_x(v) - minXval)/contourGranularity)+1, size(Z,2)),1);
        i = max(min(floor((node_y(v) - minYval)/contourGranularity)+1, size(Z,1)),1);
        
        if isinf(node_z(v))
            % nodes that are furhter than path-legnth from the goal
            % never have thier initial inf value removed (since
            % the wavefeont has not expanded to them yet)
          continue
        end
        
        Z(i,j) = Z(i,j) + node_z(v);
        Counts(i,j) = Counts(i,j) + 1;
        
        Zmin(i,j) = min(Zmin(i,j), node_z(v));
    end
    % now take the average
    Z(Z ~= 0) = Z(Z ~= 0)./Counts(Z ~= 0);
    
    % now, if there are cells do not have any values, we need to put
    % something in them, we'll average over non-zero neighbors
    % but do nothing if path to goal does not exist
    jjj = 1;
    while sum(Z(:)==0) > 0
     
        jjj = jjj + 1;
        
        if sum(Z(:)~=0) < 5 || jjj > 3 % max(size(Z))
            % whole thing is unpopulated
            Z(Z(:)==0) = countorLevels(end);
            Zmin(Z(:)==0) = countorLevels(end);
            break
        end
        
        [yZeroInds, xZeroInds] = find(Z == 0);
        
        dZ = zeros(size(Z));
        dZmin = zeros(size(Zmin));
        for k = 1:length(xZeroInds)
            xZind = xZeroInds(k);
            yZind = yZeroInds(k);
            
            % find the "3 x 3" sub matrix around (yZind, xZind) in Z
            % note that it can be smaller if (yZind, xZind) is on the border
            minxZind = max(xZind - 1, 1);
            maxxZind = min(xZind + 1, size(Z, 2));
            minyZind = max(yZind - 1, 1);
            maxyZind = min(yZind + 1, size(Z, 1));
            
            if (videoFill == true) && (length(Ys)/2-2 < yZind) && (yZind < length(Ys)/2+2)  
                % use 2 X 3 (equal to and below) so that don't get cost
                % through wall obstacle due to contour interpolation
                
                minyZind = yZind;
            end
            
            subZ = Z(minyZind:maxyZind, minxZind:maxxZind);
            if  sum(subZ(:) ~= 0) > 1
                dZ(yZind, xZind) = sum(subZ(:))/sum(subZ(:) ~= 0);
                dZmin(yZind, xZind) = min(subZ(subZ(:) ~= 0));
            end
        end
        Z = Z+dZ;
        Zmin(isinf(Zmin) & dZmin ~= 0) = dZmin(isinf(Zmin) & dZmin ~= 0);
    end
     
    % transform nodes so we can plot them on the contour plot
    c_node_x = (node_x-minXval)/contourGranularity+.5;
    c_node_y = (node_y-minYval)/contourGranularity+.5;
    
    % transform path so we can plot it on the contour plot
    c_path_x = (path_x-minXval)/contourGranularity+.5;
    c_path_y = (path_y-minYval)/contourGranularity+.5;
    
    % transform move path so we can plot it on the contour plot
    c_move_x = (move_x-minXval)/contourGranularity+.5;
    c_move_y = (move_y-minYval)/contourGranularity+.5;    
    c_move_theta = move_theta - pi/2;
    
    % transform edges
    c_x = (x-minXval)/contourGranularity+.5;
    c_y = (y-minYval)/contourGranularity+.5;
    
    % transform obstacles
    c_obs_x = (obs_x-minXval)/contourGranularity+.5;
    c_obs_y = (obs_y-minYval)/contourGranularity+.5;
    
    % calculate ticks
    theXticks = -50:tickInterval:maxXval;
    theYticks = -50:tickInterval:maxXval;
    c_theXticks = (theXticks-minXval)/contourGranularity+.5;
    c_theYticks = (theYticks-minYval)/contourGranularity+.5;
   
    c_OBSNodes_x = (OBSNodes_x-minXval)/contourGranularity+.5;
    c_OBSNodes_y = (OBSNodes_y-minXval)/contourGranularity+.5;
    
    c_OBSNodesN_x = (OBSNodesN_x-minXval)/contourGranularity+.5;
    c_OBSNodesN_y = (OBSNodesN_y-minXval)/contourGranularity+.5;
    
    % make path start at robot pose and not move goal 
    %c_path_x(1) = c_move_x(end);
    %c_path_y(1) = c_move_y(end);
    
     
    %     figure(4)
    %     clf
    %     contourf(Z,countorLevels)
    %     hold on
    %     plot(c_path_x, c_path_y, 'k', 'LineWidth',3)
    %     plot(c_path_x, c_path_y, 'w', 'LineWidth',1)
    %     hold off
    %
    %     axis([1, size(Z,1), 1, size(Z,2)-1])
    %     set(gca,'XTick',c_theXticks)
    %     set(gca,'XTickLabel', theXticks)
    %     set(gca,'YTick',c_theYticks)
    %     set(gca,'YTickLabel', theYticks)
    
   
    % extract polygon obstacle inds
    if ~isempty(c_obs_x)
        naninds = find(isnan(c_obs_x));
        polyStartInds = [1; (naninds(1:end-1))+1];
        polyEndEnds = naninds - 1;
    else
        polyStartInds = [];
        polyEndEnds = [];
    end
    
    
    % make costs above robot cost color grey
    robot_Zind_x = floor(c_move_x(end))+1;
    robot_Zind_y = floor(c_move_y(end))+1;
    
    % but keep cells near robot original values
    robot_minxZind = max(robot_Zind_x - 1, 1);
    robot_maxxZind = min(robot_Zind_x + 1, size(Z, 2));
    robot_minyZind = max(robot_Zind_y - 1, 1);
    robot_maxyZind = min(robot_Zind_y + 1, size(Z, 1)); 
    robotSamplePatch = Zmin(robot_minyZind:robot_maxyZind, robot_minxZind:robot_maxxZind);

    robotSampleVal = mean(robotSamplePatch(~isinf(robotSamplePatch)));
    %robotSampleVal = Zmin(robot_Zind_y, robot_Zind_x);
    
    plotContourValIndRobotVal = find(countorLevels >= robotSampleVal, 1,'first')+1; 
    if isempty(plotContourValIndRobotVal) || plotContourValIndRobotVal > length(countorLevels)
      plotContourValIndRobotVal = length(countorLevels);
    end
    plotContourValIndAboveRobotVal = min(plotContourValIndRobotVal + 1, length(countorLevels));
    %dividingCost = (countorLevels(plotContourValIndRobotVal) + countorLevels(plotContourValIndAboveRobotVal))/2;
    dividingCost = countorLevels(plotContourValIndRobotVal);
    
    Zmin(Zmin > dividingCost) = Inf;
    Zmin(robot_minyZind:robot_maxyZind, robot_minxZind:robot_maxxZind) = robotSamplePatch;
    
    tempcolormap = mycolormap;
    tempcolormap(plotContourValIndAboveRobotVal:end,:) = 0.3;
    
    % this keeps the colormap constant vs time
    Zmin(1,length(Xs)+1) = countorLevels(end);
   
    
%     figure(3)
%     imagesc(Zmin)
%     axis xy

    
    fig = figure(5);
    
    set(fig,'OuterPosition', [100, 100, 576*1.5, 512*1.5]);
    
    clf
    colormap(tempcolormap)
    contourf(Zmin,countorLevels, 'EdgeColor', 'none')
    hold on
    plot(c_x, c_y, 'Color',[0.5,0.5,0.5],'LineWidth',1)
    plot(c_node_x, c_node_y, '.', 'Color',[0.5,0.5,0.5],'MarkerSize',.5)
    plot(c_move_x, c_move_y, 'k', 'LineWidth',3)
    plot(c_move_x, c_move_y, 'r', 'LineWidth',1)
    plot(c_path_x, c_path_y, 'k', 'LineWidth',3)
    plot(c_path_x, c_path_y, 'w', 'LineWidth',1)
    %contour(Zmin,countorLevels(1:(maxPlotcontourValindPlusOne-1)), 'k')
    for p = 1:length(polyStartInds)
       poly_inds = polyStartInds(p):polyEndEnds(p);
       patch(c_obs_x(poly_inds), c_obs_y(poly_inds), 'k') 
    end
    plot(c_obs_x,c_obs_y, 'w', 'LineWidth',1)
    if start_move_at_ctr > file_ctr
      plot(c_x(2), c_y(2), 'sw', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    else
      plot(c_path_x(end), c_path_y(end), 'sw', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    end
    plot(c_move_x(end), c_move_y(end), 'o', 'LineWidth',1, 'MarkerEdgeColor','w','MarkerFaceColor','w','MarkerSize',15)
    plot(raw_x(2), raw_y(2), 'sw', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    plot(c_OBSNodes_x, c_OBSNodes_y, '.k')
    plot(c_OBSNodesN_x, c_OBSNodesN_y, 'ok')
    plotVehicleTheta(fig, [c_move_x(end) c_move_y(end)], c_move_theta(end), .5, 'k', sensor_radius, '--w')
    
    hold off
    axis([1, size(Z,1), 1, size(Z,2)-1])
    set(gca,'XTick',c_theXticks)
    set(gca,'XTickLabel', theXticks)
    set(gca,'YTick',c_theYticks)
    set(gca,'YTickLabel', theYticks)
    colorbar
    title('RRT^X')
    
    %axis tight
    %set(gca,'nextplot','replacechildren');
    %set(gcf,'Renderer','zbuffer');
    
    F = getframe(fig);
    writeVideo(writerObj,F);
    
    file_ctr = file_ctr + 1; 
    %if file_ctr >= 20
    %    pause()
    %end
end
% close video file
close(writerObj);
