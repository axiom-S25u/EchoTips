#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <fstream>
#include <vector>
#include <string>

using namespace geode::prelude;

class $modify(MyLoadingLayer, LoadingLayer) {
    bool init(bool fromReload) {
        if (!LoadingLayer::init(fromReload)) return false;

        std::vector<std::string> fakeTips;
        
        auto filePath = Mod::get()->getResourcesDir() / "tips.txt";
        
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

        int r = geode::utils::num::rand(0, static_cast<int>(fakeTips.size() - 1));

        auto label = typeinfo_cast<CCLabelBMFont*>(this->getChildByID("loading-tip-label"));
        if (!label) {
            label = this->getChildByType<CCLabelBMFont>(0);
        }

        if (label) {
            label->setString(fakeTips[r].c_str());
        }

        return true;
    }
};
