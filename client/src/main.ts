import {app, BrowserWindow, ipcMain} from 'electron';
import path from "path";
import net from "net";
import * as process from "process";
import {setupWindow} from "./main/index";
import {fromEvent} from "baconjs";
import {Buffer} from "buffer";
import {Store} from "./main/Store";
import {TcpMiddleware} from "./tcp/TcpMiddleware";
import {Pack} from "./tcp/Pack";


function setupActions(window: BrowserWindow): void {

  ipcMain.on('tcp-connection-details', (event, payload: { host: string, port: number }) => {
    const client = new net.Socket();
    const appState = new Store()
    const tcpMiddleware = new TcpMiddleware(window.webContents, appState)

    const {host, port} = payload;
    console.log(`connect with options:`, payload)


    ipcMain.on('client-exit', (event, code?: number) => {
      client.destroy()
      appState.resetAll();
      // app.exit(code)
    })

    ipcMain.on('app:unsubscribe', (event, payload: { id: number }) => {
      const {id} = payload;
      console.log(Pack.unsubscribe(id))
      client.write(Pack.unsubscribe(id))
    })

    ipcMain.on('app:subscribe', (event, payload: { id: number }) => {
      const {id} = payload;
      client.write(Pack.subscribe(id))
    });

    ipcMain.on('app:create-conversation', (event, payload: { name: string }) => {
      const {name} = payload
      const {uuid} = appState.createConversation(name)
      client.write(`C\t${name}\t${uuid};`);
    });


    ipcMain.on('app:post-msg', (event, payload: { id: number, text: string }) => {
      const {id, text} = payload
      client.write(Pack.post(id, text));
    });


    ipcMain.on('app:delete-conversation', (event, payload: { id: number }) => {
      const {id} = payload
      appState.deleteConversationById(id)
      client.write(Pack.del(id))
    });


    client.connect(port, host);

    client.on('connect', async () => {
      // await new Promise(resolve => setTimeout(resolve, 1000));
      // todo
      tcpMiddleware.onConnect()
      // await new Promise(resolve => setTimeout(resolve, 1000));
      // tcpMiddleware.onListConversations()
      console.log('CONNECTED TO: ' + host + ':' + port);
      // window.webContents.send('fromMain', `CONNECTED TO: ${host}:${port}`);
    })

    client.on('error', err => {
      tcpMiddleware.onConnectionError(err)
    })

    client.on('end', () => {
      tcpMiddleware.onEnd();
    })

    // Add a 'data' event handler for the client socket
    // data is what the server sent to this socket
    client.on('data', data => {
      console.log(process.argv0, data)
      // todo
      tcpMiddleware.onData(data)
      window.webContents.send('fm', data.toString());
    });

    // Add a 'close' event handler for the client socket
    client.on('close', () => {
      console.log('Connection closed');
    });
  })
}


app.once('ready', () => {
  console.log('App is ready');
  const window = setupWindow()

  const indexHTML = path.join(__dirname + '/renderer' + '/index.html');

  /**
   * Start listening to the events from Renderer
   * once the window is ready
   */
  window.loadFile(indexHTML)
    .then(() => setupActions(window));
});