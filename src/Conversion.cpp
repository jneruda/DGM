#include <DGM\dgm.hpp>
#include <regex>
#include <algorithm>
#include <Strings.hpp>

const float PIOVER180 = 0.01745329252f;

using std::vector;
using std::string;
using dgm::Conversion;

uint8_t hexBitToInt(const char bit) {
	if ('a' <= bit && bit <= 'f') return uint8_t(bit - 'a' + 10);
	return uint8_t(bit - '0');
}

uint8_t hexToInt(const std::string &hex) {
	uint8_t result = 0;
	for (auto bit : hex) {
		result *= 16;
		result += hexBitToInt(bit);
	}
	return result;
}

sf::Color Conversion::stringToColor(const std::string & str) {
	std::regex hexaShort("#[0-9a-fA-F]{3}");
	std::regex hexaLong("#[0-9a-fA-F]{6}");
	std::string base;
	uint8_t colorBits[3];
	
	if (std::regex_match(str, hexaShort)) {
		base = str.substr(1);
		std::transform(base.begin(), base.end(), base.begin(), ::tolower);
		for (int i = 0; i < 3; i++) {
			colorBits[i] = hexToInt(base.substr(i, 1));
		}
	}
	else if (std::regex_match(str, hexaLong)) {
		base = str.substr(1);
		std::transform(base.begin(), base.end(), base.begin(), ::tolower);
		for (int i = 0; i < 3; i++) {
			colorBits[i] = hexToInt(base.substr(i * 2, 2));
		}
	}

	return sf::Color(colorBits[0], colorBits[1], colorBits[2]);
}

vector<int> Conversion::stringToIntArray(const char delimiter, const std::string & str) {
	vector<string> split;
	Strings::split(delimiter, str, split);
	
	vector<int> result(split.size());

	for (size_t i = 0; i < split.size(); i++) {
		result[i] = int(strtol(split[i].c_str(), NULL, 10));
	}

	return result;
}

bool Conversion::stringToVector2i(const char delimiter, const std::string & str, sf::Vector2i & dst) {
	auto arr = Conversion::stringToIntArray(delimiter, str);

	if (arr.size() == 2) {
		dst.x = arr[0];
		dst.y = arr[1];
	}

	return (arr.size() == 2);
}

bool Conversion::stringToIntRect(const char delimiter, const std::string & str, sf::IntRect & dst) {
	auto arr = Conversion::stringToIntArray(delimiter, str);

	if (arr.size() == 4) {
		dst.left = arr[0];
		dst.top = arr[1];
		dst.width = arr[2];
		dst.height = arr[3];
	}

	return (arr.size() == 4);
}

void Conversion::circleToIntRect(const dgm::Circle & circ, sf::IntRect & dst) {
	dst.left = int(circ.getPosition().x - circ.getRadius());
	dst.top = int(circ.getPosition().y - circ.getRadius());
	dst.width = int(circ.getRadius()) * 2;
	dst.height = int(circ.getRadius()) * 2;
}

sf::Vector2f Conversion::cartesianToPolar(const float x, const float y) {
	std::cerr << "Conversion::cartesianToPolar(...) - TODO this\n";
	float size = dgm::Math::vectorSize(x, y);

	float angle = asin(x / size);

	return sf::Vector2f();
}
