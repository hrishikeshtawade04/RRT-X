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



% plots line x vs y where the line changes color according
% to c from start to end, plots it thickness th
function colorPlot(x, y, c, th)
    if length(c) <= 1
       return 
    end

    % make edges
    xx = [x;x];
    xx = xx(2:end-1);
    yy = [y;y];
    yy = yy(2:end-1);
    
    % calculate change of original edges
    dx = x(2:end) - x(1:end-1);
    dy = y(2:end) - y(1:end-1);
    
    % calculate lengths of original edges
    len = sqrt(dx.^2+dy.^2);
    
    % calculate necessary changes to x and y necessary to
    % move each edge perpindiculary by th/2
    
    py = (dx./len)*(th/2);
    py = [py; py];
    py = py(:)';
    
    px = (dy./len)*(th/2);
    px = [px; px];
    px = px(:)';
    
    % we want to calculate two new lines, that represent
    % each side of the thicknes, need to expand each edge
    % perpindicular to its direction of travel
    x_in = xx+px;
    x_out = xx-px;
    
    y_in = yy-py;
    y_out = yy+py;
    
    X = [x_in;x_out];
    Y = [y_in;y_out];
    Z = zeros(size(X));
    cc = [c;c];
    C = [cc(2:end-1);cc(2:end-1)];
    
    
    surface(X,Y,Z,C,'faceColor','interp','edgeColor','none');

end
