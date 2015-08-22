#if !defined(_FEI_IMAGEPOOL_H_)
#define _FEI_IMAGEPOOL_H_

#include "render/Image.h"
#include "render/Texture.h"
#include <GL/glew.h>

namespace fei {

class ImagePool
{
public:
	ImagePool();
	ImagePool(const char* texName, const char* sipName);
	ImagePool(const fei::Texture& texure, const char* sipName);

	void load(const char* texName, const char* sipName);
	void load(const fei::Texture& texure, const char* sipName);

	Image* getImage(int index);
	Image* getImage(const char* imagename);

private:
	GLuint texId;
	int imageNum;
	std::map<int, int> nameHash2ImageIndex;
	std::vector<Image> imageList;
};

}

#endif