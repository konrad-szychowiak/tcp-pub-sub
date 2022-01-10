import {Conversation} from "./Conversation";

export class Store {
  // fixme: i'm a mock
  last_id = 0;

  published: number[] = []
  subscribed: number[] = []
  unsubscribed: number[] = []

  conversations: Conversation[] = [
    new Conversation(this.last_id++, 'Hello', ['Hello!']),
    new Conversation(this.last_id++, 'World', ['World!']),
    new Conversation(this.last_id++, 'Ala ma kota', ['Ala...', '... ma...', '... kota!']),
  ]

  // fixme: mock
  addConversation(name: string)
  {
    this.conversations.push(new Conversation(this.last_id++, name, [], true))
  }

  // fixme: mock
  deleteConversationById(id: number)
  {
    this.conversations = this.conversations.filter(el => el.id !== id)
  }
}