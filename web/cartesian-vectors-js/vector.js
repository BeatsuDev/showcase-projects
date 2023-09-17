class Vector {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    get length() { return Math.sqrt(this.x*this.x + this.y*this.y) }
    get angle() { return Math.atan(this.y / this.x) }
    get normalized() {
        var copy = Object.assign(new Vector(0, 0), this);
        copy.length = 1;
        return copy;
    }
    set length(targetLength) {
        var oldLength = this.length;
        var factor = targetLength / oldLength;
        this.x *= factor;
        this.y *= factor;
    }
    withLength(targetLength) {
        var oldLength = this.length;
        var factor = targetLength / oldLength;
        var newx = this.x * factor;
        var newy = this.y * factor;
        return new Vector(newx, newy);
    }
    rotate(angle) {
        var x2 = Math.cos(angle)*this.x - Math.sin(angle)*this.y;
        var y2 = Math.sin(angle)*this.x + Math.cos(angle)*this.y;
        return new Vector(x2, y2);
    }    
    add(vector) {
        return typeof(vector) == "number" ? 
          new Vector(this.x+vector, this.y+vector) : new Vector(this.x+vector.x, this.y+vector.y);
    }
    subtract(vector) {
        return typeof(vector) == "number" ? 
          new Vector(this.x-vector, this.y-vector) : new Vector(this.x-vector.x, this.y-vector.y);
    }
    multiply(scalar) { return new Vector(this.x * scalar, this.y * scalar) }
    divide(scalar) { return this.multiply(1/scalar) }

    plus(vector) {return this.add(vector)}
    minus(vector) {return this.subtract(vector)}
    times(scalar) {return this.multiply(scalar)}
    dividedBy(scalar) {return this.multiply(1/scalar)}

    static get random() { return new Vector(Math.random()*2-1, Math.random()*2-1).normalized }
    static dot(vector1, vector2) { return vector1.x*vector2.x + vector1.y*vector2.y }
    static multiply(vector, scalar) { return new Vector(vector.x*scalar, vector2.y*scalar) }
    static divide(vector, scalar) { return new Vector(vector.x/scalar, vector2.y/scalar) }
}
