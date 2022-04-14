#include <vector>

namespace NES
{
    //Physics Class
    //This class is the core of the physics system.
class Physics
{
public:
    Physics(); //Constructor
    ~Physics(); //Destructor

    // Collider class
    //This class is used to create colliders.
    class Collider
    {
    public:
        Collider(); //Constructor
        ~Collider(); //Destructor

        // Check if two colliders are colliding
        bool isColliding(Collider* other);
        bool isColliding(Collider& other);

        // Check if a collider is colliding with a box
        bool isColliding(int x, int y, int w, int h);

        //Position of the collider
        int x;
        int y;

        //Size of the collider
        int w;
        int h;

    };

    //Physics Object class
    class Object
    {
    public:
        Object(); //Constructor
        ~Object();  //Destructor

        //Set Position of the object
        void SetPosition(int x, int y);

        //Set the velocity of the object
        void SetVelocity(int x, int y);

        //Set the acceleration of the object
        void SetAcceleration(int x, int y);

        //Set the mass of the object
        void SetMass(int m);

        //Set the friction of the object
        void SetFriction(int f);
        
        //Get the position of the object
        int GetPositionX();
        int GetPositionY();

        //Get the velocity of the object
        int GetVelocityX();
        int GetVelocityY();

        //Get the acceleration of the object
        int GetAccelerationX();
        int GetAccelerationY();

        //Get the mass of the object
        int GetMass();

        //Get the friction of the object
        int GetFriction();

        //Update the object
        void Update();


    private:
        //Position of the object
        int positionX;
        int positionY;
        //Velocity of the object
        int velocityX;
        int velocityY;
        //Acceleration of the object
        int accelerationX;
        int accelerationY;
        //Mass of the object
        int mass;
        //Friction of the object
        int friction;
    };

    // Collision struct
    struct Collision {
        //Direction of the collision
        bool top; 
        bool bottom;
        bool left;
        bool right;
        //Objects that collided
        Object* A;
        Object* B;
    };

    //Check if two objects are colliding
    Collision CheckCollision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);
    //Perform a Raycast
    Collision Raycast(int x, int y, int x2, int y2);
    //Perform a Circlecast
    Collision CircleCast(int x, int y, int radius);
    //Perform a Boxcast
    Collision RectangleCast(int x, int y, int width, int height);
    //Perform a Linecast
    Collision LineCast(int x, int y, int x2, int y2);
    //Perform a PointCast
    Collision PointCast(int x, int y);

    // Physics World Class
    class World
    {
    public:
        World(); //Constructor
        ~World(); //Destructor

        void Update(); //Update the world

        void SetGravity(float gravity); //Set the gravity of the world

        void AddObject(Physics::Object* object); //Add an object to the world

    private:
        std::vector<Physics::Object> objects; //List of objects
        float gravity; //Gravity of the world
    };

};
};
