var scene;
var camera;
var renderer;
var controls;

var particles = [];

const TAIL_LENGTH = 10; // number of previous points to use to draw tail
var PAUSED = false;

document.addEventListener('DOMContentLoaded', function() {
    var socket = io();

    setupScene();

    socket.on('data', (res) => {
        res = JSON.parse(res);
        res.forEach((item) => {
            if (getParticle(item.id) == null) createParticle(item.id);
            let newPosition = { x: item.x, y: item.y, z: item.z };
            getParticle(item.id).pos.push(newPosition);
        });
    });

    document.getElementById('start_button').onclick = () => {
        socket.emit('startSimulation', {});

        setupSimulationUI();
    };

    document.getElementById('play_pause_button').onclick = () => {
        PAUSED = !PAUSED;
        var btn = document.getElementById('play_pause_button');
        btn.innerHTML = PAUSED ? "⏵" : "⏸";
    };

    document.getElementById('reset_camera_button').onclick = () => {
        controls.reset();
    };
});

function setupSimulationUI() {
    var startBtn = document.getElementById('start_button');
    startBtn.style.display = 'none';

    var playpauseBtn = document.getElementById('play_pause_button');
    playpauseBtn.style.display = null;
    playpauseBtn.innerHTML = "⏸";
}

function setupScene() {
    // Basic THREE.js scene setup
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera( 50, window.innerWidth / window.innerHeight, 0.1, 1000 );
    camera.position.z = 50;
    renderer = new THREE.WebGLRenderer();
    renderer.setSize( 0.8 * window.innerWidth, 0.8 * window.innerHeight );
    document.body.appendChild( renderer.domElement );

    // Orbit Controls
    controls = new THREE.OrbitControls(camera, renderer.domElement);

    // Cartesian coordinate system axes
    const axesHelper = new THREE.AxisHelper( 5 );
    scene.add( axesHelper );

    animate();
}

function animate() {
    if (!PAUSED) {
        // Update particles
        if (particles.length > 0) {
            particles.forEach(p => {
                p.tail = generateTail(p);
            });
            updateParticlePositions();
        }
    }

    // Render scene
    requestAnimationFrame( animate );
    renderer.render( scene, camera );
}

function generateSphere() {
    var geometry = new THREE.SphereGeometry( 0.4 );
    let randomColor = "#" + ((1 << 24) * Math.random() | 0).toString(16).padStart(6, "0");
    var material = new THREE.MeshBasicMaterial( { color: randomColor } );
    var sphere = new THREE.Mesh( geometry, material );
    scene.add( sphere );

    return sphere;
}

function generateTail(particle) {
    if (particle.tail != null) scene.remove(particle.tail);

    if (particle.pos.length <= 1) return;

    let geometry = new THREE.Geometry();
    for (var i = 0; i < TAIL_LENGTH; i++) {
        let j = particle.posIndex - i;
        if (j < 0) break;
        let position = particle.pos[j];
        geometry.vertices.push( new THREE.Vector3( position.x, position.y, position.z ) );
    }
    let line = new THREE.Line(
        geometry,
        new THREE.LineBasicMaterial({ color: particle.body.material.color })
    );
    scene.add(line);

    return line;
}

function getParticle(id) {
    for (var i = 0; i < particles.length; i++) {
        if (particles[i].id == id) return particles[i];
    }
    return null;
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

function updateParticlePositions() {
    particles.forEach(p => {
        if (p.pos.length <= p.posIndex) return; // TODO: Track length ourself
        let next = p.pos[p.posIndex];
        p.body.position.x = next.x;
        p.body.position.y = next.y;
        p.body.position.z = next.z;
        p.posIndex++;
    });
}