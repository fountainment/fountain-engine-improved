#if !defined(_FEI_IMAGEPOOL_H_)
#define _FEI_IMAGEPOOL_H_

#include <GL/glew.h>

#include "base/basedef.h"
#include "render/Image.h"
#include "render/Texture.h"

namespace fei {

class ImagePool
{
public:
	ImagePool();
	ImagePool(const std::string& texName, const std::string& sipName);
	ImagePool(const fei::Texture& texure, const std::string& sipName);

	void load(const std::string& texName, const std::string& sipName);
	void loadTextureAndSIP(const fei::Texture& texure, const std::string& sipName);
	void loadTextureAndIPI(const fei::Texture& texure, const std::string& ipiName);

	Image* getImage(int index);
	Image* getImage(const std::string& imagename);

	int getImageNum();
	void moveImageAnchor(const Vec2& v);

	void dumpIPI(const std::string& name);

private:
	int imageNum;
	std::map<int, int> nameHash2ImageIndex;
	std::vector<Image> imageList;
};

} // namespace fei

#endif // _FEI_IMAGEPOOL_H_
