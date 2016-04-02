% for use with Single_Image_SR 
% http://www.cs.technion.ac.il/~elad/software/

clear all;
clc;

cd(fileparts(mfilename('fullpath')))


addpath('Solver');
addpath('Sparse coding');

tr_dir = 'Data/training';

patch_size = 3; % patch size for the low resolution input image
overlap = 1; % overlap between adjacent patches
lambda = 0.1; % sparsity parameter
zooming = 3; % zooming factor, if you change this, the dictionary needs to be retrained.
num_patch = 50000; % number of patches to sample as the dictionary
codebook_size = 1024; % size of the dictionary

regres = 'L1'; % 'L1' or 'L2', use the sparse representation directly, or use the supports for L2 regression


load('Data/Dictionary/Dictionary.mat');

files = dir('in');
for file = files'
    if ~file.isdir
        disp(file.name);
        img = imread(strcat('in/',file.name), 'PNG');
        img2 = rgb2ycbcr(img);
        
        lImy = double(img2(:,:,1));
        
        interpimg = imresize(img,zooming,'bicubic');
        interpimg2 = rgb2ycbcr(interpimg);
        hImcb = interpimg2(:,:,2);
        hImcr = interpimg2(:,:,3);

        disp('Start superresolution...');

        [hImy] = L1SR(lImy, zooming, patch_size, overlap, Dh, Dl, lambda, regres);
        
        ReconIm(:,:,1) = uint8(hImy);
        ReconIm(:,:,2) = hImcb;
        ReconIm(:,:,3) = hImcr;
        
        ReconIm = ycbcr2rgb(ReconIm);
        
        imwrite(uint8(ReconIm),strcat('out/',file.name), 'PNG');
        % Do some stuff
    end
    
end