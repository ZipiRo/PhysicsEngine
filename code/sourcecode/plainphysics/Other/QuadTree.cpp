#include "QuadTree.h"

namespace PlainPhysics
{
    RectangleBoundry::RectangleBoundry() {}

    RectangleBoundry::RectangleBoundry(Vector2D position, float width, float height)
    {
        this->position = position;
        this->width = width;
        this->height = height;
    }

    RectangleBoundry::RectangleBoundry(float x, float y, float width, float heigth)
    {
        this->position = Vector2D(x, y);
        this->width = width;
        this->height = heigth;   
    }
    
    bool RectangleBoundry::Contains(Vector2D position)
    {
        return (position.x >= this->position.x - this->width &&
                position.x <= this->position.x + this->width &&
                position.y >= this->position.y - this->height &&
                position.y <= this->position.y + this->height);
    }

    bool RectangleBoundry::Intersects(AABB bounds)
    {
        float left = this->position.x - this->width / 2;
        float right = this->position.x + this->width / 2;
        float top = this->position.y + this->height / 2;
        float bottom = this->position.y - this->height / 2;
        
        if (right <= bounds.min.x || left >= bounds.max.x) return false;
        if (top <= bounds.min.y || bottom >= bounds.max.y) return false;

        return true;       
    }

    QuadTree::QuadTree() {}

    QuadTree::QuadTree(RectangleBoundry bounds, int capacity)
    {
        this->boundry = bounds;
        this->capacity = capacity;
        this->divided = false;

        this->northest = nullptr;
        this->northwest = nullptr;
        this->southwest = nullptr;
        this->southest = nullptr;
    }    

    void QuadTree::clear()
    {
        if (!divided) return;

        if (this->northest) {
            this->northest->clear();
            delete this->northest;
            this->northest = nullptr;
        }

        if (this->northwest) {
            this->northwest->clear();
            delete this->northwest;
            this->northwest = nullptr;
        }

        if (this->southwest) {
            this->southwest->clear();
            delete this->southwest;
            this->southwest = nullptr;
        }

        if (this->southest) {
            this->southest->clear();
            delete this->southest;
            this->southest = nullptr;
        }

        divided = false;
    }

    void QuadTree::SubDivide()
    {
        float x = this->boundry.position.x;
        float y = this->boundry.position.y;
        float w = this->boundry.width;
        float h = this->boundry.height;

        RectangleBoundry NE({x - w / 2, y - h / 2, w / 2, h / 2});
        this->northest = new QuadTree(NE, this->capacity);

        RectangleBoundry NW({x + w / 2, y - h / 2, w / 2, h / 2});
        this->northwest = new QuadTree(NW, this->capacity);

        RectangleBoundry SE({x - w / 2, y + h / 2, w / 2, h / 2});
        this->southest = new QuadTree(SE, this->capacity);

        RectangleBoundry SW({x + w / 2, y + h / 2, w / 2, h / 2});
        this->southwest = new QuadTree(SW, this->capacity);

        this->divided = true;
    }

    void QuadTree::Insert(Point point)
    {
        if(!this->boundry.Contains(point.position)) return;

        if(this->points.size() < this->capacity)
        {
            this->points.push_back(point);
        }
        else
        {
            if(!divided)
                this->SubDivide();

                this->northest->Insert(point);
                this->northwest->Insert(point);
                this->southwest->Insert(point);
                this->southest->Insert(point);
        }
    }

    void QuadTree::Querry(AABB bounds, std::vector<Point>& foundPoints)
    {
        // if(!this->boundry.Intersects(bounds)) return;
        
        // for(Point point : this->points)
        // {
        //     if(bounds.Contains(point.position))
        //         foundPoints.push_back(point);
        // }

        // if(divided)
        // {
        //     this->northest->Querry(bounds, foundPoints);
        //     this->northwest->Querry(bounds, foundPoints);
        //     this->southwest->Querry(bounds, foundPoints);
        //     this->southest->Querry(bounds, foundPoints);
        // }
    }

    void QuadTree::Show(sf::RenderWindow& window)
    {
        sf::RectangleShape rectangle(sf::Vector2f(this->boundry.width * 2, this->boundry.height * 2));
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::White);
        rectangle.setOutlineThickness(0.1f);
        rectangle.setOrigin(this->boundry.width, this->boundry.height);
        rectangle.setPosition(sf::Vector2f(this->boundry.position.x, this->boundry.position.y));

        window.draw(rectangle);

        if(this->divided)
        {
            this->northest->Show(window);
            this->northwest->Show(window);
            this->southwest->Show(window);
            this->southest->Show(window);
        }
    }
}