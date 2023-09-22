class Vector {
	constructor(x,y,z) {
		this.x = x
		this.y = y
		this.z = z
	}

	get length() {
		return Math.sqrt(this.x*this.x + this.y*this.y + this.z*this.z)
	}

	get normalised() {
		// Round off length avoid infinite recurrsion
		return this.length.toFixed(10) == 1 ? this.multiply(1/this.length) : this
	}

	get polar() {
		var lat = this.z ? Math.PI - Math.atan(this.x / this.z) : 0
		var long = this.y ? Math.PI - Math.atan(this.x / this.y) : 0
		return {lat:lat, long:long}
	}

	dot(vector) {
		return this.x * vector.x + this.y * vector.y + this.z * vector.z
	}

	cross(vector) {
		return new Vector(
			this.y * vector.z - this.z * vector.y,
			this.z * vector.x - this.x * vector.z,
			this.x * vector.y - this.y * vector.x
		)
	}

	add(vector) {
		return new Vector(
			this.x + vector.x,
			this.y + vector.y,
			this.z + vector.z
		)
	}

	subtract(vector) {
		return new Vector(
			this.x - vector.x,
			this.y - vector.y,
			this.z - vector.z
		)
	}

	multiply(scalar) {
		return new Vector(
			this.x * scalar,
			this.y * scalar,
			this.z * scalar
		)
	}
}