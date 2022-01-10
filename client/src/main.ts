import {app, ipcMain} from 'electron';
import path from "path";
import net from "net";
import * as process from "process";
import {setupWindow} from "./main/index";
import {fromEvent} from "baconjs";
import {Buffer} from "buffer";
import {Store} from "./main/Store";
import {TcpMiddleware} from "./tcp/TcpMiddleware";
import {BrowserWindow} from 'electron';


function setupActions(window: BrowserWindow): void {

    ipcMain.on('client-exit', (event, code?: number) => {
      app.exit(code)
    })

    ipcMain.on('tcp-connection-details', (event, payload: { host: string, port: number }) => {
      const client = new net.Socket();
      const appState =  new Store()
      const tcpMiddleware = new TcpMiddleware(window.webContents, appState)

      const {host, port} = payload;
      console.log(`connect with options:`, payload)

      ipcMain.on('app:create-conversation', (event, payload: { name: string }) => {
        console.log(payload)
        const {name} = payload
        appState.addConversation(name)
        tcpMiddleware.onListConversations()
      })

      ipcMain.on('app:delete-conversation', (event, payload: { id: number }) => {
        console.log(payload)
        const {id} = payload
        appState.deleteConversationById(id)
        tcpMiddleware.onListConversations()
      })

      client.connect(port, host, async function () {
        await new Promise(resolve => setTimeout(resolve, 1000));
        // todo
        tcpMiddleware.onConnect()
        await new Promise(resolve => setTimeout(resolve, 1000));
        tcpMiddleware.onListConversations()
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