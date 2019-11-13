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


% plots an aircraft at a at angle theta that is c big
% also plots a sensor range circle of radius sr
% set sr to NaN to ignor
function plotVehicle(f, a, theta, c, clr, sr, clrB)

%     % slender aircraft
%     x = [0 .1 .1  1  1   .1  .05  .3 .3];
%     y = [1 .8 .3 .2 -.1 -.1 -.8 -.83 -.95];
    
    % fat aircraft
    x = [0 .2 .2  1  1   .2  .2  .5 .5];
    y = [1 .8 .4 .4 -.1 -.1 -.7 -.7 -1];
    
    x = c*[x -fliplr(x)];
    y = c*[y fliplr(y)];
    
    xy = [x;y];
    
    R = [cos(theta) -sin(theta); sin(theta) cos(theta)];
    
    
    
    xy_hat = R*xy;
    
    %figure(f)
    %plot(xy_hat(1,:) + a(1), xy_hat(2,:) + a(2) , clr)
    fill(xy_hat(1,:) + a(1),xy_hat(2,:) + a(2) , clr, 'EraseMode', 'none', 'EdgeColor', 'none')
    %fill3(xy_hat(1,:) + a(1),xy_hat(2,:) + a(2), ones(size(xy_hat(1,:))) , clr, 'EdgeColor', 'none')

    
    if ~isnan(sr)
        steps = 20;
        phis = 0:2*pi/steps:2*pi;
    
        xs = sr*cos(phis);
        ys = sr*sin(phis);
    
        plot(xs + a(1), ys + a(2) , 'k')  
        plot(xs + a(1), ys + a(2) , clrB)
    end
end

