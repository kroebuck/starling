console.log("hello");

document.addEventListener('DOMContentLoaded', function() {
	var socket = io();

	socket.on('data', (res) => {
		console.log(res.data);
	});

	document.getElementById('start_simulation').onclick = () => {
		socket.emit('startSimulation', {});
	};
});

// socket call to server
	// have server run cpp & send back

// listen for cpp data
	// display