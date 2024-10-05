#include <SFML/Graphics.hpp>
#include <list>

#include "Vector2D.h"
#include "Transform.h"
#include "VectorMath.h"
#include "Body.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Collisions.h"
#include "World.h"

namespace PlainPhysics
{
    World::World()
    {
        this->gravity = Vector2D(0, 9.81f);
        this->bodyList = std::list<Body *>();
    }

    int World::BodyCount()
    {
       return this->bodyList.size();
    }

    void World::AddBody(Body *body)
    {
        this->bodyList.push_back(body);
    }

    void World::RemoveBody(Body *body)
    {
        this->bodyList.remove(body);
    }

    Body* World::GetBody(int index)
    {
        int i = 0;
        for (Body* body : this->bodyList)
        {
            if(index == ++i) 
                return body;
        }

        return NULL;
    }

    bool Collide(Body* bodyA, Body* bodyB, Vector2D& normal, float& depth)
    {
        normal = Vector2D(0, 0);
        depth = 0.0f;

        if(bodyA->shapeType == Body::RectangleShape)
        {
            if(bodyB->shapeType == Body::RectangleShape)
            {
                return Collisions::IntersectPolygons(bodyA->GetTransformedVertices(), bodyA->position, bodyB->GetTransformedVertices(), bodyB->position, normal, depth);
            }
            else if(bodyB->shapeType == Body::CircleShape)
            {
                bool result = Collisions::IntersectCirclesPolygons(bodyB->position, bodyB->radius, bodyA->GetTransformedVertices(), bodyA->position, normal, depth);
                
                normal = (normal * -1);
                return result;
            }  
        }
        else if(bodyA->shapeType == Body::CircleShape)
        {
            if(bodyB->shapeType == Body::RectangleShape)
            {
                return Collisions::IntersectCirclesPolygons(bodyA->position, bodyA->radius, bodyB->GetTransformedVertices(), bodyB->position, normal, depth);
            }
            else if(bodyB->shapeType == Body::CircleShape)
            {
                return Collisions::IntersectCircles(bodyA->position, bodyA->radius, bodyB->position, bodyB->radius, normal, depth);
            }  
        }

        return false;
    }

    void World::Step(float delta)
    {
        for(Body* body : bodyList)
        {
            body->Step(delta);
            body->SetOutlineColor(sf::Color::White);
        }

        for(auto body_it = bodyList.begin(), body_it_ = body_it; body_it != --bodyList.end(); ++body_it)
        {
            Body* bodyA = *(body_it);    

            for(auto body_jt = ++body_it_; body_jt != bodyList.end(); ++body_jt)
            {
                Body* bodyB = *(body_jt);

                Vector2D normal; float depth;
                if(Collide(bodyA, bodyB, normal, depth))
                {
                    bodyA->SetOutlineColor(sf::Color::Red);
                    bodyB->SetOutlineColor(sf::Color::Red);
                    bodyA->Move((normal * -1) * depth / 2.0f);
                    bodyB->Move(normal * depth / 2.0f);
                }
            }
        }
    }
}