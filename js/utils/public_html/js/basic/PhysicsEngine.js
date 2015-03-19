Vec2 = Box2D.Common.Math.b2Vec2;
BodyDef = Box2D.Dynamics.b2BodyDef;
Body = Box2D.Dynamics.b2Body;
FixtureDef = Box2D.Dynamics.b2FixtureDef;
Fixture = Box2D.Dynamics.b2Fixture;
World = Box2D.Dynamics.b2World;
MassData = Box2D.Collision.Shapes.b2MassData;
PolygonShape = Box2D.Collision.Shapes.b2PolygonShape;
CircleShape = Box2D.Collision.Shapes.b2CircleShape;
DebugDraw = Box2D.Dynamics.b2DebugDraw;
RevoluteJointDef = Box2D.Dynamics.Joints.b2RevoluteJointDef;

var entityDef = function(type, x, y, w, h, useBouncyFixture)
{
    this.type = type; // string.
    this.x = x;       // horizontal position.
    this.y = y;       // vertical position.
    this.w = w;
    this.h = h;
    this.halfWidth = this.w / 2;
    this.halfHeight = this.h / 2;
    this.useBouncyFixture = useBouncyFixture;
    this.userData = null; // Added dynamically.
};

PhysicsEngineClass = Class.extend(
{
    world: null,
    PHYSICS_LOOP_HZ : 1.0 / 60.0,
    VELOCITY : 10,
    POSITION : 10,
    BODY_TYPE : {"static" : Body.b2_staticBody, "dynamic" : Body.b2_dynamicBody},

    //-----------------------------------------
    create: function ()
    {
        // World takes two parameters:
        // a Vec2(x,y) object specifying the gravity vector
        // a Boolean allowing sleep (true) or disallowing sleep (false)
        gPhysicsEngine.world = new World(
            new Vec2(0,0),
            false
        );
    },

    //-----------------------------------------
    update: function ()
    {
        var start = Date.now();
        this.world.Step(
            this.PHYSICS_LOOP_HZ,
            this.VELOCITY,
            this.POSITION);
            
        // Call the 'ClearForces' method of the world object to remove any forces
        // at every physics update. If our hero is moving in a give direction, and
        // clear forces is not called, it will gain velocity and keep going even
        // if the player release the movement key.
        this.world.ClearForces();

        return(Date.now() - start);
    },

    //-----------------------------------------
    addContactListener: function (callbacks)
    {
        var listener = new Box2D.Dynamics.b2ContactListener();

        if(callbacks.PostSolve) listener.PostSolve = function (contact, impulse) {
            callbacks.PostSolve(contact.GetFixtureA().GetBody(),
                                contact.GetFixtureB().GetBody(),
                                impulse.normalImpulses[0]);
        };

        gPhysicsEngine.world.SetContactListener(listener);
    },
    
    //-----------------------------------------
    // Internal use.
    registerBody: function (bodyDef)
    {
        var body = this.world.CreateBody(bodyDef);
        return body;
    },

    //-----------------------------------------
    addBody: function (entityDef)
    {
        // Create a new BodyDef object
        var bodyDef = new BodyDef();

        // Check if type exist.
        if ( (entityDef.type in this.BODY_TYPE) === false )
        {
            console.log("Invalid body type: " + entityDef.type);
            return null;
        }
        bodyDef.type = this.BODY_TYPE[entityDef.type];
        bodyDef.x = entityDef.x;
        bodyDef.y = entityDef.y;
        bodyDef.allowSleep = false;
        
        if ( entityDef.userData )
        {
            bodyDef.userData = entityDef.userData;
        }

        // call registerBody with your BodyDef object to attach it to our world.
        var body = this.registerBody(bodyDef);

        // Create a new FixtureDef object
        var fixture = new FixtureDef();

        if(entityDef.useBouncyFixture)
        {
            fixture.density = 1.0;
            fixture.friction = 0;
            fixture.restitution = 1.0;
        }

        // Create a new PolygonShape object, set your FixtureDef object's
        // 'shape' member to this PolygonShape.
        fixture.shape = new PolygonShape();

        // Set the FixtureDef object's shape to a box using the shape's SetAsBox
        // method, which takes half the width and half the height of the box as
        // parameters. You should get these from the passed-in entityDef, which
        // has 'halfWidth' and 'halfHeight' properties that specify this.
        fixture.shape.SetAsBox(entityDef.halfWidth, entityDef.halfHeight);
        
        // Call the CreateFixture method of your BodyDef
        // object with your FixtureDef object as a parameter
        // to attach the fixture to your BodyDef object.
        body.CreateFixture(fixture);

        // Return your BodyDef object.
        return body;
    },

    //-----------------------------------------
    removeBody: function (obj)
    {
        this.world.DestroyBody(obj);   
    }
});

var gPhysicsEngine = new PhysicsEngineClass();