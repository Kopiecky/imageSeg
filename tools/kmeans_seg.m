function kmeans_seg(filename)
    image = imread(filename);
    subplot(121)
    imshow(image)
    
    [l, centers] = imsegkmeans(image, 50);
    B = labeloverlay(image, l);
    subplot(122)
    imshow(B)
end