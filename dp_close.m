function [ind, pts] = dp_close(pts, nVert)

ind = dp_close_mex(pts, nVert);

ind = double(ind) + 1;
pts = pts(:,ind);

end
