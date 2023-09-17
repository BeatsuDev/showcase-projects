[![MIT License](https://badgen.net/badge/license/MIT/blue)](https://opensource.org/licenses/MIT)
![I want more badges](https://badgen.net/badge/i%20want/more%20badges/green "But since it's NTNUs instance of Gitlab, it won't allow me :(")

# 2D Cartesian Vectors in Javascript
This is a simple Vector class for storing and manipulating mathematical two-dimensional cartesian vectors. They can have many different use cases that I will demonstrate below. The syntax is heavily inspired by Unity's [Vector2 class](https://docs.unity3d.com/ScriptReference/Vector2.html). To go directly to the list of methods and properties available, [click here](#list-of-methods-and-properties).

### Example 1: Using it to store an objects' position
Let's say you're creating a top-down simple simulation of our solar system. You want to store the planets as objects with a position, and velocity (among other things irrelevant to this example). Since 2d-cartesian Vectors in principle just store an x-coordinate and a y-coordinate, it's a great way to store positions in a 2d coordinate system. 
```javascript
class Planet {
    constructor(position : Vector, velocity : Vector) {
        this.position = position;
        this.velocity = velocity;
    }
}
``` 
> Note: In the examples I might use typescript syntax some places for clarification only.

The benefit of using Vectors in this way is that we now can do mathematical operations on them. For example, finding the distance between two planets is as simple as:
```javascript
earth = new Planet(Vector.zero, Vector.zero);
mars = new Planet(new Vector(50, 50), Vector.zero);
distance = earth.position
                .minus(mars.position)
                .length;
```

### Example 2: Adding forces
Imagine you have two planets that have a gravitational attraction force towards each other. They both have a velocity in different directions and magnitudes. Let's say the attraction force at the given moment gives an acceleration of 30 units per second squared on the first planet. This acceleration should work towards the other planet. This is done as such:
```javascript
planet1AddedVelocity = planet2.position
                              .minus(planet1.position)
                              .withLength(30);
planet1.velocity = planet1.velocity.plus(planet1AddedVelocity.times(timeDelta));
```
Alternatively, you can set the length of the Vector between the planets afterwards.
```javascript
planet1AddedVelocity = planet2.position.minus(planet1.position);
plante1AddedVelocity.length = 30;
planet1.velocity = planet1.velocity.plus(planet1AddedVelocity.times(timeDelta));
```

# List of methods and properties
### Vector

### `.add(vector)`
-	 `vector` : Vector 

Alias: `.plus(vector)`
Return type: [Vector](#vector)

### `.subtract(vector)`
-	 `vector` : Vector 

Alias: `.minus(vector)`
Return type: [Vector](#vector)

### `.multiply(scalar)`
-	 `scalar` : number 

Alias: `.times(vector)`
Return type: [Vector](#vector)

### `.divide(scalar)`
-	 `scalar` : number

Alias: `.dividedBy(vector)`
Return type: [Vector](#vector)

### `.withLength(targetLength)`
-	 `targetLength` : number

Return type: [Vector](#vector)

### `.rotate(angle)`
-	 `angle` : number

The angle is given in radians.
Return type: [Vector](#vector)

### `.length`
### `.angle`
### `.normalized`

### Static methods and properties

### `.dot(vector1, vector2)` 
-	`vector1` : Vector
-	`vector2` : Vector

Calculates the dot product of the two given vectors.
Return type: [Vector](#vector)

### `.random`
Returns a Vector pointing in a random direction.

# Todo list
Knowing myself, I might at any point just stop working on this project. Feel free to work on any of the below features, or something else you find interesting and nice to add!
- [ ] Add CI testing
- [ ] Add full-project examples of uses
- [ ] Support for polar coordinate vectors
- [ ] Add 3D Vector class
- [ ] Add n-th dimension vector class
- [ ] Typescript rewrite
