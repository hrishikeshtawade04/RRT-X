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
% it is assumed that positon saved in files includes [x, y, time, etc.]
% i.e., the first three coordinates are x, y, and time.

clear all
close all

%dbstop if error

dir = 'temp/';

file_ctr = 2;
max_file_ctr = 651;
remove_frame = 401;
move_starts_at_file_ctr = 401;
stop_using_theta_at_ctr = 4000;
costDim = 6; % this is the dimesnion of the nodes files that has cost
obsShrinkProp = .8; % obstacles are plotted this big (relatively)
carrot_dist = 100; % movment estimate for obstacles that are moving dynamically is displayed
                   % this far ahead of obstacle
c_scale = [0 8]



minXval = -50;
minYval = -50;
maxXval = 50;
maxYval = 50;
maxTime = 35;
minTime = -15;

tickInterval = 10; % for plitting ticks


maxObs = 11;
obs_used = zeros(1, maxObs); % uses so each obstacle keeps thier randomly
% generated paramiters
obs_type = [1 1 1 1 2 2 2 2 2 2 2]; % 1 = spike, 2 = pacman

obs_clrs = {[.1 .1 .1], [.15 .15 .15], [.2 .2 .2], [.25 .25 .25], [.3 .3 .3], [.35 .35 .35], [.4 .4 .4], [.45 .45 .45], [.5 .5 .5], [.55 .55 .55], [.6 .6 .6]};


max_time = 0;

% open the video file
writerObj = VideoWriter( [dir 'TimeMovie.avi']);
open(writerObj);
while exist([dir 'robotMovePath_' num2str(file_ctr) '.txt'], 'file') && file_ctr < max_file_ctr
    display(file_ctr)
    
    %if file_ctr == 218
    %   keyboard
    %end
    
    x_start = 0;
    y_start = -5;
    
    EdgeData = load([dir 'edges_' num2str(file_ctr) '.txt']);
    
    
    i = size(EdgeData,1);
    raw_x = EdgeData(1:i,1);
    raw_y = EdgeData(1:i,2);
    raw_z = EdgeData(1:i,3);
    
    x = nan(i*1.5, 1);
    y = nan(i*1.5, 1);
    z = nan(i*1.5, 1);
    
    x(1:3:end-2) = raw_x(1:2:end-1);
    x(2:3:end-1) = raw_x(2:2:end);
    
    y(1:3:end-2) = raw_y(1:2:end-1);
    y(2:3:end-1) = raw_y(2:2:end);
    
    z(1:3:end-2) = raw_z(1:2:end-1);
    z(2:3:end-1) = raw_z(2:2:end);
    
    
    NodeData = load([dir 'nodes_' num2str(file_ctr) '.txt']);
    
    j = size(NodeData,1);
    node_x = NodeData(1:j,1);
    node_y = NodeData(1:j,2);
    node_z = NodeData(1:j,3);
    
    if exist([dir 'Cnodes_' num2str(file_ctr) '.txt'], 'file')
        CNodeData = load([dir 'Cnodes_' num2str(file_ctr) '.txt']);
    else
        CNodeData = [];
    end
    
    j = size(CNodeData,1);
    if j > 0
        Cnode_x = CNodeData(1:j,1);
        Cnode_y = CNodeData(1:j,2);
        Cnode_z = CNodeData(1:j,3);
    else
        Cnode_x = [nan nan];
        Cnode_y = [nan nan];
        Cnode_z = [nan nan];
    end
    
    if exist([dir 'Qnodes_' num2str(file_ctr) '.txt'], 'file')
        QNodeData = load([dir 'Qnodes_' num2str(file_ctr) '.txt']);
    else
        QNodeData = [];
    end
    
    j = size(QNodeData,1);
    if j > 0
        Qnode_x = QNodeData(1:j,1);
        Qnode_y = QNodeData(1:j,2);
        Qnode_z = QNodeData(1:j,3);
    else
        Qnode_x = [nan nan];
        Qnode_y = [nan nan];
        Qnode_z = [nan nan];
    end
    
    MoveData = load([dir 'robotMovePath_' num2str(file_ctr) '.txt']);
    if ~isempty(MoveData)
        move_x = MoveData(:,1);
        move_y = MoveData(:,2);
        move_time = MoveData(:,3);
        move_theta = 0; %MoveData(:,4) - pi/2;
        
        if stop_using_theta_at_ctr < file_ctr % calcul;ate from path segments instead
            mi = length(move_x);
            move_theta = atan2( move_y(mi) - move_y(mi-1), move_x(mi) - move_x(mi-1) );
        end
    else
        move_x = nan;
        move_y = nan;
        move_time = nan;
    end
    
    PathData = load([dir 'path_' num2str(file_ctr) '.txt']);
    path_x = PathData(:,1);
    path_y = PathData(:,2);
    path_time = PathData(:,3);
    
    path_x = [move_x(end); path_x];
    path_y = [move_y(end); path_y];
    path_time = [move_time(end); path_time];
    
    % remove x and y that represent no movement at end of path
    
    ind = find(path_x == path_x(end) & path_y == path_y(end), 1, 'first');
    path_x = path_x(1:ind);
    path_y = path_y(1:ind);
    path_time = path_time(1:ind);
    
    robotCostToGoal = PathData(1,3);
    
    %     someInds = find(z > move_time(end));
    %     x(someInds) = NaN;
    %     y(someInds) = NaN;
    %     z(someInds) = NaN;
    
    
    
    ObstacleData = load([dir 'obstacles_' num2str(file_ctr) '.txt']);
    if ~isempty(ObstacleData)
        obs_x = ObstacleData(:,1);
        obs_y = ObstacleData(:,2);
        obs_time = ObstacleData(:,3);
        obs_rads = ObstacleData(:,4) * obsShrinkProp;
        
        % now make a different obstacle circle for each obstacle (at its current location)
        
        nan_inds = find(isnan(ObstacleData(:,1)));
        start_inds = [1; nan_inds(1:end-1)+1];
        end_inds = nan_inds-1;
        
        obs_x_est = [];
        obs_y_est = [];
        obs_times_est = [];
        
        for i = 1:length(end_inds)
            si = start_inds(i);
            ei = end_inds(i);
            
            this_obs_times = obs_time(si:ei);
            this_obs_x = obs_x(si:ei);
            this_obs_y = obs_y(si:ei);
            obstacle_radius = obs_rads(si);
           
            
            before_now_ind = find(this_obs_times <= path_time(1), 1, 'last');
            if isnan(before_now_ind)
                before_now_ind = 1;
            end
            
            [after_now_ind] = find(this_obs_times >= path_time(1), 1, 'first');
            if isnan(after_now_ind)
                after_now_ind = length(this_obs_times);
            end
            
            edge_fraction = (path_time(1) - this_obs_times(before_now_ind))/(this_obs_times(after_now_ind) - this_obs_times(before_now_ind));
            
            if isnan(edge_fraction)
                edge_fraction = 0;
            end
            
            obs_centers_x{i} = this_obs_x(before_now_ind) + edge_fraction*(this_obs_x(after_now_ind) - this_obs_x(before_now_ind));
            obs_centers_y{i} = this_obs_y(before_now_ind) + edge_fraction*(this_obs_y(after_now_ind) - this_obs_y(before_now_ind));
            obs_centers_time{i} = this_obs_times(before_now_ind) + edge_fraction*(this_obs_times(after_now_ind) - this_obs_times(before_now_ind));
            obs_rad{i} = obstacle_radius;
            
            if isempty(before_now_ind)
            
                
                %obs_tradj{i} = 0;
                obs_speed{i} = 0;
                
                obs_centers_x{i} = this_obs_x(end);
                obs_centers_y{i} = this_obs_y(end);
                obs_centers_time{i} = path_time(1);
                
                % these are the carrot (carrot on a stick) used to show estimated movement
                obs_centers_next_x{i} = obs_centers_x{i};
                obs_centers_next_y{i} = obs_centers_y{i};
                
                
                dist_to_carrot{i} = 0;
                obs_centers_next_time{i} = obs_centers_time{i} - dist_to_carrot{i}/obs_speed{i};
            
                
            elseif before_now_ind == after_now_ind
                if after_now_ind == 1
                    obs_tradj{i} = 0;
                    obs_speed{i} = 0;

                else
                    obs_tradj{i} = atan2(this_obs_y(after_now_ind) - this_obs_y(after_now_ind-1),this_obs_x(after_now_ind) - this_obs_x(after_now_ind-1)) + pi;
                    obs_speed{i} = -sqrt((this_obs_x(before_now_ind) - this_obs_x(after_now_ind-1))^2 + (this_obs_y(after_now_ind-1) - this_obs_y(after_now_ind))^2)/(this_obs_times(after_now_ind-1) - this_obs_times(after_now_ind));
                end
                
                % these are the carrot (carrot on a stick) used to show estimated movement
                obs_centers_next_x{i} = obs_centers_x{i} + carrot_dist*cos(obs_tradj{i});
                obs_centers_next_y{i} = obs_centers_y{i} + carrot_dist*sin(obs_tradj{i});
                
                
                dist_to_carrot{i} = sqrt((obs_centers_x{i}-obs_centers_next_x{i})^2 + (obs_centers_y{i}-obs_centers_next_y{i})^2);
                obs_centers_next_time{i} = obs_centers_time{i} - dist_to_carrot{i}/obs_speed{i};
            
            else
                
                if length(after_now_ind) < 1
                    after_now_ind = before_now_ind-1;
                end
                
                obs_tradj{i} = atan2(this_obs_y(after_now_ind) - this_obs_y(before_now_ind),this_obs_x(after_now_ind) - this_obs_x(before_now_ind)) + pi;
                obs_speed{i} = -sqrt((this_obs_x(before_now_ind) - this_obs_x(after_now_ind))^2 + (this_obs_y(before_now_ind) - this_obs_y(after_now_ind))^2)/(this_obs_times(before_now_ind) - this_obs_times(after_now_ind));
                % these are the carrot (carrot on a stick) used to show estimated movement
                obs_centers_next_x{i} = obs_centers_x{i} + carrot_dist*cos(obs_tradj{i});
                obs_centers_next_y{i} = obs_centers_y{i} + carrot_dist*sin(obs_tradj{i});
                
                
                dist_to_carrot{i} = sqrt((obs_centers_x{i}-obs_centers_next_x{i})^2 + (obs_centers_y{i}-obs_centers_next_y{i})^2);
                obs_centers_next_time{i} = obs_centers_time{i} - dist_to_carrot{i}/obs_speed{i};
                   
            end
            
         
            obs_x_est = [obs_x_est ; [obs_centers_x{i}; obs_centers_next_x{i}; NaN]];
            obs_y_est = [obs_y_est ; [obs_centers_y{i}; obs_centers_next_y{i}; NaN]];
            obs_times_est = [obs_times_est ; [obs_centers_time{i}; obs_centers_next_time{i}; NaN]];
            
            if(isempty(obs_tradj{i}))
                obs_tradj{i} = 0;
            end
            
            if obs_used(i) == 0
                obs_theta{i} = rand()*pi;
                obs_d_theta{i} =  .35*pi/10 * 3*sqrt(obs_rad{i})/10;
                if rand() > 0.5
                    obs_d_theta{i} = -obs_d_theta{i};
                end
                obs_spikes{i} = 5 + floor(rand()*5);
                
                obs_mouth{i} = pi/6;
                d_obs_mouth{i} = -(pi/3)/6;
                
                obs_used(i) = 1;
            end
            
            if isempty(obs_centers_x{i}) % obstacle has finished moving, assume that it stays at the same place
                obs_centers_x{i} = this_obs_x(1);
                obs_centers_y{i} = this_obs_y(1);
            end
            
            %num_slices = 50;      % number of segments for the draw circle outlining obstacle
            %st = 2*pi/num_slices; % step size to get that many slices
            %r = [0:st:2*pi 0];
            %unit_circle_points_X = cos(r);
            %unit_circle_points_Y = sin(r);
            
            %obs_outline_points_x{i} = obs_centers_x{i} + obstacle_radius*unit_circle_points_X';
            %obs_outline_points_y{i} = obs_centers_y{i} + obstacle_radius*unit_circle_points_Y';
            
            
            
        end
        
    else
        obs_x = [];
        obs_y = [];
        obs_time = [];
        obs_rads = [];
        obs_centers_x = {};
        obs_centers_y = {};
    end
    
    
    
    
    
    %     figure(3)
    %     clf
    %     plot3(x, y, z)
    %     hold on
    %     plot3(Cnode_x, Cnode_y, Cnode_z, 'xr')
    %     plot3(Qnode_x, Qnode_y, Qnode_z, 'or')
    %     %plot3(node_x, node_y, node_z, '.r')
    %
    %     plot3(obs_x, obs_y, obs_time,  'g', 'LineWidth',2)
    %     plot3(path_x,path_y, path_time, 'r', 'LineWidth',2)
    % %         plot(move_x,move_y, 'k', 'LineWidth',2)
    %     hold off
    %     axis([minXval maxXval minYval maxYval minTime maxTime])
    %     xlabel('x')
    %     ylabel('y')
    %     zlabel('time')
    
    %
    %     figure(4)
    %     clf
    %     plot3(path_x, path_y, path_time, 'c', 'LineWidth',2)
    %     hold on
    %     plot3(move_x, move_y, move_time, 'k', 'LineWidth',2)
    %     plot3(move_x(end), move_y(end), move_time(end), 'sw', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    %     plot3(path_x(end), path_y(end), path_time(end), 'ow', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    %     axis([minXval maxXval minYval maxYval 0.0 maxTime])
    %     xlabel('x')
    %     ylabel('y')
    %     zlabel('time')
    
    
    % note need to make line width better by modifying the +1 to path_x and
    % path_y to be apporipate vs dpath_x and dpath_y
    
    % 2D plot of current time
    fig = figure(5);
    set(fig,'OuterPosition', [100, 100, 576*1.5, 512*1.5]);
    
    clf
    plot(move_x, move_y, ':k', 'LineWidth',3)
    hold on
    plot(move_x, move_y, 'k', 'LineWidth',1)
    %plot(move_x(end), move_y(end), 'o', 'LineWidth',1, 'MarkerEdgeColor','w','MarkerFaceColor','w','MarkerSize',15)
    plot(path_x(end), path_y(end), 's', 'LineWidth',1, 'MarkerEdgeColor','k','MarkerFaceColor','w','MarkerSize',8)
    
    time_adjust = path_time(end);
    path_time_prime = path_time - time_adjust;
    obs_time_prime = obs_time - time_adjust;
    obs_times_prime_est = obs_times_est - time_adjust;
    if path_time_prime(1) > max_time
        max_time = path_time_prime(1);
    end
    
    colorPlot(obs_x_est', obs_y_est', obs_times_prime_est', 1)
    
    for i = 1:length(obs_centers_x)
        %plot(obs_centers_x{i}, obs_centers_y{i}, 'o', 'MarkerEdgeColor','k','MarkerFaceColor','k')
        
        if obs_type(i) == 1
            plotSpikes([obs_centers_x{i} obs_centers_y{i}], obs_rad{i}, obs_theta{i}, obs_d_theta{i}, obs_spikes{i}, obs_clrs{i})
            if file_ctr > move_starts_at_file_ctr
                obs_theta{i} = obs_theta{i} + obs_d_theta{i};
            end
        elseif obs_type(i) == 2
            plotPackman([obs_centers_x{i} obs_centers_y{i}], obs_rad{i}, obs_tradj{i}, obs_mouth{i}, obs_clrs{i})
            if file_ctr > move_starts_at_file_ctr
                obs_mouth{i} = obs_mouth{i} + d_obs_mouth{i};
                
                if obs_mouth{i} >= pi/3 - .01
                    obs_mouth{i} = pi/3;
                    d_obs_mouth{i} = -d_obs_mouth{i};
                elseif obs_mouth{i} <= .01
                    obs_mouth{i} = 0;
                    d_obs_mouth{i} = -d_obs_mouth{i};
                end
                
            end
        end
        
        %plot(obs_outline_points_x{i}, obs_outline_points_y{i}, 'k', 'LineWidth',2)
    end
    
    colorPlot(path_x', path_y', path_time_prime', 1.5)
    
    
    
    %plotVehicleTheta(fig, [move_x(end) move_y(end)], move_theta(end), 2, 'k', NaN, '--w')
    if length(path_x) < 3
        plotVehicle(fig, [path_x(1) path_y(1)], [path_x(1) path_y(1)], 2, 'k', NaN, 'none')
        
    else
        plotVehicle(fig, [path_x(2) path_y(2)], [path_x(3) path_y(3)], 2, 'k', NaN, 'none')
    end
    
    axis([minXval maxXval minYval maxYval ])
    axis square
    set(gca,'XTick',minXval:tickInterval:maxXval)
    set(gca,'YTick',minYval:tickInterval:maxYval)
    colorbar
    %caxis([0, max_time])
    caxis(c_scale)
    xlabel('x')
    ylabel('y')
    zlabel('time')
    title('robot and obstacle pose (x,y) vs. robot time-to-goal (color)')
    
    % write to video file
    F = getframe(fig);
    writeVideo(writerObj,F);
    
    
    file_ctr = file_ctr + 1
    
    if remove_frame == file_ctr
        file_ctr = file_ctr + 1
    end
    
    %pause()
end

% close video file
close(writerObj);

