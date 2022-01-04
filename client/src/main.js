import net from "net";
import {createUser} from "./ask.js";

const HOST = '127.0.0.1';
const PORT = 8080;

const client = new net.Socket();

const user = await createUser()
await user.action();

client.connect(PORT, HOST, function() {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
});
let i = 0;
// Add a 'data' event handler for the client socket
// data is what the server sent to this socket
client.on('data', function(data) {
    user.onData(data);
    client.destroy();
});

// Add a 'close' event handler for the client socket
client.on('close', function() {
    console.log('Connection closed');
});