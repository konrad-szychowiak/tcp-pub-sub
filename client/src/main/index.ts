import {BrowserWindow} from "electron";
import path from "path";

export function setupWindow()
{
  const win = new BrowserWindow({
    width: 600,
    height: 400,
    fullscreen: true,
    webPreferences: {
      preload: path.join(__dirname, "preload.js") // use a preload script
    }
  });
  win.webContents.openDevTools()
  return win
}