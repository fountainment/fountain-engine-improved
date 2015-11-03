#include "Anime.h"
#include "anime/FrameAnime.h"
#include "render/Texture.h"
#include "render/ImagePool.h"
#include "base/basedef.h"

using fei::Anime;

Anime::~Anime()
{
}

void Anime::feiUpdate(fei::RenderObj* rObj)
{
	update(rObj);
}

void Anime::update(fei::RenderObj* rObj)
{
}

Anime* Anime::createFrameAnime(float fps, const fei::ImagePool& animeImage)
{
	FrameAnime* anime = new FrameAnime;
	anime->load(animeImage);
	anime->setFps(fps);
	return anime;
}

Anime* Anime::createFrameAnime(float fps, const fei::Texture& texture, const std::string& sipName)
{
	//TODO: redesign Anime::createFrameAnime args
	FrameAnime* anime = new FrameAnime;
	anime->load(texture, sipName);
	anime->setFps(fps);
	return anime;
}

Anime* Anime::createFrameAnime(float fps, const std::string& textureName, const std::string& sipName)
{
	FrameAnime* anime = new FrameAnime;
	anime->load(textureName, sipName);
	anime->setFps(fps);
	return anime;
}

Anime* Anime::createActionAnime()
{
	//TODO: add class ActionAnime and complete this function
	return nullptr;
}