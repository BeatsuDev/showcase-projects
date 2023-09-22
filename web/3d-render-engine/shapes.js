function vertex(x, y, z) { return {x:x,y:y,z:z} }


class Shape {
	constructor(x, y, z, faces) {
		this.x = x
		this.y = y
		this.z = z
		this.faces = faces
	} 

	rotate(x, y, z) {
		this.faces.forEach( face => {
			face.forEach( vertex => {

				
				
			})
		})
	}
}


function loadObj(objFile) {
	var vertexPool = [0]

	objFile.forEach(line => {
		let type = line[0]
		let data = line.substring(2, Infinity)

		switch (type) {
			case 'v':
				let split = data.split(' ') 
				vertexPool.push(split[0], split[1], split[2])
				break

			case 'f':
				break
		}
	})
}

function createCube(x,y,z,s) {
	let offset = s/2

	return {
		x: x,
		y: y,
		z: z,
		scale: s,

		rotate: function (x, y, z) {
			this.faces.forEach( face => {
				face.forEach( vertex => {

					
					
				})
			})
		},

		faces: [
			// Back face
			[
				vertex(x-offset, y-offset, z+offset),
				vertex(x+offset, y-offset, z+offset),
				vertex(x+offset, y+offset, z+offset),
				vertex(x-offset, y+offset, z+offset)
			],

			// Front face
			[
				vertex(x-offset, y-offset, z-offset),
				vertex(x+offset, y-offset, z-offset),
				vertex(x+offset, y+offset, z-offset),
				vertex(x-offset, y+offset, z-offset)
			],

			// Left face
			[
				vertex(x-offset, y-offset, z+offset),
				vertex(x-offset, y-offset, z-offset),
				vertex(x-offset, y+offset, z-offset),
				vertex(x-offset, y+offset, z+offset)
			],

			// Right face
			[
				vertex(x+offset, y+offset, z+offset),
				vertex(x+offset, y+offset, z-offset),
				vertex(x+offset, y-offset, z-offset),
				vertex(x+offset, y-offset, z+offset)
			],

			// Top face
			[
				vertex(x-offset, y+offset, z+offset),
				vertex(x+offset, y+offset, z+offset),
				vertex(x+offset, y+offset, z-offset),
				vertex(x-offset, y+offset, z-offset)
			],

			// Bottom face
			[
				vertex(x-offset, y-offset, z+offset),
				vertex(x+offset, y-offset, z+offset),
				vertex(x+offset, y-offset, z-offset),
				vertex(x-offset, y-offset, z-offset)
			]
		]
	}
}

cubes = [
	createCube(0, 0, 20, 5)
] 

function render() {
	ctx.clearRect(0, 0, canvas.width, canvas.height)

	cubes.forEach( cube => renderVertices(cube.faces) )
	requestAnimationFrame(render)
}

requestAnimationFrame(render)