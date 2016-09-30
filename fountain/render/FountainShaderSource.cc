#include "render/FountainShader.h"

const GLchar *fei::FountainShader::defaultVert_ = {
#include "fountain.vert.inc"
};

const GLchar *fei::FountainShader::defaultFrag_ = {
#include "fountain.frag.inc"
};
