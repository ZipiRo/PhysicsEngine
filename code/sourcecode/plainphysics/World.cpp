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

    void SeparateBodies(Body *bodyA, Body *bodyB, Vector2D MinTranslationVector)
    {
        if(bodyA->isStatic)
        {
            bodyB->Move(MinTranslationVector);
        }
        else if(bodyB->isStatic)
        {
            bodyA->Move(-MinTranslationVector);
        }
        else 
        {
            bodyA->Move(-MinTranslationVector / 2.0f);
            bodyB->Move(MinTranslationVector / 2.0f);
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

    void ResolveCollisionRotation(Manifold contact) {
        Body* bodyA = contact.bodyA;
        Body* bodyB = contact.bodyB;
        Vector2D normal = contact.normal;
        Vector2D contactOne = contact.contactOne;
        Vector2D contactTwo = contact.contactTwo;
        int contactCount = contact.contactCount;

        Vector2D contactList[2] = { contactOne, contactTwo };
        Vector2D impulseList[2] = { Vector2D(0, 0), Vector2D(0, 0) };
        Vector2D raList[2] = { Vector2D(0, 0), Vector2D(0, 0) };
        Vector2D rbList[2] = { Vector2D(0, 0), Vector2D(0, 0) };

        float e = std::min(bodyA->restitution, bodyB->restitution);

        for (int i = 0; i < contactCount; i++)
        {
            Vector2D ra = contactList[i] - bodyA->position;
            Vector2D rb = contactList[i] - bodyB->position;

            raList[i] = ra;
            rbList[i] = rb;

            Vector2D raPerp = Vector2D(-ra.y, ra.x);
            Vector2D rbPerp = Vector2D(-rb.y, rb.x);

            Vector2D angularLinearVelocityA = raPerp * bodyA->angularVelocity;
            Vector2D angularLinearVelocityB = rbPerp * bodyB->angularVelocity;

            Vector2D relativeVelocity =
                (bodyB->linearVelocity + angularLinearVelocityB) -
                (bodyA->linearVelocity + angularLinearVelocityA);

            float contactVelocityMag =VectorMath::DotProduct(relativeVelocity, normal);

            if (contactVelocityMag > 0.0f)
                continue;

            float raPerpDotN = VectorMath::DotProduct(raPerp, normal);
            float rbPerpDotN = VectorMath::DotProduct(rbPerp, normal);

            float denom = bodyA->invMass + bodyB->invMass +
                (raPerpDotN * raPerpDotN) * bodyA->invInertia +
                (rbPerpDotN * rbPerpDotN) * bodyB->invInertia;

            float j = -(1.0f + e) * contactVelocityMag;
            j /= denom;
            j /= (float)contactCount;

            Vector2D impulse = j * normal;
            impulseList[i] = impulse;
        }

        for (int i = 0; i < contactCount; i++)
        {
            Vector2D impulse = impulseList[i];
            Vector2D ra = raList[i];
            Vector2D rb = rbList[i];

            bodyA->linearVelocity += -impulse * bodyA->invMass;
            bodyA->angularVelocity += -VectorMath::CrossProduct(ra, impulse) * bodyA->invInertia;
            bodyB->linearVelocity += impulse * bodyB->invMass;
            bodyB->angularVelocity += VectorMath::CrossProduct(rb, impulse) * bodyB->invInertia;
        }
    }

    void ResolveCollisionRotationFriction(Manifold contact) {
        Body* bodyA = contact.bodyA;
        Body* bodyB = contact.bodyB;
        Vector2D normal = contact.normal;
        Vector2D contactOne = contact.contactOne;
        Vector2D contactTwo = contact.contactTwo;
        float depth = contact.depth;
        int contactCount = contact.contactCount;

        float e = std::min(bodyA->restitution, bodyB->restitution);

        float sf = (bodyA->staticFriction + bodyB->staticFriction) * 0.5f;
        float df = (bodyA->dinamicFriction + bodyB->dinamicFriction) * 0.5f;

        float jList[2] = {0, 0};
        Vector2D contactList[2] = {contactOne, contactTwo};
        Vector2D impulseList[2] = {Vector2D(0, 0), Vector2D(0, 0)};
        Vector2D frictionImpulseList[2] = { Vector2D(0, 0), Vector2D(0, 0) };
        Vector2D raList[2] = { Vector2D(0, 0), Vector2D(0, 0) };
        Vector2D rbList[2] = { Vector2D(0, 0), Vector2D(0, 0) };

        for (int i = 0; i < contactCount; i++) {
            Vector2D ra = contactList[i] - bodyA->position;
            Vector2D rb = contactList[i] - bodyB->position;

            raList[i] = ra; rbList[i] = rb;

            Vector2D raPerp = Vector2D(-ra.y, ra.x);
            Vector2D rbPerp = Vector2D(-rb.y, rb.x);

            Vector2D angularLinearVelocityA = raPerp * bodyA->angularVelocity;
            Vector2D angularLinearVelocityB = rbPerp * bodyB->angularVelocity;

            Vector2D relativeVelocity = 
                (bodyB->linearVelocity + angularLinearVelocityB) 
                - (bodyA->linearVelocity + angularLinearVelocityA);

            float contactVelocityMag = VectorMath::DotProduct(relativeVelocity, normal);

            if (contactVelocityMag > 0) continue;

            float raPerpDot = VectorMath::DotProduct(raPerp, normal);
            float rbPerpDot = VectorMath::DotProduct(rbPerp, normal);

            float denominator = (bodyA->invMass + bodyB->invMass) +
                (raPerpDot * raPerpDot) * bodyA->invInertia + 
                (rbPerpDot * rbPerpDot) * bodyB->invInertia;

            float j = -(1.0f + e) * contactVelocityMag;
            j /= denominator;
            j /= float(contactCount);

            Vector2D impulse = j * normal;

            impulseList[i] = impulse;
            jList[i] = j;

        }

        for (int i = 0; i < contactCount; i++) {
            Vector2D impulse = impulseList[i];
            Vector2D ra = raList[i];
            Vector2D rb = rbList[i];

            bodyA->linearVelocity += -impulse * bodyA->invMass;
            bodyA->angularVelocity += -VectorMath::CrossProduct(ra, impulse) * bodyA->invInertia;
            bodyB->linearVelocity += impulse * bodyB->invMass;
            bodyB->angularVelocity += VectorMath::CrossProduct(rb, impulse) * bodyB->invInertia;
        }

        for (int i = 0; i < contactCount; i++) {
            Vector2D ra = contactList[i] - bodyA->position;
            Vector2D rb = contactList[i] - bodyB->position;

            raList[i] = ra; rbList[i] = rb;

            Vector2D raPerp = Vector2D(-ra.y, ra.x);
            Vector2D rbPerp = Vector2D(-rb.y, rb.x);

            Vector2D angularLinearVelocityA = raPerp * bodyA->angularVelocity;
            Vector2D angularLinearVelocityB = rbPerp * bodyB->angularVelocity;

            Vector2D relativeVelocity =
                (bodyB->linearVelocity + angularLinearVelocityB)
                - (bodyA->linearVelocity + angularLinearVelocityA);

            Vector2D tangent = relativeVelocity - VectorMath::DotProduct(relativeVelocity, normal) * normal;

            if(VectorMath::NearlyEqualVectors(tangent, Vector2D(0, 0))) continue;
            else {
                tangent = VectorMath::Normalize(tangent);
            }

            float raPerpDot = VectorMath::DotProduct(raPerp, tangent);
            float rbPerpDot = VectorMath::DotProduct(rbPerp, tangent);

            float denominator = (bodyA->invMass + bodyB->invMass) +
                (raPerpDot * raPerpDot) * bodyA->invInertia +
                (rbPerpDot * rbPerpDot) * bodyB->invInertia;

            float jt = -VectorMath::DotProduct(relativeVelocity, tangent);
            jt /= denominator;
            jt /= float(contactCount);

            Vector2D frictionImpulse;
            float j = jList[i];

            if (std::abs(jt) <= j * sf) {
                frictionImpulse = jt * tangent;
            }
            else {
                frictionImpulse = -j * tangent * df;
            }

            frictionImpulseList[i] = frictionImpulse;
        }

        for (int i = 0; i < contactCount; i++) {
            Vector2D frictionImpulse = frictionImpulseList[i];
            Vector2D ra = raList[i];
            Vector2D rb = rbList[i];

            bodyA->linearVelocity += -frictionImpulse * bodyA->invMass;
            bodyA->angularVelocity += -VectorMath::CrossProduct(ra, frictionImpulse) * bodyA->invInertia;
            bodyB->linearVelocity += frictionImpulse * bodyB->invMass;
            bodyB->angularVelocity += VectorMath::CrossProduct(rb, frictionImpulse) * bodyB->invInertia;
        }
    }
    
    void World::StepBodies(float delta, int totalIterations)
    {
        for(Body* body : bodyList)
        {
            if(!body->isStatic)
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

            ResolveCollisionRotationFriction(contact);
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