#pragma once
#include <string>

class Level
{
private:
	std::string level_name;
	int level_id;

public:
	Level(std::string level_name, int level_id) : level_name(level_name), level_id(level_id) { };
	Level();
	~Level();
};

