function Particle(position, options={}) {
    this.position = position;
    this.velocity = options.velocity ? options.velocity : new Vector(0, 0);
    this.color = options.color ? options.color : "#fff";
    this.radius = options.radius ? options.radius : 1;
    this.static = options.static ? options.static : false;
    this.options = options;


    this.move = function(timefactor) {
        if (this.options.static) return
        this.position = this.position.add(this.velocity.times(timefactor));
    }

    this.draw = function(canvasContext) {
        ctx.beginPath();
        ctx.fillStyle = this.color;
        canvasContext.arc(this.position.x, this.position.y, this.radius, 0, 2*Math.PI);
        ctx.fill();
    }
}