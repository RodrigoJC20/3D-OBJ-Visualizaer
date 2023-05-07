#pragma once
#ifndef OBJECTREADER_H
#define OBJECTREADER_H

#include "Model3D.h"
#include <string>

#define TRIANGLE 1
#define SQUARE 2

class ObjectReader
{
public:
	static Model3D ReadObject(const char * file_name, int type = 2);

private:
	static void ReadVertex(Model3D *, const std::string&);
	static void ReadFace(Model3D *, const std::string&, int);
	static std::vector<std::string> Split(const std::string&, char);
};

#endif


