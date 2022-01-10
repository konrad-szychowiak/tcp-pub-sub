import {app, ipcMain} from 'electron';
import path from "path";
import net from "net";
import * as process from "process";
import {setupWindow} from "./main/index";
import {TcpMiddleware} from "./tcp";
import {fromEvent} from "baconjs";
import {Buffer} from "buffer";


app.once('ready', () => {
  console.log('App is ready');
  const window = setupWindow()

  const indexHTML = path.join(__dirname + '/renderer' + '/index.html');

  /**
   * Start listening to the events from Renderer
   * once the window is ready
   */
  window.loadFile(indexHTML)
    .then(() => {
    ipcMain.on('client-exit', (event, code?: number) => {
      app.exit(code)
    })

    // ipcMain.on("toMain", (event, arg) => {
    //   console.log(`connect with options: ${arg}`)
    //   window.webContents.send("fromMain", 'hello');
    // });


    ipcMain.on('tcp-connection-details', (event, payload: { host: string, port: number }) => {
      const client = new net.Socket();
      const tcpMiddleware = new TcpMiddleware(window.webContents)

      const {host, port} = payload;
      console.log(`connect with options:`, payload)

      client.connect(port, host, async function () {
        await new Promise(resolve => setTimeout(resolve, 5000));
        // todo
        tcpMiddleware.onConnect()
        console.log('CONNECTED TO: ' + host + ':' + port);
        // window.webContents.send('fromMain', `CONNECTED TO: ${host}:${port}`);
      });

      // Add a 'data' event handler for the client socket
      // data is what the server sent to this socket
      client.on('data', function (data) {
        console.log(process.argv0, data)
        // todo
        tcpMiddleware.onData(data)
        window.webContents.send('fm', data.toString());
        client.destroy()
      });

      let allData = fromEvent(client, 'data', (buffer: Buffer) => buffer.toString())
        .onValue(v => console.log({v}))

      // Add a 'close' event handler for the client socket
      client.on('close', function () {
        console.log('Connection closed');
      });
    })
  });
});

