import {WebContents} from 'electron'
import {reEmmit} from "./reEmmit.decorator";
import {Socket} from "net";
import * as Buffer from "buffer";

export class TcpMiddleware {
  private wc: Electron.WebContents;

  constructor(webContents: WebContents) {
    // console.log({webContents})
    this.wc = webContents;
    // console.log({wc: this.wc})
  }

  /**
   * Translate socket's `'connect'` to custom `'tcp-connected'` event.
   *
   * Handle `'connect'` event form node's net Socket and re-emmit it as a custom event handled by
   * the renderer process.
   */
  @reEmmit('tcp-connected', true)
  onConnect() {
    return 'Connected to the server'
  }

  @reEmmit('tcp-data')
  onData(data: Buffer)
  {
    return data.toString()
  }
}