clear all; close all; clc;

jet_mat = jet;
c_vec = round(jet_mat(:,1) * 255 + jet_mat(:,2) * 255 * 2^8 + jet_mat(:,3) * 255 * 2^16);

fd = fopen('jet.cmap', 'wt+');
for ii = 1:length(c_vec)
  
  fprintf(fd, "%i\n", c_vec(ii));
  
end
fclose(fd);