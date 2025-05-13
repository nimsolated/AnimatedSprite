#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fsys = std::filesystem;

namespace sf {
	class AnimatedSprite : public Sprite {
	public:
		// an iterator alias to iterate through a directory
		using DirectoryIterator = fsys::directory_iterator;
	public:
		// constructor: populates the frames vector from the specified directory
		AnimatedSprite(const std::string& spritesPath) : currentFrame(0) {
			if (!fsys::exists(spritesPath) || !fsys::is_directory(spritesPath)) {
				// take this branch if path doesn't exist or path is not a directory
				std::cerr << "[ERROR] Invalid directory path: " << spritesPath << std::endl;
				exit(1);
			}

			for (const auto& entry : DirectoryIterator(spritesPath)) {
				if (fsys::is_regular_file(entry) && isPNG(entry.path().filename().string())) {
					// take this branch if the entry is a PNG file
					// load texture from the entry and append it to the frames vector
					Texture tex;
					tex.loadFromFile(entry.path().filename().string(), IntRect(10, 10, 64, 64));
					frames.push_back(tex);
				}
			}
		}

		void update() {
			setTexture(frames.at(currentFrame));
			currentFrame = (currentFrame + 1) % frames.size();
		}

		void setFrames(const std::vector<Texture>& newFrames) {
			frames = newFrames;
		}
		std::vector<Texture> getFrames() const {
			return frames;
		}

		void setCurrentFrame(const size_t pos) {
			if (pos < frames.size()) {
				currentFrame = pos;
			}
		}
		size_t getCurrentFrame() const {
			return currentFrame;
		}

	private:
		// vector that contains each texture/frame
		std::vector<Texture> frames;
		size_t currentFrame;

		// checks if a file is of .png extension
		bool isPNG(const std::string& fileName) {
			std::string lowerFileName = fileName;
			std::transform(lowerFileName.begin(), lowerFileName.end(), lowerFileName.begin(), ::tolower);
			return lowerFileName.size() >= 4 && lowerFileName.substr(lowerFileName.size() - 4) == ".png";
		}
	};
}