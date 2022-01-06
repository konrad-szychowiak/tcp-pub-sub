import net from "net";
import {createUser} from "./ask.js";
// import {app} from "electron";
import {Command} from "commander";
import {DEFAULT_HOST, DEFAULT_PORT} from "../client.config.js";
const cli = new Command();

cli
    .version('0.0.1')
    .option('-p, --port <PORT>', "TCP Socket's port")
    .option('-a, --host <HOST>', "TCP Socket's address")

cli.parse(process.argv)

const options = cli.opts()
console.log({options})

const user = await createUser()
await user.action();

const HOST = options.host ?? DEFAULT_HOST;
const PORT = options.port ?? DEFAULT_PORT;


const client = new net.Socket();


client.connect(PORT, HOST, function () {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
});

// Add a 'data' event handler for the client socket
// data is what the server sent to this socket
client.on('data', function (data) {
    user.onData(data);
    client.destroy();
});

// Add a 'close' event handler for the client socket
client.on('close', function () {
    console.log('Connection closed');
});