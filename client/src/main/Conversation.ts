const conversationFactory = (id: number, name: string, msg: string[], isPublisher = false) =>
  ({id, name, msg, isPublisher})

type Message = string;

export class Conversation {
  id: number;
  name: string;
  isPublisher: boolean;
  messages: Message[];
  uuid: string;

  constructor(id: number, name: string, uuid: string, msg: string[] = [], isPublisher: boolean = false) {
    this.id = id;
    this.name = name;
    this.isPublisher = isPublisher;
    // this.messages = []
    // fixme
    this.messages = msg
    this.uuid = uuid;
  }

  postMessage(text: string)
  {
    this.messages.push(text)
  }
}