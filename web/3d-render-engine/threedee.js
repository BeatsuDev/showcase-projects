const winWidth = window.innerWidth
const winHeight = window.innerHeight
const middle = {x: winWidth/2, y: winHeight/2}

var FOV = 90

// Degrees to radians conversion
const rad = num => num/360 * 2*Math.PI


function drawPoint(x, y) {
	ctx.beginPath()
	ctx.fillStyle = 'green'
	ctx.arc(x, y, 5, 0, 2*Math.PI)
	ctx.fill()
	ctx.closePath()
}


function depthTransform(point) {
	// Return 2D coordinates of a 3D point
	const outside = {x: undefined, y: undefined}
	const ratio = winHeight/winWidth
	const {x, y, z} = point

	// Camera X Y Z directional vector
	var camDirection = new Vector(
		Math.sin(-rad(camera.rotation.lat)),
		Math.sin(-rad(camera.rotation.long)),
		Math.cos(rad(camera.rotation.lat))
	).normalised

	// Vector from camera to point
	var pointVector = new Vector(
		x - camera.position.x,
		y - camera.position.y,
		z - camera.position.z
	)

	var depth = camDirection.dot(pointVector)
	if (depth <= 0) return outside

	// 
	// Find deltaX and deltaY on projected plane
	//
	let deltaVector = pointVector.subtract(camDirection.multiply(depth))

	const eX = 2;
	const eY = 2;
	
	var deltaX = deltaVector.x
	var deltaY = deltaVector.y
	
	// Set projected screen size
	let opposite = depth * Math.tan( rad(FOV/2) )
	var projectedScreenX = opposite*2
	var projectedScreenY = projectedScreenX * ratio

	projectedX = deltaX / projectedScreenX * winWidth + winWidth/2
	projectedY = deltaY / projectedScreenY * winHeight + winHeight/2

	return {x: projectedX, y: projectedY}
}


function renderLine(p1, p2) {
	ctx.beginPath()
	var {x,y} = depthTransform(p1)
	ctx.moveTo(x,y)
	var {x,y} = depthTransform(p2)
	ctx.lineTo(x,y)

	ctx.lineWidth = 5
	ctx.strokeStyle = 'red'
	ctx.stroke()
}


function renderVertices(obj) {
	obj.forEach(face => {
		ctx.beginPath()
		ctx.strokeStyle = "white"

		points = [...face.map(depthTransform)]


		points.forEach( point => ctx.lineTo(point.x, point.y) )

		ctx.closePath()
		ctx.stroke()

		/*
		ctx.fillStyle = "rgba(255, 255, 255, 0.1)"
		ctx.fill()

		points.forEach( point => drawPoint(point.x, point.y) )
		*/
	})
}