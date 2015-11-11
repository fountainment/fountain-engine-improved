#include "audio/Source.h"

#include "base/basedef.h"

/*
* Special thanks to Oliver Plunkett
* http://www.dunsanyinteractive.com/blogs/oliver/?p=72
*/

#define TEST_ERROR(_msg)\
	error = alGetError();\
	if (error != AL_NO_ERROR) {\
		std::fprintf(stderr,_msg "\n");\
		return -1;\
	}

struct RIFF_Header {
	char chunkID[4];
	int chunkSize;
	char format[4];
};

struct WAVE_Data {
	char subChunkID[4];
	int subChunk2Size;
};

struct WAVE_Format {
	char subChunkID[4];
	int subChunkSize;
	short audioFormat;
	short numChannels;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
};

bool loadWavFile(const std::string filename, ALuint* buffer,
                 ALsizei* size, ALsizei* frequency, ALenum* format) {
	std::FILE* soundFile = nullptr;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;
	size_t tmp;

	try {
		soundFile = std::fopen(filename.c_str(), "rb");
		if (!soundFile) {
			throw "File not found!";
		}

		tmp = std::fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		if ((riff_header.chunkID[0] != 'R' ||
		        riff_header.chunkID[1] != 'I' ||
		        riff_header.chunkID[2] != 'F' ||
		        riff_header.chunkID[3] != 'F') ||
		        (riff_header.format[0] != 'W' ||
		         riff_header.format[1] != 'A' ||
		         riff_header.format[2] != 'V' ||
		         riff_header.format[3] != 'E')) {
			throw "Invalid RIFF or WAVE Header";
		}

		tmp = std::fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
		if (wave_format.subChunkID[0] != 'f' ||
		        wave_format.subChunkID[1] != 'm' ||
		        wave_format.subChunkID[2] != 't' ||
		        wave_format.subChunkID[3] != ' ')
			throw "Invalid Wave Format!";

		if (wave_format.subChunkSize > 16)
			std::fseek(soundFile, sizeof(short), SEEK_CUR);

		tmp = std::fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
		if (!tmp) {}
		if (wave_data.subChunkID[0] != 'd' ||
		        wave_data.subChunkID[1] != 'a' ||
		        wave_data.subChunkID[2] != 't' ||
		        wave_data.subChunkID[3] != 'a') {
			throw "Invalid data header!";
		}
		data = new unsigned char[wave_data.subChunk2Size];
		if (!std::fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw "Error loading WAVE data into struct!";
		*size = wave_data.subChunk2Size;
		*frequency = wave_format.sampleRate;
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8 )
				*format = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_MONO16;
		} else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8 )
				*format = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				*format = AL_FORMAT_STEREO16;
		}
		alBufferData(*buffer, *format, (void*)data,
		             *size, *frequency);
		delete [] data;
		std::fclose(soundFile);
		return true;
	} catch(const char *error) {
		std::fprintf(stderr, "Audio: Loading \"%s\": %s\n", filename.c_str(), error);
		if (soundFile) {
			std::fclose(soundFile);
		}
		return false;
	}
}

/*
* http://www.dunsanyinteractive.com/blogs/oliver/?p=72
*/

using fei::Source;

Source::Source()
{
	alGenSources(1, &id);
	alGenBuffers(1, &buffer);
	setPitch(1.0f);
	setGain(1.0f);
	setPosition(fei::Vec2::ZERO);
	setVelocity(fei::Vec2::ZERO);
	setLoop(false);
}

Source::~Source()
{
	alDeleteSources(1, &id);
	alDeleteBuffers(1, &buffer);
}

void Source::setPitch(float pitch)
{
	if (pitch <= 0.0f || pitch > 10.0f) return;
	alSourcef(id, AL_PITCH, pitch);
}

void Source::setGain(float gain)
{
	alSourcef(id, AL_GAIN, gain);
}

void Source::setVelocity(const fei::Vec2& velocity)
{
	fei::Vec3 v3v(velocity, 0.0f);
	alSourcefv(id, AL_VELOCITY, &v3v.x);
}

void Source::setPosition(const fei::Vec2& position)
{
	fei::Vec3 v3p(position, 0.0f);
	alSourcefv(id, AL_POSITION, &v3p.x);
}

bool Source::loadWAV(const std::string& filename)
{
	ALsizei size, frequency;
	ALenum format;
	bool state = loadWavFile(filename.c_str(), &buffer, &size, &frequency, &format);
	if (!state) {
		return false;
	}
	alSourcei(id, AL_BUFFER, buffer);
	return true;
}

void Source::play()
{
	alSourcePlay(id);
}

void Source::pause()
{
	alSourcePause(id);
}

void Source::stop()
{
	alSourceStop(id);
}

void Source::setLoop(bool loop)
{
	if (loop) {
		alSourcei(id, AL_LOOPING, AL_TRUE);
	} else {
		alSourcei(id, AL_LOOPING, AL_FALSE);
	}
}
