#pragma once

#include <list>
#include <SFML/Graphics.hpp>


namespace engine {

    /**
     * @brief   Abstract utility class for having object hierarchy for transformations based on sf::Transformable and sf::Drawable
     *          Calling transform functions will also apply changes to lower levels of the hierarchy.
    */
    class Node : public sf::Drawable {
    public:
        Node() = default;

        // Game loop
        virtual void update() { /*empty by default*/ }

        /*
        * @brief Methods creating or destroying parent - child connections (setting both sides in one call)
        */
        void attach_child(Node* child);
        void detach_child(Node* child);
        void attach_parent(Node* parent);
        void detach_parent();


        ///////////////////
        // Transformable //
        ///////////////////
        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);
        void setRotation(float angle);
        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f& factors);
        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f& origin);
        const sf::Vector2f& getPosition() const;
        float getRotation() const;
        const sf::Vector2f& getScale() const;
        const sf::Vector2f& getOrigin() const;
        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f& offset);
        void rotate(float angle);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);
        const sf::Transform& getTransform() const;
        const sf::Transform& getInverseTransform() const;

    protected:
        // Overriding sf::Drawable
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

        // Helper functions - designed for inheritance //
        virtual void onMove(float offsetX, float offsetY) { /*empty by default*/ };
        virtual void onMove(const sf::Vector2f& offset) { /*empty by default*/ };
        virtual void onRotate(float angle) { /*empty by default*/ };
        virtual void onScale(float factorX, float factorY) { /*empty by default*/ };
        virtual void onScale(const sf::Vector2f& factor) { /*empty by default*/ };



    private:
        Node* _parent = nullptr;
        std::list<Node*> _children;

        sf::Transformable _transformable;
    };

}
