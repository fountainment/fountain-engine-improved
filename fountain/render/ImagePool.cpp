#include "render/ImagePool.h"

#include "base/basedef.h"
#include "math/hash.h"
#include "math/Rect.h"

using fei::ImagePool;

struct ImageInfo {
	ImageInfo(const std::string& name, int hash, fei::Rect rect, fei::Vec2 anchor)
	: _name(name),
	  _hash(hash),
	  _rect(rect),
	  _anchor(anchor)
	{}

	const std::string& _name;
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
		result.push_back(ImageInfo(name, fei::bkdrHash(name), \
				fei::Rect(rx, y - ry - rh, rw, rh), fei::Vec2::ZERO));
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
		result.push_back(ImageInfo(name, fei::bkdrHash(name), \
				fei::Rect(rx, y - ry - rh, rw, rh), fei::Vec2(ax, -ay)));
	}
	std::fclose(ipiF);
	return result;
}

void writeIpiFile(const std::string& filename, const fei::Vec2& size, const std::vector<ImageInfo>& imageInfo)
{
	std::FILE *ipiF = std::fopen(filename.c_str(), "w");
	if (!ipiF) {
		std::fprintf(stderr, "loadIpiFile: \"%s\" file not exist!\n", filename.c_str());
		return;
	}
	std::fprintf(ipiF, "%.0f %.0f\n%d\n", size.x, size.y, (int)imageInfo.size());
	for (auto im : imageInfo) {
		auto pos = im._rect.getPosition();
		auto imsize = im._rect.getSize();
		std::fprintf(ipiF, "%s %.0f %.0f %.0f %.0f %f %f\n", \
				im._name.c_str(), imsize.x, imsize.y, \
				pos.x, size.y - pos.y - imsize.y, \
				im._anchor.x, -im._anchor.y);
	}
	std::fclose(ipiF);
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

void ImagePool::moveImageAnchor(const fei::Vec2& v)
{
	for (auto& image : imageList) {
		image.moveAnchor(v);
	}
}

void ImagePool::dumpIPI(const std::string& name)
{
	std::vector<ImageInfo> infoVec;
	fei::Vec2 texSize;
	if (!imageList.empty()) {
		texSize = imageList[0].getTextureSize();
	}
	for (auto image : imageList) {
		auto rect = image.getTexturePixelRect();
		auto pos = rect.getPosition();
		pos.y = texSize.y - pos.y - image.getSize().y;
		rect.setPosition(pos);
		auto anchor = image.getAnchor();
		infoVec.push_back(ImageInfo("test", 123, rect, anchor));
	}
	writeIpiFile(name, texSize, infoVec);
}
