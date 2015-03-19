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

GameEngineClass = Class.extend(
{
    framerate : 30,
    dirVec: new Vec2(0,0),
    player : null,
    _deferredKill: [],
    entities: [],
    factory : {},
    world_physics : null,

    //-----------------------------
    setup: function (framerate, drawctx)
    {
        var self = this;
        
        this.framerate = framerate;
        this.drawctx = drawctx;
        self.world_physics = gPhysicsEngine.create();
        
        gPhysicsEngine.addContactListener(
        {
            PostSolve: function (bodyA, bodyB, impulse)
            {
                var entA = bodyA.GetUserData();
                var entB = bodyB.GetUserData();
                console.log(bodyA.GetUserData());
                
                entA.onTouch(entB, null, impulse);
                entB.onTouch(entA, null, impulse);                
            }
        });
        
        setInterval(function() {self.update(self);}, this.framerate);
    },
    
    update: function (self)
    {
        var i;
        
        if (self.player !== null)
        {
            self.updatePlayer(self);
        }
        
        for (i = 0 ; i < self.entities.length; i++)
        {
            var entity = self.entities[i];
            if (entity._killed === true)
            {
                self._deferredKill.push(entity);
                continue;
            }
            
            entity.update();
        }
        
        for (i = 0; i < self._deferredKill.length; i++)
        {
            var entity = self._deferredKill[i];
            self.entities.erase(entity);
        }
        
        self._deferredKill = [];
        
        gPhysicsEngine.update();
        this.draw(self);
    },
    
    loadPlayer: function (entity)
    {
        this.player = entity;
    },

    updatePlayer: function (self)
    {        
        var player = self.player;
        
        player.facing = FACING_NONE;
        if (gInputEngine.actions['move-up'])
        {
            player.move_dir.y -= 1;
            player.facing = FACING_UP;
        }
        if (gInputEngine.actions['move-down'])
        {
            player.move_dir.y += 1;
            player.facing = FACING_DOWN;
        }
        if (gInputEngine.actions['move-left'])
        {
            player.move_dir.x -= 1;
            player.facing = FACING_LEFT;
        }
        if (gInputEngine.actions['move-right'])
        {
            player.move_dir.x += 1;
            player.facing = FACING_RIGHT;
        }

        // After modifying the move_dir above, we check if the vector is
        // non-zero. If it is, we adjust the vector length based on the player's
        // walk speed.
        if (player.move_dir.LengthSquared())
        {
            // First set 'move_dir' to a unit vector in the same direction it's
            // currently pointing.
            player.move_dir.Normalize();

            // Next, multiply 'move_dir' by the player's set 'walkSpeed'. We do
            // this in case we might want to change the player's walk speed due
            // to a power-up, etc.
            player.move_dir.Multiply(player.speed);
        }

        // Update player position.
        player.body_phy.SetLinearVelocity(new Vec2(player.move_dir.x * player.speed, player.move_dir.y * player.speed));

//        if (self.gInputEngine.actions['fire-left'])
//        {
//            self.dirVec.x--;
//        }
//        if (self.gInputEngine.actions['fire-up'])
//        {
//            self.dirVec.y--;
//        }
//        if (self.gInputEngine.actions['fire-right'])
//        {
//            self.dirVec.x++;
//        }
//        if (self.gInputEngine.actions['fire-down'])
//        {
//            self.dirVec.y++;
//        }

        // Keyboard based facing & firing direction
//        if (self.gInputEngine.actions.fire0)// || self.gInputEngine.actions.fire1)
//        {
//            console.log("shoot!");
//
//            // TASK #1
//            // Grab the player's screen position in space. We've provided
//            // the 'gRenderEngine.getScreenPosition' method for this.
//            // It returns an object of the form:
//            // 
//            // { x, y }
//            // 
//            // Pass the player's position to this method and store the
//            // resulting value.
//            //
//            // TODO: Get player's position relative to the map!!
//
//            // TASK #2
//            // Set the dirVec property to the difference between the
//            // current mouse position and the player's position in
//            // screen space, then normalize dirVec using its normalize method.
//            //
//            self.dirVec.x = (self.gInputEngine.mouse.click.x - self.gPlayer0.pos.x);
//            self.dirVec.y = (self.gInputEngine.mouse.click.y - self.gPlayer0.pos.y);
//            self.dirVec.Normalize();
//            
////            var angleInRadians = Math.atan2(self.dirVec.y, self.dirVec.x);
////            var faceAngle0to7 = (Math.round(angleInRadians / (2 * Math.PI) * 8) + 8) % 8;
////            self.dirVec = LUTofJustice[faceAngle0to7];
//        }
        player.move_dir.x = 0;
        player.move_dir.y = 0;
    },
    
    spawnEntity: function (typename, x, y)
    {        
        if ( (typename in this.factory) !== true )
        {
            console.log(typename + " is not registered");
            return null;
        }
        
        var entity = new (this.factory[typename])();
        entity.pos.x = x;
        entity.pos.y = y;
        
        this.entities.push(entity);
        
        if (entity.entity_def != null)
        {
            entity.entity_def.userData = entity;
            var body_phy = gPhysicsEngine.addBody(entity.entity_def);
            entity.body_phy = body_phy;
            entity.body_phy.SetPosition(new Vec2(x, y));
        }
        
        console.log(entity.id + " created!");
        
        return entity;
    },
    
    //-----------------------------
    draw: function (self)
    {
        // Draw map. Note that we're passing a canvas context of 'null' in. This
        // would normally be our game context, but we don't need to grade this
        // here.
       // gMap.draw(null);

        // Bucket entities by zIndex
        var fudgeVariance = 128;
        var zIndex_array = [];
        var entities_bucketed_by_zIndex = {};
        self.entities.forEach(
        function(entity)
        {
            entity.draw(self.drawctx);
//            //don't draw entities that are off screen
//            if(entity.pos.x >= gMap.viewRect.x - fudgeVariance &&
//               entity.pos.x < gMap.viewRect.x + gMap.viewRect.w + fudgeVariance &&
//               entity.pos.y >= gMap.viewRect.y - fudgeVariance &&
//               entity.pos.y < gMap.viewRect.y + gMap.viewRect.h + fudgeVariance)
//            {
//                // Bucket the entities in the entities list by their zindex
//                // property.
//                if (zIndex_array.indexOf(entity.zIndex) === -1)
//                {
//                    zIndex_array.push(entity.zIndex);
//                    entities_bucketed_by_zIndex[entity.zIndex] = [];
//                }
//                entities_bucketed_by_zIndex[entity.zIndex].push(entity);
//            }
//            
//            zIndex_array.sort(function(a,b) { return a - b;});
//            zIndex_array.forEach(function(zIndex)
//            {
//               entities_bucketed_by_zIndex[zIndex].forEach(function(entity)
//               {
//                   entity.draw(fractionOfNextPhisicsUpdate);
//               })
//            });
                
        });

        // Draw entities sorted by zIndex
        
    }
});

gGameEngine = new GameEngineClass();

