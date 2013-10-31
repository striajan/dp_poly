function [ind, pts] = dp_open(pts, nVert)

ind = dp_open_mex(pts, nVert);

ind = double(ind) + 1;
pts = pts(:,ind);

end
