function Particle(id, position) {
	this.id = id;
	this.position = position;
}

var particles = [];

function getParticle(id) {
	for (var i = 0; i < particles.length; i++) {
		if (particles[i].id == id) return particles[i];
	}
	return null;
}

function addPoint(id, x, y, z) {
	if (particles[id].pos.length == 10) {
		particles[id].pos.splice(0, 1);
	}

	let point = new THREE.Vector3(x, y, z);
	particles[id].pos.push(point);
}

var scene;
var camera;
var renderer;

document.addEventListener('DOMContentLoaded', function() {
	var socket = io();

	setupScene();
	//draw();

	socket.on('data', (res) => {
		res = JSON.parse(res);
		res.forEach((item) => {
			draw(item.x, item.y, 0.0);
			// var particle = getParticle(item.id);
			// if (particle == null) {
			// 	particle = new Particle(particles.length, item.x, item.y, 0.0);
			// 	particles.push(particle);
			// } else {
			// 	addPoint(particle.id, item.x, item.y, 0.0);
			// 	draw(particle.id);
			// }
		});
	});

	document.getElementById('start_simulation').onclick = () => {
		socket.emit('startSimulation', {});
	};
});

function setupScene() {
	scene = new THREE.Scene();
	camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.1, 1000 );
	
	renderer = new THREE.WebGLRenderer();
	renderer.setSize( 0.8 * window.innerWidth, 0.8 * window.innerHeight );
	document.body.appendChild( renderer.domElement );

	var controls = new THREE.OrbitControls(camera, renderer.domElement);

	var geometry = new THREE.BoxGeometry( 1, 1, 1 );
	var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
	cube = new THREE.Mesh( geometry, material );
	scene.add( cube );

	camera.position.z = 5;

	animate();
}

function animate() {
	requestAnimationFrame( animate );

	cube.rotation.x += 0.01;
	cube.rotation.y += 0.01;

	renderer.render( scene, camera );
}

// function draw() {
// 	const geometry = new THREE.BoxGeometry( 1, 1, 1 );
// 	const material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
// 	const cube = new THREE.Mesh( geometry, material );
// 	scene.add( cube );

// 	camera.position.z = 5;

// 	animate(cube);
// }

// function animate(obj) {
// 	requestAnimationFrame( animate );

// 	obj.rotation.x += 0.01;
// 	obj.rotation.y += 0.01;

// 	renderer.render( scene, camera );
// }