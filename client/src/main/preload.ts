import {contextBridge, ipcRenderer} from "electron";

// Expose protected methods that allow the renderer process to use
// the ipcRenderer without exposing the entire object
contextBridge.exposeInMainWorld(
  "api", {
    send: (channel: string, data: any) => {
      ipcRenderer.send(channel, data);
    },
    on: (channel: string, callback: Function) => {
      ipcRenderer.on(channel, (event, ...args) => callback(event, ...args));
    },
    exit: (code?: number) => {
      ipcRenderer.send('client-exit', code)
    }
  }
);