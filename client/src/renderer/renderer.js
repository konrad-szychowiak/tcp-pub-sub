// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.ts` to
// selectively enable features needed in the rendering
// process.

window.api.on("tcp-connected", (e, data) => {
    // todo
    // is showed if and only if a list of conversations is loaded
    // Alpine.store('view').connected()
    console.log(data)
});

window.api.on('app:list-conversations', (event, data) => {
    console.warn({event, data})
    Alpine.store('conversations').value = data
    const availableIDs = data.map(el => el.id)

    // update //
    const unsubscribed = Alpine.store('unsubscribed').value
    const subscribed = _.intersection(Alpine.store('subscribed').value, availableIDs)
    const authored = _.intersection(Alpine.store('authored').value, availableIDs)

    const subscribable = _.difference(availableIDs, _.union(authored, subscribed))

    console.log({subscribable})
    console.log({subscribed})
    console.log({authored})

    // save //
    Alpine.store('unsubscribed').value = subscribable
    Alpine.store('subscribed').value = subscribed
    Alpine.store('authored').value = authored

    // show //
    Alpine.store('view').connected()
})

window.api.on('fm', (e, data) => {
    console.error('fm event is deprecated')
})

window.api.on("fromMain", (e, data) => {
    console.warn('fromMain event is deprecated')
    console.log(`Received ${data} from main process`);
    document.getElementById('more').innerText = data
});

function handleConnect() {
    const host = Alpine.store('host')
    const port = Alpine.store('port')
    Alpine.store('view').connecting()
    window.api.send("tcp-connection-details", {host, port});
}

function handleClientExit() {
    window.api.exit()
}

let last_id = 0;
const conversationFactory = (name, msg, isPublisher = false) => ({id: last_id++, name, msg, isPublisher})

const initialConversations = [
    conversationFactory('Hello', ['Hello!']),
    conversationFactory('World', ['World!']),
    conversationFactory('Ala ma kota', ['Ala...', '... ma...', '... kota!']),
]

document.addEventListener('alpine:init', () => {
    Alpine.store('host', 'localhost')
    Alpine.store('port', '8080')
    Alpine.store('conversations', {
        value: [],
        get(_id) {
            return this.value.filter(el => el.id === _id)[0];
        },
        remove(id) {
            this.value = this.value.filter(el => el.id !== id)
        },
        postMessageIn(message, id) {
            const modified = this.get(id);
            this.remove(id)
            modified.msg.push(message)
            this.value.push(modified)
        }
    })
    Alpine.store('subscribed', {
        value: [],
        get() {
            return this.value
        },
        add(id) {
            this.value.push(id);
            return this.get();
        },
        remove(id) {
            this.value = this.value.filter(el => el !== id);
            return this.get();
        }
    })
    Alpine.store('unsubscribed', {
        value: [],
        get() {
            return this.value
        },
        add(id) {
            this.value.push(id);
            return this.get();
        },
        remove(id) {
            this.value = this.value.filter(el => el !== id);
            return this.get();
        }
    })
    Alpine.store('authored', {
        value: [],
        get() {
            return this.value
        },
        add(id) {
            this.value.push(id);
            return this.get();
        },
        remove(id) {
            this.value = this.value.filter(el => el !== id);
            return this.get();
        }
    })
    Alpine.store('activeConversation', {
        conv: undefined,
        set(id) {
            const foo = Alpine.store('conversations').get(id);
            console.log(foo)
            this.conv = foo;
        },
        getID() {
            if (this.conv)
                return this.conv.id
        },
        get name() {
            if (this.conv)
                return this.conv.name
        },
        get messages () {
            if (this.conv)
                return this.conv.msg
            return []
        },
        unset() {
            this.conv = undefined;
        },
        isActive() {
            return this.conv !== undefined;
        },
        postMessage(text) {
            Alpine.store('conversations').postMessageIn(text, this.getID())
            this.set(this.getID())
        }
    })
    Alpine.store('view', {
        state: 'logOut',
        isConnecting() {
            return this.state === 'connecting'
        },
        connecting() {
            this.state = 'connecting'
        },
        isConnected() {
            return this.state === 'connected'
        },
        connected() {
            this.state = 'connected'
        },
        isLoggedOut() {
            return this.state === 'logOut'
        },
        logOut() {
            this.state = 'logOut'
        },
    })
})

function subscribeTo(conversationId) {
    Alpine.store('unsubscribed').remove(conversationId)
    Alpine.store('subscribed').add(conversationId)
}

function unsubscribe(conversationId) {
    Alpine.store('activeConversation').unset()
    Alpine.store('subscribed').remove(conversationId)
    Alpine.store('unsubscribed').add(conversationId)
}

function publishConversation(name) {
    const newConversation = conversationFactory(name, [], true)
    console.log(newConversation)
    Alpine.store('conversations').value.push(newConversation)
    Alpine.store('authored').add(newConversation.id)
    window.api.send("app:create-conversation", {name});
}

function destroyPublished(id) {
    Alpine.store('activeConversation').unset()
    Alpine.store('conversations').remove(id)
    Alpine.store('authored').remove(id)
    window.api.send("app:delete-conversation", {id});
}
