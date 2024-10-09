#include "World.h"

namespace PlainPhysics
{
    World::World()
    {
        this->gravity = Vector2D(0, 9.81f);
        this->bodyList = std::list<Body *>();
        this->contactList = std::list<Manifold>();
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

    void ResolveCollisionBasic(Manifold contact)
    {
        Body *bodyA = contact.bodyA;
        Body *bodyB = contact.bodyB;
        Vector2D normal = contact.normal;
        float depth = contact.depth;

        Vector2D relativeVelocity = bodyB->linearVelocity - bodyA->linearVelocity;

        if(VectorMath::DotProduct(relativeVelocity, normal) > 0.0f) return;

        float e = std::min(bodyA->restitution, bodyB->restitution);

        float j = -(1 + e) * VectorMath::DotProduct(relativeVelocity, normal);
        j = j / (bodyA->invMass + bodyB->invMass); 

        Vector2D impulse = j * normal;

        bodyA->linearVelocity += -impulse * bodyA->invMass;
        bodyB->linearVelocity += impulse * bodyB->invMass;
    }

    bool Collide(Body* bodyA, Body* bodyB, Vector2D& normal, float& depth)
    {
        normal = Vector2D(0, 0);
        depth = 0.0f;

        if(bodyA->shapeType == Body::RectangleShape || bodyA->shapeType == Body::RegulatedPolygonShape)
        {
            if(bodyB->shapeType == Body::RectangleShape || bodyB->shapeType == Body::RegulatedPolygonShape)
            {
                return Collisions::IntersectPolygons(bodyA->GetTransformedVertices(), bodyA->position, bodyB->GetTransformedVertices(), bodyB->position, normal, depth);
            }
            else if(bodyB->shapeType == Body::CircleShape)
            {
                bool result = Collisions::IntersectCirclesPolygons(bodyB->position, bodyB->radius, bodyA->GetTransformedVertices(), bodyA->position, normal, depth);
                
                normal = -normal;
                return result;
            }  
        }
        else if(bodyA->shapeType == Body::CircleShape)
        {
            if(bodyB->shapeType == Body::RectangleShape || bodyB->shapeType == Body::RegulatedPolygonShape)
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

    void World::Step(float delta, int totalItterations)
    {
        for(int currentIterartion = 0; currentIterartion < totalItterations; currentIterartion++)
        {
            for(Body* body : bodyList)
            {
                body->AddForce(body->mass * gravity);
                body->Step(delta, totalItterations);
            }

            this->contactList.clear();

            for(auto body_it = bodyList.begin(), body_it_ = body_it; body_it != --bodyList.end(); ++body_it)
            {
                Body* bodyA = *(body_it);    
                AABB bodyA_AABB = bodyA->GetAABB();

                for(auto body_jt = ++body_it_; body_jt != bodyList.end(); ++body_jt)
                {
                    Body* bodyB = *(body_jt);
                    AABB bodyB_AABB = bodyB->GetAABB();

                    if(bodyA->isStatic && bodyB->isStatic) continue;
                    if(!Collisions::IntersectAABB(bodyA_AABB, bodyB_AABB)) continue;

                    Vector2D normal; float depth;
                    if(!Collide(bodyA, bodyB, normal, depth)) continue;

                    if(VectorMath::NAN_Values(normal)) continue;

                    if(bodyA->isStatic)
                    {
                        bodyB->Move(normal * depth);
                    }
                    else if(bodyB->isStatic)
                    {
                        bodyA->Move(-normal * depth);
                    }
                    else 
                    {
                        bodyA->Move(-normal * depth / 2.0f);
                        bodyB->Move(normal * depth / 2.0f);
                    }

                    Manifold contact(bodyA, bodyB, normal, depth, Vector2D(0, 0), Vector2D(0, 0), 0);
                    this->contactList.push_back(contact);
                }
            }

            for(Manifold contact : contactList)
                ResolveCollisionBasic(contact);
        }        
    }
}