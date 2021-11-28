RGB = imread("../images/kmeans.bmp");

L = zeros([size(RGB,1) size(RGB,2)]);

squeeze(RGB(1, 1, :))'

colors = squeeze(RGB(1,1,:))'; % 1x3

for r = 1:size(L - 5,1);
    for c = 1:size(L - 5,2);
        
        color =  squeeze(RGB(r,c,:))'; %1x3
        
        matches = ismember(colors, color); %1x3
        matches = matches(:,1) .* matches(:,2) .* matches(:,3); % 1x1
        l = find(matches, 1); %bool
        if l
            L(r,c) = l; %out = size_t
        else
            colors = [colors ; color]; %dodanie do colors wektora color
            L(r,c) = size(colors,1); %out = colors.size();
        end
    end
end


