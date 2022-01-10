// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.ts` to
// selectively enable features needed in the rendering
// process.

window.api.on("tcp-connected", (e, data) => {
    console.log(`Connected: `, data);
    document.getElementById('more').innerHTML = ''
    document.getElementById('server-res').innerHTML = data
});

window.api.on('fm', (e, data) => {
    console.error('fm event is deprecated')
})

window.api.on("fromMain", (e, data) => {
    console.warn('fromMain event is deprecated')
    console.log(`Received ${data} from main process`);
    document.getElementById('more').innerText = data
});

function handleConnect()
{
    const host = document.getElementById('host').value
    const port = document.getElementById('port').value
    window.api.send("tcp-connection-details", { host, port });
    document.getElementById('more').innerHTML = `<span class="loader"></span>`
}

function handleClientExit()
{
    window.api.exit()
}