#pragma once
#include <string>
#include <vector>
class SceneReader
{
public:
	typedef std::string String;
	SceneReader(String directory);
	~SceneReader();

	void readFromFile();

private:
	String directory;
};