/*
 * fluorescence is a free, customizable Ultima Online client.
 * Copyright (C) 2011-2012, http://fluorescence-client.org

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef FLUO_UI_COMPONENTS_BACKGROUND_HPP
#define FLUO_UI_COMPONENTS_BACKGROUND_HPP

#include <ClanLib/Core/Math/quad.h>
#include <ClanLib/GUI/gui_component.h>
#include <ClanLib/Display/Render/graphic_context.h>
#include <boost/shared_ptr.hpp>

namespace fluo {
namespace ui {

class Texture;
class GumpFactory;
    
namespace components {

class Background : public CL_GUIComponent {

friend class ui::GumpFactory;

public:
    Background(CL_GUIComponent* parent);

    void setBaseId(unsigned int id);
    void render(CL_GraphicContext& gc, const CL_Rect& clipRect);
    
    void setColorRGBA(const CL_Colorf& color);
    void setHue(unsigned int hue);
    void setAlpha(float alpha);
    
private:
    boost::shared_ptr<ui::Texture> textures_[9];
    CL_Vec2f vertexCoords_[9][6];
    CL_Vec2f textureCoords_[9][6];
    
    CL_Vec3f hueInfo_;
    CL_Colorf colorRgba_;
    
    void renderShader(CL_GraphicContext& gc, const CL_Rect& clipRect);
    
    // due to some strange clanlib behaviour. when opening a paperdoll for the first time, the hue texture seems
    // not to be loaded correctly, so the gump is mostly black (with outlines). When rendering it again, all seems
    // fine. this flag indicates wheter the renderer has to re-render the image because of this condition
    bool requireInitialRepaint_;
    
    void calculateVertexCoordinates();
    void setVertexCoordinates(unsigned int index, const CL_Rectf& rect);
    void setTextureCoordinates(unsigned int index, const CL_Rectf& rect);
    
    void calculateQuadCoordinates();
    CL_Quadf quadCoords_[9];
    CL_Rectf quadTextureCoords_[9];
};

}
}
}

#endif

