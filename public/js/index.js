
var scene;
var camera;
var renderer;

var particles = [];

document.addEventListener('DOMContentLoaded', function() {
    var socket = io();

    setupScene();

    socket.on('data', (res) => {
        res = JSON.parse(res);
        res.forEach((item) => {
            if (getParticle(item.id) == null) createParticle(item.id);
            let newPosition = { x: item.x, y: item.y, z: 0.0 };
            appendPosition(item.id, newPosition);
        });
    });

    document.getElementById('start_simulation').onclick = () => {
        socket.emit('startSimulation', {});
    };
});

function setupScene() {
    // Basic THREE.js scene setup
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera( 75, window.innerWidth / window.innerHeight, 0.01, 100 );
    camera.position.z = 50;
    renderer = new THREE.WebGLRenderer();
    renderer.setSize( 0.8 * window.innerWidth, 0.8 * window.innerHeight );
    document.body.appendChild( renderer.domElement );

    // Orbit Controls
    const controls = new THREE.OrbitControls(camera, renderer.domElement);

    // Cartesian coordinate system axes
    const axesHelper = new THREE.AxisHelper( 5 );
    scene.add( axesHelper );

    animate();
}

function animate() {
    // Update particles
    if (particles.length > 0) {
        particles.forEach(p => {
            drawTail(p);
        });
        moveParticles();
    }

    // Render scene
    requestAnimationFrame( animate );
    renderer.render( scene, camera );
}

function generateSphere() {
    var geometry = new THREE.SphereGeometry( 0.4 );
    let hue = "#" + ((1 << 24) * Math.random() | 0).toString(16).padStart(6, "0");
    var material = new THREE.MeshBasicMaterial( { color: hue } );
    var sphere = new THREE.Mesh( geometry, material );
    scene.add( sphere );

    return sphere;
}

function getParticle(id) {
    for (var i = 0; i < particles.length; i++) {
        if (particles[i].id == id) return particles[i];
    }
    return null;
}

function appendPosition(id, position) {
    var particle = getParticle(id);
    particle.pos.push(position);
}

function createParticle(id) {
    var particle = {
        id: id,
        body: generateSphere(),
        posIndex: 0,
        pos: [],
        tail: null
    };
    particles.push(particle);
}

function moveParticles() {
    particles.forEach(p => {
        if (p.pos.length <= p.posIndex) return; // TODO: Track length ourself
        let next = p.pos[p.posIndex];
        p.body.position.x = next.x;
        p.body.position.y = next.y;
        p.body.position.z = next.z;
        p.posIndex++;
    });
}

function drawTail(particle) {
    if (particle.tail != null) scene.remove(particle.tail);

    let geometry = new THREE.Geometry();
    for (var i = 1; i< 10; i++) {
        let j = particle.posIndex - i;
        if (j < 0) break;
        let position = particle.pos[j];
        geometry.vertices.push( new THREE.Vector3( position.x, position.y, position.z ) );
    }
    let line = new THREE.Line(
        geometry,
        new THREE.LineBasicMaterial({ color: 0x888888 })
    );
    scene.add(line);

    particle.tail = line;
}