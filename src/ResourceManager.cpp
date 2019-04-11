#include <DGM/dgm.hpp>
#include <regex>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem::v1;

void dgm::ResourceManager::deinit() {
	for (auto item : database) {
		freeResource(item.first);
	}
}

bool dgm::ResourceManager::loadFromDir(const std::string &foldername, dgm::ResourceManager::Type type, std::vector<std::string> *names) {
	fs::path path(foldername);
	if (not fs::is_directory(path)) {
		std::cerr << "ResourceManager::loadFromDir - " << foldername << " is not a directory!\n";
		return false;
	}

	fs::recursive_directory_iterator dirIter(path);
	for (auto item : dirIter) {
		fs::path itemPath(item);
		std::string name;

		switch (type) {
		case Type::Font:
			if (not loadResource<sf::Font>(itemPath.string())) return false;
			name = resourceName<sf::Font>(itemPath.string());
			break;
		case Type::Graphic:
			if (not loadResource<sf::Texture>(itemPath.string())) return false;
			name = resourceName<sf::Texture>(itemPath.string());
			break;
		case Type::Sound:
			if (not loadResource<sf::SoundBuffer>(itemPath.string())) return false;
			name = resourceName<sf::SoundBuffer>(itemPath.string());
			break;
		case Type::AnimationData:
			if (not loadResource<dgm::AnimationData>(itemPath.string())) return false;
			name = resourceName<dgm::AnimationData>(itemPath.string());
			break;
		}

		if (names != nullptr) {
			(*names).push_back(name);
		}
	}

	return true;
}

void dgm::ResourceManager::freeResource(const std::string &name) {
	if (database.find(name) == database.end()) return;

	auto itr = database.find(name);
	delete itr->second;
	database.erase(itr);
}

dgm::ResourceManager::ResourceManager() {
	
}

dgm::ResourceManager::~ResourceManager() {
	deinit();
}