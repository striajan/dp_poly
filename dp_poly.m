function [ind, pts] = dp_poly(pts, nVert)

ind = dp_poly_mex(pts, nVert);

ind = double(ind) + 1;
pts = pts(:,ind);

end
