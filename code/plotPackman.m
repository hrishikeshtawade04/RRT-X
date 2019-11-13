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


% plots pacman at pose location with radius and offset by theta, with 
% mouth open at phi degrees

function plotPackman(pose, radius, theta, phi, clr)

    % local normalized radial coordinates of a single spike
    
    num_segs = 40;
    step = 2*pi/num_segs;
    th = 0:step:2*pi;
    
    x = radius*cos(th);
    y = radius*sin(th);
    
    x(th < phi | th > 2*pi-phi ) = -.2*radius;
    y(th < phi | th > 2*pi-phi ) = 0;
    
    
    
    xy = [x;y];
    
    R = [cos(theta) -sin(theta); sin(theta) cos(theta)];
    
    xy_hat = R*xy;
    

    fill(xy_hat(1,:) + pose(1), xy_hat(2,:) + pose(2) , clr, 'EdgeColor', 'none')
end
