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
			bool isPos = false;
			string name = "";
			string key = "";
			int rectInd = 0;
			bool isRectStart = false;
			bool isRectEnd = false;
			bool flag = false;
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
					std::string id = "";
					string depth = "";
					string xp = "", yp = "", w = "", h = "";
					bool isStart = false;
					bool isEnd = false;
					bool isMiddle = false;
					bool isIdStart = false;
					bool isIdEnd = false;

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

							if (isRectStart && chr=='}') {
								isRectStart =false;
								isRectEnd = true;
							}


							if (isRectStart) {
								if (chr == ',') {
									rectInd++;
									flag = true;
								}
								else {
									flag = false;
								}
							}


							if (isRectStart && !flag) {
								if (rectInd == 0) {
									depth += chr;
								}
								if (rectInd == 1) {
									xp += chr;
								}
								if (rectInd == 2) {
									yp += chr;
								}
								if (rectInd == 3) {
									w += chr;
								}
								if (rectInd == 4) {
									h += chr;
								}
							}

							if (chr == '{') {
								isRectStart = true;
								isRectEnd = false;
							}


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

							if (isEnd && isIdEnd) {
								float xcor = std::stod(x);
								float ycor = std::stod(y);
								Vector2f pos;
								pos.x = xcor;
								pos.y = ycor;
								float xval = std::stof(xp);
								float yval = std::stof(yp);
								float wval = std::stof(w);
								float hval = std::stof(h);
								int dep= std::stoi(depth);
								FloatRect rect(xval,yval,wval,hval);

								StaticObject* obj = new StaticObject(&_assets->GetTexture(tex_name), pos, tex_name);
								if (id == "0") {
									obj->id = "null";
								}
								else {
									obj->id = id;
								}
								obj->IRect = rect;
								obj->depth = dep;

								obj_map[tex_name].push_back(obj);
								x = "";
								y = "";
								id = "";
								isMiddle = false;
								isStart = false;
								isEnd = false;
								isIdStart = false;
								isIdEnd = false;
								isRectEnd = false;
								isRectStart = false;
								flag = false;
								isPos = false;
								rectInd = 0;
							}

							if (chr == ']') {
								isIdStart = false;
								isIdEnd = true;
							}

							if (isIdStart && isEnd) {
								id += chr;
							}

							if (chr=='[') {
								isIdStart = true;
								isIdEnd = false;
							}
							

							

							if (chr == '(') {
								isPos = true;
								isStart = true;
								isMiddle = false;
								isEnd = false;
							}

							if (isPos && chr == ',') {
								isMiddle = true;
								isEnd = false;
								isStart = false;
							}
						}
						ind++;
					}
				}
				std::cout << std::endl;
				lineno++;


			}
		}
		else {
			cout << "file couldnt be opened!";
		}


		Map map(mapkey, obj_map);
		return map;
	}

}