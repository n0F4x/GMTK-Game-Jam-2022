#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Components/Animator.hpp"
#include "Components/Collider.hpp"
#include "Components/Drawable.hpp"
#include "Components/Physics.hpp"


namespace engine {

    /**
     * @brief   Abstract utility class for having object hierarchy for transformations based on sf::Transformable
     *          Calling transform functions will also apply changes to lower levels of the hierarchy.
     *          This class is built to work with components - see 'Component.hpp'.
     *          Supported components: Animator, Collider, Drawable, Physics
    */
    class Object {
    public:
        Object() = default;
        virtual ~Object() = default;


        ///////////////
        // Hierarchy //     Calling these will set both sides in one call.
        ///////////////
        void attach_child(Object* child);
        void detach_child(Object* child);
        void attach_parent(Object* parent);
        void detach_parent();


        ////////////////
        // Components //
        ////////////////
        void setComponent(std::unique_ptr<Animator> component);
        void setComponent(std::unique_ptr<Collider> component);
        void setComponent(std::unique_ptr<Drawable> component);
        void setComponent(std::unique_ptr<Physics> component);

        template<typename COMPONENT>
        COMPONENT* getComponent();

        void update() const;


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


    private:
        Object* _parent = nullptr;
        std::vector<Object*> _children;

        sf::Transformable _transformable;

        // Components //
        std::unique_ptr<Animator> _animator;
        std::unique_ptr<Collider> _collider;
        std::unique_ptr<Drawable> _drawable;
        std::unique_ptr<Physics> _physics;
    };

}
