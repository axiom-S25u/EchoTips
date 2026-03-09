#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/utils/random.hpp>
#include <fstream>
#include <vector>
#include <string>

using namespace geode::prelude;

class $modify(MyLoadingLayer, LoadingLayer) {
    bool init(bool fromReload) {
        if (!LoadingLayer::init(fromReload)) return false;

        std::vector<std::string> fakeTips;

        auto filePath = CCFileUtils::sharedFileUtils()->fullPathForFilename("tips.txt", false);

        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    fakeTips.push_back(line);
                }
            }
            file.close();
        }

        if (fakeTips.empty()) {
            fakeTips = {
                "optimizing wave physics... 73%",
                "negotiating with spikes",
                "downloading more skill"
            };
        }

        int r = geode::utils::random(0, static_cast<int>(fakeTips.size() - 1));

        auto label = this->getChildByType<CCLabelBMFont>(0);
        if (label) {
            label->setString(fakeTips[r].c_str());
        }

        return true;
    }
};
