#ifndef UOME_NET_MANAGER_HPP
#define UOME_NET_MANAGER_HPP

#include <boost/shared_ptr.hpp>

#include <misc/config.hpp>

#include "packet.hpp"
#include "socket.hpp"

namespace uome {
namespace ui {
    class GumpMenu;
    namespace components {
        class LocalButton;
    }
}

namespace net {

namespace packets {
    class ServerRedirect;
}

class Manager {
public:
    static bool create(const Config& config);
    static Manager* getSingleton();
    static void destroy();

    void step();

    static boost::shared_ptr<Packet> createPacket(uint8_t id);

    bool connect(ui::GumpMenu* menu, ui::components::LocalButton* button);
    void disconnect();

    bool selectServer(ui::GumpMenu* menu, ui::components::LocalButton* button);

    void handleServerRedirect(const packets::ServerRedirect* packet);

private:
    static Manager* singleton_;
    Manager(const Config& config);
    Manager(const Manager& copy) { }
    Manager& operator=(const Manager& copy) { return *this; }
    ~Manager();

    Socket socket_;

};

}
}

#endif
