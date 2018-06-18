#pragma once

#include"AssetManager.h"
#include"Object.h"
#include"StaticObject.h"
#include<fstream>
#include<sfml/Graphics.hpp>
#include"Map.h"

namespace sg {

	class MapLoader
	{
	public:
		MapLoader();
		Map loadMap(std::string filename, AssetManager* _assets);
		void init(AssetManager* _assets);

	};

}