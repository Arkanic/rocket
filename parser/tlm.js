const path = require("path");
const {exec} = require("child_process");
const {exit} = require("process");

if(process.argv.length < 3) {
    console.log(`Usage: node tlm.js <FOLDER>\nWhere <FOLDER> is the copied telemetry data`);
    exit(1);
}

console.log("---- TLM ----\nRocket Telemetry Parser (v3)");

let folder = process.argv[2];

console.log("Starting ffmpeg...");
let framesdir = path.join(__dirname, folder, "/frames/");
exec(`ffmpeg -framerate ${12} -i ${path.join(framesdir, "frame-%d.jpg")} ${path.join(framesdir, "video.mp4")}`, (error, stdout, stderr) => {
    if(error) {
        console.log(`ERR. Is FFMPEG installed?\n${error}`);
        exit(1);
    }

    console.log("finished.");
});