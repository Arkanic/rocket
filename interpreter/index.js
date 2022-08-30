const express = require("express");

const app = express();

app.use(express.static("../out"));
app.use(express.static("pub"));

app.listen("8080", () => {
    console.log("Server Started.");
});