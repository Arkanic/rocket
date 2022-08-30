const fs = require("fs");
const path = require("path");
const { exit } = require("process");

let dirname = path.join(__dirname, process.argv[2]);
let datdir = path.join(dirname, "dat");

let outdir = path.join(__dirname, "out");
let jsondir = path.join(outdir, "json");

let data = {};

let files = fs.readdirSync(datdir).filter((f) => f.startsWith("dat-"));
for(let file of files) {
    const dat = fs.readFileSync(path.join(datdir, file), "utf-8");
    
    let json = {};
    let millis = parseInt(file.split(".")[0].split("dat-")[1]);
    console.log(`At ${millis}`);

    const lines = dat.split("\n");
    for(let line of lines) {
        let parts = line.split(": ");
        json[parts[0]] = isNaN(parts[1]) ? parts[1] : parseFloat(parts[1]);
    }

    data[millis] = json;
    fs.writeFileSync(path.join(jsondir, `${millis}.json`), JSON.stringify(json));
}

fs.writeFileSync(path.join(outdir, "all.json"), JSON.stringify(data));

// data interpretation

let framerates = [];

for(let millis in data) {
    let frame = data[millis];

    if(frame.framerate) framerates.push(frame.framerate);
}

let framerate = framerates.reduce((a, b) => a + b) / framerates.length;
console.log(`Average framerate is ${framerate}, avg to ${Math.round(framerate)}`);

exit(Math.round(framerate)); // return the approx framerate to parse.sh