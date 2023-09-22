var lastTimeCheck = performance.now();

function physicsloop() {
    time.deltaTime = (performance.now() - lastTimeCheck) / 10000;
    lastTimeCheck = performance.now();
    particles.forEach(particle => particle.move(time.deltaTime));
    framecall();
}   

function drawloop() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawcall();
    requestAnimationFrame(drawloop);
}


var fps = 50; 
requestAnimationFrame(drawloop);
setInterval(physicsloop, 1000/fps);