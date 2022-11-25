clear all; close all; clc;

n = 256;
mat = [white(n); jet(n); viridis(n); ocean(n); autumn(n); winter(n); pink(n)];

%c_vec = round(jet_mat(:,1) * 255 + jet_mat(:,2) * 255 * 2^8 + jet_mat(:,3) * 255 * 2^16);
c_vec = round(mat(:,1) * 255) + round(mat(:,2) * 255) * 2^8 + round(mat(:,3) * 255) * 2^16;

fd = fopen('colormaps.cmap', 'wt+');
for ii = 1:length(c_vec)
  
  fprintf(fd, "%i\n", c_vec(ii));
 
end
fclose(fd);