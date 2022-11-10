const express = require("express")
const app = express()
const PORT = 200
app.get('/', function(req, res) {
    res.sendFile(__dirname + "/WEB-LAB2.html");
});
const server = app.listen(PORT, function() {
    console.log("server running in server: " + PORT);
});
const SocketServer = require("ws").Server;
const wss = new SocketServer({ server });
value = "0";
wss.on("connection", function(ws) {
    console.log('Client Connected');
    ws.send(value);
    ws.on("message", function(msg) {
        //   console.log(msg);
        value = msg + "";
        console.log(value);
        broadcast(value);
    });

    ws.on("close", function() {
        console.log("Client Left");
    });
});

function broadcast(msg) {
    wss.clients.forEach(function(client) {
        if (client.readyState === client.OPEN) {
            client.send(msg);
        }
    });
}