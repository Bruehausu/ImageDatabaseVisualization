% for use with SingleImageSR_TIP14_Box
% http://www.cs.technion.ac.il/~elad/software/

root = '/out';
mill_range = 1; % somewhhere in 1 - 78
mill_fld = '/00';
thou_fld = '/00000';

start = 5001
range = 1000000;
%range = 79302017;

for ii = start:range
    i = ii - 1;
   
    if (mod(i, 1000000) == 0)
        mill_fld = strcat('/',sprintf('%02d',i/1000000));
        mkdir(root, mill_fld);
    end
        
    if (mod(i, 1000) == 0)
        thou_fld = strcat('/',sprintf('%05d',i/1000));
        mkdir(strcat(root,mill_fld), thou_fld);
        
        %disp(strcat('at ', i))
    end
        
    
    imgname = sprintf('/%09d',i);
    path = strcat(root, mill_fld, thou_fld, imgname, '.png')
    
    img = loadTinyImages(ii:ii);
    
    imwrite(img, path);
end
    
    
    
    