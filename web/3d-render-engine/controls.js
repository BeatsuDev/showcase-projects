var camera = {
	position: {
		x: 0,
		y: 0,
		z: -5
	},
	rotation: {
		long: 0,
		lat: 0,
		swivel: 0
	}
}

setInterval(() => {
	// Right, up, in movement
	camera.position.x += 0.1 * movement['d']
	camera.position.y += 0.1 * movement['Shift']
	camera.position.z += 0.1 * movement['w']

	// Left, down, out movement
	camera.position.x -= 0.1 * movement['a']
	camera.position.y -= 0.1 * movement[' ']
	camera.position.z -= 0.1 * movement['s']
}, 10)

// Track movement to mouse movement
var trackLook = e => {
	camera.rotation.lat -= e.movementX / 10
	camera.rotation.long -= e.movementY / 10
}

window.onmousedown = () => window.addEventListener('mousemove', trackLook)
window.onmouseup = () => window.removeEventListener('mousemove', trackLook)


// Zoom in and out
window.onmousewheel = e => {
	FOV += e.deltaY/100
	console.log(FOV)
}

// Keep track of which buttons are held
var movement = {
	'w': false,
	'a': false,
	's': false,
	'd': false,
	' ': false,
	'Shift': false
}

// WASD movement
window.onkeydown = e => { movement[e.key] = true }
window.onkeyup = e => { movement[e.key] = false }