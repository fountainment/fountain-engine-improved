#include "base/fileUtil.h"

using fei::File;

bool fei::isFileExist(const std::string& filename)
{
	bool ans = false;
	auto fp = std::fopen(filename.c_str(), "r");
	if (fp) {
		ans = true;
		std::fclose(fp);
	}
	return ans;
}

unsigned char* fei::readFileBuffer(FILE* fp, long* size)
{
	long fSize;
	size_t result;
	std::fseek(fp, 0, SEEK_END);
	fSize = std::ftell(fp);
	if (size) {
		*size = fSize;
	}
	std::rewind(fp);
	auto buffer = new unsigned char[fSize + 1];
	result = std::fread(buffer, 1, fSize, fp);
	buffer[fSize] = '\0';
	std::fclose(fp);
	if ((long)result != fSize) {
		std::fprintf(stderr, "FileUtil: reading error!\n");
		return nullptr;
	}
	return buffer;
}

unsigned char* fei::readFileBuffer(const std::string& filename, long* size)
{
	std::FILE *fp = std::fopen(filename.c_str(), "rb");
	unsigned char *buffer;
	if (fp) {
		buffer = fei::readFileBuffer(fp, size);
	} else {
		std::fprintf(stderr, "FileUtil: \"%s\" file not exist!\n", filename.c_str());
		return nullptr;
	}
	return buffer;
}

void fei::writeFileBuffer(const std::string& filename, const std::string& buffer)
{
	std::FILE *fp = std::fopen(filename.c_str(), "wb");
	if (fp) {
		std::fwrite(buffer.c_str(), 1, buffer.size(),fp);
		std::fclose(fp);
	}
}

File::File()
: _buffer(nullptr),
  _filePtr(nullptr),
  _fileSize(0),
  _isLoaded(false),
  _isLoading(false),
  _loadingThread(nullptr),
  _ownBuffer(false),
  _state(State::NONE)
{
}

File::~File()
{
	close();
}

bool File::open(const std::string& filename, const std::string& mode)
{
	closeFile();
	_filePtr = std::fopen(filename.c_str(), mode.c_str());
	_state = State::FILE;
	return false;
}

bool File::open(const unsigned char* ptr, int size, bool copy)
{
	deleteBuffer();
	if (copy) {
		_buffer = new unsigned char[size];
		std::memcpy(_buffer, ptr, size);
	} else {
		_buffer = (unsigned char*)ptr;
	}
	_ownBuffer = copy;
	_state = State::BUFFER;
	return false;
}

bool File::exist()
{
	return _filePtr != nullptr;
}

void File::load()
{
	if (_isLoading) {
		_loadingThread->join();
	} else {
		if (_isLoaded) {
			return;
		} else {
			loadFileIntoBuffer();
		}
	}
}

void File::loadFileIntoBuffer()
{
	_isLoaded = false;
	_isLoading = true;
	deleteBuffer();
	_buffer = fei::readFileBuffer(_filePtr, &_fileSize);
	_state = State::BUFFER;
	closeFile();
	_isLoading = false;
	_isLoaded = true;
}

void File::preload()
{
	if (_isLoading || _isLoaded) {
		return;
	}
	deleteThread();
	_loadingThread = new std::thread(&File::loadFileIntoBuffer, this);
}

bool File::isLoaded()
{
	return _isLoaded;
}

int File::scanf(const char* format, ...)
{
	//TODO: add _buffer support
	if (!_filePtr) return EOF;
	va_list args;
	va_start(args, format);
	int ret = std::fscanf(_filePtr, format, args);
	va_end(args);
	return ret;
}

void File::closeFile()
{
	if (_filePtr != nullptr) {
		std::fclose(_filePtr);
		_filePtr = nullptr;
		if (_state == State::FILE) {
			_state = State::NONE;
		}
	}
}

void File::deleteBuffer()
{
	if (_buffer.load() != nullptr) {
		if (_ownBuffer) {
			delete[] _buffer.load();
		}
		_buffer = nullptr;
		_fileSize = -1;
		if (_state == State::BUFFER) {
			_state = State::NONE;
		}
		_isLoaded = false;
	}
}

void File::deleteThread()
{
	if (_loadingThread) {
		_loadingThread->join();
		delete _loadingThread;
	}
}

void File::close()
{
	deleteThread();
	closeFile();
	deleteBuffer();
}

unsigned char* File::getBuffer()
{
	return _buffer;
}

const std::string File::getBufferString()
{
	if (_fileSize > 0) {
		return std::string((const char*)_buffer.load(), _fileSize);
	}
	return fei::EmptyStr;
}