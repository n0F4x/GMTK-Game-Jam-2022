#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "components/Animator.hpp"
#include "components/Collider.hpp"
#include "components/Physics.hpp"

namespace engine {

    /**
     * @brief   Abstract utility class for having object hierarchy for transformations based on sf::Transformable
     *          Calling transform functions will also apply changes to lower levels of the hierarchy.
     *          This class is built to work with components - see 'Component.hpp'.
     *          Supported components: Animator, Collider, Physics
    */
    class Object {
    public:
        Object() = default;


        ///////////////
        // Hierarchy //     Calling these will set both sides in one call.
        ///////////////
        void attach_child(Object* child);
        void detach_child(Object* child);
        void attach_parent(Object* parent);
        void detach_parent();
        bool hasParent() const;


        ////////////////
        // Components //
        ////////////////
        Animator* setComponent(std::unique_ptr<Animator> component);
        Collider* setComponent(std::unique_ptr<Collider> component);
        Physics* setComponent(std::unique_ptr<Physics> component);

        template<typename COMPONENT>
        COMPONENT* getComponent();

        virtual void update();


        ///////////////////
        // Transformable //
        ///////////////////
        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);
        void setRotation(float angle);
        void setScale(float factor);
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
        void scale(float factor);
        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);

        const sf::Transform& getTransform() const;
        const sf::Transform& getInverseTransform() const;


        /////////////
        // Texture //
        /////////////
        virtual void setTexture(const sf::Texture*, bool) { /*empty*/ }
        virtual const sf::Texture* getTexture() const { return nullptr; }

        virtual ~Object() = default;


    private:
        Object* _parent = nullptr;
        std::vector<Object*> _children;

        sf::Transformable _transformable;

        // Components //
        std::unique_ptr<Animator> _animator;
        std::unique_ptr<Collider> _collider;
        std::unique_ptr<Physics> _physics;
    };

}
