import {Socket} from "net";
import {EventStream, fromEvent, Property} from "baconjs";
import {Buffer} from "buffer";

export class BaconSocket {
  private readonly _socket: Socket;
  private _dataStream: EventStream<string>;
  private _dataProperty: Property<string>;

  constructor() {
    this._socket = new Socket();
    this._dataStream = fromEvent(this._socket, 'data', (buffer: Buffer | string) => {
      if (buffer instanceof Buffer) return buffer.toString()
      return buffer
    })
    this._dataProperty = this._dataStream.toProperty()
  }

  get data(): Property<string> {
    return this._dataProperty
  }
}