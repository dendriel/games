InputEngineClass = Class.extend(
{
    bindings: {},
    actions: {},
    mouse: {
        x: 0,
        y: 0,
        click: { // last click position.
            x: 0,
            y: 0
        }
    },

    keyState : new Array(256),
    canvas : null,

    //-----------------------------
    setup: function (canvas)
    {
        this.canvas = canvas;
        var self = this;

        self.bind(87, 'move-up');
        self.bind(65, 'move-left');
        self.bind(83, 'move-down');
        self.bind(68, 'move-right');
        
        self.bind(37, 'fire-left');
        self.bind(38, 'fire-up');
        self.bind(39, 'fire-right');
        self.bind(40, 'fire-down');

        canvas.addEventListener('mousemove', function(e) {self.onMouseMove(self, e);});
        canvas.addEventListener('mousedown', function(e) {self.onMouseDown(self, e);});
        canvas.addEventListener('mouseup', function(e) {self.onMouseUp(self, e);});
        canvas.addEventListener('keydown', function(e) {self.onKeyDown(self, e);});
        canvas.addEventListener('keyup', function(e) {self.onKeyUp(self, e);});
    },

    bind: function (key, action)
    {
        this.bindings[key] = action;
    },

    //-----------------------------
    onMouseMove: function (self, e)
    {
        var rect = self.canvas.getBoundingClientRect();
        self.mouse.x = e.clientX - rect.left;
        self.mouse.y = e.clientY - rect.top;
    },

    //-----------------------------
    onMouseDown: function (self, e)
    {
        self.actions['fire0'] = true;
        self.mouse.click.x = self.mouse.x;
        self.mouse.click.y = self.mouse.y;
    },

    //-----------------------------
    onMouseUp: function (self, e)
    {
        self.actions['fire0'] = false;
    },

    //-----------------------------
    onKeyDown: function (self, e)
    {
        var action = self.bindings[e.keyCode];
        if (action)
        {
            self.actions[action] = true;
        }
    },

    //-----------------------------
    onKeyUp: function (self, e)
    {
        var action = self.bindings[e.keyCode];
        if (action)
        {
            self.actions[action] = false;
        }
    }
});

gInputEngine = new InputEngineClass();