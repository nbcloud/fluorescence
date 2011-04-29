
#include "gumpmenus.hpp"

#include <sstream>
#include <list>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include <client.hpp>
#include <misc/logger.hpp>
#include <misc/config.hpp>

#include "gumpmenu.hpp"
#include "gumpfactory.hpp"
#include "components/localbutton.hpp"

namespace uome {
namespace ui {

GumpMenu* GumpMenus::openMessageBox(const std::string& message) {
    GumpMenu* menu = GumpFactory::fromXmlFile("messagebox");
    if (menu) {
        menu->setComponentText<CL_Label>("messagetext", message);
    }

    LOGARG_INFO(LOGTYPE_UI, "MessageBox: %s", message.c_str());

    return menu;
}

GumpMenu* GumpMenus::openLoginGump() {
    GumpMenu* menu = GumpFactory::fromXmlFile("login");

    if (menu) {
        Config* config = Client::getSingleton()->getConfig();
        menu->setComponentTextFromConfig<CL_LineEdit>("loginhost", "shard.host", config);

        if (config->count("shard.port") > 0) {
            std::stringstream ss;
            ss << config->get("shard.port").as<unsigned short>();
            menu->setComponentText<CL_LineEdit>("loginport", ss.str());
        }

        menu->setComponentTextFromConfig<CL_LineEdit>("loginaccount", "shard.account", config);
        menu->setComponentTextFromConfig<CL_LineEdit>("loginpassword", "shard.password", config);

    }

    return menu;
}

GumpMenu* GumpMenus::openShardSelectionGump() {
    namespace bfs = boost::filesystem;

    bfs::path path("shards");

    if (!bfs::exists(path) || !bfs::is_directory(path)) {
        LOG_ERROR(LOGTYPE_UI, "Unable to list shards directory");
        return NULL;
    }

    GumpMenu* menu = GumpFactory::fromXmlFile("shardselection");

    if (menu) {
        std::list<std::string> nameList;

        bfs::directory_iterator nameIter(path);
        bfs::directory_iterator nameEnd;

        std::vector<CL_GUIComponent*> allComponents = menu->get_child_components();
        std::vector<CL_GUIComponent*>::iterator compIter = allComponents.begin();
        std::vector<CL_GUIComponent*>::iterator compEnd = allComponents.end();

        for (; compIter != compEnd; ++compIter) {
            ui::components::LocalButton* localButton = dynamic_cast<ui::components::LocalButton*>(*compIter);

            if (localButton && localButton->getAction() == "selectshard") {
                if (nameIter != nameEnd) {
                    // another shard left
                    std::string shardName = nameIter->path().filename();
                    localButton->setParameter(shardName);
                    localButton->set_text(shardName);

                    do {
                        ++nameIter;
                    } while (nameIter != nameEnd && !bfs::is_directory(nameIter->status()));
                } else {
                    localButton->set_enabled(false);
                    localButton->set_text("- - -");
                }
            }
        }


    }

    return menu;
}

}
}
