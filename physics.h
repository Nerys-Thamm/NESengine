#include <vector>

class Physics
{
public:
    Physics();
    ~Physics();

    


    class Collider
    {
    public:
        Collider();
        ~Collider();


        bool isColliding(Collider* other);
        bool isColliding(Collider& other);

        bool isColliding(int x, int y, int w, int h);

        int x;
        int y;

        int w;
        int h;

    };

    class Object
    {
    public:
        Object();
        ~Object();

        void setPosition(int x, int y);
        void setVelocity(int x, int y);
        void setAcceleration(int x, int y);
        void setMass(int m);
        void setFriction(int f);
        
        int getPositionX();
        int getPositionY();
        int getVelocityX();
        int getVelocityY();
        int getAccelerationX();
        int getAccelerationY();
        int getMass();
        int getFriction();

        void update();


    private:
        int positionX;
        int positionY;
        int velocityX;
        int velocityY;
        int accelerationX;
        int accelerationY;
        int mass;
        int friction;
    };

    struct Collision {
        bool top;
        bool bottom;
        bool left;
        bool right;
        Object* A;
        Object* B;
    };

    Collision CheckCollision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
    Collision Raycast(int x, int y, int x2, int y2);
    Collision CircleCast(int x, int y, int radius);
    Collision RectangleCast(int x, int y, int width, int height);
    Collision LineCast(int x, int y, int x2, int y2);
    Collision PointCast(int x, int y);

    class World
    {
    public:
        World();
        ~World();

        void update();

        void SetGravity(float gravity);

        void AddObject(Physics::Object* object);

    private:
        std::vector<Physics::Object> objects;
        float gravity;
    };

};
