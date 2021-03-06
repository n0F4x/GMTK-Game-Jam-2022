////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include "engine/drawables/Shape.hpp"


namespace engine {

    /**
     * @brief   Rewriting sf::RectangleShape to inherit from engine::Object instead of sf::Transformable
    */
    class RectangleShape : public Shape {
    public:
        explicit RectangleShape(const sf::Vector2f& size = sf::Vector2f{ 0, 0 });

        void setSize(const sf::Vector2f& size);

        const sf::Vector2f& getSize() const;
        std::size_t getPointCount() const override;
        sf::Vector2f getPoint(std::size_t index) const override;


    private:
        sf::Vector2f m_size; ///< Size of the rectangle
    };

}
