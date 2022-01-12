import {Conversation} from "./Conversation";
import crypto from 'crypto';

export class Store {
  // fixme: i'm a mock
  last_id = 0;

  published: string[] = []
  subscribed: number[] = []
  unsubscribed: number[] = []

  conversations: Conversation[] = [
    // new Conversation(this.last_id++, 'Hello', 'a', ['Hello!']),
    // new Conversation(this.last_id++, 'World', 'w', ['World!']),
    // new Conversation(this.last_id++, 'Ala ma kota', 'k',['Ala...', '... ma...', '... kota!']),
  ]

  // fixme: mock
  createConversation(name: string)
  {
    const uuid = crypto.randomUUID();
    this.published.push(uuid);
    const convo = new Conversation(this.last_id++, name, uuid, [], true)
    this.conversations.push(convo);
    return convo;
  }

  resetConversations()
  {
    this.conversations = []
  }

  addConversation(conversation: Conversation)
  {
    if (this.published.indexOf(conversation.uuid) != -1) conversation.isPublisher = true;
    this.conversations.push(conversation);
  }

  // fixme: mock
  deleteConversationById(id: number)
  {
    this.conversations = this.conversations.filter(el => el.id !== id)
  }
}