
RGB = imread("../images/kmeans.bmp")

L = zeros([size(RGB,1) size(RGB,2)]);
colors = squeeze(RGB(1,1,:))';
for r = 1:size(L,1);
    for c = 1:size(L,2);
        
        color =  squeeze(RGB(r,c,:))';
        
        matches = ismember(colors, color);
        matches = matches(:,1) .* matches(:,2) .* matches(:,3);
        l = find(matches, 1);
        if l
            L(r,c) = l;
        else
            colors = [colors ; color]; %#ok<AGROW>
            L(r,c) = size(colors,1);
        end
    end
end