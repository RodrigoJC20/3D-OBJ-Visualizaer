#include "ObjectReader.h"
#include <iostream>
#include <fstream>

Model3D ObjectReader::ReadObject(const char * FileName, int type) {
	Model3D *object = new Model3D();
	
	object->init(type);

	std::ifstream ifs (FileName);

	if (!ifs.is_open()) {
		std::cout << "File does not exists!" << std::endl;
		exit(1);
	}

	std::string line;

	while (std::getline(ifs, line)) {
		if (line[0] == 'v') {
			ReadVertex(object, line);
		}
		else if (line[0] == 'f') {
			ReadFace(object, line, type);
		}
		else if (line[0] == 'o') {
			std::string name = Split(line, ' ')[1];
			object->SetName(name);
		}
	}

	ifs.close();

	object->clear();

	return *object;
}

void ObjectReader::ReadVertex(Model3D* o, const std::string& line) {
	float x, y, z;

	std::vector<std::string> lineSplitted = Split(line, ' ');

	x = std::stof(lineSplitted[1]);
	y = std::stof(lineSplitted[2]);
	z = std::stof(lineSplitted[3]);

	Vertex v(x, y, z);

	o->AddVertex(v);
}

void ObjectReader::ReadFace(Model3D* o, const std::string& line, int t) {
	int a, b, c, d;
	Face f;

	std::vector<std::string> lineSplitted = Split(line, ' ');

	a = std::stoi(lineSplitted[1]);
	b = std::stoi(lineSplitted[2]);
	c = std::stoi(lineSplitted[3]);

	if (t == 2) {
		d = std::stoi(lineSplitted[4]);
		f.AddVertices(a, b, c, d);
	}
	else {
		f.AddVertices(a, b, c);
	}

	o->AddFace(f);
}

std::vector<std::string> ObjectReader::Split(const std::string& s, char separator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = s.find(separator, pos)) != std::string::npos)
	{
		std::string substring(s.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		prev_pos = ++pos;
	}

	output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word

	return output;
}
