import net from "net";
// import {app} from "electron";
import {Command} from "commander";
const DEFAULT_HOST = '127.0.0.1';
const DEFAULT_PORT = 8080;
const cli = new Command();

cli
    .version('0.0.1', '-v, --version', 'output the current version')
    .option('-p, --port <PORT>', "TCP Socket's port")
    .option('-a, --host <HOST>', "TCP Socket's address")

cli.parse(process.argv)

const options = cli.opts()
console.log({options})

const HOST = options.host ?? DEFAULT_HOST;
const PORT = options.port ?? DEFAULT_PORT;

const client = new net.Socket();

client.connect(PORT, HOST, function () {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
});

// Add a 'data' event handler for the client socket
// data is what the server sent to this socket
client.on('data', function (data) {
    console.log(data.toString())
    client.destroy();
});

// Add a 'close' event handler for the client socket
client.on('close', function () {
    console.log('Connection closed');
});