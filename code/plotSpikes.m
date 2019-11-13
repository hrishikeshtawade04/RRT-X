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


% plots spikes at pose location with radius and offset by theta, there are
% num spikes around the object, d_theta is the change to theta between
% frames (only used here to determine direction of spikes)

function plotSpikes(pose, radius, theta, d_theta, num, clr)

    % local normalized radial coordinates of a single spike
    
    th = [0 .1 .2 .3 .4 .5 .6 .7 .8 .9 1];
    r = [.5 .6 .7 .8 .9 1 .9 .8 .7 .6 .5];
    
    
    max_spike = .9;
    spike_step = max_spike*2/length(th);
    spikes_forward = 0:spike_step:max_spike*2;
    
    th_r_offset = zeros(size(th));
    th_r_offset(1:ceil(length(th)/2)) = spikes_forward(1:ceil(length(th)/2));
    
    th_r_offset = max([th_r_offset ; fliplr(th_r_offset)]);
    
    if d_theta > 0
        th = th + th_r_offset;
    else
        th = th - th_r_offset;
    end
    
    % change this to local radial coordinates of all spikes
    th = (repmat(th, [num,1]) + repmat((0:(num-1))',[1, size(th,2)]))';
    th = (2*pi/num)*th(:) + theta;
    r = radius*repmat(r, [1,num]);

    % change to global cartesian coordinates
    x = r'.*cos(th) + pose(1);
    y = r'.*sin(th) + pose(2);
    
    fill(x,y , clr, 'EdgeColor', 'none')
end
