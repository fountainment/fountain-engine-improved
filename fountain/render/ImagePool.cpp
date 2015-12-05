#include "render/ImagePool.h"

#include "base/basedef.h"
#include "math/hash.h"
#include "math/Rect.h"

using fei::ImagePool;

struct ImageInfo {
	ImageInfo(int hash, fei::Rect rect, fei::Vec2 anchor)
	: _hash(hash),
	  _rect(rect),
	  _anchor(anchor)
	{}

	int _hash;
	fei::Rect _rect;
	fei::Vec2 _anchor;
};

const std::vector<ImageInfo> loadSipFile(const std::string& filename)
{
	std::vector<ImageInfo> result;
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
		result.push_back(ImageInfo(fei::bkdrHash(name), fei::Rect(rx, y - ry - rh, rw, rh), fei::Vec2::ZERO));
	}
	std::fclose(sipF);
	return result;
}

const std::vector<ImageInfo> loadIpiFile(const std::string& filename)
{
	std::vector<ImageInfo> result;
	char name[100];
	int x, y, imageNum, tmp;
	float rx, ry, rw, rh, ax, ay;
	std::FILE *ipiF = std::fopen(filename.c_str(), "r");
	if (!ipiF) {
		std::fprintf(stderr, "loadIpiFile: \"%s\" file not exist!\n", filename.c_str());
		return result;
	}
	tmp = std::fscanf(ipiF, "%d%d%d", &x, &y, &imageNum);
	for (int i = 0; i < imageNum; i++) {
		tmp = std::fscanf(ipiF, "%s%f%f%f%f%f%f", name, &rw, &rh, &rx, &ry, &ax, &ay);
		if (EOF == tmp) break;
		result.push_back(ImageInfo(fei::bkdrHash(name), fei::Rect(rx, y - ry - rh, rw, rh), fei::Vec2(ax, -ay)));
	}
	std::fclose(ipiF);
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
	loadTextureAndSIP(texure, sipName);
}

void ImagePool::load(const std::string& texName, const std::string& sipName)
{
	fei::Texture tmpTex;
	tmpTex.load(texName);
	loadTextureAndSIP(tmpTex, sipName);
}

void ImagePool::loadTextureAndSIP(const fei::Texture& texure, const std::string& sipName)
{
	imageList.clear();
	auto result = loadSipFile(sipName);
	imageNum = result.size();
	for (int i = 0; i < imageNum; i++) {
		nameHash2ImageIndex[result[i]._hash] = i;
		auto image = texure.getImage(result[i]._rect);
		image.setAnchor(result[i]._anchor);
		imageList.push_back(image);
	}
}

void ImagePool::loadTextureAndIPI(const fei::Texture& texure, const std::string& ipiName)
{
	imageList.clear();
	auto result = loadIpiFile(ipiName);
	imageNum = result.size();
	for (int i = 0; i < imageNum; i++) {
		nameHash2ImageIndex[result[i]._hash] = i;
		auto image = texure.getImage(result[i]._rect);
		image.setAnchor(result[i]._anchor);
		imageList.push_back(image);
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
