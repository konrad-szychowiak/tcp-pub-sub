import {Store} from "../main/Store";
import {WebContents} from "electron";
import {reEmmit} from "./reEmmit.decorator";
import Buffer from "buffer";

export class TcpMiddleware {
  private wc: Electron.WebContents;

  private conversations: Store;

  constructor(webContents: WebContents, store: Store) {
    // console.log({webContents})
    this.wc = webContents;
    this.conversations = store;
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
  onData(data: Buffer) {
    return data.toString()
  }

  // fixme: i'm a mock
  @reEmmit('app:list-conversations')
  onListConversations() {
    return this.conversations.conversations;
  }

  // @reEmmit('pack:list')
  // static listConversations() {
  // }
  //
  // @reEmmit('pack:new')
  // static newMessage() {
  // }
  //
  // static subscribeToConversation() {
  // }
  //
  // static createConversation() {
  // }
  //
  // static postMessage() {
  // }
  //
  // static deleteConversation() {
  // }
}