#include "ImagePool.h"
#include "base/basedef.h"
#include "math/Rect.h"
#include "math/hash.h"

using fei::ImagePool;

const std::vector<std::pair<int, fei::Rect>> loadSipFile(const std::string& filename)
{
	std::vector<std::pair<int, fei::Rect>> result;
	char name[100];
	int x, y, imageNum, tmp;
	float rx, ry, rw, rh;
	std::FILE *sipF = std::fopen(filename.c_str(), "r");
	if (!sipF) {
		std::fprintf(stderr, "loadSipFile: \"%s\" file not exist!\n", filename.c_str());
		return result;
	}
	tmp = std::fscanf(sipF, "%d%d%d", &x, &y, &imageNum);
	for (int i = 0; i < imageNum; i++) {
		tmp = std::fscanf(sipF, "%s%f%f%f%f", name, &rw, &rh, &rx, &ry);
		if (EOF == tmp) break;
		result.push_back(std::make_pair(fei::bkdrHash(name), fei::Rect(rx, y - ry - rh, rw, rh)));
	}
	std::fclose(sipF);
	return result;
}

ImagePool::ImagePool()
: imageNum(0)
{
}

ImagePool::ImagePool(const std::string& texName, const std::string& sipName)
{
	load(texName, sipName);
}

ImagePool::ImagePool(const fei::Texture& texure, const std::string& sipName)
{
	load(texure, sipName);
}

void ImagePool::load(const std::string& texName, const std::string& sipName)
{
	fei::Texture tmpTex;
	tmpTex.load(texName);
	load(tmpTex, sipName);
}

void ImagePool::load(const fei::Texture& texure, const std::string& sipName)
{
	imageList.clear();
	auto result = loadSipFile(sipName);
	imageNum = result.size();
	for (int i = 0; i < imageNum; i++) {
		nameHash2ImageIndex[result[i].first] = i;
		imageList.push_back(texure.getImage(result[i].second));
	}
}

fei::Image* ImagePool::getImage(const std::string& imageName)
{
	int index = nameHash2ImageIndex[fei::bkdrHash(imageName)];
	return getImage(index);
}

fei::Image* ImagePool::getImage(int index)
{
	fei::Image* image = nullptr;
	if (index >= 0 && index < imageNum) {
		image = &imageList[index];
	}
	return image;
}

int ImagePool::getImageNum()
{
	return imageNum;
}
