import enquirer from "enquirer";
import {Publisher, Subscriber} from "./user.js";

const {Select, Input, Confirm} = enquirer;


const whatMode = new Select({
    name: 'color',
    message: 'Are you here to publish or subscribe?',
    choices: ['publish', 'subscribe']
});

const whatMessage = () => new Input({
    message: 'What is your message to the world?'
})

async function sendMessage() {
    console.error('<Continue?> [N] ctrl+C [Y] message bellow')
    console.log(await (whatMessage()).run())
}

async function publish() {
    console.error('REQ a new conversation')
    console.error('await RES conversation id')
    while (true) await sendMessage()
}

async function connectByID() {
    const wasOK = async () => new Confirm({
        name: 'q',
        message: 'was the id ok ((debug))?'
    }).run()

    const id = await (new Input({
        message: 'Id of the channel'
    }).run())
    console.error(`REQ conversation with id = ${id}`)

    return await wasOK()
}

async function subscribe() {
    while (!await connectByID()) {
    }
}

export async function createUser() {
    // ask user for operation mode
    const mode = await whatMode.run()
    console.log({mode});

    // create User based on that mode
    if (mode === 'publish') return new Publisher().addAction(publish);
    return new Subscriber().addAction(subscribe);
}

// const mode = await whatMode.run()
// if (mode === 'publish') await publish();
// await subscribe();