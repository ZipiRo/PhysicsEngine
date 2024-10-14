#include "World.h"

namespace PlainPhysics
{
    World::World()
    {
        this->gravity = Vector2D(0, 9.81f);
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

        if(bodyA->shapeType == Body::PolygonShape)
        {
            if(bodyB->shapeType == Body::PolygonShape)
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
            if(bodyB->shapeType == Body::PolygonShape)
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

    void SeparateBodies(Body *bodyA, Body *bodyB, Vector2D MTV)
    {
        if(bodyA->isStatic)
        {
            bodyB->Move(MTV);
        }
        else if(bodyB->isStatic)
        {
            bodyA->Move(-MTV);
        }
        else 
        {
            bodyA->Move(-MTV / 2.0f);
            bodyB->Move(MTV / 2.0f);
        }
    }

    void FindContactPoints(Body *bodyA, Body* bodyB, Vector2D& contactOne, Vector2D& contactTwo, int& contactCount)
    {
        contactOne = Vector2D(0, 0);
        contactTwo = Vector2D(0, 0);
        contactCount = 0;

        if(bodyA->shapeType == Body::PolygonShape)
        {
            if(bodyB->shapeType == Body::PolygonShape)
            {
                Collisions::FindPolygonsContactPoints(bodyA->GetTransformedVertices(), bodyB->GetTransformedVertices(), contactOne, contactTwo, contactCount);
            }
            else if(bodyB->shapeType == Body::CircleShape)
            {
                Collisions::FindCirclePolygonContactPoint(bodyB->position, bodyB->radius, bodyA->GetTransformedVertices(), bodyA->position, contactOne);
                contactCount = 1;
            }  
        }
        else if(bodyA->shapeType == Body::CircleShape)
        {
            if(bodyB->shapeType == Body::PolygonShape)
            {
                Collisions::FindCirclePolygonContactPoint(bodyA->position, bodyA->radius, bodyB->GetTransformedVertices(), bodyB->position, contactOne);
                contactCount = 1;
            }   
            else if(bodyB->shapeType == Body::CircleShape)
            {
                Collisions::FindCircleContactPoint(bodyA->position, bodyA->radius, bodyB->position, contactOne);
                contactCount = 1;
            }  
        }
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
    
    void World::StepBodies(float delta, int totalIterations)
    {
        for(Body* body : bodyList)
        {
            body->AddForce(body->mass * gravity);
            body->Step(delta, totalIterations);
        }
    }

    void World::BroadPhase()
    {
        int i = 1;
        for(auto body_it = bodyList.begin(); body_it != bodyList.end(); ++body_it, i++)
        {
            Body* bodyA = *(body_it);    
            AABB bodyA_AABB = bodyA->GetAABB();
            
            int j = i + 1;
            for(auto body_jt = std::next(body_it); body_jt != bodyList.end(); ++body_jt, j++)
            {
                Body* bodyB = *(body_jt);
                AABB bodyB_AABB = bodyB->GetAABB();

                if(bodyA->isStatic && bodyB->isStatic) continue;
                if(!Collisions::IntersectAABB(bodyA_AABB, bodyB_AABB)) continue;
                
                contactPairs.push_back(ContactPair({i, j}));
            }
        }
    }

    void World::NarrowPhase()
    {
        for(ContactPair pair : contactPairs)
        {
            Body *bodyA = this->GetBody(pair.first);
            Body *bodyB = this->GetBody(pair.second);

            Vector2D normal; float depth;
            if(!Collide(bodyA, bodyB, normal, depth)) continue;
            if(VectorMath::NAN_Values(normal)) continue;

            SeparateBodies(bodyA, bodyB, normal * depth);

            Vector2D contactOne, contactTwo; int contactCount;
            FindContactPoints(bodyA, bodyB, contactOne, contactTwo, contactCount);
            Manifold contact(bodyA, bodyB, normal, depth, contactOne, contactTwo, contactCount);

            ResolveCollisionBasic(contact);
        }
    }

    void World::Step(float delta, int totalIterations)
    {
        for(int currentIteration = 0; currentIteration < totalIterations; currentIteration++)
        {
            this->contactPairs.clear();
            this->StepBodies(delta, totalIterations);
            this->BroadPhase();
            this->NarrowPhase();
        }        
    }
}