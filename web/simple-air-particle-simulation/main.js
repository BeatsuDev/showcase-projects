const particles = [];

var position = new Vector(canvas.width/2, canvas.height/2);
particles.push(new Particle(position, {static:true, radius:150}));

var id = setInterval(() => {
    for (let i = 0; i < 100; i++) {
        var position = new Vector(canvas.width, Math.random()*canvas.height);
        particles.push(
            new Particle(position, { velocity: new Vector(-3000, 0) })
        );
    }
    if (particles.length >= 1000) clearInterval(id)
}, 50);


function framecall() {
    for (let i=0; i<particles.length; i++) {
        for (let j=i+1; j<particles.length; j++) {
            var p1 = particles[i];
            var p2 = particles[j];

            if (!p1 || !p2) continue

            var distance = p1.position.minus(p2.position).length;
            distance -= (p1.radius + p2.radius);

            if (!distance) debugger

            if (distance > 35) continue
            if (Math.abs(distance) < 1) continue

            
            // Collision with a static object (assuming a circle for now)
            if (distance < 0 && p1.static) {
                /* Fix new velocity angle for the colliding particle */
                // First calculate the angle from the static point to the colliding point
                var collisionX = p2.position.minus(p1.position).x;
                var collisionY = p2.position.minus(p1.position).y;
                var collisionAngle = Math.atan(collisionY / collisionX);

                // Make sure atan angle and collision point is in the same quadrant
                if ((collisionAngle > Math.PI/2 || collisionAngle < 3*Math.PI/2) && collisionX > 0) { collisionAngle -= Math.PI }
                else if ((collisionAngle > 0 || collisionAngle < Math.PI) && collisionY < 0) { collisionAngle -= Math.PI }

                // New velocity vector
                var newVelocity = new Vector( p2.velocity.x * Math.cos(collisionAngle), p2.velocity.y * Math.sin(collisionAngle) );
                p2.velocity = newVelocity;
                

                /* Fix new position for the colliding particle */
                var newPosition = p2.position.minus(p1.position);
                newPosition.length = p1.radius + p2.radius;
                p2.position = p1.position.plus(newPosition);
            }

            var force = 10**5 / distance + max(10**4 - 10**3*distance, 0);

            // if (p1.radius == 50 && distance < 15 && force > 10) debugger 

            // Add forces on p1
            p1Force = p1.position.minus(p2.position).normalized.times(force).times(time.deltaTime);
            p1.velocity = p1.velocity.plus(p1Force);

            // Add forces on p2
            p2Force = p2.position.minus(p1.position).normalized.times(force).times(time.deltaTime);
            p2.velocity = p2.velocity.plus(p2Force);
        }
    }

    // Despawn particles on left and spawn on right
    particles.forEach(particle => {
        if (particle.position.x < 0) {
            particles.splice(particles.indexOf(particle), 1);

            var position = new Vector(canvas.width, Math.random()*canvas.height);
            particles.push( new Particle(position, { velocity: new Vector(-3000, 0) }) );
        }

        
        if (particle.position.x >= canvas.width) {
            particle.position.x = min( canvas.width-0.01, max( 0, particle.position.x ));
            particle.velocity.x *= -1;
        }

        if (particle.position.y < 0 || particle.position.y > canvas.height) {
            particle.position.y = min( canvas.height-0.01, max( 0, particle.position.y ));
            particle.velocity.y *= -1;
        }
    });
}


function drawcall() {


    // Set square size and amount of particles before max opacity in square is achieved
    const squareSize = 32;
    const opacityThreshold = 5;

    for (let x=0; x<canvas.width; x+=squareSize) {
        for (let y=0; y<canvas.height; y+=squareSize) {
            // Divided into squares
            // Check how many pixels in the square
            var inSquare = particles.filter(p => (
                (p.position.x >= x && p.position.x < x+squareSize) &&
                (p.position.y >= y && p.position.y < y+squareSize)
            )).length;

            if (!inSquare) {
                var opacity = 0;
            } else {
                var opacity = min(inSquare/opacityThreshold, 1);
            }
            ctx.fillStyle = `rgba(255, 255, 255, ${opacity})`;
            ctx.fillRect(x, y, squareSize, squareSize);
        }
    }
    
    particles.forEach(particle => particle.draw(ctx));
    particles.filter(p => p.static).forEach(particle => particle.draw(ctx));
}