import {Store} from "../main/Store";
import {WebContents} from "electron";
import {reEmmit} from "./reEmmit.decorator";
import Buffer from "buffer";
import {Conversation} from "../main/Conversation";

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

  onData(data: Buffer) {
    const text = data.toString();
    text.replace(/\x00/g, '').split(';').filter(el => el && el.length > 0).forEach(message => {
      const [symbol,...args] = message.split('\t');
      // console.log(symbol, '->', args)
      switch (symbol) {
        case 'L': this.listConversations(args); break;
        case 'N': this.newMessage(parseInt(args[0]), args[1]); break;
        default: this.onGenericData(text);
      }
    })
    return text;
  }

  @reEmmit('tcp:data')
  onGenericData(text: string) {
    return text;
  }

  @reEmmit('app:list-conversations')
  listConversations(args: string[]) {
    this.conversations.resetConversations();
    for (let i = 0; i < args.length; i++)
    {
      this.conversations.addConversation(new Conversation(parseInt(args[i]), args[++i], args[++i], []))
    }
    return this.conversations.conversations;
  }

  @reEmmit('app:list-conversations')
  // @reEmmit('app:new-msg')
  newMessage(id: number, text: string) {
    this.conversations.conversations.filter(el => el.id === id)[0].postMessage(text);
    return this.conversations.conversations;
  }

  @reEmmit('app:connection-error')
  onConnectionError(error: Error)
  {
    return error
  }

  @reEmmit('app:server-end')
  onEnd()
  {
    return 'Server just closed. Retry later or try another server.'
  }


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