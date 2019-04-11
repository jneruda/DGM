#include <DGM\dgm.hpp>
#include <cassert>

void dgm::TilesetRenderer::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = texturePtr;

	// draw the vertex array
	target.draw(vertices, states);
}

void dgm::TilesetRenderer::changeTile_(float x, float y, uint32_t tileIndex, uint32_t tileValue) {
	assert(tileValue < clip.getFrameCount());
	assert(tileIndex * 4 < vertices.getVertexCount());

	// Find textureRect for this tile
	const sf::IntRect &frame = clip.getFrame(tileValue);

	// get a pointer to the current tile's quad
	sf::Vertex *quad = &vertices[tileIndex * 4];

	// Define corners
	quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
	quad[1].position = sf::Vector2f((x + 1.f) * tileSize.x, y * tileSize.y);
	quad[2].position = sf::Vector2f((x + 1.f) * tileSize.x, (y + 1.f) * tileSize.y);
	quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1.f) * tileSize.y);

	// Define texture coordinates
	quad[0].texCoords = sf::Vector2f(float(frame.left), float(frame.top));
	quad[1].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top));
	quad[2].texCoords = sf::Vector2f(float(frame.left + frame.width), float(frame.top + frame.height));
	quad[3].texCoords = sf::Vector2f(float(frame.left), float(frame.top + frame.height));
}

void dgm::TilesetRenderer::build(const dgm::Clip &clip, const sf::Vector2i tileSize, const std::vector<int> &imageData, const sf::Vector2i &dataSize) {
	assert(imageData.size() == dataSize.x * dataSize.y);

	TilesetRenderer::clip = clip;
	TilesetRenderer::tileSize = sf::Vector2f(float(tileSize.x), float(tileSize.y));
	TilesetRenderer::dataSize = dataSize;

	// initialize vertex array
	vertices.clear();
	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(dataSize.x * dataSize.y * 4);

	// Loop over all tiles
	for (int y = 0; y < dataSize.y; y++) {
		for (int x = 0; x < dataSize.x; x++) {
			changeTile(x, y, imageData[y * dataSize.x + x]);
		}
	}
}

void dgm::TilesetRenderer::setTexture(sf::Texture * texture) {
	assert(texture != NULL);
	texturePtr = texture;
}

dgm::TilesetRenderer::TilesetRenderer() {
}

dgm::TilesetRenderer::~TilesetRenderer() {
}