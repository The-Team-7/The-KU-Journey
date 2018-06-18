#include "MapLoader.h"
#include "Settings.h"
#include"DEFINITIONS.h"


using namespace std;

namespace sg {
	MapLoader::MapLoader()
	{

	}
	void MapLoader::init(AssetManager* _assets)
	{
		string dir = "assets//";
		Settings settings;

		for (auto info : settings.MapTextureInfo) {
			_assets->LoadTexture(info.first, info.second);
		}

	}

	Map MapLoader::loadMap(std::string filename, AssetManager* _assets)
	{

		std::map<std::string, std::vector<StaticObject*>> obj_map;
		std::vector<std::string> mapkey;
		string line;
		ifstream file;
		string _dir = MAPEDITOR_DIR;
		string fname = _dir + filename + ".txt";
		file.open(fname);

		if (file.is_open()) {
			int lineno = 1;
			bool isName = false;
			bool isKey = false;
			bool isEnd = false;
			string name = "";
			string key = "";
			while (getline(file, line)) {

				if (lineno == 1) {
					for (auto chr : line) {

						if (chr == '-') {
							isName = false;
							isKey = true;
						}

						if (chr == '#') {
							isEnd = true;
							isName = false;
							isKey = false;
						}

						if (isName) {
							name += chr;
						}

						if (isKey) {
							key = chr;
						}

						if (isEnd) {
							mapkey.push_back(name);
							name = "";
							key = "";
							isEnd = false;
						}

						if (chr == '@') {
							isName = true;
							isKey = false;
						}


					}
				}

				if (lineno > 1) {
					int ind = 0;
					std::string x = "";
					std::string y = "";
					bool isStart = false;
					bool isEnd = false;
					bool isMiddle = false;

					string tex_name = "";

					bool gotName = false;
					for (auto chr : line) {
						if (!gotName) {
							if (chr == '#') {
								gotName = true;
							}
							else {
								tex_name += chr;
							}

						}
						else {
							if (chr == ')') {
								isEnd = true;
								isStart = false;
								isMiddle = false;
							}

							if (isStart) {
								if (chr != ',') {
									x += chr;
								}
							}
							if (isMiddle) {
								y += chr;
							}
							if (isEnd) {

								float xcor = std::stod(x);
								float ycor = std::stod(y);
								Vector2f pos;
								pos.x = xcor;
								pos.y = ycor;
								std::cout << " " << xcor << "," << ycor;

								obj_map[tex_name].push_back(new StaticObject(&_assets->GetTexture(tex_name), pos, tex_name));
								x = "";
								y = "";
								isMiddle = false;
								isStart = false;
								isEnd = false;
							}

							if (chr == '(') {
								isStart = true;
								isMiddle = false;
								isEnd = false;
							}

							if (chr == ',') {
								isMiddle = true;
								isEnd = false;
								isStart = false;
							}
						}
						ind++;
					}
				}
				lineno++;


			}
		}
		else {
			cout << "file couldnt be opened!";
		}

		for (auto a : obj_map) {
			std::cout << a.first << " " << a.second.size() << endl;
		}

		Map map(mapkey, obj_map);
		return map;
	}

}