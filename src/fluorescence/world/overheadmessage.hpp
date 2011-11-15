#ifndef FLUO_WORLD_OVERHEADMESSAGE_HPP
#define FLUO_WORLD_OVERHEADMESSAGE_HPP

#include <boost/shared_ptr.hpp>

#include "ingameobject.hpp"
#include <misc/string.hpp>

namespace fluo {

namespace ui {
class Texture;
}

namespace world {
class OverheadMessage : public IngameObject {
public:
    // If parameter useRgbColor is true, the color value is interpreted as a 32bit rgba value. If false, like a uo hue id
    OverheadMessage(const UnicodeString& text, unsigned int font, unsigned int color, bool useRgbColor = true);

    virtual boost::shared_ptr<ui::Texture> getIngameTexture() const;

    void setParentPixelOffset(int y);

    virtual void onClick();
    virtual void onAddedToParent();
    virtual void onRemovedFromParent();

    bool isExpired() const;
    void expire();

private:
    UnicodeString text_;
    boost::shared_ptr<ui::Texture> texture_;

    void updateVertexCoordinates();
    void updateRenderPriority();
    void updateTextureProvider();
    bool updateAnimation(unsigned int elapsedMillis);

    int parentPixelOffsetY_;

    int milliSecondsToLive_;
};
}
}


#endif