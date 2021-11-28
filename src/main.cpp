#include <iostream>
#include <sstream>

#include "image/image.hpp"
#include "kmeans/kmeans.hpp"
#include "label/label.hpp"

int main(int argc, char** argv)
{
    std::stringstream strValue;
    unsigned int intValue;

    if (argc <= 3)
    {
        printf("Wrong input\n");
        exit(1);
    }

    strValue << argv[1];
    strValue >> intValue;

    Image im(0, 0);
    im.read(argv[2]);

    std::vector<Colors> colors = im.getColors();

    KMeans kmeans(intValue, colors.size());

    kmeans.calculate(colors);

    im.parseColors(kmeans.clusters);

    im.save(argv[3]);

    Label label(im.width(), im.hight());
    label.calculate(kmeans.clusters);
    label.save("../data/data.txt");

    return 0;
}