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

function draw(canvas, x, y, xNew, yNew) {
	var ctx = canvas.getContext("2d");
	ctx.moveTo(x, y);
	ctx.lineTo(xNew, yNew);
	ctx.stroke();
}

document.addEventListener('DOMContentLoaded', function() {
	var socket = io();

	socket.on('data', (res) => {
		res = JSON.parse(res);
		res.forEach((item) => {
			var body = getBody(item.id);
			if (body == null) {
				body = new Body(item.id, item.m, item.x, item.y, item.vx, item.vy);
				bodies.push(body);
			} else {
				var canvas = document.getElementById('canvas');
				draw(canvas, body.x, body.y, item.x, item.y);
			}
		});
	});

	document.getElementById('start_simulation').onclick = () => {
		socket.emit('startSimulation', {});
	};
});