function Body(id, m, x, y, vx, vy) {
	this.id = id;
	this.m = m;
	this.x = x;
	this.y = y;
	this.vx = vx;
	this.vy = vy;
}

var bodies = [];

function getBody(id) {
	for (var i = 0; i < bodies.length; i++) {
		if (bodies[i].id == id) return bodies[i];
	}
	return null;
}

function draw(x, y) {
	let X = scale * x;
	let Y = scale * y;
	ctx.fillRect(X, Y, 1, 1);
	// ctx.fillRect(xNew, yNew, 5, 5);
	// ctx.moveTo(x, y);
	// ctx.lineTo(xNew, yNew);
	// ctx.stroke();
}

var canvas, ctx;
let scale = 0.3;

document.addEventListener('DOMContentLoaded', function() {
	var socket = io();
	canvas = document.getElementById('canvas');
	ctx = canvas.getContext("2d");
	ctx.translate(canvas.width/2, canvas.height/2);
	//ctx.fillStyle = "#FF0000";
	ctx.fillRect(0,0,2,2);
	//ctx.fillStyle = "#FFFFFF";

	socket.on('data', (res) => {
		res = JSON.parse(res);
		res.forEach((item) => {
			draw(item.x, item.y);
			// var body = getBody(item.id);
			// if (body == null) {
			// 	body = new Body(item.id, item.m, item.x, item.y, item.vx, item.vy);
			// 	bodies.push(body);
			// } else {
			// 	//var canvas = document.getElementById('canvas');
			// 	draw(body.x, body.y, item.x, item.y);
			// 	// update body
			// }
		});
	});

	document.getElementById('start_simulation').onclick = () => {
		socket.emit('startSimulation', {});
	};
});