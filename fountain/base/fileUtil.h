#ifndef _FEI_FILEUTIL_H_
#define _FEI_FILEUTIL_H_

#include "base/basedef.h"

namespace fei {

bool isFileExist(const std::string& filename);
unsigned char* readFileBuffer(FILE* fileptr, long* size = nullptr);
unsigned char* readFileBuffer(const std::string& filename, long* size = nullptr);
void writeFileBuffer(const std::string& filename, const std::string& buffer);

class File
{
public:
	enum class State {
		NONE,
		FILE,
		BUFFER,
	};

	File();
	~File();

	bool open(const std::string& filename, const std::string& mode);
	bool open(const unsigned char* ptr, int size, bool copy = true);

	bool exist();

	void load();
	void preload();
	bool isLoaded();

	int scanf(const char* format, ...);

	void closeFile();
	void deleteBuffer();
	void deleteThread();
	void close();

	unsigned char* getBuffer();
	const std::string getBufferString();

private:
	void waitLoading();
	void loadFileIntoBuffer();

	std::atomic<unsigned char*> _buffer;
	FILE* _filePtr;
	long _fileSize;

	std::atomic_bool _isLoaded;
	std::atomic_bool _isLoading;
	std::thread* _loadingThread;

	std::atomic_bool _ownBuffer;
	State _state;
};

} // namespace fei

#endif // _FEI_FILEUTIL_H_
